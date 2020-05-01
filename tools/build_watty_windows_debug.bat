@echo OFF
setlocal EnableDelayedExpansion
PUSHD "%~dp0..\"
if not exist "build_windows\NUL" ( mkdir build_windows )
PUSHD "build_windows"
call VsDevCmd.bat 
cmake %~dp0.. && msbuild.exe /p:Configuration=Debug Watty_Engine.sln && POPD && POPD & pause
 @echo "Building Watty For Windows finished"