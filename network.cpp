#include "network.h"
#include <iostream>
#include <algorithm>
#include <cctype>  // for std::tolower

namespace bht {

// CSVReader implementation
CSVReader::CSVReader(const std::string& filePath) {
    file.open(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }
    parseHeaders();
}

void CSVReader::parseHeaders() {
    if (!file.good()) return;
    
    std::string headerLine;
    if (std::getline(file, headerLine)) {
        auto headerFields = parseLine(headerLine);
        for (size_t i = 0; i < headerFields.size(); ++i) {
            headers[headerFields[i]] = static_cast<int>(i);
        }
    }
}

std::vector<std::string> CSVReader::parseLine(const std::string& line) {
    std::vector<std::string> fields;
    bool inQuotes = false;
    std::string field;
    
    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    fields.push_back(field); // Add the last field
    
    return fields;
}

std::string CSVReader::getField(const std::string& key) {
    auto it = headers.find(key);
    if (it == headers.end() || it->second >= static_cast<int>(currentRow.size())) {
        return "";
    }
    return currentRow[it->second];
}

std::string CSVReader::getField(const std::string& key, const std::string& defaultValue) {
    std::string value = getField(key);
    return value.empty() ? defaultValue : value;
}

bool CSVReader::next() {
    if (!file.good()) return false;
    
    std::string line;
    if (std::getline(file, line)) {
        currentRow = parseLine(line);
        return true;
    }
    return false;
}

bool CSVReader::hasNext() {
    return file.good();
}

void CSVReader::reset() {
    file.clear();
    file.seekg(0);
    parseHeaders();
}

// Network implementation
Network::Network(const std::string& directoryPath) {
    loadAgencies(directoryPath);
    loadCalendarDates(directoryPath);
    loadCalendars(directoryPath);
    loadLevels(directoryPath);
    loadPathways(directoryPath);
    loadRoutes(directoryPath);
    loadShapes(directoryPath);
    loadStopTimes(directoryPath);
    loadStops(directoryPath);
    loadTransfers(directoryPath);
    loadTrips(directoryPath);
}

std::vector<Stop> Network::search(const std::string& searchTerm) {
    std::vector<Stop> results;

    // Convert search term to lowercase for case-insensitive comparison
    std::string lowerSearchTerm = searchTerm;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(),
        [](unsigned char c) { return std::tolower(c); });

    // Search in stop names
    for (const auto& pair : stops) {
        const Stop& stop = pair.second;
        
        // Convert stop name to lowercase for case-insensitive comparison
        std::string lowerStopName = stop.name;
        std::transform(lowerStopName.begin(), lowerStopName.end(), lowerStopName.begin(),
            [](unsigned char c) { return std::tolower(c); });
        
        // Check if stop name contains the search term
        if (lowerStopName.find(lowerSearchTerm) != std::string::npos) {
            results.push_back(stop);
        }
    }

    return results;
}

// Utility methods
GTFSDate Network::parseDate(const std::string& dateStr) {
    GTFSDate date = {0, 0, 0};
    if (dateStr.length() >= 8) {
        try {
            date.year = static_cast<unsigned short>(std::stoi(dateStr.substr(0, 4)));
            date.month = static_cast<unsigned char>(std::stoi(dateStr.substr(4, 2)));
            date.day = static_cast<unsigned char>(std::stoi(dateStr.substr(6, 2)));
        } catch (...) {
            // Handle parsing errors
        }
    }
    return date;
}

GTFSTime Network::parseTime(const std::string& timeStr) {
    GTFSTime time = {0, 0, 0};
    
    if (timeStr.length() >= 8) {
        try {
            time.hour = static_cast<unsigned char>(std::stoi(timeStr.substr(0, 2)));
            time.minute = static_cast<unsigned char>(std::stoi(timeStr.substr(3, 2)));
            time.second = static_cast<unsigned char>(std::stoi(timeStr.substr(6, 2)));
        } catch (...) {
            // Handle parsing errors
        }
    }
    
    return time;
}

