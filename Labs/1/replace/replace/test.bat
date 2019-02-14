@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > %OUT%
fc %OUT% noArguments-out.txt || goto err

%PROGRAM% lalala output.txt abc def > %OUT%
fc %OUT% failedFile-out.txt || goto err

%PROGRAM% severalLines.txt output.txt abc def || goto err
fc output.txt severalLines-out.txt || goto err

%PROGRAM% empty.txt output.txt abc def || goto err
fc output.txt empty-out.txt || goto err

%PROGRAM% severalLines.txt output.txt "" def || goto err
fc output.txt noSearchStr-out.txt || goto err

%PROGRAM% mama.txt output.txt ma mama || goto err
fc output.txt mama-out.txt || goto err

%PROGRAM% 123.txt output.txt 1231234 abc || goto err
fc output.txt 123-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
