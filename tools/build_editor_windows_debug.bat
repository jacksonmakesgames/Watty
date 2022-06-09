@echo OFF
PUSHD "%~dp0..\editor\"
setlocal EnableDelayedExpansion
if not exist "build_windows\NUL" (mkdir build_windows)
PUSHD "build_windows"
call VsDevCmd.bat 
cmake .. -DCOPY_WATTY_DEPENDENCIES=0 && msbuild.exe /p:Configuration=Debug Editor.sln && POPD && POPD
