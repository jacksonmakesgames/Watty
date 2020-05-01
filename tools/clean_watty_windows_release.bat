@echo OFF
Setlocal EnableDelayedExpansion
@echo Cleaning Windows Release....
PUSHD "%~dp0..\"

IF EXIST bin\Release\ (
	@echo **Found Release bin folder, removing....
	RMDIR /S/Q bin\Release
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for bin files. Ending. )

IF EXIST build_windows\ (
	@echo **Found Release build folder, removing....
	RMDIR /S/Q build_windows
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for build files. Ending. )
POPD

