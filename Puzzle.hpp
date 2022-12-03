#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#include <fstream>
#include <sstream>

#include <queue>
#include <cmath>
#include <unordered_set>
#include <chrono>
#include <map>
#include <set>


#include <unistd.h>


#include "Tree.hpp"

enum heuristic {manhattan, euclid, chebyshev};
enum direction {right, left, up, down};

class Puzzle {
    private:
        size_t                                              _size;
        int**                                               _puzzle;
        int**                                               _result;
        std::unordered_map<int, std::pair<size_t, size_t> > _nbrPlaces;
		// std::priority_queue<Node*, std::vector<Node*> /*, lessNode*/ >                          _openSet;
        // std::unordered_set<Node*>							_closeSet;
        Tree                                                _states;
		int													_heuristic;
		std::pair<int, int>									_emptyCell;
		size_t												_depth;					// equal number of moves
		std::string											_path;
		size_t												_sizeComplexity;
		// size_t												_moves;
        Node*												_solutionNode;

		void												printArray(int** arr);
		void												generator();
		std::string											getPureLine(std::string line);
		void												parse(char* filename);
        // void                                                calculateCost(Node* node);
		// float												ManhattanHeuristics(int Ax, int Ay, int Bx, int By);
		// float												EuclidDistance(int Ax, int Ay, int Bx, int By);
		// float												ChebyshevHeuristics(int Ax, int Ay, int Bx, int By);
		bool												emptyRight();
		bool 												emptyLeft();
		bool 												emptyUp();
		bool 												emptyDown();
    
    public:
       Puzzle();
	   Puzzle(size_t size);
	   Puzzle(char* filename);
       ~Puzzle();

       size_t                                               getSize() const;
       int**                                                getPuzzle() const;          // CHANGE RETURN TYPE
       int**                                                getResultPuzzle() const;    // CHANGE RETURN TYPE
       std::unordered_map<int, std::pair<size_t, size_t> >  getNbrPlaces() const;
       int													getHeuristic() const;

       void                                                 setSize(size_t size);
       void                                                 setPuzzle(int** puzzle, size_t size);
       void                                                 setRezultPuzzle();
	   void													setHeuristic(int heuristic);

	   bool													checkSolvability();
       void                                                 solve();
       // void													clearOpenSet();
       void                                                 clearPriorityQueue(std::priority_queue<Node*, std::vector<Node*> /*, lessNode*/ > priQueue);
       void													changeEmptyCoordinates(int direction);
	   void 												changeNode(Node* node /*, int direction*/ );

	   std::vector<Node*>									makeChildren(Node* node);

       bool                                                 compareState(int** puzzle);
};