@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > %OUT%
fc %OUT% noArguments-out.txt || goto err

%PROGRAM% lalala output.txt > %OUT%
fc %OUT% failedFile-out.txt || goto err

%PROGRAM% notFullInput.txt output.txt > %OUT%
fc %OUT% inputError-out.txt || goto err

%PROGRAM% noCoordinates.txt output.txt > %OUT%
fc %OUT% inputError-out.txt || goto err

%PROGRAM% unwantedCoordinates.txt output.txt > %OUT%
fc %OUT% inputError-out.txt || goto err

%PROGRAM% input1.txt output.txt || goto err
fc output.txt output1.txt || goto err

%PROGRAM% input2.txt output.txt || goto err
fc output.txt output2.txt || goto err

%PROGRAM% input3.txt output.txt || goto err
fc output.txt output3.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
