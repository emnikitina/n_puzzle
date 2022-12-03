#pragma once

#include <ostream>
#include <vector>
#include <unordered_map>

class Node {
    public:
        int					_cost;
        size_t				_size;
        int**				_puzzleState;
		std::pair<int, int>	_emptyCell;
        Node*				_parent;
        std::vector<Node*>	_children;
        // int					_direction;


        Node();
        Node(int** puzzle, size_t size);
        Node(Node const& copy);
        Node& operator=(Node const& source);
        ~Node();

        float	ManhattanHeuristics(int Ax, int Ay, int Bx, int By);
		float	EuclidDistance(int Ax, int Ay, int Bx, int By);
		float	ChebyshevHeuristics(int Ax, int Ay, int Bx, int By);
        void    calculateCost(int heuristic, std::unordered_map<int, std::pair<size_t, size_t> > nbrPositions);

		bool	emptyRight();
		bool	emptyLeft();
		bool	emptyUp();
		bool	emptyDown();
        
        friend std::ostream& operator<<(std::ostream& out, Node const& node);
};

/* struct lessNode {
	bool operator() (Node* x, Node* y) const { return x->_cost >= y->_cost; }
}; */