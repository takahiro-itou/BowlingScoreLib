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

    FrameScore  s01 = { 10, 0, 0, 0, 0, 0, 0, 30 };
    FrameScore  s10 = { 10, 10, 10, 0, 0, 0, 0, 300 };

    testee.setNumPlayers(1);
    for ( int i = 0; i < 9; ++ i ) {
        s01.check   = (i + 1) * 30;
        CPPUNIT_ASSERT_EQUAL(
                ErrCode::SUCCESS, testee.setFrameScore(0, i, s01));
    }
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 9, s10));

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            300, testee.getFrameScore(0, 9).score);

    for ( int i = 0; i < 10; ++ i ) {
        const   FrameScore  &fs = testee.getFrameScore(0, i);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL((i + 1) * 30, fs.score);
    }

    return;
}

void  ScoreDocumentTest::testComputeScore2()
{
    Testee  testee;

    FrameScore  s1 = {  9, 1, 0, 0, 0, 0, 0, 0 };
    FrameScore  s2 = { 10, 0, 0, 0, 0, 0, 0, 0 };
    FrameScore  s3 = { 10, 9, 1, 0, 0, 0, 0, 200 };

    testee.setNumPlayers(1);
    for ( int i = 0; i < 9; ++ i ) {
        s1.check    = (i + 1) * 20;
        s2.check    = (i + 1) * 20;
        if ( i & 1 ) {
            CPPUNIT_ASSERT_EQUAL(
                    ErrCode::SUCCESS, testee.setFrameScore(0, i, s2));
        } else {
            CPPUNIT_ASSERT_EQUAL(
                    ErrCode::SUCCESS, testee.setFrameScore(0, i, s1));
        }
    }
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 9, s3));

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            200, testee.getFrameScore(0, 9).score);

    for ( int i = 0; i < 10; ++ i ) {
        const   FrameScore  &fs = testee.getFrameScore(0, i);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL((i + 1) * 20, fs.score);
    }

    return;
}

void  ScoreDocumentTest::testComputeScore3()
{
    Testee  testee;

    FrameScore  s01 = { 10, 0, 0, 0x000, 0x000, 0, 0, 21 };
    FrameScore  s02 = { 10, 0, 0, 0x000, 0x000, 0, 0, 32 };
    FrameScore  s03 = {  1, 0, 0, 0x7FE, 0x7FE, 0, 0, 33 };
    FrameScore  s04 = { 10, 0, 0, 0x000, 0x000, 0, 0, 44 };
    FrameScore  s05 = {  1, 0, 0, 0x7FE, 0x7FE, 0, 0, 45 };
    FrameScore  s06 = { 10, 0, 0, 0x000, 0x000, 0, 0, 56 };
    FrameScore  s07 = {  1, 0, 0, 0x7FE, 0x7FE, 0, 0, 57 };
    FrameScore  s08 = { 10, 0, 0, 0x000, 0x000, 0, 0, 68 };
    FrameScore  s09 = {  1, 0, 0, 0x7FE, 0x7FE, 0, 0, 69 };
    FrameScore  s10 = { 10, 10, 10, 0, 0, 0, 0, 99 };

    testee.setNumPlayers(1);
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 0, s01));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 1, s02));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 2, s03));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 3, s04));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 4, s05));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 5, s06));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 6, s07));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 7, s08));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 8, s09));
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.setFrameScore(0, 9, s10));

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            99, testee.getFrameScore(0, 9).score);

    for ( int i = 0; i < 10; ++ i ) {
        const   FrameScore  &fs = testee.getFrameScore(0, i);
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
