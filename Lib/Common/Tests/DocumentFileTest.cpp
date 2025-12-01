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

    for ( FrameNumber j = 0; j < 9; ++ j ) {
        const   FrameScore  &fs = objDoc.getFrameScore(0, j);
        CPPUNIT_ASSERT_EQUAL(fs.check, fs.score);
        CPPUNIT_ASSERT_EQUAL((j + 1) * 30, fs.score);
    }

    return;
}

void  DocumentFileTest::testSaveToTextStream()
{
    Testee          testee;
    ScoreDocument   objDoc;

    std::stringstream   ss;
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS,
            testee.saveToTextStream(objDoc, ss)
    );

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
