//
//  node.cpp
//  differentialGrowth
//
//  Created by Malgorzata Nowicka on 17/05/2022.
//

#include "node.hpp"

Node::Node(int _id){
    id = _id;
}

Node::Node(int _id, int x, int y){
    id = _id;
    pos = {x, y};
    step = {0,0};
}


void Node::attract(Node other){
    glm::vec2 mid;
    glm::vec2 target = other.pos + 20 * glm::vec2(ofNoise(other.pos.x*0.1)-0.5, ofNoise(other.pos.y*0.1)-0.5);

    mid = (target - pos) * 0.5;
    mid *= ATTRACT_SPEED;

    step += mid;
    
//    ATTRACT_SPEED = (ofNoise(ofGetFrameNum()*0.01))*0.1;
//    REPULSE_SPEED = (ofNoise(ofGetFrameNum()*0.01))*10;
    
//    cout<<"att "<<step<<endl;
}

void Node::repulse(Node other){
    glm::vec2 diff = glm::normalize(pos - other.pos);
    float dist = glm::distance(pos, other.pos);
    if(dist > 0){
        diff *= REPULSE_SPEED / (dist*1.5);
        step += diff;
    }

//    cout<<"rep "<<step<<endl;
    
}

void Node::move(){
    pos += step;
    
//    reset the node
    step.x = step.y = 0;
}


void Node::print(){
    cout<<"node "<<id<<endl;
}
