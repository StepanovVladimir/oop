@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > %OUT%
fc %OUT% noArguments-out.txt || goto err

%PROGRAM% lalala output.txt > %OUT%
fc %OUT% failedFile-out.txt || goto err

%PROGRAM% badInput.txt output.txt > %OUT%
fc %OUT% inputError-out.txt || goto err

%PROGRAM% input1.txt output.txt || goto err
fc output.txt output1.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1