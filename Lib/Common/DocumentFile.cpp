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
#include    "BowlingScore/Common/TextParser.h"


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
    std::stringstream   ssLogs;
    //  std::ostream  & ssLogs  = std::cerr;

    int         lineNo  = 0;
    PlayerIndex numPlayers  = 0;
    std::string strLine;
    TextParser::TextBuffer  buf;
    TextParser::TokenArray  vTokens;

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
        TextParser::splitText(strLine, "|", buf, vTokens, " \t");
#if defined( _DEBUG )
        std::copy(
                vTokens.begin(), vTokens.end(),
                std::ostream_iterator<const char *>(ssLogs, "/")
        );
        ssLogs  <<  std::endl;
#endif

        if ( ! strcmp(vTokens[0], "date") ) {
            ptrDoc->setGameDate(vTokens[1]);
        }
        if ( ! strcmp(vTokens[0], "title") ) {
            ptrDoc->setGameTitle(vTokens[1]);
        }
        if ( ! strcmp(vTokens[0], "players") ) {
            numPlayers  = atoi(vTokens[1]);
            ptrDoc->setNumPlayers(numPlayers);
        }
        for ( PlayerIndex i = 0; i < numPlayers; ++ i ) {
            std::stringstream   ss;
            ss  <<  "player"    <<  i;
            if ( ss.str() == vTokens[0] ) {
                ptrDoc->setPlayerName(i, vTokens[1]);
            }
        }

        if ( vTokens.size() != 5 ) {
            continue;
        }

        TextParser::TextBuffer  buf2;
        TextParser::TokenArray  vSub;
        vSub.clear();
        TextParser::splitText(vTokens[0], ",", buf2, vSub, " \t");
        if ( vSub.size() < 2 ) { continue; }
        const  PlayerIndex  pi  = atoi(vSub[0]);
        const  FrameNumber  fj  = atoi(vSub[1]);
        ssLogs  <<  "pi = " << pi << ", fj = " << fj  <<  ", ";

        FrameScore  fs1;
        fs1.flg1st  = 0;
        fs1.flg2nd  = 0;

        vSub.clear();
        TextParser::splitText(vTokens[1], ",", buf2, vSub, " \t");

        if ( ! strcmp(vSub[0], "str") || ! strcmp(vSub[0], "sp") ) {
            fs1.got1st  = NUM_PINS_PER_FRAME;
        } else {
            fs1.got1st  = atoi(vSub[0]);
            if ( (fs1.got1st >= 1) && (vSub[0][1] == 's') ) {
                fs1.flg1st  |= FlagValues::SPLIT;
            }
        }
        if ( ! strcmp(vSub[0], "-") ) {
            fs1.flg1st  |= FlagValues::MISS;
        } else if ( ! strcmp(vSub[0], "G") ) {
            fs1.flg1st  |= FlagValues::GUTTER;
        } else if ( ! strcmp(vSub[0], "F") ) {
            fs1.flg1st  |= FlagValues::FAUL;
        }

        if ( vSub.size() == 1 ) {
            //  第11フレーム（最終10フレームの三投目）か、  //
            //  一投目でストライクを出した場合は、          //
            //  二投目のデータが必要ないので読み飛ばす。    //
        } if ( ! strcmp(vSub[1], "str") || ! strcmp(vSub[1], "sp") ) {
            fs1.got2nd  = NUM_PINS_PER_FRAME;
        } else {
            fs1.got2nd  = atoi(vSub[1]);
            if ( (fs1.got2nd >= 1) && (vSub[1][1] == 's') ) {
                fs1.flg2nd  |= FlagValues::SPLIT;
            }
        }
        if ( ! strcmp(vSub[1], "-") ) {
            fs1.flg2nd  |= FlagValues::MISS;
        } else if ( ! strcmp(vSub[1], "G") ) {
            fs1.flg2nd  |= FlagValues::GUTTER;
        } else if ( ! strcmp(vSub[1], "F") ) {
            fs1.flg2nd  |= FlagValues::FAUL;
        }

        if ( fj == 11 ) {
            if ( vTokens.size() == 4 ) {
                //  第11フレームのカラム数が足りない時は、  //
                //  検証用スコアデータが省略されたと場合。  //
                fs1.check   = 0;
            } else {
                fs1.check   = atoi(vTokens[4]);
            }
            if ( fs1.check == 0 ) {
                fs1.check   = ptrDoc->getFrameScore(pi, 9).check;
            }
            fs1.flg2nd  = FlagValues::NO_SCORE;
        } else {
            fs1.check   = atoi(vTokens[4]);
        }

        //  一投目の残りピン。  //
        if ( fs1.got1st == 0 ) {
            //  スコアがゼロ、つまりピンが全部残っている。  //
            fs1.rem1st  = REMAIN_ALL_PINS;
            if ( fj == 11 ) {
                //  最終フレームの例外処理。        //
                const  FrameScore  &fs2 = ptrDoc->getFrameScore(pi, 9);
                fs1.rem1st  =  fs2.rem2nd;
                if ( fs1.rem1st == 0 ) {
                    fs1.rem1st  = REMAIN_ALL_PINS;
                }
                if ( fs2.got1st + fs2.got2nd < NUM_PINS_PER_FRAME ) {
                    //  スペアミスの場合、三投目はない。    //
                    fs1.rem1st  = 0;
                }
            }
        } else {
            fs1.rem1st  = parseRemainPins(vTokens[2], fs1.flg1st);
        }
        {
            TextParser::TextBuffer  buf3;
            TextParser::TokenArray  vSub3;

            vSub3.clear();
            TextParser::splitText(vTokens[2], ",", buf3, vSub3, " \t");
            for ( size_t i = 0; i < vSub3.size(); ++ i ) {
                if ( ! strcmp(vSub3[i], "-") ) {
                    fs1.flg1st  |= FlagValues::MISS;
                } else if ( ! strcmp(vSub3[i], "G") ) {
                    fs1.flg1st  |= FlagValues::GUTTER;
                } else if ( ! strcmp(vSub3[i], "F") ) {
                    fs1.flg1st  |= FlagValues::FAUL;
                }
            }
        }

        //  二投目の残りピン。  //
        if ( fs1.got2nd == 0 ) {
            //  スコアがゼロ、つまり一投目の残ピンと同じ。  //
            fs1.rem2nd  = fs1.rem1st;
            if ( fj == NUM_FRAMES && fs1.got1st >= NUM_PINS_PER_FRAME ) {
                //  最終フレームの例外処理。        //
                //  一投目ストライク、二投目ゼロ。  //
                fs1.rem2nd  = REMAIN_ALL_PINS;
            }
        } else {
            fs1.rem2nd  = parseRemainPins(vTokens[3], fs1.flg2nd);
        }
        {
            TextParser::TextBuffer  buf3;
            TextParser::TokenArray  vSub3;

            vSub3.clear();
            TextParser::splitText(vTokens[3], ",", buf3, vSub3, " \t");
            for ( size_t i = 0; i < vSub3.size(); ++ i ) {
                if ( ! strcmp(vSub3[i], "-") ) {
                    fs1.flg2nd  |= FlagValues::MISS;
                } else if ( ! strcmp(vSub3[i], "G") ) {
                    fs1.flg2nd  |= FlagValues::GUTTER;
                } else if ( ! strcmp(vSub3[i], "F") ) {
                    fs1.flg2nd  |= FlagValues::FAUL;
                }
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
        for ( FrameNumber j = 0; j < (NUM_FRAMES - 1); ++ j ) {
            outStr  <<  i  <<  ","  <<  (j + 1)  << ", |";
            const   FrameScore  &fs = objDoc.getFrameScore(i, j);
            if ( fs.got1st >= NUM_PINS_PER_FRAME ) {
                outStr  <<  "str,, |* |* |";
            } else {
                std::stringstream   rm1;
                std::stringstream   rm2;

                writeRemainPins(fs.rem1st, fs.flg1st, rm1);

                writeRemainPins(fs.rem2nd, fs.flg2nd, rm2);

                if ( fs.flg1st & FlagValues::GUTTER ) {
                    outStr  <<  "G";
                } else if ( fs.flg1st & FlagValues::FAUL ) {
                    outStr  <<  "F";
                } else {
                    outStr  <<  fs.got1st;
                    if ( fs.flg1st & FlagValues::SPLIT ) {
                        outStr  <<  "s";
                    }
                }
                outStr  <<  ",";

                if ( fs.got1st + fs.got2nd >= NUM_PINS_PER_FRAME ) {
                    outStr  <<  "sp";
                    rm2.clear();
                    rm2.str("*");
                } else if ( fs.flg2nd & FlagValues::MISS ) {
                    outStr  <<  "-";
                } else if ( fs.flg2nd & FlagValues::GUTTER ) {
                    outStr  <<  "G";
                } else if ( fs.flg2nd & FlagValues::FAUL ) {
                    outStr  <<  "F";
                } else {
                    outStr  <<  fs.got2nd;
                    if ( fs.flg2nd & FlagValues::SPLIT ) {
                        outStr  <<  "s";
                    }
                }
                outStr  <<  ", |"
                        <<  rm1.str()
                        <<  " |"
                        <<  rm2.str()
                        <<  " |";
            }
            outStr  <<  fs.score    <<  "\n";
        }

        outStr  <<  i  <<  ","  <<  NUM_FRAMES  << ", |";

        std::stringstream   bf1;
        std::stringstream   bf2;
        std::stringstream   bf3;

        const  FrameScore  &fs1 = objDoc.getFrameScore(i, NUM_FRAMES - 1);
        const  FrameScore  &fs3 = objDoc.getFrameScore(i, NUM_FRAMES    );

        if ( fs1.got1st >= NUM_PINS_PER_FRAME ) {
            //  ストライク
            bf1 <<  "str";
            if ( fs1.got2nd >= NUM_PINS_PER_FRAME ) {
                //  ダブル
                bf2 <<  "str";
                if ( fs3.got1st >= NUM_PINS_PER_FRAME ) {
                    //  ターキー
                    bf3 <<  "str";
                } else  {
                    if ( fs3.flg1st & FlagValues::MISS ) {
                        bf3 <<  "-";
                    } else if ( fs3.flg1st & FlagValues::GUTTER ) {
                        bf3 <<  "G";
                    } else if ( fs3.flg1st & FlagValues::FAUL ) {
                        bf3 <<  "F";
                    } else {
                        bf3 <<  fs3.got1st;
                        if ( fs3.flg1st & FlagValues::SPLIT ) {
                            bf3 <<  "s";
                        }
                    }
                }
            } else {
                if ( fs1.flg2nd & FlagValues::MISS ) {
                    bf2 <<  "-";
                } else if ( fs1.flg2nd & FlagValues::GUTTER ) {
                    bf2 <<  "G";
                } else if ( fs1.flg2nd & FlagValues::FAUL ) {
                    bf2 <<  "F";
                } else {
                    bf2 <<  fs1.got2nd;
                    if ( fs1.flg2nd & FlagValues::SPLIT ) {
                        bf2 <<  "s";
                    }
                }

                if ( fs1.got2nd + fs3.got1st >= NUM_PINS_PER_FRAME ) {
                    bf3 <<  "sp";
                } else {
                    if ( fs3.flg1st & FlagValues::MISS ) {
                        bf3 <<  "-";
                    } else if ( fs3.flg1st & FlagValues::GUTTER ) {
                        bf3 <<  "G";
                    } else if ( fs3.flg1st & FlagValues::FAUL ) {
                        bf3 <<  "F";
                    } else {
                        bf3 <<  fs3.got1st;
                        if ( fs3.flg1st & FlagValues::SPLIT ) {
                            bf3 <<  "s";
                        }
                    }
                }
            }
        } else {
            //  それ以外
            if ( fs1.flg1st & FlagValues::MISS ) {
                bf1 <<  "-";
            } else if ( fs1.flg1st & FlagValues::GUTTER ) {
                bf1 <<  "G";
            } else if ( fs1.flg1st & FlagValues::FAUL ) {
                bf1 <<  "F";
            } else {
                bf1 <<  fs1.got1st;
                if ( fs1.flg1st & FlagValues::SPLIT ) {
                    bf1 <<  "s";
                }
            }

            if ( fs1.got1st + fs1.got2nd >= NUM_PINS_PER_FRAME ) {
                bf2 <<  "sp";
                if ( fs3.got1st >= NUM_PINS_PER_FRAME ) {
                    bf3 <<  "str";
                } else {
                    bf3 <<  fs3.got1st;
                }
            } else {
                //  スペアミス
                if ( fs1.flg2nd & FlagValues::MISS ) {
                    bf2 <<  "-";
                } else if ( fs1.flg2nd & FlagValues::GUTTER ) {
                    bf2 <<  "G";
                } else if ( fs1.flg2nd & FlagValues::FAUL ) {
                    bf2 <<  "F";
                } else {
                    bf2 <<  fs1.got2nd;
                    if ( fs1.flg2nd & FlagValues::SPLIT ) {
                        bf2 <<  "s";
                    }
                }
                bf3 <<  "*";
            }
        }

        std::stringstream   rm1;
        std::stringstream   rm2;
        std::stringstream   rm3;

        writeRemainPins(fs1.rem1st, fs1.flg1st, rm1);

        writeRemainPins(fs1.rem2nd, fs1.flg2nd, rm2);

        writeRemainPins(fs3.rem1st, fs3.flg1st, rm3);

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
        outStr  <<  i  <<  ","  <<  FRAME_ARRAY_SIZE  << ", |"
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
//    残りピンの情報を解析する。
//

const   RemainPins
DocumentFile::parseRemainPins(
        const  char  *  text,
        FrameFlags    & flags)
{
    TextParser::TextBuffer  buf2;
    TextParser::TokenArray  vSub;

    vSub.clear();
    TextParser::splitText(text, ",", buf2, vSub, " \t");

    RemainPins  rp  = 0;
    for ( size_t i = 0; i < vSub.size(); ++ i ) {
        int k = atoi(vSub[i]);
        if ( k != 0 ) {
            rp  |= (1 << k);
        }
    }

    return ( rp );
}

//----------------------------------------------------------------
//    残りピンの情報を出力する。
//

std::ostream  &
DocumentFile::writeRemainPins(
        const   RemainPins  rPins,
        const   FrameFlags  flags,
        std::ostream      & outStr)
{
    if ( rPins != 0 ) {
        for ( int k = 1; k <= 10; ++ k ) {
            if ( (rPins >> k) & 1 ) {
                outStr  <<  k  <<  ",";
            }
        }
    } else {
        outStr  <<  "*";
    }

    if ( flags & FlagValues::GUTTER ) {
        outStr  <<  "G,";
    }
    if ( flags & FlagValues::FAUL ) {
        outStr  <<  "F,";
    }

    return ( outStr );
}

}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END
