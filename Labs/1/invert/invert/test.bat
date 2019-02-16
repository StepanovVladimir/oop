@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > %OUT%
fc %OUT% noArguments-out.txt || goto err

%PROGRAM% lalala > %OUT%
fc %OUT% failedFile-out.txt || goto err

%PROGRAM% notEnoughNumbers.txt > %OUT%
fc %OUT% inputError-out.txt || goto err

%PROGRAM% badInput.txt > %OUT%
fc %OUT% inputError-out.txt || goto err

%PROGRAM% zeroDeterminant.txt > %OUT% || goto err
fc %OUT% zeroDeterminant-out.txt || goto err

%PROGRAM% matrix1.txt > %OUT% || goto err
fc %OUT% matrix1-out.txt || goto err

%PROGRAM% matrix2.txt > %OUT% || goto err
fc %OUT% matrix2-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
