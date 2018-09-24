/*
Author: Nathan Smith

This header file contains the implementation of the mathematical type Graph.
The implementation represents a strict graph, also known as a simple graph,
which contains no self-loops, no multiple edges, and no weights. It is also 
non-directional.

The Graph is represented by a class that contains a matrix, which
is built on the concept of linked lists in the user-defined header 
LinkedList.h.

The matrix representation is a two dimensional array of integers, where the
existence of a positive integer in a column indicates an edge between the
vertice represented by the row and the vertice represented by the column.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#ifndef MATRIX_GRAPH
#define MATRIX_GRAPH

class MatrixGraph {
private:
    //The matrix representation, modeled as an array of arrays of integers.
    std::vector<std::vector<int>> matrix;

    //A list of used integer identifiers that has the same ordering as the
    //matrix
    std::vector<int> order;

    //A hash-mapped set of vertex identifiers
    std::unordered_set<int> vertices;

    //A variable to keep track of the number of vertices in the graph
    int size;

public:
    MatrixGraph () {
        matrix = std::vector<std::vector<int>>();
        order = std::vector<int>();
        vertices = std::unordered_set<int>();
    }

    //Requires that the identifier used is not contained already within
    //(*this).order
    void add_vertice(int identifier) {
        //Add vertex identifier to the identifier set
        (*this).vertices.insert(identifier);
        (*this).order.push_back(identifier);

        //Extend the matrix
        (*this).matrix.push_back(std::vector<int>());

        //Extend every row wiht a zero
        for(int i = 0; i < (*this).matrix.size()-1; i++) {
            (*this).matrix.at(i).push_back(0);
        }

        //Initialize final row to zeroes
        for(int i = 0; i < (*this).matrix.size(); i++) {
            (*this).matrix.at((*this).matrix.size()-1).push_back(0);
        }
    }

    //Requires that ident1 and ident2 are contained in (*this).order
    void add_edge(int ident1, int ident2) {
        int index1, index2;
        
        for(int i = 0; i < (*this).order.size(); i++) {
            if((*this).order.at(i) == ident1) {
                index1 = i;
                break;
            }
        }

        for(int i = 0; i < (*this).order.size(); i++) {
            if((*this).order.at(i) == ident2) {
                index2 = i;
                break;
            }
        }

        (*this).matrix.at(index1).at(index2) = 1;
        (*this).matrix.at(index2).at(index1) = 1;
    }

    //Vertice identifier must be contained in the graph
    //Returns a pointer to the number of neighbors with each successive
    //integer in that array being the identifier of a neighbor
    std::vector<int> get_neighbors(int identifier) {
        int index1;
        std::vector<int> neighbors;

        for(int i = 0; i < (*this).order.size(); i++) {
            if((*this).order.at(i) == identifier) {
                index1 = i;
            }
        }

        for(int i = 0; i < (*this).matrix.at(index1).size(); i++) {
            if((*this).matrix.at(index1).at(i) == 1) {
                neighbors.push_back((*this).order.at(i));
            }
        }
        return neighbors;
    }

    void print_graph() {
        for(int i = 0; i < (*this).matrix.size(); i++) {
            for(int j = 0; j < (*this).matrix.at(i).size(); j++) {
                std::cout << (*this).matrix.at(i).at(j) << " ";
            }
            std::cout << "\n";
        }
    }
};
#endif