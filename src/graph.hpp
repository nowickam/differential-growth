//
//  graph.hpp
//  differentialGrowth
//
//  Created by Malgorzata Nowicka on 17/05/2022.
//

#pragma once

#include "ofMain.h"
#include "node.hpp"



class Graph{
public:
    float MIN_DIST = 30;
    float MAX_ADJ_DIST = 18;
    float CURVE_SPLIT = 1;
    float RANDOM_EDGE = 0.005;
    float MIN_SPLIT_DIST = 2;
    
    vector<Node*> nodes;
    vector<vector<int>> adj;

    Graph();
    ~Graph();
    
    int size;
    
    void addNode(int x, int y);
    void addEdge(int n1, int n2);
    
    void attract();
    void repulse();
    
    void split();
    void splitEdge(int n1, int n2, int newNode);
    
    void clearVisited();
    
    void draw();
    void update();
    void move();
    
    void print();
    void init();
};
