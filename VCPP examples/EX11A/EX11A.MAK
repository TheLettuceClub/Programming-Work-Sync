# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX11A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX11A\
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
DEFFILE = EX11A.DEF
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
		EX11A.SBR \
		MAINFRM.SBR \
		EX11ADOC.SBR \
		EX11AVW.SBR \
		EX11ADLG.SBR


EX11A_RCDEP = c:\vcpp\ex11a\res\ex11a.ico \
	c:\vcpp\ex11a\res\toolbar.bmp \
	c:\vcpp\ex11a\res\ex11a.rc2


STDAFX_DEP = c:\vcpp\ex11a\stdafx.h


EX11A_DEP = c:\vcpp\ex11a\stdafx.h \
	c:\vcpp\ex11a\ex11a.h \
	c:\vcpp\ex11a\mainfrm.h \
	c:\vcpp\ex11a\ex11adoc.h \
	c:\vcpp\ex11a\ex11avw.h


MAINFRM_DEP = c:\vcpp\ex11a\stdafx.h \
	c:\vcpp\ex11a\ex11a.h \
	c:\vcpp\ex11a\mainfrm.h


EX11ADOC_DEP = c:\vcpp\ex11a\stdafx.h \
	c:\vcpp\ex11a\ex11a.h \
	c:\vcpp\ex11a\ex11adoc.h


EX11AVW_DEP = c:\vcpp\ex11a\stdafx.h \
	c:\vcpp\ex11a\ex11a.h \
	c:\vcpp\ex11a\ex11adoc.h \
	c:\vcpp\ex11a\ex11avw.h


all:	$(PROJ).EXE

EX11A.RES:	EX11A.RC $(EX11A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX11A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX11A.OBJ:	EX11A.CPP $(EX11A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX11ADOC.OBJ:	EX11ADOC.CPP $(EX11ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11ADOC.CPP

EX11AVW.OBJ:	EX11AVW.CPP $(EX11AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11AVW.CPP

EX11ADLG.OBJ:	EX11ADLG.CPP $(EX11ADLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11ADLG.CPP


$(PROJ).EXE::	EX11A.RES

$(PROJ).EXE::	STDAFX.OBJ EX11A.OBJ MAINFRM.OBJ EX11ADOC.OBJ EX11AVW.OBJ EX11ADLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX11A.OBJ +
MAINFRM.OBJ +
EX11ADOC.OBJ +
EX11AVW.OBJ +
EX11ADLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX11A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX11A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX11A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
