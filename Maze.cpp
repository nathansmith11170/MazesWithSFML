#include <SFML/Graphics.hpp>
#include <MatrixGraph.h>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <cstdlib>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define NODES 25
#define STROKE 5

int recursiveBacktracker(MatrixGraph, MatrixGraph*, std::vector<int>*, std::unordered_set<int>*, int);

int main(int argc, char **argv) {
    std::vector<sf::RectangleShape> rects;
    std::vector<sf::RectangleShape> bottomEdges;
    std::vector<sf::RectangleShape> rightEdges;
    sf::RectangleShape topBorder;
    sf::RectangleShape leftBorder;
    MatrixGraph grid, maze;
    std::vector<int> stack;
    std::unordered_set<int> visitedSet;
    int i, currentVertex, row, column, j, seed;
    sf::RenderWindow window;
    char *commandLine;

    commandLine = *(argv+1);
    seed = atoi(commandLine);
    srand(seed);

    //Create two graphs with N^2 vertices
    for( i = 0; i < NODES * NODES; i++ ) {
        grid.add_vertice(i);
        maze.add_vertice(i);
    }

    //Populate the grid with the proper edges
    row = 0;
    column = 0;
    for( i = 0; i < NODES * NODES; i++ ) {
        if( i + 1 <= (row+1) * NODES - 1 ) {
            grid.add_edge(i, i + 1);
        }
        if( i - 1 >= row * NODES ) {
            grid.add_edge(i, i - 1);
        }
        if( i + NODES <= NODES * NODES - 1 ) {
            grid.add_edge(i, i + NODES);
        }
        if( i - NODES >= 0 ) {
            grid.add_edge(i, i - NODES);
        }

        column++;
        if(column >= NODES) {
            column = 0;
            row++;
        }
    }

    currentVertex = 0;
    visitedSet.insert(currentVertex);
    stack.push_back(currentVertex);

    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Maze");
    window.setFramerateLimit(60);

    //Set up shapes
    topBorder = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, STROKE));
    leftBorder = sf::RectangleShape(sf::Vector2f(STROKE, WINDOW_HEIGHT));
    row = 0;
    column = 0;
    for( i = 0; i < NODES * NODES; i++ ) {
        rects.push_back(sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH/NODES-STROKE,\
        WINDOW_HEIGHT/NODES-STROKE)));

        rects.at(i).setPosition(STROKE + column * (WINDOW_WIDTH/NODES),\
        STROKE + row * (WINDOW_HEIGHT/NODES));

        column++;
        if(column >= NODES) {
            column = 0;
            row++;
        }
    }

    row = 0;
    column = 0;
    for( i = 0; i < NODES * NODES; i++ ) {
        rightEdges.push_back(sf::RectangleShape(sf::Vector2f(STROKE,\
        WINDOW_HEIGHT/NODES-STROKE)));

        rightEdges.at(i).setPosition((column + 1) * (WINDOW_WIDTH/NODES),\
        STROKE + row * (WINDOW_HEIGHT/NODES));

        column++;
        if(column >= NODES) {
            column = 0;
            row++;
        }
    }

    row = 0;
    column = 0;
    for( i = 0; i < NODES * NODES; i++ ) {
        bottomEdges.push_back(sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH/NODES-STROKE,\
        STROKE)));

        bottomEdges.at(i).setPosition(STROKE + column * (WINDOW_WIDTH/NODES),\
        (row + 1) * (WINDOW_HEIGHT/NODES));

        column++;
        if(column >= NODES) {
            column = 0;
            row++;
        }
    }

    while( window.isOpen() ) {
        sf::Event event;
        while( window.pollEvent(event) ){
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        for( i = 0; i < rects.size(); i++) {
            rects.at(i).setFillColor(sf::Color::White);
            bottomEdges.at(i).setFillColor(sf::Color::Cyan);
            rightEdges.at(i).setFillColor(sf::Color::Cyan);
        }
        rects.at(currentVertex).setFillColor(sf::Color::Red);

        /* Drawing Logic */
        for( i = 0; i < rects.size(); i++) {
            if(i != currentVertex && visitedSet.count(i)) {
                rects.at(i).setFillColor(sf::Color::Cyan);
            }
            window.draw(rects.at(i));
        }
        
        for( i = 0; i < rightEdges.size(); i++ ) {
            std::vector<int> neighbors = maze.get_neighbors(i);
            for( j = 0; j < neighbors.size(); j++ ) {
                if(neighbors.at(j) == i + 1) {
                    window.draw(rightEdges.at(i));
                }
            }
        }

        for( i = 0; i < bottomEdges.size(); i++ ) {
            std::vector<int> neighbors = maze.get_neighbors(i);
            for( j = 0; j < neighbors.size(); j++ ) {
                if(neighbors.at(j) == i + NODES) {
                    window.draw(bottomEdges.at(i));
                }
            }
        }
        window.display();
        if(!stack.empty()) {
            currentVertex = recursiveBacktracker(grid, &maze, &stack, &visitedSet, currentVertex);
        }
    }

    return 0;
}

int recursiveBacktracker(MatrixGraph grid, MatrixGraph *maze, std::vector<int> *stack,\
std::unordered_set<int> *visitedSet, int currentVertex) {
    int i, j, isVisited = 0, randomIndex, nextVertex;
    std::vector<int> unvisitedNeighbors;
    std::vector<int> neighbors;
    int isvisited;

    neighbors = grid.get_neighbors(currentVertex);
    for( i = 0; i < neighbors.size(); i++ ) {
        if(!(*visitedSet).count(neighbors.at(i))) {
            unvisitedNeighbors.push_back(neighbors.at(i));
        }
    }
    if(!unvisitedNeighbors.empty()) {
        std::random_shuffle (unvisitedNeighbors.begin(), unvisitedNeighbors.end());
        nextVertex = unvisitedNeighbors.back();
        (*stack).push_back(currentVertex);
        (*maze).add_edge(currentVertex, nextVertex);
        (*visitedSet).insert(nextVertex);
    } else if (!(*stack).empty()) {
        nextVertex = (*stack).back();
        (*stack).pop_back();
    }
    return nextVertex;
}