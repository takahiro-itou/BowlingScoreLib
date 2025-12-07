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
**      An Implementation of TextParser class.
**
**      @file       Common/TextParser.cpp
**/

#include    "BowlingScore/Common/TextParser.h"

#include    <cstring>


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    TextParser  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

TextParser::TextParser()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

TextParser::~TextParser()
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
//    文字列を指定した文字で分割する。
//

ErrCode
TextParser::splitText(
        const  std::string  &inText,
        const  char  *      sepChrs,
        TextBuffer          &bufText,
        TokenArray          &vTokens,
        const  char  *      delChrs)
{
    const   size_t  szText  = inText.size();
    bufText.clear();
    bufText.resize(szText + 1);
    char  *  const  ptrBuf  = &(bufText[0]);

    memcpy(ptrBuf, inText.c_str(), szText);
    ptrBuf[szText]  = '\0';

    return  splitTextSub(ptrBuf, ptrBuf + szText, sepChrs, vTokens, delChrs);
}

//----------------------------------------------------------------
//    末尾の空白を削除する。
//

char  *
TextParser::stripRight(
        char  *  const  ptrBuf,
        const  char  *  delChrs)
{
    char *  pp  = ptrBuf + strlen(ptrBuf) - 1;
    while ( (pp >= ptrBuf) && (strchr(delChrs, *pp) != NULL) ) {
        (* pp)  = '\0';
        -- pp;
    }
    return ( ptrBuf );
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
TextParser::splitTextSub(
        char  *  const  ptrBuf,
        char  *  const  ptrEnd,
        const  char  *  sepChrs,
        TokenArray     &vTokens,
        const  char  *  delChrs)
{
    char  *         pWrite  = nullptr;
    char  *         pToken  = ptrBuf;
    const  int      cqBegin = '"';
    const  int      cqEnd   = '"';
    int             cqLevel = 0;

    for ( char * p = ptrBuf; p < ptrEnd; ++ p ) {
        const  int  ch  = static_cast<unsigned char>(*p);
        if ( cqLevel > 0 ) {
            if ( ch == cqEnd ) {
                if ( pWrite == nullptr ) {
                    pWrite  = p;
                }
                -- cqLevel;
            }
            continue;
        }
        if ( ch == cqBegin ) {
            if ( p == pToken ) {
                //  トークンの先頭にクォートがある場合は、  //
                //  そのクォートを削除するため、            //
                //  トークンの開始位置を調整する。          //
                pToken  = p + 1;
            } else if ( pWrite == nullptr ) {
                pWrite  = p;
            }
            ++ cqLevel;
            continue;
        }
        if ( strchr(sepChrs, ch) != NULL ) {
            //  区切り文字（のいずれか）なので、ここで区切る。  //
            *p  = '\0';
            if ( pWrite != nullptr ) {
                *pWrite = '\0';
            }
            if ( delChrs != nullptr ) {
                vTokens.push_back(stripRight(pToken, delChrs));
            } else {
                vTokens.push_back(pToken);
            }

            pToken  = p + 1;
            pWrite  = nullptr;
        }
        if ( pWrite != nullptr ) {
            *pWrite = *p;
            ++ pWrite;
        }
    }

    //  最後の区切り文字以降の分があるのでそれを追加する。  //
    //  ちょうど文字列の末尾が区切り文字だった場合は、      //
    //  最後に空文字列があるものとして追加する必要がある。  //
    if ( delChrs != nullptr ) {
        vTokens.push_back(stripRight(pToken, delChrs));
    } else {
        vTokens.push_back(pToken);
    }

    return ( ErrCode::SUCCESS );
}

}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END
