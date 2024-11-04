#if 0 //To compile, use MSVC 6.0 (or above) and type "nmake rubix.c"; dan: removed " /opt:nowin98" at the end because we don't need to worry about that anymore
rubix.exe: rubix.obj cwinmain.obj bjwsolve.obj bjwsolve2.obj bjwsolve3.obj bjwsolve4.obj bjwhc.obj
	link    rubix.obj cwinmain.obj bjwsolve.obj bjwsolve2.obj bjwsolve3.obj bjwsolve4.obj bjwhc.obj\
			  user32.lib gdi32.lib comdlg32.lib winmm.lib
	del rubix.obj
rubix.obj:    rubix.c cwinmain.h; cl /c /J /TP rubix.c     /Ox /Ob2 /G6Fy /MD /nologo
bjwsolve.obj: bjwsolve.c;         cl /c /J /TP bjwsolve.c  /Ox /Ob2 /G6Fy /MD /nologo
bjwsolve2.obj:bjwsolve2.c;        cl /c /J /TP bjwsolve2.c /Ox /Ob2 /G6Fy /MD /nologo
bjwsolve3.obj:bjwsolve3.c;        cl /c /J /TP bjwsolve3.c /Ox /Ob2 /G6Fy /MD /nologo
bjwsolve4.obj:bjwsolve4.c;        cl /c /J /TP bjwsolve4.c /Ox /Ob2 /G6Fy /MD /nologo
bjwhc.obj:    bjwhc.c;            cl /c /J /TP bjwhc.c     /Ox /Ob2 /G6Fy /MD /nologo
cwinmain.obj: cwinmain.c;         cl /c /J /TP cwinmain.c  /Ox /Ob2 /G6Fy /MD /nologo
!if 0
#endif

