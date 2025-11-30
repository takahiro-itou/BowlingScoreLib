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
