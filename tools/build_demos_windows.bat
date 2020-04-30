@echo OFF
PUSHD "%~dp0..\Demos\"
setlocal EnableDelayedExpansion
if not exist "build_windows\NUL" (mkdir build_windows)
PUSHD "build_windows"
call VsDevCmd.bat 
IF "%1" == "" (
   cmake .. && msbuild.exe Demos.sln && POPD && POPD & pause
 ) ELSE ( 
    cmake .. && msbuild.exe /p:Configuration=%1 Demos.sln && POPD && POPD & pause
 )