@echo off
xcopy source\BitOperations.h UnitTest\ /V /F /K /Y
xcopy source\src\BitOperations.c UnitTest\src\ /V /F /K /Y
pause