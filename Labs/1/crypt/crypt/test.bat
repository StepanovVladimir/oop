@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > %OUT%
fc %OUT% noArguments-out.txt || goto err

%PROGRAM% cropt decrypted.txt output.txt 6 > %OUT%
fc %OUT% badCommand-out.txt || goto err

%PROGRAM% crypt decrypted.txt output.txt abc > %OUT%
fc %OUT% notByte-out.txt || goto err

%PROGRAM% crypt decrypted.txt output.txt 300 > %OUT%
fc %OUT% notByte-out.txt || goto err

%PROGRAM% crypt lalala output.txt 6 > %OUT%
fc %OUT% failedFile-out.txt || goto err

%PROGRAM% crypt decrypted.txt output.txt 6 || goto err
fc output.txt encrypted.txt || goto err

%PROGRAM% decrypt encrypted.txt output.txt 6 || goto err
fc output.txt decrypted.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1