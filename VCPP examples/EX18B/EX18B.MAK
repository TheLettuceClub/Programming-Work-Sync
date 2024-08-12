# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX18B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX18B\
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
DEFFILE = EX18B.DEF
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
		EX18B.SBR \
		MAINFRM.SBR \
		EX18BDOC.SBR \
		EX18BVW.SBR


EX18B_RCDEP = c:\vcpp\ex18b\res\ex18b.ico \
	c:\vcpp\ex18b\res\ex18bdoc.ico \
	c:\vcpp\ex18b\res\toolbar.bmp \
	c:\vcpp\ex18b\res\ex18b.rc2


STDAFX_DEP = c:\vcpp\ex18b\stdafx.h


EX18B_DEP = c:\vcpp\ex18b\stdafx.h \
	c:\vcpp\ex18b\ex18b.h \
	c:\vcpp\ex18b\mainfrm.h \
	c:\vcpp\ex18b\ex18bdoc.h \
	c:\vcpp\ex18b\ex18bvw.h


MAINFRM_DEP = c:\vcpp\ex18b\stdafx.h \
	c:\vcpp\ex18b\ex18b.h \
	c:\vcpp\ex18b\mainfrm.h


EX18BDOC_DEP = c:\vcpp\ex18b\stdafx.h \
	c:\vcpp\ex18b\ex18b.h \
	c:\vcpp\ex18b\ex18bdoc.h


EX18BVW_DEP = c:\vcpp\ex18b\stdafx.h \
	c:\vcpp\ex18b\ex18b.h \
	c:\vcpp\ex18b\ex18bdoc.h \
	c:\vcpp\ex18b\ex18bvw.h


all:	$(PROJ).EXE

EX18B.RES:	EX18B.RC $(EX18B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX18B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX18B.OBJ:	EX18B.CPP $(EX18B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX18B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX18BDOC.OBJ:	EX18BDOC.CPP $(EX18BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX18BDOC.CPP

EX18BVW.OBJ:	EX18BVW.CPP $(EX18BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX18BVW.CPP


$(PROJ).EXE::	EX18B.RES

$(PROJ).EXE::	STDAFX.OBJ EX18B.OBJ MAINFRM.OBJ EX18BDOC.OBJ EX18BVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX18B.OBJ +
MAINFRM.OBJ +
EX18BDOC.OBJ +
EX18BVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX18B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX18B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX18B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
