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
    for(auto n : nodes)
        delete n;
    nodes.clear();
}

void Graph::init(){    
//    LINE
//    addNode(100, ofGetHeight()/2);
//    addNode(ofGetWidth()-100, ofGetHeight()/2-1);
//
//    addEdge(0, 1);
    
    
//  TRIANGLE
//    addNode(ofGetWidth()/2, ofGetHeight()/2-100);
//    addNode(ofGetWidth()/2+100, ofGetHeight()/2+100);
//    addNode(ofGetWidth()/2-100, ofGetHeight()/2+100);
//
//    addEdge(0, 1);
//    addEdge(1, 2);
//    addEdge(2, 0);
    
//    RANDOM
//    int MARGIN = ofGetHeight()/3;
//
//    addNode(100, ofGetHeight()/2);
//    for(int i=1; i<10; i++){
//        addNode(ofClamp(ofRandomWidth(), MARGIN, ofGetWidth()-MARGIN),
//                      ofClamp(ofRandomHeight(), MARGIN, ofGetHeight()-MARGIN));
//        addEdge(i, i-1);
//    }
//
//    addEdge(0, 3);
//    addEdge(1, 4);
//    addEdge(2, 9);
    
//    CIRCLE
    int cor = 40;
    int mid = 60;
    addNode(ofGetWidth()/2 - cor, ofGetHeight()/2-cor);
    addNode(ofGetWidth()/2, ofGetHeight()/2-mid);
    addNode(ofGetWidth()/2 + cor, ofGetHeight()/2-cor);
    addNode(ofGetWidth()/2 + mid, ofGetHeight()/2);
    addNode(ofGetWidth()/2 + cor, ofGetHeight()/2+cor);
    addNode(ofGetWidth()/2, ofGetHeight()/2+mid);
    addNode(ofGetWidth()/2 - cor, ofGetHeight()/2+cor);
    addNode(ofGetWidth()/2 - mid, ofGetHeight()/2);

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(5, 6);
    addEdge(6, 7);
    addEdge(7, 0);


}

void Graph::addNode(int x, int y){
    Node *node = new Node(size, x, y);
    size++;
    nodes.push_back(node);
    adj.push_back(vector<int>());
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
    vector<int> stack;
    stack.push_back(0);
    vector<int> visited(size, false);
    visited[0] = true;
    float dotSum;

    while(stack.size() > 0){
        int id = stack.back();
        stack.pop_back();
        dotSum = 0;
        Node node = *(nodes[id]);

        for(int i=0; i<adj[id].size(); i++){
            int adjId = adj[id][i];
//            if this edge was not yet traversed and it's not a new edge
            if(!visited[adjId] && adjId < visited.size()){
                stack.push_back(adjId);
                visited[adjId] = true;

                Node adjNode = *(nodes[adjId]);
                float dist = glm::distance(node.pos, adjNode.pos);
//                split the edge in two
                if(dist > MAX_ADJ_DIST){
                    glm::vec2 newPos = (node.pos + adjNode.pos) / 2;
                    addNode(newPos.x, newPos.y);
                    splitEdge(id, adjId, size-1);
                }
            }
            if(i > 0){
                glm::vec2 v1 = (*nodes[adj[id][i-1]]).pos-(*nodes[id]).pos;
                glm::vec2 v2 = (*nodes[adj[id][i]]).pos-(*nodes[id]).pos;
                float dot = glm::dot(v1, v2)/(glm::length(v1)*glm::length(v2));
                dotSum += MAX(dot, 0);
            }
        }
        if(adj[id].size()>0 && dotSum > 0 && ofRandom(CURVE_SPLIT) < dotSum/adj[id].size()){
            Node adjNode = *(nodes[adj[id][0]]);
            if(glm::distance(node.pos, adjNode.pos) > MIN_SPLIT_DIST){
                glm::vec2 newPos = (node.pos + adjNode.pos) / 2;
                addNode(newPos.x, newPos.y);
                splitEdge(id, adj[id][0], size-1);
            }
        }
        
        if(ofRandom(1) < RANDOM_EDGE){
            Node adjNode = *(nodes[adj[id][0]]);
            glm::vec2 newPos = (node.pos + adjNode.pos) / 2;
            addNode(newPos.x, newPos.y);
            splitEdge(id, adj[id][0], size-1);
        }
    }
}

void Graph::splitEdge(int n1, int n2, int newNode){
    if(find(adj[n1].begin(), adj[n1].end(), n2) != adj[n1].end())
        adj[n1].erase(find(adj[n1].begin(), adj[n1].end(), n2));
    
    if(find(adj[n2].begin(), adj[n2].end(), n1) != adj[n2].end())
        adj[n2].erase(find(adj[n2].begin(), adj[n2].end(), n1));
    
    adj[newNode].push_back(n1);
    adj[newNode].push_back(n2);
    
    adj[n1].push_back(newNode);
    adj[n2].push_back(newNode);
    
}

void Graph::repulse(){
    float d;

    for(int i=0; i<nodes.size(); i++){
        for(int j=0; j<nodes.size(); j++){
            if(i != j){
                d = glm::distance((*nodes[i]).pos, (*nodes[j]).pos);
//                replace this with kd-tree
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
    vector<int> stack;
    stack.push_back(0);
    vector<int> visited(size, false);
    visited[0] = true;

    while(stack.size() > 0){
        int id = stack.back();
        stack.pop_back();
//        ofDrawCircle((*nodes[id]).pos, 1);

        for(int i=0; i<adj[id].size(); i++){
            int adjId = adj[id][i];
            if(!visited[adjId]){
                stack.push_back(adjId);
                visited[adjId] = true;

                ofDrawLine((*nodes[id]).pos, (*nodes[adjId]).pos);
                
            }
        }
    }

}

void Graph::update(){
    attract();
    repulse();
    move();
    split();
}

void Graph::print(){
    for(int i=0; i<nodes.size(); i++){
        (*nodes[i]).print();
    }

}