/***************************************************************************************************
RUBIX.C written by Ken Silverman (http://advsys.net/ken), (1998-2007)

For hints on compiling, please refer to the 'introduction' section from here:
	http://advsys.net/ken/voxlap/readme.txt
Note that some of it is specific to the Voxlap distribution, although most of it still applies here.

License: You may use this code for non-commercial purposes as long as credit is maintained.
***************************************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cwinmain.h"

#define MAXYDIM 2048
#define MAXCDIM 256 //NOTE:MAXCDIM must be even
#define PI 3.141592653589793

extern int rubixsolve_bjw (int n, int mem_n, char *facelist, unsigned short *rotlist, int quality);

HINSTANCE ghinst;
static int pal[256];
static int cputype = 0;
static tiletype gdd;

static HCURSOR ghcrosscurs = 0, ghhandcurs = 0;
static HCURSOR gencrosscursor (void)
{
	unsigned int buf1[32], buf0[32];
	int i, j, x, y;

	memset(buf1,-1,sizeof(buf1)); memset(buf0,0,sizeof(buf0));

		//   ∞∞              ∞∞
		// ∞∞€€∞∞          ∞∞€€∞∞
		//   ∞∞€€∞∞      ∞∞€€∞∞
		//     ∞∞€€∞∞  ∞∞€€∞∞
		//       ∞∞      ∞∞
		//
		//       ∞∞      ∞∞
		//     ∞∞€€∞∞  ∞∞€€∞∞
		//   ∞∞€€∞∞      ∞∞€€∞∞
		// ∞∞€€∞∞          ∞∞€€∞∞
		//   ∞∞              ∞∞
		//
		//buf1 buf0 display:
		// 0    0   black
		// 0    1   white
		// 1    0   transparent
		// 1    1   xor

	for(j=4;j;j--)
	{
		x = 16+((j&1)<<2)-2; y = 16+(j&2)  -1; buf1[y] &= ~(1<<(x^7)); buf0[y] |= (1<<(x^7)); //white
		x = 16+((j&1)<<3)-4; y = 16+(j&2)*5-5; buf1[y] &= ~(1<<(x^7)); buf0[y] |= (1<<(x^7)); //white
		for(i=4;i>1;i--)
		{
			if (j&1) x = 16+i; else x = 16-i;
			if (j&2) y = 16+i; else y = 16-i;
			buf1[y] &= ~(1<<(x^7));                                //black
			buf1[y] &= ~(1<<((x+1)^7)); buf0[y] |= (1<<((x+1)^7)); //white
			buf1[y] &= ~(1<<((x-1)^7)); buf0[y] |= (1<<((x-1)^7)); //white
		}
	}

	return(CreateCursor(ghinst,16,16,32,32,buf1,buf0));
}
static HCURSOR genhandcursor (void) //Hand icon shamelessly lifted from Acrobat and then optimized :P
{
	static const short handwhite[] = {0,0x180,0x19b0,0x19b0,0xdb2,0xdb6,0x7f6,0x67fe,0x77fc,0x3ffc,0x1ffc,0x1ff8,0xff8,0x7f0,0x3f0,0x3f0,0};
	unsigned int buf1[32], buf0[32];
	int x, y;

	memset(buf1,-1,sizeof(buf1)); memset(buf0,0,sizeof(buf0));
	for(y=8;y<24;y++)
		for(x=8;x<24;x++)
		{
			if (handwhite[y-8]&(1<<(23-x))) { buf1[y] &= ~(1<<(x^7)); buf0[y] |= (1<<(x^7)); } //white
			else if ((handwhite[y+1-8]&(1<<(23-x))) || (handwhite[y-8]&_lrotl(5,22-x))) buf1[y] &= ~(1<<(x^7)); //black if there's a white down, left or right
		}
	return(CreateCursor(ghinst,16,16,32,32,buf1,buf0));
}

typedef struct { float x, y; } point2d;
typedef struct { float x, y, z; } point3d;
typedef struct { float x, y, z, u, v; } vertyp;
static point3d c3, i3, j3, k3, ii3, jj3, kk3;
static float a1v = 0, a2v = 0, a3v = 0, ghx, ghy, ghz, fmousx, fmousy, fsearchx, fsearchy;
static float rotang, rotcnt, rotinc, rotmul, colwidth = .91, ocolwidth, rotatespeed = 16.0;
static int cdim = 3, rotaxis, rotslice, rotnum, timermode, doscrcap = 0;
static int ylookup[MAXYDIM], lastx[MAXYDIM];
static int searchx, searchy, searchstat;
static int cgrabx, cgraby, cgrabz, cgrabs, ocgrabx, ocgraby, ocgrabz, ocgrabs;
static int order[4][MAXCDIM], cdimm1, cdimm1tMAXCDIM;
static int showothercubemode = 0, anglemode = 0, visualdetail = 2;
static int editmode = 0, curcolindex = 3;
static int obstatus = 0, mouseoutstat = 0;
static float winstate = -1, winshade = 1.0;
char cubefacecol[6*MAXCDIM*MAXCDIM];
static char ocubefacecol[6*MAXCDIM*MAXCDIM]; //For 'c' mode
static char *drawcubefacecol = cubefacecol;
static char ptface[6][4];

#define EDITPATCHMAX 65536
static int editpatches[EDITPATCHMAX], editpatchcnt = 0, editpatchbeg = 0, editpatchend = 0; //6*(6*MAXCDIM*MAXCDIM)

static char notation3[6] = {'L','R','U','D','F','B'};
#define ROTSAVSIZ 524288
	//< 02/17/2007: 'rotsav'  format: (slice{0..MAXCDIM-1}<<3) + (axis{0..2}<<1) + numtimes{1,3}
	//>=02/17/2007: 'rotsav2' format: (slice{0..MAXCDIM-1}<<4) + (axis{0..2}<<2) + numtimes{1,2,3}
	//>=02/17/2007: 'rotsav3' format:
	//    1:L   2:L2   3:L'
	//    5:U'  6:U2   7:U
	//    9:F  10:F2  11:F'
	// ( 17:M  18:M2  19:M' )
	// ( 21:E  22:E2  23:E' )
	// ( 25:S  26:S2  27:S' )
	//   33:R' 34:R2  35:R
	//   37:D  38:D2  39:D'
	//   41:B' 42:B2  43:B
static unsigned short rotsav[ROTSAVSIZ], orotsav[ROTSAVSIZ]; //For 'c' mode
static int rotsavbeg = 0, rotsavcur = 0, rotsavend = 0; //rotsavcur:current, rotsavnum:last_written
static int orotsavbeg = 0, orotsavcur = 0, orotsavend = 0; //For 'c' mode

static int backcol, crackcol;
#define STICKERSIZ 128
static int stickertex[13][STICKERSIZ][STICKERSIZ];

char message[1024] = "";
static int messagetimeout = 0;

static __int64 qperfrq, qtotclk, startotclk;
static int ltotclk, startimer, stoptimer;
static float fsynctics;
static double rperfrq;

static HMENU gmenu = 0;
enum
{
	FILENEW,FILELOAD,FILESAVE,SCREENCAP,FILEEXIT,
	CUBESIZE,CUBECOPY=CUBESIZE+8,CUBEPASTE,CUBEERASE,CUBERAND1,CUBERANDALL,
	HISTBACK,HISTFORW,HISTHOME,HISTEND,
	SOLVE,
	OPTROTSPEED=SOLVE+6,OPTRESETORI=OPTROTSPEED+9,OPTANGLE,OPTBACKCOL,OPTCRACKCOL,OPTEDITCUBE,
	VISUALDETAIL,HELPABOUT=VISUALDETAIL+3,
};

void drawblackrect(int x1, int y1, int z1, int x2, int y2, int z2, int side);
void drawcube(int x, int y, int z);

//======================== CPU detection code begins ========================

#ifdef _MSC_VER

#pragma warning(disable:4799) //I know how to use EMMS

static _inline int testflag (int c)
{
	_asm
	{
		mov ecx, c
		pushfd
		pop eax
		mov edx, eax
		xor eax, ecx
		push eax
		popfd
		pushfd
		pop eax
		xor eax, edx
		mov eax, 1
		jne menostinx
		xor eax, eax
		menostinx:
	}
}

static _inline void cpuid (int a, int *s)
{
	_asm
	{
		push ebx
		push esi
		mov eax, a
		cpuid
		mov esi, s
		mov dword ptr [esi+0], eax
		mov dword ptr [esi+4], ebx
		mov dword ptr [esi+8], ecx
		mov dword ptr [esi+12], edx
		pop esi
		pop ebx
	}
}

	//Bit numbers of return value:
	//0:FPU, 4:RDTSC, 15:CMOV, 22:MMX+, 23:MMX, 25:SSE, 26:SSE2, 30:3DNow!+, 31:3DNow!
static int getcputype (void)
{
	int i, cpb[4], cpid[4];
	if (!testflag(0x200000)) return(0);
	cpuid(0,cpid); if (!cpid[0]) return(0);
	cpuid(1,cpb); i = (cpb[3]&~((1<<22)|(1<<30)|(1<<31)));
	cpuid(0x80000000,cpb);
	if (((unsigned int)cpb[0]) > 0x80000000)
	{
		cpuid(0x80000001,cpb);
		i |= (cpb[3]&(1<<31));
		if (!((cpid[1]^0x68747541)|(cpid[3]^0x69746e65)|(cpid[2]^0x444d4163))) //AuthenticAMD
			i |= (cpb[3]&((1<<22)|(1<<30)));
	}
	if (i&(1<<25)) i |= (1<<22); //SSE implies MMX+ support
	return(i);
}

#else
static int getcputype (void) { return(0); }
#endif
//========================= CPU detection code ends =========================

#ifdef _MSC_VER

	//Precision: bits 8-9:, Rounding: bits 10-11:
	//00 = 24-bit    (0)   00 = nearest/even (0)
	//01 = reserved  (1)   01 = -inf         (4)
	//10 = 53-bit    (2)   10 = inf          (8)
	//11 = 64-bit    (3)   11 = 0            (c)
static int fpuasm[2];
static _inline void fpuinit (int a)
{
	_asm
	{
		mov eax, a
		fninit
		fstcw fpuasm
		and byte ptr fpuasm[1], 0f0h
		or byte ptr fpuasm[1], al
		fldcw fpuasm
	}
}

static _inline void ftol (float f, int *a)
{
	//(*a) = (int)(f+1);
	_asm
	{
		mov eax, a
		fld f
		fistp dword ptr [eax]
	}
}

static _inline void fcossin (float a, float *c, float *s)
{
	_asm
	{
		fld a
		fsincos
		mov eax, c
		fstp dword ptr [eax]
		mov eax, s
		fstp dword ptr [eax]
	}
}

static _inline void clearbuflongsafe (void *d, int c, int a)
{
	_asm
	{
		push edi
		mov edi, d
		mov ecx, c
		mov eax, a
		test ecx, ecx
		jle short skip1
		rep stosd
skip1:pop edi
	}
}

static _inline void clearbufshortsafe (void *d, int c, int a)
{
	_asm
	{
		push edi
		mov edi, d
		mov edx, c
		mov eax, a
		mov ecx, edi
		and ecx, 1
		sub edx, ecx
		jle short skip1
		rep stosw
		mov ecx, edx
		and edx, 1
		shr ecx, 1
		rep stosd
skip1:add ecx, edx
		jl short skip2
		rep stosw
skip2:pop edi
	}
}

static _inline void clearbufbytesafe (void *d, int c, int a)
{
	_asm
	{
		push edi
		mov edi, d
		mov edx, c
		mov eax, a
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub edx, ecx
		jle short skip1
		rep stosb
		mov ecx, edx
		and edx, 3
		shr ecx, 2
		rep stosd
skip1:add ecx, edx
		jl short skip3
		rep stosb
skip3:pop edi
	}
}

static _inline void qinterpolatedown16 (void *a, int c, int d, int s)
{
	_asm
	{
		push ebx
		push esi
		push edi
		mov eax, a
		mov ecx, c
		mov edx, d
		mov esi, s
		mov ebx, ecx
		shr ecx, 1
		jz skipbegcalc
begqcalc:lea edi, [edx+esi]
		sar edx, 16
		mov dword ptr [eax], edx
		lea edx, [edi+esi]
		sar edi, 16
		mov dword ptr [eax+4], edi
		add eax, 8
		dec ecx
		jnz begqcalc
		test ebx, 1
		jz skipbegqcalc2
		skipbegcalc: sar edx, 16
		mov dword ptr [eax], edx
skipbegqcalc2:
		pop edi
		pop esi
		pop ebx
	}
}

#else
#pragma message ("Compiler says it isn't Visual C.");
#endif

static void sticker_init (void)
{
	static int ocols[6] = {0,0,0,0,0,0};
	float nu, nv;
	int i, j, u, v, instick;

	if ((pal[0+1] == ocols[0]) && (pal[1+1] == ocols[1]) && (pal[2+1] == ocols[2]) &&
		 (pal[3+1] == ocols[3]) && (pal[4+1] == ocols[4]) && (pal[5+1] == ocols[5]) &&
		 (pal[6+1] == ocols[6])) return;
	for(i=0;i<6;i++)
	{
		j = pal[i+1]; ocols[i] = j;
		for(v=0;v<STICKERSIZ;v++)
			for(u=0;u<STICKERSIZ;u++)
			{
				nu = (u+.5)/(float)STICKERSIZ; nv = (v+.5)/(float)STICKERSIZ;
				nu = fabs(nu-.5);
				nv = fabs(nv-.5);
				instick = 0;
				if ((nu+nu < colwidth) && (nv+nv < colwidth))
				{
					nu = max(nu+.08-colwidth*.5,0);
					nv = max(nv+.08-colwidth*.5,0);
					if (nu*nu + nv*nv < .08*.08) { stickertex[i][v][u] = j; instick = 1; }
				}
				if (!instick) stickertex[i][v][u] = crackcol;
				stickertex[i][v][u] ^= ((rand()<<15)+rand())&0x0f0f0f;

				stickertex[i+6][v][u] = stickertex[i][v][u];
				if ((instick) && ((labs(v-u) < (STICKERSIZ>>3)) || (labs(v+u-STICKERSIZ) < (STICKERSIZ>>3))))
					stickertex[i+6][v][u] ^= 0x808080;
			}
	}
	for(v=0;v<STICKERSIZ;v++)
		for(u=0;u<STICKERSIZ;u++)
			stickertex[12][v][u] = (crackcol^(((rand()<<15)+rand())&0x0f0f0f));
}

static void menu_update_cdim (void)
{
	MENUITEMINFO mii;
	int i;

	for(i=1;i<=8;i++) CheckMenuItem(gmenu,i+CUBESIZE-1,(-(cdim==i))&MF_CHECKED);

	memset(&mii,0,sizeof(MENUITEMINFO));
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STATE;
	for(i=0;i<6;i++)
	{
		if ((cdim == 3) || ((cdim == 2) && (i < 2)) || (!i)) mii.fState = MFS_ENABLED;
																		else mii.fState = MFS_GRAYED;
		SetMenuItemInfo(gmenu,SOLVE+i,0,&mii);
	}
}

static void resetcube (void)
{
	memset(&cubefacecol[0*MAXCDIM*MAXCDIM],1,MAXCDIM*MAXCDIM);
	memset(&cubefacecol[1*MAXCDIM*MAXCDIM],2,MAXCDIM*MAXCDIM);
	memset(&cubefacecol[2*MAXCDIM*MAXCDIM],3,MAXCDIM*MAXCDIM);
	memset(&cubefacecol[3*MAXCDIM*MAXCDIM],4,MAXCDIM*MAXCDIM);
	memset(&cubefacecol[4*MAXCDIM*MAXCDIM],5,MAXCDIM*MAXCDIM);
	memset(&cubefacecol[5*MAXCDIM*MAXCDIM],6,MAXCDIM*MAXCDIM);
	showothercubemode = 0;
	rotsavbeg = rotsavcur = rotsavend = 0;
	timermode = -1;
	c3.z = (cdim<<1);
	cdimm1 = cdim-1;
	cdimm1tMAXCDIM = cdimm1*MAXCDIM;
}

static void clearkeys (void)
{
	memset(keystatus,0,sizeof(keystatus)); bstatus = 0;
}

static void saverubix (char *v)
{
	FILE *fil;
	int i, x, y;

	fil = fopen(v,"w"); if (!fil) { MessageBox(ghwnd,"Error saving!",prognam,MB_OK); clearkeys(); return; }

	fprintf(fil,"RUBIX save game. Edit at your own risk!\n");
	fprintf(fil,"cubedim=%d\n",cdim);
	fprintf(fil,"cubefacecol=\n");
	for(x=0;x<cdim*2-1;x++) fputc('-',fil);
	fputc('\n',fil);
	for(i=0;i<6;i++)
	{
		for(y=0;y<cdim;y++)
		{
			for(x=0;x<cdim;x++)
			{
				fputc(cubefacecol[(i*MAXCDIM+x)*MAXCDIM+y]+'0',fil);
				if (x < cdim-1) fputc(',',fil);
			}
			fputc('\n',fil);
		}
		for(x=0;x<cdim*2-1;x++) fputc('-',fil);
		fputc('\n',fil);
	}
	fprintf(fil,"showothercubemode=%d\n",showothercubemode);
	if (showothercubemode)
	{
		for(x=0;x<cdim*2-1;x++) fputc('-',fil);
		fputc('\n',fil);
		for(i=0;i<6;i++)
		{
			for(y=0;y<cdim;y++)
			{
				for(x=0;x<cdim;x++)
				{
					fputc(ocubefacecol[(i*MAXCDIM+x)*MAXCDIM+y]+'0',fil);
					if (x < cdim-1) fputc(',',fil);
				}
				fputc('\n',fil);
			}
			for(x=0;x<cdim*2-1;x++) fputc('-',fil);
			fputc('\n',fil);
		}
	}

	fprintf(fil,"anglemode=%d\n",anglemode);
	if (!anglemode)
		fprintf(fil,"angles=%f,%f,%f\n",a1v,a2v,a3v);
	else
	{
		fprintf(fil,"veci=%f,%f,%f\n",i3.x,i3.y,i3.z);
		fprintf(fil,"vecj=%f,%f,%f\n",j3.x,j3.y,j3.z);
		fprintf(fil,"veck=%f,%f,%f\n",k3.x,k3.y,k3.z);
	}
	fprintf(fil,"rotatespeed=%g\n",rotatespeed);
	fprintf(fil,"visualdetail=%d\n",visualdetail);
	fprintf(fil,"editmode=%d\n",editmode);
	fprintf(fil,"curcolindex=%d\n",curcolindex);

	for(i=1;i<=6;i++) fprintf(fil,"RGB%d=%d,%d,%d\n",i,(pal[i]>>16)&255,(pal[i]>>8)&255,pal[i]&255);
	fprintf(fil,"RGBBACK=%d,%d,%d\n",(backcol>>16)&255,(backcol>>8)&255,backcol&255);
	fprintf(fil,"RGBCRACK=%d,%d,%d\n",(crackcol>>16)&255,(crackcol>>8)&255,crackcol&255);

	fprintf(fil,"rotsavbeg=%d\n",rotsavbeg);
	fprintf(fil,"rotsavcur=%d\n",rotsavcur);
	fprintf(fil,"rotsavend=%d\n",rotsavend);
	fprintf(fil,"notation3=%c%c%c%c%c%c\n",notation3[0],notation3[1],notation3[2],notation3[3],notation3[4],notation3[5]);
	if ((cdim >= 2) && (cdim <= 4))
	{
		fprintf(fil,"rotsav3=\n");
		for(i=rotsavbeg;i<rotsavend;i++)
		{
			x = rotsav[i&(ROTSAVSIZ-1)];
			if ((cdim == 2) && (x >= 16)) x += 16;
			if (cdim == 4) x &= ~16;
			switch(x&~3)
			{
				case  0: y = notation3[0]; x = (x&~3)+((-x)&3); break;
				case  4: y = notation3[2];                      break;
				case  8: y = notation3[4]; x = (x&~3)+((-x)&3); break;
				case 16: y =          'M'; x = (x&~3)+((-x)&3); break;
				case 20: y =          'E'; x = (x&~3)+((-x)&3); break;
				case 24: y =          'S'; x = (x&~3)+((-x)&3); break;
				case 32: y = notation3[1];                      break;
				case 36: y = notation3[3]; x = (x&~3)+((-x)&3); break;
				case 40: y = notation3[5];                      break;
			}
			if ((cdim == 4) && (rotsav[i&(ROTSAVSIZ-1)] >= 16) && (rotsav[i&(ROTSAVSIZ-1)] < 48)) y += 32;
			fputc(y,fil);
			if ((x&3) == 1) fputc('\'',fil);
			if ((x&3) == 2) fputc('2',fil);
			fputc(',',fil);
			if (((i-rotsavbeg)&31) == 31) fputc('\n',fil);
		}
		if ((i-rotsavbeg)&31) fputc('\n',fil);
	}
	else
	{
		fprintf(fil,"rotsav2=\n");
		for(i=rotsavbeg;i<rotsavend;i++)
		{
			fprintf(fil,"%d,",rotsav[i&(ROTSAVSIZ-1)]);
			if (((i-rotsavbeg)&31) == 31) fputc('\n',fil);
		}
		if ((i-rotsavbeg)&31) fputc('\n',fil);
	}

	fprintf(fil,"timermode=%d\n",timermode);
	if (timermode >= 0)
	{
		switch(timermode)
		{
			case 0: i = 0; break;
			case 1: i = ltotclk-startimer; break;
			case 2: i = stoptimer-startimer; break;
		}
		fprintf(fil,"elapsed_ms=%d\n",i);
	}

	fclose(fil);
}

static int loadrubix (char *v)
{
	FILE *fil;
	int i, j, k, x, y, r, g, b, ch, cubewhich, cubeface, cubey; //0=cubefacecol, 1=ocubefacecol
	int rotread, rotver;
	char tbuf[1024];

	fil = fopen(v,"r"); if (!fil) return(0);

	fscanf(fil,"RUBIX save game. Edit at your own risk!\n");

	i = 0; cubewhich = -1; rotread = -1; rotsavbeg = rotsavcur = rotsavend = 0;
	while (!feof(fil))
	{
		ch = fgetc(fil);
		if ((i < sizeof(tbuf)) && (ch >= 32)) tbuf[i++] = (int)ch;
		if ((ch == '\n') || (feof(fil)))
		{
			if (i < sizeof(tbuf))
			{
				tbuf[i++] = 0;

				if ((cubewhich >= 0) && (tbuf[0] >= '1') && (tbuf[0] <= '6'))
				{
					j = 0;
					for(x=0;x<cdim;x++)
					{
						if (!cubewhich) cubefacecol[(cubeface*MAXCDIM+x)*MAXCDIM+cubey] = strtol(&tbuf[j],(char **)&j,0);
									 else ocubefacecol[(cubeface*MAXCDIM+x)*MAXCDIM+cubey] = strtol(&tbuf[j],(char **)&j,0);
						j += 1-((int)tbuf);
					}
					cubey++; if (cubey >= cdim) { cubey = 0; cubeface++; if (cubeface >= 6) cubewhich = -1; }
				}
				else if ((rotread >= rotsavbeg) && (rotread < rotsavend))
				{
					j = 0;
					for(x=0;x<32;x++)
					{
						switch (rotver)
						{
							case 1: k = (strtol(&tbuf[j],(char **)&j,0)<<1)+1; j += 1-((int)tbuf); break;
							case 2: k = strtol(&tbuf[j],(char **)&j,0); j += 1-((int)tbuf); break;
							case 3:
								y = tbuf[j];
									  if ((y == notation3[0]) || (y == (notation3[0]^32))) k =  0+1;
								else if ((y == notation3[2]) || (y == (notation3[2]^32))) k =  4+3;
								else if ((y == notation3[4]) || (y == (notation3[4]^32))) k =  8+1;
								else if ((y == 'M'         ) || (y == 'm'              )) k = 16+1;
								else if ((y == 'E'         ) || (y == 'e'              )) k = 20+1;
								else if ((y == 'S'         ) || (y == 's'              )) k = 24+1;
								else if ((y == notation3[1]) || (y == (notation3[1]^32))) k = 32+3;
								else if ((y == notation3[3]) || (y == (notation3[3]^32))) k = 36+1;
								else if ((y == notation3[5]) || (y == (notation3[5]^32))) k = 40+3;
								j++; if (tbuf[j] == '2') { j++; k = (k&~1)|2; }
								else if (tbuf[j] == '\'') { j++; k ^= 2; }
								j++;
								if ((cdim == 2) && (k >= 32)) k -= 16;
								if ((cdim == 4) && ((k >= 32) ^ (y >= 96))) k += 16;
								break;
						}
						rotsav[rotread&(ROTSAVSIZ-1)] = k;
						rotread++; if (rotread >= rotsavend) break;
					}
				}
				else if (!memcmp(tbuf,"cubedim="    , 8))
				{
					cdim = strtol(&tbuf[8],0,0);
					menu_update_cdim();
				}
				else if (!memcmp(tbuf,"cubefacecol=",12)) { cubewhich = 0; cubeface = cubey = 0; }
				else if (!memcmp(tbuf,"showothercubemode=",18))
				{
					showothercubemode = strtol(&tbuf[18],0,0);
					if (showothercubemode) cubewhich = 1;
					cubeface = cubey = 0;
				}

				else if (!memcmp(tbuf,"anglemode=",10)) anglemode = strtol(&tbuf[10],0,0);
				else if (!memcmp(tbuf,"angles=",7)) sscanf(&tbuf[7],"%f,%f,%f",&a1v,&a2v,&a3v);
				else if (!memcmp(tbuf,"veci=",5)) sscanf(&tbuf[5],"%f,%f,%f",&i3.x,&i3.y,&i3.z);
				else if (!memcmp(tbuf,"vecj=",5)) sscanf(&tbuf[5],"%f,%f,%f",&j3.x,&j3.y,&j3.z);
				else if (!memcmp(tbuf,"veck=",5)) sscanf(&tbuf[5],"%f,%f,%f",&k3.x,&k3.y,&k3.z);

				else if (!memcmp(tbuf,"RGB1=",5)) { sscanf(&tbuf[5],"%d,%d,%d",&r,&g,&b); pal[1] = (r<<16)+(g<<8)+b; }
				else if (!memcmp(tbuf,"RGB2=",5)) { sscanf(&tbuf[5],"%d,%d,%d",&r,&g,&b); pal[2] = (r<<16)+(g<<8)+b; }
				else if (!memcmp(tbuf,"RGB3=",5)) { sscanf(&tbuf[5],"%d,%d,%d",&r,&g,&b); pal[3] = (r<<16)+(g<<8)+b; }
				else if (!memcmp(tbuf,"RGB4=",5)) { sscanf(&tbuf[5],"%d,%d,%d",&r,&g,&b); pal[4] = (r<<16)+(g<<8)+b; }
				else if (!memcmp(tbuf,"RGB5=",5)) { sscanf(&tbuf[5],"%d,%d,%d",&r,&g,&b); pal[5] = (r<<16)+(g<<8)+b; }
				else if (!memcmp(tbuf,"RGB6=",5)) { sscanf(&tbuf[5],"%d,%d,%d",&r,&g,&b); pal[6] = (r<<16)+(g<<8)+b; }
				else if (!memcmp(tbuf,"RGBBACK=",8))
				{
					sscanf(&tbuf[8],"%d,%d,%d",&r,&g,&b);
					backcol = (r<<16)+(g<<8)+b; pal[7] = backcol;
				}
				else if (!memcmp(tbuf,"RGBCRACK=",8))
				{
					sscanf(&tbuf[9],"%d,%d,%d",&r,&g,&b);
					crackcol = (r<<16)+(g<<8)+b; pal[0] = crackcol;
				}

				else if (!memcmp(tbuf,"rotsavbeg=",10)) rotsavbeg = strtol(&tbuf[10],0,0);
				else if (!memcmp(tbuf,"rotsavcur=",10)) rotsavcur = strtol(&tbuf[10],0,0);
				else if (!memcmp(tbuf,"rotsavend=",10)) rotsavend = strtol(&tbuf[10],0,0);
				else if (!memcmp(tbuf,"notation3=",10)) memcpy(notation3,&tbuf[10],6);
				else if (!memcmp(tbuf,"rotsav=" ,7)) { rotread = 0; rotver = 1; }
				else if (!memcmp(tbuf,"rotsav2=",8)) { rotread = 0; rotver = 2; }
				else if (!memcmp(tbuf,"rotsav3=",8)) { rotread = 0; rotver = 3; }

				else if (!memcmp(tbuf,"timermode=",10)) timermode = strtol(&tbuf[10],0,0);
				else if (!memcmp(tbuf,"elapsed_ms=",11)) { j = strtol(&tbuf[11],0,0); startimer = ltotclk-j; stoptimer = ltotclk; }

				else if (!memcmp(tbuf,"rotatespeed=",12))
				{
					rotatespeed = strtod(&tbuf[12],0);
					j = (int)(log(rotatespeed)/log(2.0)+0.5);
					for(k=0;k<9;k++) CheckMenuItem(gmenu,k+OPTROTSPEED,(-(k==j))&MF_CHECKED);
				}
				else if (!memcmp(tbuf,"visualdetail=",13))
				{
					visualdetail = min(max(strtol(&tbuf[13],0,0),0),2);
					for(i=0;i<3;i++) CheckMenuItem(gmenu,VISUALDETAIL+i,(-(visualdetail==i))&MF_CHECKED);
				}
				else if (!memcmp(tbuf,"editmode=",9))
				{
					editmode = min(max(strtol(&tbuf[9],0,0),0),1);
					CheckMenuItem(gmenu,OPTEDITCUBE,(-editmode)&MF_CHECKED);
				}
				else if (!memcmp(tbuf,"curcolindex=",12)) curcolindex = min(max(strtol(&tbuf[12],0,0),0),5);
			}
			i = 0;
		}
	}
	fclose(fil);

		//Extra crud to make it happy
	editpatchcnt = editpatchbeg = editpatchend = 0;
	c3.z = (cdim<<1);
	cdimm1 = cdim-1;
	cdimm1tMAXCDIM = cdimm1*MAXCDIM;
	sticker_init();

	return(1);
}

	//Characters 32-127 packed bits 8x(15*(128-32))
static const __int64 kascbit_8x15[] =
{
	0x0000000000000000,0x0000000000000000,0x18183c3c3c180000,0x0000000000181800,
	0x0000000066666600,0x0000000000000000,0x6cfe6c6c6cfe6c6c,0x3c1818000000006c,
	0x3c666030180c0666,0x5b1b0e0000001818,0x70d8da760c18306e,0x36361c0000000000,
	0x0000dc6666f6061c,0x0018181800000000,0x0000000000000000,0x0c0c181830000000,
	0x00003018180c0c0c,0x30303018180c0000,0x0000000c18183030,0x6c38fe386c000000,
	0x0000000000000000,0x0018187e18180000,0x0000000000000000,0x3838000000000000,
	0x0000000000001830,0x00000000007e0000,0x0000000000000000,0x0000383800000000,
	0x3030606000000000,0x000006060c0c1818,0xccececcc78000000,0x0000000078ccdcdc,
	0x3030303e38300000,0x0000000000303030,0x0c18306066663c00,0x0000000000007e06,
	0x666660386066663c,0x0c0000000000003c,0x6060fe666c6c6c0c,0x067e000000000000,
	0x001e3060603e0606,0x0c18380000000000,0x00003c666666663e,0x3030607e00000000,
	0x0000000c0c0c1818,0x3c6e66663c000000,0x000000003c666676,0x7c666666663c0000,
	0x00000000001c1830,0x0000003838000000,0x0000000000003838,0x3800000038380000,
	0x6000000000183038,0x6030180c060c1830,0x0000000000000000,0x000000007e007e00,
	0x180c060000000000,0x0000060c18306030,0x3066663c00000000,0x0000001818001818,
	0xdbf3c3c37e000000,0x00000000fe03f3db,0x7e6666663c180000,0x0000000000666666,
	0x66663e6666663e00,0x0000000000003e66,0x666606060666663c,0x1e0000000000003c,
	0x1e36666666666636,0x067e000000000000,0x007e0606063e0606,0x06067e0000000000,
	0x0000060606063e06,0x0666663c00000000,0x0000007c66667606,0x7e66666666000000,
	0x0000000066666666,0x18181818183c0000,0x00000000003c1818,0x6660606060606000,
	0x0000000000003c66,0x6636361e36366666,0x0600000000000066,0x7e06060606060606,
	0xc6c6000000000000,0x00c6c6c6d6d6d6ee,0xcec6c60000000000,0x0000c6c6c6e6f6de,
	0x6666663c00000000,0x0000003c66666666,0x3e6666663e000000,0x0000000006060606,
	0x66666666663c0000,0x00000060303c6666,0x66363e6666663e00,0x0000000000006666,
	0x666030180c06663c,0x7e0000000000003c,0x1818181818181818,0x6666000000000000,
	0x003c666666666666,0x6666660000000000,0x0000183c66666666,0xd6c6c6c600000000,
	0x0000006c6c6cd6d6,0x18182c6666000000,0x0000000066666634,0x183c666666660000,
	0x0000000000181818,0x060c183060607e00,0x0000000000007e06,0x0c0c0c0c0c0c0c3c,
	0x060000003c0c0c0c,0x60303018180c0c06,0x303c000000000060,0x3030303030303030,
	0x0000663c18003c30,0x0000000000000000,0x0000000000000000,0xff00000000000000,
	0x0000000030181c00,0x0000000000000000,0x7c60603c00000000,0x00000000007c6666,
	0x666666663e060600,0x0000000000003e66,0x66060606663c0000,0x600000000000003c,
	0x7c66666666667c60,0x0000000000000000,0x003c06067e66663c,0x0c0c780000000000,
	0x00000c0c0c0c7e0c,0x667c000000000000,0x3e60607c66666666,0x66663e0606000000,
	0x0000000066666666,0x1818181e00181800,0x00000000007e1818,0x303030303c003030,
	0x0000001e30303030,0x66361e3666660606,0x1e00000000000066,0x7e18181818181818,
	0x0000000000000000,0x00c6d6d6d6d6d67e,0x3e00000000000000,0x0000666666666666,
	0x663c000000000000,0x0000003c66666666,0x66663e0000000000,0x000606063e666666,
	0x6666667c00000000,0x00006060607c6666,0x06060e7666000000,0x0000000000000606,
	0x60603c06067c0000,0x0c0000000000003e,0x780c0c0c0c0c7e0c,0x0000000000000000,
	0x007c666666666666,0x6600000000000000,0x0000183c66666666,0xd6c6000000000000,
	0x0000006c6cd6d6d6,0x3c66660000000000,0x0000000066663c18,0x6666666600000000,
	0x00000f18303c6666,0x0c1830607e000000,0x0000000000007e06,0x180c060c18181830,
	0x1800000000301818,0x1818181818181818,0x180c000000181818,0x1818183060301818,
	0x71db8e000000000c,0x0000000000000000,0x7e7e7e7e00000000,0x0000007e7e7e7e7e,
	0x0000000000000000,
};

typedef struct { char *buf; int leng, xs, ys; } fontbittyp;
static fontbittyp fontlist[] =
{
	{(char *)kascbit_8x15 ,sizeof(kascbit_8x15) , 8,15}, //Fixedsys (notepad font)
};
static tiletype font[sizeof(fontlist)/sizeof(fontlist[0])];

static void drawtext (int dafont, int x, int y, int fcol, int bcol, const char *fmt, ...)
{
	va_list arglist;
	char st[1024], *cptr;
	int i, k, l, nx, xx, yy, op, p, bpl, xs, ys, tabstat, *fptr, lind;

	if (!fmt) return;
	va_start(arglist,fmt);
	_vsnprintf(st,sizeof(st),fmt,arglist);
	va_end(arglist);

	xs = fontlist[dafont].xs; fptr = (int *)font[dafont].f;
	ys = fontlist[dafont].ys; bpl = font[dafont].p;
	op = y*gdd.p + gdd.f;
	for(yy=0;yy<ys;yy++,y++,op+=gdd.p)
	{
		if ((unsigned int)y >= (unsigned int)gdd.y) continue;

		tabstat = 0; nx = x; p = op; i = 0;
		for(cptr=st;cptr[0];cptr++)
		{
			if (!tabstat) i = (unsigned char)cptr[0]; else tabstat--;
			if (i == 9) { tabstat = 2; i = 32; }

			if (((unsigned int)(i-32)) >= 96) i = 32;
			lind = ((i-32)*ys+yy)*xs - nx;
			p = op + nx*4;
			if (bcol < 0)
			{
				for(xx=nx,nx+=xs;xx<nx;xx++,p+=4)
				{
					if ((unsigned int)xx >= (unsigned int)gdd.x) continue;
					if (fptr[(lind+xx)>>5]&(1<<(lind+xx))) *(int *)p = fcol;
				}
			}
			else if (fcol < 0)
			{
				for(xx=nx,nx+=xs;xx<nx;xx++,p+=4)
				{
					if ((unsigned int)xx >= (unsigned int)gdd.x) continue;
					if (!(fptr[(lind+xx)>>5]&(1<<(lind+xx)))) *(int *)p = bcol;
				}
			}
			else
			{
				for(xx=nx,nx+=xs;xx<nx;xx++,p+=4)
				{
					if ((unsigned int)xx >= (unsigned int)gdd.x) continue;
					if (fptr[(lind+xx)>>5]&(1<<(lind+xx))) *(int *)p = fcol; else *(int *)p = bcol;
				}
			}
		}
	}
}

static void getrenderorder (point3d *a, point3d *b, point3d *c, int *spl, int *ord0, int *ord1, int *ord2)
{
	int i, j, k, x, *ord[3];

	ftol(-(c3.x*a->x + c3.y*a->y + c3.z*a->z) / (a->x*a->x + a->y*a->y + a->z*a->z) + (float)cdim*.5-1,&spl[0]);
	ftol(-(c3.x*b->x + c3.y*b->y + c3.z*b->z) / (b->x*b->x + b->y*b->y + b->z*b->z) + (float)cdim*.5-1,&spl[1]);
	ftol(-(c3.x*c->x + c3.y*c->y + c3.z*c->z) / (c->x*c->x + c->y*c->y + c->z*c->z) + (float)cdim*.5-1,&spl[2]);
	ord[0] = ord0; ord[1] = ord1; ord[2] = ord2;
	for(x=0;x<3;x++)
	{
		j = min(max(spl[x],0),cdimm1); k = cdimm1;
		for(i=cdimm1;i>j;i--) ord[x][k--] = i;
		for(i=0;i<=j;i++) ord[x][k--] = i;
	}
}

static void drawscreen (void)
{
	int x, y, z, i, j, k, split[6];
	float c, s;

	fpuinit(0x08);  //24 bit, round to Ï
	getrenderorder(&i3,&j3,&k3,&split[0],&order[0][0],&order[1][0],&order[2][0]);
	fcossin(rotang,&c,&s);
	ii3 = i3; jj3 = j3; kk3 = k3;
	switch(rotaxis)
	{
		case 0:
			for(k=cdimm1;;k--)
			{
				x = order[0][k];
				if (x == rotslice)
				{
					if (x >      0) drawblackrect(x-1,0,0,x-1,cdimm1,cdimm1,split[0]>x-1);
					if (x < cdimm1) drawblackrect(x+1,0,0,x+1,cdimm1,cdimm1,split[0]>x+1);
					jj3.x = j3.x*c+k3.x*s; kk3.x = k3.x*c-j3.x*s;
					jj3.y = j3.y*c+k3.y*s; kk3.y = k3.y*c-j3.y*s;
					jj3.z = j3.z*c+k3.z*s; kk3.z = k3.z*c-j3.z*s;
					getrenderorder(&ii3,&jj3,&kk3,&split[3],&order[3][0],&order[1][0],&order[2][0]);
				}
				for(z=cdimm1;z>=0;z--)
					for(y=cdimm1;y>=0;y--) drawcube(x,order[1][y],order[2][z]);
				if (searchstat == 2) return;
				if (!k) break;
				if (x == rotslice)
				{
					drawblackrect(x,0,0,x,cdimm1,cdimm1,split[0]>rotslice);
					jj3 = j3; kk3 = k3;
					getrenderorder(&i3,&j3,&k3,&split[0],&order[3][0],&order[1][0],&order[2][0]);
				}
			}
			break;
		case 1:
			for(k=cdimm1;;k--)
			{
				y = order[1][k];
				if (y == rotslice)
				{
					if (y >      0) drawblackrect(0,y-1,0,cdimm1,y-1,cdimm1,(split[1]>y-1)+2);
					if (y < cdimm1) drawblackrect(0,y+1,0,cdimm1,y+1,cdimm1,(split[1]>y+1)+2);
					ii3.x = i3.x*c+k3.x*s; kk3.x = k3.x*c-i3.x*s;
					ii3.y = i3.y*c+k3.y*s; kk3.y = k3.y*c-i3.y*s;
					ii3.z = i3.z*c+k3.z*s; kk3.z = k3.z*c-i3.z*s;
					getrenderorder(&ii3,&jj3,&kk3,&split[3],&order[0][0],&order[3][0],&order[2][0]);
				}
				for(z=cdimm1;z>=0;z--)
					for(x=cdimm1;x>=0;x--) drawcube(order[0][x],y,order[2][z]);
				if (searchstat == 2) return;
				if (!k) break;
				if (y == rotslice)
				{
					drawblackrect(0,y,0,cdimm1,y,cdimm1,(split[1]>rotslice)+2);
					ii3 = i3; kk3 = k3;
					getrenderorder(&i3,&j3,&k3,&split[0],&order[0][0],&order[3][0],&order[2][0]);
				}
			}
			break;
		case 2:
			for(k=cdimm1;;k--)
			{
				z = order[2][k];
				if (z == rotslice)
				{
					if (z >      0) drawblackrect(0,0,z-1,cdimm1,cdimm1,z-1,(split[2]>z-1)+4);
					if (z < cdimm1) drawblackrect(0,0,z+1,cdimm1,cdimm1,z+1,(split[2]>z+1)+4);
					ii3.x = i3.x*c+j3.x*s; jj3.x = j3.x*c-i3.x*s;
					ii3.y = i3.y*c+j3.y*s; jj3.y = j3.y*c-i3.y*s;
					ii3.z = i3.z*c+j3.z*s; jj3.z = j3.z*c-i3.z*s;
					getrenderorder(&ii3,&jj3,&kk3,&split[3],&order[0][0],&order[1][0],&order[3][0]);
				}
				for(y=cdimm1;y>=0;y--)
					for(x=cdimm1;x>=0;x--) drawcube(order[0][x],order[1][y],z);
				if (searchstat == 2) return;
				if (!k) break;
				if (z == rotslice)
				{
					drawblackrect(0,0,z,cdimm1,cdimm1,z,(split[2]>rotslice)+4);
					ii3 = i3; jj3 = j3;
					getrenderorder(&i3,&j3,&k3,&split[0],&order[0][0],&order[1][0],&order[3][0]);
				}
			}
			break;
	}
}

//--------------------------------------------------------------------------------------------------

#define SELFMODVAL(dalab,daval) \
{  void *_daddr; unsigned long _oprot; \
	_asm { mov _daddr, offset dalab } \
	VirtualProtect(_daddr,sizeof(daval),PAGE_EXECUTE_READWRITE,&_oprot); \
	switch(sizeof(daval)) \
	{  case 1: *(char *)_daddr = daval; break; \
		case 2: *(short *)_daddr = daval; break; \
		case 4: *(int *)_daddr = daval; break; \
		case 8: *(__int64 *)_daddr = daval; break; \
	} \
	VirtualProtect(_daddr,sizeof(daval),PAGE_EXECUTE,&_oprot); \
	/*FlushInstructionCache(GetCurrentProcess(),_daddr,sizeof(daval));*/ \
}

