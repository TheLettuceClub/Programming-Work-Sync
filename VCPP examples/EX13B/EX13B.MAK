# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX13B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX13B\
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
DEFFILE = EX13B.DEF
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
		EX13B.SBR \
		MAINFRM.SBR \
		EX13BDOC.SBR \
		EX13BVW.SBR


EX13B_RCDEP = c:\vcpp\ex13b\res\ex13b.ico \
	c:\vcpp\ex13b\res\ex13b.rc2


STDAFX_DEP = c:\vcpp\ex13b\stdafx.h


EX13B_DEP = c:\vcpp\ex13b\stdafx.h \
	c:\vcpp\ex13b\ex13b.h \
	c:\vcpp\ex13b\mainfrm.h \
	c:\vcpp\ex13b\ex13bdoc.h \
	c:\vcpp\ex13b\ex13bvw.h


MAINFRM_DEP = c:\vcpp\ex13b\stdafx.h \
	c:\vcpp\ex13b\ex13b.h \
	c:\vcpp\ex13b\mainfrm.h


EX13BDOC_DEP = c:\vcpp\ex13b\stdafx.h \
	c:\vcpp\ex13b\ex13b.h \
	c:\vcpp\ex13b\ex13bdoc.h


EX13BVW_DEP = c:\vcpp\ex13b\stdafx.h \
	c:\vcpp\ex13b\ex13b.h \
	c:\vcpp\ex13b\ex13bdoc.h \
	c:\vcpp\ex13b\ex13bvw.h


all:	$(PROJ).EXE

EX13B.RES:	EX13B.RC $(EX13B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX13B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX13B.OBJ:	EX13B.CPP $(EX13B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX13B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX13BDOC.OBJ:	EX13BDOC.CPP $(EX13BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX13BDOC.CPP

EX13BVW.OBJ:	EX13BVW.CPP $(EX13BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX13BVW.CPP


$(PROJ).EXE::	EX13B.RES

$(PROJ).EXE::	STDAFX.OBJ EX13B.OBJ MAINFRM.OBJ EX13BDOC.OBJ EX13BVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX13B.OBJ +
MAINFRM.OBJ +
EX13BDOC.OBJ +
EX13BVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX13B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX13B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX13B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
