#include <iostream>
#include <queue>
#include "Node.hpp"
#include <memory>
#include "Tree.hpp"

//typedef std::allocator<Node*>        Allocator;

Node* createNode(int** puzzle, size_t size) {
    std::allocator<Node> Allocator = std::allocator<Node>();
    Node* node = Allocator.allocate(1);
    Allocator.construct(node, puzzle, size);
    return node;
};

struct lessNode {
    bool operator()(Node const& a, Node const& b) {
        return (a._cost < b._cost);
    }

};

int main() {
    //std::priority_queue<Node*, std::vector<Node*>, lessNode> test;
    std::priority_queue<Node*, std::vector<Node*> > test;
    // std::priority_queue<Node*> test;
    int** puzzle = new int* [3];
    int k = 1;

    std::priority_queue<int> nbrs;
    nbrs.push(5);
    nbrs.push(7);
    nbrs.push(10);
    nbrs.push(10);
    nbrs.push(3);



    for (size_t i = 0; i < 3; i++) {
        puzzle[i] = new int[3];
        for (size_t j = 0; j < 3; j++)
            puzzle[i][j] = k++;
    }
    Node* node1 = createNode(puzzle, 3);
    node1->_cost = 5;
    Node* node2 = createNode(puzzle, 3);
    node2->_cost = 7;
    Node* node3 = createNode(puzzle, 3);
    node3->_cost = 10;
    Node* node4 = createNode(puzzle, 3);
    node4->_cost = 10;
    Node* node5 = createNode(puzzle, 3);
    node5->_cost = 3;

    test.push(node1);
    test.push(node2);
    test.push(node3);
    test.push(node4);
    test.push(node5);

    while (!nbrs.empty()) {
        std::cout << nbrs.top() << std::endl;
        nbrs.pop();
    }


    // std::cout << "cost: " << node4->_cost << std::endl;
    while (!test.empty()) {
        std::cout << *test.top() << std::endl;
        test.pop();
    }

}