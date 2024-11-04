#include <stdio.h>
#include <windows.h>

// Copyright by Ben Jos Walbeehm. Written March-April 2007. Slight improvements made on 20-May-2010. Many infrequent improvements made during March-May 2012.
// Licence: This code may be used for non-commercial purposes as long as the author (Ben Jos Walbeehm) is clearly credited.

// Note that we use Dutch notation for the cube faces:
//   Dutch  English
//     R       R
//     B       U
//     V       F
//     L       L
//     O       D
//     A       B

// This is NOT a standalone 4x4x4 cube solver. It just contains some functions that my generic NxNxN cube solver can use to solve a 4x4x4 cube more efficiently.
// See also the definition of USE4X4X4CODE in bjwsolve.c.

// RotationCode: (slice{0..3} << 4) + (axis{0..2} << 2) + numtimes{1..3}.

static const DWORD FaceL = 0;
static const DWORD FaceR = 1;
static const DWORD FaceB = 2;
static const DWORD FaceO = 3;
static const DWORD FaceV = 4;
static const DWORD FaceA = 5;

static const DWORD AxisL = 0;
static const DWORD AxisO = 1;
static const DWORD AxisV = 2;

static const BYTE RotateNothing = 0;
static const BYTE RotateCentres = 1;
static const BYTE RotateAll     = 2;

static DWORD SitCount;

static DWORD MaxDim;
static BYTE *CubeFaceColours;
static BYTE *SavedCubeFaceColours;
static BYTE  CubeFaceColours4[6*4*4];
static BYTE  SavedCubeFaceColours4[6*4*4];
static WORD *SolutionPtr,Solution[1024];

static BYTE *ASNptr,*SavedASNptr,ASN[3*256],SavedASN[3*256]; // "Axis-Slice-Numtimes".

static char *VOAB[4] = {"V","O","A","B"};
static char *EdgeFormulas1Through8[48] =
{ "O'L O ","B L'B'","A'L2A ","A L2A'","B'L'B ","O L O'",  // LV.
  "A'L A ","V L'V'","B'L2B ","B L2B'","V'L'V ","A L A'",  // LO.
  "B'L B ","O L'O'","V'L2V ","V L2V'","O'L'O ","B L B'",  // LA.
  "V'L V ","A L'A'","O'L2O ","O L2O'","A'L'A ","V L V'",  // LB.
  "O R'O'","B'R B ","A R2A'","A'R2A ","B R B'","O'R'O ",  // RV.
  "A R'A'","V'R V ","B R2B'","B'R2B ","V R V'","A'R'A ",  // RO.
  "B R'B'","O'R O ","V R2V'","V'R2V ","O R O'","B'R'B ",  // RA.
  "V R'V'","A'R A ","O R2O'","O'R2O ","A R A'","V'R'V "   // RB.
};

// For solving the O face centre pieces in the minimal possible amount of turns.
static DWORD OFaceCounts[6] = {1,13,186,2072,8826,10626};
static BYTE  OFaceSolutions[10626];
static WORD  SeqSitLookup[24*24*24*24]; // 663,552 bytes. Returns a value in the range 0..10,625.
static DWORD SeqSitRev[10626]; // Reverse lookup for the above.
static BYTE  Lengths[10626];

/********************************************************/
static __forceinline BYTE GetColour (DWORD face, DWORD x, DWORD y)
{ return CubeFaceColours[(face * MaxDim + x) * MaxDim + y];
} // GetColour

/********************************************************/
static __forceinline BYTE GetColour4 (DWORD face, DWORD x, DWORD y)
{ return CubeFaceColours4[(((face << 2) + x) << 2) + y];
} // GetColour4

/********************************************************/
static __forceinline void SetColour4 (DWORD face, DWORD x, DWORD y, BYTE colour)
{ CubeFaceColours4[(((face << 2) + x) << 2) + y] = colour;
} // SetColour4

/********************************************************/
static void Extract4x4x4Cube ()
{ DWORD face,x,y;

  for (face = 0; face < 6; face++) for (y = 0; y < 4; y++) for (x = 0; x < 4; x++) SetColour4(face,x,y,GetColour(face,x,y));
} // Extract4x4x4Cube

/********************************************************/
// Taken from Ken Silverman's rubix.c. Adapted to my needs and somewhat optimised for the 4x4x4.
#define rotate1(c1,c2,c3,c4) { BYTE c0 = c1; c1 = c2; c2 = c3; c3 = c4; c4 = c0; }
#define rotate2(c1,c2,c3,c4) { BYTE c0 = c1; c1 = c3; c3 = c0; c0 = c2; c2 = c4; c4 = c0; }
#define rotate3(c1,c2,c3,c4) { BYTE c0 = c4; c4 = c3; c3 = c2; c2 = c1; c1 = c0; }

