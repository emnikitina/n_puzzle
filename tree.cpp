#include "tree.hpp"

Tree::Tree(): _allocator(Allocator()), _root(NULL), _size(0) {};

Tree::~Tree() {
    clear(_root);
};


Tree::pointer Tree::createNode(std::string data);

void Tree::destoyNode(pointer node);

void Tree::nodeToOut(std::ostream& out, pointer node);


Tree::pointer Tree::getRoot() const {
    return _root;
};

size_t Tree::getSize() const {
    return _size;
};

Tree::pointer Tree::find(std::string data, pointer node) const;

void Tree::clear(pointer node);

std::ostream& operator<<(std::ostream& out, Tree& tree);