
project(urtcenginedemoarm64)
cmake_minimum_required(VERSION 3.5)

#SET(CROSS_COMPILE 1)

#IF(CROSS_COMPILE)
#SET(TOOLCHAIN_DIR "/path/to/compile-toolchain/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu")
#set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-g++)
#set(CMAKE_C_COMPILER   ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-gcc)

#SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_DIR}
# ${TOOLCHAIN_DIR}/include
# ${TOOLCHAIN_DIR}/lib )
#ENDIF(CROSS_COMPILE)

set(CMAKE_BUILD_TYPE "release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -o3 -fpermissive -fPIC")
set(ENGINEDEMO_LDFLAGS "-Wl,-rpath ")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(THIRDPARTY ${PROJECT_SOURCE_DIR}/third_party)
set(RAPIDJSON ${THIRDPARTY}/rapidjson/include)
set(URTC_MEDIA_PATH ${PROJECT_SOURCE_DIR}/urtclib/interface)
set(URTC_MEDIA_LIB ${PROJECT_SOURCE_DIR}/urtclib/lib)
#set(URTC_SHARED_LIB ${TOOLCHAIN_DIR}/aarch64-linux-gnu/lib)


aux_source_directory(
  ${PROJECT_SOURCE_DIR}/
  SRCS
)

include_directories(
  ${PROJECT_SOURCE_DIR}
)

include_directories(
  ${URTC_MEDIA_PATH}
  ${RAPIDJSON}
)

link_directories(
  ${URTC_MEDIA_LIB}
  #  ${URTC_SHARED_LIB}
)

set (ALL_LDFLAGS
  ${ENGINEDEMO_LDFLAGS}
)

link_libraries(
    "liburtcmediaengine.so"
)

add_executable(enginedemo ${SRCS})
target_link_libraries(enginedemo dl pthread stdc++)