static void Rotate (long axis, long slice, long numtimes, BYTE rotatemode)
{ BYTE *c;

  switch (numtimes & 3)
  { case 1:
      switch (axis)
      { case 0:
          c = &CubeFaceColours4[slice<<2];
          rotate1(c[(2<<4)+2],c[(5<<4)+2],c[(3<<4)+1],c[(4<<4)+1]);
          rotate1(c[(2<<4)+1],c[(5<<4)+1],c[(3<<4)+2],c[(4<<4)+2]);
          if (rotatemode == RotateAll)
          { rotate1(c[(2<<4)+3],c[(5<<4)+3],c[(3<<4)+0],c[(4<<4)+0]);
            rotate1(c[(2<<4)+0],c[(5<<4)+0],c[(3<<4)+3],c[(4<<4)+3]);
          }
          break;
        case 1:
          rotate1(CubeFaceColours4[(((0<<2)+slice)<<2)+2],CubeFaceColours4[(((5<<2)+2)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+1],CubeFaceColours4[(((4<<2)+1)<<2)+slice]);
          rotate1(CubeFaceColours4[(((0<<2)+slice)<<2)+1],CubeFaceColours4[(((5<<2)+1)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+2],CubeFaceColours4[(((4<<2)+2)<<2)+slice]);
          if (rotatemode == RotateAll)
          { rotate1(CubeFaceColours4[(((0<<2)+slice)<<2)+3],CubeFaceColours4[(((5<<2)+3)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+0],CubeFaceColours4[(((4<<2)+0)<<2)+slice]);
            rotate1(CubeFaceColours4[(((0<<2)+slice)<<2)+0],CubeFaceColours4[(((5<<2)+0)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+3],CubeFaceColours4[(((4<<2)+3)<<2)+slice]);
          }
          break;
        case 2:
          c = &CubeFaceColours4[slice];
          rotate1(c[(0<<4)+ 8],c[(3<<4)+ 8],c[(1<<4)+ 4],c[(2<<4)+ 4]);
          rotate1(c[(0<<4)+ 4],c[(3<<4)+ 4],c[(1<<4)+ 8],c[(2<<4)+ 8]);
          if (rotatemode == RotateAll)
          { rotate1(c[(0<<4)+12],c[(3<<4)+12],c[(1<<4)+ 0],c[(2<<4)+ 0]);
            rotate1(c[(0<<4)+ 0],c[(3<<4)+ 0],c[(1<<4)+12],c[(2<<4)+12]);
          }
          break;
      }
      if ((DWORD)(slice-1) >= (DWORD)(3-1))
      { c = &CubeFaceColours4[((slice!=0)+(axis<<1))<<4];
        rotate1(c[(1<<2)+2],c[(2<<2)+2],c[(2<<2)+1],c[(1<<2)+1]);
        if (rotatemode == RotateAll)
        { rotate1(c[(1<<2)+3],c[(3<<2)+2],c[(2<<2)+0],c[(0<<2)+1]);
          rotate1(c[(0<<2)+2],c[(2<<2)+3],c[(3<<2)+1],c[(1<<2)+0]);
          rotate1(c[(0<<2)+3],c[(3<<2)+3],c[(3<<2)+0],c[(0<<2)+0]);
        }
      }
      break;
    case 2:
      switch (axis)
      { case 0:
          c = &CubeFaceColours4[slice<<2];
          rotate2(c[(2<<4)+2],c[(5<<4)+2],c[(3<<4)+1],c[(4<<4)+1]);
          rotate2(c[(2<<4)+1],c[(5<<4)+1],c[(3<<4)+2],c[(4<<4)+2]);
          if (rotatemode == RotateAll)
          { rotate2(c[(2<<4)+3],c[(5<<4)+3],c[(3<<4)+0],c[(4<<4)+0]);
            rotate2(c[(2<<4)+0],c[(5<<4)+0],c[(3<<4)+3],c[(4<<4)+3]);
          }
          break;
        case 1:
          rotate2(CubeFaceColours4[(((0<<2)+slice)<<2)+2],CubeFaceColours4[(((5<<2)+2)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+1],CubeFaceColours4[(((4<<2)+1)<<2)+slice]);
          rotate2(CubeFaceColours4[(((0<<2)+slice)<<2)+1],CubeFaceColours4[(((5<<2)+1)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+2],CubeFaceColours4[(((4<<2)+2)<<2)+slice]);
          if (rotatemode == RotateAll)
          { rotate2(CubeFaceColours4[(((0<<2)+slice)<<2)+3],CubeFaceColours4[(((5<<2)+3)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+0],CubeFaceColours4[(((4<<2)+0)<<2)+slice]);
            rotate2(CubeFaceColours4[(((0<<2)+slice)<<2)+0],CubeFaceColours4[(((5<<2)+0)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+3],CubeFaceColours4[(((4<<2)+3)<<2)+slice]);
          }
          break;
        case 2:
          c = &CubeFaceColours4[slice];
          rotate2(c[(0<<4)+ 8],c[(3<<4)+ 8],c[(1<<4)+ 4],c[(2<<4)+ 4]);
          rotate2(c[(0<<4)+ 4],c[(3<<4)+ 4],c[(1<<4)+ 8],c[(2<<4)+ 8]);
          if (rotatemode == RotateAll)
          { rotate2(c[(0<<4)+12],c[(3<<4)+12],c[(1<<4)+ 0],c[(2<<4)+ 0]);
            rotate2(c[(0<<4)+ 0],c[(3<<4)+ 0],c[(1<<4)+12],c[(2<<4)+12]);
          }
          break;
      }
      if ((DWORD)(slice-1) >= (DWORD)(3-1))
      { c = &CubeFaceColours4[((slice!=0)+(axis<<1))<<4];
        rotate2(c[(1<<2)+2],c[(2<<2)+2],c[(2<<2)+1],c[(1<<2)+1]);
        if (rotatemode == RotateAll)
        { rotate2(c[(1<<2)+3],c[(3<<2)+2],c[(2<<2)+0],c[(0<<2)+1]);
          rotate2(c[(0<<2)+2],c[(2<<2)+3],c[(3<<2)+1],c[(1<<2)+0]);
          rotate2(c[(0<<2)+3],c[(3<<2)+3],c[(3<<2)+0],c[(0<<2)+0]);
        }
      }
      break;
    case 3:
      switch (axis)
      { case 0:
          c = &CubeFaceColours4[slice<<2];
          rotate3(c[(2<<4)+2],c[(5<<4)+2],c[(3<<4)+1],c[(4<<4)+1]);
          rotate3(c[(2<<4)+1],c[(5<<4)+1],c[(3<<4)+2],c[(4<<4)+2]);
          if (rotatemode == RotateAll)
          { rotate3(c[(2<<4)+3],c[(5<<4)+3],c[(3<<4)+0],c[(4<<4)+0]);
            rotate3(c[(2<<4)+0],c[(5<<4)+0],c[(3<<4)+3],c[(4<<4)+3]);
          }
          break;
        case 1:
          rotate3(CubeFaceColours4[(((0<<2)+slice)<<2)+2],CubeFaceColours4[(((5<<2)+2)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+1],CubeFaceColours4[(((4<<2)+1)<<2)+slice]);
          rotate3(CubeFaceColours4[(((0<<2)+slice)<<2)+1],CubeFaceColours4[(((5<<2)+1)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+2],CubeFaceColours4[(((4<<2)+2)<<2)+slice]);
          if (rotatemode == RotateAll)
          { rotate3(CubeFaceColours4[(((0<<2)+slice)<<2)+3],CubeFaceColours4[(((5<<2)+3)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+0],CubeFaceColours4[(((4<<2)+0)<<2)+slice]);
            rotate3(CubeFaceColours4[(((0<<2)+slice)<<2)+0],CubeFaceColours4[(((5<<2)+0)<<2)+slice],CubeFaceColours4[(((1<<2)+slice)<<2)+3],CubeFaceColours4[(((4<<2)+3)<<2)+slice]);
          }
          break;
        case 2:
          c = &CubeFaceColours4[slice];
          rotate3(c[(0<<4)+ 8],c[(3<<4)+ 8],c[(1<<4)+ 4],c[(2<<4)+ 4]);
          rotate3(c[(0<<4)+ 4],c[(3<<4)+ 4],c[(1<<4)+ 8],c[(2<<4)+ 8]);
          if (rotatemode == RotateAll)
          { rotate3(c[(0<<4)+12],c[(3<<4)+12],c[(1<<4)+ 0],c[(2<<4)+ 0]);
            rotate3(c[(0<<4)+ 0],c[(3<<4)+ 0],c[(1<<4)+12],c[(2<<4)+12]);
          }
          break;
      }
      if ((DWORD)(slice-1) >= (DWORD)(3-1))
      { c = &CubeFaceColours4[((slice!=0)+(axis<<1))<<4];
        rotate3(c[(1<<2)+2],c[(2<<2)+2],c[(2<<2)+1],c[(1<<2)+1]);
        if (rotatemode == RotateAll)
        { rotate3(c[(1<<2)+3],c[(3<<2)+2],c[(2<<2)+0],c[(0<<2)+1]);
          rotate3(c[(0<<2)+2],c[(2<<2)+3],c[(3<<2)+1],c[(1<<2)+0]);
          rotate3(c[(0<<2)+3],c[(3<<2)+3],c[(3<<2)+0],c[(0<<2)+0]);
        }
      }
      break;
  }
} // Rotate

// End of "Taken from Ken Silverman's rubix.c".

/********************************************************/
static void StoreTurn (BYTE axis, BYTE slice, BYTE numtimes, BYTE rotatemode)
{ if (rotatemode != RotateNothing) Rotate(axis,(axis == AxisO) ? slice^3 : slice,numtimes,rotatemode);
  // Before storing the turn, see if we can combine it with the last turn.
  if (ASNptr > ASN)
  { if ((ASNptr[-3] == axis) && (ASNptr[-2] == slice))
    { numtimes = (numtimes + ASNptr[-1]) & 3;
      ASNptr -= 3;
    }
  }
  if (numtimes)
  { ASNptr[0] = axis;
    ASNptr[1] = slice;
    ASNptr[2] = numtimes;
    ASNptr += 3;
  }
} // StoreTurn

/********************************************************/
static DWORD StoreFormula (char *fptr, BYTE rotatemode)
{ BYTE axis,slice,numtimes,*asnptr;

  asnptr = ASNptr;
  while (*fptr)
  { switch (*fptr++)
    { case 'L': axis = (BYTE)AxisL; slice = 0; break;
      case 'l': axis = (BYTE)AxisL; slice = 1; break;
      case 'r': axis = (BYTE)AxisL; slice = 2; break;
      case 'R': axis = (BYTE)AxisL; slice = 3; break;
      case 'O': axis = (BYTE)AxisO; slice = 0; break;
      case 'o': axis = (BYTE)AxisO; slice = 1; break;
      case 'b': axis = (BYTE)AxisO; slice = 2; break;
      case 'B': axis = (BYTE)AxisO; slice = 3; break;
      case 'V': axis = (BYTE)AxisV; slice = 0; break;
      case 'v': axis = (BYTE)AxisV; slice = 1; break;
      case 'a': axis = (BYTE)AxisV; slice = 2; break;
      case 'A': axis = (BYTE)AxisV; slice = 3; break;
    }
    switch (*fptr++)
    { case '0' : numtimes = 0; break;
      case '\0': fptr--; // Fall through. This is so that we can write "R B" instead of "R B ".
      case '1' : // Fall through.
      case ' ' : numtimes = 1; break;
      case '2' : numtimes = 2; break;
      case '3' : // Fall through.
      case '\'': numtimes = 3; break;
    }
    if (numtimes == 0) continue;
    if (slice >= 2) numtimes = 4-numtimes;
    StoreTurn(axis,slice,numtimes,rotatemode);
  }
  return (ASNptr-asnptr)/3;
} // StoreFormula

/********************************************************/
static void DoTurn (DWORD axis, DWORD slice, DWORD numtimes)
{ StoreTurn((BYTE)axis,(BYTE)slice,(BYTE)numtimes,RotateAll);
} // DoTurn

/********************************************************/
static void DoFormula (char *fptr)
{ StoreFormula(fptr,RotateAll);
} // DoFormula

/********************************************************/
static __forceinline BOOL Unstriped ()
{ return (GetColour4(FaceV,1,1) == GetColour4(FaceV,2,1));
} // Unstriped

/********************************************************/
static __forceinline void Unstripe ()
{ while (!Unstriped()) DoTurn(AxisL,1,1);
} // Unstripe

/********************************************************/
static void CheckSituation (DWORD axis, DWORD slice, DWORD numtimes, DWORD len)
{ DWORD i,sitnum;

  for (i = sitnum = 0; i < 6; i++)
  { if (GetColour4(i,1,1) == 1) sitnum = sitnum*24 + i*4;
    if (GetColour4(i,1,2) == 1) sitnum = sitnum*24 + i*4+1;
    if (GetColour4(i,2,1) == 1) sitnum = sitnum*24 + i*4+2;
    if (GetColour4(i,2,2) == 1) sitnum = sitnum*24 + i*4+3;
  }
  if (OFaceSolutions[sitnum=SeqSitLookup[sitnum]] != 0xff) return;  // We already have a solution for this situation.
  SitCount++;
  if (axis == AxisO) slice ^= 3;
  numtimes = -(long)numtimes & 3;
  OFaceSolutions[sitnum] = (BYTE)((slice << 4) + (axis << 2) + numtimes);
  Lengths[sitnum] = (BYTE)len;
} // CheckSituation

/********************************************************/
void BJW4Initialise (int mem_n, char *facelist, BYTE **asnptr)
{ BYTE b;
  DWORD i,j,k,m,len,lastaxis,lastslice,axis,slice,sit,seqsitnum;

  static BOOL initialised = FALSE;

  if (initialised) return;

  MaxDim = (DWORD)mem_n;
  CubeFaceColours = (BYTE *)facelist;
  SavedCubeFaceColours = NULL;
  *asnptr = ASN;
  // Initialise SeqSitLookup[] and SeqSitRev[].
  for (i = seqsitnum = 0; i < 21; i++) for (j = i+1; j < 22; j++) for (k = j+1; k < 23; k++) for (m = k+1; m < 24; m++)
  { SeqSitLookup[SeqSitRev[seqsitnum] = ((i*24+j)*24+k)*24+m] = (WORD)seqsitnum++; }
  // Generate all solutions for the centres of the O face. We paint those centres 1 ("white") and the rest of the cube 0 ("black").
  SitCount = 0;
  memset(Lengths,0xff,sizeof(Lengths));
  memset(OFaceSolutions,0xff,sizeof(OFaceSolutions));
  memset(CubeFaceColours4,0,sizeof(CubeFaceColours4));
  CubeFaceColours4[53] = CubeFaceColours4[54] = CubeFaceColours4[57] = CubeFaceColours4[58] = 1;
  // We now have the identity; process it.
  CheckSituation(3,0,3,0);
  // Now repeatedly take solutions that were solved in one turn less and try one turn to see if it results in a situation we do not have yet encountered.
  for (len = 1; len < 6; len++)
  { for (i = 0; i < sizeof(OFaceSolutions); i++)
    { if (Lengths[i] != len-1) continue;
      b = OFaceSolutions[i];
      lastslice = b >> 4;
      lastaxis = (b >> 2) & 3;
      if (lastaxis == AxisO) lastslice ^= 3; // lastslice = 3-lastslice;
      // Create the situation.
      memset(CubeFaceColours4,0,sizeof(CubeFaceColours4));
      k = SeqSitRev[i];
      for (j = 0; j < 4; j++)
      { sit = k % 24;
        k /= 24;
        SetColour4(sit >> 2,((sit >> 1) & 1) + 1,(sit & 1) + 1,1);
      }
      // Try a bunch of single turns.
      for (axis = 0; axis < 3; axis++) for (slice = 0; slice < 4; slice++) if ((axis != lastaxis) || (slice > lastslice))
      { Rotate(axis,slice,1,RotateCentres);
        CheckSituation(axis,slice,1,len);
        Rotate(axis,slice,1,RotateCentres);
        CheckSituation(axis,slice,2,len);
        Rotate(axis,slice,1,RotateCentres);
        CheckSituation(axis,slice,3,len);
        Rotate(axis,slice,1,RotateCentres);  // To restore the original situation.
      }
      if (SitCount == OFaceCounts[len]) break; // Early-out.
    }
  }

  initialised = TRUE;
} // BJW4Initialise

/********************************************************/
DWORD BJW4SolveOFace (BYTE thecolour)
{ DWORD i,code;
  BYTE axis,slice,numtimes;

  ASNptr = ASN;
  Extract4x4x4Cube();
  do
  { for (i = code = 0; i < 24; i++) if (GetColour4(i >> 2,((i >> 1) & 1) + 1,(i & 1) + 1) == thecolour) code = code*24 + i;
    code = OFaceSolutions[SeqSitLookup[code]];
    if ((axis = (BYTE)(code >> 2) & 3) == 3) return (ASNptr-ASN)/3;
    slice = (BYTE)(code >> 4);
    numtimes = (BYTE)(code & 3);
    StoreTurn(axis,slice,numtimes,RotateCentres);
  } while (TRUE);

  // This point is never reached.

} // BJW4SolveOFace

/********************************************************/
static void RemoveUndesiredEndTurns (DWORD axis, DWORD slice)
{ // (DWORD)(-1) removes all slices of the specified axis.

  if ((slice != (DWORD)(-1)) && (axis == AxisO)) slice ^= 3;
  while (ASNptr > ASN)
  { if ((ASNptr[-3] != axis) || ((ASNptr[-2] != slice) && (slice != (DWORD)(-1)))) return;
    ASNptr -= 3;
    Rotate(ASNptr[0],ASNptr[1],-(long)ASNptr[2] & 3,RotateAll);
  }
} // RemoveUndesiredEndTurns

/********************************************************/
static BOOL SolveLARFacesAux (DWORD face, DWORD x, DWORD y, DWORD limitation, BYTE thecolour)
{ if (face == FaceV) { if (y == limitation) return FALSE; }
  else if (face == FaceA) { if (y >= limitation) return FALSE; }
  else { if (x >= limitation) return FALSE; }
  if (GetColour4(face,x,y) != thecolour) return FALSE;
  // Turn it into the B face.
  if (face == FaceL)
  { DoTurn(AxisL,0,1); // It is located at (3-y,x) now.
    DoTurn(AxisV,x,1);
    DoTurn(AxisO,3,2);
    DoTurn(AxisV,x,3);
    DoTurn(AxisL,0,3);
  }
  else if (face == FaceA)
  { DoTurn(AxisV,3,3); // It is located at (y,3-x) now.
    DoTurn(AxisL,y,1);
    DoTurn(AxisO,3,2);
    DoTurn(AxisL,y,3);
    DoTurn(AxisV,3,1);
  }
  else if (face == FaceR)
  { DoTurn(AxisL,3,3); // It is located at (y,3-x) now.
    DoTurn(AxisV,3-x,3);
    DoTurn(AxisO,3,2);
    DoTurn(AxisV,3-x,1);
    DoTurn(AxisL,3,1);
  }
  else // if (face == FaceV)
  { DoTurn(AxisV,0,1); // It is located at (3-y,x) now.
    DoTurn(AxisL,3-y,3);
    DoTurn(AxisO,3,2);
    DoTurn(AxisL,3-y,1);
    DoTurn(AxisV,0,3);
  }
  return TRUE;
} // SolveLARFacesAux

/********************************************************/
DWORD BJW4SolveLARFaces (BYTE *colours)
{ BYTE thecolour,*bestasnptr;
  BOOL goleft,changed1,changed2;
  DWORD i,j,jj,k,x,y,slice,invalid,numtimes,maxxL,maxyA,maxxR,notyV,num,numcorrect,side,attempt,bestattempt,faces[3],slicenumbers[4];
  // Solve first slice of L (from the bottom, not counting edges), first slice of A, first slice of R. Then the same for second slices. And so on. We use the V face as a "scratchpad".
  // We actually do this 4 times (all combinations of solving L, A, R or R, A, L for first or second slice) and choose the best.
  // Note that when we solve them in the order L, A, R, we turn the solved slices to the right. After doing that slice for all 3 faces, they will be in the correct position.
  // Likewise, we "go left" when we do R, A, L.

  ASNptr = ASN;
  Extract4x4x4Cube();
  memcpy(SavedASN,ASN,(SavedASNptr = ASNptr) - ASN);
  memcpy(SavedCubeFaceColours4,CubeFaceColours4,sizeof(CubeFaceColours4));
  bestasnptr = (BYTE *)(-1);

  for (attempt = 0; attempt <= 4; attempt++)
  { // attempt 0: First slice: L, A, R. Second slice: L, A, R.
    // attempt 1: First slice: L, A, R. Second slice: R, A, L.
    // attempt 2: First slice: R, A, L. Second slice: L, A, R.
    // attempt 3: First slice: R, A, L. Second slice: R, A, L.
    // attempt 4: Do the best of the four attempts above.
    num = (attempt < 4) ? attempt : bestattempt;
    goleft = ((num == 1) && (slice == 2)) || ((num == 2) && (slice == 1)) || (num == 3);
    if (goleft)
    { faces[0] = FaceR;
      faces[2] = FaceL;
    } else
    { faces[0] = FaceL;
      faces[2] = FaceR;
    }
    faces[1] = FaceA;

    for (slice = 1; slice < 3; slice++)
    { for (side = 0; side < 3; side++) // L, A, R or R, A, L.
      { thecolour = colours[faces[side]];
        // Find the best slice already in the V face and put it running vertically on the "left". This may require doing a V face turn first.


/*
// See if we can place it inexpensively. First side of first slice only for now.
if (side == 0)
{ // This handles with the all cases where the slice for the first side is in the correct layer in any of the L, A, R, V faces.
  if ((GetColour4(faces[2],3-slice,1) == thecolour) && (GetColour4(faces[2],3-slice,2) == thecolour)) { DoTurn(AxisO,slice,0); continue; }
  if ((GetColour4(faces[0],3-slice,1) == thecolour) && (GetColour4(faces[0],3-slice,2) == thecolour)) { DoTurn(AxisO,slice,2); continue; }
  if ((GetColour4(FaceA,1,3-slice) == thecolour) && (GetColour4(FaceA,2,3-slice) == thecolour)) { DoTurn(AxisO,slice,(goleft) ? 1 : 3); continue; }
//  if ((GetColour4(FaceV,1,3-slice) == thecolour) && (GetColour4(FaceV,2,3-slice) == thecolour)) { DoTurn(AxisO,slice,(goleft) ? 3 : 1); continue; }
}
if ((GetColour4(FaceV,1,3-slice) == thecolour) && (GetColour4(FaceV,2,3-slice) == thecolour)) { DoTurn(AxisO,slice,(goleft) ? 3 : 1); continue; }
*/

        numcorrect = numtimes = 0;
        for (i = 1, k = 0; i < 3; i++) if (GetColour4(FaceV,slice,i) == thecolour) k++;
        if (k > numcorrect) { numcorrect = k; numtimes = 0; }
        for (i = 1, k = 0; i < 3; i++) if (GetColour4(FaceV,i,3-slice) == thecolour) k++;
        if (k > numcorrect) { numcorrect = k; numtimes = 1; }
        for (i = 1, k = 0; i < 3; i++) if (GetColour4(FaceV,3-slice,i) == thecolour) k++;
        if (k > numcorrect) { numcorrect = k; numtimes = 2; }
        for (i = 1, k = 0; i < 3; i++) if (GetColour4(FaceV,i,slice) == thecolour) k++;
        if (k > numcorrect) { numcorrect = k; numtimes = 3; }
        if (numtimes) DoTurn(AxisV,0,numtimes);
        if (numcorrect == 2)
        { DoTurn(AxisV,0,3);
          goto slicedone;
        }
        do
        { // Try to get additional facelets out of the L, A, R faces.
          do
          { changed2 = FALSE;
            numtimes = 3-slice + (side == 0);
            for (i = 1; i < numtimes; i++)
            { if (GetColour4(FaceV,slice,i) == thecolour) continue;
              for (j = 0; j < 3; j++)
              { jj = (goleft) ? 2-j : j;
                switch (jj)
                { case 0: x = i; y = 3-slice; break;
                  case 1: x = 3-slice; y = i; break;
                  case 2: x = i; y = slice; break;
                }
                if (GetColour4(faces[j],x,y) == thecolour) { DoTurn(AxisO,3-i,jj+1); changed2 = TRUE; break; }
              }
            }
            // Do a V2 turn and try to get more out of the L, A, R faces.
            DoTurn(AxisV,0,2);
            for (i = 1; i < numtimes; i++)
            { if (GetColour4(FaceV,3-slice,i) == thecolour) continue;
              for (j = 0; j < 3; j++)
              { jj = (goleft) ? 2-j : j;
                switch (jj)
                { case 0: x = i; y = slice; break;
                  case 1: x = slice; y = i; break;
                  case 2: x = i; y = 3-slice; break;
                }
                if (GetColour4(faces[j],x,y) == thecolour) { DoTurn(AxisO,3-i,jj+1); changed2 = TRUE; break; }
              }
            }
            if (changed2) DoTurn(AxisV,0,2);
          } while (changed2);
          // Try to get easy ones out of our own V face. Several might be done simultaneously.
          do
          { changed2 = FALSE;
            for (j = 1; j <= 3; j += 2) // For j = 1 and j = 3.
            { for (i = 1, numcorrect = numtimes = 0; i < 3; i++)
              { if (GetColour4(FaceV,3-slice,i) == thecolour) { numcorrect++; continue; }
                switch (j)
                { case 1: x =   i; y =   slice; break;
                  case 3: x = 3-i; y = 3-slice; break;
                }
                if ((x != 3-slice) && (GetColour4(FaceV,x,y) == thecolour)) slicenumbers[numtimes++] = x;
              }
              if (numtimes)
              { for (i = 0; i < numtimes; i++) DoTurn(AxisL,slicenumbers[i],1);
                DoTurn(AxisV,0,4-j);
                for (i = 0; i < numtimes; i++) DoTurn(AxisL,slicenumbers[i],3);
                DoTurn(AxisV,0,j);
                changed2 = TRUE;
              }
              if (numcorrect + numtimes == 2)
              { // Our slice must be running horizontally for where we jump to.
                DoTurn(AxisV,0,1);
                goto slicedone;
              }
            }
          } while (changed2);
          // Do a V turn to orient the slice horizontally and try to get more out of the B face.
          DoTurn(AxisV,0,1);
          if (goleft)
          { maxxR = 4-slice;
            maxxL = 3-slice + (side == 0);
          } else
          { maxxL = 4-slice;
            maxxR = 3-slice + (side == 0);
          }
          maxyA = 3-slice + (side <= 1);
          notyV = 3-slice;
          do
          { changed1 = FALSE;
            for (j = 0; j < 4; j++)
            { if (j) DoTurn(AxisO,3,3);
              do
              { changed2 = FALSE;
                // Try putting several facelets in place simultaneously.
                num = 1;
                invalid = (DWORD)(-1);
                for (i = 1, numcorrect = numtimes = 0; i < 3; i++)
                { if (GetColour4(FaceV,i,3-slice) == thecolour) { numcorrect++; continue; }
                  if ((i != invalid) && (GetColour4(FaceB,i,slice) == thecolour))
                  { slicenumbers[numtimes++] = i;
                    if (i == slice)
                    { invalid = 3-slice;
                      num = 3;
                    }
                    else if (i == 3-slice) invalid = slice;
                  }
                }
                if (numtimes)
                { for (i = 0; i < numtimes; i++) DoTurn(AxisL,slicenumbers[i],1);
                  DoTurn(AxisV,0,num);
                  for (i = 0; i < numtimes; i++) DoTurn(AxisL,slicenumbers[i],3);
                  DoTurn(AxisV,0,4-num);
                  changed1 = changed2 = TRUE;
                }
                if (numcorrect + numtimes == 2) goto slicedone;
              } while (changed2);
            }
            RemoveUndesiredEndTurns(AxisO,3);
          } while (changed1);
          // Missing ones are somewhere in the side faces (L, A, R, V). Get one of them out into the B face. Then use the above code to place it.
          for (i = 1; i < 3; i++)
          { if (GetColour4(FaceV,i,3-slice) == thecolour) continue;
            // Try all possible locations where it can be.
            if (SolveLARFacesAux(FaceR,slice,3-i,maxxR,thecolour)) break;
            if (SolveLARFacesAux(FaceR,3-i,3-slice,maxxR,thecolour)) break;
            if (SolveLARFacesAux(FaceR,3-slice,i,maxxR,thecolour)) break;
            if (SolveLARFacesAux(FaceR,i,slice,maxxR,thecolour)) break;

            if (SolveLARFacesAux(FaceA,3-i,3-slice,maxyA,thecolour)) break;
            if (SolveLARFacesAux(FaceA,3-slice,i,maxyA,thecolour)) break;
            if (SolveLARFacesAux(FaceA,i,slice,maxyA,thecolour)) break;
            if (SolveLARFacesAux(FaceA,slice,3-i,maxyA,thecolour)) break;

            if (SolveLARFacesAux(FaceL,slice,i,maxxL,thecolour)) break;
            if (SolveLARFacesAux(FaceL,3-i,slice,maxxL,thecolour)) break;
            if (SolveLARFacesAux(FaceL,3-slice,3-i,maxxL,thecolour)) break;
            if (SolveLARFacesAux(FaceL,i,3-slice,maxxL,thecolour)) break;

            if (SolveLARFacesAux(FaceV,slice,i,notyV,thecolour)) break;
            if (SolveLARFacesAux(FaceV,3-i,slice,notyV,thecolour)) break;
            if (SolveLARFacesAux(FaceV,3-slice,3-i,notyV,thecolour)) break;
          }
          DoTurn(AxisV,0,1);
        } while (TRUE);
slicedone:
        // Turn it into the R (or L when "go left") face. After doing all this 3 times, all 3 slices will be in the correct place.
        DoTurn(AxisO,slice,(goleft) ? 3 : 1);
      }
    }
    if (attempt < 4)
    { if (ASNptr < bestasnptr)
      { bestasnptr = ASNptr;
        bestattempt = attempt;
      }
      memcpy(ASN,SavedASN,(ASNptr = SavedASNptr) - ASN);
      memcpy(CubeFaceColours4,SavedCubeFaceColours4,sizeof(SavedCubeFaceColours4));
    }
  }
  return (ASNptr-ASN)/3;
} // BJW4SolveLARFaces

/********************************************************/
DWORD BJW4SolveBVFaces (BYTE thecolour)
{ DWORD i,j,numcorrect;
  char ch1,ch2,formula[32];
  BYTE bc,vc,bcolours[4],vcolours[4];
  // 'thecolour' is the correct colour for the V face.
  // Returns the number of turns to solve the BV faces while the actual turns are put into the axis/slice/numtimes arrays.

  static char *c1formulas[4]    = {"Bil'B'l2V2l'"    ,"Bir B r2V2r"     ,"Bil'B l2V2l'"    ,"Bir B'r2V2r"};
  static char *c2formulas[12]   = {"BiVjr B2r'"      ,"BiVjr'V2r"       ,"Bir B r2V r"     ,"Bil'B'l2V'l'",
                                   "Vir B2r'B'r B r'","Vir B'r'B r B2r'","Vil'B l B'l'B2l" ,"Vil'B2l B l'B'l",
                                   "Bir'V2r V'r'V r" ,"Bil V l'V'l V2l'","Bir'V'r V r'V2r" ,"Bil V2l'V l V'l'"};
  static char *c3formulas[4]    = {"Bil'B l"         ,"Bir B'r'"        ,"Bil'B'l"         ,"Bir B r'"};
  static char  c13numtimes[4*4] = {'2','1','3','0'   ,'3','2','0','1'   ,'1','0','2','3'   ,'0','3','1','2'};

  ASNptr = ASN;

  // V: (0)1,1 (1)2,1   B: (0)1,2 (1)2,2
  //    (2)1,2 (3)2,2      (2)1,1 (3)2,1
  for (i = numcorrect = 0; i < 4; i++)
  { if ((vcolours[i] = GetColour(FaceV,(i & 1) + 1,(i >> 1) + 1)) == thecolour) numcorrect++;
    bcolours[i] = GetColour(FaceB,(i & 1) + 1,2 - (i >> 1));
  }
  formula[0] = '\0';
  switch (numcorrect)
  { case 0:
      strcpy(formula,"r B2r2V2r");
      break;
    case 1:
      for (i = 0; vcolours[i] != thecolour; i++) ;
      for (j = 0; bcolours[j] == thecolour; j++) ;
      strcpy(formula,c1formulas[i]);
      formula[1] = c13numtimes[i*4+j];
      break;
    case 2:
      // Create convenient codes vc and bc giving the pattern of the colours that are correct. For instance bc = 0x13 means bcolours[1] and bcolours[3] are correct.
      for (i = 0, vc = 0; i < 4; i++) if (vcolours[i] == thecolour) vc = (vc << 4) + (BYTE)i;
      for (i = 0, bc = 0; i < 4; i++) if (bcolours[i] != thecolour) bc = (bc << 4) + (BYTE)i;
      ch2 = '\0';
      switch (vc)
      { case 0x01:
          switch (bc)
          { case 0x01: i =  1; ch1 = '3'; ch2 = '1'; break;
            case 0x02: i =  1; ch1 = '0'; ch2 = '1'; break;
            case 0x03: i =  6; ch1 = '1'; break;
            case 0x12: i =  7; ch1 = '1'; break;
            case 0x13: i =  1; ch1 = '2'; ch2 = '1'; break;
            case 0x23: i =  1; ch1 = '1'; ch2 = '1'; break;
          }
          break;
        case 0x02:
          switch (bc)
          { case 0x01: i =  0; ch1 = '1'; ch2 = '0'; break;
            case 0x02: i =  0; ch1 = '2'; ch2 = '0'; break;
            case 0x03: i =  4; ch1 = '0'; break;
            case 0x12: i =  5; ch1 = '0'; break;
            case 0x13: i =  0; ch1 = '0'; ch2 = '0'; break;
            case 0x23: i =  0; ch1 = '3'; ch2 = '0'; break;
          }
          break;
        case 0x03:
          switch (bc)
          { case 0x01: i =  9; ch1 = '1'; break;
            case 0x02: i =  8; ch1 = '0'; break;
            case 0x03: i =  3; ch1 = '0'; break;
            case 0x12: i =  3; ch1 = '1'; break;
            case 0x13: i =  9; ch1 = '0'; break;
            case 0x23: i =  8; ch1 = '1'; break;
          }
          break;
        case 0x12:
          switch (bc)
          { case 0x01: i = 11; ch1 = '1'; break;
            case 0x02: i = 10; ch1 = '0'; break;
            case 0x03: i =  2; ch1 = '1'; break;
            case 0x12: i =  2; ch1 = '0'; break;
            case 0x13: i = 11; ch1 = '0'; break;
            case 0x23: i = 10; ch1 = '1'; break;
          }
          break;
        case 0x13:
          switch (bc)
          { case 0x01: i =  1; ch1 = '3'; ch2 = '0'; break;
            case 0x02: i =  1; ch1 = '0'; ch2 = '0'; break;
            case 0x03: i =  6; ch1 = '0'; break;
            case 0x12: i =  7; ch1 = '0'; break;
            case 0x13: i =  1; ch1 = '2'; ch2 = '0'; break;
            case 0x23: i =  1; ch1 = '1'; ch2 = '0'; break;
          }
          break;
        case 0x23:
          switch (bc)
          { case 0x01: i =  0; ch1 = '1'; ch2 = '1'; break;
            case 0x02: i =  0; ch1 = '2'; ch2 = '1'; break;
            case 0x03: i =  4; ch1 = '1'; break;
            case 0x12: i =  5; ch1 = '1'; break;
            case 0x13: i =  0; ch1 = '0'; ch2 = '1'; break;
            case 0x23: i =  0; ch1 = '3'; ch2 = '1'; break;
          }
          break;
      }
      strcpy(formula,c2formulas[i]);
      formula[1] = ch1;
      if (ch2) formula[3] = ch2;
      break;
    case 3:
      for (i = 0; vcolours[i] == thecolour; i++) ;
      for (j = 0; bcolours[j] != thecolour; j++) ;
      strcpy(formula,c3formulas[i]);
      formula[1] = c13numtimes[i*4+j];
      break;
  }
  return StoreFormula(formula,RotateNothing);
} // BJW4SolveBVFaces

/********************************************************/
static BOOL IsEdgeFixedBO (DWORD face1, DWORD face2)
{ // face1 should be FaceB or FaceO. face2 should be FaceV or FaceA. For face2 values of FaceR and FaceL, IsEdgeFixedLR() can be used.
  DWORD y1,y2;

  y1 = (face2 == FaceV) ? 0 : 3;
  y2 = (face1 == FaceB) ? 0 : 3;
  return ((GetColour4(face1,1,y1) == GetColour4(face1,2,y1)) && (GetColour4(face2,1,y2) == GetColour4(face2,2,y2)));
} // IsEdgeFixedBO

/********************************************************/
static BOOL IsEdgeFixedLR (DWORD face1, DWORD face2)
{ // face1 should be FaceL or FaceR. face2 should be FaceV, FaceB, FaceA, or FaceO.
  DWORD c,x;

  x = (face1 == FaceL) ? 0 : 3;
  if ((face2 == FaceV) || (face2 == FaceA))
  { c = (face2 == FaceV) ? 0 : 3;
    return ((GetColour4(face1,1,c) == GetColour4(face1,2,c)) && (GetColour4(face2,x,1) == GetColour4(face2,x,2)));
  }
  // ((face2 == FaceB) || (face2 == FaceO))
  c = (face2 == FaceB) ? 0 : 3;
  return ((GetColour4(face1,c,1) == GetColour4(face1,c,2)) && (GetColour4(face2,x,1) == GetColour4(face2,x,2)));
} // IsEdgeFixedLR

/********************************************************/
static BOOL IsEdgeFixedLR (DWORD idx)
{ // idx should be 0..7 for LV, LO, LA, LB, RV, RO, RA, RB, respectively.
  DWORD face1, face2;

  face1 = (idx < 4) ? FaceL : FaceR;
  switch (idx & 3)
  { case 0: face2 = FaceV; break;
    case 1: face2 = FaceO; break;
    case 2: face2 = FaceA; break;
    case 3: face2 = FaceB; break;
  }
  return IsEdgeFixedLR(face1,face2);
} // IsEdgeFixedLR

/********************************************************/
static DWORD KeepSafe1Through8 (DWORD *numcorrect)
{ // Puts one or two fixed edges from the middle slice into one of the two side faces as inexpensively as possible. One edge can always be placed in 1-3 turns.
  // Returns the number of edges placed (numcorrect != NULL) or that can be placed (numcorrect == NULL).
  // Updates *numcorrect. The caller has to make sure never to call this when *numcorrect equals 8.
  // Note that all "[4]" arrays are used as a circular arrays. This includes VOAB[4].
  char formula[3];
  BOOL unstriped,lfree[4],rfree[4],fixededges[4];
  DWORD i,numtoplace,idx1,idx2,numlfree,numrfree,adjidx,adjcnt,adjtmp,numl,numr,numls[2],numrs[2];

  numtoplace = 0;
  // fixededges[0..3]: BV, OV, OA, BA, respectively.
  if ((fixededges[0] = IsEdgeFixedBO(FaceB,FaceV))) numtoplace++;
  if ((fixededges[1] = IsEdgeFixedBO(FaceO,FaceV))) numtoplace++;
  if ((fixededges[2] = IsEdgeFixedBO(FaceO,FaceA))) numtoplace++;
  if ((fixededges[3] = IsEdgeFixedBO(FaceB,FaceA))) numtoplace++;
  if ((numcorrect == NULL) || (numtoplace == 0)) return numtoplace;

  formula[2] = '\0';
  unstriped = Unstriped();
  numlfree = numrfree = 0;
  // lfree[0..3]: LV, LO, LA, LB, respectively.
  // rfree[0..3]: RV, RO, RA, RB, respectively.
  for (i = 0; i < 8; i++)
  { if (i < 4)
    { if ((lfree[i-0] = !IsEdgeFixedLR(i))) numlfree++; } else
    { if ((rfree[i-4] = !IsEdgeFixedLR(i))) numrfree++; }
  }

  // One or two to be placed? We may only place two if they are adjacent AND there are at least two free spots in the side faces.
  for (idx2 = 0, idx1 = 0xff; idx2 < 4; idx2++)
  { if (fixededges[idx2])
    { if (idx1 == 0xff) idx1 = idx2;
      if (fixededges[(idx2+1) & 3]) break;
    }
  }
  // If we cannot do two edges simultaneously the way we want to, then we let things be handled by the "one edge at a time" code below, doing one edge
  // during this call and leave the other for the next time.
  if ((idx2 < 4) && (*numcorrect < 7) && (unstriped) && (numlfree) && (numrfree))
  { // Two edges to be placed. Given by idx2 and idx2+1 mod 4.
    // The values in fixededges refer to BV, OV, OA, BA, respectively. Used as a circular array.
    //   idx2 == 0: The edges are BV and OV. Both V and V' may be used. This requires free spots at LV and RV.
    //   idx2 == 1: The edges are OV and OA. Both O and O' may be used. This requires free spots at LO and RO.
    //   idx2 == 2: The edges are OA and BA. Both A and A' may be used. This requires free spots at LA and RA.
    //   idx2 == 3: The edges are BA and BV. Both B and B' may be used. This requires free spots at LB and RB.
    // See if we can place them both in a single turn. In addition to the above requirements, this requires the cube to be unstriped.
    // We may need to adjust the side faces first.
    for (numl = 0; !lfree[(idx2+numl) & 3]; numl++) ;
    DoTurn(AxisL,0,-(long)numl & 3);  // numl L' turns. (numl * 3) & 3.
    for (numr = 0; !rfree[(idx2+numr) & 3]; numr++) ;
    DoTurn(AxisL,3,-(long)numr & 3);  // numr R  turns. (4 - numr) & 3.
    // ((lfree[idx2]) && (rfree[idx2])). Place both in a single turn now.
    DoFormula(VOAB[idx2]);
    (*numcorrect) += 2;
    return 2;
  }

  // One edge to be placed. Given by idx1.
  //   idx1 == 0: The edge is BV. It may be possible to use one of the following single turns: B, B', V, V'.
  //   idx1 == 1: The edge is OV. It may be possible to use one of the following single turns: O, O', V, V'.
  //   idx1 == 2: The edge is OA. It may be possible to use one of the following single turns: O, O', A, A'.
  //   idx1 == 3: The edge is BA. It may be possible to use one of the following single turns: B, B', A, A'.
  // Since we did not handle all two edge cases above, we need to be careful not to disturb a possible second fixed edge.
  (*numcorrect)++;
  if ((unstriped) && (numlfree) && (numrfree))
  { // We may need to adjust the side faces first (0, 1, or 2 adjustments). We prefer no adjustments.
    //   B  places BV in the left face and BA in the right face. It requires LB and RB to be free. idx1 == 0, lfree[3], rfree[3]. idx1 == 3, lfree[3], rfree[3].
    //   B' places BA in the left face and BV in the right face. It requires LB and RB to be free. idx1 == 0, lfree[3], rfree[3]. idx1 == 3, lfree[3], rfree[3].
    //   V  places OV in the left face and BV in the right face. It requires LV and RV to be free. idx1 == 0, lfree[0], rfree[0]. idx1 == 1, lfree[0], rfree[0].
    //   V' places BV in the left face and OV in the right face. It requires LV and RV to be free. idx1 == 0, lfree[0], rfree[0]. idx1 == 1, lfree[0], rfree[0].
    //   O  places OA in the left face and OV in the right face. It requires LO and RO to be free. idx1 == 1, lfree[1], rfree[1]. idx1 == 2, lfree[1], rfree[1].
    //   O' places OV in the left face and OA in the right face. It requires LO and RO to be free. idx1 == 1, lfree[1], rfree[1]. idx1 == 2, lfree[1], rfree[1].
    //   A  places BA in the left face and OA in the right face. It requires LA and RA to be free. idx1 == 2, lfree[2], rfree[2]. idx1 == 3, lfree[2], rfree[2].
    //   A' places OA in the left face and BA in the right face. It requires LA and RA to be free. idx1 == 2, lfree[2], rfree[2]. idx1 == 3, lfree[2], rfree[2].
    for (i = adjidx = 0; i < 2; i++)
    { adjtmp = 0;
      for (numls[i] = 0; !lfree[(idx1+i*3+numls[i]) & 3]; numls[i]++) ;
      if (numls[i]) adjtmp++;
      for (numrs[i] = 0; !rfree[(idx1+i*3+numrs[i]) & 3]; numrs[i]++) ;
      if (numrs[i]) adjtmp++;
      if (i == 0) adjcnt = adjtmp; else if (adjtmp < adjcnt) adjidx = 1;
    }
    // adjidx gives the index (0 or 1) that leads to the minimum number of adjustments to make (0, 1, or 2).
    DoTurn(AxisL,0,-(long)numls[adjidx] & 3);  // L' turns. (numls[adjidx] * 3) & 3).
    DoTurn(AxisL,3,-(long)numrs[adjidx] & 3);  // R  turns. (4 - numrs[adjidx]) & 3).
    // Now we can place the edge in a single turn.
    if (((idx1 == 0) && (adjidx == 1)) || ((idx1 == 3) && (adjidx == 0))) DoFormula("B");
    if (((idx1 == 0) && (adjidx == 0)) || ((idx1 == 1) && (adjidx == 1))) DoFormula("V");
    if (((idx1 == 1) && (adjidx == 0)) || ((idx1 == 2) && (adjidx == 1))) DoFormula("O");
    if (((idx1 == 2) && (adjidx == 0)) || ((idx1 == 3) && (adjidx == 1))) DoFormula("A");
    return 1;
  }

  // Place the idx1 one in the L face or the R face. Since each edge can be placed in a given face in two ways (for instance, BV can be placed in the L face
  // with a B turn, but also with a V' turn), at least one of them does not need an L face turn first, so this can always be done in 3 turns.
  if (numlfree)
  { idx1 = (idx1 + (idx2 = (lfree[idx1]) ? 3 : 0)) & 3;
    for (numl = 1; !lfree[(idx1+numl) & 3]; numl++) ;
    formula[0] = VOAB[idx1][0];
    formula[1] = (idx2 == 0) ? '\'' : ' ';
    DoFormula(formula);
    DoTurn(AxisL,0,-(long)numl & 3);  // (numl * 3) & 3.
    formula[1] = (idx2 == 0) ? ' ' : '\'';
    DoFormula(formula);
    return 1;
  }

  // (numrfree).
  idx1 = (idx1 + (idx2 = (rfree[idx1]) ? 3 : 0)) & 3;
  for (numr = 1; !rfree[(idx1+numr) & 3]; numr++) ;
  formula[0] = VOAB[idx1][0];
  formula[1] = (idx2 == 0) ? ' ' : '\'';
  DoFormula(formula);
  DoTurn(AxisL,3,-(long)numr & 3);  // (4-numr) & 3).
  formula[1] = (idx2 == 0) ? '\'' : ' ';
  DoFormula(formula);
  return 1;
} // KeepSafe1Through8

/********************************************************/
static DWORD BestlSliceTurn (DWORD *bestnumcorrect)
{ DWORD i,num,numturns,numcorrect;

  for (i = 1, numturns = numcorrect = 0; i < 4; i++)
  { DoTurn(AxisL,1,1);
    if ((num = KeepSafe1Through8(NULL)) > numcorrect)
    { numcorrect = num;
      numturns = i;
    }
  }
  if (bestnumcorrect) *bestnumcorrect = numcorrect;
  DoTurn(AxisL,1,(bestnumcorrect) ? 1 : ((numturns+1) & 3));  // Restore the situation or do the actual turns.
  return numturns;
} // BestlSliceTurn

/********************************************************/
DWORD BJW4SolveEdges1Through8 ()
{ BYTE *bestptr;
  BOOL unstriped;
  DWORD i,j,edge,face1,face2,numturns,numcorrect;

  ASNptr = ASN;
  Extract4x4x4Cube();

  unstriped = Unstriped();  // Because counting the edges that are already fixed may make us skip the big "while (edge < 8)" loop.
  for (i = edge = 0; i < 8; i++) if (IsEdgeFixedLR(i)) edge++;

  while (edge < 8)
  { // There is at least one more edge to be placed. See if we have any in the middle slice that are already fixed.
    if (KeepSafe1Through8(&edge)) continue;

    // There is nothing in the middle slice now. See if l, l2, and l' help. If so, choose the best.
    if (BestlSliceTurn(NULL)) continue;

    // The remainder has to come from flipped edgelets in the horizontal edges and from the R and L faces.
    // An inexpensive way of trying to fix more edges is by unstriping the cube first (0 or 1 turns) and then trying each of V2, O2, A2, B2 to see
    // if something in the middle slice can be fixed. If so, then this also results in edgelets coming out of the R and L faces.
    // To save writing a lot of code, we simply save the situation here and restore it after each test.
    memcpy(SavedASN,ASN,(SavedASNptr = ASNptr) - ASN);
    memcpy(SavedCubeFaceColours4,CubeFaceColours4,sizeof(CubeFaceColours4));
    for (face1 = numcorrect = 0, bestptr = (BYTE *)(-1); face1 < 4; face1++)
    { Unstripe();
      DoFormula(VOAB[face1]); DoFormula(VOAB[face1]);
      i = BestlSliceTurn(&j);  // i is the number of l turns, j is number of edges that will be fixed by those l turns.
      if (edge+j > 8) j = 8-edge;  // We can place only 8 edges.
      if ((j > numcorrect) || ((j == numcorrect) && (ASNptr < bestptr)))
      { numturns = i;
        numcorrect = j;
        face2 = face1;
        bestptr = ASNptr;
      }
      memcpy(ASN,SavedASN,(ASNptr = SavedASNptr) - ASN);
      memcpy(CubeFaceColours4,SavedCubeFaceColours4,sizeof(SavedCubeFaceColours4));
    }
    if (numcorrect)
    { Unstripe();
      DoFormula(VOAB[face2]); DoFormula(VOAB[face2]);
      DoTurn(AxisL,1,numturns);
      continue;
    }

    // The only way we can get more now is to get something out of the R or L face. There are up to 16 possibilities, but we of course do not take anything
    // out of those that is already fixed. Note that we will always find at least one way to take something out of those faces.
    memcpy(SavedASN,ASN,(SavedASNptr = ASNptr) - ASN);
    memcpy(SavedCubeFaceColours4,CubeFaceColours4,sizeof(CubeFaceColours4));
    for (face1 = numcorrect = 0, bestptr = (BYTE *)(-1); face1 < 48; face1++)
    { if (!IsEdgeFixedLR(face1 / 6))
      { DoFormula(EdgeFormulas1Through8[face1]);
        i = BestlSliceTurn(&j);  // i is the number of l turns, j is number of edges that will be fixed by those l turns.
        if (edge+j > 8) j = 8-edge;  // We can place only 8 edges.
        if ((j > numcorrect) || ((j == numcorrect) && (ASNptr < bestptr)))
        { numturns = i;
          numcorrect = j;
          face2 = face1;
          bestptr = ASNptr;
        }
        memcpy(ASN,SavedASN,(ASNptr = SavedASNptr) - ASN);
        memcpy(CubeFaceColours4,SavedCubeFaceColours4,sizeof(SavedCubeFaceColours4));
      }
    }
    DoFormula(EdgeFormulas1Through8[face2]);
    DoTurn(AxisL,1,numturns);
  }

  Unstripe();
  DoFormula("B V2A2");  // To put the remaining ones in the B face. We use the B face as our "main" face from now on.

  return (ASNptr-ASN)/3;
} // BJW4SolveEdges1Through8

/********************************************************/
DWORD BJW4SolveEdges11And12 (BYTE parity, WORD **solution, WORD **solutionptr)
{ // We fix all parity problems here as well. Possible parity problems: Edge parity and/or swap parity.
  BYTE bl1,bl2,br1;

  // This function is called twice. The first time, we save the current situation and solution and then solve edges 11 and 12, ignoring any possible
  // parity problems. The second time, we restore the situation and use the provided parity to find a formula that not only solves edges 11 and 12
  // but also makes sure the parity is 0 afterwards.
  ASNptr = ASN;
  if (parity == 0xff)
  { SolutionPtr = *solutionptr;
    memcpy(Solution,*solution,sizeof(Solution));
    SavedCubeFaceColours = (BYTE *)malloc(6*MaxDim*MaxDim);
    memcpy(SavedCubeFaceColours,CubeFaceColours,6*MaxDim*MaxDim);
    parity = 0;
  } else
  { *solutionptr = SolutionPtr;
    memcpy(*solution,Solution,sizeof(Solution));
    memcpy(CubeFaceColours,SavedCubeFaceColours,6*MaxDim*MaxDim);
    free(SavedCubeFaceColours);
    SavedCubeFaceColours = NULL;
  }
  Extract4x4x4Cube();

  bl1 = (GetColour4(FaceB,0,1) << 4) + GetColour4(FaceL,0,1);
  bl2 = (GetColour4(FaceB,0,2) << 4) + GetColour4(FaceL,0,2);
  br1 = (GetColour4(FaceB,3,1) << 4) + GetColour4(FaceR,0,1);
  // br2 = (GetColour4(FaceB,3,2) << 4) + GetColour4(FaceR,0,2); // We do not need this one.
  // We have only 3 possible situations (with 4 parities each) for these last 2 edges.
  // I very much suspect that the solutions of length 13 and 15 are not optimal at this point while taking the variances and invariances into account.
  // A brute-force search showed that all solutions of length 10 or less are optimal and that the ones of length 13 and 15 cannot be solved in less than AT LEAST
  // 11 turns. Their optimal solutions may be longer than 11, but cannot be shorter because the brute-force search of all lengths of 10 or less was completed.
  if (bl1 == bl2)
  { switch (parity)
    { case 0: break; // 0.
      case 1: DoFormula("v2B2v2B2b2v2b2"); break; // 7.
      case 2: DoFormula("v2L2B2a'B2v B2v'B2R2v'R2a L2v2"); break; // 15.
      case 3: DoFormula("v R2v'R2v'L2v L2v'O2v O2v'"); break; // 13. Also: "v O2v'O2v L2v'L2v R2v R2v'"
    }
  } else if (bl1 == br1)
  { switch (parity)
    { case 0: DoFormula("v R B'A R'B v'"); break; // 7.
      case 1: DoFormula("v'L B'V L'B v "); break; // 7.
      case 2: DoFormula("R B'A r2B2r A2r2B2r'O2V2l "); break; // 13.
      case 3: DoFormula("R B'A r2O2r V2r2O2r'O2V2r'"); break; // 13.
    }
  } else
  { switch (parity)
    { case 0: DoFormula("L2a'O2R2B2L2v'"); break; // 7.
      case 1: DoFormula("L2v O2L2B2R2a "); break; // 7.
      case 2: DoFormula("v2B2v R2v2B2v'O2L2a "); break; // 10.
      case 3: DoFormula("v2O2v L2v2O2v'O2L2v'"); break; // 10.
    }
  }
  return (ASNptr-ASN)/3;
} // BJW4SolveEdges11And12

/********************************************************/
