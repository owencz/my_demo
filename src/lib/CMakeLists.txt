
# public 库构建
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/crash SRC_CRASH)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/elog SRC_ELOG)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/kernel SRC_KERNEL)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/nio SRC_NIO)

add_library(public STATIC ${SRC_ELOG} 
							${SRC_KERNEL} 
							${SRC_NIO}
							${SRC_CRASH})

target_include_directories(public PUBLIC
							${CMAKE_CURRENT_SOURCE_DIR}/crash
							${CMAKE_CURRENT_SOURCE_DIR}/elog
							${CMAKE_CURRENT_SOURCE_DIR}/kernel
							${CMAKE_CURRENT_SOURCE_DIR}/nio)

target_link_libraries(public PRIVATE pthread uv nanomsg unwind)
