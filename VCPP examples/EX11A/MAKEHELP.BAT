@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by EX11A.HPJ. >hlp\ex11a.hm
echo. >>hlp\ex11a.hm
echo // Commands (ID_* and IDM_*) >>hlp\ex11a.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\ex11a.hm
echo. >>hlp\ex11a.hm
echo // Prompts (IDP_*) >>hlp\ex11a.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\ex11a.hm
echo. >>hlp\ex11a.hm
echo // Resources (IDR_*) >>hlp\ex11a.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\ex11a.hm
echo. >>hlp\ex11a.hm
echo // Dialogs (IDD_*) >>hlp\ex11a.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\ex11a.hm
echo. >>hlp\ex11a.hm
echo // Frame Controls (IDW_*) >>hlp\ex11a.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\ex11a.hm
REM -- Make help for Project EX11A
call hc31 ex11a.hpj
echo.
