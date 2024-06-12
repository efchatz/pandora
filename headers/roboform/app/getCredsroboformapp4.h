#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "../../core/saveFile.h"

//Repetitiveness for Roboform
// Helper function to find occurrences of a sequence in the file data
int countOccurrences(const std::vector<unsigned char>& data, const std::vector<unsigned char>& sequence) {
    int count = 0;
    auto it = data.begin();
    while (it != data.end()) {
        it = std::search(it, data.end(), sequence.begin(), sequence.end());
        if (it != data.end()) {
            ++count;
            ++it; // Move iterator to continue search after this match
        }
    }
    return count;
}

int getCredsroboformapp4(std::string filename) {
    std::ifstream sequencesFile("output.txt");
    std::ifstream dataFile(filename, std::ios::binary);

    if (!sequencesFile.is_open()) {
        std::cerr << "Error opening the sequences file." << std::endl;
        return 1;
    }

    if (!dataFile.is_open()) {
        std::cerr << "Error opening the data file." << std::endl;
        return 1;
    }

    // Read the entire data file into memory
    std::vector<unsigned char> fileData((std::istreambuf_iterator<char>(dataFile)), std::istreambuf_iterator<char>());
    dataFile.close();

    std::string line;
    while (std::getline(sequencesFile, line)) {
        // Convert the line to a sequence of unsigned char
        std::vector<unsigned char> sequence(line.begin(), line.end());

        // Count occurrences of the sequence in the file data
        int occurrences = countOccurrences(fileData, sequence);

        // Print and save the results only if found exactly once
        if (occurrences == 1) {
            std::cout << "Sequence: " << line << " found " << occurrences << " time." << std::endl;
            saveFile("Sequence: " << line << " found " << occurrences << " time.");
        }
    }

    sequencesFile.close();
  
    return 0;
}
