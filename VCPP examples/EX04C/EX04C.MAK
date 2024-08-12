# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX04C
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX04C\
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
DEFFILE = EX04C.DEF
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
		EX04C.SBR \
		MAINFRM.SBR \
		EX04CDOC.SBR \
		EX04CVW.SBR


EX04C_RCDEP = c:\vcpp\ex04c\res\ex04c.ico \
	c:\vcpp\ex04c\res\toolbar.bmp \
	c:\vcpp\ex04c\res\ex04c.rc2


STDAFX_DEP = c:\vcpp\ex04c\stdafx.h


EX04C_DEP = c:\vcpp\ex04c\stdafx.h \
	c:\vcpp\ex04c\ex04c.h \
	c:\vcpp\ex04c\mainfrm.h \
	c:\vcpp\ex04c\ex04cdoc.h \
	c:\vcpp\ex04c\ex04cvw.h


MAINFRM_DEP = c:\vcpp\ex04c\stdafx.h \
	c:\vcpp\ex04c\ex04c.h \
	c:\vcpp\ex04c\mainfrm.h


EX04CDOC_DEP = c:\vcpp\ex04c\stdafx.h \
	c:\vcpp\ex04c\ex04c.h \
	c:\vcpp\ex04c\ex04cdoc.h


EX04CVW_DEP = c:\vcpp\ex04c\stdafx.h \
	c:\vcpp\ex04c\ex04c.h \
	c:\vcpp\ex04c\ex04cdoc.h \
	c:\vcpp\ex04c\ex04cvw.h


all:	$(PROJ).EXE

EX04C.RES:	EX04C.RC $(EX04C_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX04C.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX04C.OBJ:	EX04C.CPP $(EX04C_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04C.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX04CDOC.OBJ:	EX04CDOC.CPP $(EX04CDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04CDOC.CPP

EX04CVW.OBJ:	EX04CVW.CPP $(EX04CVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04CVW.CPP


$(PROJ).EXE::	EX04C.RES

$(PROJ).EXE::	STDAFX.OBJ EX04C.OBJ MAINFRM.OBJ EX04CDOC.OBJ EX04CVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX04C.OBJ +
MAINFRM.OBJ +
EX04CDOC.OBJ +
EX04CVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX04C.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX04C.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX04C.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
