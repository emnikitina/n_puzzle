#include "Node.hpp"

Node::Node(): _cost(0), _parent(NULL), _children(std::vector<Node*>()) {};

Node::Node(Node const& copy): _cost(copy._cost), _parent(copy._parent) {
    _children.clear();
    _children = copy._children;
};

Node& Node::operator=(Node const& source) {
    if (this != &source) {
        _cost = source._cost;
        _parent = source._parent;
        _children.clear();
        _children = source._children;
    }
    return *this;
};

Node::~Node() {
    _children.clear();
    _parent = NULL;
};

std::ostream& operator<<(std::ostream& out, Node const& node) {
    out << node._cost;
    return  out;
};