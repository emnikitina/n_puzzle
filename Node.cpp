#include "Node.hpp"
#include "Puzzle.hpp"

Node::Node(): _cost(0), _size(0), _parent(NULL), _children(std::vector<Node*>()) {};

Node::Node(Node const& copy): _cost(copy._cost), _size(copy._size), _parent(copy._parent) {
    _children.clear();
    _children = copy._children;
    _puzzleState = new int* [_size];
    for (size_t i = 0; i < _size; i++) {
        _puzzleState[i] = new int[_size];
        for (size_t j = 0; j < _size; j++)
            _puzzleState[i][j] = copy._puzzleState[i][j];
    }
};

Node::Node(int** puzzle, size_t size): _cost(0), _size(size), _parent(NULL), _children(std::vector<Node*>()) {
    _puzzleState = new int* [size];
    for (size_t i = 0; i < size; i++) {
        _puzzleState[i] = new int[size];
        for (size_t j = 0; j < size; j++)
            _puzzleState[i][j] = puzzle[i][j];
    }
};

Node& Node::operator=(Node const& source) {
    if (this != &source) {
        _cost = source._cost;
        _size = source._size;
        _parent = source._parent;
        _children.clear();
        _children = source._children;
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
    }
    return *this;
};

Node::~Node() {
    _children.clear();
    _parent = NULL;
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

void Node::calculateCost(int heuristic, size_t depth, std::unordered_map<int, std::pair<size_t, size_t> > nbrPositions) {
	std::cout << "size: " << _size << std::endl;
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
    _cost += depth;	
};

std::ostream& operator<<(std::ostream& out, Node const& node) {
    out << node._cost;
    return  out;
};