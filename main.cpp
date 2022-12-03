#include "tree.hpp"
#include "puzzle.hpp"
#include <string.h>
#include <string>
#include <algorithm>

enum genType {OWNFILE, GENERATOR};

int writeError() {
    std::cerr << "Error! Wrong number of arguments" << std::endl;
    std::cerr << "Please, use the next flags:" << std::endl;
    std::cerr << "-s <number> to set size of puzzle" << std::endl;
    std::cerr << "-shuffle <number> to set number of shuffle to generate puzzle" << std::endl;
    std::cerr << "-f <filename> to get puzzle from file" << std::endl;
    std::cerr << "-h <manhattan/euclid/chebyshev> to choose what heuristic is used: manhattan, euclid or chebyshev distance" << std::endl;
    return -1;
}

int checkArgv(int argc, char** argv) {
    bool		size, shuffle, heuristic;
    std::string	filename;

    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    Puzzle npuzzle;
    std::string str;
    int shuffle = -1, heuristic = -1, sourseType = -1;
    
    if (argc == 1)
        return writeError();
    else {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "-s")) {
                sourseType = GENERATOR;
                if (i == argc - 1)
                    return writeError();
                npuzzle =  Puzzle(std::stoi(argv[i + 1]));
            }
            else if (!strcmp(argv[i], "-f")) {
                sourseType = OWNFILE;
                if (i == argc - 1)
                    return writeError();
                npuzzle =  Puzzle(argv[i + 1]);
            }
            else if (!strcmp(argv[i], "-h")) {
                if (i == argc - 1)
                    return writeError();
                if (!strcmp(argv[i + 1], "manhattan"))
                    heuristic = manhattan;
                else if (!strcmp(argv[i + 1], "chebyshev"))
                    heuristic = chebyshev;
                else if (!strcmp(argv[i + 1], "euclid"))
                    heuristic = euclid;
            }
            else if (!strcmp(argv[i], "-shuffle")) {
                if (i == argc - 1)
                    return writeError();
                str = argv[i + 1];
                shuffle = std::stoi(str);
            }       
        }
        // std::cout << "shuffle: " << shuffle << " heuristic: " << heuristic << std::endl;
        if (heuristic == -1 || (sourseType == GENERATOR && shuffle == -1))
            return writeError();
        npuzzle.setHeuristic(heuristic);
    }
   
    // if (shuffle != -1)
    //     npuzzle.setShuffle(shuffle);
    // npuzzle.setHeuristic(heuristic);
    
    if (npuzzle.checkSolvability()) {
        // std::cout << "Solvability: " << std::boolalpha << true << std::endl;
        npuzzle.solve();
    }
    else
        std::cout << "Solvability: false" << std::endl;
		std::cout << "Please generate puzzle again or put to programm another file" << std::endl;
    
    return 0;
}