# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX16A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = 
R_RCDEFINES = 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX16A\
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
CFLAGS_R_WEXE = /nologo /f- /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:8192 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:8192 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z 
RESFLAGS = /nologo /t 
RUNFLAGS = 
DEFFILE = EX16A.DEF
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
		EX16A.SBR \
		MAINFRM.SBR \
		STUDOC.SBR \
		STUVIEW.SBR \
		STUDENT.SBR


EX16A_RCDEP = c:\vcpp\ex16a\res\ex16a.ico \
	c:\vcpp\ex16a\res\ex16a.rc2


STDAFX_DEP = c:\vcpp\ex16a\stdafx.h


EX16A_DEP = c:\vcpp\ex16a\stdafx.h \
	c:\vcpp\ex16a\ex16a.h \
	c:\vcpp\ex16a\mainfrm.h \
	c:\vcpp\ex16a\studoc.h \
	c:\vcpp\ex16a\stuview.h


MAINFRM_DEP = c:\vcpp\ex16a\stdafx.h \
	c:\vcpp\ex16a\ex16a.h \
	c:\vcpp\ex16a\mainfrm.h


STUDOC_DEP = c:\vcpp\ex16a\stdafx.h \
	c:\vcpp\ex16a\studoc.h


STUVIEW_DEP = c:\vcpp\ex16a\stdafx.h \
	c:\vcpp\ex16a\student.h \
	c:\vcpp\ex16a\studoc.h \
	c:\vcpp\ex16a\stuview.h


STUDENT_DEP = c:\vcpp\ex16a\stdafx.h \
	c:\vcpp\ex16a\student.h


all:	$(PROJ).EXE

EX16A.RES:	EX16A.RC $(EX16A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX16A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX16A.OBJ:	EX16A.CPP $(EX16A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX16A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

STUDOC.OBJ:	STUDOC.CPP $(STUDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDOC.CPP

STUVIEW.OBJ:	STUVIEW.CPP $(STUVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUVIEW.CPP

STUDENT.OBJ:	STUDENT.CPP $(STUDENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDENT.CPP


$(PROJ).EXE::	EX16A.RES

$(PROJ).EXE::	STDAFX.OBJ EX16A.OBJ MAINFRM.OBJ STUDOC.OBJ STUVIEW.OBJ STUDENT.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX16A.OBJ +
MAINFRM.OBJ +
STUDOC.OBJ +
STUVIEW.OBJ +
STUDENT.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX16A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX16A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX16A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
