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
**      @file       Common/BowlingSettings.h
**/

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_BOWLING_SETTINGS_H )
#    define   BOWLINGSCORE_COMMON_INCLUDED_BOWLING_SETTINGS_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if !defined( BOWLINGSCORE_CONFIG_INCLUDED_CONFIGURED_BOWLING_H )
#    if defined( BOWLINGSCORE_USE_PRE_CONFIGURED_MSVC )
#        include    "BowlingScore/.Config/PreConfigBowling.msvc.h"
#    else
#        include    "BowlingScore/.Config/ConfiguredBowling.h"
#    endif
#endif

BOWLINGSCORE_NAMESPACE_BEGIN

/**
**    ダミーの型宣言。
**/

typedef     int     CommonType;

BOWLINGSCORE_NAMESPACE_END

#endif
