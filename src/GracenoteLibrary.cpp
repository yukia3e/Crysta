//
//  GracenoteLibrary.cpp
//  mu_jewel
//
//  Created by yuki. on 2015/08/19.
//
//

#include "GracenoteLibrary.h"

// コンストラクタ
GracenoteLibrary::GracenoteLibrary() {
    
}

// ---------- Gracenote情報取得 ----------
vector<SongInfoSet> GracenoteLibrary::getGNInfo(vector<SongInfoSet> _infoSet) {
    
    // infoSetを参照・内部保持
    infoSet = _infoSet;

    // gracenoteユーザー情報を取得
    getGNUserId();
    
    // 楽曲情報を取得
    for (loopCount = 0; loopCount < infoSet.size(); loopCount++) {
        getSongInfo();
    }
    httpUtils.stop();
    
    return infoSet;
}

// ---------- ユーザーID情報取得 ----------
void GracenoteLibrary::getGNUserId() {
    ofAddListener(httpUtils.newResponseEvent,this,&GracenoteLibrary::responseUserId);
    httpUtils.start();
    
    string clientId = clientId_prefix + clientId_div + clientId_postfix;
    const string &request
        = "<QUERIES>"
            "<QUERY CMD=\"REGISTER\">"
                "<CLIENT>"
                    + clientId +
                "</CLIENT>"
            "</QUERY>"
          "</QUERIES>";
    
    ofxHttpResponse response = httpUtils.postData(action_url, request, "text/xml");
}

// ---------- ユーザーID情報取得 レスポンスキャッチャー ----------
void GracenoteLibrary::responseUserId(ofxHttpResponse & response){

    /** ********** デバッグ用（レスポンス内容出力） start ************** **/
//    responseStr = (string)response.responseBody;
//    cout << responseStr;
    /** ********** デバッグ用（レスポンス内容出力） end   ************** **/
    
    ofXml xml;
    if(xml.loadFromBuffer(response.responseBody)) {
        userId = xml.getValue("RESPONSE/USER");
    }
    httpUtils.stop();
    httpUtils.newResponseEvent.clear();
}

// ---------- 楽曲情報取得 ----------
void GracenoteLibrary::getSongInfo() {
    ofAddListener(httpUtils.newResponseEvent,this,&GracenoteLibrary::responseSongInfo);
    httpUtils.start();
    
    string clientId = clientId_prefix + clientId_div + clientId_postfix;
    const string &request
    = "<QUERIES>"
        "<AUTH>"
            "<CLIENT>7282944-634C831B1EB5F8BCC4C701DAA678CE9D</CLIENT>"
            "<USER>" + userId + "</USER>"
        "</AUTH>"
        "<LANG>jpn</LANG>"
        "<QUERY CMD=\"ALBUM_SEARCH\">"
            "<MODE>SINGLE_BEST</MODE>"
            "<OPTION>"
                "<PARAMETER>SELECT_EXTENDED</PARAMETER>"
                "<VALUE>MOOD</VALUE>"
            "</OPTION>"
            "<OPTION>"
                "<PARAMETER>SELECT_DETAIL</PARAMETER>"
                "<VALUE>GENRE:3LEVEL,MOOD:2LEVEL</VALUE>"
            "</OPTION>"
            "<TEXT TYPE=\"ARTIST\">" + infoSet[loopCount].getArtistName() + "</TEXT>"
            "<TEXT TYPE=\"ALBUM_TITLE\">" + infoSet[loopCount].getAlbumName() + "</TEXT>"
            "<TEXT TYPE=\"TRACK_TITLE\">" + infoSet[loopCount].getTrackName() + "</TEXT>"
        "</QUERY>"
    "</QUERIES>";
    
    ofxHttpResponse response = httpUtils.postData(action_url, request, "text/xml");
}

// 楽曲情報取得 レスポンスキャッチャー
void GracenoteLibrary::responseSongInfo(ofxHttpResponse & response){
    /** ********** デバッグ用（レスポンス内容出力） start ************** **/
//    responseStr = (string)response.responseBody;
//    cout << responseStr;
    /** ********** デバッグ用（レスポンス内容出力） end ************** **/
    
    ofXml xml;
    if(xml.loadFromBuffer(response.responseBody)) {
        
        /** ********** デバッグ用（xml移動情報出力） start ************** **/
//        cout << xml.getName();
//        cout << xml.getNumChildren();
//        cout << xml.setTo("RESPONSE");
//        cout << xml.getName();
//        cout << xml.getNumChildren();
//        cout << xml.setTo("ALBUM");
//        cout << xml.getName();
//        cout << xml.getNumChildren();
//        cout << xml.setTo("TRACK");
//        cout << xml.getName();
//        cout << xml.getNumChildren();
//        cout << xml.setTo("MOOD[1][@ORD]");
//        cout << xml.getName();
//        cout << xml.getNumChildren();
        /** ********** デバッグ用（xml移動情報出力） end ************** **/

        xml.setTo("RESPONSE/ALBUM");

        // ジャンル情報取得
        xml.setToChild(5);
        infoSet[loopCount].setGenre(xml.getValue());
        xml.setToParent();
        
        // ムード情報取得
        xml.setTo("TRACK");
        xml.setToChild(3);
        infoSet[loopCount].setMood(xml.getValue());
        xml.setToSibling();
        infoSet[loopCount].setSubMood(xml.getValue());
    }
    httpUtils.newResponseEvent.clear();
}


