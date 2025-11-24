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
**      @file       Common/SampleSettings.h
**/

#if !defined( BOWLING_SCORE_COMMON_INCLUDED_SAMPLE_SETTINGS_H )
#    define   BOWLING_SCORE_COMMON_INCLUDED_SAMPLE_SETTINGS_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if defined( SAMPLE_USE_PRE_CONFIGURED_MSVC )
#    include    "BowlingScore/.Config/PreConfigBowling.msvc.h"
#else
#    include    "BowlingScore/.Config/ConfiguredBowling.h"
#endif

SAMPLE_NAMESPACE_BEGIN

/**
**    ダミーの型宣言。
**/

typedef     int     CommonType;

SAMPLE_NAMESPACE_END

#endif
