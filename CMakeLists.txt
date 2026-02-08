cmake_minimum_required(VERSION 3.10)
project(UnauthScoutCpp)

set(CMAKE_CXX_STANDARD 17)

# Dependências
find_package(CURL REQUIRED)

# Arquivos de origem
file(GLOB SOURCES "src/**/*.cpp" "src/main.cpp")
file(GLOB HEADERS "include/**/*.hpp")

# Executável
add_executable(unauthscout ${SOURCES} ${HEADERS})

# Inclua o caminho para os headers
target_include_directories(unauthscout PRIVATE include)

# Linkagem
target_link_libraries(unauthscout PRIVATE CURL::libcurl)
