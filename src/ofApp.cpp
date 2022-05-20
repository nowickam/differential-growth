#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    shader.load("shaders/simple");
    
    ofSetBackgroundAuto(false);
    ofSetColor(255, 25);
    ofBackground(0);
    
    graph = Graph();
    graph.init();
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
        fbo.begin();
        ofClear(0,0,0,255);
        fbo.end();
        
        graph = Graph();
        graph.init();
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
