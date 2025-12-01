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

#include    "TestDriver.h"
#include    "BowlingScore/Common/ScoreDocument.h"


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ScoreDocumentTest  class.
//
/**
**    クラス ScoreDocument の単体テスト。
**/

class  ScoreDocumentTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ScoreDocumentTest);
    CPPUNIT_TEST(testCtor);
    CPPUNIT_TEST(testComputeScore1);
    CPPUNIT_TEST(testComputeScore2);
    CPPUNIT_TEST(testComputeScore3);
    CPPUNIT_TEST(testGameDate);
    CPPUNIT_TEST(testGameTitle);
    CPPUNIT_TEST(testNumPlayers);
    CPPUNIT_TEST(testPlayerName);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCtor();
    void  testComputeScore1();
    void  testComputeScore2();
    void  testComputeScore3();
    void  testGameDate();
    void  testGameTitle();
    void  testNumPlayers();
    void  testPlayerName();

    typedef     ScoreDocument   Testee;
};

CPPUNIT_TEST_SUITE_REGISTRATION( ScoreDocumentTest );

//========================================================================
//
//    Tests.
//

void  ScoreDocumentTest::testCtor()
{
    Testee  testee;

    return;
}

void  ScoreDocumentTest::testComputeScore1()
{
    Testee  testee;

    FrameScore  s01 = { 10, 0, 0x000, 0x000, 0, 30 };

    testee.setNumPlayers(1);
    for ( FrameNumber j = 0; j < 10; ++ j ) {
        s01.check   = (j + 1) * 30;
        CPPUNIT_ASSERT_EQUAL(
                ErrCode::SUCCESS, testee.setFrameScore(0, j, s01));
    }
    {
        s01.check   = 300;
        CPPUNIT_ASSERT_EQUAL(
                ErrCode::SUCCESS, testee.setFrameScore(0, 10, s01));
    }

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            300, testee.getFrameScore(0, 9).score);

    for ( FrameNumber j = 0; j < 10; ++ j ) {
        const   FrameScore  &fs = testee.getFrameScore(0, j);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL((j + 1) * 30, fs.score);
    }
    {
        const   FrameScore  &fs = testee.getFrameScore(0, 10);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL(300, fs.score);
    }

    return;
}

void  ScoreDocumentTest::testComputeScore2()
{
    Testee  testee;

    FrameScore  scores[11] = {
        {  9, 1, 0x400, 0x000, 0,  20 },
        { 10, 0, 0x000, 0x000, 0,  40 },
        {  9, 1, 0x400, 0x000, 0,  60 },
        { 10, 0, 0x000, 0x000, 0,  80 },
        {  9, 1, 0x400, 0x000, 0, 100 },
        { 10, 0, 0x000, 0x000, 0, 120 },
        {  9, 1, 0x400, 0x000, 0, 140 },
        { 10, 0, 0x000, 0x000, 0, 160 },
        {  9, 1, 0x400, 0x000, 0, 180 },
        { 10,10, 0x000, 0x000, 0, 200 },
        { 10, 0, 0x000, 0x000, 0, 200 },
    };

    testee.setNumPlayers(1);
    for ( FrameNumber j = 0; j < 11; ++ j ) {
        CPPUNIT_ASSERT_EQUAL(
                ErrCode::SUCCESS, testee.setFrameScore(0, j, scores[j]));
    }

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            200, testee.getFrameScore(0, 9).score);

    for ( FrameNumber j = 0; j < 10; ++ j ) {
        const   FrameScore  &fs = testee.getFrameScore(0, j);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL((j + 1) * 20, fs.score);
    }
    {
        const   FrameScore  &fs = testee.getFrameScore(0, 10);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL(200, fs.score);
    }

    return;
}

void  ScoreDocumentTest::testComputeScore3()
{
    Testee  testee;

    FrameScore  scores[11] = {
        { 10, 0, 0x000, 0x000, 0, 21 },
        { 10, 0, 0x000, 0x000, 0, 32 },
        {  1, 0, 0x7FE, 0x7FE, 0, 33 },
        { 10, 0, 0x000, 0x000, 0, 44 },
        {  1, 0, 0x7FE, 0x7FE, 0, 45 },
        { 10, 0, 0x000, 0x000, 0, 56 },
        {  1, 0, 0x7FE, 0x7FE, 0, 57 },
        { 10, 0, 0x000, 0x000, 0, 68 },
        {  1, 0, 0x7FE, 0x7FE, 0, 69 },
        { 10,10, 0x000, 0x000, 0, 99 },
        { 10, 0, 0x000, 0x000, 0, 99 },
    };

    testee.setNumPlayers(1);
    for ( FrameNumber j = 0; j <= 10; ++ j ) {
        CPPUNIT_ASSERT_EQUAL(
                ErrCode::SUCCESS, testee.setFrameScore(0, j, scores[j]));
    }

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            99, testee.getFrameScore(0, 9).score);

    for ( FrameNumber j = 0; j <= 10; ++ j ) {
        const   FrameScore  &fs = testee.getFrameScore(0, j);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
    }

    return;
}

void  ScoreDocumentTest::testGameDate()
{
    Testee  testee;
    const  std::string  value("2025/11/30");

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setGameDate(value));
    CPPUNIT_ASSERT_EQUAL(value, testee.getGameDate());

    return;
}

void  ScoreDocumentTest::testGameTitle()
{
    Testee  testee;
    const  std::string  value("TITLE of GAME");

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setGameTitle(value));
    CPPUNIT_ASSERT_EQUAL(value, testee.getGameTitle());

    return;
}

void  ScoreDocumentTest::testNumPlayers()
{
    Testee  testee;
    const  PlayerIndex  value = 3;

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setNumPlayers(value));
    CPPUNIT_ASSERT_EQUAL(value, testee.getNumPlayers());

    return;
}

void  ScoreDocumentTest::testPlayerName()
{
    Testee  testee;
    const  std::string  value("TEST PLAYER");

    testee.setNumPlayers(1);

    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS, testee.setPlayerName(0, value));
    CPPUNIT_ASSERT_EQUAL(value, testee.getPlayerName(0));

    return;
}


}   //  End of namespace  Common
BOWLINGSCORE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
