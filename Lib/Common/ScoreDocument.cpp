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
**      An Implementation of ScoreDocument class.
**
**      @file       Common/ScoreDocument.cpp
**/

#include    "BowlingScore/Common/ScoreDocument.h"


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    ScoreDocument  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

ScoreDocument::ScoreDocument()
    : m_gameDate(),
      m_gameTitle(),
      m_gameScore()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ScoreDocument::~ScoreDocument()
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
//    点数を計算する。
//

ErrCode
ScoreDocument::computeScores(
        const  PlayerIndex  index)
{
    ScoreSheet  &ss = this->m_gameScore.at(index);
    NumPins     sum = 0;

    NumPins     pins[33] = { 0 };
    int         offs[11] = { 0 };

    //  最初にデータを正規化する。    //
    for ( int j = 0; j < 9; ++ j ) {
        FrameScore &fs1 = ss.frames[j];
        sum = (10 - fs1.got1st);
        if ( fs1.got2nd > sum ) {
            fs1.got2nd   = sum;
        }
    }
    {
        FrameScore &fs1 = ss.frames[ 9];
        FrameScore &fs2 = ss.frames[10];
        sum = (10 - fs1.got1st);
        if ( sum <= 0 ) {
            sum = 10;
        }
        if ( fs1.got2nd > sum ) {
            fs1.got2nd  = sum;
        }
        sum -= fs1.got2nd;
        if ( sum <= 0 ) {
            sum = 10;
        }
        if ( fs2.got1st > sum ) {
            fs2.got1st  = sum;
        }
    }

    //  倒したピンの数を、バッファに「詰めて」コピー。  //
    int pos = 0;
    for ( int i = 0; i < 10; ++ i ) {
        offs[i] = pos;
        FrameScore  &sc = ss.frames[i];
        //  一投目  //
        if ( ((pins[pos++] = sum = sc.got1st) >= 10) && (i < 9) ) {
            continue;
        }
        //  二投目  //
        sum += pins[pos++] = sc.got2nd;

        //  オープンフレームの場合は、番兵を挿入する。  //
        if ( sum < 10 ) {
            pins[pos++] = 0;
        }
    }
    {
        FrameScore  &sc = ss.frames[10];
        pins[pos++] = sc.got1st;
        pins[pos]   = 0;
    }
    offs[10] = pos;

    //  配列 pins の内容から、各フレームの点数を計算。  //
    //  各フレームの先頭位置 pos  を offs から得る。    //
    //                                          //
    //  ストライクの場合は、                    //
    //  そのフレームが pos  にあり、            //
    //  次の二投 pos+1, pos+2 を加算する。      //
    //                                          //
    //  スペアの場合は、                        //
    //  そのフレームが pos+0, pos+1 にあり      //
    //  次フレームの一投目が pos+2  にある      //
    //
    //  オープンフレームの場合は、              //
    //  そのフレームが pos+0, pos+1 にあり      //
    //  番兵として pos+2 に 0 が置かれる。      //
    //                                          //
    //  最終 10 フレームについては、            //
    //  三投分が pos, pos+1, pos+2  にある      //
    //                                          //
    //  上記いずれの場合も、                    //
    //  pos, pos+1, pos+2 番目を合計すれば、    //
    //  そのフレームで加算される得点となる。    //

    sum = 0;
    for ( int i = 0; i < 10; ++ i ) {
        pos = offs[i];
        sum += (pins[pos] + pins[pos + 1] + pins[pos + 2]);
        ss.frames[i].score  = sum;
    }
    ss.frames[10].score = ss.frames[9].score;

    return ( ErrCode::SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    フレームデータを取得する。
//

const   FrameScore  &
ScoreDocument::getFrameScore(
        const  PlayerIndex  index,
        const  FrameNumber  frame)  const
{
    return ( this->m_gameScore.at(index).frames[frame] );
}

//----------------------------------------------------------------
//    フレームデータを設定する。
//

ErrCode
ScoreDocument::setFrameScore(
        const  PlayerIndex  index,
        const  FrameNumber  frame,
        const  FrameScore  &score)
{
    if ( (index < 0) || (this->m_gameScore.size() <= index) ) {
        return ( ErrCode::INDEX_OUT_OF_RANGE );
    }
    if ( (frame < 0) || (10 <= index) ) {
        return ( ErrCode::INDEX_OUT_OF_RANGE );
    }

    this->m_gameScore.at(index).frames[frame]   = score;
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    試合の日付を取得する。
//

const  std::string  &
ScoreDocument::getGameDate()  const
{
    return ( this->m_gameDate );
}

//----------------------------------------------------------------
//    試合の日付を設定する。
//

ErrCode
ScoreDocument::setGameDate(
        const  std::string  &value)
{
    this->m_gameDate    = value;
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    タイトルを取得する。
//

const  std::string  &
ScoreDocument::getGameTitle()  const
{
    return ( this->m_gameTitle );
}

//----------------------------------------------------------------
//    タイトルを設定する。
//

ErrCode
ScoreDocument::setGameTitle(
        const  std::string  &title)
{
    this->m_gameTitle   = title;
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    プレーヤーの人数を取得する。
//

const   PlayerIndex
ScoreDocument::getNumPlayers()  const
{
    return  static_cast<PlayerIndex>(this->m_gameScore.size());
}

//----------------------------------------------------------------
//    プレーヤーの人数を設定する。
//

ErrCode
ScoreDocument::setNumPlayers(
        const  PlayerIndex  value)
{
    this->m_gameScore.resize(value);
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    プレーヤーの名前を取得する。
//

const  std::string  &
ScoreDocument::getPlayerName(
        const  PlayerIndex  index)  const
{
    return ( this->m_gameScore.at(index).playerName );
}

//----------------------------------------------------------------
//    プレーヤーの名前を設定する。
//

ErrCode
ScoreDocument::setPlayerName(
        const  PlayerIndex  index,
        const  std::string  &value)
{
    if ( (index < 0) || (this->m_gameScore.size() <= index) ) {
        return ( ErrCode::INDEX_OUT_OF_RANGE );
    }
    this->m_gameScore.at(index).playerName = value;
    return ( ErrCode::SUCCESS );
}

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
