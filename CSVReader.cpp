#include "CSVReader.h"
#include <iostream>
#include <cctype>

using namespace bht;
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
