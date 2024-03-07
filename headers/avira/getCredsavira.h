#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../core/saveFile.h"

int getCredsavira(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> searchPattern = { 0x21, 0x6a, 0x19, 0x00, 0x19, 0x02, 0x00, 0x00, 0x19, 0x02, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x8d, 0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00 };
    std::vector<unsigned char> foundData;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        if (c == searchPattern[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchPattern.size()) {
                // We found the search pattern, now collect data until reaching the 600 data limit
                std::vector<unsigned char> extractedData;
                int dataCount = 0;

                while (dataCount < 600 && !file.eof()) {
                    file.read(reinterpret_cast<char*>(&c), sizeof(c));
                    extractedData.push_back(c);
                    dataCount++;
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
    return 0;
}
