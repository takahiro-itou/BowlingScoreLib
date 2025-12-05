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
**      An Interface of DocumentFile class.
**
**      @file       Common/DocumentFile.h
**/

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_DOCUMENT_FILE_H )
#    define   BOWLINGSCORE_COMMON_INCLUDED_DOCUMENT_FILE_H

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_BOWLING_TYPES_H )
#    include    "BowlingTypes.h"
#endif


#if !defined( BOWLINGSCORE_SYS_INCLUDED_IOSFWD )
#    include    <iosfwd>
#    define   BOWLINGSCORE_SYS_INCLUDED_IOSFWD
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
class   ScoreDocument;


//========================================================================
//
//    DocumentFile  class.
//

class  DocumentFile
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     std::vector<char>           TextBuffer;

    typedef     std::vector<const char *>   TokenArray;


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
    DocumentFile();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~DocumentFile();

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
    /**   データをテキストファイルから読み込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @param[out] ptrDoc      ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    readFromTextFile(
            const  std::string  &fileName,
            ScoreDocument  *    ptrDoc);

    //----------------------------------------------------------------
    /**   データをテキストストリームから読み込む。
    **
    **  @param [in,out] inStr     入力ストリーム。
    **  @param    [out] ptrDoc    ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    readFromTextStream(
            std::istream       &inStr,
            ScoreDocument  *    ptrDoc);

    //----------------------------------------------------------------
    /**   データをテキストファイルに書き込む。
    **
    **  @param [in] objDoc      ドキュメント。
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    saveToTextFile(
            const  ScoreDocument   & objDoc,
            const  std::string     & fileName);

    //----------------------------------------------------------------
    /**   データをテキストストリームに書き込む。
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param[out] outStr    出力ストリーム。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    saveToTextStream(
            const  ScoreDocument   & objDoc,
            std::ostream           & outStr);

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
    **  @param [in] inText    入力テキスト。
    **  @param [in] sepChrs   区切り文字。
    **  @param[out] bufText   テキストバッファ。
    **  @param[out] vTokens   分割結果を追記する変数。
    **      必要なら呼び出す前に内容をクリアする。
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
            TokenArray          &vTokens);

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
    friend  class   DocumentFileTest;
};

}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END

#endif
