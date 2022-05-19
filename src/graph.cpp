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
//    visited.push_back(false);
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

    while(stack.size() > 0){
        int id = stack.back();
        stack.pop_back();

        for(int i=0; i<adj[id].size(); i++){
            int adjId = adj[id][i];
//            if this edge was not yet traversed and it's not a new edge
            if(!visited[adjId] && adjId < visited.size()){
                stack.push_back(adjId);
                visited[adjId] = true;

                Node node = *(nodes[id]);
                Node adjNode = *(nodes[adjId]);
                float dist = glm::distance(node.pos, adjNode.pos);
                if(dist > MAX_ADJ_DIST){
                    glm::vec2 newPos = (node.pos + adjNode.pos) / 2;
                    addNode(newPos.x, newPos.y);
                    splitEdge(id, adjId, size-1);
                }
            }
        }
    }
    
//    clearVisited();

}

void Graph::clearVisited(){
    for(int i=0; i<visited.size();i++){
        visited[i] = false;
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
        (*nodes[id]).draw();

        for(int i=0; i<adj[id].size(); i++){
            int adjId = adj[id][i];
            if(!visited[adjId]){
                stack.push_back(adjId);
                visited[adjId] = true;

                ofDrawLine((*nodes[id]).pos, (*nodes[adjId]).pos);
                
            }
        }
    }
    
//    clearVisited();

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

