#include "Node.hpp"

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

Node::Node(int** puzzle, size_t size): _cost(0), _parent(NULL), _children(std::vector<Node*>()) {
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

std::ostream& operator<<(std::ostream& out, Node const& node) {
    out << node._cost;
    return  out;
};