
# demo  test
add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
target_link_libraries(test pthread uv public)

# demo  crash
add_executable(crash ${CMAKE_CURRENT_SOURCE_DIR}/crash.c)
target_link_libraries(crash pthread uv unwind public)

# demo  nanomsg  push/pull
add_executable(pushpull ${CMAKE_CURRENT_SOURCE_DIR}/pushpull.c)
target_link_libraries(pushpull pthread uv public)

# demo  nanomsg  survey
add_executable(survey ${CMAKE_CURRENT_SOURCE_DIR}/survey.c)
target_link_libraries(survey pthread uv public)
