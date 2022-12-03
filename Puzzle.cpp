#include "Puzzle.hpp"

Puzzle::Puzzle(): _size(0), _puzzle(NULL), _result(NULL), _nbrPlaces(std::unordered_map<int, std::pair<size_t, size_t> >()), _states(Tree()), _heuristic(-1), _emptyCell(std::make_pair(-1, -1)), _depth(0), _path("") {};

Puzzle::Puzzle(size_t size): _size(size), _nbrPlaces(std::unordered_map<int, std::pair<size_t, size_t> >()), _states(Tree()), _heuristic(-1), _emptyCell(std::make_pair(-1, -1)), _depth(0), _path("") {
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

Puzzle::Puzzle(char* filename): _size(0), _nbrPlaces(std::unordered_map<int, std::pair<size_t, size_t> >()), _states(Tree()), _heuristic(-1), _emptyCell(std::make_pair(-1, -1)), _depth(0), _path("") {
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
    int inv = 0;

	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			if (_puzzle[i][j]) {
				for (size_t l = 0; l < i; l++) {
					for (size_t m = 0; m < j; m++) {
						if (_puzzle[l][m] && _puzzle[l][m] > _puzzle[i][j])
							inv++;
					}
				}
			}
			else
                inv += (1 + float(i + j) / _size);
		}
	}
    return (inv & 1);
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

	// std::cout << "before empty cell i: " << _emptyCell.first << " j: " << _emptyCell.second << std::endl;
    if (_emptyCell.second != -1 && _emptyCell.second != int(_size) - 1) {
        tmp = _puzzle[_emptyCell.first][_emptyCell.second + 1];
        _puzzle[_emptyCell.first][_emptyCell.second + 1] = 0;
        _puzzle[_emptyCell.first][_emptyCell.second] = tmp;
        _emptyCell.second++;
        // std::cout << "after empty cell i: " << _emptyCell.first << " j: " << _emptyCell.second << std::endl;
		return true;
    }
	return false;
};

/*bool Puzzle::emptyLeft() {
    int tmp;
    
	if (_emptyCell.second != -1 && _emptyCell.second != 0) {
		tmp = _puzzle[_emptyCell.first][_emptyCell.second - 1];
		_puzzle[_emptyCell.first][_emptyCell.second - 1] = 0;
		_puzzle[_emptyCell.first][_emptyCell.second] = tmp;
        _emptyCell.second--;
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
        _emptyCell.first--;
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
        _emptyCell.first++;
        return true;
    }
	return false;
};*/

bool	Puzzle::compareState(int** puzzle) {
	size_t count = 0;
	
	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			if (puzzle[i][j] == _result[i][j])
				count++;
		}
	}
	std::cout << (count == (_size * _size)) << std::endl;
	return (count == (_size * _size));
};

void Puzzle::clearPriorityQueue(std::priority_queue<Node*, std::vector<Node*> /*, lessNode*/ > priQueue) {
    while (!priQueue.empty())
        priQueue.pop();
};

void Puzzle::changeEmptyCoordinates(int direction) {
    if (direction == right)
        _emptyCell.second++;
    else if (direction == left)
        _emptyCell.second--;
    else if (direction == up)
        _emptyCell.first--;
    else if (direction == down)
        _emptyCell.first++;
};

/*void Puzzle::changeNode(Node* node, int direction) {
    node->_children.push_back(_states.createNode(node->_puzzleState, _size));
    node->_children.back()->calculateCost(_heuristic, _depth, _nbrPlaces);
    node->_children.back()->_direction = direction;
    // std::cout << "new state\n";
	// printArray(node->_children.back()->_puzzleState); // REMOVE
	// std::cout << "new state cost: " << node->_children.back()->_cost << std::endl;
	// node->_children.back()->_parent = node;
    _openSet.push(node->_children.back());
};*/

bool findeNodeInPriQueue(Node* node, std::priority_queue<Node*, std::vector<Node*> /*, lessNode*/ > priQueue) {
    std::priority_queue<Node*, std::vector<Node*> /*, lessNode*/ > copy = priQueue;

    while (copy.size()) {
        if (node == copy.top())
            return true;
        copy.pop();
    }
    return false;
};

void Puzzle::changeNode(Node* node /*, int direction*/ ) {
    /*bool finded = false;
    std::priority_queue<Node*, std::vector<Node*>, lessNode> copyOpenSet = _openSet;
    
    while (copyOpenSet.size()) {
        if (node == copyOpenSet.top())
            finded = true;
    }
    clearPriorityQueue(copyOpenSet);
    
    if (!finded && (_closeSet.find(node) == _closeSet.end())) {*/
        node->_children.push_back(_states.createNode(node->_puzzleState, _size));
        node->_children.back()->calculateCost(_heuristic, _nbrPlaces);
        // node->_children.back()->_direction = direction;
        // _openSet.push(node->_children.back());
    //}
    // else {
    //     /// ???????
    //     if () {
    //         if () {

    //         }
    //     }
    // }    
};

