@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% < input.txt > %OUT% || goto err
fc %OUT% output.txt || goto err

%PROGRAM% < empty.txt > %OUT% || goto err
fc %OUT% empty-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1