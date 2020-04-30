@echo OFF
PUSHD "%~dp0..\"
setlocal EnableDelayedExpansion
if not exist "build_windows\NUL" (mkdir build_windows)
PUSHD "build_windows"
call VsDevCmd.bat 
IF "%1" == "" (
   cmake %~dp0.. && msbuild.exe Watty_Engine.sln && POPD && POPD & pause
 ) ELSE ( 
    cmake %~dp0.. && msbuild.exe /p:Configuration=%1 Watty_Engine.sln && POPD && POPD & pause
 )
 @echo "Building Watty For Windows finished"