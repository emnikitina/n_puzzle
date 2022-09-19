#include "tree.hpp"

Tree::Tree(): _allocator(Allocator()), _root(NULL), _size(0) {};

Tree::~Tree() {
    clear(_root);
};


Tree::pointer Tree::createNode(int cost) {
    Node* node;

    _allocator.allocate(1);
    _allocator.construct(node, cost);
    return node;
};

void Tree::destoyNode(pointer node) {
    if (node) {
        _allocator.destroy(node);
        _allocator.deallocate(node, 1);
    }
};


Tree::pointer Tree::getRoot() const {
    return _root;
};

size_t Tree::getSize() const {
    return _size;
};

Tree::pointer Tree::find(int cost, pointer node) const {
    pointer finded;
    
    if (node && node->_cost == cost)
        return node;
    for (size_t i = 0; i < node->_children.size(); i++) {
        if ((finded = find(cost, node->_children[i])))
            return finded;
    }
    return NULL;
};

void Tree::clear(pointer node) {
    if (node) {
        for (size_t i = 0; i < node->_children.size(); i++)
            clear(node->_children[i]);
        destoyNode(node);
        node = NULL;
    }
};

std::ostream& operator<<(std::ostream& out, Tree& tree);