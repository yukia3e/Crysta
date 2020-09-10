//
//  GracenoteLibrary.h
//  mu_jewel
//
//  Created by yuki. on 2015/08/19.
//
//

#ifndef __mu_jewel__GracenoteLibrary__
#define __mu_jewel__GracenoteLibrary__

#include "ofMain.h"
#include "SongInfoSet.h"
#include "ofxHttpTypes.h"
#include "ofxHttpUtils.h"

class GracenoteLibrary {
    
public:
    // コンストラクタ
    GracenoteLibrary();
    
    // Gracenote情報取得
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
    // -------------------------- gracenoteアクセス用情報 --------------------------
    // set your clientId
    const string clientId_prefix = "";
    const string clientId_div = "-";
    const string clientId_postfix = "";
    const string clientId = clientId_prefix + clientId_div + clientId_postfix;
    
    const string action_url = "https://" + clientId_prefix + ".web.cddbp.net/webapi/xml/1.0/";

    // -------------------------- gracenoteアクセス用情報 --------------------------
    vector<SongInfoSet> infoSet;
    string userId;

    ofxHttpUtils httpUtils;
    string requestStr;
    string responseStr;
    
    // -------------------------- ループカウンタ --------------------------
    int loopCount;
};

#endif /* defined(__mu_jewel__GracenoteLibrary__) */
