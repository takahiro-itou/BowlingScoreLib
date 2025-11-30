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

    for ( int i = 0; i < 9; ++ i ) {
        FrameScore  &sc = ss.frames[i];
        NumPins     tmp = (sc.got1st + sc.got2nd);
        if ( sc.got1st == 10 ) {
            //  ストライク  //
            //  まず、次のフレームの１投目を加える。    //
            sum += ss.frames[i + 1].got1st;
            if ( ss.frames[i + 1].got1st == 10 ) {
                //  ダブルの時はその次のフレームの１投目も加える。  //
                if ( i == 8 ) {
                    //  ９フレーム目のダブルの時は１０フレの１、２投目  //
                    sum += (ss.frames[i + 1].got2nd);
                } else {
                    sum += (ss.frames[i + 2].got1st);
                }
            } else {
                sum += (ss.frames[i + 1].got2nd);
            }
        } else if ( tmp == 10 ) {
            //  スペア。    //
            sum += ss.frames[i + 1].got1st;
        }
        //  そのフレーム自身の点数も加える。    //
        sum += tmp;
        sc.score    = sum;
    }

    //  最終10フレームは例外処理。  //
    {
        FrameScore  &sc = ss.frames[9];
        sum += (sc.got1st + sc.got2nd + sc.got3rd);
        sc.score    = sum;
    }

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
