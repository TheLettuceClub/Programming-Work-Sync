# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX12B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX12B\
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
DEFFILE = EX12B.DEF
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
		EX12B.SBR \
		MAINFRM.SBR \
		EX12BDOC.SBR \
		EX12BVW.SBR


EX12B_RCDEP = c:\vcpp\ex12b\res\ex12b.ico \
	c:\vcpp\ex12b\res\ex12b.rc2


STDAFX_DEP = c:\vcpp\ex12b\stdafx.h


EX12B_DEP = c:\vcpp\ex12b\stdafx.h \
	c:\vcpp\ex12b\ex12b.h \
	c:\vcpp\ex12b\mainfrm.h \
	c:\vcpp\ex12b\ex12bdoc.h \
	c:\vcpp\ex12b\ex12bvw.h


MAINFRM_DEP = c:\vcpp\ex12b\stdafx.h \
	c:\vcpp\ex12b\ex12b.h \
	c:\vcpp\ex12b\mainfrm.h


EX12BDOC_DEP = c:\vcpp\ex12b\stdafx.h \
	c:\vcpp\ex12b\ex12b.h \
	c:\vcpp\ex12b\ex12bdoc.h


EX12BVW_DEP = c:\vcpp\ex12b\stdafx.h \
	c:\vcpp\ex12b\ex12b.h \
	c:\vcpp\ex12b\ex12bdoc.h \
	c:\vcpp\ex12b\ex12bvw.h


all:	$(PROJ).EXE

EX12B.RES:	EX12B.RC $(EX12B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX12B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX12B.OBJ:	EX12B.CPP $(EX12B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX12B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX12BDOC.OBJ:	EX12BDOC.CPP $(EX12BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX12BDOC.CPP

EX12BVW.OBJ:	EX12BVW.CPP $(EX12BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX12BVW.CPP


$(PROJ).EXE::	EX12B.RES

$(PROJ).EXE::	STDAFX.OBJ EX12B.OBJ MAINFRM.OBJ EX12BDOC.OBJ EX12BVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX12B.OBJ +
MAINFRM.OBJ +
EX12BDOC.OBJ +
EX12BVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX12B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX12B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX12B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
