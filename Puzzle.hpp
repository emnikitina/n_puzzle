#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#include <fstream>
#include <sstream>
#include "Tree.hpp"

class Puzzle {
    private:
        size_t                                              _size;
        int**                                               _puzzle;
        int**                                               _result;
        std::unordered_map<int, std::pair<size_t, size_t> > _nbrPlaces;

		void												printArray(int** arr);
		void												generator();
		std::string											getPureLine(std::string line);
		void												parse(char* filename);

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
};