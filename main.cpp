#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>

void generator(int **arr, size_t size) {
    int* sequence = new int[size];
    int x, y, replace;

    srand(time(0));
    for (size_t i = 0; i < size * size; i++)
        sequence[i] = i;
    for (size_t i = 0; i < (size * size) / 2; i++) {
        x = rand() % (size * size);
        y = rand() % (size * size);
        replace = sequence[x];
        sequence[x] = sequence[y];
        sequence[y] = replace;
    }
 
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            arr[i][j] = sequence[i * size + j];
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> splitLine(std::string str, std::string sep) {
    std::vector<std::string> words;

	for (size_t i = 0; i < str.size(); i++) {
        for (size_t j = 0; j < sep.size(); j++) {
            if (str[i] == sep[j]) {
				words.push_back(str.substr(0, i));
                str = str.substr(i + 1);
            }
        }
    }
	return words;
}

void parse(int** arr, char* filename) {
    std::fstream fin;
    std::string line;
    size_t pos;
    
    fin.open(filename);
    if (!fin.is_open())
        throw ;
    arr = new int* [10];
    while (std::getline(fin, line))
    {
        std::cout << "line: " << line << std::endl;
        if (line[0] == '#')
            continue ;
        else if ((pos = line.find_first_of("#")) != std::string::npos)
            line = line.substr(0, pos);
        std::cout << "new line: " << line << std::endl;
		
        
    }
    fin.close();
}

int main(int argc, char** argv) {
    int **array;

    if (argc > 2) {
        std::cerr << "Error! Wrong number of arguments\n";
        return 1;
    }
    else if (argc == 2) {
        // open file and read data
        std::cout << argv[1] << std::endl;
        try
        {
            parse(array, argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    else {
        std::string str;
        int size;
        
        std::cout << "Input field size, please:\n";
        std::getline(std::cin, str);
        try
        {
            size = std::stoi(str);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cerr << "Wrong format of input data\n";
            return 1;
        }
        array = new int* [size];
        for (int i = 0; i < size; i++)
            array[i] = new int[size];
        generator(array, size);
    }
    return 0;
}