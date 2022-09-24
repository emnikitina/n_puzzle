#include "Puzzle.hpp"

Puzzle::Puzzle(): _size(0), _puzzle(NULL), _result(NULL), _nbrPlaces(std::unordered_map<int, std::pair<size_t, size_t> >()), _openSet(std::priority_queue<Node*>()), _closeSet(std::priority_queue<Node*>()), _states(Tree()), _heuristic(-1), _emptyCell(std::make_pair(-1, -1)), _depth(0) {};

Puzzle::Puzzle(size_t size): _size(size), _nbrPlaces(std::unordered_map<int, std::pair<size_t, size_t> >()), _openSet(std::priority_queue<Node*>()), _closeSet(std::priority_queue<Node*>()), _states(Tree()), _heuristic(-1), _emptyCell(std::make_pair(-1, -1)), _depth(0) {
    _puzzle = new int* [_size];
    _result = new int* [_size];
    for (size_t i = 0; i < _size; i++) {
        _puzzle[i] = new int[_size];
        _result[i] = new int[_size];
    }
    generator();
    setRezultPuzzle();

    std::cout << "puzzle: \n";
    printArray(_puzzle);
    std::cout << "result: \n";
    printArray(_result);
};

Puzzle::Puzzle(char* filename): _size(0), _nbrPlaces(std::unordered_map<int, std::pair<size_t, size_t> >()), _openSet(std::priority_queue<Node*>()), _closeSet(std::priority_queue<Node*>()), _states(Tree()), _heuristic(-1), _emptyCell(std::make_pair(-1, -1)), _depth(0) {
    parse(filename);
    _result = new int* [_size];
    for (size_t i = 0; i < _size; i++)
        _result[i] = new int[_size];
    setRezultPuzzle();

    std::cout << "puzzle: \n";
    printArray(_puzzle);
    std::cout << "result: \n";
    printArray(_result);
};

Puzzle::~Puzzle() {
    // if (_puzzle) {
	// 	for (size_t i = 0; i < _size; i++)
	// 		delete[] _puzzle[i];
	// 	delete[] _puzzle;
	// }
	// if (_result) {
	// 	for (size_t i = 0; i < _size; i++)
    //     	delete[] _result[i];
	// 	delete[] _result;
	// }
    _nbrPlaces.clear();
};

void Puzzle::printArray(int** arr) {
    for (size_t i = 0; i < _size; i++) {
        for (size_t j = 0; j < _size; j++) {
            if (arr[i][j] < 10) 
                std::cout << " ";    
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
};

std::string Puzzle::getPureLine(std::string line) {
    size_t pos;

    if ((pos = line.find_first_of("#")) != std::string::npos)
            line = line.substr(0, pos);
    size_t found = line.find_first_not_of("1234567890 ");
    if (found != std::string::npos) {
        std::cout << "pos: " << found << std::endl;
        std::cout << "ой, есть не цифровой символ " << line[found] << " в позиции " << found << std::endl;
        throw ;
    }
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
			if (!_puzzle[i][j]) {
				_emptyCell.first = i;
				_emptyCell.second = j;
			}
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
    std::stringstream flow;                // CHANGE NAME
    
    fin.open(filename);
    if (!fin.is_open())
        throw ;
    _size = 0;
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
        flow << str;   //Перенос строки в поток 
        j = 0;            
        while (flow >> nbr) {
            _puzzle[i][j] = stoi(nbr);
			if (!_puzzle[i][j]) {
				_emptyCell.first = i;
				_emptyCell.second = j;
			}
            j++;
        }
        flow.clear();
    }
    fin.close();
}

size_t	Puzzle::getSize() const {
    return _size;
};

int**	Puzzle::getPuzzle() const {
    return _puzzle;
};

int**	Puzzle::getResultPuzzle() const {
    return _result;
};

std::unordered_map<int, std::pair<size_t, size_t> >	Puzzle::getNbrPlaces() const {
    return _nbrPlaces;
};

void	Puzzle::setSize(size_t size) {
    _size = size;
};

int	Puzzle::getHeuristic() const {
    return _heuristic;
};

void	Puzzle::setPuzzle(int** puzzle, size_t size) {
    if (size == _size) {
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size; j++)
                _puzzle[i][j] = puzzle[i][j];
    }
};