// Implement all the loading methods with placeholder functionality
void Network::loadAgencies(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/agency.txt");
        while (reader.next()) {
            Agency agency;
            agency.id = reader.getField("agency_id");
            agency.name = reader.getField("agency_name");
            agency.url = reader.getField("agency_url");
            agency.timezone = reader.getField("agency_timezone");
            agency.language = reader.getField("agency_lang", "");
            agency.phone = reader.getField("agency_phone", "");
            
            agencies[agency.id] = agency;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading agencies: " << e.what() << std::endl;
    }
}

void Network::loadCalendarDates(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/calendar_dates.txt");
        while (reader.next()) {
            CalendarDate calendarDate;
            calendarDate.serviceId = reader.getField("service_id");
            calendarDate.date = parseDate(reader.getField("date"));
            
            std::string exceptionType = reader.getField("exception_type", "0");
            if (!exceptionType.empty()) {
                try {
                    calendarDate.exception = static_cast<CalendarDateException>(std::stoi(exceptionType));
                } catch (...) {
                    calendarDate.exception = CalendarDateException_AddedDate; // Default value
                }
            } else {
                calendarDate.exception = CalendarDateException_AddedDate; // Default value
            }
            
            calendarDates.push_back(calendarDate);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading calendar dates: " << e.what() << std::endl;
    }
}

void Network::loadCalendars(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/calendar.txt");
        while (reader.next()) {
            Calendar calendar;
            calendar.serviceId = reader.getField("service_id");
            
            // Safe conversion with default values
            auto parseAvailability = [](const std::string& value) -> CalendarAvailability {
                if (value.empty()) return CalendarAvailability_NotAvailable;
                try {
                    return static_cast<CalendarAvailability>(std::stoi(value));
                } catch (...) {
                    return CalendarAvailability_NotAvailable;
                }
            };
            
            calendar.monday = parseAvailability(reader.getField("monday", "0"));
            calendar.tuesday = parseAvailability(reader.getField("tuesday", "0"));
            calendar.wednesday = parseAvailability(reader.getField("wednesday", "0"));
            calendar.thursday = parseAvailability(reader.getField("thursday", "0"));
            calendar.friday = parseAvailability(reader.getField("friday", "0"));
            calendar.saturday = parseAvailability(reader.getField("saturday", "0"));
            calendar.sunday = parseAvailability(reader.getField("sunday", "0"));
            
            calendar.startDate = parseDate(reader.getField("start_date", ""));
            calendar.endDate = parseDate(reader.getField("end_date", ""));
            
            calendars[calendar.serviceId] = calendar;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading calendars: " << e.what() << std::endl;
    }
}

void Network::loadLevels(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/levels.txt");
        while (reader.next()) {
            Level level;
            level.id = reader.getField("level_id");
            
            std::string levelIndex = reader.getField("level_index", "0");
            try {
                level.index = std::stoi(levelIndex);
            } catch (...) {
                level.index = 0; // Default value
            }
            
            level.name = reader.getField("level_name", "");
            
            levels[level.id] = level;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading levels: " << e.what() << std::endl;
    }
}

void Network::loadPathways(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/pathways.txt");
        while (reader.next()) {
            Pathway pathway;
            pathway.id = reader.getField("pathway_id");
            pathway.fromStopId = reader.getField("from_stop_id");
            pathway.toStopId = reader.getField("to_stop_id");
            
            std::string pathwayMode = reader.getField("pathway_mode", "0");
            try {
                pathway.mode = static_cast<PathwayMode>(std::stoi(pathwayMode));
            } catch (...) {
                pathway.mode = PathwayMode_Unset; // Default value
            }
            
            std::string isBidirectional = reader.getField("is_bidirectional", "0");
            try {
                pathway.isBidirectional = std::stoi(isBidirectional) != 0;
            } catch (...) {
                pathway.isBidirectional = false; // Default value
            }
            
            std::string length = reader.getField("length", "0");
            try {
                pathway.length = std::stof(length);
            } catch (...) {
                pathway.length = 0.0f; // Default value
            }
            
            std::string traversalTime = reader.getField("traversal_time", "0");
            try {
                pathway.traversalTime = std::stoi(traversalTime);
            } catch (...) {
                pathway.traversalTime = 0; // Default value
            }
            
            std::string stairCount = reader.getField("stair_count", "0");
            try {
                pathway.stairCount = std::stoi(stairCount);
            } catch (...) {
                pathway.stairCount = 0; // Default value
            }
            
            std::string maxSlope = reader.getField("max_slope", "0");
            try {
                pathway.maxSlope = std::stof(maxSlope);
            } catch (...) {
                pathway.maxSlope = 0.0f; // Default value
            }
            
            std::string minWidth = reader.getField("min_width", "0");
            try {
                pathway.minWidth = std::stof(minWidth);
            } catch (...) {
                pathway.minWidth = 0.0f; // Default value
            }
            
            pathway.signpostedAs = reader.getField("signposted_as", "");
            
            pathways[pathway.id] = pathway;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading pathways: " << e.what() << std::endl;
    }
}

