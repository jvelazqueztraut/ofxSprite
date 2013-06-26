#include "ofxSprite.h"

ofxSprite::ofxSprite() {
    isLoaded=false;
    isPlaying = false;
    totalFrames = 0;
    speed = 1;
    pos = 0;
    currentFrame = 0;
    palindrome = false;
    loop = true;
    visible = true;
    frameRate = 20;
}

void ofxSprite::addFile(string filename) {
    files.push_back(filename);
    totalFrames = files.size();
    if(isLoaded){
        ofPixels img;
        ofLoadImage(img,filename);
        images.push_back(img);
        if(!texture.isAllocated()){
            texture.allocate(images.back());
            texture.loadData(images[currentFrame]);
        }
    }
    else{
        images.assign(totalFrames,ofPixels());
    }
}

void ofxSprite::loadImages() {
    for(int i=0;i<totalFrames;i++){
        ofLoadImage(images[i],files[i]);
        if(!texture.isAllocated()){
            texture.allocate(images[i]);
            texture.loadData(images[currentFrame]);
        }
    }
    isLoaded=true;
}

void ofxSprite::unloadImages(){
    isLoaded=false;
    images.clear();
    images.assign(totalFrames,ofPixels());
    texture.clear();
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
    if(pos<0 || pos>=totalFrames){
        if(palindrome) {
            speed = -speed;
            if(totalFrames>1){
                if (pos<0)                  pos = 1;
                else if (pos>=totalFrames)  pos=totalFrames-2;
            }
            else{
                if (pos<0)                  pos = 0;
                else if (pos>=totalFrames)  pos=totalFrames-1;
            }
        }
        else{
            if (pos<0)                  pos+= totalFrames;
            else if (pos>=totalFrames)  pos-= totalFrames;
        }
        
        isPlaying = loop;
    }
    if((int)pos != currentFrame){
        currentFrame=pos;
        if(isLoaded)
            texture.loadData(images[currentFrame]);
    }
}

float ofxSprite::getProgress() {
    return pos / (totalFrames-1);
}

void ofxSprite::setLoop(bool loop) {
    this->loop = loop;
}

void ofxSprite::setPalindrome(bool palindrome) {
    this->palindrome = palindrome;
}

void ofxSprite::update() {
    if (!isPlaying) return;
    
    setCurrentFrame(pos + speed * frameRate / ofGetFrameRate());
}

int ofxSprite::getCurrentFrame() {
    return currentFrame;
}

void ofxSprite::previousFrame() {
    setCurrentFrame(pos-1);
}

void ofxSprite::nextFrame() {
    setCurrentFrame(pos+1);
}

void ofxSprite::setAnchorPercent(float xPct, float yPct) {
    texture.setAnchorPercent(xPct,yPct);
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

bool ofxSprite::getIsLoaded() {
    return isLoaded;
}

float ofxSprite::getWidth() {
    return images[0].getWidth();
}

float ofxSprite::getHeight() {
    return images[0].getHeight();
}

void ofxSprite::draw() {
    draw(0,0);
}

void ofxSprite::draw(ofVec2f v) {
    draw(v.x,v.y);
}

void ofxSprite::draw(float x, float y) {
    if (isLoaded && visible)
        texture.draw(ofPoint(x,y)-anchorPoint);
}
