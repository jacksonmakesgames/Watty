@echo OFF
PUSHD "%~dp0..\Demos\"
setlocal EnableDelayedExpansion
if not exist "build_windows\NUL" (mkdir build_windows)
PUSHD "build_windows"
call VsDevCmd.bat 
cmake .. && msbuild.exe /p:Configuration=Debug Demos.sln && POPD && POPD & pause
