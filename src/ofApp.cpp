#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    graph = Graph();
    
    
    graph.addNode(100, ofGetHeight()/2);
    graph.addNode(ofGetWidth()-100, ofGetHeight()/2-1);
    
    graph.addEdge(0, 1);
    
    
//    for(int i=1; i<2; i++){
//        graph.addNode(100+i*50, 100+i*10);
//        graph.addEdge(i, i-1);
//    }

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
