@ECHO OFF

set "folder=%cd%/build"
set "keep=Win32"
set "keeptwo=x64"

cd /d %folder%

for /F "delims=" %%G in ('dir /b') do (
    if /I NOT "%%G"=="%keep%" (
        if /I NOT "%%G"=="%keeptwo%" (
            REM check if it is a directory or file
            IF EXIST "%%G\" (
                rmdir "%%G" /s /q
            ) else (
                del "%%G" /q
            )
        )
    )
)

cd ..

copy "main.cpp" "build/x64/" >nul

cd build/x64

cmake -S . -B .. -G "MinGW Makefiles"

make -C ".." -s

del /f "main.cpp"

IF EXIST "build" (
    del /f "build"
)

cd ../..