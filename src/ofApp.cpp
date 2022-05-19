#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofSetColor(255, 10);
    ofBackground(20);
    
    graph = Graph();
    
//    LINE
//    graph.addNode(100, ofGetHeight()/2);
//    graph.addNode(ofGetWidth()-100, ofGetHeight()/2-1);
//
//    graph.addEdge(0, 1);
    
    
//  TRIANGLE
//    graph.addNode(ofGetWidth()/2, ofGetHeight()/2-100);
//    graph.addNode(ofGetWidth()/2+100, ofGetHeight()/2+100);
//    graph.addNode(ofGetWidth()/2-100, ofGetHeight()/2+100);
//
//    graph.addEdge(0, 1);
//    graph.addEdge(1, 2);
//    graph.addEdge(2, 0);
    
//    RANDOM
    graph.addNode(100, ofGetHeight()/2);
    for(int i=1; i<10; i++){
        graph.addNode(ofRandomWidth(), ofRandomHeight());
        graph.addEdge(i, i-1);
    }
    
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 9);

    graph.print();
}

//--------------------------------------------------------------
void ofApp::update(){
    graph.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    graph.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        ofBackground(20);
        
        graph = Graph();
        graph.addNode(100, ofGetHeight()/2);
        for(int i=1; i<10; i++){
            graph.addNode(ofRandomWidth(), ofRandomHeight());
            graph.addEdge(i, i-1);
        }
        
        graph.addEdge(0, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 9);

        graph.print();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
