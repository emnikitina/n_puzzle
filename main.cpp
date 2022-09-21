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
        std::cout << argv[1] << std::endl;
        npuzzle = Puzzle(argv[1]);
    }
    else {
        std::cout << "Input field size, please:\n";
        getline(std::cin, str);
        npuzzle = Puzzle(std::stoi(str));
    }
    std::cout << "Solvability: " << npuzzle.checkSolvability() << std::endl;
    
    return 0;
}