@echo off
set SRC=code.cpp
set EXE=a
g++ -std=c++17 -DLOCAL -Wshadow -Wall -g -D_GLIBCXX_DEBUG %SRC% -o %EXE% -fmax-errors=2

if errorlevel 1 (
    echo Compilation failed!
    exit /b
)
echo.
echo Compiled!
%EXE% 
echo.
