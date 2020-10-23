cmake_minimum_required(VERSION 3.13)

# Путь к компилятору явным образом указывать не надо, т.к. он будет взят из настроек QtCreator.
# Если всё-таки нужно явно указать какой компилятор использовать, то надо делать как написано здесь (1 или 2 способ):
# https://gitlab.kitware.com/cmake/community/wikis/FAQ#how-do-i-use-a-different-compiler
# Если вы используете Qt Creator, то компилятор будет взять из его настроек. В противном
# случае вы можете его установить одним из способов по ссылке выше.

# Ваш компилятор может не поддерживать C++17 и в таком случае можно прописать 14 или 11.
set(CMAKE_CXX_STANDARD 17)
# Отображать все предупреждения в процессе компиляции.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# Искать инклуды также и в текущей директории.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(passwordgen)

# Для macOS добавляем путь до папки с установленным Qt 5.
set(QTPATH /usr/local/opt/qt)
if (APPLE AND EXISTS ${QTPATH})
    list(APPEND CMAKE_PREFIX_PATH ${QTPATH})
endif()

set(SOURCES
    main.cpp
    passwordgenerator.h
    passwordgenerator.cpp
    argparser.h
    argparser.cpp
    alphabet.h
    alphabet.cpp
    errors.h
)

find_package(Qt5Core CONFIG REQUIRED)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(passwordgen Qt5::Core)
