cmake_minimum_required(VERSION 3.10)
project(CriminalMind++)

# Configurar o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adicionar todos os arquivos fonte
set(SOURCES
    main.cpp
    Game.cpp
    Suspeito.cpp
    Pista.cpp
)

# Adicionar todos os arquivos de cabeçalho
set(HEADERS
    Game.hpp
    Suspeito.hpp
    Pista.hpp
    utils.hpp
)

# Criar o executável
add_executable(CriminalMind++ ${SOURCES} ${HEADERS})

# Configurar flags de compilação
if(MSVC)
    target_compile_options(CriminalMind++ PRIVATE /W4)
else()
    target_compile_options(CriminalMind++ PRIVATE -Wall -Wextra -pedantic)
endif()

# Configurar diretório de saída
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 