static __forceinline int bsr (int a) { _asm bsr eax, a }

#define LFLATSTEPSIZ 3
#define FLATSTEPSIZ (1<<LFLATSTEPSIZ)
static __int64 g_rgbmul; //0x010001000100 (256's is no change)
static float g_mat[9], g_di8, g_ui8, g_vi8, fone = 1.f;
static int v2h_lmost[MAXYDIM], v2h_rmost[MAXYDIM], g_ttps, g_ymsk, g_xmsk, g_ttf, g_ttp;
static void htflatnear (int sy)
{
	float f, d, u, v, vx, vy, di8, ui8, vi8;
	int iu, iv, iui, ivi, p, p2, pe, sx0, *cbuf, ttps, ymsk, xmsk, ttf;

	if (sy < 0)
	{
		if (cputype&(1<<25)) //Got SSE
		{
			static int ottps = -1, ocbuf = 0, ottf = 0;
			if (g_ttps != ottps) { ottps = g_ttps; SELFMODVAL(selfmod_shift-1,((char)ottps)); }
			if (g_ttf  != ottf)  { ottf  = g_ttf;  SELFMODVAL(selfmod_ttf  -4,ottf         ); }
			if (gdd.f  != ocbuf) { ocbuf = gdd.f;  SELFMODVAL(selfmod_cbuf -4,ocbuf        ); }
		}
		return;
	}

	sx0 = max(v2h_lmost[sy],0);
	p = (gdd.p>>2)*sy; pe = min(v2h_rmost[sy],gdd.x)+p; p += sx0;
	if (p >= pe) return;

	cbuf = (int *)gdd.f;
	ttps = g_ttps; xmsk = g_xmsk; ymsk = g_ymsk;

	vx = (float)sx0; vy = (float)sy;
	d = g_mat[0]*vx + g_mat[3]*vy + g_mat[6];
	u = g_mat[1]*vx + g_mat[4]*vy + g_mat[7];
	v = g_mat[2]*vx + g_mat[5]*vy + g_mat[8];
	f = 1.0/d; d += g_di8;
	iu = (int)(u*f);
	iv = (int)(v*f);
	if (!(cputype&(1<<25))) //No SSE
	{
		ttf = g_ttf;
		do
		{
			f = 1.0/d; u += g_ui8; v += g_vi8; d += g_di8;
			iui = ((((int)(u*f))-iu)>>LFLATSTEPSIZ);
			ivi = ((((int)(v*f))-iv)>>LFLATSTEPSIZ);
			p2 = min(p+FLATSTEPSIZ,pe);
			do
			{
				cbuf[p] = *(int *)(((iv>>ttps)&ymsk) + ((iu>>14)&xmsk) + ttf);
				iu += iui; iv += ivi; p++;
			} while (p < p2);
		} while (p < pe);
	}
	else
	{
		xmsk >>= 2; p <<= 2; pe <<= 2;
		_asm
		{
			push esi
			push edi

			movss xmm1, v
			movss xmm0, u
			unpcklps xmm1, xmm0 ;xmm1: [. . u v]
			movss xmm0, d
			movlhps xmm0, xmm1 ;xmm0: [u v . d]

			movss xmm2, g_vi8
			movss xmm1, g_ui8
			unpcklps xmm2, xmm1 ;xmm2: [. . ui8 vi8]
			movss xmm1, g_di8
			movlhps xmm1, xmm2 ;xmm1: [ui8 vi8 . di8]

			movd mm0, iv
			punpckldq mm0, iu ;mm0: [iu iv]

			mov edi, p
	begit1:
			;rcpss xmm2, xmm0 ;noticably faster but looks too crappy
			movss xmm2, fone
			divss xmm2, xmm0   ;f = 1.0/d;
			addps xmm0, xmm1   ;u += g_ui8; v += g_vi8; d += g_di8;
			movhlps xmm3, xmm0 ;xmm3: [. . u v]
			shufps xmm2, xmm2, 0 ;xmm2: [f f f f]
			mulps xmm3, xmm2   ;xmm3: [. . u*f v*f]

			cvtps2pi mm1, xmm3 ;mm0: [(int)u*f (int)v*f]
			psubd mm1, mm0
			psrad mm1, LFLATSTEPSIZ ;mm1: [iui ivi]

			lea esi, [edi+FLATSTEPSIZ*4] ;esi:p2
			cmp esi, pe
			jl short near_preskip
			mov esi, pe
	near_preskip:
			sub edi, esi

	begit2:
			movd eax, mm0
			shr eax, 0x88 _asm selfmod_shift:
			pextrw ecx, mm0, 3
			and eax, ymsk
			and ecx, xmsk
#if 0
			movd mm2, [eax+ecx*4+0x88888888] _asm selfmod_ttf: ;no rgbmul
#else
			punpcklbw mm2, [eax+ecx*4+0x88888888] _asm selfmod_ttf:
			pmulhuw mm2, g_rgbmul
			packuswb mm2, mm2
#endif
			movd dword ptr [edi+esi+0x88888888], mm2 _asm selfmod_cbuf:
			paddd mm0, mm1 ;iu += iui; iv += ivi;
			add edi, 4
			jl short begit2

			add edi, esi
			cmp esi, pe
			jne short begit1

			pop edi
			pop esi
			emms
		}
	}
}

	//Nearest polygon renderer copied from GROUSMOOTH.C (03/15/2007) and then simplified a bit
static void drawpolyquad (tiletype *tt, vertyp *vt, __int64 rgbmul)
{
	__declspec(align(16)) static float dpqmulval[4] = {0,1,2,3}, dpqfours[4] = {4,4,4,4};
	//__declspec(align(16)) static float dpqmagic[4] = {4194304.f*3.f,4194304.f*3.f,4194304.f*3.f,4194304.f*3.f};
	//__declspec(align(16)) static int dpqsub[4] = {0x4b400000,0x4b400000,0x4b400000,0x4b400000};
	point2d scr[4];
	float ax, ay, az, au, av, bx, by, bz, bu, bv, cx, cy, cz, cu, cv;
	float f, g, p0x, p0y, p0z, p1x, p1y, p1z, p2x, p2y, p2z;
	int i, j, k, l, sx0, sx1, sy, x, xi, y, mini, maxi, minx, miny, maxx, maxy;
	int ord[4], *lptr, isy[4], yy0, yy1;

	minx = gdd.x; maxx = 0;
	miny = gdd.y; maxy = 0;
	for(i=4-1;i>=0;i--)
	{
		f = ghz/vt[i].z;
		scr[i].x = vt[i].x*f + ghx; x = (int)ceil(scr[i].x);
		scr[i].y = vt[i].y*f + ghy; y = (int)ceil(scr[i].y);
		isy[i] = min(max(y,0),gdd.y);
		if (x < minx) minx = x;
		if (x > maxx) maxx = x;
		if (y < miny) { miny = y; mini = i; }
		if (y > maxy) { maxy = y; maxi = i; }
	}
	if (minx < 0) minx = 0; if (maxx > gdd.x) maxx = gdd.x; if (maxx <= minx) return;
	if (miny < 0) miny = 0; if (maxy > gdd.y) maxy = gdd.y; if (maxy <= miny) return;

		//Calculate facing of polygon
	f = 0.f;
	for(i=4-2,j=4-1,k=0;k<4;i=j,j=k,k++) f += (scr[i].x-scr[k].x)*scr[j].y;
	if (*(int *)&f < 0) return;

	i = mini; j = 0;                while (i != maxi) { ord[j++] = i; i = ((i+1)&3); }
	i = mini-1; if (i < 0) i = 4-1; while (i != maxi) { ord[j++] = i; i = ((i-1)&3); }
	ord[j] = maxi;

	if (cputype&(1<<25)) //Got SSE
	{
		_asm
		{
			mov eax, 0x5f80 ;round +inf
			mov i, eax
			ldmxcsr i
		}
	}
	for(k=0;k<4;k++)
	{
		i = ord[k]; j = ((i+1)&3);
		if (isy[i] == isy[j]) continue;
		if (isy[i] < isy[j]) { yy0 = isy[i]; yy1 = isy[j]; lptr = v2h_rmost; }
							 else { yy0 = isy[j]; yy1 = isy[i]; lptr = v2h_lmost; }
		g = (scr[j].x-scr[i].x)/(scr[j].y-scr[i].y); f = (yy0-scr[i].y)*g + scr[i].x;
		if (!(cputype&(1<<25))) //No SSE
		{
			for(y=yy0;y<yy1;y++) { lptr[y] = (int)ceil(f); f += g; }
		}
		else
		{
			_asm
			{
				mov edx, yy0
				mov ecx, lptr
				movss xmm2, f         ;xmm2:  -  , -  , -  , f
				movss xmm0, g         ;xmm0:  -  , -  , -  , g
				shufps xmm2, xmm2, 0  ;xmm2:  f  , f  , f  , f
				shufps xmm0, xmm0, 0  ;xmm0:  g  , g  , g  , g
				movaps xmm1, xmm0     ;xmm1:  g  , g  , g  , g
				mulps xmm0, dpqmulval ;xmm0: 3g  ,2g  ,1g  ,0g
				addps xmm0, xmm2      ;xmm0: 3g+f,2g+f, g+f,  f
				mulps xmm1, dpqfours  ;xmm1: 4g  ,4g  ,4g  ,4g

	 dqrast: cvtps2pi mm0, xmm0
				movhlps xmm2, xmm0
				cvtps2pi mm1, xmm2
				movq [ecx+edx*4], mm0
				movq [ecx+edx*4+8], mm1

				;movaps xmm2, xmm0
				;addps xmm2, dpqmagic
				;psubd xmm2, dpqsub  ;P4 ONLY!
				;movups [ecx+edx*4], xmm2

				addps xmm0, xmm1
				add edx, 4
				cmp edx, yy1
				jl short dqrast

				emms
			}
		}
	}
	if (cputype&(1<<25)) //Got SSE
	{
		_asm
		{
			mov eax, 0x3f80 ;round -inf
			mov i, eax
			ldmxcsr i
		}
	}

		//Parametric plane equation
	ax = vt[1].x-vt[0].x; bx = vt[3].x-vt[0].x; cx = vt[0].x;
	ay = vt[1].y-vt[0].y; by = vt[3].y-vt[0].y; cy = vt[0].y;
	az = vt[1].z-vt[0].z; bz = vt[3].z-vt[0].z; cz = vt[0].z;
	p2x = ay*bz - az*by; p2y = az*bx - ax*bz; p2z = ax*by - ay*bx; //f = p2x*cx + p2y*cy + p2z*cz; if (f < 0) return;
	p0x = by*cz - bz*cy; p0y = bz*cx - bx*cz; p0z = bx*cy - by*cx;
	p1x = cy*az - cz*ay; p1y = cz*ax - cx*az; p1z = cx*ay - cy*ax;
	/*ax = 1;*/
	ay = (float)(tt->x<<16);
	az = (float)(tt->y<<16);
	au = vt[1].u-vt[0].u; bu = vt[3].u-vt[0].u; cu = vt[0].u;
	av = vt[1].v-vt[0].v; bv = vt[3].v-vt[0].v; cv = vt[0].v;
	g_mat[0] = p2x/*ax*/; g_mat[1] = (p0x*au + p1x*bu + p2x*cu)*ay; g_mat[2] = (p0x*av + p1x*bv + p2x*cv)*az;
	g_mat[3] = p2y/*ax*/; g_mat[4] = (p0y*au + p1y*bu + p2y*cu)*ay; g_mat[5] = (p0y*av + p1y*bv + p2y*cv)*az;
	g_mat[6] = p2z/*ax*/; g_mat[7] = (p0z*au + p1z*bu + p2z*cu)*ay; g_mat[8] = (p0z*av + p1z*bv + p2z*cv)*az;
	g_mat[6] = g_mat[6]*ghz - g_mat[0]*ghx - g_mat[3]*ghy;
	g_mat[7] = g_mat[7]*ghz - g_mat[1]*ghx - g_mat[4]*ghy;
	g_mat[8] = g_mat[8]*ghz - g_mat[2]*ghx - g_mat[5]*ghy;
	g_di8 = g_mat[0]*FLATSTEPSIZ;
	g_ui8 = g_mat[1]*FLATSTEPSIZ;
	g_vi8 = g_mat[2]*FLATSTEPSIZ;

	g_rgbmul = rgbmul;
	g_ttp = tt->p; g_ttf = tt->f; i = bsr(g_ttp);
	g_xmsk = (1<<bsr(tt->x))-1; g_xmsk <<= 2;
	g_ymsk = (1<<bsr(tt->y))-1; g_ymsk <<= i;
	g_ttps = 16-i;
	htflatnear(-1); //init self-modifying code
	for(i=miny;i<maxy;i++) htflatnear(i);
}

//--------------------------------------------------------------------------------------------------

