# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX07B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX07B\
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
DEFFILE = EX07B.DEF
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
		EX07B.SBR \
		MAINFRM.SBR \
		EX07BDOC.SBR \
		EX07BVW.SBR \
		EX07BDLG.SBR


EX07B_RCDEP = c:\vcpp\ex07b\res\ex07b.ico \
	c:\vcpp\ex07b\res\toolbar.bmp \
	c:\vcpp\ex07b\res\ex07b.rc2


STDAFX_DEP = c:\vcpp\ex07b\stdafx.h


EX07B_DEP = c:\vcpp\ex07b\stdafx.h \
	c:\vcpp\ex07b\ex07b.h \
	c:\vcpp\ex07b\mainfrm.h \
	c:\vcpp\ex07b\ex07bdoc.h \
	c:\vcpp\ex07b\ex07bvw.h


MAINFRM_DEP = c:\vcpp\ex07b\stdafx.h \
	c:\vcpp\ex07b\ex07b.h \
	c:\vcpp\ex07b\mainfrm.h


EX07BDOC_DEP = c:\vcpp\ex07b\stdafx.h \
	c:\vcpp\ex07b\ex07b.h \
	c:\vcpp\ex07b\ex07bdoc.h


EX07BVW_DEP = c:\vcpp\ex07b\stdafx.h \
	c:\vcpp\ex07b\ex07b.h \
	c:\vcpp\ex07b\ex07bdoc.h \
	c:\vcpp\ex07b\ex07bvw.h


all:	$(PROJ).EXE

EX07B.RES:	EX07B.RC $(EX07B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX07B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX07B.OBJ:	EX07B.CPP $(EX07B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX07BDOC.OBJ:	EX07BDOC.CPP $(EX07BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07BDOC.CPP

EX07BVW.OBJ:	EX07BVW.CPP $(EX07BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07BVW.CPP

EX07BDLG.OBJ:	EX07BDLG.CPP $(EX07BDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07BDLG.CPP


$(PROJ).EXE::	EX07B.RES

$(PROJ).EXE::	STDAFX.OBJ EX07B.OBJ MAINFRM.OBJ EX07BDOC.OBJ EX07BVW.OBJ EX07BDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX07B.OBJ +
MAINFRM.OBJ +
EX07BDOC.OBJ +
EX07BVW.OBJ +
EX07BDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX07B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX07B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX07B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
