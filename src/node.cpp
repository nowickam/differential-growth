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

    mid = (other.pos - pos) * 0.5;
    mid *= ATTRACT_SPEED;

    step += mid;
    
//    cout<<"att "<<step<<endl;
}

void Node::repulse(Node other){
    glm::vec2 diff = glm::normalize(pos - other.pos);
    float dist = glm::distance(pos, other.pos);
    diff *= REPULSE_SPEED * 1 / dist;

    step += diff;

//    cout<<"rep "<<step<<endl;
    
}

void Node::move(){
    pos += step;
    
//    reset the node
    step.x = step.y = 0;
}

void Node::draw(){
    ofDrawCircle(pos, 5);
}


void Node::print(){
    cout<<"node "<<id<<endl;
//    for(int j=0; j<adj.size(); j++){
//        cout<<"\tadj "<<adj[j].pos<<endl;
//    }
}
