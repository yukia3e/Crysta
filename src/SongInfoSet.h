//
//  SongInfoSet.h
//  mu_jewel
//
//  Created by yuki. on 2015/08/19.
//
//

#ifndef __mu_jewel__SongInfoSet__
#define __mu_jewel__SongInfoSet__

#include "ofMain.h"

class SongInfoSet {

    public:
        // コンストラクタ
        SongInfoSet();

        // トラック名
        void setTrackName(string _trackName);
        string getTrackName();

        // アーティスト名
        void setArtistName(string _artistName);
        string getArtistName();

        // アルバム名
        void setAlbumName(string _albumName);
        string getAlbumName();

        // 楽曲追加日
        void setAddedDate(string _addedDate);
        string getAddedDate();
    
        // 楽曲再生日
        void setPlayDate(string _playDate);
        string getPlayDate();
    
        // ムード情報
        void setMood(string _mood);
        string getMood();
    
        // サブムード情報
        void setSubMood(string _subMood);
        string getSubMood();
    
        // ジャンル情報
        void setGenre(string _genre);
        string getGenre();
    
        // 座標情報
        void setPoint(ofPoint _point);
        ofPoint getPoint();
    
        // 楽曲年
        void setSongYear(int _year);
        int getSongYear();
    
        // カラー情報
        void setColor(ofFloatColor _color);
        ofFloatColor getColor();
    
        // 文字型日時 -> 日付型日時
        time_t convertStringToTime(string stringDate);
    
        // トラック名
        string trackName;
    
        // アーティスト名
        string artistName;

        // アルバム名
        string albumName;

        // 追加日
        string addedDate;
    
        // 再生日
        string playDate;

        // ムード Lv.1
        string mood;
    
        // ムード Lv.2
        string sub_mood;

        // ムード Lv.2
        string genre;
    
        // 座標情報
        ofPoint point;
    
        // カラー情報
        ofFloatColor color;
    
        // 楽曲年
        int songYear;

};

#endif /* defined(__mu_jewel__SongInfoSet__) */
