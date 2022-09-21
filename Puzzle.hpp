#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#include <fstream>
#include <sstream>

#include <queue>
#include <cmath>

#include "Tree.hpp"

enum heuristic {manhattan, euclid, chebyshev};

class Puzzle {
    private:
        size_t                                              _size;
        int**                                               _puzzle;
        int**                                               _result;
        std::unordered_map<int, std::pair<size_t, size_t> > _nbrPlaces;
        std::priority_queue<Node*>                          _openSet;
        std::priority_queue<Node*>                          _closeSet;
        Tree                                                _states;
		int													_heusistic;

		void												printArray(int** arr);
		void												generator();
		std::string											getPureLine(std::string line);
		void												parse(char* filename);
        void                                                 calculateCost(Node* node);
		int													ManhattanHeuristics(int Ax, int Ay, int Bx, int By);
		float												EuclidDistance(int Ax, int Ay, int Bx, int By);
		int													ChebyshevHeuristics(int Ax, int Ay, int Bx, int By);

    public:
       Puzzle();
	   Puzzle(size_t size);
	   Puzzle(char* filename);
       ~Puzzle();

       size_t                                               getSize() const;
       int**                                                getPuzzle() const;          // CHANGE RETURN TYPE
       int**                                                getResultPuzzle() const;    // CHANGE RETURN TYPE
       std::unordered_map<int, std::pair<size_t, size_t> >  getNbrPlaces() const;

       void                                                 setSize(size_t size);
       void                                                 setPuzzle(int** puzzle, size_t size);
       void                                                 setRezultPuzzle();

	   bool													checkSolvability();
       void                                                 solve();
};