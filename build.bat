@echo off
if not exist %GCC_PATH%/bin/g++.exe echo GCC_PATH must be set to GCC directory 
if not exist bin\libstdc++-6.dll copy %GCC_PATH%\bin\lib*.dll .\bin
%GCC_PATH%/bin/g++.exe -o bin/averager.exe src/*.cpp -Wfatal-errors -std=c++17 -lstdc++
echo Build finished. Created bin/averager.exe executable
