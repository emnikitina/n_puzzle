#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#include <sstream>
#include <unordered_map>
#include "tree.hpp"

using namespace std;

void printArray(int** arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

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
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

vector<string> splitLine(string str, string sep) {
    vector<string> words;

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

string getPureLine(string line) {
    size_t pos;

    if ((pos = line.find_first_of("#")) != string::npos)
            line = line.substr(0, pos);
    size_t found = line.find_first_not_of("1234567890 ");
    if (found != string::npos) {
        cout << "ой, есть не цифровой символ " << line[found] << " в позиции " << found << endl;
        throw ;
    }
    // else {
    //     cout << "Все ок!" << endl;
    // }
    return line;
}

size_t getPuzzleSize(char* filename) {
    fstream fin;
    size_t size;
    string line, str;
    
    fin.open(filename);
    if (!fin.is_open())
        throw ;

    while (!size && getline(fin, line)) {
        str = getPureLine(line);
        if (str.size())
            size = stoi(str);
    }
    fin.close();
    return size;
}

size_t parse(int** arr, char* filename) {
    fstream fin;
    string line, str, nbr;
    size_t size = 0, j = 0;
    stringstream x;
    
    fin.open(filename);
    if (!fin.is_open())
        throw ;

    while (!size && getline(fin, line)) {
        str = getPureLine(line);
        if (str.size())
            size = stoi(str);
    }
    // arr = new int* [size];
    // std::cout << "parse size: " << size << endl;
    for (size_t i = 0; i < size; i++) {
        // arr[i] = new int[size];
        getline(fin, line);
        str = getPureLine(line);
        x << str;   //Перенос строки в поток 
        j = 0;            
        while (x >> nbr) {
            arr[i][j] = stoi(nbr);
            j++;
        }
        x.clear();
    }
    // cout << "here\n";
    // printArray(arr, size);
    // cout << "after print\n";
    fin.close();
    return size;
}

bool checkSolvability(int** puzzle, size_t size) {
    int inv = 0;
    
    for (size_t i = 0; i < size * size; i++)
        if (puzzle[i])
            for (size_t j = 0; j < i; j++)
                if (puzzle[j] > puzzle[i])
                    inv++;
    for (size_t i = 0; i < size * size; i++)
        if (puzzle[i] == 0)
            inv += (1 + i / size);

    return (inv & 1);
}

int ManhattanHeuristics(int Ax, int Ay, int Bx, int By) {
    return abs(Ax - Bx) + abs(Ay - By);
};

float EuclidDistance(int Ax, int Ay, int Bx, int By) {
    return sqrt(pow(Ax - Bx, 2) + pow(Ay - By, 2));
};

int ChebyshevHeuristics(int Ax, int Ay, int Bx, int By) {
    return max(abs(Ax - Bx), abs(Ay - By));
};



// void calculateWeights(int** puzzle, int** result, size_t size) {

// };

void generateResultPuzzle(int** result, size_t size, std::unordered_map<int, std::pair<size_t, size_t> > &nbrPlaces) {
    for (size_t i = 0; i < size; i++) {
        result[i] = new int[size];
        for (size_t j = 0; j < size; j++)
            result[i][j] = -1;
    }

    int max = size - 1, min = 0, i = 0, j = 0;
    for (size_t count = 1; count <= size * size; count++) {
        i = min;
        j = min;
        for (; j <= max; j++, count++) {
            result[i][j] = count % (size * size);
            nbrPlaces.insert(std::make_pair(result[i][j], std::make_pair(i, j)));
        }
        j--;
        count--;
        for (; i <= max; i++, count++) {
            result[i][j] = count % (size * size);
            nbrPlaces.insert(std::make_pair(result[i][j], std::make_pair(i, j)));
        }
        i--;
        count--;
        for (; j >= min; j--, count++) {
            result[i][j] = count % (size * size);
            nbrPlaces.insert(std::make_pair(result[i][j], std::make_pair(i, j)));
        }
        j++;
        count--;
        for (; i > min; i--, count++) {
            result[i][j] = count % (size * size);
            nbrPlaces.insert(std::make_pair(result[i][j], std::make_pair(i, j)));
        }
        count--;
        min++;
        max--;
    }
};

int main(int argc, char** argv) {
    int **puzzle = NULL;
    size_t size;
    string str;
    // priority_queue<Node> open_set;
    std::unordered_map<int, std::pair<size_t, size_t> > nbrPlaces;


    if (argc > 2) {
        cerr << "Error! Wrong number of arguments\n";
        return 1;
    }
    else if (argc == 2) {
        // open file and read data
        cout << argv[1] << endl;
        try
        {
            size = getPuzzleSize(argv[1]);
            puzzle = new int* [size];
            for (size_t i = 0; i < size; i++)
                puzzle[i] = new int[size];
            parse(puzzle, argv[1]);
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
        }
    }
    else {
        cout << "Input field size, please:\n";
        getline(cin, str);
        try
        {
            size = stoi(str);
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
            cerr << "Wrong format of input data\n";
            return 1;
        }
        puzzle = new int* [size];
        for (size_t i = 0; i < size; i++)
            puzzle[i] = new int[size];
        generator(puzzle, size);
    }
    
    //print rez result
    int **result = new int*[size];
    generateResultPuzzle(result, size, nbrPlaces);
    cout << "gotten puzzle:\n";
    printArray(puzzle, size);
    cout << "full result:\n";
    printArray(result, size);
    cout << "Solvability: " << (checkSolvability(puzzle, size) ? "true" : "false") << endl;
    return 0;
}