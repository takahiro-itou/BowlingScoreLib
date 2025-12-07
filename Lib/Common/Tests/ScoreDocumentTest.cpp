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

#include    "ScoreDocumentTest.h"


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
    CPPUNIT_TEST(testComputeScore4);
    CPPUNIT_TEST(testComputeScore5);
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
    void  testComputeScore4();
    void  testComputeScore5();
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

    testee.setNumPlayers(1);
    setupFrameScores(testee, 0, score1);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            300, testee.getFrameScore(0, 9).score);

    testFrameScores(testee, 0, score1);

    return;
}

void  ScoreDocumentTest::testComputeScore2()
{
    Testee  testee;

    testee.setNumPlayers(1);
    setupFrameScores(testee, 0, score2);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            99, testee.getFrameScore(0, 9).score);

    testFrameScores(testee, 0, score2);

    return;
}

void  ScoreDocumentTest::testComputeScore3()
{
    Testee  testee;

    testee.setNumPlayers(1);
    setupFrameScores(testee, 0, score3);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            200, testee.getFrameScore(0, 9).score);

    testFrameScores(testee, 0, score3);

    return;
}

void  ScoreDocumentTest::testComputeScore4()
{
    Testee  testee;

    testee.setNumPlayers(1);
    setupFrameScores(testee, 0, score4);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            200, testee.getFrameScore(0, 9).score);

    testFrameScores(testee, 0, score4);

    return;
}

void  ScoreDocumentTest::testComputeScore5()
{
    Testee  testee;

    testee.setNumPlayers(1);
    setupFrameScores(testee, 0, score5);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.computeScores(0));
    CPPUNIT_ASSERT_EQUAL(
            119, testee.getFrameScore(0, 9).score);

    testFrameScores(testee, 0, score5);

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