void printPriQueue(std::priority_queue<Node*, std::vector<Node*> > priQueue) {
    std::priority_queue<Node*, std::vector<Node*> > copy = priQueue;
    
    std::cout << "open set: \n";
    while (copy.size()) {
        std::cout << *copy.top();
        copy.pop();
    }    
}

std::vector<Node*> Puzzle::makeChildren(Node* node) {
	std::vector<Node*> children;

	if (node->emptyRight()) {
		children.push_back(_states.createNode(node->_puzzleState, _size));
        children.back()->calculateCost(_heuristic, _nbrPlaces);
		node->emptyLeft();
	}
	if (node->emptyLeft()) {
		children.push_back(_states.createNode(node->_puzzleState, _size));
        children.back()->calculateCost(_heuristic, _nbrPlaces);
		node->emptyRight();
	}
	if (node->emptyUp()) {
		children.push_back(_states.createNode(node->_puzzleState, _size));
        children.back()->calculateCost(_heuristic, _nbrPlaces);
		node->emptyDown();
	}
	if (node->emptyDown()) {
		children.push_back(_states.createNode(node->_puzzleState, _size));
        children.back()->calculateCost(_heuristic, _nbrPlaces);
		node->emptyUp();
	}
	return children;

};

/*bool findOpenSet(std::priority_queue<std::pair<int, Node*> >  openSet, Node* node) {



}*/

void	Puzzle::solve() {
	Node												node;
	Node*												tmp;
    std::chrono::time_point<std::chrono::steady_clock>	end, start = std::chrono::steady_clock::now();
	std::priority_queue<std::pair<int, Node*> >			openQueue;
    // std::set<Node*>										closeSet;
	std::vector<Node*>									children;
	std::set<int**>										openSet, closeSet;
	bool												success = false;
	size_t												size;

	node = Node(_puzzle, _size);
	children = makeChildren(&node);
	size = children.size();
	for (size_t i = 0; i < size; ++i) {
		openSet.insert(children[i]->_puzzleState);
		openQueue.push({children[i]->_cost, children[i]});
	}
	while (!openSet.empty() && !success) {
		tmp = openQueue.top().second;
		if (compareState(tmp->_puzzleState)) {
			_solutionNode = tmp;
			success = true;
			break ;
		}
	}
}


void	Puzzle::solve() {
    Node*												node = NULL;
    std::chrono::time_point<std::chrono::steady_clock>	end, start = std::chrono::steady_clock::now();
	std::priority_queue<std::pair<int, Node*> >			openSet;
    std::set<Node*>										closeSet;
	std::vector<Node*>									children;


	_states.setRoot(_puzzle, _size);
	_states.getRoot()->calculateCost(_heuristic, _nbrPlaces);
    openSet.push(std::make_pair(_states.getRoot()->_cost + _depth ,  _states.getRoot()));
    // printPriQueue(_openSet);
    while (openSet.size()) {
        node = openSet.top().second;
        std::cout << "lowest node: " << *node;
        _sizeComplexity++;
        if (compareState(node->_puzzleState, _result, _size)) {
            _solutionNode = node;
            break;
        }
        else {
            openSet.pop(); // opened - state
            closeSet.insert(node);
		
			/*std::cout << "close set:\n";
			for (std::set<Node*>::iterator it = closeSet.begin(); it != closeSet.end(); it++)
				std::cout << **it << " "; */
            
			children = makeChildren(node);
            /*std::cout << "node children: \n";
            for (size_t i = 0; i < children.size(); i++) {
                std::cout << *children[i] << std::endl;
            }*/
            // _closeSet.insert( ??? );
            for (size_t i = 0; i < children.size(); i++) {
				if (children[i] ) {
                    
                }
                if (compareState(children[i]->_puzzleState, _result, _size)) {
					node->_children.push_back(children[i]);
					node->_children.back()->_parent = node;
					_solutionNode = node->_children.back();
                    break;
				}
                else if (closeSet.find(children[i]) == closeSet.end()) {
					openSet.push(std::make_pair(children[i]->_cost + _depth, children[i]));
					node->_children.push_back(children[i]);
				}
            }
        }
           
        std::cout << "new node: " << *node;
        
        std::cout << "depth: " << _depth << std::endl;
        /*std::cout << "new puzzle state: " << std::endl;
        for (size_t i = 0; i < _size; i++) {
            for (size_t j = 0; j < _size; j++) {
                _puzzle[i][j] = _openSet.top()->_puzzleState[i][j];
                std::cout << _puzzle[i][j] << " ";
            }
            std::cout << std::endl;
        }*/
        // changeEmptyCoordinates(node->_direction);
        // std::cout << "priority queue\n";
        // while (!_openSet.empty()) {
        //     std::cout << _openSet.top()->_cost << std::endl;
        //     _openSet.pop();
        // }
		_depth++;
        sleep(1);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "work time: " << (end - start).count() << "s" << std::endl;
};