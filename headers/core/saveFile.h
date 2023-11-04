#pragma once
#include <iostream>
#include <fstream>
#include <string>

int saveFile(std::string utf8ExtractedData) {

    // Specify the file path
    std::string filePath = "credentials.txt";

    // Open the file in append mode
    std::ofstream outputFile(filePath, std::ios::app);

    if (outputFile.is_open()) {
        // Write the data to the file
        outputFile << utf8ExtractedData;

        // Close the file
        outputFile.close();

        std::cout << "Data saved to file." << std::endl;
    }
    else {
        std::cerr << "Error opening the file for writing." << std::endl;
    }

    return 0;
}
