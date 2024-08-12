# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX10B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX10B\
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
DEFFILE = EX10B.DEF
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
		EX10B.SBR \
		MAINFRM.SBR \
		EX10BDOC.SBR \
		EX10BVW.SBR


EX10B_RCDEP = c:\vcpp\ex10b\res\ex10b.ico \
	c:\vcpp\ex10b\res\toolbar.bmp \
	c:\vcpp\ex10b\res\ex10b.rc2


STDAFX_DEP = c:\vcpp\ex10b\stdafx.h


EX10B_DEP = c:\vcpp\ex10b\stdafx.h \
	c:\vcpp\ex10b\ex10b.h \
	c:\vcpp\ex10b\mainfrm.h \
	c:\vcpp\ex10b\ex10bdoc.h \
	c:\vcpp\ex10b\ex10bvw.h


MAINFRM_DEP = c:\vcpp\ex10b\stdafx.h \
	c:\vcpp\ex10b\ex10b.h \
	c:\vcpp\ex10b\mainfrm.h


EX10BDOC_DEP = c:\vcpp\ex10b\stdafx.h \
	c:\vcpp\ex10b\ex10b.h \
	c:\vcpp\ex10b\ex10bdoc.h


EX10BVW_DEP = c:\vcpp\ex10b\stdafx.h \
	c:\vcpp\ex10b\ex10b.h \
	c:\vcpp\ex10b\ex10bdoc.h \
	c:\vcpp\ex10b\ex10bvw.h


all:	$(PROJ).EXE

EX10B.RES:	EX10B.RC $(EX10B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX10B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX10B.OBJ:	EX10B.CPP $(EX10B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX10B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX10BDOC.OBJ:	EX10BDOC.CPP $(EX10BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX10BDOC.CPP

EX10BVW.OBJ:	EX10BVW.CPP $(EX10BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX10BVW.CPP


$(PROJ).EXE::	EX10B.RES

$(PROJ).EXE::	STDAFX.OBJ EX10B.OBJ MAINFRM.OBJ EX10BDOC.OBJ EX10BVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX10B.OBJ +
MAINFRM.OBJ +
EX10BDOC.OBJ +
EX10BVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX10B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX10B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX10B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
