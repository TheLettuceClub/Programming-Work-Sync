# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX23A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = 
R_RCDEFINES = 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX23A\
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
DEFFILE = EX23A.DEF
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
		EX23A.SBR \
		MAINFRM.SBR \
		EX23ADOC.SBR \
		EX23AVW.SBR \
		BITSDLG.SBR \
		CDIB.SBR


STDAFX_DEP = c:\vcpp\ex23a\stdafx.h


EX23A_DEP = c:\vcpp\ex23a\stdafx.h \
	c:\vcpp\ex23a\ex23a.h \
	c:\vcpp\ex23a\bitsdlg.h \
	c:\vcpp\ex23a\cdib.h \
	c:\vcpp\ex23a\mainfrm.h \
	c:\vcpp\ex23a\ex23adoc.h \
	c:\vcpp\ex23a\ex23avw.h


MAINFRM_DEP = c:\vcpp\ex23a\stdafx.h \
	c:\vcpp\ex23a\ex23a.h \
	c:\vcpp\ex23a\mainfrm.h


EX23ADOC_DEP = c:\vcpp\ex23a\stdafx.h \
	c:\vcpp\ex23a\ex23a.h \
	c:\vcpp\ex23a\cdib.h \
	c:\vcpp\ex23a\ex23adoc.h


EX23AVW_DEP = c:\vcpp\ex23a\stdafx.h \
	c:\vcpp\ex23a\ex23a.h \
	c:\vcpp\ex23a\cdib.h \
	c:\vcpp\ex23a\ex23adoc.h \
	c:\vcpp\ex23a\ex23avw.h \
	c:\vcpp\ex23a\bitsdlg.h


EX23A_RCDEP = c:\vcpp\ex23a\res\ex23a.ico \
	c:\vcpp\ex23a\res\ex23a.rc2


BITSDLG_DEP = c:\vcpp\ex23a\stdafx.h \
	c:\vcpp\ex23a\bitsdlg.h


CDIB_DEP = c:\vcpp\ex23a\stdafx.h \
	c:\vcpp\ex23a\cdib.h


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX23A.OBJ:	EX23A.CPP $(EX23A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX23A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX23ADOC.OBJ:	EX23ADOC.CPP $(EX23ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX23ADOC.CPP

EX23AVW.OBJ:	EX23AVW.CPP $(EX23AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX23AVW.CPP

EX23A.RES:	EX23A.RC $(EX23A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX23A.RC

BITSDLG.OBJ:	BITSDLG.CPP $(BITSDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BITSDLG.CPP

CDIB.OBJ:	CDIB.CPP $(CDIB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CDIB.CPP


$(PROJ).EXE::	EX23A.RES

$(PROJ).EXE::	STDAFX.OBJ EX23A.OBJ MAINFRM.OBJ EX23ADOC.OBJ EX23AVW.OBJ BITSDLG.OBJ \
	CDIB.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX23A.OBJ +
MAINFRM.OBJ +
EX23ADOC.OBJ +
EX23AVW.OBJ +
BITSDLG.OBJ +
CDIB.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX23A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX23A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX23A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