void	Puzzle::setRezultPuzzle() {
    int max = _size - 1, min = 0, i = 0, j = 0;
    
    for (size_t count = 1; count <= _size * _size; count++) {
        i = min;
        j = min;
        for (; j <= max; j++, count++)
            _result[i][j] = count % (_size * _size);
        j--;
        count--;
        for (; i <= max; i++, count++) 
            _result[i][j] = count % (_size * _size);
        i--;
        count--;
        for (; j >= min; j--, count++) 
            _result[i][j] = count % (_size * _size);
        j++;
        count--;
        for (; i > min; i--, count++)
            _result[i][j] = count % (_size * _size);
        count--;
        min++;
        max--;
    }
    for (size_t i = 0; i < _size; i++) 
        for (size_t j = 0; j < _size; j++)
            _nbrPlaces.insert(std::make_pair(_result[i][j], std::make_pair(i, j)));

};

void	Puzzle::setHeuristic(int heuristic) {
    _heuristic = heuristic;
};

bool Puzzle::checkSolvability() {
    int n = 0, k = 0;

	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			if (_puzzle[i][j]) {
				for (size_t l = 0; l < i; l++) {
					for (size_t m = 0; m < j; m++) {
						if (_puzzle[l][m] && _puzzle[l][m] > _puzzle[i][j])
							n++;
					}
				}
			}
			else
				k = i + 1;
		}
	}
	return (!((n + k + _size) % 2));
};

// float	Puzzle::ManhattanHeuristics(int Ax, int Ay, int Bx, int By) {
//     return float(abs(Ax - Bx) + abs(Ay - By));
// };

// float	Puzzle::EuclidDistance(int Ax, int Ay, int Bx, int By) {
//     return sqrt(pow(Ax - Bx, 2) + pow(Ay - By, 2));
// };

// float	Puzzle::ChebyshevHeuristics(int Ax, int Ay, int Bx, int By) {
//     return std::max(abs(Ax - Bx), abs(Ay - By));
// };

// void	Puzzle::calculateCost(Node* node) {
// 	for (size_t i = 0; i < _size; i++) {
// 		for (size_t j = 0; j < _size; j++) {
// 			if (_heusistic == manhattan)
// 				node->_cost = ManhattanHeuristics(i, j, _nbrPlaces[node->_puzzleState[i][j]].first, _nbrPlaces[node->_puzzleState[i][j]].second);
// 			else if (_heusistic == euclid)
// 				node->_cost = EuclidDistance(i, j, _nbrPlaces[node->_puzzleState[i][j]].first, _nbrPlaces[node->_puzzleState[i][j]].second);
// 			else if (_heusistic == chebyshev)
// 				node->_cost = ChebyshevHeuristics(i, j, _nbrPlaces[node->_puzzleState[i][j]].first, _nbrPlaces[node->_puzzleState[i][j]].second);
// 		}
// 	}
// };

bool Puzzle::emptyRight() {
    int tmp;

    if (_emptyCell.second != -1 && _emptyCell.second != int(_size) - 1) {
        tmp = _puzzle[_emptyCell.first][_emptyCell.second + 1];
        _puzzle[_emptyCell.first][_emptyCell.second + 1] = 0;
        _puzzle[_emptyCell.first][_emptyCell.second] = tmp;
		return true;
    }
	return false;
};

