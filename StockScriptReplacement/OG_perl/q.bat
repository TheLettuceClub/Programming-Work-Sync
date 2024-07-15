@echo off
echo This is the quarterly report
echo mf
echo done

perl quarterly1.pl mf
echo next is retirement
pause
perl quarterly1.pl retirement
echo next is stocks
pause
perl quarterly1.pl stocks
echo next is stocks2
pause
perl quarterly1.pl stocks2
echo next is trusts1
pause
perl quarterly1.pl trusts1
echo next is trusts2
pause
perl quarterly1.pl trusts2
echo All DONE!