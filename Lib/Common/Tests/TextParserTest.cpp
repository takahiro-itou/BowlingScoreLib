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
**      An Implementation of Test Case 'TextParser'.
**
**      @file       Common/Tests/TextParserTest.cpp
**/

#include    "TestDriver.h"
#include    "BowlingScore/Common/TextParser.h"


BOWLINGSCORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    TextParserTest  class.
//
/**
**    クラス TextParser の単体テスト。
**/

class  TextParserTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(TextParserTest);
    CPPUNIT_TEST(testCtor);
    CPPUNIT_TEST(testSplitText1);
    CPPUNIT_TEST(testSplitText2);
    CPPUNIT_TEST(testSplitText3);
    CPPUNIT_TEST(testSplitText4);
    CPPUNIT_TEST(testSplitText5);
    CPPUNIT_TEST(testSplitText6);
    CPPUNIT_TEST(testStripRight);
    CPPUNIT_TEST(testSubSplit1);
    CPPUNIT_TEST(testSubSplit2);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCtor();
    void  testSplitText1();
    void  testSplitText2();
    void  testSplitText3();
    void  testSplitText4();
    void  testSplitText5();
    void  testSplitText6();
    void  testStripRight();
    void  testSubSplit1();
    void  testSubSplit2();

    typedef     TextParser      Testee;
};

CPPUNIT_TEST_SUITE_REGISTRATION( TextParserTest );

//========================================================================
//
//    Tests.
//

void  TextParserTest::testCtor()
{
    Testee  testee;
    return;
}

void  TextParserTest::testSplitText1()
{
    Testee  testee;
    Testee::TextBuffer  bufText;
    Testee::TokenArray  vTokens;

    ErrCode retCode;
    retCode = testee.splitText(
                    "abc;def;;g;h;i", ";", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(6),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string("g"),   std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string("i"),   std::string(vTokens[5]) );

    return;
}

void  TextParserTest::testSplitText2()
{
    Testee  testee;
    Testee::TextBuffer  bufText;
    Testee::TokenArray  vTokens;

    ErrCode retCode;
    retCode = testee.splitText(
                    "abc;def;;g;h;i;", ";", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(7),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string("g"),   std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string("i"),   std::string(vTokens[5]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[6]) );

    return;
}

void  TextParserTest::testSplitText3()
{
    Testee  testee;
    Testee::TextBuffer  bufText;
    Testee::TokenArray  vTokens;

    ErrCode retCode;
    retCode = testee.splitText(
                    ";abc;def;;g;h;i", ";", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(7),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string("g"),   std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[5]) );
    CPPUNIT_ASSERT_EQUAL( std::string("i"),   std::string(vTokens[6]) );

    return;
}

void  TextParserTest::testSplitText4()
{
    Testee  testee;
    Testee::TextBuffer  bufText;
    Testee::TokenArray  vTokens;

    ErrCode retCode;
    retCode = testee.splitText(
                    "abc,\"123,456\",,def,,h", ",", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(6),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("123,456"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[5]) );

    return;
}

void  TextParserTest::testSplitText5()
{
    Testee  testee;
    Testee::TextBuffer  bufText;
    Testee::TokenArray  vTokens;

    ErrCode retCode;
    retCode = testee.splitText(
                    "abc,\"123,456\",,def,,h,", ",", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(7),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("123,456"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[5]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[6]) );

    return;
}

void  TextParserTest::testSplitText6()
{
    Testee  testee;
    Testee::TextBuffer  bufText;
    Testee::TokenArray  vTokens;

    ErrCode retCode;
    retCode = testee.splitText(
                    ",abc,\"123,456\",,def,,h,", ",", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(8),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string("123,456"), std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[5]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[6]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[7]) );

    return;
}

void  TextParserTest::testStripRight()
{
    Testee  testee;

    char    buf[] = "1,2,3, \0";
    const  char  *  ptr;

    ptr = testee.stripRight(buf);

    CPPUNIT_ASSERT_EQUAL( (const void *)(ptr), (const void *)(buf) );
    CPPUNIT_ASSERT_EQUAL( std::string("1,2,3,"), std::string(buf) );
    CPPUNIT_ASSERT_EQUAL( std::string("1,2,3,"), std::string(ptr) );

    return;
}

void  TextParserTest::testSubSplit1()
{
    Testee  testee;
    Testee::TextBuffer  bufText1;
    Testee::TokenArray  vTokens1;

    Testee::TextBuffer  bufText2;
    Testee::TokenArray  vTokens2;

    ErrCode retCode;
    retCode = testee.splitText(
                    "1,2, |str,, |* | |", "|", bufText1, vTokens1);

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(5),
            static_cast<size_t>(vTokens1.size()) );

    retCode = testee.splitText(
                    vTokens1[1], ",", bufText2, vTokens2);
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(3),
            static_cast<size_t>(vTokens2.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("1,2, "),  std::string(vTokens1[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("str,, "), std::string(vTokens1[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string("* "),     std::string(vTokens1[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string(" "),      std::string(vTokens1[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),       std::string(vTokens1[4]) );

    CPPUNIT_ASSERT_EQUAL( std::string("str"),  std::string(vTokens2[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),     std::string(vTokens2[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(" "),    std::string(vTokens2[2]) );

    return;
}

void  TextParserTest::testSubSplit2()
{
    Testee  testee;
    Testee::TextBuffer  bufText1;
    Testee::TokenArray  vTokens1;

    Testee::TextBuffer  bufText2;
    Testee::TokenArray  vTokens2;

    ErrCode retCode;
    retCode = testee.splitText(
                    "1,2, |str,, |* | |", "|", bufText1, vTokens1, " ");

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(5),
            static_cast<size_t>(vTokens1.size()) );

    retCode = testee.splitText(
                    vTokens1[1], ",", bufText2, vTokens2);
    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, retCode);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(3),
            static_cast<size_t>(vTokens2.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("1,2,"),  std::string(vTokens1[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("str,,"), std::string(vTokens1[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string("*"),     std::string(vTokens1[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),      std::string(vTokens1[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),      std::string(vTokens1[4]) );

    CPPUNIT_ASSERT_EQUAL( std::string("str"),  std::string(vTokens2[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),     std::string(vTokens2[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),     std::string(vTokens2[2]) );

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
