# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX14A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX14A\
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
CFLAGS_D_WEXE = /nologo /G2 /W3 /AM /Od /D "_DEBUG" /GA /Fp"..\stdafx.pch" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg olesvr olecli shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg olesvr olecli shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX14A.DEF
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
		EX14A.SBR \
		MAINFRM.SBR \
		EX14ADOC.SBR \
		EX14AVW.SBR \
		PERSIST.SBR


EX14A_RCDEP = c:\vcpp\ex14a\res\ex14a.ico \
	c:\vcpp\ex14a\res\toolbar.bmp \
	c:\vcpp\ex14a\res\ex14a.rc2


STDAFX_DEP = c:\vcpp\ex14a\stdafx.h


EX14A_DEP = c:\vcpp\ex14a\stdafx.h \
	c:\vcpp\ex14a\ex14a.h \
	c:\vcpp\ex14a\mainfrm.h \
	c:\vcpp\ex14a\ex14adoc.h \
	c:\vcpp\ex14a\ex14avw.h


MAINFRM_DEP = c:\vcpp\ex14a\stdafx.h \
	c:\vcpp\ex14a\ex14a.h \
	c:\vcpp\ex14a\mainfrm.h


EX14ADOC_DEP = c:\vcpp\ex14a\stdafx.h \
	c:\vcpp\ex14a\ex14a.h \
	c:\vcpp\ex14a\ex14adoc.h


EX14AVW_DEP = c:\vcpp\ex14a\stdafx.h \
	c:\vcpp\ex14a\ex14a.h \
	c:\vcpp\ex14a\ex14adoc.h \
	c:\vcpp\ex14a\ex14avw.h


PERSIST_DEP = c:\vcpp\ex14a\stdafx.h \
	c:\vcpp\ex14a\persist.h


all:	$(PROJ).EXE

EX14A.RES:	EX14A.RC $(EX14A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX14A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX14A.OBJ:	EX14A.CPP $(EX14A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX14A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX14ADOC.OBJ:	EX14ADOC.CPP $(EX14ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX14ADOC.CPP

EX14AVW.OBJ:	EX14AVW.CPP $(EX14AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX14AVW.CPP

PERSIST.OBJ:	PERSIST.CPP $(PERSIST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PERSIST.CPP


$(PROJ).EXE::	EX14A.RES

$(PROJ).EXE::	STDAFX.OBJ EX14A.OBJ MAINFRM.OBJ EX14ADOC.OBJ EX14AVW.OBJ PERSIST.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX14A.OBJ +
MAINFRM.OBJ +
EX14ADOC.OBJ +
EX14AVW.OBJ +
PERSIST.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX14A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX14A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX14A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
