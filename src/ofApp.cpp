#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    camWidth 		= 1280/2 ;	// try to grab at this size.
    camHeight 		= 720/2;
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    img.load("/Users/admin/Downloads/colorful-iguana-tessa-fairey.jpg");
    ofVboMesh tMesh;
    tMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    tMesh.setUsage(GL_DYNAMIC_DRAW);
    for(int j = 0; j < SEG_COUNT; j++)
    {
        tMesh.addVertex(ofVec2f(0,0));
    }
    
    for(int i = 0; i < LINE_COUNT; i++)
    {
        mMesh[i] = ofVboMesh(tMesh);
    }
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    videoTexture.allocate(camWidth,camHeight, GL_RGB);
    ofSetVerticalSync(true);
    
//    camWidth =  img.getWidth();
//    camHeight =  img.getHeight();

    sketchWidth = ofGetWidth();
    sketchHeight= ofGetHeight();
}


//--------------------------------------------------------------
void testApp::update()
{
    vidGrabber.update();
    double tm = ofGetElapsedTimef();
    

    
    if (vidGrabber.isFrameNew())
    {
        unsigned char * pixels = vidGrabber.getPixels();
//        unsigned char * pixels = img.getPixels();
        float lineMaxAmp = 6.f;
        float maxLineFreq =2.7;
        for(int i = 0; i < LINE_COUNT; i++)
        {
            float yNorm = i*1.f/(LINE_COUNT);
            int colorIndex = i % 3;
            int currentLineIndex = i;
            float tVal = 0.f;
            for(int j = 0; j < SEG_COUNT; j++)
            {
                float xNorm = j*1.f/(SEG_COUNT);
                
                int camIndex = (int)((int)(yNorm*camHeight+1) *camWidth*3 - xNorm*camWidth*3);
                float brightnessNorm = pixels[camIndex+colorIndex]/255.0;//(pixels[camIndex]+pixels[camIndex+1]+pixels[camIndex+2])/(255.f*3.f);
                tVal += pow((brightnessNorm*maxLineFreq),2);
                mMesh[currentLineIndex].setVertex(j, ofVec2f(j*sketchWidth/(SEG_COUNT-1.f),
                                                             i*sketchHeight/(LINE_COUNT-1.f) +lineMaxAmp*sin(tm+tVal)));
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(20,20,20);
    ofEnableSmoothing();
    ofGetCurrentRenderer()->setFillMode(OF_OUTLINE);
    ofGetCurrentRenderer()->setLineSmoothing(true);

    //	vidGrabber.draw(0,0);
    //videoTexture.draw(20+camWidth,20,camWidth,camHeight);
//    ofTranslate(ofPoint(0,0,-1500));
//    ofScale(2,1);
    for(int i = 0; i < LINE_COUNT; i++)
    {
        int colorIndex = i % 3;
        switch (colorIndex) {
            case 0:
                ofSetColor(255,0,0,200);
                break;
            case 1:
                ofSetColor(0,255,0,200);
                break;
            case 2:
                ofSetColor(0,0,255,200);
                break;
            default:
                break;
        }
        mMesh[i].draw();
    }
    
    // in draw:
    char fpsStr[255]; // an array of chars
    sprintf(fpsStr, "frame rate: %.2f", ofGetFrameRate());
    ofSetColor(0,0,0,0);
    ofDrawBitmapString(fpsStr, 40,50);
    ofSetColor(255,255,255,255);
    ofDrawBitmapString(fpsStr, 45,55);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    
    // in fullscreen mode, on a pc at least, the
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...
    
    // Video settings no longer works in 10.7
    // You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343
    if (key == 's' || key == 'S'){
        vidGrabber.videoSettings();
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}
