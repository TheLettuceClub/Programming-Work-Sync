# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX17B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX17B\
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
DEFFILE = EX17B.DEF
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
		EX17B.SBR \
		MAINFRM.SBR \
		EX17BDOC.SBR \
		EX17BVW.SBR


EX17B_RCDEP = c:\vcpp\ex17b\res\ex17b.ico \
	c:\vcpp\ex17b\res\toolbar.bmp \
	c:\vcpp\ex17b\res\ex17b.rc2


STDAFX_DEP = c:\vcpp\ex17b\stdafx.h


EX17B_DEP = c:\vcpp\ex17b\stdafx.h \
	c:\vcpp\ex17b\ex17b.h \
	c:\vcpp\ex17b\mainfrm.h \
	c:\vcpp\ex17b\ex17bdoc.h \
	c:\vcpp\ex17b\ex17bvw.h


MAINFRM_DEP = c:\vcpp\ex17b\stdafx.h \
	c:\vcpp\ex17b\ex17b.h \
	c:\vcpp\ex17b\mainfrm.h


EX17BDOC_DEP = c:\vcpp\ex17b\stdafx.h \
	c:\vcpp\ex17b\ex17b.h \
	c:\vcpp\ex17b\ex17bdoc.h


EX17BVW_DEP = c:\vcpp\ex17b\stdafx.h \
	c:\vcpp\ex17b\ex17b.h \
	c:\vcpp\ex17b\ex17bdoc.h \
	c:\vcpp\ex17b\ex17bvw.h


all:	$(PROJ).EXE

EX17B.RES:	EX17B.RC $(EX17B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX17B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX17B.OBJ:	EX17B.CPP $(EX17B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX17B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX17BDOC.OBJ:	EX17BDOC.CPP $(EX17BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX17BDOC.CPP

EX17BVW.OBJ:	EX17BVW.CPP $(EX17BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX17BVW.CPP


$(PROJ).EXE::	EX17B.RES

$(PROJ).EXE::	STDAFX.OBJ EX17B.OBJ MAINFRM.OBJ EX17BDOC.OBJ EX17BVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX17B.OBJ +
MAINFRM.OBJ +
EX17BDOC.OBJ +
EX17BVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX17B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX17B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX17B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
