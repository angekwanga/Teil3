#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>  // Add this for std::ifstream
#include <stdexcept> // For exception handling
#include "types.h"

namespace bht {

class CSVReader {
private:
    std::ifstream file;
    std::unordered_map<std::string, int> headers;
    std::vector<std::string> currentRow;

public:
    CSVReader(const std::string& filePath);
    std::string getField(const std::string& key);
    std::string getField(const std::string& key, const std::string& defaultValue);
    bool next();
    bool hasNext();
    void reset();

private:
    void parseHeaders();
    std::vector<std::string> parseLine(const std::string& line);
};

class Network {
public:
    // Public attributes as required
    std::unordered_map<std::string, Agency> agencies;
    std::vector<CalendarDate> calendarDates;
    std::unordered_map<std::string, Calendar> calendars;
    std::unordered_map<std::string, Level> levels;
    std::unordered_map<std::string, Pathway> pathways;
    std::unordered_map<std::string, Route> routes;
    std::vector<Shape> shapes;
    std::vector<StopTime> stopTimes;
    std::unordered_map<std::string, Stop> stops;
    std::vector<Transfer> transfers;
    std::vector<Trip> trips;

    // Constructor
    Network(const std::string& directoryPath);

    // Search method for Exercise 2
    std::vector<Stop> search(const std::string& searchTerm);

private:
    // Helper methods to load different file types
    void loadAgencies(const std::string& directoryPath);
    void loadCalendarDates(const std::string& directoryPath);
    void loadCalendars(const std::string& directoryPath);
    void loadLevels(const std::string& directoryPath);
    void loadPathways(const std::string& directoryPath);
    void loadRoutes(const std::string& directoryPath);
    void loadShapes(const std::string& directoryPath);
    void loadStopTimes(const std::string& directoryPath);
    void loadStops(const std::string& directoryPath);
    void loadTransfers(const std::string& directoryPath);
    void loadTrips(const std::string& directoryPath);

    // Utility methods
    GTFSDate parseDate(const std::string& dateStr);
    GTFSTime parseTime(const std::string& timeStr);
};

} // namespace bht