@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by EX10A.HPJ. >hlp\ex10a.hm
echo. >>hlp\ex10a.hm
echo // Commands (ID_* and IDM_*) >>hlp\ex10a.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\ex10a.hm
echo. >>hlp\ex10a.hm
echo // Prompts (IDP_*) >>hlp\ex10a.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\ex10a.hm
echo. >>hlp\ex10a.hm
echo // Resources (IDR_*) >>hlp\ex10a.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\ex10a.hm
echo. >>hlp\ex10a.hm
echo // Dialogs (IDD_*) >>hlp\ex10a.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\ex10a.hm
echo. >>hlp\ex10a.hm
echo // Frame Controls (IDW_*) >>hlp\ex10a.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\ex10a.hm
REM -- Make help for Project EX10A
call hc31 ex10a.hpj
echo.
