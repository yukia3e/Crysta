#pragma once

#include "ofMain.h"
#include "SongInfoSet.h"
#include "ITunesLibrary.h"
#include "GracenoteLibrary.h"
#include "SpotifyLibrary.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    bool saveSongFile();
    bool readSongFile();
    void mapSetting();
    void editCrystalInfo();
    void editCrystalInfo2();
    void editCrystalInfoYear();
    void editCrystalInfoYear2();
    
    int meshDrawMode;
    
    int rotateMode;
    int yAngle;
    
    int yearMode;
    
    int apiMode;
    
    vector<SongInfoSet> infoSet;
    
    const string resultDir = "result/";
    const string resultFileName = "result.xml";
    
    bool firstFlg;
    bool loadWindowFlg;
    bool finishFlg;
    
    map<string, ofVec2f> moodMap;
    map<string, int> depthMap;
    
    ofTrueTypeFont font;
    ofBoxPrimitive box;
    ofEasyCam cam;
    ofLight light;
    ofMesh mesh;
    int w, h, d;
    
    const int size = 3;
    const int cameraDistance = 400;
    const int boxColor = 64;
    //    const int boxColor = 255;
    
    int minYear;
    int maxYear;
    int processingYear;
};
