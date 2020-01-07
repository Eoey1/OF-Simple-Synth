#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int sampleRate = 44100;
    int bufferSize = 1024;
    
    ofSoundStreamSettings soundSettings;
    
    soundSettings.setOutListener(this);
    soundSettings.sampleRate = sampleRate;
    soundSettings.bufferSize = bufferSize;
    soundSettings.numOutputChannels = 2;
    soundSettings.numInputChannels = 0;
    
    soundStream.setup(soundSettings);
}

//--------------------------------------------------------------
void ofApp::update(){
    synth.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& buffer) {
    float pan = 0.5;
    
    float leftScale = 1 - pan;
    float rightScale = pan;
    
    float volume = 0.5;
    float output = 0.0;
    
    for (int i = 0; i < buffer.getNumFrames(); i++) {
        output = synth.output();
        
        buffer [i * buffer.getNumChannels()] = output * volume * leftScale;
        buffer [i * buffer.getNumChannels() + 1] = output * volume * rightScale;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    synth.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    synth.keyReleased(key);
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