void Network::loadRoutes(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/routes.txt");
        while (reader.next()) {
            Route route;
            route.id = reader.getField("route_id");
            route.agencyId = reader.getField("agency_id", "");
            route.shortName = reader.getField("route_short_name", "");
            route.longName = reader.getField("route_long_name", "");
            route.description = reader.getField("route_desc", "");
            
            std::string routeType = reader.getField("route_type", "0");
            try {
                route.type = static_cast<RouteType>(std::stoi(routeType));
            } catch (...) {
                route.type = RouteType_Bus; // Default value
            }
            
            route.color = reader.getField("route_color", "");
            route.textColor = reader.getField("route_text_color", "");
            
            routes[route.id] = route;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading routes: " << e.what() << std::endl;
    }
}

void Network::loadShapes(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/shapes.txt");
        while (reader.next()) {
            Shape shape;
            shape.id = reader.getField("shape_id");
            
            std::string lat = reader.getField("shape_pt_lat", "0");
            try {
                shape.latitude = std::stod(lat);
            } catch (...) {
                shape.latitude = 0.0; // Default value
            }
            
            std::string lon = reader.getField("shape_pt_lon", "0");
            try {
                shape.longitude = std::stod(lon);
            } catch (...) {
                shape.longitude = 0.0; // Default value
            }
            
            std::string seq = reader.getField("shape_pt_sequence", "0");
            try {
                shape.sequence = std::stoi(seq);
            } catch (...) {
                shape.sequence = 0; // Default value
            }
            
            shapes.push_back(shape);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading shapes: " << e.what() << std::endl;
    }
}

void Network::loadStopTimes(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/stop_times.txt");
        while (reader.next()) {
            StopTime stopTime;
            stopTime.tripId = reader.getField("trip_id");
            stopTime.arrivalTime = parseTime(reader.getField("arrival_time", "00:00:00"));
            stopTime.departureTime = parseTime(reader.getField("departure_time", "00:00:00"));
            stopTime.stopId = reader.getField("stop_id");
            
            std::string seq = reader.getField("stop_sequence", "0");
            try {
                stopTime.stopSequence = std::stoi(seq);
            } catch (...) {
                stopTime.stopSequence = 0; // Default value
            }
            
            std::string pickupType = reader.getField("pickup_type", "0");
            try {
                stopTime.pickupType = static_cast<PickupType>(std::stoi(pickupType));
            } catch (...) {
                stopTime.pickupType = PickupType_Regular; // Default value
            }
            
            std::string dropOffType = reader.getField("drop_off_type", "0");
            try {
                stopTime.dropOffType = static_cast<EDropOffType>(std::stoi(dropOffType));
            } catch (...) {
                stopTime.dropOffType = DropOffType_Regular; // Default value
            }
            
            stopTime.stopHeadsign = reader.getField("stop_headsign", "");
            
            stopTimes.push_back(stopTime);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading stop times: " << e.what() << std::endl;
    }
}

