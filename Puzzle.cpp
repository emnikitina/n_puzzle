#include "Puzzle.hpp"

Puzzle::Puzzle(): _size(0), _puzzle(NULL), _result(NULL), _nbrPlaces(std::unordered_map<int, std::pair<size_t, size_t> >()) {};

Puzzle::Puzzle(size_t size): _size(size) {
    _puzzle = new int* [_size];
    _result = new int* [_size];
    for (size_t i = 0; i < _size; i++) {
        _puzzle[i] = new int[_size];
        _result[i] = new int[_size];
    }
    generator();
    // printArray(_puzzle);
    setRezultPuzzle();
    // printArray(_result);
};

Puzzle::Puzzle(char* filename) {
    parse(filename);
    _result = new int* [_size];
    for (size_t i = 0; i < _size; i++)
        _result[i] = new int[_size];
    setRezultPuzzle();
};

Puzzle::~Puzzle() {
    // for (size_t i = 0; i < _size; i++) {
    //     delete[] _puzzle[i];
    //     delete[] _result[i];
    // }
    // delete[] _puzzle;
    // delete[] _result;
    _nbrPlaces.clear();
};

void Puzzle::printArray(int** arr) {
    for (size_t i = 0; i < _size; i++) {
        for (size_t j = 0; j < _size; j++)
            std::cout << arr[i][j] << " ";
        std::cout << std::endl;
    }
};

std::string Puzzle::getPureLine(std::string line) {
    size_t pos;

    if ((pos = line.find_first_of("#")) != std::string::npos)
            line = line.substr(0, pos);
    size_t found = line.find_first_not_of("1234567890 ");
    if (found != std::string::npos) {
        std::cout << "ой, есть не цифровой символ " << line[found] << " в позиции " << found << std::endl;
        throw ;
    }
    // else {
    //     cout << "Все ок!" << endl;
    // }
    return line;
}

void Puzzle::generator() {
    int* sequence = new int[_size];
    int x, y, replace;

    srand(time(0));
    for (size_t i = 0; i < _size * _size; i++)
        sequence[i] = i;
    for (size_t i = 0; i < (_size * _size) / 2; i++) {
        x = rand() % (_size * _size);
        y = rand() % (_size * _size);
        replace = sequence[x];
        sequence[x] = sequence[y];
        sequence[y] = replace;
    }
 
    for (size_t i = 0; i < _size; i++) {
        for (size_t j = 0; j < _size; j++) {
            _puzzle[i][j] = sequence[i * _size + j];
            // std::cout << _puzzle[i][j] << " ";
        }
        // std::cout << std::endl;
    }
    delete[] sequence;
};

void Puzzle::parse(char* filename) {
    std::fstream fin;
    std::string line, str, nbr;
    size_t j = 0;
    std::stringstream x;                // CHANGE NAME
    
    fin.open(filename);
    if (!fin.is_open())
        throw ;

    while (!_size && getline(fin, line)) {
        str = getPureLine(line);
        if (str.size())
            _size = stoi(str);
    }
    _puzzle = new int* [_size];
    for (size_t i = 0; i < _size; i++) {
        _puzzle[i] = new int[_size];
        getline(fin, line);
        str = getPureLine(line);
        x << str;   //Перенос строки в поток 
        j = 0;            
        while (x >> nbr) {
            _puzzle[i][j] = stoi(nbr);
            j++;
        }
        x.clear();
    }
    fin.close();
}

size_t                                               Puzzle::getSize() const {
    return _size;
};

int**                                                Puzzle::getPuzzle() const {
    return _puzzle;
};

int**                                                Puzzle::getResultPuzzle() const {
    return _result;
};

std::unordered_map<int, std::pair<size_t, size_t> >  Puzzle::getNbrPlaces() const {
    return _nbrPlaces;
};

void                                                 Puzzle::setSize(size_t size) {
    _size = size;
};

void                                                 Puzzle::setPuzzle(int** puzzle, size_t size) {
    if (size == _size) {
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size; j++)
                _puzzle[i][j] = puzzle[i][j];
    }
};

void                                                 Puzzle::setRezultPuzzle() {
    int max = _size - 1, min = 0, i = 0, j = 0;
    
    for (size_t count = 1; count <= _size * _size; count++) {
        i = min;
        j = min;
        for (; j <= max; j++, count++) {
            _result[i][j] = count % (_size * _size);
            _nbrPlaces.insert(std::make_pair(_result[i][j], std::make_pair(i, j)));
        }
        j--;
        count--;
        for (; i <= max; i++, count++) {
            _result[i][j] = count % (_size * _size);
            _nbrPlaces.insert(std::make_pair(_result[i][j], std::make_pair(i, j)));
        }
        i--;
        count--;
        for (; j >= min; j--, count++) {
            _result[i][j] = count % (_size * _size);
            _nbrPlaces.insert(std::make_pair(_result[i][j], std::make_pair(i, j)));
        }
        j++;
        count--;
        for (; i > min; i--, count++) {
            _result[i][j] = count % (_size * _size);
            _nbrPlaces.insert(std::make_pair(_result[i][j], std::make_pair(i, j)));
        }
        count--;
        min++;
        max--;
    }
};

bool Puzzle::checkSolvability() {
    int inv = 0;
    
    for (size_t i = 0; i < _size * _size; i++)
        if (_puzzle[i])
            for (size_t j = 0; j < i; j++)
                if (_puzzle[j] > _puzzle[i])
                    inv++;
    for (size_t i = 0; i < _size * _size; i++)
        if (_puzzle[i] == 0)
            inv += (1 + i / _size);

    return (inv & 1);
};