@echo OFF
setlocal EnableDelayedExpansion
PUSHD "%~dp0..\"
if not exist "build_windows\NUL" ( mkdir build_windows )
PUSHD "build_windows"
call VsDevCmd.bat 
cmake -DBuildResources=ON %~dp0.. && POPD && POPD & pause
 @echo "Building Resources For Watty finished"