#include "tree.hpp"
#include "puzzle.hpp"

int writeError() {
    std::cerr << "Error! Wrong number of arguments" << std::endl;
    std::cerr << "Please, use the next flags:" << std::endl;
    std::cerr << "-s <number> to set size of puzzle" << std::endl;
    std::cerr << "-shuffle <number> to set number of shuffle to generate puzzle" << std::endl;
    std::cerr << "-f <filename> to get puzzle from file" << std::endl;
    std::cerr << "-h <manhattan/euclid/chebyshev> to choose what heuristic is used: manhattan, euclid or chebyshev distance" << std::endl;
    return -1;
}

int main(int argc, char** argv) {
    // std::cout << "stoi(str): " << std::stoi(argv[1]) << std::endl;
    Puzzle npuzzle;
    std::string str;
    int heuristic, shuffle = -1;
    
    if (argc == 1)
        return writeError();
    else {
        for (size_t i = 1; i < argc; i++) {
            if (argv[i] == "-s") {
                if (i == argc - 1)
                    return writeError();
                npuzzle =  Puzzle(std::stoi(argv[i + 1]));
            }
            else if (argv[i] == "-f") {
                if (i == argc - 1)
                    return writeError();
                npuzzle =  Puzzle(argv[i + 1]);
            }
            else if (argv[i] == "-h") {
                if (i == argc - 1)
                    return writeError();
                heuristic = std::stoi(argv[i + 1]);
            }
            else if (argv[i] == "-shuffle") {
                if (i == argc - 1)
                    return writeError();
                shuffle = std::stoi(argv[i + 1]);
            }
                
        }

    }
    // if (shuffle != -1)
    //     npuzzle.setShuffle(shuffle);
    // npuzzle.setHeuristic(heuristic);
    
    /*if (argc > 2) {
        std::cerr << "Error! Wrong number of arguments\n";
        return 1;
    }
    else if (argc == 2) {
        std::cout << argv[1] << std::endl;
        npuzzle = Puzzle(argv[1]);
    }
    else {
        std::cout << "Input field size, please:\n";
        getline(std::cin, str);
        npuzzle = Puzzle(std::stoi(str));
    }*/


    std::cout << "Solvability: " << npuzzle.checkSolvability() << std::endl;
    
    return 0;
}