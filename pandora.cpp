#include <windows.h>
#include <psapi.h>
#include <vector>
#include <string>
#include <dbghelp.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "headers/core/saveAllProc.h"
#include "headers/core/checkApps.h"




int main() {
    std::cout << std::endl;
    std::cout << " .########.....###....##....##.########...#######..########.....###...   " << std::endl;
    std::cout << " .##.....##...##.##...###...##.##.....##.##.....##.##.....##...##.##..   " << std::endl;
    std::cout << " .##.....##..##...##..####..##.##.....##.##.....##.##.....##..##...##.   " << std::endl;
    std::cout << " .########..##.....##.##.##.##.##.....##.##.....##.########..##.....##   " << std::endl;
    std::cout << " .##........#########.##..####.##.....##.##.....##.##...##...#########   " << std::endl;
    std::cout << " .##........##.....##.##...###.##.....##.##.....##.##....##..##.....##   " << std::endl;
    std::cout << " .##........##.....##.##....##.########...#######..##.....##.##.....##   " << std::endl;
    std::cout << std::endl;
    checkApps();
    cout << "Pandora finished. Press Enter to exit...";
    cin.ignore();
    cin.get();
    
    
    

    return 0;
}
