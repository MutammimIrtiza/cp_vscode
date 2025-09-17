@echo off
set SRC=f.cpp
set EXE=a

:: Compile
g++ -std=c++17 -DLOCAL -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Wfloat-equal -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -ggdb3 -fmax-errors=2 %SRC% -o %EXE%
if errorlevel 1 (
    echo Compilation failed!
    exit /b
)

:: Print Input
echo.
echo Input:
type %1
echo.

:: Print Output
echo.
echo Output:
%EXE% < %1
echo.
