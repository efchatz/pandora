#pragma once

int mergeFiles() {
    std::vector<std::string> dump_files;
    std::string input;

    std::cout << "Enter dump file name one per line (type 'done' to finish): ";

    while (true) {
        std::cin >> input;
        if (input == "done") {
            break;
        }
        dump_files.push_back(input);
    }

    std::vector<std::string> merged_data;

    for (const std::string& dump_file : dump_files) {
        std::ifstream file(dump_file, std::ios::binary);

        if (file.is_open()) {
            std::vector<std::string> data;
            std::string line;
            while (std::getline(file, line)) {
                data.push_back(line);
            }
            merged_data.insert(merged_data.end(), data.begin(), data.end());
            file.close();
        }
        else {
            std::cerr << "Failed to open file: " << dump_file << std::endl;
        }
    }

    std::ofstream merged_file("app.dmp", std::ios::binary);

    if (merged_file.is_open()) {
        for (const std::string& line : merged_data) {
            merged_file << line << std::endl;
        }
        merged_file.close();
        std::cout << "Merged data saved to app.dmp" << std::endl;
    }
    else {
        std::cerr << "Failed to create merged data file" << std::endl;
    }

    return 0;
}
