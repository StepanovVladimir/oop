@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > %OUT%
fc %OUT% noArguments-out.txt || goto err

%PROGRAM% "" > %OUT%
fc %OUT% notByte-out.txt || goto err

%PROGRAM% 1b3 > %OUT%
fc %OUT% notByte-out.txt || goto err

%PROGRAM% 300 > %OUT%
fc %OUT% notByte-out.txt || goto err

%PROGRAM% 6 > %OUT% || goto err
fc %OUT% reverse_6-out.txt || goto err

%PROGRAM% 0 > %OUT% || goto err
fc %OUT% reverse_0-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1