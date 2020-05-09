@echo OFF

PUSHD "%~dp0..\Demos"
IF EXIST bin\Web\ (
	PUSHD bin\Web
	del /s /q /f *.js
	del /s /q /f *.wasm
	del /s /q /f *.a
	POPD
)

if not exist "build_web\NUL" mkdir build_web
PUSHD "build_web"

..\..\dependencies\emscripten\emsdk_env.bat && emcmake cmake -DEMSCRIPTEN=TRUE -G "Unix Makefiles" .. && make && POPD && POPD & GOTO continue

:continue
set interactive=1
echo %cmdcmdline% | find /i "%~0" >nul
if not errorlevel 1 set interactive=0
@echo %interactive%

if %interactive% == 0 pause
