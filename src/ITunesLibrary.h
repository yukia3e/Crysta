//
//  ITunesLibrary.h
//  mu_jewel
//
//  Created by yuki. on 2015/08/19.
//
//

#ifndef __mu_jewel__ITunesLibrary__
#define __mu_jewel__ITunesLibrary__

#include "ofMain.h"
#include "SongInfoSet.h"

class ITunesLibrary {
    
    public:
        // コンストラクタ
        ITunesLibrary();

        // iTunes Music Library.xmlの配置パス
        void setXmlPath(string _xmlPath);
        string getXmlPath();

        // SongInfoSet取得処理
        vector<SongInfoSet> getITLInfoSet();

    private:
        string xmlPath;
        vector<SongInfoSet> infoSet;
};
#endif /* defined(__mu_jewel__ITunesLibrary__) */
