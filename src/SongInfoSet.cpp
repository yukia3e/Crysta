//
//  SongInfoSet.cpp
//  mu_jewel
//
//  Created by yuki. on 2015/08/19.
//
//

#include "SongInfoSet.h"

//--------------------------------------------------------------
//  コンストラクタ
//--------------------------------------------------------------
SongInfoSet::SongInfoSet() {
    trackName = "";
    artistName = "";
    albumName = "";
    addedDate = "";
    playDate = "";
    mood = "";
    sub_mood = "";
    genre = "";
    point = ofPoint(0, 0, 0);
    color = ofFloatColor(0.0, 0.0, 0.0, 0.0);
}

//--------------------------------------------------------------
//  トラック名 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setTrackName(string _trackName) {
    trackName = _trackName;
}
string SongInfoSet::getTrackName() {
    return trackName;
}

//--------------------------------------------------------------
//  アーティスト名 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setArtistName(string _artistName) {
    artistName = _artistName;
}
string SongInfoSet::getArtistName() {
    return artistName;
}

//--------------------------------------------------------------
//  アルバム名 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setAlbumName(string _albumName) {
    albumName = _albumName;
}
string SongInfoSet::getAlbumName() {
    return albumName;
}

//--------------------------------------------------------------
//  楽曲追加日 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setAddedDate(string _addedDate) {
    addedDate = _addedDate;
}
string SongInfoSet::getAddedDate() {
    return addedDate;
}

//--------------------------------------------------------------
//  ムード情報 Lv.1 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setMood(string _mood) {
    mood = _mood;
}
string SongInfoSet::getMood() {
    return mood;
}

//--------------------------------------------------------------
//  ムード情報 Lv.2 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setSubMood(string _subMood) {
    sub_mood = _subMood;
}
string SongInfoSet::getSubMood() {
    return sub_mood;
}

//--------------------------------------------------------------
//  ジャンル情報 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setGenre(string _genre) {
    genre = _genre;
}
string SongInfoSet::getGenre() {
    return genre;
}

//--------------------------------------------------------------
//  座標情報 setter/getter
//--------------------------------------------------------------
void SongInfoSet::setPoint(ofPoint _point) {
    point = _point;
}
ofPoint SongInfoSet::getPoint() {
    return point;
}

void SongInfoSet::setSongYear(int _songYear) {
    songYear = _songYear;
}
int SongInfoSet::getSongYear() {
    return songYear;
}

// カラー情報
void SongInfoSet::setColor(ofFloatColor _color) {
    color = _color;
}
ofFloatColor SongInfoSet::getColor() {
    return color;
}


//--------------------------------------------------------------
//  string -> 日付 メソッド
//--------------------------------------------------------------
time_t SongInfoSet::convertStringToTime(string stringDate) {
    
}