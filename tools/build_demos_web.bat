@echo OFF
PUSHD "%~dp0..\Demos\"
IF EXIST bin\Web\ (
del bin\Web\*.js
del bin\Web\*.wasm
)
IF EXIST Demos\bin\Web\ (
del Demos\bin\Web\*.js
del Demos\bin\Web\*.wasm
)
if not exist "build_web\NUL" mkdir build_web
PUSHD "build_web"
call ..\..\dependencies\emscripten\emsdk_env.bat && emcmake cmake -DEMSCRIPTEN=TRUE -G "Unix Makefiles" .. && make && POPD && POPD & pause

