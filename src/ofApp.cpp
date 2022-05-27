#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();

    gui.add(MIN_DIST.setup("MIN_DIST", 100, 10, 300));
    gui.add(MAX_ADJ_DIST.setup("MAX_ADJ_DIST", 80, 10, 300));
    gui.add(CURVE_SPLIT.setup("CURVE_SPLIT", 10, 1, 20));
    gui.add(RANDOM_EDGE.setup("RANDOM_EDGE", 0.01, 0.001, 0.1));
    gui.add(MIN_SPLIT_DIST.setup("MIN_SPLIT_DIST", 2, 2, 20));
    gui.add(RAYMARCHING.setup("RAYMARCHING", false));
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    shader.load("shaders/simple");
    
    ofSetBackgroundAuto(false);
    ofSetColor(255, 30);
    ofBackground(0);
    
    
    graph = Graph();
    graph.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    graph.MIN_DIST = MIN_DIST;
    graph.MAX_ADJ_DIST = MAX_ADJ_DIST;
    graph.CURVE_SPLIT = CURVE_SPLIT;
    graph.RANDOM_EDGE = RANDOM_EDGE;
    graph.MIN_SPLIT_DIST = MIN_SPLIT_DIST;
    
    if(RAYMARCHING)
        shader.load("shaders/raymarching");
    else
        shader.load("shaders/simple");
    
    graph.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    draw the graph into the depth buffer
    fbo.begin();
    graph.draw();
    fbo.end();
    
        
    shader.begin();
    shader.setUniformTexture("depth", fbo.getTexture(), 0);
    shader.setUniform1f("width", ofGetWidth());
    shader.setUniform1f("height", ofGetHeight());
    shader.setUniform1f("mouseX", mouseX);
    shader.setUniform1f("mouseY", mouseY);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    
    gui.draw();
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
