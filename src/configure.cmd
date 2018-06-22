@echo off

call :create_sources
cd ..\test
call :create_sources

goto :eof

:create_sources
echo SOURCES = \>sources.mk
for %%f in (*.cpp) do @echo 	%%f \>>sources.mk
goto :eof
