# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX06A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = 
R_RCDEFINES = 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX06A\
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
CFLAGS_D_WEXE = /nologo /Gs /G2 /Zp1 /W3 /AM /Od /D "_DEBUG" /GA /Fp"..\stdafx.h" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mafxcwd mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mafxcw mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z 
RESFLAGS = /nologo /t 
RUNFLAGS = 
DEFFILE = EX06A.DEF
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
		EX06A.SBR \
		MAINFRM.SBR \
		EX06ADOC.SBR \
		EX06AVW.SBR \
		EX06ADLG.SBR


STDAFX_DEP = c:\vcpp\ex06a\stdafx.h


EX06A_DEP = c:\vcpp\ex06a\stdafx.h \
	c:\vcpp\ex06a\ex06a.h \
	c:\vcpp\ex06a\mainfrm.h \
	c:\vcpp\ex06a\ex06adoc.h \
	c:\vcpp\ex06a\ex06avw.h


MAINFRM_DEP = c:\vcpp\ex06a\stdafx.h \
	c:\vcpp\ex06a\ex06a.h \
	c:\vcpp\ex06a\mainfrm.h


EX06ADOC_DEP = c:\vcpp\ex06a\stdafx.h \
	c:\vcpp\ex06a\ex06a.h \
	c:\vcpp\ex06a\ex06adoc.h


EX06AVW_DEP = c:\vcpp\ex06a\stdafx.h \
	c:\vcpp\ex06a\ex06a.h \
	c:\vcpp\ex06a\ex06adoc.h \
	c:\vcpp\ex06a\ex06avw.h \
	c:\vcpp\ex06a\ex06adlg.h


EX06A_RCDEP = c:\vcpp\ex06a\res\ex06a.ico \
	c:\vcpp\ex06a\res\ex06a.rc2


EX06ADLG_DEP = c:\vcpp\ex06a\stdafx.h \
	c:\vcpp\ex06a\ex06a.h \
	c:\vcpp\ex06a\ex06adlg.h


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX06A.OBJ:	EX06A.CPP $(EX06A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX06A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX06ADOC.OBJ:	EX06ADOC.CPP $(EX06ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX06ADOC.CPP

EX06AVW.OBJ:	EX06AVW.CPP $(EX06AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX06AVW.CPP

EX06A.RES:	EX06A.RC $(EX06A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX06A.RC

EX06ADLG.OBJ:	EX06ADLG.CPP $(EX06ADLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX06ADLG.CPP


$(PROJ).EXE::	EX06A.RES

$(PROJ).EXE::	STDAFX.OBJ EX06A.OBJ MAINFRM.OBJ EX06ADOC.OBJ EX06AVW.OBJ EX06ADLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX06A.OBJ +
MAINFRM.OBJ +
EX06ADOC.OBJ +
EX06AVW.OBJ +
EX06ADLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX06A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX06A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX06A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
