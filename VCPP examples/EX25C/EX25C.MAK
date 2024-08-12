# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX25C
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX25C\
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
CFLAGS_D_WDLL = /nologo /G2 /W3 /ALw /Od /D "_DEBUG" /D "_USRDLL" /GD /Fp"..\dllafx.pch" 
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /D "_USRDLL" /GD /Fp"EX25D.PCH" 
LFLAGS_D_WDLL = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WDLL = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = lafxdwd oldnames libw ldllcew compobj storage ole2 ole2disp ole2nls mfcoleui commdlg.lib shell.lib 
LIBS_R_WDLL = lafxdw oldnames libw ldllcew compobj storage ole2 ole2disp ole2nls mfcoleui commdlg.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo /k /t 
RUNFLAGS = 
DEFFILE = EX25C.DEF
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
SBRS = STDAFX.SBR \
		CVARIANT.SBR \
		EX25C.SBR \
		EX25CAUT.SBR


STDAFX_DEP = c:\vcpp\ex25c\stdafx.h


CVARIANT_DEP = c:\vcpp\ex25c\stdafx.h \
	c:\vcpp\ex25c\cvariant.h


EX25C_DEP = c:\vcpp\ex25c\stdafx.h \
	c:\vcpp\ex25c\prompt.h


EX25CAUT_DEP = c:\vcpp\ex25c\stdafx.h \
	c:\vcpp\ex25c\ex25caut.h \
	c:\vcpp\ex25c\cvariant.h \
	c:\vcpp\ex25c\prompt.h


all:	$(PROJ).DLL

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

CVARIANT.OBJ:	CVARIANT.CPP $(CVARIANT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CVARIANT.CPP

EX25C.OBJ:	EX25C.CPP $(EX25C_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25C.CPP

EX25CAUT.OBJ:	EX25CAUT.CPP $(EX25CAUT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25CAUT.CPP

EX25C.RES:	EX25C.RC $(EX25C_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX25C.RC


$(PROJ).DLL::	EX25C.RES

$(PROJ).DLL::	STDAFX.OBJ CVARIANT.OBJ EX25C.OBJ EX25CAUT.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
CVARIANT.OBJ +
EX25C.OBJ +
EX25CAUT.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
J:\+
C:\MSVC15\LIB\+
C:\MSVC15\MFC\LIB\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX25C.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	EX25C.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX25C.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
