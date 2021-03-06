#pragma once

#include "ofMain.h"
class ofxSprite {
public:
    
    ofxSprite();
    
    void draw(float x, float y);
    void draw(ofVec2f v);
    void draw();
    
    void setAnchorPercent(float xPct, float yPct);
    void setFrameRate(int frameRate);
    void setSpeed(float speed);
    void setProgress(float pct);
    void addFile(string filename);
    void setCurrentFrame(float frame);
    void setLoop(bool loop);
    void setPalindrome(bool palindrome);
    void nextFrame();
    void previousFrame();
    void center();
    
    void play();
    void pause();
    void stop();
    void update();
    
    float getProgress(); // 0..1
    int getTotalFrames();
    int getCurrentFrame();
    bool getIsPlaying();
    float getWidth();
    float getHeight();

    ofImage& getImageAtFrame(int frame);
    ofImage& getCurrentImage();
    ofRectangle getBounds();
    ofVec2f getSize();
    
    bool getIsLoaded();
    void loadImages();
    void unloadImages();
    
    bool visible;
    
private:
    int totalFrames;
    int frameRate;
    bool loop;
    bool palindrome;
    float speed;
    float pos;
    int currentFrame;
    bool isPlaying;
    bool isLoaded;
    ofPoint anchorPoint;
    vector<string> files;
    vector<ofPixels> images;
    ofTexture texture;
};
