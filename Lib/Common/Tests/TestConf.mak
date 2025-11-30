
##
##    List of Tests.
##

extra_tests             =
TESTS                   =  \
        BowlingProjectTest      \
        DocumentFileTest        \
        ScoreDocumentTest       \
        ${extra_tests}

##
##    Test Configurations.
##

target_testee_library       +=  -lsampleCommon

dist_noinst_data_files      +=
dist_noinst_header_files    +=
extra_test_drivers          +=
library_test_drivers        +=
source_test_drivers         +=

##
##    Compile and Link Options.
##

test_cppflags_common        +=
test_ldflags_common         +=

##
##    Test Programs.
##

BowlingProjectTest_SOURCES      =  BowlingProjectTest.cpp
DocumentFileTest_SOURCES        =  DocumentFileTest.cpp
ScoreDocumentTest_SOURCES       =  ScoreDocumentTest.cpp
