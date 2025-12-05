//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---   Bowling Score.   ---                      **
**                                                                      **
**          Copyright (C), 2025-2025, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of DocumentFile class.
**
**      @file       Common/DocumentFile.cpp
**/

#include    "BowlingScore/Common/DocumentFile.h"

#include    "BowlingScore/Common/ScoreDocument.h"

#include    <iostream>
#include    <iterator>
#include    <fstream>
#include    <sstream>
#include    <string.h>


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

inline  void
rstrip( std::string  &s)
{
    s.erase(s.find_last_not_of(" ") + 1);
}

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    DocumentFile  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

DocumentFile::DocumentFile()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DocumentFile::~DocumentFile()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    データをテキストファイルから読み込む。
//

ErrCode
DocumentFile::readFromTextFile(
        const  std::string  &fileName,
        ScoreDocument  *    ptrDoc)
{
    std::ifstream   ifs(fileName.c_str());
    return  readFromTextStream(ifs, ptrDoc);
}

//----------------------------------------------------------------
//    データをテキストストリームから読み込む。
//

ErrCode
DocumentFile::readFromTextStream(
        std::istream       &inStr,
        ScoreDocument  *    ptrDoc)
{
    //std::stringstream   ssLogs;
    std::ostream  & ssLogs  = std::cerr;

    int         lineNo  = 0;
    PlayerIndex numPlayers  = 0;
    std::string strLine;
    TextBuffer  buf;
    TokenArray  vTokens;

    while ( inStr.good() ) {
        if ( ! std::getline(inStr, strLine) ) {
            break;
        }
        ssLogs  <<  (++lineNo)  <<  " :"
                <<  strLine     <<  std::endl;

        //  空行は読み飛ばす。  //
        if ( strLine.empty() ) {
            continue;
        }
        //  先頭がハッシュ記号の場合も読み飛ばす。  //
        if ( strLine[0] == '#' ) {
            continue;
        }

        vTokens.clear();
        splitText(strLine, "|", buf, vTokens);
#if defined( _DEBUG )
        std::copy(
                vTokens.begin(), vTokens.end(),
                std::ostream_iterator<const char *>(ssLogs, "/")
        );
        ssLogs  <<  std::endl;
#endif

        if ( ! strcmp(vTokens[0], "date") ) {
            std::cerr   <<  "DATE:"  <<  vTokens[1];
            ptrDoc->setGameDate(vTokens[1]);
        }
        if ( ! strcmp(vTokens[0], "title") ) {
            std::cerr   <<  "TITLE:"  <<  vTokens[1];
            ptrDoc->setGameTitle(vTokens[1]);
        }
        if ( ! strcmp(vTokens[0], "players") ) {
            std::cerr   <<  "PLAYERS"  <<  vTokens[1];
            numPlayers  = atoi(vTokens[1]);
            ptrDoc->setNumPlayers(numPlayers);
        }
        for ( PlayerIndex i = 0; i < numPlayers; ++ i ) {
            std::stringstream   ss;
            ss  <<  "player"    <<  i;
            if ( ss.str() == vTokens[0] ) {
                std::cerr   <<  "PLAYER" <<  i  << ":"
                            <<  vTokens[1];
                ptrDoc->setPlayerName(i, vTokens[1]);
            }
        }

        if ( vTokens.size() != 4 && vTokens.size() != 5 ) {
            continue;
        }

        TextBuffer  buf2;
        TokenArray  vSub;
        vSub.clear();
        splitText(vTokens[0], ",", buf2, vSub);
        if ( vSub.size() < 2 ) { continue; }
        const  PlayerIndex  pi  = atoi(vSub[0]);
        const  FrameNumber  fj  = atoi(vSub[1]);
        ssLogs  <<  "pi = " << pi << ", fj = " << fj  <<  ", ";

        FrameScore  fs1;

        vSub.clear();
        splitText(vTokens[1], ",", buf2, vSub);

        if ( ! strcmp(vSub[0], "str") || ! strcmp(vSub[0], "sp") ) {
            fs1.got1st  = 10;
        } else {
            fs1.got1st  = atoi(vSub[0]);
        }

        if ( vSub.size() == 1 ) {
            //  第11フレーム（最終10フレームの三投目）か、  //
            //  一投目でストライクを出した場合は、          //
            //  二投目のデータが必要ないので読み飛ばす。    //
        } if ( ! strcmp(vSub[1], "str") || ! strcmp(vSub[1], "sp") ) {
            fs1.got2nd  = 10;
        } else {
            fs1.got2nd  = atoi(vSub[1]);
        }

        if ( fj == 11 && vTokens.size() == 4 ) {
            //  第11フレームのカラム数が足りない時は、  //
            //  検証用スコアデータが省略されたと場合。  //
            fs1.check   = ptrDoc->getFrameScore(pi, 9).check;
        } else {
            fs1.check   = atoi(vTokens[4]);
        }
        std::cerr   <<  fs1.got1st  << "," << fs1.got2nd
                    <<  ", check="  <<  fs1.check  <<  std::endl;

        //  一投目の残りピン。  //
        vSub.clear();
        splitText(vTokens[2], ",", buf2, vSub);
        fs1.rem1st  = 0;
        for ( size_t i = 0; i < vSub.size(); ++ i ) {
            int k = atoi(vSub[i]);
            if ( k != 0 ) {
                fs1.rem1st  |= (1 << k);
            }
        }

        //  二投目の残りピン。  //
        vSub.clear();
        splitText(vTokens[3], ",", buf2, vSub);
        fs1.rem2nd  = 0;
        for ( size_t i = 0; i < vSub.size(); ++ i ) {
            int k = atoi(vSub[i]);
            if ( k != 0 ) {
                fs1.rem2nd  |= (1 << k);
            }
        }

        ptrDoc->setFrameScore(pi, fj - 1, fs1);
    }

    for ( PlayerIndex i = 0; i < numPlayers; ++ i ) {
        ptrDoc->computeScores(i);
    }

#if defined( _DEBUG )
    //  std::cerr   <<  ssLogs.str();
#endif

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    データをテキストファイルに書き込む。
//

ErrCode
DocumentFile::saveToTextFile(
        const  ScoreDocument   & objDoc,
        const  std::string     & fileName)
{
    std::ofstream   ofs(fileName.c_str());
    return  saveToTextStream(objDoc, ofs);
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む。
//

ErrCode
DocumentFile::saveToTextStream(
        const  ScoreDocument   & objDoc,
        std::ostream           & outStr)
{
    outStr  <<  "# info\n"
            <<  "\ndate |"      <<  objDoc.getGameDate()
            <<  "\ntitle |"     <<  objDoc.getGameTitle()
            <<  "\nplayers |"   <<  objDoc.getNumPlayers();
    for ( PlayerIndex i = 0; i < objDoc.getNumPlayers(); ++ i ) {
        outStr  <<  "\nplayer"  <<  i
                <<  " |"
                <<  objDoc.getPlayerName(i);
    }

    outStr  <<  "\n\n# score\n\n";
    for ( PlayerIndex i = 0; i < objDoc.getNumPlayers(); ++ i ) {
        for ( FrameNumber j = 0; j < 9; ++ j ) {
            outStr  <<  i  <<  ","  <<  (j + 1)  << ", |";
            const   FrameScore  &fs = objDoc.getFrameScore(i, j);
            if ( fs.got1st >= 10 ) {
                outStr  <<  "str,, |* |* |";
            } else {
                std::stringstream   rm1;
                std::stringstream   rm2;

                for ( int k = 1; k <= 10; ++ k ) {
                    if ( (fs.rem1st >> k) & 1 ) {
                        rm1 << k << ",";
                    }
                }

                for ( int k = 1; k <= 10; ++ k ) {
                    if ( (fs.rem2nd >> k) & 1 ) {
                        rm2 << k << ",";
                    }
                }

                outStr  <<  fs.got1st  << ",";
                if ( fs.got1st + fs.got2nd >= 10 ) {
                    outStr  <<  "sp, |"
                            <<  rm1.str()
                            <<  " |"
                            <<  "* |";
                } else {
                    outStr  <<  fs.got2nd << ", |"
                            <<  rm1.str()
                            <<  " |"
                            <<  rm2.str()
                            <<  " |";
                }
            }
            outStr  <<  fs.score    <<  "\n";
        }

        outStr  <<  i  <<  ","  <<  10  << ", |";

        std::stringstream   bf1;
        std::stringstream   bf2;
        std::stringstream   bf3;

        const  FrameScore  &fs1 = objDoc.getFrameScore(i,  9);
        const  FrameScore  &fs3 = objDoc.getFrameScore(i, 10);

        if ( fs1.got1st >= 10 ) {
            //  ストライク
            bf1 <<  "str";
            if ( fs1.got2nd >= 10 ) {
                //  ダブル
                bf2 <<  "str";
                if ( fs3.got1st >= 10 ) {
                    //  ターキー
                    bf3 <<  "str";
                } else  {
                    bf3 <<  fs3.got1st;
                }
            } else {
                bf2 <<  fs1.got2nd;
                if ( fs1.got2nd + fs3.got1st >= 10 ) {
                    bf3 <<  "sp";
                } else {
                    bf3 <<  fs3.got1st;
                }
            }
        } else {
            //  それ以外
            bf1 <<  fs1.got1st;
            if ( fs1.got1st + fs1.got2nd >= 10 ) {
                bf2 <<  "sp";
                if ( fs3.got1st >= 10 ) {
                    bf3 <<  "str";
                } else {
                    bf3 <<  fs3.got1st;
                }
            } else {
                //  スペアミス
                bf2 <<  fs1.got2nd;
            }
        }

        std::stringstream   rm1;
        std::stringstream   rm2;
        std::stringstream   rm3;

        if ( fs1.rem1st != 0 ) {
            for ( int k = 1; k <= 10; ++ k ) {
                if ( (fs1.rem1st >> k) & 1 ) {
                    rm1 << k << ",";
                }
            }
        } else {
            rm1 <<  "*";
        }

        if ( fs1.rem2nd != 0 ) {
            for ( int k = 1; k <= 10; ++ k ) {
                if ( (fs1.rem2nd >> k) & 1 ) {
                    rm2 << k << ",";
                }
            }
        } else {
            rm2 <<  "*";
        }

        if ( fs3.rem1st != 0 ) {
            for ( int k = 1; k <= 10; ++ k ) {
                if ( (fs3.rem1st >> k) & 1 ) {
                    rm3 << k << ",";
                }
            }
        } else {
            rm3 <<  "*";
        }

        outStr  <<  bf1.str()
                <<  ","
                <<  bf2.str()
                <<  ", |"
                <<  rm1.str()
                <<  " |"
                <<  rm2.str()
                <<  " |"
                <<  fs1.score
                <<  "\n";
        outStr  <<  i  <<  ","  <<  11  << ", |"
                <<  bf3.str()
                <<  ",, |"
                <<  rm3.str()
                <<  " | |";
        outStr  <<  std::endl;
    }

    return ( ErrCode::SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    文字列を指定した文字で分割する。
//

ErrCode
DocumentFile::splitText(
        const  std::string  &inText,
        const  char  *      sepChrs,
        TextBuffer          &bufText,
        TokenArray          &vTokens)
{
    const   size_t  szText  = inText.size();
    bufText.clear();
    bufText.resize(szText + 1);
    char  *  const  ptrBuf  = &(bufText[0]);

    ::memcpy(ptrBuf, inText.c_str(), szText);
    ptrBuf[szText]  = '\0';

    char *  pSaved  = nullptr;
    char *  pToken  = nullptr;

#if defined( _WIN32 )
    pToken  = strtok_s(ptrBuf, sepChrs, &pSaved);
#else
    pToken  = strtok_r(ptrBuf, sepChrs, &pSaved);
#endif

    while ( pToken != nullptr ) {
        //  末尾にある空白は捨てる。    //
        char *  pp  = pToken + strlen(pToken) - 1;
        while ( *pp == ' ' ) {
            (* pp)  = '\0';
            -- pp;
        }

        vTokens.push_back(pToken);
#if defined( _WIN32 )
        pToken  = strtok_s(nullptr, sepChrs, &pSaved);
#else
        pToken  = strtok_r(nullptr, sepChrs, &pSaved);
#endif
    }

    return ( ErrCode::SUCCESS );
}


}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END
