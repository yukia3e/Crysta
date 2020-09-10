#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofHideCursor();
    
    ofSetVerticalSync(true);
    ofSetFrameRate(40);
    
    ofBackground(0);
    
    ofSetCircleResolution(60);
    ofEnableAlphaBlending();
    
    mapSetting();
    
    loadWindowFlg = true;
    
    firstFlg = false;
    finishFlg = false;
    
    meshDrawMode = 0;
    rotateMode = 0;
    yAngle = 0;
    apiMode = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

    if (firstFlg) {
        ofFile resultFile;
        
        if (!resultFile.doesFileExist(resultDir + resultFileName, true)) {
            auto *ITLibrary = new ITunesLibrary();
            infoSet = ITLibrary->getITLInfoSet();
            
            for (int i = 0; i < infoSet.size(); i++) {
                string strYear = infoSet[i].getAddedDate();
                
                if (strYear != "") {
                    istringstream is(infoSet[i].getAddedDate().substr(0, 4));
                    int intYear = 0;
                    is >> intYear;
                    
                    infoSet[i].setSongYear(intYear);
                    if (intYear < minYear || minYear == 0) {
                        minYear = intYear;
                    }
                    if (intYear > maxYear || maxYear == 0) {
                        maxYear = intYear;
                    }
                }
            }
            
            GracenoteLibrary gnLibrary;
            infoSet = gnLibrary.getGNInfo(infoSet);

            editCrystalInfo();
            
            saveSongFile();
        } else {
            int apiMode = 1;
            
            readSongFile();
            editCrystalInfo2();
        }
        
        finishFlg = true;
    }
}

void ofApp::editCrystalInfo() {
    
    w = ofGetWidth() / size;
    h = ofGetWidth() / size;
    d = ofGetWidth() / size;
    
    mesh.clearVertices();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    for (int i = 0; i < infoSet.size(); i++) {
        
        ofVec2f keisu = moodMap[infoSet[i].getMood()];
        int depth = depthMap[infoSet[i].getSubMood()];
        
        int rectWidthHalf = w / 5 / 2;
        int rectHeightHalf = h / 5 / 2;
        int rectDepthHalf = d / 4 / 2;
        
        int x = rectWidthHalf * keisu.x + ofRandom(-(rectWidthHalf), rectWidthHalf);
        int y = rectHeightHalf * keisu.y + ofRandom(-(rectHeightHalf), rectHeightHalf);
        int z = rectDepthHalf * depth + ofRandom(-(rectDepthHalf), rectDepthHalf);
        
        infoSet[i].setPoint(ofPoint(x, y, z));
        
        float alpha = 0.7;
        float r = ofMap(infoSet[i].getPoint().x, 0, w, 0.2, 1.0);
        float g = ofMap(infoSet[i].getPoint().y, 0, h, 0.2, 1.0);
        float b = ofMap(infoSet[i].getPoint().z, 0, d, 0.2, 1.0);
        
        mesh.addVertex(infoSet[i].getPoint());
        infoSet[i].setColor(ofFloatColor(r, g, b, alpha));
        mesh.addColor(ofFloatColor(r, g, b, alpha));
    }
    
    mesh.setupIndicesAuto();
}

void ofApp::editCrystalInfo2() {
    
    w = ofGetWidth() / size;
    h = ofGetWidth() / size;
    d = ofGetWidth() / size;
    
    mesh.clearVertices();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    for (int i = 0; i < infoSet.size(); i++) {
        
        mesh.addVertex(infoSet[i].getPoint());
        mesh.addColor(infoSet[i].getColor());
    }
    
    mesh.setupIndicesAuto();
}

