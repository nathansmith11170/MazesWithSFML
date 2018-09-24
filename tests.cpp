#include <MatrixGraph.h>
#include <cstdio>

#define NODES 5
int main() {
    int i, row, column;
    std::vector<int> neighborsTest;
    MatrixGraph test;

    for( i = 0; i < NODES*NODES; i++ ) {
        test.add_vertice(i);
    }

    row = 0;
    column = 0;
    for( i = 0; i < NODES*NODES; i++ ) {
        if( i + 1 <= (row+1) * NODES - 1 ) {
            test.add_edge(i, i + 1);
        }
        if( i - 1 >= row * NODES ) {
            test.add_edge(i, i - 1);
        }
        if( i + NODES <= NODES*NODES - 1 ) {
            test.add_edge(i, i + NODES);
        }
        if( i - NODES >= 0 ) {
            test.add_edge(i, i - NODES);
        }

        column++;
        if(column >= NODES) {
            column = 0;
            row++;
        }
    }
    neighborsTest = test.get_neighbors(1);
    for( i = 0; i < neighborsTest.size(); i++ ) {
        std::cout << neighborsTest.at(i) << std::endl;
    }
    std::cout << "Next check" << std::endl;
    neighborsTest = test.get_neighbors(4);
    for( i = 0; i < neighborsTest.size(); i++ ) {
        std::cout << neighborsTest.at(i) << std::endl;
    }
    std::cout << "Next check" << std::endl;
    neighborsTest = test.get_neighbors(5);
    for( i = 0; i < neighborsTest.size(); i++ ) {
        std::cout << neighborsTest.at(i) << std::endl;
    }
    std::cout << "Next check" << std::endl;
    neighborsTest = test.get_neighbors(16);
    for( i = 0; i < neighborsTest.size(); i++ ) {
        std::cout << neighborsTest.at(i) << std::endl;
    }
    test.print_graph();
}