static int krunkmask[4] = {0x80000000,0x80000000,0x80000000,0x80000000};
static void drawquad (point3d *vt, int dlcol)
{
	point2d scr[4];
	int p, np, topp, botp, sx1, sy1, sx2, sy2, dx, xs, ncol, i, j, k, lx, rx;
	float f;

	for(i=4-1;i>=0;i--)
	{
		f = ghz/vt[i].z;
		scr[i].x = vt[i].x*f + ghx;
		scr[i].y = vt[i].y*f + ghy;
	}

		//Calculate facing of polygon
	f = 0.f;
	for(i=4-2,j=4-1,k=0;k<4;i=j,j=k,k++) f += (scr[i].x-scr[k].x)*scr[j].y;
	if (*(int *)&f < 0) return;

		//Nice method for getting top&bot indeces (No floatcmp, no j??)
	f = scr[1].y-scr[0].y; i = ((*(unsigned int *)&f) >> 31);
	f = scr[3].y-scr[2].y; j = ((*(unsigned int *)&f) >> 31)+2;
	f = scr[j].y-scr[i].y; topp = i + ((j-i)&((*(int *)&f)>>31));
	f = scr[i^1].y-scr[j^1].y; botp = (i^1)+(((j^1)-(i^1))&((*(int *)&f)>>31));

		//Note: .5 should be added to all ftol's with normal rounding mode.
		//Since I'm rounding using "round to Ï" mode, this code is optimized out!

		//WARNING: NO CLIPPING WITH SCREEN BORDERS!

	p = botp;
	ftol(scr[p].y,&sy1); if (sy1 > gdd.y) sy1 = gdd.y;
	do
	{
		np = (p+1)&3;
		ftol(scr[np].y,&sy2); if (sy2 < 0) sy2 = 0;
		if (sy1 > sy2)
		{
			ftol((scr[np].x-scr[p].x)*65536.0/(scr[np].y-scr[p].y),&dx);
			ftol(scr[np].x*65536.0+((float)sy2-scr[np].y)*(float)dx,&xs);
			qinterpolatedown16((void *)&lastx[sy2],sy1-sy2,xs+65536,dx);
			sy1 = sy2;
		}
		p = np;
	} while (np != topp);
	i = ylookup[sy1]+gdd.f;
	do
	{
		np = (p+1)&3;
		ftol(scr[np].y,&sy2); if (sy2 > gdd.y) sy2 = gdd.y;
		if (sy2 > sy1)
		{
			ftol((scr[np].x-scr[p].x)*65536.0/(scr[np].y-scr[p].y),&dx);
			ftol(scr[p].x*65536.0+((float)sy1-scr[p].y)*(float)dx,&xs); xs += 65536;
			do
			{
				lx = max(lastx[sy1],0); rx = min((xs>>16),gdd.x);
				ncol = dlcol; if (krunkmask[sy1&3] != 0x80000000) ncol = krunkmask[sy1&3];
				clearbuflongsafe((void *)((lx<<2)+i),rx-lx,ncol);
				xs += dx; sy1++; i += gdd.p;
			} while (sy1 < sy2);
		}
		p = np;
	} while (np != botp);
}

static float getshade (vertyp *vt)
{
	point3d l, n, u, r;
	float f;

		//n = normalized normal vector
	n.x = (vt[1].y-vt[0].y)*(vt[3].z-vt[0].z) - (vt[1].z-vt[0].z)*(vt[3].y-vt[0].y);
	n.y = (vt[1].z-vt[0].z)*(vt[3].x-vt[0].x) - (vt[1].x-vt[0].x)*(vt[3].z-vt[0].z);
	n.z = (vt[1].x-vt[0].x)*(vt[3].y-vt[0].y) - (vt[1].y-vt[0].y)*(vt[3].x-vt[0].x);
	f = 1.0/sqrt(n.x*n.x + n.y*n.y + n.z*n.z); n.x *= f; n.y *= f; n.z *= f;

		//l = normalized light direction
	l.x = 1.0/sqrt(3.0);
	l.y = 1.0/sqrt(3.0);
	l.z = 1.0/sqrt(3.0);

		//u = normalized view direction
	u.x = (vt[0].x + vt[1].x + vt[2].x + vt[3].x)*.25;
	u.y = (vt[0].y + vt[1].y + vt[2].y + vt[3].y)*.25;
	u.z = (vt[0].z + vt[1].z + vt[2].z + vt[3].z)*.25;
	f = 1.0/sqrt(u.x*u.x + u.y*u.y + u.z*u.z); u.x *= f; u.y *= f; u.z *= f;

		//Specular reflection (Phong shading)
		//r = reflected view direction
		//   /|\
		// r/_|_\u
		//    |n
	f = (n.x*l.x + n.y*l.y + n.z*l.z)*2.0;
	r.x = n.x*f - l.x;
	r.y = n.y*f - l.y;
	r.z = n.z*f - l.z;

	f = r.x*u.x + r.y*u.y + r.z*u.z;
	if (*(int *)&f > 0) { f *= f; f *= f; f *= f; } else f = 0;
	return(((n.x*l.x + n.y*l.y + n.z*l.z)*128+f*128+256)*winshade);
}

static void drawcubeface (int x, int y, int z, int i)
{
	vertyp vt[4];
	point3d pt[4], veca, vecb, vecn;
	tiletype tt;
	float f, g, t, rx, ry, rz, ix, iy, iz, jx, jy, jz, kx, ky, kz, t0, t1, t2, t3, fx, fy, fz;
	int offs, j, k, krunk;
	char col;

	t = ((float)cdim)*-.5;
	ix = ii3.x; iy = ii3.y; iz = ii3.z; t0 = t;
	jx = jj3.x; jy = jj3.y; jz = jj3.z; t1 = t;
	kx = kk3.x; ky = kk3.y; kz = kk3.z; t2 = t;
	if (!visualdetail)
	{
		if ((i&~1) != 0) { ix *= colwidth; iy *= colwidth; iz *= colwidth; t0 += (1-colwidth)*.5; }
		if ((i&~1) != 2) { jx *= colwidth; jy *= colwidth; jz *= colwidth; t1 += (1-colwidth)*.5; }
		if ((i&~1) != 4) { kx *= colwidth; ky *= colwidth; kz *= colwidth; t2 += (1-colwidth)*.5; }
	}
	rx = ii3.x*(x+t0) + jj3.x*(y+t1) + kk3.x*(z+t2) + c3.x;
	ry = ii3.y*(x+t0) + jj3.y*(y+t1) + kk3.y*(z+t2) + c3.y;
	rz = ii3.z*(x+t0) + jj3.z*(y+t1) + kk3.z*(z+t2) + c3.z;
	for(k=4-1;k>=0;k--)
	{
		j = ptface[i][k];
		fx = rx; fy = ry; fz = rz;
		if (j&1) { fx += ix; fy += iy; fz += iz; }
		if (j&2) { fx += jx; fy += jy; fz += jz; }
		if (j&4) { fx += kx; fy += ky; fz += kz; }
		pt[k].x = fx; pt[k].y = fy; pt[k].z = fz;
	}
	//t = (scr[2].x-scr[0].x)*(scr[1].y-scr[0].y)-(scr[1].x-scr[0].x)*(scr[2].y-scr[0].y); if (*(int *)&t >= 0) return;

	if (searchstat)
	{
		if (searchstat == 2) return;
			//(0,0,0) to (searchx-ghx,searchy-ghy,ghz)
			//(pt[j].x,pt[j].y,pt[j].z) to (pt[k].x,pt[k].y,pt[k].z)
		for(j=4-1,k=0;j>=0;k=j,j--)
		{
			//t = (scr[k].x-scr[j].x)*(searchy-scr[j].y)-(searchx-scr[j].x)*(scr[k].y-scr[j].y);
			t = + (pt[j].y*pt[k].z - pt[j].z*pt[k].y) * (searchx-ghx)
				 + (pt[j].z*pt[k].x - pt[j].x*pt[k].z) * (searchy-ghy)
				 + (pt[j].x*pt[k].y - pt[j].y*pt[k].x) * ghz;
			if (*(int *)&t < 0) return;
		}
		cgrabs = i; cgrabx = x; cgraby = y; cgrabz = z;
		searchstat = 2; return;
	}

	switch(i>>1)
	{
		case 0: offs = (i*MAXCDIM+y)*MAXCDIM+z; break;
		case 1: offs = (i*MAXCDIM+x)*MAXCDIM+z; break;
		case 2: offs = (i*MAXCDIM+x)*MAXCDIM+y; break;
	}

	col = drawcubefacecol[offs]; krunk = 0;
	if (drawcubefacecol == ocubefacecol)
	{
		if (cubefacecol[offs] != ocubefacecol[offs]) krunk = 1;
	}
	else if (!editmode)
	{
		if (cdim == 3)
		{
			if (keystatus[0x2]) { if ((x == 1) && (z == 1) && (y != 1)) krunk = 1; } //1
			if (keystatus[0x3]) { if (((x == 1) ^ (z == 1))&& (y == 1)) krunk = 1; } //2
			if (keystatus[0x4]) { if (((x == 1) ^ (z == 1))&& (y == 0)) krunk = 1; } //3
			if (keystatus[0x5]) { if ((x != 1) && (z != 1) && (y == 0)) krunk = 1; } //4
			if (keystatus[0x6]) { if ((x != 1) && (z != 1) && (y == 1)) krunk = 1; } //5
			if (keystatus[0x7]) { if ((x != 1) && (z != 1) && (y == 2)) krunk = 1; } //6
			if (keystatus[0x8]) { if (((x == 1) ^ (z == 1))&& (y == 2)) krunk = 1; } //7
		}
		if (keystatus[0x1d]|keystatus[0x9d]) //Ctrl
		{
			int xx, yy, zz, i0, i1;

				//is on same square?
			xx = min(cgrabx,cdim-1-cgrabx);
			yy = min(cgraby,cdim-1-cgraby);
			zz = min(cgrabz,cdim-1-cgrabz);
				 //cgrabs is invalid here;finding median dimension also works..
			if (xx > yy) { j = xx; xx = yy; yy = j; }
				  if (zz < xx) i0 = xx;
			else if (zz > yy) i0 = yy;
			else              i0 = zz;

			i1 = cdim;
			if ((i&~1) != 0) i1 = min(i1,min(x,cdim-1-x));
			if ((i&~1) != 2) i1 = min(i1,min(y,cdim-1-y));
			if ((i&~1) != 4) i1 = min(i1,min(z,cdim-1-z));
			if (i0 == i1) krunk = 1;
			if ((x == cgrabx) && (y == cgraby) && (z == cgrabz)) krunk = 1;
		}
	}

	if (!visualdetail)
	{
		if (krunk)
		{
			krunkmask[(ltotclk>>4)&3] = 0x404040;
			krunkmask[((ltotclk>>4)+1)&3] = 0xe0e0e0;
		}
		drawquad(pt,pal[col]);
		if (krunk) { krunkmask[0] = krunkmask[1] = krunkmask[2] = krunkmask[3] = 0x80000000; }
	}
	else
	{
		tt.f = (int)&stickertex[krunk*6+col-1][0][0]; tt.x = tt.y = STICKERSIZ; tt.p = (tt.x<<2);
		if (visualdetail == 1)
		{
			for(i=4-1;i>=0;i--) { vt[i].x = pt[i].x; vt[i].y = pt[i].y; vt[i].z = pt[i].z; }
			vt[0].u = 0; vt[0].v = 0;
			vt[1].u = 1; vt[1].v = 0;
			vt[2].u = 1; vt[2].v = 1;
			vt[3].u = 0; vt[3].v = 1;
			drawpolyquad(&tt,vt,0x010001000100);
		}
		else
		{
			veca.x = pt[1].x-pt[0].x;
			veca.y = pt[1].y-pt[0].y;
			veca.z = pt[1].z-pt[0].z;
			t = 1.0/sqrt(veca.x*veca.x + veca.y*veca.y + veca.z*veca.z); veca.x *= t; veca.y *= t; veca.z *= t;
			vecb.x = (pt[3].x-pt[0].x)*t;
			vecb.y = (pt[3].y-pt[0].y)*t;
			vecb.z = (pt[3].z-pt[0].z)*t;
			vecn.x = veca.y*vecb.z - veca.z*vecb.y;
			vecn.y = veca.z*vecb.x - veca.x*vecb.z;
			vecn.z = veca.x*vecb.y - veca.y*vecb.x;

				// o------o
				// | 0--1 |
				// | |  | |
				// | 3--2 |
				// o------o
			f = .05;
			vt[0].x = pt[0].x + veca.x*f + vecb.x*f - vecn.x*f*.5;
			vt[0].y = pt[0].y + veca.y*f + vecb.y*f - vecn.y*f*.5;
			vt[0].z = pt[0].z + veca.z*f + vecb.z*f - vecn.z*f*.5;
			vt[1].x = pt[1].x - veca.x*f + vecb.x*f - vecn.x*f*.5;
			vt[1].y = pt[1].y - veca.y*f + vecb.y*f - vecn.y*f*.5;
			vt[1].z = pt[1].z - veca.z*f + vecb.z*f - vecn.z*f*.5;
			vt[2].x = pt[2].x - veca.x*f - vecb.x*f - vecn.x*f*.5;
			vt[2].y = pt[2].y - veca.y*f - vecb.y*f - vecn.y*f*.5;
			vt[2].z = pt[2].z - veca.z*f - vecb.z*f - vecn.z*f*.5;
			vt[3].x = pt[3].x + veca.x*f - vecb.x*f - vecn.x*f*.5;
			vt[3].y = pt[3].y + veca.y*f - vecb.y*f - vecn.y*f*.5;
			vt[3].z = pt[3].z + veca.z*f - vecb.z*f - vecn.z*f*.5;
			vt[0].u = 0+f; vt[0].v = 0+f;
			vt[1].u = 1-f; vt[1].v = 0+f;
			vt[2].u = 1-f; vt[2].v = 1-f;
			vt[3].u = 0+f; vt[3].v = 1-f;
			drawpolyquad(&tt,vt,((__int64)getshade(vt))*0x100010001I64);

			tt.f = (int)&stickertex[12][0][0];
			vt[0].u = 0; vt[0].v = 0;
			vt[1].u = 1; vt[1].v = 0;
			vt[2].u = 1; vt[2].v = .05;
			vt[3].u = 0; vt[3].v = .05;

				//____.
				//       .
				//         .

				//Closer to top
			for(k=0;k<2;k++)
			{
				if (!k) { t0 = f*0.00; t1 = f*0.45; t2 = f*0.00; t3 = f*0.32; }
					else { t0 = f*0.45; t1 = f*1.00; t2 = f*0.32; t3 = f*0.50; }
				for(i=4-1,j=0;i>=0;j=i,i--)
				{
					vt[0].x = pt[i].x + (pt[i^2].x-pt[i].x)*t*t0 - vecn.x*t2;
					vt[0].y = pt[i].y + (pt[i^2].y-pt[i].y)*t*t0 - vecn.y*t2;
					vt[0].z = pt[i].z + (pt[i^2].z-pt[i].z)*t*t0 - vecn.z*t2;
					vt[1].x = pt[j].x + (pt[j^2].x-pt[j].x)*t*t0 - vecn.x*t2;
					vt[1].y = pt[j].y + (pt[j^2].y-pt[j].y)*t*t0 - vecn.y*t2;
					vt[1].z = pt[j].z + (pt[j^2].z-pt[j].z)*t*t0 - vecn.z*t2;
					vt[2].x = pt[j].x + (pt[j^2].x-pt[j].x)*t*t1 - vecn.x*t3;
					vt[2].y = pt[j].y + (pt[j^2].y-pt[j].y)*t*t1 - vecn.y*t3;
					vt[2].z = pt[j].z + (pt[j^2].z-pt[j].z)*t*t1 - vecn.z*t3;
					vt[3].x = pt[i].x + (pt[i^2].x-pt[i].x)*t*t1 - vecn.x*t3;
					vt[3].y = pt[i].y + (pt[i^2].y-pt[i].y)*t*t1 - vecn.y*t3;
					vt[3].z = pt[i].z + (pt[i^2].z-pt[i].z)*t*t1 - vecn.z*t3;
					drawpolyquad(&tt,vt,((__int64)getshade(vt))*0x100010001I64);
				}
			}
		}
	}
}

static void drawcube (int x, int y, int z)
{
	if (x ==      0) drawcubeface(x,y,z,0);
	if (x == cdimm1) drawcubeface(x,y,z,1);
	if (y ==      0) drawcubeface(x,y,z,2);
	if (y == cdimm1) drawcubeface(x,y,z,3);
	if (z ==      0) drawcubeface(x,y,z,4);
	if (z == cdimm1) drawcubeface(x,y,z,5);
}

static void drawblackrect (int x1, int y1, int z1, int x2, int y2, int z2, int side)
{
	point3d vt[4], vt2[4];
	float t, t1, t2, rx, ry, rz, ox, oy, oz;
	int i, j, col;

	if (searchstat) return;
	if (!visualdetail) col = 7; else col = 0;
	if (x2 < x1) { i = x1; x1 = x2; x2 = i; }
	if (y2 < y1) { i = y1; y1 = y2; y2 = i; }
	if (z2 < z1) { i = z1; z1 = z2; z2 = i; }
	t1 = 0.0 - .5*(float)cdim;
	t2 = 1.0 - .5*(float)cdim;
	if (side >= 0)
	{
		for(i=4-1;i>=0;i--)
		{
			j = ptface[side][i];
			if (j&1) ox = (float)x2+t2; else ox = (float)x1+t1;
			if (j&2) oy = (float)y2+t2; else oy = (float)y1+t1;
			if (j&4) oz = (float)z2+t2; else oz = (float)z1+t1;
			vt[i].x = ii3.x*ox + jj3.x*oy + kk3.x*oz + c3.x;
			vt[i].y = ii3.y*ox + jj3.y*oy + kk3.y*oz + c3.y;
			vt[i].z = ii3.z*ox + jj3.z*oy + kk3.z*oz + c3.z;
		}
		drawquad(vt,pal[col]);
	}
	else
	{
		float sx[8], sy[8];
		for(j=8-1;j>=0;j--)
		{
			if (j&1) ox = (float)x2+t2; else ox = (float)x1+t1;
			if (j&2) oy = (float)y2+t2; else oy = (float)y1+t1;
			if (j&4) oz = (float)z2+t2; else oz = (float)z1+t1;
			vt[i].x = ii3.x*ox + jj3.x*oy + kk3.x*oz + c3.x;
			vt[i].y = ii3.y*ox + jj3.y*oy + kk3.y*oz + c3.y;
			vt[i].z = ii3.z*ox + jj3.z*oy + kk3.z*oz + c3.z;
		}
		for(side=6-1;side>=0;side--)
		{
			for(i=4-1;i>=0;i--) vt2[i] = vt[ptface[side][i]];
			drawquad(vt2,pal[col]);
		}
	}
}

