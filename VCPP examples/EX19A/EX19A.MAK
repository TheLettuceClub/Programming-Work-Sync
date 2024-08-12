# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX19A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = 
R_RCDEFINES = 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX19A\
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
CFLAGS_D_WEXE = /nologo /Gs /G2 /Zp1 /W3 /AM /Od /D "_DEBUG" /GA /Fp"..\stdafx.pch" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mafxcwd commdlg shell olecli olesvr mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mafxcw commdlg shell olecli olesvr mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z 
RESFLAGS = /nologo /t 
RUNFLAGS = 
DEFFILE = EX19A.DEF
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
		EX19A.SBR \
		MAINFRM.SBR \
		POEMDOC.SBR \
		STRINGVW.SBR


EX19A_RCDEP = c:\vcpp\ex19a\res\ex19a.ico \
	c:\vcpp\ex19a\res\ex19a.rc2


STDAFX_DEP = c:\vcpp\ex19a\stdafx.h


EX19A_DEP = c:\vcpp\ex19a\stdafx.h \
	c:\vcpp\ex19a\ex19a.h \
	c:\vcpp\ex19a\mainfrm.h \
	c:\vcpp\ex19a\poemdoc.h \
	c:\vcpp\ex19a\stringvw.h


MAINFRM_DEP = c:\vcpp\ex19a\stdafx.h \
	c:\vcpp\ex19a\ex19a.h \
	c:\vcpp\ex19a\mainfrm.h


POEMDOC_DEP = c:\vcpp\ex19a\stdafx.h \
	c:\vcpp\ex19a\poemdoc.h


STRINGVW_DEP = c:\vcpp\ex19a\stdafx.h \
	c:\vcpp\ex19a\poemdoc.h \
	c:\vcpp\ex19a\stringvw.h


all:	$(PROJ).EXE

EX19A.RES:	EX19A.RC $(EX19A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX19A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX19A.OBJ:	EX19A.CPP $(EX19A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX19A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

POEMDOC.OBJ:	POEMDOC.CPP $(POEMDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c POEMDOC.CPP

STRINGVW.OBJ:	STRINGVW.CPP $(STRINGVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STRINGVW.CPP


$(PROJ).EXE::	EX19A.RES

$(PROJ).EXE::	STDAFX.OBJ EX19A.OBJ MAINFRM.OBJ POEMDOC.OBJ STRINGVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX19A.OBJ +
MAINFRM.OBJ +
POEMDOC.OBJ +
STRINGVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX19A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX19A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX19A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