bool ofApp::saveSongFile() {
    
    ofXml tmp;
    tmp.addChild("songs");
    for (int i = 0; i < infoSet.size(); i++) {
        tmp.setTo("songs");
        stringstream ss;
        ss << i;
        tmp.addChild("song");
        tmp.setToChild(i);
        ss.clear();
        tmp.addValue("trackName", infoSet[i].getTrackName());
        tmp.addValue("artistName", infoSet[i].getArtistName());
        tmp.addValue("albumName", infoSet[i].getAlbumName());
        tmp.addValue("songYear", infoSet[i].getSongYear());
        tmp.addValue("mood", infoSet[i].getMood());
        tmp.addValue("sub_mood", infoSet[i].getSubMood());
        tmp.addValue("x", infoSet[i].getPoint().x);
        tmp.addValue("y", infoSet[i].getPoint().y);
        tmp.addValue("z", infoSet[i].getPoint().z);
        tmp.addValue("r", infoSet[i].getColor().r);
        tmp.addValue("g", infoSet[i].getColor().g);
        tmp.addValue("b", infoSet[i].getColor().b);
        tmp.addValue("a", infoSet[i].getColor().a);
        tmp.setToParent();
    }
    tmp.save("result/result.xml");
    
    ofXml tmp2;
    tmp2.addChild("songs");
    for (int i = 0; i < infoSet.size(); i++) {
        tmp2.setTo("songs");
        stringstream ss;
        ss << i;
        tmp2.addChild("song");
        tmp2.setToChild(i);
        ss.clear();
        tmp2.addValue("x", infoSet[i].getPoint().x);
        tmp2.addValue("y", infoSet[i].getPoint().y);
        tmp2.addValue("z", infoSet[i].getPoint().z);
        tmp2.addValue("r", infoSet[i].getColor().r);
        tmp2.addValue("g", infoSet[i].getColor().g);
        tmp2.addValue("b", infoSet[i].getColor().b);
        tmp2.addValue("a", infoSet[i].getColor().a);
        tmp2.setToParent();
    }
    tmp2.save("result/for_iPhone.xml");
}

