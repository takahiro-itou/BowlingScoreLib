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
**      プロジェクトの設定。
**
**      @file       Common/BowlingTypes.h
**/

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_BOWLING_TYPES_H )
#    define   BOWLINGSCORE_COMMON_INCLUDED_BOWLING_TYPES_H

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_BOWLING_SETTINGS_H )
#    include    "BowlingProject.h"
#endif

#if !defined( BOWLINGSCORE_SYS_INCLUDED_CSTDINT )
#    include    <cstdint>
#    define   BOWLINGSCORE_SYS_INCLUDED_CSTDINT
#endif

#if !defined( BOWLINGSCORE_SYS_INCLUDED_STDDEF_H )
#    include    <stddef.h>
#    define   BOWLINGSCORE_SYS_INCLUDED_STDDEF_H
#endif


BOWLINGSCORE_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum class  ErrCode
{
    /**   正常終了。    **/
    SUCCESS                 = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    FAILURE                 = 1,

    /**   無効なインデックス指定。  **/
    INDEX_OUT_OF_RANGE      = 2,

    /**   ファイルオープンエラー。  **/
    FILE_OPEN_ERROR         = 3,

    /**   ファイル入出力エラー。    **/
    FILE_IO_ERROR           = 4,

    /**   不正なファイル形式。      **/
    FILE_INVALID_FORMAT     = 5,
};

//----------------------------------------------------------------
/**
**    型安全なブール型。
**/

enum  Boolean
{
    BOOL_FALSE  =  0,       /**<  偽。  **/
    BOOL_TRUE   =  1        /**<  真。  **/
};

//----------------------------------------------------------------
/**
**    プレーヤー番号。
**/

typedef     int         PlayerIndex;


//----------------------------------------------------------------
/**
**    フレーム番号。
**/

typedef     int         FrameNumber;


//----------------------------------------------------------------
/**
**    投球で倒したピンの数、および点数を示す型。
**/

typedef     int         NumPins;


//----------------------------------------------------------------
/**
**    投球後に残ったピン。
**/

typedef     int         RemainPins;


//----------------------------------------------------------------
/**
**    投球結果に関する追加情報のフラグ。
**/

typedef     int         FrameFlags;

namespace  FlagValues  {

enum  {
    NONE        = 0x00000000,

    /**   一投目がスプリットになった。  **/
    SPLIT_1ST   = 0x00000001,

    /**   二投目がスプリットになった。  **/
    SPLIT_2ND   = 0x00000002,

    /**   三投目がスプリットになった。  **/
    SPLIT_3RD   = 0x00000004,

    /**   一投目がガターになった。      **/
    GUTTER_1ST  = 0x00000010,

    /**   二投目がガターになった。      **/
    GUTTER_2ND  = 0x00000020,

    /**   三投目がガターになった。      **/
    GUTTER_3RD  = 0x00000040,

    /**   一投目がファールになった。    **/
    FAUL_1ST    = 0x00000100,

    /**   二投目がファールになった。    **/
    FAUL_2ND    = 0x00000200,

    /**   三投目がファールになった。    **/
    FAUL_3RD    = 0x00000400,

    /**   一投目がミスになった。        **/
    MISS_1ST    = 0x00001000,

    /**   二投目がミスになった。        **/
    MISS_2ND    = 0x00002000,

    /**   三投目がミスになった。        **/
    MISS_3RD    = 0x00004000,
};

};


//----------------------------------------------------------------
/**
**    スコアに関する定数。
**/

enum  {
    NUM_PINS_PER_FRAME  = 10,
    NUM_FRAMES          = 10,
    FRAME_ARRAY_SIZE    = NUM_FRAMES + 1,
};


//----------------------------------------------------------------
/**
**    フレームデータ。
**
**    最終10フレームの三投目は11フレームの１投目として扱う。
**/

struct  FrameScore
{
    NumPins     got1st;     /**<  一投目で倒したピンの数。  **/
    NumPins     got2nd;     /**<  二投目で倒したピンの数。  **/

    RemainPins  rem1st;     /**<  一投目投球後の残りピン。  **/
    RemainPins  rem2nd;     /**<  二投目投球後の残りピン。  **/

    NumPins     score;      /**<  このフレームの点数。      **/
    NumPins     check;      /**<  点数のチェック用に記録された値。  **/

    FrameFlags  flags;      /**<  その他のフラグ。          **/
};

typedef     FrameScore  FrameArray[FRAME_ARRAY_SIZE];


//========================================================================
//
//    安全なポインタ型のキャスト。
//

template  <typename  T>
T  pointer_cast(void  *  p)
{
    return ( static_cast<T>(p) );
}

template  <typename  T>
T  pointer_cast(const  void  *  p)
{
    return ( static_cast<T>(p) );
}


//========================================================================
/**
**    配列の要素数を取得する補助関数。
**/

template  <typename  T,  size_t  N>
CONSTEXPR_FUNC
size_t  getArraySize(T (&)[N])
{
    return ( N );
}


BOWLINGSCORE_NAMESPACE_END

#endif
