@echo off
set SRC=i.cpp
set EXE=a

:: Compile
g++ -std=c++17 -O2 -Wno-unused-result -Wno-sign-conversion %SRC% -o %EXE%
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
