cmake_minimum_required(VERSION 3.10)
project(CriminalMindPP)

# Configurar o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adicionar todos os arquivos fonte
set(SOURCES
    main.cpp
    Game.cpp
    Suspeito.cpp
    Pista.cpp
    Engine.cpp
    Achievement.cpp
    CaseEditor.cpp
)

# Adicionar todos os arquivos de cabeçalho
set(HEADERS
    Game.hpp
    Suspeito.hpp
    Pista.hpp
    Engine.hpp
    Achievement.hpp
    CaseEditor.hpp
    utils.hpp
)

# Criar o executável
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Configurar flags de compilação
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Configurar diretório de saída
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Copiar arquivos de dados e sons para o diretório de saída
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/sounds DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/casos_exportados) 