void Network::loadStops(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/stops.txt");
        while (reader.next()) {
            Stop stop;
            stop.id = reader.getField("stop_id");
            stop.code = reader.getField("stop_code", "");
            stop.name = reader.getField("stop_name", "");
            stop.description = reader.getField("stop_desc", "");
            
            std::string lat = reader.getField("stop_lat", "0");
            try {
                stop.latitide = std::stod(lat);
            } catch (...) {
                stop.latitide = 0.0; // Default value
            }
            
            std::string lon = reader.getField("stop_lon", "0");
            try {
                stop.longitude = std::stod(lon);
            } catch (...) {
                stop.longitude = 0.0; // Default value
            }
            
            std::string locationType = reader.getField("location_type", "0");
            try {
                stop.locationType = static_cast<LocationType>(std::stoi(locationType));
            } catch (...) {
                stop.locationType = LocationType_Stop; // Default value
            }
            
            stop.parentStation = reader.getField("parent_station", "");
            
            std::string wheelchairBoarding = reader.getField("wheelchair_boarding", "0");
            try {
                stop.wheelchairBoarding = static_cast<WheelchairAccessibility>(std::stoi(wheelchairBoarding));
            } catch (...) {
                stop.wheelchairBoarding = WheelchairAccessibility_NoInformation; // Default value
            }
            
            stop.platformCode = reader.getField("platform_code", "");
            stop.levelId = reader.getField("level_id", "");
            stop.zoneId = reader.getField("zone_id", "");
            
            stops[stop.id] = stop;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading stops: " << e.what() << std::endl;
    }
}

void Network::loadTransfers(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/transfers.txt");
        while (reader.next()) {
            Transfer transfer;
            transfer.fromStopId = reader.getField("from_stop_id");
            transfer.toStopId = reader.getField("to_stop_id");
            transfer.fromRouteId = reader.getField("from_route_id", "");
            transfer.toRouteId = reader.getField("to_route_id", "");
            transfer.fromTripId = reader.getField("from_trip_id", "");
            transfer.toTripId = reader.getField("to_trip_id", "");
            
            std::string transferType = reader.getField("transfer_type", "0");
            try {
                transfer.type = static_cast<TransferType>(std::stoi(transferType));
            } catch (...) {
                transfer.type = TransferType_Recommended; // Default value
            }
            
            std::string minTransferTime = reader.getField("min_transfer_time", "0");
            try {
                transfer.minTransferTime = std::stoi(minTransferTime);
            } catch (...) {
                transfer.minTransferTime = 0; // Default value
            }
            
            transfers.push_back(transfer);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading transfers: " << e.what() << std::endl;
    }
}

void Network::loadTrips(const std::string& directoryPath) {
    try {
        CSVReader reader(directoryPath + "/trips.txt");
        while (reader.next()) {
            Trip trip;
            trip.id = reader.getField("trip_id");
            trip.routeId = reader.getField("route_id");
            trip.serviceId = reader.getField("service_id");
            trip.headsign = reader.getField("trip_headsign", "");
            trip.shortName = reader.getField("trip_short_name", "");
            
            std::string direction = reader.getField("direction_id", "0");
            try {
                trip.direction = static_cast<TripDirection>(std::stoi(direction));
            } catch (...) {
                trip.direction = TripDirection_Inbound; // Default value
            }
            
            trip.blockId = reader.getField("block_id", "");
            trip.shapeId = reader.getField("shape_id", "");
            
            std::string wheelchairAccessible = reader.getField("wheelchair_accessible", "0");
            try {
                trip.wheelchairAccessible = static_cast<WheelchairAccessibility>(std::stoi(wheelchairAccessible));
            } catch (...) {
                trip.wheelchairAccessible = WheelchairAccessibility_NoInformation; // Default value
            }
            
            std::string bikesAllowed = reader.getField("bikes_allowed", "0");
            try {
                trip.bikesAllowed = static_cast<BikesAllowed>(std::stoi(bikesAllowed));
            } catch (...) {
                trip.bikesAllowed = BikesAllowed_NoInformation; // Default value
            }
            
            trips.push_back(trip);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading trips: " << e.what() << std::endl;
    }
}

} // namespace bht