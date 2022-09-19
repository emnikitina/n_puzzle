#include "tree.hpp"
#include "puzzle.hpp"

int main(int argc, char** argv) {
    Puzzle npuzzle;
    std::string str;
    
    if (argc > 2) {
        std::cerr << "Error! Wrong number of arguments\n";
        return 1;
    }
    else if (argc == 2) {
        // open file and read data
        std::cout << argv[1] << std::endl;
        // try
        // {
            npuzzle = Puzzle(argv[1]);
        // }
        // catch(const exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }
    else {
        std::cout << "Input field size, please:\n";
        getline(std::cin, str);
        // try
        // {
            npuzzle = Puzzle(std::stoi(str));
            
        // }
        // catch(const exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        //     std::cerr << "Wrong format of input data\n";
        //     return 1;
        // }
    }
    std::cout << "Solvability: " << npuzzle.checkSolvability() << std::endl;
    return 0;
}