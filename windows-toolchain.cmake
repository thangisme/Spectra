# Toolchain file for finding cross-compiled SDL2 for Windows

# Specify the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# Specify the target architecture
SET(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the cross compiler
SET(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)

# Specify the root directory for the target platform
SET(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32 ${CMAKE_SOURCE_DIR}/zlib  ${CMAKE_SOURCE_DIR}/SDL2)

# Tell CMake to search for libraries and headers only in the target root directory
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