bool Puzzle::emptyLeft() {
    int tmp;
    
    if (_emptyCell.second != -1 && _emptyCell.second != 0) {
		tmp = _puzzle[_emptyCell.first][_emptyCell.second - 1];
		_puzzle[_emptyCell.first][_emptyCell.second - 1] = 0;
		_puzzle[_emptyCell.first][_emptyCell.second] = tmp;
		return true;
    }
	return false;
};
bool Puzzle::emptyUp() {
    int tmp;
    
    if (_emptyCell.first != -1 && _emptyCell.first != 0) {
		tmp = _puzzle[_emptyCell.first - 1][_emptyCell.second];
		_puzzle[_emptyCell.first - 1][_emptyCell.second] = 0;
		_puzzle[_emptyCell.first][_emptyCell.second] = tmp;
		return true;
    }
	return false;
};

bool Puzzle::emptyDown() {
    int tmp;
    
    if (_emptyCell.first != -1 && _emptyCell.first != int(_size) - 1) {
		tmp = _puzzle[_emptyCell.first + 1][_emptyCell.second];
		_puzzle[_emptyCell.first + 1][_emptyCell.second] = 0;
		_puzzle[_emptyCell.first][_emptyCell.second] = tmp;
		return true;
    }
	return false;
};

/* bool	Puzzle::emptyRight(int** modifiedPuzzle) {
	int tmp;

	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			// if (i == _emptyCell.first && j == _emptyCell.second)
			modifiedPuzzle[i][j] == _puzzle[i][j];
		}
	}
    if (_emptyCell.second != -1 && _emptyCell.second != int(_size) - 1) {
        tmp = modifiedPuzzle[_emptyCell.first][_emptyCell.second + 1];
        modifiedPuzzle[_emptyCell.first][_emptyCell.second + 1] = 0;
        modifiedPuzzle[_emptyCell.first][_emptyCell.second] = tmp;
		return true;
    }
	return false;

};

bool 	Puzzle::emptyLeft(int** modifiedPuzzle) {

};

bool 	Puzzle::emptyUp(int** modifiedPuzzle) {

};

bool 	Puzzle::empthDown(int** modifiedPuzzle) {

}; */

bool	compareState(int** puzzle, int** result, size_t size) {
	size_t count = 0;
	
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (puzzle[i][j] == result[i][j])
				count++;
		}
	}
	std::cout << (count == (size * size)) << std::endl;
	return (count == (size * size));
};

void	Puzzle::solve() {
	std::cout << "tree size: " << _states.getSize() << std::endl;
	// Node *node = _states.createNode(_puzzle, _size);
	// node->calculateCost(_heuristic, _depth, _nbrPlaces);
	
	Node* node;
	std::cout << "_size: " << _size << std::endl;
	_states.setRoot(_puzzle, _size);
	std::cout << "oks1\n";
	std::cout << "_size: " << _size << std::endl;
	_states.getRoot()->calculateCost(_heuristic, _depth, _nbrPlaces);
	std::cout << "roor cost: " << _states.getRoot()->_cost << std::endl;
	
	node = _states.getRoot();
	while (!compareState(_puzzle, _result, _size)) {
		printArray(node->_puzzleState);
		if (emptyRight()) {
			node->_children.push_back(_states.createNode(_puzzle, _size));
			node->_children.back()->calculateCost(_heuristic, _depth, _nbrPlaces);
			emptyLeft();
			_openSet.push(node->_children.back());
		}
		if (emptyLeft()) {
			node->_children.push_back(_states.createNode(_puzzle, _size));
			node->_children.back()->calculateCost(_heuristic, _depth, _nbrPlaces);
			emptyRight();
			_openSet.push(node->_children.back());
		}
		if (emptyUp()) {
			node->_children.push_back(_states.createNode(_puzzle, _size));
			node->_children.back()->calculateCost(_heuristic, _depth, _nbrPlaces);
			emptyDown();
			_openSet.push(node->_children.back());
		}
		if (emptyDown()) {
			node->_children.push_back(_states.createNode(_puzzle, _size));
			node->_children.back()->calculateCost(_heuristic, _depth, _nbrPlaces);
			emptyLeft();
			_openSet.push(node->_children.back());
		}
		node = _openSet.top();
		// printArray(node->_puzzleState);
	}	
};