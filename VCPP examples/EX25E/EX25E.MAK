# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX25E
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX25E\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /Gy /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"EX25E.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew compobj storage ole2 ole2disp ole2nls mfcoleui odbc commdlg.lib shell.lib 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew compobj storage ole2 ole2disp ole2nls mfcoleui odbc commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX25E.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		MAINFRM.SBR \
		APP.SBR \
		RANGE.SBR \
		WKBOOKS.SBR \
		WKSHEET.SBR \
		CVARIANT.SBR \
		ALARMDLG.SBR \
		EX25E.SBR \
		EX25EDOC.SBR \
		EX25EVW.SBR \
		HELLO.SBR \
		MARKETC.SBR \
		DLLCONT.SBR \
		ALARMC.SBR \
		CLOCKC.SBR


STDAFX_DEP = c:\vcpp\ex25e\stdafx.h


MAINFRM_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\ex25e.h \
	c:\vcpp\ex25e\mainfrm.h


APP_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\app.h


RANGE_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\range.h \
	c:\vcpp\ex25e\cvariant.h


WKBOOKS_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\wkbooks.h


WKSHEET_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\wksheet.h


CVARIANT_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\cvariant.h


ALARMDLG_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\ex25e.h \
	c:\vcpp\ex25e\alarmdlg.h


EX25E_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\ex25e.h \
	c:\vcpp\ex25e\mainfrm.h \
	c:\vcpp\ex25e\ex25edoc.h \
	c:\vcpp\ex25e\ex25evw.h \
	c:\vcpp\ex25e\app.h \
	c:\vcpp\ex25e\range.h \
	c:\vcpp\ex25e\cvariant.h \
	c:\vcpp\ex25e\wksheet.h \
	c:\vcpp\ex25e\wkbooks.h \
	c:\vcpp\ex25e\clockc.h \
	c:\vcpp\ex25e\alarmc.h \
	c:\vcpp\ex25e\dllcont.h \
	c:\vcpp\ex25e\marketc.h


EX25EDOC_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\ex25e.h \
	c:\vcpp\ex25e\ex25edoc.h


EX25EVW_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\ex25e.h \
	c:\vcpp\ex25e\ex25edoc.h \
	c:\vcpp\ex25e\ex25evw.h \
	c:\vcpp\ex25e\app.h \
	c:\vcpp\ex25e\range.h \
	c:\vcpp\ex25e\cvariant.h \
	c:\vcpp\ex25e\wksheet.h \
	c:\vcpp\ex25e\wkbooks.h \
	c:\vcpp\ex25e\clockc.h \
	c:\vcpp\ex25e\alarmc.h \
	c:\vcpp\ex25e\dllcont.h \
	c:\vcpp\ex25e\marketc.h \
	c:\vcpp\ex25e\alarmdlg.h


HELLO_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\hello.h


EX25E_RCDEP = c:\vcpp\ex25e\res\ex25e.ico \
	c:\vcpp\ex25e\res\ex25e.rc2


MARKETC_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\marketc.h


DLLCONT_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\dllcont.h \
	c:\vcpp\ex25e\cvariant.h


ALARMC_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\alarmc.h \
	c:\vcpp\ex25e\cvariant.h


CLOCKC_DEP = c:\vcpp\ex25e\stdafx.h \
	c:\vcpp\ex25e\clockc.h \
	c:\vcpp\ex25e\cvariant.h


all:	$(PROJ).EXE $(PROJ).BSC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

APP.OBJ:	APP.CPP $(APP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c APP.CPP

RANGE.OBJ:	RANGE.CPP $(RANGE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RANGE.CPP

WKBOOKS.OBJ:	WKBOOKS.CPP $(WKBOOKS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WKBOOKS.CPP

WKSHEET.OBJ:	WKSHEET.CPP $(WKSHEET_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WKSHEET.CPP

CVARIANT.OBJ:	CVARIANT.CPP $(CVARIANT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CVARIANT.CPP

ALARMDLG.OBJ:	ALARMDLG.CPP $(ALARMDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ALARMDLG.CPP

EX25E.OBJ:	EX25E.CPP $(EX25E_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25E.CPP

EX25EDOC.OBJ:	EX25EDOC.CPP $(EX25EDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25EDOC.CPP

EX25EVW.OBJ:	EX25EVW.CPP $(EX25EVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25EVW.CPP

HELLO.OBJ:	HELLO.CPP $(HELLO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c HELLO.CPP

EX25E.RES:	EX25E.RC $(EX25E_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX25E.RC

MARKETC.OBJ:	MARKETC.CPP $(MARKETC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MARKETC.CPP

DLLCONT.OBJ:	DLLCONT.CPP $(DLLCONT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLLCONT.CPP

ALARMC.OBJ:	ALARMC.CPP $(ALARMC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ALARMC.CPP

CLOCKC.OBJ:	CLOCKC.CPP $(CLOCKC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLOCKC.CPP


$(PROJ).EXE::	EX25E.RES

$(PROJ).EXE::	STDAFX.OBJ MAINFRM.OBJ APP.OBJ RANGE.OBJ WKBOOKS.OBJ WKSHEET.OBJ CVARIANT.OBJ \
	ALARMDLG.OBJ EX25E.OBJ EX25EDOC.OBJ EX25EVW.OBJ HELLO.OBJ MARKETC.OBJ DLLCONT.OBJ \
	ALARMC.OBJ CLOCKC.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
MAINFRM.OBJ +
APP.OBJ +
RANGE.OBJ +
WKBOOKS.OBJ +
WKSHEET.OBJ +
CVARIANT.OBJ +
ALARMDLG.OBJ +
EX25E.OBJ +
EX25EDOC.OBJ +
EX25EVW.OBJ +
HELLO.OBJ +
MARKETC.OBJ +
DLLCONT.OBJ +
ALARMC.OBJ +
CLOCKC.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX25E.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX25E.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX25E.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
