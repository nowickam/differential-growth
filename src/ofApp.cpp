#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    shader.load("shaders/raymarching");
    
    ofSetBackgroundAuto(false);
    ofSetColor(255, 10);
    ofBackground(0);
    
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
        graph.addNode(ofClamp(ofRandomWidth(), MARGIN, ofGetWidth()-MARGIN),
                      ofClamp(ofRandomHeight(), MARGIN, ofGetHeight()-MARGIN));
        graph.addEdge(i, i-1);
    }
    
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 9);

//    graph.print();
}

//--------------------------------------------------------------
void ofApp::update(){
    graph.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    draw the graph into the depth buffer
    fbo.begin();
//    ofDrawCircle(0, 0, 100);
    graph.draw();
    fbo.end();
    
    shader.begin();
    shader.setUniformTexture("depth", fbo.getTexture(), 0);
    shader.setUniform1f("width", ofGetWidth());
    shader.setUniform1f("height", ofGetHeight());
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();

//    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        ofBackground(0);
        
        graph = Graph();
        graph.addNode(100, ofGetHeight()/2);
        for(int i=1; i<10; i++){
            graph.addNode(ofClamp(ofRandomWidth(), MARGIN, ofGetWidth()-MARGIN),
                          ofClamp(ofRandomHeight(), MARGIN, ofGetHeight()-MARGIN));
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
