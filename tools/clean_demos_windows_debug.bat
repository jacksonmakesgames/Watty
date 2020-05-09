@echo OFF
Setlocal EnableDelayedExpansion
@echo Cleaning....
PUSHD "%~dp0..\Demos\"

IF EXIST bin\Debug\ (
	@echo **Found demos bin debug folder, removing....
	RMDIR /S/Q bin\Debug
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for bin files. Ending. )

IF EXIST build_windows\ (
	@echo **Found demos windows build folder, removing....
	RMDIR /S/Q build_windows\
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for build files. Ending. )
POPD

