@echo off
setlocal enabledelayedexpansion

REM Smart MA.VI Manager - Windows Build Script
REM This script builds the application and creates .exe installer

echo [INFO] Starting Windows build process for Smart MA.VI Manager v1.0.0

REM Configuration
set PROJECT_NAME=SmartMAVIManager
set VERSION=1.0.0
set BUILD_DIR=build-windows
set PACKAGE_DIR=packages

REM Check if we're in the right directory
if not exist "CMakeLists.txt" (
    echo [ERROR] CMakeLists.txt not found. Please run this script from the project root directory.
    exit /b 1
)

REM Check for CMake
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] CMake is not installed or not in PATH.
    echo [INFO] Please install CMake from https://cmake.org/download/
    exit /b 1
)

REM Check for Visual Studio or MinGW
where cl >nul 2>&1
if %errorlevel% equ 0 (
    echo [INFO] Found Visual Studio compiler
    set COMPILER=msvc
) else (
    where g++ >nul 2>&1
    if %errorlevel% equ 0 (
        echo [INFO] Found MinGW compiler
        set COMPILER=mingw
    ) else (
        echo [ERROR] No C++ compiler found. Please install Visual Studio or MinGW.
        exit /b 1
    )
)

REM Create directories
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
if not exist "%PACKAGE_DIR%" mkdir "%PACKAGE_DIR%"

REM Build the application
echo [INFO] Building the application...
cd "%BUILD_DIR%"

if "%COMPILER%"=="msvc" (
    cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
) else (
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build .
)

if %errorlevel% neq 0 (
    echo [ERROR] Build failed
    exit /b 1
)

echo [SUCCESS] Application built successfully

REM Create installer
echo [INFO] Creating installer...
cpack -G NSIS

if %errorlevel% neq 0 (
    echo [ERROR] Installer creation failed
    exit /b 1
)

cd ..

REM Move installer to packages directory
if exist "%BUILD_DIR%\SmartMAVIManager-1.0.0-win64.exe" (
    move "%BUILD_DIR%\SmartMAVIManager-1.0.0-win64.exe" "%PACKAGE_DIR%\"
    echo [SUCCESS] Installer created: %PACKAGE_DIR%\SmartMAVIManager-1.0.0-win64.exe
) else (
    echo [ERROR] Installer not found
    exit /b 1
)

echo [SUCCESS] Windows build completed!
echo [INFO] Installer created in %PACKAGE_DIR%\
echo [INFO] Installation: Run %PACKAGE_DIR%\SmartMAVIManager-1.0.0-win64.exe
