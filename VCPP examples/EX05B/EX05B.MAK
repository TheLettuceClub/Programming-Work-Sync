# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX05B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX05B\
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
DEFFILE = EX05B.DEF
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
		EX05B.SBR \
		MAINFRM.SBR \
		EX05BDOC.SBR \
		EX05BVW.SBR


EX05B_RCDEP = c:\vcpp\ex05b\res\ex05b.ico \
	c:\vcpp\ex05b\res\toolbar.bmp \
	c:\vcpp\ex05b\res\ex05b.rc2


STDAFX_DEP = c:\vcpp\ex05b\stdafx.h


EX05B_DEP = c:\vcpp\ex05b\stdafx.h \
	c:\vcpp\ex05b\ex05b.h \
	c:\vcpp\ex05b\mainfrm.h \
	c:\vcpp\ex05b\ex05bdoc.h \
	c:\vcpp\ex05b\ex05bvw.h


MAINFRM_DEP = c:\vcpp\ex05b\stdafx.h \
	c:\vcpp\ex05b\ex05b.h \
	c:\vcpp\ex05b\mainfrm.h


EX05BDOC_DEP = c:\vcpp\ex05b\stdafx.h \
	c:\vcpp\ex05b\ex05b.h \
	c:\vcpp\ex05b\ex05bdoc.h


EX05BVW_DEP = c:\vcpp\ex05b\stdafx.h \
	c:\vcpp\ex05b\ex05b.h \
	c:\vcpp\ex05b\ex05bdoc.h \
	c:\vcpp\ex05b\ex05bvw.h


all:	$(PROJ).EXE

EX05B.RES:	EX05B.RC $(EX05B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX05B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX05B.OBJ:	EX05B.CPP $(EX05B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX05B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX05BDOC.OBJ:	EX05BDOC.CPP $(EX05BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX05BDOC.CPP

EX05BVW.OBJ:	EX05BVW.CPP $(EX05BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX05BVW.CPP


$(PROJ).EXE::	EX05B.RES

$(PROJ).EXE::	STDAFX.OBJ EX05B.OBJ MAINFRM.OBJ EX05BDOC.OBJ EX05BVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX05B.OBJ +
MAINFRM.OBJ +
EX05BDOC.OBJ +
EX05BVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX05B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX05B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX05B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
