# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX11B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX11B\
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
DEFFILE = EX11B.DEF
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
		EX11B.SBR \
		MAINFRM.SBR \
		EX11BDOC.SBR \
		EX11BVW.SBR \
		EX11BDLG.SBR


EX11B_RCDEP = c:\vcpp\ex11b\res\ex11b.ico \
	c:\vcpp\ex11b\res\toolbar.bmp \
	c:\vcpp\ex11b\res\ex11b.rc2


STDAFX_DEP = c:\vcpp\ex11b\stdafx.h


EX11B_DEP = c:\vcpp\ex11b\stdafx.h \
	c:\vcpp\ex11b\ex11b.h \
	c:\vcpp\ex11b\mainfrm.h \
	c:\vcpp\ex11b\ex11bdoc.h \
	c:\vcpp\ex11b\ex11bvw.h


MAINFRM_DEP = c:\vcpp\ex11b\stdafx.h \
	c:\vcpp\ex11b\ex11b.h \
	c:\vcpp\ex11b\mainfrm.h


EX11BDOC_DEP = c:\vcpp\ex11b\stdafx.h \
	c:\vcpp\ex11b\ex11b.h \
	c:\vcpp\ex11b\ex11bdoc.h


EX11BVW_DEP = c:\vcpp\ex11b\stdafx.h \
	c:\vcpp\ex11b\ex11b.h \
	c:\vcpp\ex11b\ex11bdoc.h \
	c:\vcpp\ex11b\ex11bvw.h


all:	$(PROJ).EXE

EX11B.RES:	EX11B.RC $(EX11B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX11B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX11B.OBJ:	EX11B.CPP $(EX11B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX11BDOC.OBJ:	EX11BDOC.CPP $(EX11BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11BDOC.CPP

EX11BVW.OBJ:	EX11BVW.CPP $(EX11BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11BVW.CPP

EX11BDLG.OBJ:	EX11BDLG.CPP $(EX11BDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11BDLG.CPP


$(PROJ).EXE::	EX11B.RES

$(PROJ).EXE::	STDAFX.OBJ EX11B.OBJ MAINFRM.OBJ EX11BDOC.OBJ EX11BVW.OBJ EX11BDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX11B.OBJ +
MAINFRM.OBJ +
EX11BDOC.OBJ +
EX11BVW.OBJ +
EX11BDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX11B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX11B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX11B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
