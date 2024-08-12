# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX15B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = 
R_RCDEFINES = 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX15B\
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
CFLAGS_D_WEXE = /nologo /Gs /G2 /Zp1 /W3 /AM /Od /D "_DEBUG" /GA /Fp"..\stdafx.pch" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mafxcwd commdlg shell olecli olesvr mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mafxcw commdlg shell olecli olesvr mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z 
RESFLAGS = /nologo /t 
RUNFLAGS = 
DEFFILE = EX15B.DEF
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
		EX15B.SBR \
		MAINFRM.SBR \
		STUDOC.SBR \
		STUVIEW.SBR \
		STUDENT.SBR


EX15B_RCDEP = c:\vcpp\ex15b\res\ex15b.ico \
	c:\vcpp\ex15b\res\ex15b.rc2


STDAFX_DEP = c:\vcpp\ex15b\stdafx.h


EX15B_DEP = c:\vcpp\ex15b\stdafx.h \
	c:\vcpp\ex15b\ex15b.h \
	c:\vcpp\ex15b\mainfrm.h \
	c:\vcpp\ex15b\student.h \
	c:\vcpp\ex15b\studoc.h \
	c:\vcpp\ex15b\stuview.h


MAINFRM_DEP = c:\vcpp\ex15b\stdafx.h \
	c:\vcpp\ex15b\ex15b.h \
	c:\vcpp\ex15b\mainfrm.h


STUDOC_DEP = c:\vcpp\ex15b\stdafx.h \
	c:\vcpp\ex15b\student.h \
	c:\vcpp\ex15b\studoc.h


STUVIEW_DEP = c:\vcpp\ex15b\stdafx.h \
	c:\vcpp\ex15b\student.h \
	c:\vcpp\ex15b\studoc.h \
	c:\vcpp\ex15b\stuview.h


STUDENT_DEP = c:\vcpp\ex15b\stdafx.h \
	c:\vcpp\ex15b\student.h


all:	$(PROJ).EXE

EX15B.RES:	EX15B.RC $(EX15B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX15B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX15B.OBJ:	EX15B.CPP $(EX15B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX15B.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

STUDOC.OBJ:	STUDOC.CPP $(STUDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDOC.CPP

STUVIEW.OBJ:	STUVIEW.CPP $(STUVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUVIEW.CPP

STUDENT.OBJ:	STUDENT.CPP $(STUDENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDENT.CPP


$(PROJ).EXE::	EX15B.RES

$(PROJ).EXE::	STDAFX.OBJ EX15B.OBJ MAINFRM.OBJ STUDOC.OBJ STUVIEW.OBJ STUDENT.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX15B.OBJ +
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
	$(RC) $(RESFLAGS) EX15B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX15B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX15B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
