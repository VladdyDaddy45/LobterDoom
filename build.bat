@echo off

pushd "H:\vscodeStuff\cpp\SDL"
color 7

set "SDLincl = H:\SDL\x86_64-w64-mingw32\include"
set "SDLlib = H:\SDL\x86_64-w64-mingw32\lib"
set "incl = %cd%/include"


gcc -c -I"H:\SDL\x86_64-w64-mingw32\include" -I"%cd%/include" src/main.c -o build/main.o -L"H:\SDL\x86_64-w64-mingw32\lib" -lSDL3 -lSDL3_image
gcc -c -I"H:\SDL\x86_64-w64-mingw32\include" -I"%cd%/include" src/graphics/graphics.c -o build/graphics.o -L"H:\SDL\x86_64-w64-mingw32\lib" -lSDL3 -lSDL3_image

gcc build/main.o build/graphics.o -o main.exe -L"H:\SDL\x86_64-w64-mingw32\lib" -lSDL3 -lSDL3_image

IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful, running program...
    .\main.exe
) ELSE (
    echo Error during compilation.
)

pause > nul