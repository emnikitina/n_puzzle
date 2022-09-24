#pragma once

#include <memory>
#include "Node.hpp"

class Tree {
	public:
		typedef std::allocator<Node>        Allocator;
		typedef typename Allocator::pointer pointer;

	private:
        Allocator _allocator;
        pointer _root;
        size_t _size;
		pointer _currentNode;

    public:		
		Tree();
        ~Tree();

        pointer	getRoot() const;
        size_t	getSize() const;

		void setRoot(int** puzzle, size_t size);

		pointer	createNode(int** puzzle, size_t size);
        void	destoyNode(pointer node);

        pointer	find(int cost, pointer node) const;
        void	clear(pointer node);


        friend std::ostream& operator<<(std::ostream& out, Tree& tree);
};