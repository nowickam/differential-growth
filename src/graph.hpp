//
//  graph.hpp
//  differentialGrowth
//
//  Created by Malgorzata Nowicka on 17/05/2022.
//

#pragma once

#include "ofMain.h"
#include "node.hpp"

# define MIN_DIST 60
#define MAX_ADJ_DIST 50

class Graph{
public:
//    Node root;
//    vector<Node*> nodes;
    
    vector<Node*> nodes;
    vector<vector<int>> adj;
    vector<bool> visited;
    
//    map<Node, vector<Node>> adj;
//    map<Node, bool> visited;

    Graph();
    ~Graph();
    
    int size;
    
    void addNode(int x, int y);
    void addEdge(int n1, int n2);
    
    void attract();
    void repulse();
    
    void split();
    void splitEdge(Node* n1, Node* n2, Node *newNode);
    
    void draw();
    void update();
    void move();
    
    void print();

    
};
