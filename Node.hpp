#pragma once

#include <ostream>
#include <vector>

class Node {
    public:
        int     _cost;
        size_t  _size;
        int**   _puzzleState;
        Node*   _parent;
        std::vector<Node*> _children;

        Node();
        Node(int** puzzle, size_t size);
        Node(Node const& copy);
        Node& operator=(Node const& source);
        ~Node();

        friend std::ostream& operator<<(std::ostream& out, Node const& node);
};