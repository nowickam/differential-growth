//
//  graph.cpp
//  differentialGrowth
//
//  Created by Malgorzata Nowicka on 17/05/2022.
//

#include "graph.hpp"

Graph::Graph(){
    size = 0;
}

Graph::~Graph(){

}

void Graph::addNode(int x, int y){
    Node *node = new Node(size, x, y);
    size++;
    nodes.push_back(node);
    adj.push_back(vector<int>());
    visited.push_back(false);
}

void Graph::addEdge(int n1, int n2){
    adj[n1].push_back(n2);
    adj[n2].push_back(n1);
}

void Graph::attract(){
    for(int i=0; i<adj.size(); i++){
        for(int j=0; j<adj[i].size(); j++){
            (*nodes[i]).attract(*nodes[adj[i][j]]);
        }
    }
    
}

void Graph::split(){
//    for(int i=0; i<nodes.size(); i++){
//        Node node = nodes[i];
//        for(int j=0; j<node.adj.size(); j++){
//            Node adj = nodes[i].adj[j];
//            float dist = glm::distance(node.pos, adj.pos);
//            if(dist > MAX_ADJ_DIST){
//                glm::vec2 newPos = (node.pos + adj.pos) / 2;
//                Node newNode = Node(newPos.x, newPos.y);
//                addNode(&newNode);
//                splitEdge(&node, &adj, &newNode);
////                print();
//
//            }
//        }
//    }
    
    
//    vector<Node> stack;
//    stack.push_back(*nodes[0]);
////    cout<<nodes[0].visited<<endl;
//    visited[*nodes[0]] = true;
////    cout<<nodes[0].visited<<endl;
//
//    while(stack.size() > 0){
////        for(auto n : stack)
////            n.print();
////        cout<<endl;
//        Node node = stack.back();
//        stack.pop_back();
//
//        for(int i=0; i<node.adj.size(); i++){
//            Node adj = node.adj[i];
//            if(!adj.visited){
//                stack.push_back(adj);
//                adj.visited = true;
//
//                float dist = glm::distance(node.pos, adj.pos);
//                if(dist > MAX_ADJ_DIST){
//                    glm::vec2 newPos = (node.pos + adj.pos) / 2;
//                    Node newNode = Node(newPos.x, newPos.y);
//                    addNode(&newNode);
//                    splitEdge(&node, adj, &newNode);
//                }
//            }
//        }
//    }
//    cout<<"stack empty"<<endl;
//
}

void Graph::splitEdge(Node *n1, Node *n2, Node *newNode){
//    (*n1).deleteAdj(n2);
//    (*n1).addAdj(newNode);
//
//    (*n2).deleteAdj(n1);
//    (*n2).addAdj(newNode);
//
//    (*newNode).addAdj(n1);
//    (*newNode).addAdj(n2);
    
}

void Graph::repulse(){
    float d;

    for(int i=0; i<nodes.size(); i++){
        for(int j=0; j<nodes.size(); j++){
            if(i != j){
                d = glm::distance((*nodes[i]).pos, (*nodes[j]).pos);
                if(d < MIN_DIST){
                    (*nodes[i]).repulse(*nodes[j]);
                    (*nodes[j]).repulse(*nodes[i]);
                }
            }
        }
    }
    
    
}

void Graph::move(){
    for(int i=0; i<nodes.size(); i++){
        (*nodes[i]).move();
    }
}

void Graph::draw(){
    for(int i=0; i<adj.size(); i++){
        (*nodes[i]).draw();
        for(int j=0; j<adj[i].size(); j++){
            ofDrawLine((*nodes[i]).pos, (*nodes[adj[i][j]]).pos);
        }
    }

}

void Graph::update(){
    attract();
    repulse();
    move();
//    split();
}

void Graph::print(){
    for(int i=0; i<nodes.size(); i++){
        (*nodes[i]).print();
    }

}

