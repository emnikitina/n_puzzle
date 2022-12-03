#include "Node.hpp"
#include "Puzzle.hpp"

Node::Node(): _cost(0), _size(0), _puzzleState(NULL), _emptyCell(std::make_pair<int, int>(1, 1)), _parent(NULL), _children(std::vector<Node*>()) /*, _direction(-1)*/ {};

Node::Node(Node const& copy): _cost(copy._cost), _size(copy._size), _emptyCell(copy._emptyCell), _parent(copy._parent) /*, _direction(copy._direction)*/ {
    if (_puzzleState) {
        for (size_t i = 0; i < _size; i++)
            delete[] _puzzleState[i];
        delete[] _puzzleState;
    }
    _puzzleState = new int* [_size];
    for (size_t i = 0; i < _size; i++) {
        _puzzleState[i] = new int[_size];
        for (size_t j = 0; j < _size; j++)
            _puzzleState[i][j] = copy._puzzleState[i][j];
    }
    _children.clear();
    _children = copy._children;
};

Node::Node(int** puzzle, size_t size): _cost(0), _size(size), /*_parent(NULL),*/ _children(std::vector<Node*>()) /*, _direction(-1)*/ {
    _puzzleState = new int* [size];
    for (size_t i = 0; i < size; i++) {
        _puzzleState[i] = new int[size];
        for (size_t j = 0; j < size; j++) {
            _puzzleState[i][j] = puzzle[i][j];
            if (_puzzleState[i][j] == 0)
                _emptyCell = std::make_pair<int, int>(i, j);
        }
    }
};

Node& Node::operator=(Node const& source) {
    if (this != &source) {
        _cost = source._cost;
        _size = source._size;
        // _parent = source._parent;
        if (_puzzleState) {
            for (size_t i = 0; i < _size; i++)
                delete[] _puzzleState[i];
            delete[] _puzzleState;
        }
        _puzzleState = new int* [_size];
        for (size_t i = 0; i < _size; i++) {
            _puzzleState[i] = new int[_size];
            for (size_t j = 0; j < _size; j++)
                _puzzleState[i][j] = source._puzzleState[i][j];
        }
        _emptyCell = source._emptyCell;
        _children.clear();
        _children = source._children;
        // _direction = source._direction;
    }
    return *this;
};

Node::~Node() {
    _children.clear();
    // _parent = NULL;
    if (_puzzleState) {
        for (size_t i = 0; i < _size; i++)
            delete[] _puzzleState[i];
        delete[] _puzzleState;
    }
};

float	Node::ManhattanHeuristics(int Ax, int Ay, int Bx, int By) {
    return float(abs(Ax - Bx) + abs(Ay - By));
};

float	Node::EuclidDistance(int Ax, int Ay, int Bx, int By) {
    return sqrt(pow(Ax - Bx, 2) + pow(Ay - By, 2));
};

float	Node::ChebyshevHeuristics(int Ax, int Ay, int Bx, int By) {
    return std::max(abs(Ax - Bx), abs(Ay - By));
};

bool	Node::emptyRight() {
    int tmp;

	// std::cout << "before empty cell i: " << _emptyCell.first << " j: " << _emptyCell.second << std::endl;
    if (_emptyCell.second != -1 && _emptyCell.second != int(_size) - 1) {
        tmp = _puzzleState[_emptyCell.first][_emptyCell.second + 1];
        _puzzleState[_emptyCell.first][_emptyCell.second + 1] = 0;
        _puzzleState[_emptyCell.first][_emptyCell.second] = tmp;
        _emptyCell.second++;
        // std::cout << "after empty cell i: " << _emptyCell.first << " j: " << _emptyCell.second << std::endl;
		// std::cout << "changed node: " << *this << std::endl;
        return true;
    }
	return false;

};

bool	Node::emptyLeft() {
    int tmp;
    
	if (_emptyCell.second != -1 && _emptyCell.second != 0) {
		tmp = _puzzleState[_emptyCell.first][_emptyCell.second - 1];
		_puzzleState[_emptyCell.first][_emptyCell.second - 1] = 0;
		_puzzleState[_emptyCell.first][_emptyCell.second] = tmp;
        _emptyCell.second--;
        return true;
    }
	return false;
};

bool	Node::emptyUp() {
    int tmp;
    
	if (_emptyCell.first != -1 && _emptyCell.first != 0) {
		tmp = _puzzleState[_emptyCell.first - 1][_emptyCell.second];
		_puzzleState[_emptyCell.first - 1][_emptyCell.second] = 0;
		_puzzleState[_emptyCell.first][_emptyCell.second] = tmp;
        _emptyCell.first--;
        return true;
    }
	return false;
};

bool	Node::emptyDown() {
    int tmp;
    
	if (_emptyCell.first != -1 && _emptyCell.first != int(_size) - 1) {
		tmp = _puzzleState[_emptyCell.first + 1][_emptyCell.second];
		_puzzleState[_emptyCell.first + 1][_emptyCell.second] = 0;
		_puzzleState[_emptyCell.first][_emptyCell.second] = tmp;
        _emptyCell.first++;
        return true;
    }
	return false;
};

void Node::calculateCost(int heuristic, std::unordered_map<int, std::pair<size_t, size_t> > nbrPositions) {
	// std::cout << "cost: " << _cost << std::endl;
    // std::cout << "heuristic: " << heuristic << std::endl;

    for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
            if (heuristic == manhattan)
				_cost += ManhattanHeuristics(i, j, nbrPositions[_puzzleState[i][j]].first, nbrPositions[_puzzleState[i][j]].second);
            else if (heuristic == euclid)
				_cost += EuclidDistance(i, j, nbrPositions[_puzzleState[i][j]].first, nbrPositions[_puzzleState[i][j]].second);
			else if (heuristic == chebyshev)
				_cost += ChebyshevHeuristics(i, j, nbrPositions[_puzzleState[i][j]].first, nbrPositions[_puzzleState[i][j]].second);
            // std::cout << "cost: " << _cost << std::endl;
        }
    }
    _cost = 1000000 - _cost;
};

std::ostream& operator<<(std::ostream& out, Node const& node) {

    out << "cost: " << node._cost << std::endl;
    // out << "direction: " << node._direction << std::endl;
    for (size_t i = 0; i < node._size; i++) {
        for (size_t j = 0; j < node._size; j++) { 
            out << node._puzzleState[i][j] << " ";
        }
        out << std::endl;
    }
    return  out;
};