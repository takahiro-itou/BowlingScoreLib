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
**      An Implementation of Test Case 'DocumentFile'.
**
**      @file       Common/Tests/DocumentFileTest.cpp
**/

#include    "TestDriver.h"
#include    "BowlingScore/Common/DocumentFile.h"

#include    "ScoreDocumentTest.h"

#include    "BowlingScore/Common/ScoreDocument.h"


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    DocumentFileTest  class.
//
/**
**    クラス DocumentFile の単体テスト。
**/

class  DocumentFileTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(DocumentFileTest);
    CPPUNIT_TEST(testCtor);
    CPPUNIT_TEST(testReadFromTextStream);
    CPPUNIT_TEST(testSaveToTextStream);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCtor();
    void  testReadFromTextStream();
    void  testSaveToTextStream();

    typedef     DocumentFile    Testee;
};

CPPUNIT_TEST_SUITE_REGISTRATION( DocumentFileTest );

//========================================================================
//
//    Tests.
//

void  DocumentFileTest::testCtor()
{
    Testee  testee;

    return;
}

void  DocumentFileTest::testReadFromTextStream()
{
    Testee          testee;
    ScoreDocument   objDoc;

    std::stringstream   ss;

    ss  <<
#include    "SampleData.md"
    ;
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS,
            testee.readFromTextStream(ss, &objDoc)
    );

    const  PlayerIndex  numPlayers  = 4;

    CPPUNIT_ASSERT_EQUAL(
            std::string("2025/11/30"), objDoc.getGameDate());
    CPPUNIT_ASSERT_EQUAL(
            std::string("TITLE of GAME"), objDoc.getGameTitle());
    CPPUNIT_ASSERT_EQUAL(
            numPlayers, objDoc.getNumPlayers());

    CPPUNIT_ASSERT_EQUAL(
            std::string("TEST PLAYER 1"), objDoc.getPlayerName(0));
    CPPUNIT_ASSERT_EQUAL(
            std::string("TEST PLAYER 2"), objDoc.getPlayerName(1));
    CPPUNIT_ASSERT_EQUAL(
            std::string("TEST PLAYER 3"), objDoc.getPlayerName(2));
    CPPUNIT_ASSERT_EQUAL(
            std::string("TEST PLAYER 4"), objDoc.getPlayerName(3));

    CPPUNIT_ASSERT_EQUAL(
            300, objDoc.getFrameScore(0, 9).score);
    CPPUNIT_ASSERT_EQUAL(
            99,  objDoc.getFrameScore(1, 9).score);
    CPPUNIT_ASSERT_EQUAL(
            200, objDoc.getFrameScore(2, 9).score);
    CPPUNIT_ASSERT_EQUAL(
            119, objDoc.getFrameScore(3, 9).score);

    testFrameScores(objDoc, 0, score1);
    testFrameScores(objDoc, 1, score2);
    testFrameScores(objDoc, 2, score3);
    testFrameScores(objDoc, 3, score5);

    return;
}

void  DocumentFileTest::testSaveToTextStream()
{
    Testee          testee;
    ScoreDocument   objDoc;

    objDoc.setNumPlayers(4);

    objDoc.setGameTitle("TITLEofGAME");
    objDoc.setGameDate("2025/11/30");
    objDoc.setPlayerName(0, "TESTPLAYER1");
    objDoc.setPlayerName(1, "TESTPLAYER2");
    objDoc.setPlayerName(2, "TESTPLAYER3");
    objDoc.setPlayerName(3, "TESTPLAYER4");

    setupFrameScores(objDoc, 0, score1);
    setupFrameScores(objDoc, 1, score2);
    setupFrameScores(objDoc, 2, score4);
    setupFrameScores(objDoc, 3, score5);

    objDoc.computeScores(0);
    objDoc.computeScores(1);
    objDoc.computeScores(2);
    objDoc.computeScores(3);

    std::stringstream   ss;
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS,
            testee.saveToTextStream(objDoc, ss)
    );

    const  std::string  expect(
#include    "SampleExpect.md"
    );
    std::cerr   <<  "\nExpect:\n"
                <<  expect
                <<  "---  Size = "
                <<  expect.size()
                <<  std::endl;

    const  std::string  buf = ss.str();
    std::cerr   <<  "\nOutput Stream:\n"
                <<  buf
                <<  "---  Size = "
                <<  buf.size()
                <<  std::endl;

    std::stringstream   ssAct(buf);
    std::stringstream   ssExp(expect);
    int i = 0;
    for ( ; ; ++ i ) {
        std::string     exp, act;
        if ( ! std::getline(ssExp, exp).good() ) {
            break;
        }
        std::getline(ssAct, act);

        if ( ! ssAct.good() || (exp != act) ) {
            std::cerr   <<  "Test FAILED at "  <<  (i + 1)  <<  std::endl;
        }
        CPPUNIT_ASSERT_EQUAL(exp, act);
    }
    std::cerr   <<  "Tested "  <<  i  <<  " lines.\n";

    CPPUNIT_ASSERT_EQUAL(expect, buf);

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
