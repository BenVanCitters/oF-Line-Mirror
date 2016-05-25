#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    camWidth 		= 1280 ;	// try to grab at this size.
    camHeight 		= 720;
    
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
}


//--------------------------------------------------------------
void testApp::update()
{
    vidGrabber.update();
    double tm = 0;//ofGetElapsedTimef();
    
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    if (vidGrabber.isFrameNew())
    {
        unsigned char * pixels = vidGrabber.getPixels();
//        unsigned char * pixels = img.getPixels();
        float lineMaxAmp = 6.f;
        double maxLineFreq =2.0;
        for(int i = 0; i < LINE_COUNT; i++)
        {
            float yNorm = i*1.f/(LINE_COUNT);
            int colorIndex = i % 3;
            int currentLineIndex = i;
            double tVal = 0.f;
            for(int j = 0; j < SEG_COUNT; j++)
            {
                float xNorm = j*1.f/(SEG_COUNT);
                
                int camIndex = (int)((int)(yNorm*camHeight+1) *camWidth*3 - xNorm*camWidth*3);
                double brightnessNorm = pixels[camIndex+colorIndex]/255.0;//(pixels[camIndex]+pixels[camIndex+1]+pixels[camIndex+2])/(255.f*3.f);
                tVal += pow((brightnessNorm*maxLineFreq),2);
                mMesh[currentLineIndex].setVertex(j, ofVec2f(j*w/(SEG_COUNT-1.f),
                                              i*h/(LINE_COUNT-1.f) +lineMaxAmp*sin(tm+tVal)));
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
    float w = ofGetCurrentRenderer()->getViewportWidth();
    float h = ofGetCurrentRenderer()->getViewportHeight();
//    call glGet with arguments GL_ALIASED_LINE_WIDTH_RANGE, GL_SMOOTH_LINE_WIDTH_RANGE, and GL_SMOOTH_LINE_WIDTH_GRANULARITY.
//    glGet( GL_ALIASED_LINE_WIDTH_RANGE);
    float range[4];
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE,range);
    glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE,range);
    glGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY,range);
    ofSetLineWidth(.3);
    //	vidGrabber.draw(0,0);
    //videoTexture.draw(20+camWidth,20,camWidth,camHeight);
//    ofTranslate(ofPoint(0,0,-1500));
//    ofScale(2,1);
    for(int i = 0; i < LINE_COUNT; i++)
    {
        int colorIndex = i % 3;
        switch (colorIndex) {
            case 0:
                ofSetColor(255,0,0,255);
                break;
            case 1:
                ofSetColor(0,255,0,255);
                break;
            case 2:
                ofSetColor(0,0,255,255);
                break;
            default:
                break;
        }
//        mMesh[i].draw();
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(.125);
//ofGetCurrentRenderer()->draw
                ofGetCurrentRenderer()->draw(mMesh[i], OF_MESH_WIREFRAME);
         glGetFloatv(GL_LINE_WIDTH,range);
         glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE,range);
//        mMesh[i].draw(OF_MESH_WIREFRAME);
    }
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
