@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by MATPLAN.HPJ. >hlp\matplan.hm
echo. >>hlp\matplan.hm
echo // Commands (ID_* and IDM_*) >>hlp\matplan.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\matplan.hm
echo. >>hlp\matplan.hm
echo // Prompts (IDP_*) >>hlp\matplan.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\matplan.hm
echo. >>hlp\matplan.hm
echo // Resources (IDR_*) >>hlp\matplan.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\matplan.hm
echo. >>hlp\matplan.hm
echo // Dialogs (IDD_*) >>hlp\matplan.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\matplan.hm
echo. >>hlp\matplan.hm
echo // Frame Controls (IDW_*) >>hlp\matplan.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\matplan.hm
REM -- Make help for Project MATPLAN
call hc31 matplan.hpj
echo.
