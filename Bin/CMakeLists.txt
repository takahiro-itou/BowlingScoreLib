
Include (${common_cmake_dir}/BuildCommon/ConfigTarget.cmake)

add_executable       (ScoreViewer       ScoreViewer.cpp)
target_link_libraries(ScoreViewer       ${project_target_prefix}Common)

install(TARGETS         ScoreViewer
        DESTINATION     ${bintop_dir_name}/
)
