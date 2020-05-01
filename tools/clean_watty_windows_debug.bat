@echo OFF
Setlocal EnableDelayedExpansion
@echo Cleaning Windows Debug....
PUSHD "%~dp0..\"

IF EXIST bin\Debug\ (
	@echo **Found Windows Debug bin folder, removing....
	RMDIR /S/Q bin\Debug
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for bin files. Ending. )

IF EXIST build_windows\ (
	@echo **Found Windows Debug build folder, removing....
	RMDIR /S/Q build_windows
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for build files. Ending. )
POPD

