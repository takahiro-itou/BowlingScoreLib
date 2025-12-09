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
        fs1.flags   = 0;

        vSub.clear();
        TextParser::splitText(vTokens[1], ",", buf2, vSub, " \t");

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
        } else {
            fs1.check   = atoi(vTokens[4]);
        }

        //  一投目の残りピン。  //
        if ( fs1.got1st == 0 ) {
            //  スコアがゼロ、つまりピンが全部残っている。  //
            fs1.rem1st  = 0x07FE;
            if ( fj == 11 ) {
                //  最終フレームの例外処理。        //
                const  FrameScore  &fs2 = ptrDoc->getFrameScore(pi, 9);
                fs1.rem1st  =  fs2.rem2nd;
                if ( fs1.rem1st == 0 ) {
                    fs1.rem1st  = 0x07FE;
                }
                if ( fs2.got1st + fs2.got2nd < NUM_PINS_PER_FRAME ) {
                    //  スペアミスの場合、三投目はない。    //
                    fs1.rem1st  = 0;
                }
            }
        } else {
        vSub.clear();
        TextParser::splitText(vTokens[2], ",", buf2, vSub, " \t");
        fs1.rem1st  = 0;
        for ( size_t i = 0; i < vSub.size(); ++ i ) {
            int k = atoi(vSub[i]);
            if ( k != 0 ) {
                fs1.rem1st  |= (1 << k);
            }
        }
        }

        //  二投目の残りピン。  //
        if ( fs1.got2nd == 0 ) {
            //  スコアがゼロ、つまり一投目の残ピンと同じ。  //
            fs1.rem2nd  = fs1.rem1st;
            if ( fj == 10 && fs1.got1st >= 10 ) {
                //  最終フレームの例外処理。        //
                //  一投目ストライク、二投目ゼロ。  //
                fs1.rem2nd  = 0x07FE;
            }
        } else {
        vSub.clear();
        TextParser::splitText(vTokens[3], ",", buf2, vSub, " \t");
        fs1.rem2nd  = 0;
        for ( size_t i = 0; i < vSub.size(); ++ i ) {
            int k = atoi(vSub[i]);
            if ( k != 0 ) {
                fs1.rem2nd  |= (1 << k);
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
        for ( FrameNumber j = 0; j < 9; ++ j ) {
            outStr  <<  i  <<  ","  <<  (j + 1)  << ", |";
            const   FrameScore  &fs = objDoc.getFrameScore(i, j);
            if ( fs.got1st >= 10 ) {
                outStr  <<  "str,, |* |* |";
            } else {
                std::stringstream   rm1;
                std::stringstream   rm2;

                if ( fs.flags & FlagValues::GUTTER_1ST ) {
                    rm1 <<  "G,";
                } else if ( fs.flags & FlagValues::FAUL_1ST ) {
                    rm1 <<  "F,";
                } else {
                for ( int k = 1; k <= 10; ++ k ) {
                    if ( (fs.rem1st >> k) & 1 ) {
                        rm1 << k << ",";
                    }
                }
                }

                if ( fs.flags & FlagValues::GUTTER_2ND ) {
                    rm2 <<  "G,";
                } else if ( fs.flags & FlagValues::FAUL_2ND ) {
                    rm2 <<  "F,";
                } else {
                for ( int k = 1; k <= 10; ++ k ) {
                    if ( (fs.rem2nd >> k) & 1 ) {
                        rm2 << k << ",";
                    }
                }
                }

                if ( fs.flags & FlagValues::GUTTER_1ST ) {
                    outStr  <<  "G";
                } else if ( fs.flags & FlagValues::FAUL_1ST ) {
                    outStr  <<  "F";
                } else {
                    outStr  <<  fs.got1st;
                    if ( fs.flags & FlagValues::SPLIT_1ST ) {
                        outStr  <<  "s";
                    }
                }
                outStr  <<  ",";

                if ( fs.got1st + fs.got2nd >= 10 ) {
                    outStr  <<  "sp";
                    rm2.clear();
                    rm2.str("*");
                } else if ( fs.flags & FlagValues::MISS_2ND ) {
                    outStr  <<  "-";
                } else if ( fs.flags & FlagValues::GUTTER_2ND ) {
                    outStr  <<  "G";
                } else if ( fs.flags & FlagValues::FAUL_2ND ) {
                    outStr  <<  "F";
                } else {
                    outStr  <<  fs.got2nd;
                    if ( fs.flags & FlagValues::SPLIT_2ND ) {
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
                    if ( fs3.flags & FlagValues::MISS_1ST ) {
                        bf3 <<  "-";
                    } else if ( fs3.flags & FlagValues::GUTTER_1ST ) {
                        bf3 <<  "G";
                    } else if ( fs3.flags & FlagValues::FAUL_1ST ) {
                        bf3 <<  "F";
                    } else {
                        bf3 <<  fs3.got1st;
                        if ( fs3.flags & FlagValues::SPLIT_1ST ) {
                            bf3 <<  "s";
                        }
                    }
                }
            } else {
                if ( fs1.flags & FlagValues::MISS_2ND ) {
                    bf2 <<  "-";
                } else if ( fs1.flags & FlagValues::GUTTER_2ND ) {
                    bf2 <<  "G";
                } else if ( fs1.flags & FlagValues::FAUL_2ND ) {
                    bf2 <<  "F";
                } else {
                    bf2 <<  fs1.got2nd;
                    if ( fs1.flags & FlagValues::SPLIT_2ND ) {
                        bf2 <<  "s";
                    }
                }

                if ( fs1.got2nd + fs3.got1st >= 10 ) {
                    bf3 <<  "sp";
                } else {
                    if ( fs3.flags & FlagValues::MISS_1ST ) {
                        bf3 <<  "-";
                    } else if ( fs3.flags & FlagValues::GUTTER_1ST ) {
                        bf3 <<  "G";
                    } else if ( fs3.flags & FlagValues::FAUL_1ST ) {
                        bf3 <<  "F";
                    } else {
                        bf3 <<  fs3.got1st;
                        if ( fs3.flags & FlagValues::SPLIT_1ST ) {
                            bf3 <<  "s";
                        }
                    }
                }
            }
        } else {
            //  それ以外
            if ( fs1.flags & FlagValues::MISS_1ST ) {
                bf1 <<  "-";
            } else if ( fs1.flags & FlagValues::GUTTER_1ST ) {
                bf1 <<  "G";
            } else if ( fs1.flags & FlagValues::FAUL_1ST ) {
                bf1 <<  "F";
            } else {
                bf1 <<  fs1.got1st;
                if ( fs1.flags & FlagValues::SPLIT_1ST ) {
                    bf1 <<  "s";
                }
            }

            if ( fs1.got1st + fs1.got2nd >= 10 ) {
                bf2 <<  "sp";
                if ( fs3.got1st >= 10 ) {
                    bf3 <<  "str";
                } else {
                    bf3 <<  fs3.got1st;
                }
            } else {
                //  スペアミス
                if ( fs1.flags & FlagValues::MISS_2ND ) {
                    bf2 <<  "-";
                } else if ( fs1.flags & FlagValues::GUTTER_2ND ) {
                    bf2 <<  "G";
                } else if ( fs1.flags & FlagValues::FAUL_2ND ) {
                    bf2 <<  "F";
                } else {
                    bf2 <<  fs1.got2nd;
                    if ( fs1.flags & FlagValues::SPLIT_2ND ) {
                        bf2 <<  "s";
                    }
                }
                bf3 <<  "*";
            }
        }

        std::stringstream   rm1;
        std::stringstream   rm2;
        std::stringstream   rm3;

        if ( fs1.flags & FlagValues::GUTTER_1ST ) {
            rm1 <<  "G,";
        } else if ( fs1.flags & FlagValues::FAUL_1ST ) {
            rm1 <<  "F,";
        } else {
        if ( fs1.rem1st != 0 ) {
            for ( int k = 1; k <= 10; ++ k ) {
                if ( (fs1.rem1st >> k) & 1 ) {
                    rm1 << k << ",";
                }
            }
        } else {
            rm1 <<  "*";
        }
        }

        if ( fs1.flags & FlagValues::GUTTER_2ND ) {
            rm2 <<  "G,";
        } else if ( fs1.flags & FlagValues::FAUL_2ND ) {
            rm2 <<  "F,";
        } else {
        if ( fs1.rem2nd != 0 ) {
            for ( int k = 1; k <= 10; ++ k ) {
                if ( (fs1.rem2nd >> k) & 1 ) {
                    rm2 << k << ",";
                }
            }
        } else {
            rm2 <<  "*";
        }
        }

        if ( fs3.flags & FlagValues::GUTTER_1ST ) {
            rm3 <<  "G,";
        } else if ( fs3.flags & FlagValues::FAUL_1ST ) {
            rm1 <<  "F,";
        } else {
        if ( fs3.rem1st != 0 ) {
            for ( int k = 1; k <= 10; ++ k ) {
                if ( (fs3.rem1st >> k) & 1 ) {
                    rm3 << k << ",";
                }
            }
        } else {
            rm3 <<  "*";
        }
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

}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END
