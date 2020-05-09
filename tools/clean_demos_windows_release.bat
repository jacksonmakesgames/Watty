@echo OFF
Setlocal EnableDelayedExpansion
@echo Cleaning....
PUSHD "%~dp0..\Demos\"

IF EXIST bin\Release\ (
	@echo **Found demos bin release folder, removing....
	RMDIR /S/Q bin\Release
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for bin files. Ending. )

IF EXIST build_windows\ (
	@echo **Found demos windows build folder, removing....
	RMDIR /S/Q build_windows\
	@echo **Done removing.
) ELSE ( @echo **Nothing to be done for build files. Ending. )
POPD

