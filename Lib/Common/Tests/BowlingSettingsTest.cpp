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
**      An Implementation of Test Case 'BowlingProject'.
**
**      @file       Common/Tests/BowlingProjectTest.cpp
**/

#include    "TestDriver.h"
#include    "BowlingScore/Common/BowlingProject.h"


BOWLINGSCORE_NAMESPACE_BEGIN

//========================================================================
//
//    BowlingProjectTest  class.
//
/**
**    クラス BowlingProject の単体テスト。
**/

class  BowlingProjectTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(BowlingProjectTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BowlingProjectTest );

//========================================================================
//
//    Tests.
//

void  BowlingProjectTest::testNameSpace()
{
    return;
}

BOWLINGSCORE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
