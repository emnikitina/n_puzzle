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

// void generator(int **arr, size_t size) {
//     int* sequence = new int[size];
//     int x, y, replace;

//     srand(time(0));
    
//     for (size_t i = 0; i < size * size; i++)
//         sequence[i] = i;


//     for (size_t i = 0; i < (size * size) / 2; i++) {
//         x = rand() % (size * size);
//         y = rand() % (size * size);
//         replace = sequence[x];
//         sequence[x] = sequence[y];
//         sequence[y] = replace;
//     }
 
//     for (size_t i = 0; i < size; i++) {
//         for (size_t j = 0; j < size; j++) {
//             arr[i][j] = sequence[i * size + j];
//             std::cout << arr[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

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

std::string getPureLine(std::string line) {
    size_t pos;

    if ((pos = line.find_first_of("#")) != std::string::npos)
            line = line.substr(0, pos);
        //std::cout << "new line: " << line << std::endl;
        size_t found = line.find_first_not_of("1234567890 ");
        if (found != std::string::npos) {
            std::cout << "ой, есть не цифровой символ " << line[found] << " в позиции " << found << std::endl;
            throw ;
        }
        else {
            std::cout << "Все ок!" << std::endl;
        }
}

size_t parse(int** arr, char* filename) {
    std::fstream fin;
    std::string line;
    size_t pos, size = 0, i = 0, j = 0;
    
    fin.open(filename);
    if (!fin.is_open())
        throw ;

    while (!size && std::getline(fin, line)) {
        std::cout << "line: " << line << std::endl;
        std::string str = getPureLine(line);
        if (str.size())
            size = std::stoi(str);
    }
    
    arr = new int* [size];
    for (size_t i = 0; i < size; i++)
        arr[i] = new int[size];
    while (std::getline(fin, line)){
        std::cout << "line: " << line << std::endl;    
        i = 0;
        j = 0;

        
    }
    fin.close();
    return size;
}

void printArray(int** arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++)
            std::cout << arr[i][j] << " ";
        std::cout << std::endl;
    }
}

bool checkSolvability(int** puzzle, size_t size) {
    int inv = 0;
    for (size_t i = 0; i < size * size; i++)
        if (puzzle[i])
            for (size_t j = 0; j<i; j++)
                if (puzzle[j] > puzzle[i])
                    inv++;

    for (size_t i = 0; i < size * size; i++)
        if (puzzle[i] == 0)
            inv += (1 + i / size);

    return (inv & 1);
}

int main(int argc, char** argv) {
    int **puzzle = NULL;
    size_t size;

    if (argc > 2) {
        std::cerr << "Error! Wrong number of arguments\n";
        return 1;
    }
    else if (argc == 2) {
        // open file and read data
        std::cout << argv[1] << std::endl;
        try
        {
            size = parse(puzzle, argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    else {
        std::string str;
        
        
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
        puzzle = new int* [size];
        for (size_t i = 0; i < size; i++)
            puzzle[i] = new int[size];
        generator(puzzle, size);
    

        //print rez result
        int **result = new int*[size];
        for (size_t i = 0; i < size; i++) {
            result[i] = new int[size];
            for (size_t j = 0; j < size; j++)
                result[i][j] = -1;
        }
        
        int max = size - 1, min = 0, i = 0, j = 0;
        for (size_t count = 1; count <= size * size; count++) {
            i = min;
            j = min;
            for (; j <= max; j++, count++)
                result[i][j] = (count == (size * size) ? 0 : count);
            j--;
            count--;
            for (; i <= max; i++, count++)
                result[i][j] = (count == (size * size) ? 0 : count);
            i--;
            count--;
            for (; j >= min; j--, count++)
                result[i][j] = (count == (size * size) ? 0 : count);
            j++;
            count--;
            for (; i > min; i--, count++)
                result[i][j] = (count == (size * size) ? 0 : count);
            count--;
            min++;
            max--;
        }

        std::cout << "full result\n";
        printArray(result, size);
        std::cout << "Solvability: " << (checkSolvability(puzzle, size) ? "true" : "false") << std::endl;

    }

    return 0;
}