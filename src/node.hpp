//
//  node.hpp
//  differentialGrowth
//
//  Created by Malgorzata Nowicka on 17/05/2022.
//

#pragma once

#include "ofMain.h"

//#define ATTRACT_SPEED 0.05
//#define REPULSE_SPEED 5

class Node{
public:
    float ATTRACT_SPEED = 0.01;
    float REPULSE_SPEED = 1;
    
    int id;
//    position
    glm::vec2 pos;
//    all the attractions from the neighbors, repulsions from others
    glm::vec2 step;

    Node(int id);
    Node(int id, int x, int y);
    
    
//    attract the neighbors to the half-point between them and add node if distance between neighbors too big
    void attract(Node other);
//    repulse all the other nodes that are to close
    void repulse(Node other);
//    apply step to the current position
    void move();
    
    void print();
    
//    bool operator<(const Node& other) const{
//        return other.id < id;
//    }
    
};
