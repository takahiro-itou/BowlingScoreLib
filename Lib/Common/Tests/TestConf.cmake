
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   BowlingSettingsTest
    COMMAND  $<TARGET_FILE:BowlingSettingsTest>
)

add_test(NAME   SampleDocumentTest
    COMMAND  $<TARGET_FILE:SampleDocumentTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(BowlingSettingsTest      BowlingSettingsTest.cpp)
add_executable(SampleDocumentTest       SampleDocumentTest.cpp)