#define rotate1(c1,c2,c3,c4) { char c0 = c1; c1 = c2; c2 = c3; c3 = c4; c4 = c0; }
#define rotate2(c1,c2,c3,c4) { char c0 = c1; c1 = c3; c3 = c0; c0 = c2; c2 = c4; c4 = c0; }
#define rotate3(c1,c2,c3,c4) { char c0 = c4; c4 = c3; c3 = c2; c2 = c1; c1 = c0; }
void rotate (long axis, long slice, long numtimes)
{
	int i, x, rx, y, ry;
	char *c;

	switch(numtimes&3)
	{
		case 1:
			switch(axis)
			{
				case 0:
					c = &cubefacecol[slice*MAXCDIM];
					for(x=cdimm1,rx=0;x>=0;x--,rx++)
						rotate1(c[2*MAXCDIM*MAXCDIM+x],c[5*MAXCDIM*MAXCDIM+x],
								  c[3*MAXCDIM*MAXCDIM+rx],c[4*MAXCDIM*MAXCDIM+rx]);
					break;
				case 1:
					for(x=cdimm1,rx=0;x>=0;x--,rx++)
						rotate1(cubefacecol[(0*MAXCDIM+slice)*MAXCDIM+x],
								  cubefacecol[(5*MAXCDIM+x)*MAXCDIM+slice],
								  cubefacecol[(1*MAXCDIM+slice)*MAXCDIM+rx],
								  cubefacecol[(4*MAXCDIM+rx)*MAXCDIM+slice]);
					break;
				case 2:
					c = &cubefacecol[slice];
					for(x=cdimm1tMAXCDIM,rx=0;x>=0;x-=MAXCDIM,rx+=MAXCDIM)
						rotate1(c[0*MAXCDIM*MAXCDIM+x],c[3*MAXCDIM*MAXCDIM+x],
								  c[1*MAXCDIM*MAXCDIM+rx],c[2*MAXCDIM*MAXCDIM+rx]);
					break;
			}
			if ((unsigned int)(slice-1) >= (unsigned int)(cdimm1-1))
			{
				c = &cubefacecol[((slice!=0)+(axis<<1))*MAXCDIM*MAXCDIM];
				for(x=(cdim>>1)-1,rx=((cdim+1)>>1);x>=0;x--,rx++)
					for(y=(cdimm1>>1),ry=(cdim>>1);y>=0;y--,ry++)
						rotate1(c[x*MAXCDIM+ry],c[ry*MAXCDIM+rx],c[rx*MAXCDIM+y],c[y*MAXCDIM+x]);
			}
			break;
		case 2:
			switch(axis)
			{
				case 0:
					c = &cubefacecol[slice*MAXCDIM];
					for(x=cdimm1,rx=0;x>=0;x--,rx++)
						rotate2(c[2*MAXCDIM*MAXCDIM+x],c[5*MAXCDIM*MAXCDIM+x],
								  c[3*MAXCDIM*MAXCDIM+rx],c[4*MAXCDIM*MAXCDIM+rx]);
					break;
				case 1:
					for(x=cdimm1,rx=0;x>=0;x--,rx++)
						rotate2(cubefacecol[(0*MAXCDIM+slice)*MAXCDIM+x],
								  cubefacecol[(5*MAXCDIM+x)*MAXCDIM+slice],
								  cubefacecol[(1*MAXCDIM+slice)*MAXCDIM+rx],
								  cubefacecol[(4*MAXCDIM+rx)*MAXCDIM+slice]);
					break;
				case 2:
					c = &cubefacecol[slice];
					for(x=cdimm1tMAXCDIM,rx=0;x>=0;x-=MAXCDIM,rx+=MAXCDIM)
						rotate2(c[0*MAXCDIM*MAXCDIM+x],c[3*MAXCDIM*MAXCDIM+x],
								  c[1*MAXCDIM*MAXCDIM+rx],c[2*MAXCDIM*MAXCDIM+rx]);
					break;
			}
			if ((unsigned int)(slice-1) >= (unsigned int)(cdimm1-1))
			{
				c = &cubefacecol[((slice!=0)+(axis<<1))*MAXCDIM*MAXCDIM];
				for(x=(cdim>>1)-1,rx=((cdim+1)>>1);x>=0;x--,rx++)
					for(y=(cdimm1>>1),ry=(cdim>>1);y>=0;y--,ry++)
						rotate2(c[x*MAXCDIM+ry],c[ry*MAXCDIM+rx],c[rx*MAXCDIM+y],c[y*MAXCDIM+x]);
			}
			break;
		case 3:
			switch(axis)
			{
				case 0:
					c = &cubefacecol[slice*MAXCDIM];
					for(x=cdimm1,rx=0;x>=0;x--,rx++)
						rotate3(c[2*MAXCDIM*MAXCDIM+x],c[5*MAXCDIM*MAXCDIM+x],
								  c[3*MAXCDIM*MAXCDIM+rx],c[4*MAXCDIM*MAXCDIM+rx]);
					break;
				case 1:
					for(x=cdimm1,rx=0;x>=0;x--,rx++)
						rotate3(cubefacecol[(0*MAXCDIM+slice)*MAXCDIM+x],
								  cubefacecol[(5*MAXCDIM+x)*MAXCDIM+slice],
								  cubefacecol[(1*MAXCDIM+slice)*MAXCDIM+rx],
								  cubefacecol[(4*MAXCDIM+rx)*MAXCDIM+slice]);
					break;
				case 2:
					c = &cubefacecol[slice];
					for(x=cdimm1tMAXCDIM,rx=0;x>=0;x-=MAXCDIM,rx+=MAXCDIM)
						rotate3(c[0*MAXCDIM*MAXCDIM+x],c[3*MAXCDIM*MAXCDIM+x],
								  c[1*MAXCDIM*MAXCDIM+rx],c[2*MAXCDIM*MAXCDIM+rx]);
					break;
			}
			if ((unsigned int)(slice-1) >= (unsigned int)(cdimm1-1))
			{
				c = &cubefacecol[((slice!=0)+(axis<<1))*MAXCDIM*MAXCDIM];
				for(x=(cdim>>1)-1,rx=((cdim+1)>>1);x>=0;x--,rx++)
					for(y=(cdimm1>>1),ry=(cdim>>1);y>=0;y--,ry++)
						rotate3(c[x*MAXCDIM+ry],c[ry*MAXCDIM+rx],c[rx*MAXCDIM+y],c[y*MAXCDIM+x]);
			}
			break;
	}
}

static void animrotate (int axis, int slice, int numtimes, int writehist)
{
	static int lastplayclk = 0x80000000;

	if (!(numtimes&3)) return;

	if (writehist)
	{
		int i;
		if (rotsavcur > 0) i = rotsav[(rotsavcur-1)&(ROTSAVSIZ-1)];
		if ((rotsavcur > 0) && ((i&~3) == (slice<<4)+(axis<<2)))
		{
			i = (i&~3) + ((i+numtimes)&3);
			if (i&3) rotsav[(rotsavcur-1)&(ROTSAVSIZ-1)] = i;
				 else { rotsavend -= (rotsavend >= rotsavcur); rotsavcur--; }
		}
		else
		{
			rotsav[(rotsavcur++)&(ROTSAVSIZ-1)] = (slice<<4)+(axis<<2)+(numtimes&3);
			if (rotsavcur-ROTSAVSIZ > rotsavbeg) rotsavbeg = rotsavcur-ROTSAVSIZ;
			rotsavend = rotsavcur;
		}
	}

		//If cube still rotating from previous animrotate, finish it immediately
	if ((rotslice >= 0) && (rotinc < 0)) rotate(rotaxis,rotslice,rotnum);

	if (labs(ltotclk-lastplayclk) > 50)
	{
		lastplayclk = ltotclk;
		float f = ((float)(rand()-16384))/262144.0+1.0+((float)((numtimes&3)==2))*.25;
		switch(rotaxis)
		{
			case 0: sndPlaySound("rotate4a.wav",SND_ASYNC); break;
			case 1: sndPlaySound("rotate4b.wav",SND_ASYNC); break;
			case 2: sndPlaySound("rotate4c.wav",SND_ASYNC); break;
		}
	}
	rotaxis = axis; rotslice = slice; rotnum = numtimes;
	rotcnt = PI; rotinc = -rotatespeed;
	switch (numtimes&3)
	{
		case 1: rotmul = PI*.25; break;
		case 2: if (numtimes < 0) rotmul = -PI*.5; else rotmul = PI*.5; break;
		case 3: rotmul = -PI*.25; break;
	}
	if (!timermode) { timermode = 1; startimer = ltotclk; } //Start timer at 1st move after 'M'
}

static int checkwin (int doanimate)
{
	int x, y, z;
	char ch;

	for(z=5;z>=0;z--)
	{
		ch = cubefacecol[z*MAXCDIM*MAXCDIM];
		for(y=cdim-1;y>=0;y--)
			for(x=cdim-1;x>=0;x--)
				if (cubefacecol[(z*MAXCDIM+y)*MAXCDIM+x] != ch) return(0);
	}
	if (doanimate)
	{
		if (winstate <= 0) { winstate = 32-1; ocolwidth = colwidth; sndPlaySound("airpump2.wav",SND_ASYNC); }
		if (timermode == 1) { timermode = 2; stoptimer = ltotclk; }
	}
	return(1);
}

static int getcubeindex (void)
{
	int i;

	if (!(rotslice&0x80000000)) return(-1);

	searchstat = 1; drawscreen(); //This drawscreen is for mouse selection
	if (searchstat != 2) { searchstat = 0; cgrabs = -1; return(-1); }

	searchstat = 0;
	switch(cgrabs>>1)
	{
		case 0: i = cgraby*MAXCDIM+cgrabz; break;
		case 1: i = cgrabx*MAXCDIM+cgrabz; break;
		case 2: i = cgrabx*MAXCDIM+cgraby; break;
	}
	i += cgrabs*MAXCDIM*MAXCDIM; cgrabs = -1;
	return(i);
}

static void drawpix (int x, int y, int col)
{
	if (((unsigned int)x >= (unsigned int)gdd.x) || ((unsigned int)y >= (unsigned int)gdd.y)) return;
	*(unsigned int *)(ylookup[y]+(x<<2)+gdd.f) = col;
}

//----------------------  WIN file select code begins ------------------------

#include <commdlg.h>
static char relpathbase[MAX_PATH];
static void relpathinit (char *st)
{
	int i;

	for(i=0;st[i];i++) relpathbase[i] = st[i];
	if ((i) && (relpathbase[i-1] != '/') && (relpathbase[i-1] != '\\'))
		relpathbase[i++] = '\\';
	relpathbase[i] = 0;
}

static char *relpath (char *st)
{
	int i;
	char ch0, ch1;
	for(i=0;st[i];i++)
	{
		ch0 = st[i];
		if ((ch0 >= 'a') && (ch0 <= 'z')) ch0 -= 32;
		if (ch0 == '/') ch0 = '\\';

		ch1 = relpathbase[i];
		if ((ch1 >= 'a') && (ch1 <= 'z')) ch1 -= 32;
		if (ch1 == '/') ch1 = '\\';

		if (ch0 != ch1) return(&st[i]);
	}
	return(&st[0]);
}

static char fileselectnam[MAX_PATH+1];
static int fileselect1stcall = -1; //Stupid directory hack
static char *loadfileselect (char *mess, char *spec, char *defext)
{
	int i;
	for(i=0;fileselectnam[i];i++) if (fileselectnam[i] == '/') fileselectnam[i] = '\\';
	OPENFILENAME ofn =
	{
		sizeof(OPENFILENAME),ghwnd,0,spec,0,0,1,fileselectnam,MAX_PATH,0,0,(char *)(((int)relpathbase)&fileselect1stcall),mess,
		/*OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|*/ OFN_HIDEREADONLY|OFN_NOCHANGEDIR,0,0,defext,0,0,0
	};
	fileselect1stcall = 0; //Let windows remember directory after 1st call
	i = GetOpenFileName(&ofn); clearkeys();
	if (!i) return(0); else return(fileselectnam);
}
static char *savefileselect (char *mess, char *spec, char *defext)
{
	int i;
	for(i=0;fileselectnam[i];i++) if (fileselectnam[i] == '/') fileselectnam[i] = '\\';
	OPENFILENAME ofn =
	{
		sizeof(OPENFILENAME),ghwnd,0,spec,0,0,1,fileselectnam,MAX_PATH,0,0,(char *)(((int)relpathbase)&fileselect1stcall),mess,
		OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,0,0,defext,0,0,0
	};
	fileselect1stcall = 0; //Let windows remember directory after 1st call
	i = GetSaveFileName(&ofn); clearkeys();
	if (!i) return(0); else return(fileselectnam);
}
//-----------------------  WIN file select code ends -------------------------
//------------------------ Simple PNG OUT code begins ------------------------
static FILE *pngofil;
static int pngoxplc, pngoyplc, pngoxsiz, pngoysiz;
static unsigned int pngocrc, pngoadcrc;

static unsigned int bswap (unsigned int a)
	{ return(((a&0xff0000)>>8) + ((a&0xff00)<<8) + (a<<24) + (a>>24)); }

static int crctab32[256];  //SEE CRC32.C
#define updatecrc32(c,crc) crc=(crctab32[(crc^c)&255]^(((unsigned)crc)>>8))
#define updateadl32(c,crc) \
{  c += (crc&0xffff); if (c   >= 65521) c   -= 65521; \
	crc = (crc>>16)+c; if (crc >= 65521) crc -= 65521; \
	crc = (crc<<16)+c; \
} \

static void fputbytes (unsigned int v, int n)
	{ for(;n;v>>=8,n--) { fputc(v,pngofil); updatecrc32(v,pngocrc); } }

static void pngoutopenfile (char *fnam, int xsiz, int ysiz)
{
	int i, j, k;
	char a[40];

	pngoxsiz = xsiz; pngoysiz = ysiz; pngoxplc = pngoyplc = 0;
	for(i=255;i>=0;i--)
	{
		k = i; for(j=8;j;j--) k = ((unsigned int)k>>1)^((-(k&1))&0xedb88320);
		crctab32[i] = k;
	}
	pngofil = fopen(fnam,"wb");
	*(int *)&a[0] = 0x474e5089; *(int *)&a[4] = 0x0a1a0a0d;
	*(int *)&a[8] = 0x0d000000; *(int *)&a[12] = 0x52444849;
	*(int *)&a[16] = bswap(xsiz); *(int *)&a[20] = bswap(ysiz);
	*(int *)&a[24] = 0x00000208; *(int *)&a[28] = 0;
	for(i=12,j=-1;i<29;i++) updatecrc32(a[i],j);
	*(int *)&a[29] = bswap(j^-1);
	fwrite(a,37,1,pngofil);
	pngocrc = -1; pngoadcrc = 1;
	fputbytes(0x54414449,4); fputbytes(0x0178,2);
}

static void pngoutputpixel (int rgbcol)
{
	int a[4];

	if (!pngoxplc)
	{
		fputbytes(pngoyplc==pngoysiz-1,1);
		fputbytes(((pngoxsiz*3+1)*0x10001)^0xffff0000,4);
		fputbytes(0,1); a[0] = 0; updateadl32(a[0],pngoadcrc);
	}
	fputbytes(bswap(rgbcol<<8),3);
	a[0] = (rgbcol>>16)&255; updateadl32(a[0],pngoadcrc);
	a[0] = (rgbcol>> 8)&255; updateadl32(a[0],pngoadcrc);
	a[0] = (rgbcol    )&255; updateadl32(a[0],pngoadcrc);
	pngoxplc++; if (pngoxplc < pngoxsiz) return;
	pngoxplc = 0; pngoyplc++; if (pngoyplc < pngoysiz) return;
	fputbytes(bswap(pngoadcrc),4);
	a[0] = bswap(pngocrc^-1); a[1] = 0; a[2] = 0x444e4549; a[3] = 0x826042ae;
	fwrite(a,1,16,pngofil);
	a[0] = bswap(ftell(pngofil)-(33+8)-16);
	fseek(pngofil,33,SEEK_SET); fwrite(a,1,4,pngofil);
	fclose(pngofil);
}
//------------------------- Simple PNG OUT code ends -------------------------

