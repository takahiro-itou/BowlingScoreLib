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
**      An Implementation of Test Case 'ScoreDocument'.
**
**      @file       Common/Tests/ScoreDocumentTest.cpp
**/

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_SCORE_DOCUMENT_TEST_H )
#    define   BOWLINGSCORE_COMMON_INCLUDED_SCORE_DOCUMENT_TEST_H

#if !defined( BOWLINGSCORE_COMMON_INCLUDED_SCORE_DOCUMENT_H )
#    include    "BowlingScore/Common/ScoreDocument.h"
#endif


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {


CONSTEXPR_VAR
FrameArray  score1 = {
    { 10,  0, 0x000, 0x000,   0,  30, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  60, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  90, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 120, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 150, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 180, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 210, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 240, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 270, 0x00000000 },
    { 10, 10, 0x000, 0x000,   0, 300, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 300, 0x00000000 },
};

CONSTEXPR_VAR
FrameArray  score2 = {
    { 10,  0, 0x000, 0x000,   0,  21, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  32, 0x00000000 },
    {  1,  0, 0x3FE, 0x3FE,   0,  33, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  44, 0x00000000 },
    {  1,  0, 0x3FE, 0x3FE,   0,  45, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  56, 0x00000000 },
    {  1,  0, 0x3FE, 0x3FE,   0,  57, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  68, 0x00000000 },
    {  1,  0, 0x3FE, 0x3FE,   0,  69, 0x00000000 },
    { 10, 10, 0x000, 0x000,   0,  99, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  99, 0x00000000 },
};

CONSTEXPR_VAR
FrameArray  score3 = {
    { 10,  0, 0x000, 0x000,   0,  20, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0,  40, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  60, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0,  80, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 100, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0, 120, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 140, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0, 160, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 180, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0, 200, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 200, 0x00000000 },
};

CONSTEXPR_VAR
FrameArray  score4 = {
    {  9,  1, 0x400, 0x000,   0,  20, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  40, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0,  60, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0,  80, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0, 100, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 120, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0, 140, 0x00000000 },
    { 10,  0, 0x000, 0x000,   0, 160, 0x00000000 },
    {  9,  1, 0x400, 0x000,   0, 180, 0x00000000 },
    { 10,  9, 0x000, 0x400,   0, 200, 0x00000000 },
    {  1,  0, 0x000, 0x000,   0, 200, 0x00000000 },
};


inline  void
setupFrameScores(
        ScoreDocument      &objDoc,
        const  PlayerIndex  player,
        const  FrameArray  &scores)
{
    for ( FrameNumber j = 0; j < FRAME_ARRAY_SIZE; ++ j ) {
        CPPUNIT_ASSERT_EQUAL(
                ErrCode::SUCCESS,
                objDoc.setFrameScore(player, j, scores[j]));
    }

    return;
}

inline  void
testFrameScores(
        ScoreDocument      &objDoc,
        const  PlayerIndex  player,
        const  FrameArray  &scores)
{
    for ( FrameNumber j = 0; j < FRAME_ARRAY_SIZE; ++ j ) {
        const   FrameScore  &fs = objDoc.getFrameScore(player, j);

        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL(scores[j].got1st, fs.got1st);
        CPPUNIT_ASSERT_EQUAL(scores[j].got2nd, fs.got2nd);
        CPPUNIT_ASSERT_EQUAL(scores[j].rem1st, fs.rem1st);
        CPPUNIT_ASSERT_EQUAL(scores[j].rem2nd, fs.rem2nd);
        CPPUNIT_ASSERT_EQUAL(scores[j].check,  fs.score );
        CPPUNIT_ASSERT_EQUAL(scores[j].check,  fs.check );
    }

    return;
}


}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END

#endif
