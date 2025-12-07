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
**      An Interface of TextParser class.
**
**      @file       Common/TextParser.h
**/

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_TEXT_PARSER_H )
#    define   BOWLINGSCORE_COMMON_INCLUDED_TEXT_PARSER_H

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_BOWLING_TYPES_H )
#    include    "BowlingTypes.h"
#endif

#if !defined( BOWLINGSCORE_SYS_STL_INCLUDED_STRING )
#    include    <string>
#    define   BOWLINGSCORE_SYS_STL_INCLUDED_STRING
#endif

#if !defined( BOWLINGSCORE_SYS_STL_INCLUDED_VECTOR )
#    include    <vector>
#    define   BOWLINGSCORE_SYS_STL_INCLUDED_VECTOR
#endif


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //


//========================================================================
//
//    TextParser  class.
//

class  TextParser
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     std::vector<char>           TextBuffer;

    typedef     std::vector<char  *>        TokenArray;

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
    TextParser();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~TextParser();

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
public:

    //----------------------------------------------------------------
    /**   文字列を指定した文字で分割する。
    **
    **  @param [in] inText    入力テキスト。
    **  @param [in] sepChrs   区切り文字。
    **  @param[out] bufText   テキストバッファ。
    **  @param[out] vTokens   分割結果を追記する変数。
    **      必要なら呼び出す前に内容をクリアしておく。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    splitText(
            const  std::string  &inText,
            const  char  *      sepChrs,
            TextBuffer          &bufText,
            TokenArray          &vTokens,
            const  char  *      delChrs = nullptr);

    //----------------------------------------------------------------
    /**   末尾の特定の文字を削除する。
    **
    **  @param [in,out] ptrBuf    入力テキスト。
    **      この文字列の内容は書き換えられる。
    **  @param [in]     delChrs   削除する文字。
    **  @return     引数 ptrBuf を返す。
    **/
    static  char  *
    stripRight(
            char  *  const  ptrBuf,
            const  char  *  delChrs = " ");

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
private:

    //----------------------------------------------------------------
    /**   文字列を指定した文字で分割する。
    **
    **  @param [in,out] ptrBuf    入力テキスト。
    **      この文字列の内容は書き換えられる。
    **  @param [in]     ptrEnd
    **  @param [in]     sepChar   区切り文字。
    **  @param    [out] vTokens   分割結果を追記する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    splitTextSub(
            char  *  const  ptrBuf,
            char  *  const  ptrEnd,
            const  char  *  sepChrs,
            TokenArray     &vTokens,
            const  char  *  delChrs);

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
    friend  class   TextParserTest;
};

}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END

#endif
