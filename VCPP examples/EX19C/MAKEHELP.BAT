@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by EX19C.HPJ. >hlp\ex19c.hm
echo. >>hlp\ex19c.hm
echo // Commands (ID_* and IDM_*) >>hlp\ex19c.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\ex19c.hm
echo. >>hlp\ex19c.hm
echo // Prompts (IDP_*) >>hlp\ex19c.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\ex19c.hm
echo. >>hlp\ex19c.hm
echo // Resources (IDR_*) >>hlp\ex19c.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\ex19c.hm
echo. >>hlp\ex19c.hm
echo // Dialogs (IDD_*) >>hlp\ex19c.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\ex19c.hm
echo. >>hlp\ex19c.hm
echo // Frame Controls (IDW_*) >>hlp\ex19c.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\ex19c.hm
REM -- Make help for Project EX19C
call hc31 ex19c.hpj
echo.
