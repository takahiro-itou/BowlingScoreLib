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
**      An Interface of ScoreDocument class.
**
**      @file       Common/ScoreDocument.h
**/

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_SCORE_DOCUMENT_H )
#    define   BOWLINGSCORE_COMMON_INCLUDED_SCORE_DOCUMENT_H

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_BOWLING_TYPES_H )
#    include    "BowlingTypes.h"
#endif

#if !defined( BOWLINGSCORE_SYS_STL_INCLUDED_STRING )
#    include    <string>
#    define   BOWLINGSCORE_SYS_STL_INCLUDED_STRING
#endif


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //


//========================================================================
//
//    ScoreDocument  class.
//

class  ScoreDocument
{

//========================================================================
//
//    Internal Type Definitions.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    ScoreDocument();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ScoreDocument();

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
public:

    //----------------------------------------------------------------
    /**   フレームデータを取得する。
    **
    **  @param [in] index   プレーヤー番号。
    **  @param [in] frame   フレーム番号。
    **  @return     フレームのスコアデータを返す。
    **/
    const   FrameScore  &
    getFrameScore(
            const  PlayerIndex  index,
            const  FrameNumber  frame)  const;

    //----------------------------------------------------------------
    /**   フレームデータを設定する。
    **
    **  @param [in] index   プレーヤー番号。
    **  @param [in] frame   フレーム番号。
    **  @param [in] score   フレームのスコアデータ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setFrameScore(
            const  PlayerIndex  index,
            const  FrameNumber  frame,
            const  FrameScore  &score);

    //----------------------------------------------------------------
    /**   試合の日付を取得する。
    **
    **  @return     日付を文字列で返す。
    **/
    const  std::string  &
    getGameDate()  const;

    //----------------------------------------------------------------
    /**   試合の日付を設定する。
    **
    **  @param [in] value   日付を表す文字列。
    **      文字列の内容が正しいかの検証は行わない。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setGameDate(
            const  std::string  &value);

    //----------------------------------------------------------------
    /**   タイトルを取得する。
    **
    **  @return
    **/
    const  std::string  &
    getGameTitle()  const;

    //----------------------------------------------------------------
    /**   タイトルを設定する。
    **
    **  @param [in] title   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setGameTitle(
            const  std::string  &title);

    //----------------------------------------------------------------
    /**   プレーヤーの人数を取得する。
    **
    **  @return
    **/
    const   PlayerIndex
    getNumPlayers()  const;

    //----------------------------------------------------------------
    /**   プレーヤーの人数を設定する。
    **
    **  @param [in] value   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setNumPlayers(
            const  PlayerIndex  value);

    //----------------------------------------------------------------
    /**   プレーヤーの名前を取得する。
    **
    **  @param [in] index   プレーヤー番号。
    **  @return     プレーヤーの名前を返す。
    **/
    const  std::string  &
    getPlayerName(
            const  PlayerIndex  index)  const;

    //----------------------------------------------------------------
    /**   プレーヤーの名前を設定する。
    **
    **  @param [in] index   プレーヤー番号。
    **  @param [in] value   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setPlayerName(
            const  PlayerIndex  index,
            const  std::string  &value);

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ScoreDocumentTest;
};

}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END

#endif
