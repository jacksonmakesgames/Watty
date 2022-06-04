@echo OFF
setlocal EnableDelayedExpansion
PUSHD "%~dp0..\"
if not exist "build_windows\NUL" ( mkdir build_windows )
PUSHD "build_windows"
call VsDevCmd.bat 
cmake .. && msbuild.exe /p:Configuration=Release Watty_Engine.sln && POPD && POPD
 @echo "Building Watty For Windows (Release) finished"