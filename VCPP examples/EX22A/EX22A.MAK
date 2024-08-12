# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX22A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX22A\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = /YcSTDAFX.H
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = /YuSTDAFX.H
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /AM /Od /D "_DEBUG" /GA /Fp"..\stdafx.pch" 
CFLAGS_R_WEXE = /nologo /f- /G2 /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:8192 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mafxcwd mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mafxcw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX22A.DEF
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
		EX22A.SBR


STDAFX_DEP = c:\vcpp\ex22a\stdafx.h


EX22A_RCDEP = c:\vcpp\ex22a\res\ex22a.ico


EX22A_DEP = c:\vcpp\ex22a\stdafx.h \
	c:\vcpp\ex22a\ex22a.h


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX22A.RES:	EX22A.RC $(EX22A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX22A.RC

EX22A.OBJ:	EX22A.CPP $(EX22A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX22A.CPP


$(PROJ).EXE::	EX22A.RES

$(PROJ).EXE::	STDAFX.OBJ EX22A.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX22A.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX22A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX22A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX22A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
