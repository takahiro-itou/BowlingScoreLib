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
    { 10,  0, 0x000, 0x000,   0,  30 },
    { 10,  0, 0x000, 0x000,   0,  60 },
    { 10,  0, 0x000, 0x000,   0,  90 },
    { 10,  0, 0x000, 0x000,   0, 120 },
    { 10,  0, 0x000, 0x000,   0, 150 },
    { 10,  0, 0x000, 0x000,   0, 180 },
    { 10,  0, 0x000, 0x000,   0, 210 },
    { 10,  0, 0x000, 0x000,   0, 240 },
    { 10,  0, 0x000, 0x000,   0, 270 },
    { 10, 10, 0x000, 0x000,   0, 300 },
    { 10,  0, 0x000, 0x000,   0, 300 },
};

CONSTEXPR_VAR
FrameArray  score2 = {
    { 10,  0, 0x000, 0x000,   0,  21 },
    { 10,  0, 0x000, 0x000,   0,  32 },
    {  1,  0, 0x3FE, 0x3FE,   0,  33 },
    { 10,  0, 0x000, 0x000,   0,  44 },
    {  1,  0, 0x3FE, 0x3FE,   0,  45 },
    { 10,  0, 0x000, 0x000,   0,  56 },
    {  1,  0, 0x3FE, 0x3FE,   0,  57 },
    { 10,  0, 0x000, 0x000,   0,  68 },
    {  1,  0, 0x3FE, 0x3FE,   0,  69 },
    { 10, 10, 0x000, 0x000,   0,  99 },
    { 10,  0, 0x000, 0x000,   0,  99 },
};

CONSTEXPR_VAR
FrameArray  score3 = {
    { 10,  0, 0x000, 0x000,   0,  20 },
    {  9,  1, 0x400, 0x000,   0,  40 },
    { 10,  0, 0x000, 0x000,   0,  60 },
    {  9,  1, 0x400, 0x000,   0,  80 },
    { 10,  0, 0x000, 0x000,   0, 100 },
    {  9,  1, 0x400, 0x000,   0, 120 },
    { 10,  0, 0x000, 0x000,   0, 140 },
    {  9,  1, 0x400, 0x000,   0, 160 },
    { 10,  0, 0x000, 0x000,   0, 180 },
    {  9,  1, 0x400, 0x000,   0, 200 },
    { 10,  0, 0x000, 0x000,   0, 200 },
};

CONSTEXPR_VAR
FrameArray  score4 = {
    {  9,  1, 0x400, 0x000,   0,  20 },
    { 10,  0, 0x000, 0x000,   0,  40 },
    {  9,  1, 0x400, 0x000,   0,  60 },
    { 10,  0, 0x000, 0x000,   0,  80 },
    {  9,  1, 0x400, 0x000,   0, 100 },
    { 10,  0, 0x000, 0x000,   0, 120 },
    {  9,  1, 0x400, 0x000,   0, 140 },
    { 10,  0, 0x000, 0x000,   0, 160 },
    {  9,  1, 0x400, 0x000,   0, 180 },
    { 10,  9, 0x000, 0x400,   0, 200 },
    {  1,  0, 0x000, 0x000,   0, 200 },
};


inline  void
setupFrameScores(
        ScoreDocument      &objDoc,
        const  PlayerIndex  player,
        const  FrameScore (&scores)[11])
{
    CONSTEXPR_VAR   FrameNumber
            NUM_FRAMES  = sizeof(FrameArray) / sizeof(FrameScore);

    for ( FrameNumber j = 0; j < NUM_FRAMES; ++ j ) {
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
        const  FrameScore (&scores)[11])
{
    CONSTEXPR_VAR   FrameNumber
            NUM_FRAMES  = sizeof(FrameArray) / sizeof(FrameScore);


    for ( FrameNumber j = 0; j < NUM_FRAMES; ++ j ) {
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