bool ofApp::readSongFile() {
    ofXml tmp;
    tmp.load("result/result.xml");
    int i = 0;
    tmp.setTo("songs");
    vector<SongInfoSet> _infoSet;
    
    tmp.setToChild(0);
    
    do {
        SongInfoSet set;
        
        // TrackName
        tmp.setToChild(0);
        set.setTrackName(tmp.getValue());
        
        // ArtistName
        tmp.setToSibling();
        set.setArtistName(tmp.getValue());
        
        // AlbumName
        tmp.setToSibling();
        set.setAlbumName(tmp.getValue());
        
        // songYear
        tmp.setToSibling();
        istringstream isYear(tmp.getValue().substr(0, tmp.getValue().length()));
        int songYear;
        isYear >> songYear;
        set.setSongYear(songYear);
        if (songYear < minYear || minYear == 0) {
            minYear = songYear;
        }
        if (songYear > maxYear || maxYear == 0) {
            maxYear = songYear;
        }
        
        
        // Mood
        tmp.setToSibling();
        //        set.setMood(tmp.getValue());
        
        // Sub-Mood
        tmp.setToSibling();
        //        set.setSubMood(tmp.getValue());
        
        // x
        tmp.setToSibling();
        istringstream isx(tmp.getValue().substr(0, tmp.getValue().length()));
        int x;
        isx >> x;
        
        // y
        tmp.setToSibling();
        istringstream isy(tmp.getValue().substr(0, tmp.getValue().length()));
        int y;
        isy >> y;
        
        // z
        tmp.setToSibling();
        istringstream isz(tmp.getValue().substr(0, tmp.getValue().length()));
        int z;
        isz >> z;
        
        set.setPoint(ofPoint(x, y, z));
        
        // r
        tmp.setToSibling();
        istringstream isr(tmp.getValue().substr(0, tmp.getValue().length()));
        float r;
        isr >> r;
        
        // g
        tmp.setToSibling();
        istringstream isg(tmp.getValue().substr(0, tmp.getValue().length()));
        float g;
        isg >> g;
        
        // b
        tmp.setToSibling();
        istringstream isb(tmp.getValue().substr(0, tmp.getValue().length()));
        float b;
        isb >> b;
        //
        // a
        tmp.setToSibling();
        istringstream isa(tmp.getValue().substr(0, tmp.getValue().length()));
        float a;
        isa >> a;
        
        set.setColor(ofFloatColor(r, g, b, a));
        
        // push this set.
        infoSet.push_back(set);
        
        tmp.setToParent();
        i++;
    } while (tmp.setToSibling());
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    // ----------- „É≠„Éº„ÉâÁîªÈù¢Ë°®Á§∫ÔºàÂàùÂõû„ÅÆ„ÅøÔºâ -----------
    if (loadWindowFlg) {
        
        ofSetColor(255, 255, 255);
        font.loadFont("font/„Éí„É©„Ç≠„Çô„ÉéËßí„Ç≥„Çô ProN W3.otf", 60);
        font.drawString("- Crysta -", 100, ofGetHeight() / 2);
        font.loadFont("font/„Éí„É©„Ç≠„Çô„ÉéËßí„Ç≥„Çô ProN W3.otf", 30);
        font.drawString("Now Generating...", 130, ofGetHeight() / 2 + 60);
        
        loadWindowFlg = false;
        
        firstFlg = true;
    }
    
    if (finishFlg) {
        
        ofEnableDepthTest();
        ofEnableSmoothing();
        cam.setDistance(cameraDistance);
        
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        
        cam.begin();
        
        ofLight light;
        light.enable();
        light.setPosition(0, h * 2, 0);
        light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
        light.setAmbientColor(ofFloatColor(1.0, 1.0, 1.0));
        light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
        
        glPointSize(2.0);
        
        glEnable(GL_POINT_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        
        ofSetColor(boxColor);
        box.set(w * 3);
        box.setPosition(0, 0, 0);
        
        ofRotateY(yAngle);
        if (rotateMode == 1) {
            yAngle += 5;
            if (yAngle >= 360) {
                yAngle = 0;
            }
        }
        
        switch (meshDrawMode) {
            case 0:
                mesh.draw();
                break;
            case 1:
                mesh.drawVertices();
                break;
            case 2:
                mesh.drawWireframe();
                break;
        }
        
        light.disable();
        cam.end();
        
        firstFlg = false;
        
        ofPopMatrix();
    }
}


// crystalÊÉÖÂ†±Ë®≠ÂÆö
void ofApp::editCrystalInfoYear() {
    
    if (apiMode == 0) {
        // ÊèèÁîªÈ†òÂüü„ÅÆË®≠ÂÆö
        w = ofGetWidth() / size;
        h = ofGetWidth() / size;
        d = ofGetWidth() / size;
        
        // „É°„ÉÉ„Ç∑„É•ÊèèÁîª
        // È†ÇÁÇπ„ÅÆÂàùÊúüÂåñ
        mesh.clearVertices();
        
        // „É¢„Éº„ÉâÂ§âÊõ¥ÔºàË™øÊï¥Ë¶ÅÔºâ
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
        // Ê•ΩÊõ≤Á©∫ÈñìÊÉÖÂ†±„ÅÆÁîüÊàê„ÉªË®≠ÂÆö
        for (int i = 0; i < infoSet.size(); i++) {
            
            if (infoSet[i].getSongYear() > processingYear) {
                continue;
            }
            
            // „É†„Éº„ÉâMap„Åã„Çâ„ÅÆ‰øÇÊï∞ÂèñÂæó
            ofVec2f keisu = moodMap[infoSet[i].getMood()];
            int depth = depthMap[infoSet[i].getSubMood()];
            
            // „Éñ„É≠„ÉÉ„ÇØÊÉÖÂ†±Ôºà„Éñ„É≠„ÉÉ„ÇØ„Çª„É≥„Çø„Éº x ‰øÇÊï∞„Åß„Éó„É≠„ÉÉ„ÉàÂÖà„ÇíË®≠ÂÆöÔºâ
            int rectWidthHalf = w / 5 / 2;
            int rectHeightHalf = h / 5 / 2;
            int rectDepthHalf = d / 4 / 2;
            
            // xyzË®≠ÂÆöÔºà„É©„É≥„ÉÄ„É†„ÇíÂà©Áî®„Åó„ÄÅ‰∏≠ÂøÉËª∏„ÅÆ„Éñ„É¨„ÇíÁîüÊàêÔºâ
            int x = rectWidthHalf * keisu.x + ofRandom(-(rectWidthHalf), rectWidthHalf);
            int y = rectHeightHalf * keisu.y + ofRandom(-(rectHeightHalf), rectHeightHalf);
            int z = rectDepthHalf * depth + ofRandom(-(rectDepthHalf), rectDepthHalf);
            
            // „Éù„Ç§„É≥„Éà„ÅÆ‰øùÊåÅ
            infoSet[i].setPoint(ofPoint(x, y, z));
            
            // mesh„ÅÆË®≠ÂÆöÔºàË™øÊï¥Ë¶ÅÔºâ
            float alpha = 0.7;
            float r = ofMap(infoSet[i].getPoint().x, 0, w, 0.2, 1.0);
            float g = ofMap(infoSet[i].getPoint().y, 0, h, 0.2, 1.0);
            float b = ofMap(infoSet[i].getPoint().z, 0, d, 0.2, 1.0);
            
            //        cout << w;
            //        cout << infoSet[i].getPoint().x;
            //        cout << infoSet[i].getPoint().y;
            //        cout << infoSet[i].getPoint().z;
            //        cout << r;
            //        cout << g;
            //        cout << b;
            
            // „É°„ÉÉ„Ç∑„É•„Å∏„ÅÆÈ†ÇÁÇπË®≠ÂÆö
            mesh.addVertex(infoSet[i].getPoint());
            mesh.addColor(ofFloatColor(r, g, b, alpha));
            //        mesh.addColor(ofFloatColor(0.5, 0.8, 1.0, 0.5));
            
            // „Ç§„É≥„Éá„ÉÉ„ÇØ„ÇπË®≠ÂÆö
            mesh.setupIndicesAuto();
        }
        
    } else if (apiMode == 1) {
        
        // ÊèèÁîªÈ†òÂüü„ÅÆË®≠ÂÆö
        w = ofGetWidth() / size;
        h = ofGetWidth() / size;
        d = ofGetWidth() / size;
        
        // „É°„ÉÉ„Ç∑„É•ÊèèÁîª
        // È†ÇÁÇπ„ÅÆÂàùÊúüÂåñ
        mesh.clearVertices();
        
        // „É¢„Éº„ÉâÂ§âÊõ¥ÔºàË™øÊï¥Ë¶ÅÔºâ
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
        // Ê•ΩÊõ≤Á©∫ÈñìÊÉÖÂ†±„ÅÆÁîüÊàê„ÉªË®≠ÂÆö
        for (int i = 0; i < infoSet.size(); i++) {
            
            if (infoSet[i].getSongYear() >= minYear) {
                // „É°„ÉÉ„Ç∑„É•„Å∏„ÅÆÈ†ÇÁÇπË®≠ÂÆö
                mesh.addVertex(infoSet[i].getPoint());
                mesh.addColor(infoSet[i].getColor());
            }
        }
        
        // „Ç§„É≥„Éá„ÉÉ„ÇØ„ÇπË®≠ÂÆö
        mesh.setupIndicesAuto();
    }
}

// crystalÊÉÖÂ†±Ë®≠ÂÆö
void ofApp::editCrystalInfoYear2() {
    
    // ÊèèÁîªÈ†òÂüü„ÅÆË®≠ÂÆö
    w = ofGetWidth() / size;
    h = ofGetWidth() / size;
    d = ofGetWidth() / size;
    
    // „É°„ÉÉ„Ç∑„É•ÊèèÁîª
    // È†ÇÁÇπ„ÅÆÂàùÊúüÂåñ
    mesh.clearVertices();
    
    // „É¢„Éº„ÉâÂ§âÊõ¥ÔºàË™øÊï¥Ë¶ÅÔºâ
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    // Ê•ΩÊõ≤Á©∫ÈñìÊÉÖÂ†±„ÅÆÁîüÊàê„ÉªË®≠ÂÆö
    for (int i = 0; i < infoSet.size(); i++) {
        
        // „É°„ÉÉ„Ç∑„É•„Å∏„ÅÆÈ†ÇÁÇπË®≠ÂÆö
        mesh.addVertex(infoSet[i].getPoint());
        mesh.addColor(infoSet[i].getColor());
    }
    
    // „Ç§„É≥„Éá„ÉÉ„ÇØ„ÇπË®≠ÂÆö
    mesh.setupIndicesAuto();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
