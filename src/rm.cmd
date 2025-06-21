@echo off
set args=%*
set args=%args:/=\%

del /Q /F %args% 2>nul
rmdir /Q /S %args% 2>nul

exit 0
