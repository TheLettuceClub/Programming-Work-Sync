# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX26AD
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX26A\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = EX26A.CPP   
RC = rc
CFLAGS_D_WDLL = /G2 /W3 /AL /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf 
CFLAGS_R_WDLL = /nologo /f- /W3 /AL /O1 /D "NDEBUG" /D "_AFXDLL" /GD /GEf 
LFLAGS_D_WDLL = /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL         
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL         
LIBS_D_WDLL = mfc250d oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = mfc250 oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = EX26AD.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = EX26A.SBR \
		PERSIST.SBR \
		ROWVIEW.SBR \
		STUDENT.SBR


EX26A_DEP = c:\vcpp\ex26a\stdafx.h


PERSIST_DEP = c:\vcpp\ex26a\stdafx.h \
	c:\vcpp\ex26a\persist.h


ROWVIEW_DEP = c:\vcpp\ex26a\stdafx.h \
	c:\vcpp\ex26a\rowview.h


STUDENT_DEP = c:\vcpp\ex26a\stdafx.h


STUDENT_DEP = c:\vcpp\ex26a\student.h


all:	$(PROJ).DLL

EX26A.OBJ:	EX26A.CPP $(EX26A_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c EX26A.CPP

PERSIST.OBJ:	PERSIST.CPP $(PERSIST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PERSIST.CPP

ROWVIEW.OBJ:	ROWVIEW.CPP $(ROWVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ROWVIEW.CPP

EX26A.RES:	EX26A.RC $(EX26A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX26A.RC

STUDENT.OBJ:	STUDENT.CPP $(STUDENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDENT.CPP


$(PROJ).DLL::	EX26A.RES

$(PROJ).DLL::	EX26A.OBJ PERSIST.OBJ ROWVIEW.OBJ STUDENT.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
EX26A.OBJ +
PERSIST.OBJ +
ROWVIEW.OBJ +
STUDENT.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX26A.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	EX26A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX26A.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
