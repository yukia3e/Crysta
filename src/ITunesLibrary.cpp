//
//  ITunesLibrary.cpp
//  mu_jewel
//
//  Created by yuki. on 2015/08/19.
//
//

#include "ITunesLibrary.h"

ITunesLibrary::ITunesLibrary() {
    xmlPath = "iTunes Music Library.xml";
}

void ITunesLibrary::setXmlPath(string _xmlPath) {
    this->xmlPath = _xmlPath;
}

string ITunesLibrary::getXmlPath() {
    return this->xmlPath;
}

vector<SongInfoSet> ITunesLibrary::getITLInfoSet() {
    
    // ファイルをバッファへ
    ofFile file;
    file.open(xmlPath);
    ofBuffer buffer = file.readToBuffer();

    // バッファからテキストを取得し、xmlへ
    ofXml pictures;
    pictures.loadFromBuffer( buffer.getText() );
    
    
    pictures.setTo("dict/dict");
    pictures.setToChild(1);
    
    do {
        SongInfoSet song;

        // トラック名取得
        pictures.setToChild(3);
        song.setTrackName(pictures.getValue());
        pictures.setToParent();
        
        // アーティスト名取得
        pictures.setToChild(5);
        song.setArtistName(pictures.getValue());
        pictures.setToParent();
        
        // アルバム名取得
        pictures.setToChild(7);
        song.setAlbumName(pictures.getValue());
        pictures.setToParent();

        // 追加日取得
        pictures.setToChild(1);
        song.setAddedDate(pictures.getValue());
        pictures.setToParent();
        
        // infoSetに取得した楽曲情報をプッシュ
        infoSet.push_back(song);
    
        pictures.setToSibling();
    } while (pictures.setToSibling());
    
    return infoSet;
}