static int selectcolor (int *c)
{
	static COLORREF mycolors[16];
	CHOOSECOLOR cc;

	memset(&cc,0,sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = ghwnd;
	cc.lpCustColors = (unsigned long *)&mycolors[0];
	cc.rgbResult = (((*c)>>16)&255) + ((*c)&0xff00) + (((*c)&255)<<16);
	cc.Flags = CC_FULLOPEN|CC_RGBINIT;
	if (ChooseColor(&cc))
	{
		(*c) = ((cc.rgbResult&255)<<16) + (cc.rgbResult&0xff00) + ((cc.rgbResult>>16)&255);
		return(1);
	}
	return(0);
}

static int capturecount = 0;
static void screencapture (char *filename, int frameptr, int daxdim, int daydim, int dabpl)
{
	int i, oi, x, y, p, dacol;

	pngoutopenfile(filename,daxdim,daydim);
	oi = 0;
	for(y=0;y<daydim;y++)
	{
		p = y*dabpl + frameptr;
		for(x=0;x<daxdim;x++) pngoutputpixel(*(int *)((x<<2)+p));
	}
}

static void showinfo ()
{
	//WARNING: MessageBox can only handle 1024 bytes!
	MessageBox(ghwnd,
"Virtual Rubik's cube by Ken Silverman (http://advsys.net/ken), (1998-)\n"
"Walbeehm solvers by Ben Jos Walbeehm. 3 separate solvers written from scratch (2007)\n"
"\n"
"Command line options:\n"
"/?, /h\tDisplay this help\n"
"/#x#(x#)\tSet window size. Use color depth for full screen. Default: /800x600\n"
"filename\tLoad game state from file. If no file is specified, RUBIX will\n"
"\tautomatically load the game state from RUBIX.SAV (if it exists)\n"
"\n"
"Controls not found in menus:\n"
"Left drag\t\tRotate cube side\n"
"Right drag/arrows\tRotate view\n"
"1-7\t\tHold to highlight cube groups (3x3 only)\n"
"CTRL\t\tHold to highlight concentric squares\n"
"Shift+{1..6}\tRun Ben Jos's solver at quality level 1-6\n"
"Zoom\t\tScroll wheel or: / and * on keypad\n"
"Drag\t\tMiddle button+Mouse or Shift+Right button+Mouse\n"
,prognam,MB_OK);
	clearkeys();
}

static void setmousein (int x, int y)
{
	mouseoutstat = 0;
	fsearchx = min(max(x,0),xres); ftol(fsearchx,&searchx);
	fsearchy = min(max(y,0),yres); ftol(fsearchy,&searchy);
}

//--------------------------------------------------------------------------------------------------
static int myclosefunc ()
{
	static int alreadyquit = 0;
	if (alreadyquit) return(1);
	if (checkwin(0)) { quitloop(); alreadyquit = 1; return(0); }
	if (MessageBox(ghwnd,"Quit?",prognam,MB_YESNO) == IDYES)
		{ quitloop(); alreadyquit = 1; return(1); }
	clearkeys();
	return(0);
}

static short *menustart (short *sptr) { *sptr++ = 0; *sptr++ = 0; return(sptr); } //MENUITEMTEMPLATEHEADER
static short *menuadd (short *sptr, char *st, int flags, int id)
{
	*sptr++ = flags; //MENUITEMTEMPLATE
	if (!(flags&MF_POPUP)) *sptr++ = id;
	sptr += MultiByteToWideChar(CP_ACP,0,st,-1,(LPWSTR)sptr,strlen(st)+1);
	return(sptr);
}

static int mymenufunc (WPARAM wparam, LPARAM lparam)
{
	__int64 q;
	int i, j, x, y;
	char *v;

	switch(LOWORD(wparam))
	{
		case FILENEW:
			if (!checkwin(0))
			{
				if (MessageBox(ghwnd,"Reset cube?",prognam,MB_OKCANCEL) == IDOK) resetcube();
				clearkeys();
			} else resetcube();
			break;
		case FILELOAD:
			if (v = (char *)loadfileselect("LOAD game...","*.SAV\0*.sav\0All files (*.*)\0*.*\0\0","SAV"))
			{
				if (!loadrubix(v)) { strcpy(message,"File not found."); messagetimeout = ltotclk+2000; break; }
				q = klock()*1000000;
				ltotclk = (int)(((double)(q-startotclk))*rperfrq*1000.0);
				sprintf(message,"Game state loaded from %s",v); messagetimeout = ltotclk+2000;
			}
			break;
		case FILESAVE:
			if (v = (char *)savefileselect("SAVE game...","*.SAV\0*.sav\0All files (*.*)\0*.*\0\0","SAV"))
			{
				saverubix(v);

				q = klock()*1000000;
				ltotclk = (int)(((double)(q-startotclk))*rperfrq*1000.0);
				sprintf(message,"Game state saved to %s",v); messagetimeout = ltotclk+2000;
			}
			break;
		case SCREENCAP: doscrcap = 1; break; //F12
		case FILEEXIT: myclosefunc(); return(0);
		case CUBESIZE: case CUBESIZE+1: case CUBESIZE+2: case CUBESIZE+3:
		case CUBESIZE+4: case CUBESIZE+5: case CUBESIZE+6: case CUBESIZE+7:
			if (!checkwin(0))
			{
				i = (MessageBox(ghwnd,"Abandon game?",prognam,MB_OKCANCEL) == IDOK);
				clearkeys();
			} else i = 1;
			if (i)
			{
				int ltotclk;

				cdim = LOWORD(wparam)-(CUBESIZE-1); resetcube();
				menu_update_cdim();

				q = klock()*1000000;
				ltotclk = (int)(((double)(q-startotclk))*rperfrq*1000.0);
				sprintf(message,"%dx%dx%d",cdim,cdim,cdim); messagetimeout = ltotclk+2000;
			}
			break;
		case CUBECOPY:
			showothercubemode = 1;
			memcpy(ocubefacecol,cubefacecol,sizeof(ocubefacecol));
			memcpy(orotsav,rotsav,sizeof(rotsav));
			orotsavbeg = rotsavbeg; orotsavcur = rotsavcur; orotsavend = rotsavend;

			sprintf(message,"Game state copied");
			messagetimeout = ltotclk+2000;
			break;
		case CUBEPASTE:
			q = klock()*1000000;
			ltotclk = (int)(((double)(q-startotclk))*rperfrq*1000.0);

			//showothercubemode = 0;
			if (ocubefacecol[0] != 255)
			{
				for(i=5;i>=0;i--)
					for(y=cdimm1;y>=0;y--)
						for(x=cdimm1;x>=0;x--)
							cubefacecol[(i*MAXCDIM+y)*MAXCDIM+x] = ocubefacecol[(i*MAXCDIM+y)*MAXCDIM+x];

				memcpy(rotsav,orotsav,sizeof(orotsav));
				rotsavbeg = orotsavbeg; rotsavcur = orotsavcur; rotsavend = orotsavend;
			}
			sprintf(message,"Game state restored");
			messagetimeout = ltotclk+2000;
			break;
		case CUBEERASE:
			showothercubemode = 0;
			sprintf(message,"Copy removed");
			messagetimeout = ltotclk+2000;
			break;
		case CUBERAND1:
			qtotclk = klock()*1000000;
			if (rotslice < 0) animrotate((rand()*3)>>15,(rand()*cdim)>>15,(rand()-16384)|1,1);
			break;
		case CUBERANDALL:
			if (!checkwin(0))
			{
				i = (MessageBox(ghwnd,"Mess up cube?",prognam,MB_OKCANCEL) == IDOK);
				clearkeys();
			}
			else i = 1;
			if (i)
			{
				for(i=16384;i;i--) rotate((rand()*3)>>15,(rand()*cdim)>>15,((rand()*3)>>15)+1);
				timermode = 0;
				rotsavbeg = rotsavcur = rotsavend = 0;
			}
			break;
		case HISTBACK: //Backspace
			if (rotsavcur > rotsavbeg)
			{
				qtotclk = klock()*1000000;
				i = rotsav[(--rotsavcur)&(ROTSAVSIZ-1)];
				animrotate((i>>2)&3,i>>4,(-i)&3,0);
			}
			break;
		case HISTFORW: //Tab
			if (rotsavcur < rotsavend)
			{
				qtotclk = klock()*1000000;
				i = rotsav[(rotsavcur++)&(ROTSAVSIZ-1)];
				animrotate((i>>2)&3,i>>4,i&3,0);
			}
			break;
		case HISTHOME: //Home
			while (rotsavcur > rotsavbeg)
			{
				i = rotsav[(--rotsavcur)&(ROTSAVSIZ-1)];
				rotate((i>>2)&3,i>>4,(-i)&3);
			}
			break;
		case HISTEND: //End
			while (rotsavcur < rotsavend)
			{
				i = rotsav[(rotsavcur++)&(ROTSAVSIZ-1)];
				rotate((i>>2)&3,i>>4,i&3);
			}
			break;
		case SOLVE: case SOLVE+1: case SOLVE+2: case SOLVE+3: case SOLVE+4: case SOLVE+5:
			j = LOWORD(wparam)-SOLVE;
			if ((j >= 4) && (cdim == 3))
			{
				j = MessageBox(ghwnd,"You selected a high quality solve. This could take a long time. Continue?",prognam,MB_OKCANCEL);
				clearkeys();
				if (j == IDCANCEL) break;
			}

			i = rubixsolve_bjw(cdim,MAXCDIM,cubefacecol,&rotsav[0],j);
			if (i >= 0)
			{
					  if (cdim == 2) sprintf(message,"BJW%d(%d)",min(j+1,2),i);
				else if (cdim == 3) sprintf(message,"BJW%d(%d)",j+1,i);
				else                sprintf(message,"BJW:Solved in %d moves",i);

				rotsavbeg = rotsavcur = 0; rotsavend = i;
				if ((cdim >= 2) && (cdim <= 4) && (i*2+32 < sizeof(message)))
				{
					if (rotsavend > 0) strcat(message,":");
					for(i=0;i<rotsavend;i++)
					{
						x = rotsav[i];
						j = strlen(message); message[j+1] = 0;
						if (j >= (gdd.x>>3)-4) { strcat(message,"..."); break; }
						if ((cdim == 2) && (x >= 16)) x += 16;
						if (cdim == 4) x &= ~16;
						switch(x&~3)
						{
							case  0: message[j] = notation3[0]; x = (x&~3)+((-x)&3); break;
							case  4: message[j] = notation3[2];                      break;
							case  8: message[j] = notation3[4]; x = (x&~3)+((-x)&3); break;
							case 16: message[j] = 'M';          x = (x&~3)+((-x)&3); break;
							case 20: message[j] = 'E';          x = (x&~3)+((-x)&3); break;
							case 24: message[j] = 'S';          x = (x&~3)+((-x)&3); break;
							case 32: message[j] = notation3[1];                      break;
							case 36: message[j] = notation3[3]; x = (x&~3)+((-x)&3); break;
							case 40: message[j] = notation3[5];                      break;
						}
						if ((cdim == 4) && (rotsav[i] >= 16) && (rotsav[i] < 48)) message[j] += 32;
						switch(x&3)
						{
							case 1: strcat(message,"\'"); break;
							case 2: strcat(message,"2"); break;
							case 3: if (i < rotsavend-1) strcat(message," "); break;
						}
					}
				}
				messagetimeout = 0x7fffffff;
			}
			else
			{
				messagetimeout = ltotclk+4000; //display error for 4 seconds
			}
			break;
		case OPTROTSPEED:   case OPTROTSPEED+1: case OPTROTSPEED+2:
		case OPTROTSPEED+3: case OPTROTSPEED+4: case OPTROTSPEED+5:
		case OPTROTSPEED+6: case OPTROTSPEED+7: case OPTROTSPEED+8:
			j = LOWORD(wparam)-OPTROTSPEED;
			for(i=0;i<9;i++) CheckMenuItem(gmenu,i+OPTROTSPEED,(-(i==j))&MF_CHECKED);
			rotatespeed = (float)(1<<j);
			sprintf(message,"Rotation speed = %g\n",rotatespeed);
			messagetimeout = ltotclk+1000;
			break;

		case OPTRESETORI:
			a2v = PI/6.0; a3v = PI/-6.0;
			{
			float cosa2, sina2, cosa3, sina3;
			fcossin(a2v,&cosa2,&sina2);
			fcossin(a3v,&cosa3,&sina3);
			i3.x = cosa3;  i3.y = -sina3*sina2; i3.z = sina3*cosa2;
			j3.x = 0;      j3.y = cosa2;        j3.z = sina2;
			k3.x = -sina3; k3.y = -cosa3*sina2; k3.z = cosa3*cosa2;
			}
			ghx = (float)gdd.x*0.5;
			ghy = (float)gdd.y*0.5;
			ghz = ghx*1.25;

			break;
		case OPTANGLE:
			anglemode ^= 1;
			if (!anglemode) { sprintf(message,"Latitude/Longitude mode"); a2v = PI/6.0; a3v = PI/-6.0; }
						  else { sprintf(message,"Free direction mode"); }
			messagetimeout = ltotclk+2000;
			break;
		case OPTBACKCOL:
			if (selectcolor(&backcol))
			{
				pal[7] = backcol;
				sticker_init();
			}
			break;
		case OPTCRACKCOL:
			if (selectcolor(&crackcol))
			{
				pal[0] = crackcol;
				sticker_init();
			}
			break;
		case OPTEDITCUBE: editmode ^= 1; editpatchcnt = editpatchbeg = editpatchend = 0;
			CheckMenuItem(gmenu,OPTEDITCUBE,(-editmode)&MF_CHECKED); break;
		case VISUALDETAIL: case VISUALDETAIL+1: case VISUALDETAIL+2:
			visualdetail = LOWORD(wparam)-VISUALDETAIL;
			for(i=0;i<3;i++) CheckMenuItem(gmenu,VISUALDETAIL+i,(-(visualdetail==i))&MF_CHECKED);
			break;
		case HELPABOUT: showinfo(); break;
	}
	return(1);
}

static long CALLBACK mypeekwindowproc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_ENTERMENULOOP: return(0);
		case WM_SYSCOMMAND: return(DefWindowProc(hwnd,msg,wParam,lParam));
		case WM_SYSKEYDOWN: case WM_SYSKEYUP: case WM_SYSCHAR: return(DefWindowProc(hwnd,msg,wParam,lParam));
		case WM_CHAR: DefWindowProc(hwnd,msg,wParam,lParam); break;
		case WM_COMMAND: return(mymenufunc(wParam,lParam));
		case WM_CLOSE: if (!myclosefunc()) return(1); break;
	}
	return(-1);
}

static void mymenuinit ()
{
	short sbuf[4096], *sptr;

	peekwindowproc = mypeekwindowproc;

		//Use MF_POPUP for top entries
		//Use MF_END for last (top or pulldown) entry
		//MF_GRAYED|MF_DISABLED|4=right_justify|MF_CHECKED|MF_MENUBARBREAK|MF_MENUBREAK|MF_OWNERDRAW

	sptr = menustart(sbuf);

	sptr = menuadd(sptr,"&File"                  ,MF_POPUP       ,0);
	sptr = menuadd(sptr,"&New\tN"                ,0              ,FILENEW);
	sptr = menuadd(sptr,"&Open\tL"               ,0              ,FILELOAD);
	sptr = menuadd(sptr,"&Save\tS"               ,0              ,FILESAVE);
	sptr = menuadd(sptr,""                       ,MF_SEPARATOR   ,0);
	sptr = menuadd(sptr,"Screen &capture (RUBX#.PNG)\tF12",0     ,SCREENCAP);
	sptr = menuadd(sptr,""                       ,MF_SEPARATOR   ,0);
	sptr = menuadd(sptr,"E&xit\tAlt+F4"          ,MF_END         ,FILEEXIT);

	sptr = menuadd(sptr,"&Cube"                  ,MF_POPUP       ,0);
	sptr = menuadd(sptr,"&Size\tPGUP/PGDN"       ,MF_POPUP       ,0);
	sptr = menuadd(sptr,"&1x1x1"                 , (-(cdim==1))&MF_CHECKED        ,CUBESIZE);
	sptr = menuadd(sptr,"&2x2x2"                 , (-(cdim==2))&MF_CHECKED        ,CUBESIZE+1);
	sptr = menuadd(sptr,"&3x3x3"                 , (-(cdim==3))&MF_CHECKED        ,CUBESIZE+2);
	sptr = menuadd(sptr,"&4x4x4"                 , (-(cdim==4))&MF_CHECKED        ,CUBESIZE+3);
	sptr = menuadd(sptr,"&5x5x5"                 , (-(cdim==5))&MF_CHECKED        ,CUBESIZE+4);
	sptr = menuadd(sptr,"&6x6x6"                 , (-(cdim==6))&MF_CHECKED        ,CUBESIZE+5);
	sptr = menuadd(sptr,"&7x7x7"                 , (-(cdim==7))&MF_CHECKED        ,CUBESIZE+6);
	sptr = menuadd(sptr,"&8x8x8"                 ,((-(cdim==8))&MF_CHECKED)|MF_END,CUBESIZE+7);
	sptr = menuadd(sptr,"&Copy\tC"               ,0              ,CUBECOPY);
	sptr = menuadd(sptr,"&Paste\tP"              ,0              ,CUBEPASTE);
	sptr = menuadd(sptr,"&Erase copy\t\\"        ,0              ,CUBEERASE);
	sptr = menuadd(sptr,"&Random move\tR"        ,0              ,CUBERAND1);
	sptr = menuadd(sptr,"&Mess up!\tM"           ,MF_END         ,CUBERANDALL);

	sptr = menuadd(sptr,"&Solve"                 ,MF_POPUP       ,0);
	sptr = menuadd(sptr,"Walbeehm &1 (Fastest)"  ,0              ,SOLVE);
	sptr = menuadd(sptr,"Walbeehm &2 (Faster)"   ,0              ,SOLVE+1);
	sptr = menuadd(sptr,"Walbeehm &3 (Fast)"     ,0              ,SOLVE+2);
	sptr = menuadd(sptr,"Walbeehm &4"            ,0              ,SOLVE+3);
	sptr = menuadd(sptr,"Walbeehm &5 (Slow)"     ,0              ,SOLVE+4);
	sptr = menuadd(sptr,"Walbeehm &6 (Very Slow)",MF_END         ,SOLVE+5);

	sptr = menuadd(sptr,"&History"               ,MF_POPUP       ,0);
	sptr = menuadd(sptr,"&Backward\tBackspace"   ,0              ,HISTBACK);
	sptr = menuadd(sptr,"&Forward\tTab"          ,0              ,HISTFORW);
	sptr = menuadd(sptr,"Jump to &start\tHome"   ,0              ,HISTHOME);
	sptr = menuadd(sptr,"Jump to &end\tEnd"      ,MF_END         ,HISTEND);

	sptr = menuadd(sptr,"&Options"               ,MF_POPUP       ,0);
	sptr = menuadd(sptr,"Reset &orientation\t/"  ,0              ,OPTRESETORI);
	sptr = menuadd(sptr,"Toggle &angle rotation mode\tA",0       ,OPTANGLE);
	sptr = menuadd(sptr,"&Change background color\tB",0          ,OPTBACKCOL);
	sptr = menuadd(sptr,"Change crack color"     ,0              ,OPTCRACKCOL);
	sptr = menuadd(sptr,"&Edit stickers\tE"      ,(-editmode)&MF_CHECKED,OPTEDITCUBE);
	sptr = menuadd(sptr,"&Rotation speed\t[,]"   ,MF_POPUP       ,0);
	sptr = menuadd(sptr,"1"                      , (-(rotatespeed==  1.f))&MF_CHECKED        ,OPTROTSPEED);
	sptr = menuadd(sptr,"2"                      , (-(rotatespeed==  2.f))&MF_CHECKED        ,OPTROTSPEED+1);
	sptr = menuadd(sptr,"4"                      , (-(rotatespeed==  4.f))&MF_CHECKED        ,OPTROTSPEED+2);
	sptr = menuadd(sptr,"8"                      , (-(rotatespeed==  8.f))&MF_CHECKED        ,OPTROTSPEED+3);
	sptr = menuadd(sptr,"16"                     , (-(rotatespeed== 16.f))&MF_CHECKED        ,OPTROTSPEED+4);
	sptr = menuadd(sptr,"32"                     , (-(rotatespeed== 32.f))&MF_CHECKED        ,OPTROTSPEED+5);
	sptr = menuadd(sptr,"64"                     , (-(rotatespeed== 64.f))&MF_CHECKED        ,OPTROTSPEED+6);
	sptr = menuadd(sptr,"128"                    , (-(rotatespeed==128.f))&MF_CHECKED        ,OPTROTSPEED+7);
	sptr = menuadd(sptr,"256"                    ,((-(rotatespeed==256.f))&MF_CHECKED)|MF_END,OPTROTSPEED+8);
	sptr = menuadd(sptr,"&Visual detail"         ,MF_POPUP|MF_END,0);
	sptr = menuadd(sptr,"&Low detail"            , (-(visualdetail==0))&MF_CHECKED        ,VISUALDETAIL);
	sptr = menuadd(sptr,"&Medium detail"         , (-(visualdetail==1))&MF_CHECKED        ,VISUALDETAIL+1);
	sptr = menuadd(sptr,"&High detail"           ,((-(visualdetail==2))&MF_CHECKED)|MF_END,VISUALDETAIL+2);

	sptr = menuadd(sptr,"&About"                 ,MF_END,HELPABOUT);

	gmenu = LoadMenuIndirect(sbuf); SetMenu(ghwnd,gmenu);
	if (gmenu == 0) gmenu = (HMENU)-1; //Don't call mymenuinit repeatedly if failed
}

static void mymenuuninit ()
{
	if ((gmenu) && (gmenu != (HMENU)-1)) { DestroyMenu(gmenu); gmenu = 0; }
}

//--------------------------------------------------------------------------------------------------

