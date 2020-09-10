//
//  SpotifyLibrary.h
//  mu_jewel
//
//  Created by yuki. on 2015/08/19.
//
//

#ifndef __mu_jewel__SpotifyLibrary__
#define __mu_jewel__SpotifyLibrary__

#include "ofMain.h"
#include "SongInfoSet.h"
#include "ofxHttpTypes.h"
#include "ofxHttpUtils.h"

class SpotifyLibrary {
    
    // コンストラクタ
    SpotifyLibrary();
    
    // SpotifyLibrary情報取得
    vector<SongInfoSet> getGNInfo(vector<SongInfoSet> _infoSet);
    
    // ユーザーID情報取得
    void getGNUserId();
    
    // ユーザーID情報取得 レスポンスキャッチャー
    void responseUserId(ofxHttpResponse & response);
    
    // 楽曲情報取得
    void getSongInfo();
    
    // 楽曲情報取得 レスポンスキャッチャー
    void responseSongInfo(ofxHttpResponse & response);
    
private:
    // -------------------------- Spotify アクセス用情報 --------------------------
    const string clientId = "";
    const string security = "";
    
    
    // -------------------------- Spotify アクセス用情報 --------------------------
    vector<SongInfoSet> infoSet;
    string userId;
    
    ofxHttpUtils httpUtils;
    string requestStr;
    string responseStr;
    
    // -------------------------- ループカウンタ --------------------------
    int loopCount;
};

#endif /* defined(__mu_jewel__SpotifyLibrary__) */
