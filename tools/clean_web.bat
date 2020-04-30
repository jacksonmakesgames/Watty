@echo OFF
Setlocal EnableDelayedExpansion
@echo Cleaning....
PUSHD "%~dp0..\"

IF EXIST bin\Web\ (
	@echo **Found web bin folder, removing....
	RMDIR /S/Q bin\Web
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for bin files. Ending. )

IF EXIST build_web\ (
	@echo **Found web build folder, removing....
	RMDIR /S/Q build_web
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for build files. Ending. )
POPD

