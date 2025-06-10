#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>  // Add this for std::ifstream
#include <stdexcept> // For exception handling
#include "types.h"

namespace bht{

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
}
