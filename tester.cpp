#include <cstddef>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "types.h"
#include "network.h"

using namespace bht;

namespace {

inline bool containsRoute(const std::vector<Route>& items, const std::string &needle) {
  for (auto item : items) {
    if (item.shortName == needle) {
      return true;
    }
  }

  return false;
}

inline bool containsTrip(const std::vector<Trip>& items, const std::string &needle) {
  for (auto item : items) {
    if (item.id == needle) {
      return true;
    }
  }

  return false;
}

inline bool containsStop(const std::vector<StopTime>& items, const std::string &needle) {
  for (auto item : items) {
    if (item.stopId == needle) {
      return true;
    }
  }

  return false;
}

// Data read tests
TEST(Network, getRoutes) {
  std::string inputDirectory{"/GTFSTest"};
  Network network{inputDirectory};

  std::vector<Route> results = network.getRoutes();
  EXPECT_EQ(results.size(), 86) << "Test routes contain 86 routes but your size() is " << results.size();
  EXPECT_TRUE(containsRoute(results, "605")) << "route 605 not in available routes but should be";
  EXPECT_TRUE(containsRoute(results, "FEX")) << "route FEX not in available routes but should be";
  EXPECT_TRUE(containsRoute(results, "N14")) << "route N14 not in available routes but should be";
  EXPECT_TRUE(containsRoute(results, "RE7")) << "route RE7 not in available routes but should be";
  EXPECT_TRUE(containsRoute(results, "X5")) << "route X5 not in available routes but should be";

  EXPECT_FALSE(containsRoute(results, "S41")) << "route S41 is in available routes but should not be";
  EXPECT_FALSE(containsRoute(results, "S7")) << "route S7 is in available routes but should not be";
  EXPECT_FALSE(containsRoute(results, "U1")) << "route U1 is in available routes but should not be";
  EXPECT_FALSE(containsRoute(results, "U5")) << "route U5 is in available routes but should not be";
  EXPECT_FALSE(containsRoute(results, "U9")) << "route U9 is in available routes but should not be";
}

TEST(Network, getRouteDisplayName) {
  std::string inputDirectory{"/GTFSTest"};
  Network network{inputDirectory};

  EXPECT_EQ(network.getRouteDisplayName(network.routes["25942_100"]), "RB61") << "Display for route with id '25942_100' should by 'RB61' but is not";
  EXPECT_EQ(network.getRouteDisplayName(network.routes["24045_100"]), "RE2") << "Display for route with id '24045_100' should by 'RE2' but is not";
  EXPECT_EQ(network.getRouteDisplayName(network.routes["19702_700"]), "RE10") << "Display for route with id '19702_700' should by 'RE10' but is not";
  
  EXPECT_EQ(network.getRouteDisplayName(network.routes["24171_700"]), "RE2 - Regionalexpress 2") << "Display for route with id '24171_700' should by 'RE2 - Regionalexpress 2' but is not";
}

TEST(Network, getTripsForRoute) {
  std::string inputDirectory{"/GTFSTest"};
  Network network{inputDirectory};

  std::string routeId = "25305_700";
  std::vector<Trip> results = network.getTripsForRoute(routeId);
  EXPECT_EQ(results.size(), 17) << "Test route '25305_700' has 17 trips but your size() is " << results.size();
  const std::string tripIds[] = { "230348305", "230348304", "230348303", "230348302", "230348301", "230348300", "230348299", "230348298", "230348297", "230348296", "230348295", "230348294", "230348293", "230348292", "230348291", "230348290", "230348289" };
  for (auto tripId : tripIds) {
    EXPECT_TRUE(containsTrip(results, tripId)) << "trip " << tripId << " should be associated with route " << routeId << "but is not";
  }
  
  routeId = "25297_100";
  results = network.getTripsForRoute(routeId);
  EXPECT_EQ(results.size(), 4) << "Test route '25297_100' has 4 trips but your size() is " << results.size();
  const std::string otherTripIds[] = { "230353671", "230353673", "230353669", "230353670" };
  for (auto tripId : otherTripIds) {
    EXPECT_TRUE(containsTrip(results, tripId)) << "trip " << tripId << " should be associated with route " << routeId << "but is not";
  }
}

TEST(Network, getTripDisplayName) {
  std::string inputDirectory{"/GTFSTest"};
  Network network{inputDirectory};

  std::string routeId = "24057_100";
  std::vector<Trip> results = network.getTripsForRoute(routeId);
  for (auto item: results) {
    std::string expected = item.shortName + " - " + item.headsign;
    EXPECT_EQ(network.getTripDisplayName(item), expected) << "Display name for trip with id '" << item.id << "' should by '" << expected << "' but is not";
  }
}

TEST(Network, getStopTimesForTrip) {
  std::string inputDirectory{"/GTFSTest"};
  Network network{inputDirectory};

  std::string tripId = "230353669";
  std::vector<StopTime> results = network.getStopTimesForTrip(tripId);
  EXPECT_EQ(results.size(), 10) << "Stops for trip 230353669 should contain 10 stops but your size() is " << results.size();
  const std::string stopIds[] = { "de:13071:80001", "de:12065:900203772:1:50", "de:12065:900203749:1:50", "de:12065:900203709:2:51", "de:12065:900203780:1:50", "de:12065:900200005:1:1", "de:11000:900007102:5:58", "de:11000:900003200:3:54", "de:11000:900100020:2:53", "de:11000:900058101:3:54" };
  for (auto item: stopIds) {
    EXPECT_TRUE(containsStop(results, item)) << "Stop " << item << " should be part of trip " << tripId << "but is not";
  }

  tripId = "222322330";
  results = network.getStopTimesForTrip(tripId);
  EXPECT_EQ(results.size(), 15) << "Stops for trip 222322330 should contain 15 stops but your size() is " << results.size();
  const std::string otherStopIds[] = { "de:12054:900230003::2", "de:12054:900230102::2", "de:12054:900230101::1", "de:12054:900230096::1", "de:12054:900230080::3", "de:12054:900230036::1", "de:12054:900230144::1", "de:12054:900230092::1", "de:12054:900230093::1", "de:12054:900230048::1", "de:12054:900230091::1", "de:12054:900230094::1", "de:12054:900230037::1", "de:12054:900230181::5", "de:12054:900230028::2" };
  for (auto item: otherStopIds) {
    EXPECT_TRUE(containsStop(results, item)) << "Stop " << item << " should be part of trip " << tripId << "but is not";
  }
}

TEST(Network, getStopById) {
  std::string inputDirectory{"/GTFSTest"};
  Network network{inputDirectory};

  const std::string stopIds[] = { "de:13071:80001", "de:12065:900203772:1:50", "de:12065:900203749:1:50", "de:12065:900203709:2:51", "de:12065:900203780:1:50", "de:12065:900200005:1:1", "de:11000:900007102:5:58", "de:11000:900003200:3:54", "de:11000:900100020:2:53", "de:11000:900058101:3:54", "de:12054:900230003::2", "de:12054:900230102::2", "de:12054:900230101::1", "de:12054:900230096::1", "de:12054:900230080::3", "de:12054:900230036::1", "de:12054:900230144::1", "de:12054:900230092::1", "de:12054:900230093::1", "de:12054:900230048::1", "de:12054:900230091::1", "de:12054:900230094::1", "de:12054:900230037::1", "de:12054:900230181::5", "de:12054:900230028::2" };
  const std::string expectedValues[] = { "Neustrelitz, Hauptbahnhof", "Fürstenberg (Havel), Bahnhof", "Dannenwalde (bei Gransee), Bahnhof", "Gransee, Bahnhof", "Löwenberg (Mark), Bahnhof", "S Oranienburg Bhf", "S+U Gesundbrunnen Bhf (Berlin)", "S+U Berlin Hauptbahnhof", "S+U Potsdamer Platz Bhf (Berlin)", "S Südkreuz Bhf (Berlin)", "S Griebnitzsee Bhf", "Potsdam, Stahnsdorfer Str./August-Bebel-Str.", "Potsdam, Lindenpark", "Potsdam, Rotdornweg/Stahnsdorfer Str.", "Potsdam, Plantagenstr.", "Potsdam, Goetheplatz", "Potsdam, Scheffelstr.", "Potsdam, Hermann-Maaß-Str.", "Potsdam, Karl-Marx-Str./Behringstr.", "Potsdam, Schloss Babelsberg", "Potsdam, Sternwarte", "Potsdam, Karl-Liebknecht-Stadion", "Potsdam, Spindelstr.", "Potsdam, Rathaus Babelsberg", "S Babelsberg/Schulstr." };
  for (int index = 0; index < 25; index++) {
    EXPECT_EQ(network.getStopById(stopIds[index]).name, expectedValues[index]) << "getStopById('" << stopIds[index] << "') should return stop with name '" << expectedValues[index] << "' but did not";
  }
}

TEST(Network, searchStopTimesForTrip) {
  std::string inputDirectory{"/GTFSTest"};
  Network network{inputDirectory};

  std::string tripId = "230353669";
  std::vector<StopTime> results = network.searchStopTimesForTrip("Gransee", tripId);
  EXPECT_EQ(results.size(), 2) << "Filtered stops for 'Gransee' for trip 230353669 should contain 2 stops but your size() is " << results.size();
  const std::string stopIds[] = { "de:12065:900203749:1:50", "de:12065:900203709:2:51" };
  for (auto item: stopIds) {
    EXPECT_TRUE(containsStop(results, item)) << "Stop " << item << " should be part of filtered trip " << tripId << "but is not";
  }

  tripId = "222322330";
  results = network.searchStopTimesForTrip("Babelsberg", tripId);
  EXPECT_EQ(results.size(), 3) << "Filtered stops for 'Babelsberg' for trip 222322330 should contain 3 stops but your size() is " << results.size();
  const std::string otherStopIds[] = { "de:12054:900230048::1", "de:12054:900230181::5", "de:12054:900230028::2" };
  for (auto item: otherStopIds) {
    EXPECT_TRUE(containsStop(results, item)) << "Stop " << item << " should be part of filtered trip " << tripId << "but is not";
  }
}

} // namespace
