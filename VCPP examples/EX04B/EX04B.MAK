# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX04B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX04B\
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
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX04B.DEF
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
		EX04B.SBR \
		MAINFRM.SBR \
		EX04BDOC.SBR \
		EX04BVW.SBR


EX04B_RCDEP = c:\vcpp\ex04b\res\ex04b.ico \
	c:\vcpp\ex04b\res\toolbar.bmp \
	c:\vcpp\ex04b\res\ex04b.rc2


STDAFX_DEP = c:\vcpp\ex04b\stdafx.h


EX04B_DEP = c:\vcpp\ex04b\stdafx.h \
	c:\vcpp\ex04b\ex04b.h \
	c:\vcpp\ex04b\mainfrm.h \
	c:\vcpp\ex04b\ex04bdoc.h \
	c:\vcpp\ex04b\ex04bvw.h


MAINFRM_DEP = c:\vcpp\ex04b\stdafx.h \
	c:\vcpp\ex04b\ex04b.h \
	c:\vcpp\ex04b\mainfrm.h


EX04BDOC_DEP = c:\vcpp\ex04b\stdafx.h \
	c:\vcpp\ex04b\ex04b.h \
	c:\vcpp\ex04b\ex04bdoc.h


EX04BVW_DEP = c:\vcpp\ex04b\stdafx.h \
	c:\vcpp\ex04b\ex04b.h \
	c:\vcpp\ex04b\ex04bdoc.h \
	c:\vcpp\ex04b\ex04bvw.h


all:	$(PROJ).EXE

EX04B.RES:	EX04B.RC $(EX04B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX04B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX04B.OBJ:	EX04B.CPP $(EX04B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX04BDOC.OBJ:	EX04BDOC.CPP $(EX04BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04BDOC.CPP

EX04BVW.OBJ:	EX04BVW.CPP $(EX04BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04BVW.CPP


$(PROJ).EXE::	EX04B.RES

$(PROJ).EXE::	STDAFX.OBJ EX04B.OBJ MAINFRM.OBJ EX04BDOC.OBJ EX04BVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX04B.OBJ +
MAINFRM.OBJ +
EX04BDOC.OBJ +
EX04BVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX04B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX04B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX04B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
