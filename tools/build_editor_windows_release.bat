@echo OFF
PUSHD "%~dp0..\editor\"
setlocal EnableDelayedExpansion
if not exist "build_windows\NUL" (mkdir build_windows)
PUSHD "build_windows"
call VsDevCmd.bat 
cmake .. && msbuild.exe /p:Configuration=Release Editor.sln && POPD && POPD
