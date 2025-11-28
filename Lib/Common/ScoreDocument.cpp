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

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    試合の日付を取得する。
//

const  std::string  &
ScoreDocument::getGameDate()  const
{
}

//----------------------------------------------------------------
//    試合の日付を設定する。
//

ErrCode
ScoreDocument::setGameDate(
        const  std::string  &value)
{
}

//----------------------------------------------------------------
//    タイトルを取得する。
//

const  std::string  &
ScoreDocument::getGameTitle()  const
{
}

//----------------------------------------------------------------
//    タイトルを設定する。
//

ErrCode
ScoreDocument::setGameTitle(
        const  std::string  &title)
{
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
