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

    FrameScore  fs3[10] = {
        { 10, 0, 0x000, 0x000,  0, 21 },
        { 10, 0, 0x000, 0x000,  0, 32 },
        {  1, 0, 0x7FE, 0x7FE,  0, 33 },
        { 10, 0, 0x000, 0x000,  0, 44 },
        {  1, 0, 0x7FE, 0x7FE,  0, 45 },
        { 10, 0, 0x000, 0x000,  0, 56 },
        {  1, 0, 0x7FE, 0x7FE,  0, 57 },
        {  1, 0, 0x7FE, 0x7FE,  0, 69 },
        { 10,10, 0x000, 0x000,  0, 99 },
        { 10, 0, 0x000, 0x000, 99, 99 },
    };

    std::stringstream   ss;

    ss  <<
#include    "SampleData.md"
        <<  "\n";
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS,
            testee.readFromTextStream(ss, &objDoc)
    );

    const  PlayerIndex  numPlayers  = 3;

    CPPUNIT_ASSERT_EQUAL(
            std::string("2025/11/30"), objDoc.getGameDate());
    CPPUNIT_ASSERT_EQUAL(
            std::string("TITLE of GAME"), objDoc.getGameTitle());
    CPPUNIT_ASSERT_EQUAL(
            numPlayers, objDoc.getNumPlayers());

    for ( FrameNumber j = 0; j < 10; ++ j ) {
        const   FrameScore  &fs = objDoc.getFrameScore(0, j);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL((j + 1) * 30, fs.score);
        CPPUNIT_ASSERT_EQUAL(10, fs.got1st);
        CPPUNIT_ASSERT_EQUAL( 0, fs.got2nd);
        CPPUNIT_ASSERT_EQUAL( 0, fs.rem1st);
        CPPUNIT_ASSERT_EQUAL( 0, fs.rem2nd);
    }

    for ( FrameNumber j = 0; j < 10; ++ j ) {
        const   FrameScore  &fs = objDoc.getFrameScore(1, j);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL((j + 1) * 20, fs.score);
    }

    for ( FrameNumber j = 0; j <= 10; ++ j ) {
        const   FrameScore  &fs = objDoc.getFrameScore(1, j);
        CPPUNIT_ASSERT_EQUAL(fs.check,  fs.score);
        CPPUNIT_ASSERT_EQUAL(fs3[j].check, fs.score);
        CPPUNIT_ASSERT_EQUAL(fs3[j].got1st, fs.got1st);
        CPPUNIT_ASSERT_EQUAL(fs3[j].got2nd, fs.got2nd);
        CPPUNIT_ASSERT_EQUAL(fs3[j].rem1st, fs.rem1st);
        CPPUNIT_ASSERT_EQUAL(fs3[j].rem2nd, fs.rem2nd);
    }
    return;
}

void  DocumentFileTest::testSaveToTextStream()
{
    Testee          testee;
    ScoreDocument   objDoc;

    objDoc.setNumPlayers(3);

    setupFrameScores(objDoc, 0, score1);
    setupFrameScores(objDoc, 1, score2);
    setupFrameScores(objDoc, 2, score3);

    std::stringstream   ss;
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS,
            testee.saveToTextStream(objDoc, ss)
    );

    const  std::string  buf = ss.str();
    std::cerr   <<  "\nOutput Stream:\n"
                <<  buf
                <<  std::endl;

    const  std::string  expect(
#include    "SampleData.md"
    );
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
