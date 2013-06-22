#include "ofxSprite.h"

ofxSprite::ofxSprite() {
    isPlaying = false;
    speed = 1;
    pos = 0;
    loop = true;
    visible = true;
    frameRate = 20;
}

void ofxSprite::load(string filename, int numFrames, int start, string id) {
    this->id = id;
    
    for (int i=start; i<numFrames+start; i++) {
        addFile(ofVAArgsToString(filename.c_str(), i));
    }
}

void ofxSprite::addFile(string filename) {
    ofImage img;
    img.loadImage(filename);
    images.push_back(img);
    totalFrames = images.size();
}

void ofxSprite::setFrameRate(int frameRate) {
    this->frameRate = frameRate;
}

void ofxSprite::setSpeed(float speed) {
    this->speed = speed;
}


int ofxSprite::getTotalFrames() {
    return totalFrames;
}

void ofxSprite::setCurrentFrame(float frame) {
    pos = frame;

    if (pos<0){
        if (loop) {
            pos += totalFrames;
        }
        else{
            stop();
        }
    }
    if (pos>=totalFrames){
        if (loop) {
            pos -= totalFrames;
        }
        else{
            pos = totalFrames-.00001f;
            isPlaying=false;
        }
    }
}

float ofxSprite::getProgress() {
    return pos / totalFrames;
}

void ofxSprite::setLoop(bool loop) {
    this->loop = loop;
}

void ofxSprite::update() {
    if (!isPlaying) return;
    
    setCurrentFrame(pos + speed * frameRate / ofGetFrameRate());
}

int ofxSprite::getCurrentFrame() {
    return (int)pos;
}

void ofxSprite::previousFrame() {
    setCurrentFrame(pos-1);
}

void ofxSprite::nextFrame() {
    setCurrentFrame(pos+1);
}

void ofxSprite::setAnchorPercent(float xPct, float yPct) {
    anchorPoint.set(xPct*getWidth(),yPct*getHeight());
}

void ofxSprite::center() {
    setAnchorPercent(.5,.5);
}

void ofxSprite::play() {
    pos = 0;
    visible = true;
    isPlaying = true;
}

void ofxSprite::stop() {
    pos = 0;
    isPlaying = false;
}

void ofxSprite::pause() {
    isPlaying = false;
}

bool ofxSprite::getIsPlaying() {
    return isPlaying;
}

float ofxSprite::getWidth() {
    return getCurrentImage().getWidth();
}

float ofxSprite::getHeight() {
    return getCurrentImage().getHeight();
}

void ofxSprite::draw() {
    draw(0,0);
}

void ofxSprite::draw(ofVec2f v) {
    draw(v.x,v.y);
}

void ofxSprite::draw(float x, float y) {
    if (!visible) return;
    getCurrentImage().draw(ofPoint(x,y)-anchorPoint);
}

ofImage& ofxSprite::getImageAtFrame(int frame) {
    if (frame<=totalFrames) return images[frame];
    else return images[0];
}

ofImage& ofxSprite::getCurrentImage() {
    return getImageAtFrame(getCurrentFrame());
}