int WINAPI WinMain (HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmdline, int ncmdshow)
{
	__int64 q;
	point3d i3b, j3b, k3b;
	float cosa1, sina1, cosa2, sina2, cosa3, sina3;
	float f, nu, nv, c1c3, c1s3, s1c3, s1s3, t, ox, oy, oz, rr[9];
	int ch, i, j, k, l, u, v, x, y, dabpl, daxdim, daydim, argc, argfilindex, grabbedbar = 0;
	int omousx = 0, omousy = 0, nmousx = 0, nmousy = 0;
	char tbuf[256], st[MAX_PATH], *argv[MAX_PATH>>1];

	ghinst = hinst;
	GetCurrentDirectory(sizeof(st),st);
	relpathinit(st);

	strcpy(fileselectnam,"rubix.sav");

	prognam = "RUBIX by Ken Silverman";
	xres = 800; yres = 600; argfilindex = -1;
	argc = cmdline2arg(cmdline,argv);
	for(i=argc-1;i>0;i--)
	{
		if ((argv[i][0] != '/') && (argv[i][0] != '-'))
		{
			if (argfilindex < 0) argfilindex = i;
			continue;
		}
		if ((argv[i][1] == '?') || (argv[i][1] == 'H') || (argv[i][1] == 'h')) { showinfo(); return(-1); }
		if ((argv[i][1] >= '0') && (argv[i][1] <= '9'))
		{
			k = 0; ch = 0;
			for(j=1;;j++)
			{
				if ((argv[i][j] >= '0') && (argv[i][j] <= '9'))
					{ k = (k*10+argv[i][j]-48); continue; }
				switch (ch)
				{
					case 0: xres = k; break;
					case 1: yres = k; break;
					case 2: break;
				}
				if (!argv[i][j]) break;
				ch++; if (ch > 2) break;
				k = 0;
			}
		}
	}
	if ((xres < 256) || (yres < 192)) { xres = 256; yres = 192; }

	if (initapp(hinst) < 0) { MessageBox(ghwnd,"initapp failed",prognam,MB_OK); return(1); }
	mymenuinit();

	cputype = getcputype();

	backcol = 0x705030; crackcol = 0x404040;

#if 0
		//Original cube colors (1980's), except orange replaced with magenta:
	pal[1] = 0xe00000; //Red
	pal[2] = 0xff00ff; //(Magenta)
 //pal[2] = 0xff9000; //Dark orange :/
	pal[3] = 0xf0f0f0; //White
	pal[4] = 0x0000a0; //Blue
	pal[5] = 0xffe800; //Yellow
	pal[6] = 0x008040; //Green
#else
		//Modern cube colors:
	pal[1] = 0x4040a0; //Blue
	pal[2] = 0x188018; //Green
	pal[3] = 0xf0f0f0; //White
	pal[4] = 0xf0f000; //Yellow
	pal[5] = 0xff7000; //Orange
	pal[6] = 0xe01818; //Red
#endif

	pal[7] = backcol; //Background col (default: 0)
	sticker_init();

	fpuinit(0x08);  //24 bit, round to Ï

	c3.x = 0; c3.y = 0; c3.z = (cdim<<1);
	i3.x = 1; i3.y = 0; i3.z = 0;
	j3.x = 0; j3.y = 1; j3.z = 0;
	k3.x = 0; k3.y = 0; k3.z = 1;
	a2v = PI/6.0;
	a3v = PI/-6.0;

	searchstat = 0; rotaxis = 0; rotslice = 0x80000000; rotang = 0;

		//points of faces
	ptface[0][0] = 0; ptface[0][1] = 2; ptface[0][2] = 6; ptface[0][3] = 4;
	ptface[1][0] = 5; ptface[1][1] = 7; ptface[1][2] = 3; ptface[1][3] = 1;
	ptface[2][0] = 0; ptface[2][1] = 4; ptface[2][2] = 5; ptface[2][3] = 1;
	ptface[3][0] = 6; ptface[3][1] = 2; ptface[3][2] = 3; ptface[3][3] = 7;
	ptface[4][0] = 1; ptface[4][1] = 3; ptface[4][2] = 2; ptface[4][3] = 0;
	ptface[5][0] = 4; ptface[5][1] = 6; ptface[5][2] = 7; ptface[5][3] = 5;

	ocubefacecol[0] = 255; //Should be invalid color

	resetcube();
	if (argfilindex >= 0) strcpy(fileselectnam,argv[argfilindex]);
	loadrubix(fileselectnam);


	typedef struct { char *buf; int leng, xs, ys; } fontbittyp;
	for(i=0;i<sizeof(fontlist)/sizeof(fontlist[0]);i++)
	{
		font[i].f = (int)fontlist[i].buf;
		font[i].p = (fontlist[i].xs<<2);
		font[i].x = fontlist[i].xs;
		font[i].y = fontlist[i].ys*(128-32);
	}

	fmousx = 0; fmousy = 0;
	fsearchx = (float)(xres>>1);
	fsearchy = (float)(yres>>1);

	ghcrosscurs = gencrosscursor();
	ghhandcurs = genhandcursor();

	rperfrq = 1.0/1000000;
	startotclk = klock()*1000000; qtotclk = startotclk;
	srand((int)qtotclk);

	while (!breath())
	{
		q = klock()*1000000;
		fsynctics = ((float)(q-qtotclk))*rperfrq;
		ltotclk = (int)(((double)(q-startotclk))*rperfrq*1000.0);
		qtotclk = q;

		while (ch = keyread())
		{
			if ((!anglemode) && (cdim == 3)) //Latitude/Longitude angle mode
			{
					//08/22/2005: An attempt at keyboard rotation controls:
					//Disabled because learning curve was too high :/
					//02/17/2007: Rewrote controls and re-enabled.
					//
					//               KP5
					//           KP2  \
					// KP8 KP9     \   KP6
					//  |   |      KP3
					// KP0 KP.
					//
					//     KP4 <-> KP+
					//     KP1 <-> KPEnt
					//
					//0x45 0xb5 0x37 0x4a
					//0x47 0x48 0x49 0x4e             0x48 0x49
					//0x4b 0x4c 0x4d |__|        0x4b 0x4c 0x4d 0x4e
					//0x4f 0x50 0x51 0x9c        0x4f 0x50 0x51 0x9c
					//[ 0x52  ] 0x53 |__|             0x52 0x53

				if (((ch>>8)&255) == 0x4b) { animrotate(1,0,-1,1); continue; } //KP4
				if (((ch>>8)&255) == 0x4e) { animrotate(1,0,+1,1); continue; } //KP+
				if (((ch>>8)&255) == 0x4f) { animrotate(1,2,-1,1); continue; } //KP1
				if (((ch>>8)&255) == 0x9c) { animrotate(1,2,+1,1); continue; } //KPEnt

				t = fmod(a3v-PI*.25,PI*2); if (t < 0) t += PI*2; i = (int)(t*(2.0/PI));
				if ((((ch>>8)&255) == 0x48) || (((ch>>8)&255) == 0x52)) //KP8, KP0
				{
					if (((ch>>8)&255) == 0x48) j = 1; else j = -1;
					switch(i)
					{
						case 0: animrotate(2,2,+j,1); break;
						case 1: animrotate(0,2,+j,1); break;
						case 2: animrotate(2,0,-j,1); break;
						case 3: animrotate(0,0,-j,1); break;
					}
					continue;
				}
				if ((((ch>>8)&255) == 0x49) || (((ch>>8)&255) == 0x53)) //KP0, KP.
				{
					if (((ch>>8)&255) == 0x49) j = 1; else j = -1;
					switch(i)
					{
						case 0: animrotate(2,0,+j,1); break;
						case 1: animrotate(0,0,+j,1); break;
						case 2: animrotate(2,2,-j,1); break;
						case 3: animrotate(0,2,-j,1); break;
					}
					continue;
				}
				if ((((ch>>8)&255) == 0x4c) || (((ch>>8)&255) == 0x4d)) //KP5, KP6
				{
					if (((ch>>8)&255) == 0x4c) j = 1; else j = -1;
					switch(i)
					{
						case 0: animrotate(0,2,-j,1); break;
						case 1: animrotate(2,0,+j,1); break;
						case 2: animrotate(0,0,+j,1); break;
						case 3: animrotate(2,2,-j,1); break;
					}
					continue;
				}
				if ((((ch>>8)&255) == 0x50) || (((ch>>8)&255) == 0x51)) //KP2, KP3
				{
					if (((ch>>8)&255) == 0x50) j = 1; else j = -1;
					switch(i)
					{
						case 0: animrotate(0,0,-j,1); break;
						case 1: animrotate(2,2,+j,1); break;
						case 2: animrotate(0,2,+j,1); break;
						case 3: animrotate(2,0,-j,1); break;
					}
					continue;
				}
			}

			if (((ch>>8)&255) == 0x15) //Y
			{
				if (ch&0xc0000) //Ctrl+Y (redo editing)
				{
					if ((editmode) && (editpatchcnt < editpatchend))
					{
						i = editpatches[(editpatchcnt&(EDITPATCHMAX-1))];
						cubefacecol[i%(6*MAXCDIM*MAXCDIM)] = ((i/(6*MAXCDIM*MAXCDIM))/6)+1;
						editpatchcnt++;
					}
				}
				continue;
			}
			if (((ch>>8)&255) == 0x2c) //Z
			{
				if (ch&0xc0000) //Ctrl+Z (undo editing)
				{
					if ((editmode) && (editpatchcnt > editpatchbeg))
					{
						editpatchcnt--;
						i = editpatches[(editpatchcnt&(EDITPATCHMAX-1))];
						cubefacecol[i%(6*MAXCDIM*MAXCDIM)] = ((i/(6*MAXCDIM*MAXCDIM))%6)+1;
					}
				}
				continue;
			}
			if ((((ch>>8)&255) == 0x3e) && (ch&0x300000)) myclosefunc(); //Simulate Alt+F4

			switch(ch&255)
			{
				case 'N': case 'n': mymenufunc(FILENEW,0); break;
				case 'L': case 'l': mymenufunc(FILELOAD ,0); break;
				case 'S': case 's': mymenufunc(FILESAVE ,0); break;
				case 'C': case 'c': mymenufunc(CUBECOPY ,0); break;
				case 'P': case 'p': mymenufunc(CUBEPASTE,0); break;
				case '\\':          mymenufunc(CUBEERASE,0); break;
				case 'R': case 'r': mymenufunc(CUBERAND1,0); break;
				case 'M': case 'm': mymenufunc(CUBERANDALL,0); break;
				case 8:             mymenufunc(HISTBACK ,0); break; //Backspace
				case 9:             if (editmode) { i = getcubeindex(); if (i >= 0) curcolindex = cubefacecol[i]; } //Tab
										  else mymenufunc(HISTFORW ,0); break;
				case '/':           if (((ch>>8)&255) == 0x35) mymenufunc(OPTRESETORI,0); break;
				case 'A': case 'a': mymenufunc(OPTANGLE,0); break;
				case 'B': case 'b': mymenufunc(OPTBACKCOL,0); break; //Set random background color
				case 'E': case 'e': mymenufunc(OPTEDITCUBE,0); break;
				case '[': case ']': //halve/double rotation speed
					if ((ch&255) == '[') { if (rotatespeed <=   1.f) break; rotatespeed *= .5f; }
										 else { if (rotatespeed >= 256.f) break; rotatespeed *= 2.f; }
					j = (int)(log(rotatespeed)/log(2.0)+0.5);
					for(i=0;i<9;i++) CheckMenuItem(gmenu,i+OPTROTSPEED,(-(i==j))&MF_CHECKED);
					sprintf(message,"Rotation speed = %g\n",rotatespeed);
					messagetimeout = ltotclk+1000;
					break;
				case '1': case '2': case '3': case '4': case '5': case '6':
					if (editmode) curcolindex = (ch&255)-'0';
					break;
				case '!': case '@': case '#': case '$': case '%': case '^': //Solve!
					switch(ch&255)
					{
						case '!': j = 0; break; //Fast
						case '@': j = 1; break;
						case '#': j = 2; break;
						case '$': j = 3; break;
						case '%': j = 4; break;
						case '^': j = 5; break; //Quality
					}
					for(i=1;i<=6;i++) keystatus[i+1] = 0; //Hack for MessageBox
					mymenufunc(SOLVE+j,0);
					break;
				case 0:
					switch((ch>>8)&0xff)
					{
						case 0xc9: case 0xd1: //PGUP,PGDN
							if (!checkwin(0))
							{
								i = (MessageBox(ghwnd,"Abandon game?",prognam,MB_OKCANCEL) == IDOK);
								clearkeys();
							} else i = 1;
							if (i)
							{
								if (((ch>>8)&0xff) == 0xc9) { if (cdim >       1) cdim--; resetcube(); }
															  else { if (cdim < MAXCDIM) cdim++; resetcube(); }

								menu_update_cdim();

								q = klock()*1000000;
								ltotclk = (int)(((double)(q-startotclk))*rperfrq*1000.0);
								sprintf(message,"%dx%dx%d",cdim,cdim,cdim); messagetimeout = ltotclk+2000;
							}
							break;
						case 0xc7: mymenufunc(HISTHOME,0); break; //Home
						case 0xcf: mymenufunc(HISTEND,0); break; //End
						case 0x3b: mymenufunc(HELPABOUT,0); break; //F1
						case 0x58: mymenufunc(SCREENCAP,0); break; //F12
					}
					break;
				case '<': case '>': case ',': case '.': case ' ': //Edit cube (could make it invalid)
					if (!editmode) break;
					i = getcubeindex(); if (i < 0) break;
					j = cubefacecol[i];
					switch(ch&255)
					{
						case ' ': cubefacecol[i] = curcolindex; break;
						case '<': case ',': if (cubefacecol[i] >= 6) cubefacecol[i] = 0; cubefacecol[i]++; break;
						case '>': case '.': cubefacecol[i]--; if (!cubefacecol[i]) cubefacecol[i] = 6; break;
					}
					if (cubefacecol[i] != j)
					{
						editpatches[(editpatchcnt&(EDITPATCHMAX-1))] = ((cubefacecol[i]-1)*6+(j-1))*(6*MAXCDIM*MAXCDIM) + i;
						editpatchcnt++;
						editpatchbeg = max(editpatchbeg,editpatchcnt-EDITPATCHMAX);
						editpatchend = editpatchcnt;
					}
					break;
				default: break;
			}
		}

		fsearchx = mousx; fmousx = dmousx; dmousx = 0;
		fsearchy = mousy; fmousy = dmousy; dmousy = 0;
		if ((dmousz != 0) || (keystatus[0xb5]|keystatus[0x37]))
		{
			float oghx, oghy, oghz;
			oghz = ghz; ghz *= pow(1.3,dmousz/120);
			if (keystatus[0x37]) ghz *= pow(8.0,fsynctics);
			if (keystatus[0xb5]) ghz /= pow(8.0,fsynctics);
			if (ghz < ((float)gdd.x*0.5)*1.25)
			{
				ghx = (float)gdd.x*0.5;
				ghy = (float)gdd.y*0.5;
				ghz = ghx*1.25;
			}
			else
			{
					//fsearchx = (x/z)*oghz + oghx = (x/z)*ghz + ghx
					//fsearchy = (y/z)*oghz + oghy = (y/z)*ghz + ghy
				t = ghz/oghz;
				ghx = fsearchx - (fsearchx-ghx)*t;
				ghy = fsearchy - (fsearchy-ghy)*t;
			}
			dmousz = 0;
		}

		{ //Must use this to get coordinates outside window
		POINT p0, p1;
		p0.x = 0; p0.y = 0; ClientToScreen(ghwnd,&p0);
		GetCursorPos(&p1);
		omousx = nmousx; nmousx = p1.x-p0.x;
		omousy = nmousy; nmousy = p1.y-p0.y;
		}
		if (((unsigned)nmousx < (unsigned)xres) && ((unsigned)nmousy < (unsigned)yres))
		{
			if ((bstatus&4) || ((keystatus[0x2a]|keystatus[0x36]) && (bstatus&2)))
			{
				ghx += nmousx-omousx;
				ghy += nmousy-omousy;
				SetCursor(ghhandcurs);
			}
			else SetCursor(ghcrosscurs);
		} else SetCursor(LoadCursor(0,IDC_ARROW));

		ftol(fsearchx,&searchx);
		ftol(fsearchy,&searchy);

		if ((bstatus&1) && (rotslice&0x80000000) && (!editmode) && (winstate <= 0))
		{
			searchstat = 1; drawscreen(); //This drawscreen is for mouse selection
			if (searchstat == 2)
			{
				searchstat = 0;
				if (ocgrabs == -2)
				{
					ocgrabx = cgrabx; ocgraby = cgraby; ocgrabz = cgrabz;
					ocgrabs = cgrabs; cgrabs = -1;
				}
				else if (cgrabs != ocgrabs)  //same cube dragging cases:
				{
					if (((ocgrabs == 2) && (cgrabs == 4)) ||
						 ((ocgrabs == 5) && (cgrabs == 2)) ||
						 ((ocgrabs == 3) && (cgrabs == 5)) ||
						 ((ocgrabs == 4) && (cgrabs == 3))) animrotate(0,ocgrabx,1,1);

					if (((ocgrabs == 4) && (cgrabs == 2)) ||
						 ((ocgrabs == 2) && (cgrabs == 5)) ||
						 ((ocgrabs == 5) && (cgrabs == 3)) ||
						 ((ocgrabs == 3) && (cgrabs == 4))) animrotate(0,ocgrabx,3,1);

					if (((ocgrabs == 5) && (cgrabs == 0)) ||
						 ((ocgrabs == 1) && (cgrabs == 5)) ||
						 ((ocgrabs == 4) && (cgrabs == 1)) ||
						 ((ocgrabs == 0) && (cgrabs == 4))) animrotate(1,ocgraby,1,1);

					if (((ocgrabs == 0) && (cgrabs == 5)) ||
						 ((ocgrabs == 5) && (cgrabs == 1)) ||
						 ((ocgrabs == 1) && (cgrabs == 4)) ||
						 ((ocgrabs == 4) && (cgrabs == 0))) animrotate(1,ocgraby,3,1);

					if (((ocgrabs == 0) && (cgrabs == 2)) ||
						 ((ocgrabs == 2) && (cgrabs == 1)) ||
						 ((ocgrabs == 1) && (cgrabs == 3)) ||
						 ((ocgrabs == 3) && (cgrabs == 0))) animrotate(2,ocgrabz,1,1);

					if (((ocgrabs == 2) && (cgrabs == 0)) ||
						 ((ocgrabs == 1) && (cgrabs == 2)) ||
						 ((ocgrabs == 3) && (cgrabs == 1)) ||
						 ((ocgrabs == 0) && (cgrabs == 3))) animrotate(2,ocgrabz,3,1);

					ocgrabs = -1; cgrabs = -1;
				}
				else if ((cgrabx != ocgrabx) + (cgraby != ocgraby) + (cgrabz != ocgrabz) >= 1)
				{
					switch(ocgrabs)
					{
						case 0:
							if (cgrabz > ocgrabz) { animrotate(1,ocgraby,3,1); break; }
							if (cgrabz < ocgrabz) { animrotate(1,ocgraby,1,1); break; }
							if (cgraby > ocgraby) { animrotate(2,ocgrabz,3,1); break; }
							if (cgraby < ocgraby) { animrotate(2,ocgrabz,1,1); break; }
							break;
						case 1:
							if (cgrabz > ocgrabz) { animrotate(1,ocgraby,1,1); break; }
							if (cgrabz < ocgrabz) { animrotate(1,ocgraby,3,1); break; }
							if (cgraby > ocgraby) { animrotate(2,ocgrabz,1,1); break; }
							if (cgraby < ocgraby) { animrotate(2,ocgrabz,3,1); break; }
							break;
						case 2:
							if (cgrabz > ocgrabz) { animrotate(0,ocgrabx,3,1); break; }
							if (cgrabz < ocgrabz) { animrotate(0,ocgrabx,1,1); break; }
							if (cgrabx > ocgrabx) { animrotate(2,ocgrabz,1,1); break; }
							if (cgrabx < ocgrabx) { animrotate(2,ocgrabz,3,1); break; }
							break;
						case 3:
							if (cgrabz > ocgrabz) { animrotate(0,ocgrabx,1,1); break; }
							if (cgrabz < ocgrabz) { animrotate(0,ocgrabx,3,1); break; }
							if (cgrabx > ocgrabx) { animrotate(2,ocgrabz,3,1); break; }
							if (cgrabx < ocgrabx) { animrotate(2,ocgrabz,1,1); break; }
							break;
						case 4:
							if (cgraby > ocgraby) { animrotate(0,ocgrabx,1,1); break; }
							if (cgraby < ocgraby) { animrotate(0,ocgrabx,3,1); break; }
							if (cgrabx > ocgrabx) { animrotate(1,ocgraby,1,1); break; }
							if (cgrabx < ocgrabx) { animrotate(1,ocgraby,3,1); break; }
							break;
						case 5:
							if (cgraby > ocgraby) { animrotate(0,ocgrabx,3,1); break; }
							if (cgraby < ocgraby) { animrotate(0,ocgrabx,1,1); break; }
							if (cgrabx > ocgrabx) { animrotate(1,ocgraby,3,1); break; }
							if (cgrabx < ocgrabx) { animrotate(1,ocgraby,1,1); break; }
							break;
					}

					ocgrabs = -1; cgrabs = -1;
				}
			}
			searchstat = 0;
		}
		else { ocgrabs = cgrabs = -2; }

		if (anglemode) { a2v = a3v = 0; }
		t = fsynctics*2;
		if (keystatus[0x2a]) t *= 0.5;
		if (keystatus[0x36]) t *= 2.0;
		a1v = 0;
		a2v += ((float)(keystatus[0xd0]-keystatus[0xc8]))*t;
		a3v += ((float)(keystatus[0xcd]-keystatus[0xcb]))*t;
		if ((bstatus&2) && (!(keystatus[0x2a]|keystatus[0x36])))
		{
			a2v += fmousy*.01;
			a3v += fmousx*.01;
		}
		fcossin(a1v,&cosa1,&sina1);
		fcossin(a2v,&cosa2,&sina2);
		fcossin(a3v,&cosa3,&sina3);
		c1c3 = cosa1*cosa3; c1s3 = cosa1*sina3;
		s1c3 = sina1*cosa3; s1s3 = sina1*sina3;
		if (!anglemode)  //Latitude/Longitude angle mode
		{
			i3.x = s1s3*sina2+c1c3; i3.y =-c1s3*sina2+s1c3; i3.z = sina3*cosa2;
			j3.x =-cosa2*sina1;     j3.y = cosa2*cosa1;     j3.z = sina2;
			k3.x = s1c3*sina2-c1s3; k3.y =-c1c3*sina2-s1s3; k3.z = cosa3*cosa2;
		}
		else   //Free direction angle mode (cube moves in direction of mouse)
		{
			rr[0] = s1s3*sina2+c1c3; rr[1] =-c1s3*sina2+s1c3; rr[2] = sina3*cosa2;
			rr[3] =-cosa2*sina1;     rr[4] = cosa2*cosa1;     rr[5] = sina2;
			rr[6] = s1c3*sina2-c1s3; rr[7] =-c1c3*sina2-s1s3; rr[8] = cosa3*cosa2;
			ox = i3.x; oy = i3.y; oz = i3.z;
			i3.x = ox*rr[0] + oy*rr[3] + oz*rr[6];
			i3.y = ox*rr[1] + oy*rr[4] + oz*rr[7];
			i3.z = ox*rr[2] + oy*rr[5] + oz*rr[8];
			ox = j3.x; oy = j3.y; oz = j3.z;
			j3.x = ox*rr[0] + oy*rr[3] + oz*rr[6];
			j3.y = ox*rr[1] + oy*rr[4] + oz*rr[7];
			j3.z = ox*rr[2] + oy*rr[5] + oz*rr[8];
			ox = k3.x; oy = k3.y; oz = k3.z;
			k3.x = ox*rr[0] + oy*rr[3] + oz*rr[6];
			k3.y = ox*rr[1] + oy*rr[4] + oz*rr[7];
			k3.z = ox*rr[2] + oy*rr[5] + oz*rr[8];
		}

		if (rotslice >= 0)
		{
			rotcnt += rotinc*fsynctics;
			rotang = (cos(rotcnt)+1)*rotmul;
			if (rotcnt > PI) rotslice |= 0x80000000;
			if (rotcnt < 0)
			{
				rotate(rotaxis,rotslice,rotnum);
				rotslice |= 0x80000000;
				checkwin(1);
			}
		}

		if (winstate > 0)
		{
			colwidth = ocolwidth;
			colwidth += (10-max(winstate-22,0))*.01;
			colwidth -= (10-min(winstate,10))*.01;
			i = (int)max(63-fabs((winstate*4)-64),0);
			winshade = ((float)i)/32.0 + 1.0;
			winstate -= fsynctics*50; if (winstate < 0) { i = 0; colwidth = ocolwidth; winstate = 0; }

			pal[7] = (((((255-((backcol>>16)&255))*i)>>6) + ((backcol>>16)&255))<<16)
					 + (((((255-((backcol>> 8)&255))*i)>>6) + ((backcol>> 8)&255))<< 8)
					 + (((((255-((backcol    )&255))*i)>>6) + ((backcol    )&255))<< 0);
			sticker_init();
		}
		else if (keystatus[0x1d]|keystatus[0x9d]) getcubeindex(); //hack for Ctrl..

		startdirectdraw((INT_PTR *)&gdd.f,(INT_PTR *)&dabpl,(INT_PTR *)&daxdim,(INT_PTR *)&daydim);

		if ((gdd.p != dabpl) || (gdd.x != daxdim) || (gdd.y != daydim))
		{
			gdd.p = dabpl;
			gdd.x = daxdim;
			gdd.y = daydim;

			ylookup[0] = 0; for(i=1;i<yres;i++) ylookup[i] = ylookup[i-1]+gdd.p;
			ghx = (float)gdd.x*0.5;
			ghy = (float)gdd.y*0.5;
			ghz = ghx*1.25;
			fsearchx = gdd.x*.5; fsearchy = gdd.y*.5;
			searchx = (gdd.x>>1); searchy = (gdd.y>>1);
		}
		drawrectfill(&gdd,0,0,gdd.x,gdd.y,pal[7]);

		//for(y=0;y<gdd.y;y++) clearbufbytesafe((void *)(ylookup[y]+gdd.f),gdd.p,pal[7]);
		if (showothercubemode)
		{
			float oghx, oghy, oghz;

			oghx = ghx; ghx = ((float)gdd.x)*.1500;
			oghy = ghy; ghy = ((float)gdd.y)*.1875;
			oghz = ghz; ghz = ((float)gdd.x)*.25;
			drawcubefacecol = ocubefacecol;
			j = rotslice; rotslice |= 0x80000000;
			drawscreen();

			ghx = oghx;
			ghy = oghy;
			ghz = oghz;
			drawcubefacecol = cubefacecol;
			rotslice = j;
		}

		if (winstate > 0)
		{
			i3b = i3; j3b = j3; k3b = k3;
			fcossin(0.f,&cosa1,&sina1);
			fcossin(0.f,&cosa2,&sina2);
			t = ((float)winstate)*PI*2/32.0;
			fcossin((1-cos(t*.5))*PI,&cosa3,&sina3);
			c1c3 = cosa1*cosa3; c1s3 = cosa1*sina3;
			s1c3 = sina1*cosa3; s1s3 = sina1*sina3;
			rr[0] = s1s3*sina2+c1c3; rr[1] =-c1s3*sina2+s1c3; rr[2] = sina3*cosa2;
			rr[3] =-cosa2*sina1;     rr[4] = cosa2*cosa1;     rr[5] = sina2;
			rr[6] = s1c3*sina2-c1s3; rr[7] =-c1c3*sina2-s1s3; rr[8] = cosa3*cosa2;
			ox = i3.x; oy = i3.y; oz = i3.z;
			i3.x = ox*rr[0] + oy*rr[3] + oz*rr[6];
			i3.y = ox*rr[1] + oy*rr[4] + oz*rr[7];
			i3.z = ox*rr[2] + oy*rr[5] + oz*rr[8];
			ox = j3.x; oy = j3.y; oz = j3.z;
			j3.x = ox*rr[0] + oy*rr[3] + oz*rr[6];
			j3.y = ox*rr[1] + oy*rr[4] + oz*rr[7];
			j3.z = ox*rr[2] + oy*rr[5] + oz*rr[8];
			ox = k3.x; oy = k3.y; oz = k3.z;
			k3.x = ox*rr[0] + oy*rr[3] + oz*rr[6];
			k3.y = ox*rr[1] + oy*rr[4] + oz*rr[7];
			k3.z = ox*rr[2] + oy*rr[5] + oz*rr[8];
		}
		drawscreen();
		if (winstate > 0) { i3 = i3b; j3 = j3b; k3 = k3b; }


		if (editmode)
		{
			float ax[3];

			ax[0] = -(c3.x*i3.x + c3.y*i3.y + c3.z*i3.z) / (i3.x*i3.x + i3.y*i3.y + i3.z*i3.z) + (float)cdim*.5;
			ax[1] = -(c3.x*j3.x + c3.y*j3.y + c3.z*j3.z) / (j3.x*j3.x + j3.y*j3.y + j3.z*j3.z) + (float)cdim*.5;
			ax[2] = -(c3.x*k3.x + c3.y*k3.y + c3.z*k3.z) / (k3.x*k3.x + k3.y*k3.y + k3.z*k3.z) + (float)cdim*.5;

			for(i=0;i<6;i++)
			{
				vertyp vt[4];
				tiletype tt;
				__int64 q;
				tt.f = (int)&stickertex[i][0][0];
				tt.x = tt.y = STICKERSIZ; tt.p = (tt.x<<2);
				vt[0].x = gdd.x+(-1)*64-ghx; vt[0].y = (gdd.y>>1)+(i-3)*64-ghy; vt[0].z = ghz; vt[0].u = 0; vt[0].v = 0;
				vt[1].x = gdd.x+( 0)*64-ghx; vt[1].y = (gdd.y>>1)+(i-3)*64-ghy; vt[1].z = ghz; vt[1].u = 1; vt[1].v = 0;
				vt[2].x = gdd.x+( 0)*64-ghx; vt[2].y = (gdd.y>>1)+(i-2)*64-ghy; vt[2].z = ghz; vt[2].u = 1; vt[2].v = 1;
				vt[3].x = gdd.x+(-1)*64-ghx; vt[3].y = (gdd.y>>1)+(i-2)*64-ghy; vt[3].z = ghz; vt[3].u = 0; vt[3].v = 1;
				if (curcolindex == i+1) q = ((__int64)(sin(((double)ltotclk)*.02)*64+256))*0x100010001I64; else q = 0x010001000100I64;
				if (cputype&(1<<25)) { drawpolyquad(&tt,vt,q); } //Have SSE
				else
				{
					k = ((gdd.y>>1)+(i-3)*64)*gdd.p + (gdd.x-64)*4 + gdd.f;
					l = (q&511)-64;
					for(y=0;y<64;y++,k+=gdd.p)
						for(x=0;x<64;x++)
						{
							j = *(int *)(((y*STICKERSIZ)>>6)*tt.p + (((x*STICKERSIZ)>>6)<<2) + tt.f);
							*(int *)(k+(x<<2)) = ((((j&0xff00ff)*l)&0xff00ff00) + (((j&0xff00)*l)&0xff0000)>>8);
						}
				}

				drawtext(0,gdd.x-32-(fontlist[0].xs>>1),(gdd.y>>1)+(i-3)*64+32-(fontlist[0].ys>>1),pal[0],-1,"%d",i+1);

					//Display the face letter (L,R,U,D,F,B) over the center of each side
				t = ((float)cdim)*.5; ox = oy = oz = 0.f;
				tbuf[0] = notation3[i]; tbuf[1] = 0; j = 1;
				switch(i)
				{
					case 0: ox =-t; if (ax[0] >=   0) j = 0; break;
					case 1: ox =+t; if (ax[0] < cdim) j = 0; break;
					case 2: oy =-t; if (ax[1] >=   0) j = 0; break;
					case 3: oy =+t; if (ax[1] < cdim) j = 0; break;
					case 4: oz =-t; if (ax[2] >=   0) j = 0; break;
					case 5: oz =+t; if (ax[2] < cdim) j = 0; break;
				}
				if (!j) continue;
				t = ghz / (i3.z*ox + j3.z*oy + k3.z*oz + c3.z);
				x = (int)((i3.x*ox + j3.x*oy + k3.x*oz + c3.x)*t + ghx);
				y = (int)((i3.y*ox + j3.y*oy + k3.y*oz + c3.y)*t + ghy);
				drawtext(0,x-((fontlist[0].xs*strlen(tbuf))>>1),y-(fontlist[0].ys>>1),pal[0],-1,"%s",tbuf);
			}
		}

			//display timer
		if (timermode >= 0)
		{
			i = 0;
			switch(timermode)
			{
				case 0: i = 0; break;
				case 1: i = ltotclk-startimer; break;
				case 2: i = stoptimer-startimer; break;
			}
			i /= 10;

			tbuf[0] = 0;
			if (i >= 100*60*60*24) sprintf(&tbuf[strlen(tbuf)],"%dd, ",i/(100*60*60*24));
			if (i >= 100*60*60   ) sprintf(&tbuf[strlen(tbuf)],"%02d:",(i/(100*60*60))%24);
										  sprintf(&tbuf[strlen(tbuf)],"%02d:%02d.%02d",(i/(100*60))%60,(i/100)%60,i%100);

			drawtext(0,gdd.x-fontlist[0].xs*strlen(tbuf),fontlist[0].ys,0xe0e0e0,-1,"%s",tbuf);
		}

		if (ltotclk < messagetimeout) drawtext(0,((signed)(gdd.x-fontlist[0].xs*strlen(message)))>>1,0,0xe0e0e0,-1,"%s",message);

		//if (rotsavcur > 0)
		//{
		//   sprintf(tbuf,"%d move%c",rotsavcur,(-(rotsavcur!=1))&'s');
		//   drawtext(0,((signed)(gdd.x-fontlist[0].xs*strlen(tbuf)))>>1,gdd.y-15,pal[8],-1,"%s",tbuf);
		//}
		if (rotsavbeg < rotsavend)
		{
			for(x=32;x<=gdd.x-32;x++) drawpix(x,gdd.y-32,0x808080);

				  if (rotsavend >= 100000) i = 8*6+4;
			else if (rotsavend >=  10000) i = 8*5+4;
			else if (rotsavend >=   1000) i = 8*4+4;
			else if (rotsavend >=    100) i = 8*3+4;
			else if (rotsavend >=     10) i = 8*2+4;
			else                          i = 8*1+4;
			i *= (rotsavend-rotsavbeg); j = gdd.x-32*2; k = 1; l = 1;
			if (i <= j*50000) { k = 50000; l = 10000; }
			if (i <= j*20000) { k = 20000; l = 5000;  }
			if (i <= j*10000) { k = 10000; l = 2000;  }
			if (i <= j*5000 ) { k = 5000;  l = 1000;  }
			if (i <= j*2000 ) { k = 2000;  l = 500;   }
			if (i <= j*1000 ) { k = 1000;  l = 200;   }
			if (i <= j*500  ) { k = 500;   l = 100;   }
			if (i <= j*200  ) { k = 200;   l = 50;    }
			if (i <= j*100  ) { k = 100;   l = 20;    }
			if (i <= j*50   ) { k = 50;    l = 10;    }
			if (i <= j*20   ) { k = 20;    l = 5;     }
			if (i <= j*10   ) { k = 10;    l = 2;     }
			if (i <= j*5    ) { k = 5;     l = 1;     }
			if (i <= j*2    ) { k = 2;     l = 1;     }
			if (i <= j*1    ) { k = 1;     l = 1;     }

			for(i=((rotsavbeg+l-1)/l)*l;i<=rotsavend;i+=l)
			{
				x = (i-rotsavbeg)*(gdd.x-32*2)/(rotsavend-rotsavbeg);
				for(y=gdd.y-36,j=gdd.y-32;y<j;y++) drawpix(x+32,y,0x808080);
			}
			for(i=((rotsavbeg+k-1)/k)*k;i<=rotsavend;i+=k)
			{
				x = (i-rotsavbeg)*(gdd.x-32*2)/(rotsavend-rotsavbeg);
				for(y=gdd.y-32,j=gdd.y-28;y<j;y++) drawpix(x+32,y,0x808080);
				sprintf(tbuf,"%d",i-rotsavbeg);
				drawtext(0,x-(strlen(tbuf)<<2)+32,gdd.y-28,0x808080,-1,"%s",tbuf);
			}

			if ((showothercubemode) && (orotsavcur < rotsavend))
			{
				if (ltotclk&64) ch = 0xe0e0e0; else ch = 0x808080;
				x = (orotsavcur-rotsavbeg)*(gdd.x-32*2)/(rotsavend-rotsavbeg);
				for(j=x-2;j<=x+2;j++)
					for(y=gdd.y-40+labs(j-x);y<=gdd.y-32;y++) drawpix(j+32,y,0xe0e0e0);
				sprintf(tbuf,"%d",orotsavcur);
				drawtext(0,x-(strlen(tbuf)<<2)+32,gdd.y-28,ch,-1,"%s",tbuf);
			}

			x = (rotsavcur-rotsavbeg)*(gdd.x-32*2)/(rotsavend-rotsavbeg);
			for(j=x-2;j<=x+2;j++)
				for(y=gdd.y-40+labs(j-x);y<=gdd.y-32;y++) drawpix(j+32,y,0xe0e0e0);
			sprintf(tbuf,"%d",rotsavcur);
			drawtext(0,x-(strlen(tbuf)<<2)+32,gdd.y-28,0xe0e0e0,-1,"%s",tbuf);
		}
		if (((~obstatus)|grabbedbar)&bstatus&1)
		{
			if ((fsearchy >= gdd.y-40) && (gdd.x > 64))
			{
				grabbedbar = 1;
				ftol((fsearchx-32)*(rotsavend-rotsavbeg)/(gdd.x-32*2)-.5,&j);
				j = min(max(j+rotsavbeg,rotsavbeg),rotsavend);
				while (rotsavcur > j) { i = rotsav[(--rotsavcur)&(ROTSAVSIZ-1)]; animrotate((i>>2)&3,i>>4,(-i)&3,0); }
				while (rotsavcur < j) { i = rotsav[(rotsavcur++)&(ROTSAVSIZ-1)]; animrotate((i>>2)&3,i>>4,  i &3,0); }
			}
		} else grabbedbar = 0;
		if ((editmode) && (bstatus&1))
		{
			if (fsearchx >= gdd.x-64)
			{
				i = ((((int)fsearchy)-((gdd.y>>1)-64*3))>>6); //Clicked palette?
				if ((unsigned)i < (unsigned)6) curcolindex = i+1; else i = -1;
			} else i = -1;
			if (i < 0)
			{
				i = getcubeindex();
				if (i >= 0)
				{
					j = cubefacecol[i];
					cubefacecol[i] = curcolindex;
					if (cubefacecol[i] != j)
					{
						editpatches[(editpatchcnt&(EDITPATCHMAX-1))] = ((cubefacecol[i]-1)*6+(j-1))*(6*MAXCDIM*MAXCDIM) + i;
						editpatchcnt++;
						editpatchbeg = max(editpatchbeg,editpatchcnt-EDITPATCHMAX);
						editpatchend = editpatchcnt;
					}
				}
			}
		}

		if (doscrcap)
		{
			char filename[16];
			FILE *fil;

			doscrcap = 0;
			for(i=100;i;i--)
			{
				sprintf(filename,"RUBX%04d.PNG",capturecount);
				fil = fopen(filename,"rb"); if (!fil) break;
				fclose(fil); capturecount++;
			}
			if (!i) fclose(fil);
			else
			{
				screencapture(filename,gdd.f,daxdim,daydim,dabpl);
				capturecount++;
				sprintf(message,"Screen captured to %s",filename);
				messagetimeout = ltotclk+2000;
			}
		}

		stopdirectdraw();
		nextpage();

		if ((editmode) && ((bstatus&2) > (obstatus&2)))
		{
			if (fsearchx >= gdd.x-64)
			{
				i = ((((int)fsearchy)-((gdd.y>>1)-64*3))>>6); //Clicked palette?
				if ((unsigned)i < (unsigned)6) curcolindex = i+1; else i = -1;
			} else i = -1;
			if (i >= 0)
			{
				j = pal[i+1];
				if (selectcolor(&j))
				{
					pal[i+1] = j;
					sticker_init();
				}
			}
		}

		obstatus = bstatus;
		MsgWaitForMultipleObjects(0,0,0,15,QS_KEY|QS_MOUSE|QS_PAINT);
	}

	mymenuuninit();
	if (ghhandcurs)  { DestroyCursor(ghhandcurs);  ghhandcurs = 0;  }
	if (ghcrosscurs) { DestroyCursor(ghcrosscurs); ghcrosscurs = 0; }

	uninitapp();
}

#if 0
!endif
#endif
