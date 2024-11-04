#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Copyright by Ben Jos Walbeehm. Written March 2007. Slight improvements made on 19-May-2010 and 20-May-2010.
// Some infrequent changes, mostly related to the 4x4x4 cube, made during March-May 2012.
// Licence: This code may be used for non-commercial purposes as long as the author (Ben Jos Walbeehm) is clearly credited.

// This is definitely NOT an example of the most elegant code I have written.
// See, for instance, my usage of goto statements and my inconsistent usage of DoTurn() vs. DoFormula().

// Note that we use Dutch notation for the cube faces:
//   Dutch  English
//     R       R
//     B       U
//     V       F
//     L       L
//     O       D
//     A       B

#define USE4X4X4CODE  // Remark out to use the generic solver instead of the improvements used for the 4x4x4 cube in bjwsolve4.cpp.

static DWORD N,N1,N2; // NxNxN cube. N1 = N-1. N2 = N-2. Used many times, so that is why I assign them their own variables.
static DWORD HalfN,HalfN1;
static DWORD MaxDim;
static BYTE *CubeFaceColours,*SavedCubeFaceColours;

// Colours used in Ken Silverman's Rubix (but note that the user can edit this in Rubix):
// 1: L face colour.
// 2: R face colour.
// 3: B face colour.
// 4: O face colour.
// 5: V face colour.
// 6: A face colour.

static const DWORD FaceL = 0;
static const DWORD FaceR = 1;
static const DWORD FaceB = 2;
static const DWORD FaceO = 3;
static const DWORD FaceV = 4;
static const DWORD FaceA = 5;

static const DWORD AxisL = 0; // FaceL >> 1 (and also FaceR >> 1).
static const DWORD AxisO = 1; // FaceO >> 1 (and also FaceB >> 1).
static const DWORD AxisV = 2; // FaceV >> 1 (and also FaceA >> 1).
// To make sure we stick to L, O, A, and ultimately not make things even more complex, we have not defined AxisR, AxisB, and AxisA here.

static BYTE Colours[6];  // Will hold the correct colour for each face (FaceL through FaceA).

// For a 3x3x3 cube, Rubix uses the following:
//   R: axis 0 (x), slice 2. numtimes is inversed (i.e. use 4-numtimes instead).
//   L: axis 0 (x), slice 0.
//   B: axis 1 (y), slice 0. numtimes is inversed (i.e. use 4-numtimes instead).
//   O: axis 1 (y), slice 2.
//   V: axis 2 (z), slice 0.
//   A: axis 2 (z), slice 2. numtimes is inversed (i.e. use 4-numtimes instead).
//
// More generally, for an NxNxN cube, we denote turns as a turn of the nth slice of a given axis.
//
//   x-axis: Turns L  through L   . Note that L  = R'    , for 0 <= n < N.
//                  0          N-1             n    N-1-n
//
//   y-axis: Turns O  through O   . Note that O  = B'    , for 0 <= n < N.
//                  0          N-1             n    N-1-n
//
//   z-axis: Turns V  through V   . Note that V  = A'    , for 0 <= n < N.
//                  0          N-1             n    N-1-n
//
// As a slight extension of this notation, a turn of the first 3 slices of the x axis might be written as L      as shorthand for L  L  L . I think I do not use either notation anywhere, though.
//                                                                                                         0,1,2                   0  1  2
// Note that O  in our notation is a turn of slice N-1-n of the y-axis in Rubix. In our code, we do a conversion in DoTurn() so that the rest of the code can treat O-slice
//            n
// turns the same way as slice turns of L and V, i.e. that O  is a 90 degree turn of the O-face, not a -90 degree turn of the B face. So we treat the turns as depicted below.
//                                                          0
//                    ________
//      V  ----------/       /|
//       N-1        /   B   / |
//    V -----------/_______/  |
//     0     O  ---|       | R|
//            N-1  |       |  /
//                 |   V   | /
//           O  ---|_______|/
//            0     |     |
//                  L     L
//                   0     N-1
//
//
// To access facelets, use the following x and y origins for the CubeFaceColours[] array:
//
//                              /
//                           y /
//   On the R and L faces:    /
//                            |
//                           x|
//                            |
//
//                              /
//                           y /
//   On the B and O faces:    /___
//                              x
//
//                               x
//                             _____
//   On the V and A faces:    |
//                           y|
//                            |
//
// Note that these lines use the view of the drawing of the cube above and that we would be looking at the (inside of) the L, O, A faces through the cube.
//
//
// In Rubix, a turn is encoded into a WORD (which, in "our" terms, is a 16-bit unsigned integer) as follows:
//
//   L : (n << 4) + (0 << 2) + numtimes.
//    n
//
//   O : (n << 4) + (1 << 2) + numtimes.
//    n
//
//   V : (n << 4) + (2 << 2) + numtimes.
//    n
//
// numtimes gives the number of quarter (i.e. 90 degree) turns for a face; for L, O, V this is 1; for L2, O2, V2 this is 2; for L', O', V' this is 3.
//
// Since 12 bits are used for the slice number, this encoding scheme can handle cubes up to (and including) size 4096x4096x4096 (although not the trivial 0x0x0 cube).

static BOOL   DoNotCombine;
static DWORD  BestXYZ[3];
static DWORD *SliceNumbers;
static WORD  *Solution,*SolutionPtr,BestSolution[524288]; // 524288 is plenty even for 256x256x256 cubes.

static  BYTE   InputFor3x3x3[54],BestInputFor3x3x3[54];

static  char  *OFaceSliceTurns[6][4] =
{ {"L2","L" ,NULL,"L'"},
  {"R2","R'",NULL,"R" },
  {NULL,"B" ,"B2","B'"},
  {NULL,NULL,NULL,NULL},
  {NULL,"V'","V2","V" },
  {"A" ,"A2","A'",NULL}
};

// Solving the edges:
//
// To match VB or BV: Find matching colours in:
// VR: FaceV,N-1,y and FaceR,  x,  0.
// VL: FaceV,  0,y and FaceL,  x,  0.
// OR: FaceO,N-1,y and FaceR,N-1,  y.
// OL: FaceO,  0,y and FaceL,N-1,  y.
// AR: FaceA,N-1,y and FaceR,  x,N-1.
// AL: FaceA,  0,y and FaceL,  x,N-1.
// BR: FaceB,N-1,y and FaceR,  0,  y.
// BL: FaceB,  0,y and FaceL,  0,  y.
//
// To encode 0, N-1, x, y:
//
//  -1: Use N-1.
//   0: Use 0.
//   1: Run x or y, depending on position.
//
// static char *EdgesFixed = "LA LO LV RA RO RV LB RB";
//
// EdgesFixed shows the order in which the edges are fixed in the SolveEdges1Through8() function. So, for example, when we are fixing the second edge (edge = 1), we are fixing LO.
// For formulas to place things correctly oriented into one of the horizontal edges, we also have to know which edges are affected. That is what safeedges[][] is for. For instance,
// if safeedges[][] gives 4 (i.e. we are working on edge RO), then we can use this formula when edge <= 4, else we have to use an alternative, usually (but not always!) longer, formula.
// But also note some "special" formulas below, marked by footnotes (1) through (5). And note that the formula explained in footnote (3) is "doubly special".
// The first set of formulas gives solutions for placing things that match BV, the second for ones that match VB. The codes array tells us which pieces to match. For instance, if code = -1,
// the piece we are looking for comes from N1-x, not x.

static struct EDGESOLVER
{ DWORD faces[2];
  DWORD codes[2][2];
  char *formulas[2][3];
  DWORD safeedges[2][3];
} EdgeSolver[8];

static struct EDGESOLVERTEMPLATE
{ char  faces[2];
  long  codes[2][2];
  char *formulas[2][3];
  DWORD safeedges[2][3];
} EdgeSolverTemplate[8] =
{ {{'V','R'},{{-1,1},{ 1, 0}},{{"V O'V'O","A'R2A R"     ,      NULL},{"B R B'"  ,"A R2A'"      ,"B R B'R'"}},{{4,5,0},{3,4,5}}}, // VR is fixed during edge = 5, so this set is complete. (1)
  {{'V','L'},{{ 0,1},{ 1, 0}},{{"V'O'V O",          NULL,      NULL},{"B'L'B"   ,"B'L'B L"     ,      NULL}},{{2,0,0},{0,2,0}}}, // VL is fixed during edge = 2, so this set is complete.
  {{'O','R'},{{-1,1},{-1, 1}},{{"V'R V"  ,"V'R V R'"    ,      NULL},{"A R'A'"  ,          NULL,      NULL}},{{3,4,0},{4,0,0}}}, // OR is fixed during edge = 4, so this set is complete.
  {{'O','L'},{{ 0,1},{-1, 1}},{{"V L'V'" ,"O'A'O A"     ,      NULL},{"A'L A"   ,          NULL,      NULL}},{{0,1,0},{1,0,0}}}, // OL is fixed during edge = 1, so this set is complete.
  {{'A','R'},{{-1,1},{ 1,-1}},{{"O'R O"  ,          NULL,      NULL},{"B R'B'"  ,          NULL,      NULL}},{{3,0,0},{3,0,0}}}, // AR is fixed during edge = 3, so this set is complete.
  {{'A','L'},{{ 0,1},{ 1,-1}},{{"O L'O'" ,          NULL,      NULL},{"B'L B"   ,          NULL,      NULL}},{{0,0,0},{0,0,0}}}, // AL is fixed during edge = 0, so this set is complete.
  {{'B','R'},{{-1,1},{ 0, 1}},{{"A'R A"  ,"R A B A'B'R'","A'R A R2"},{"O R2O'"  ,"R B R'B'"    ,"O R2O'"  }},{{4,5,7},{3,5,7}}}, // BR is fixed during edge = 7, so this set is complete. (2)(3)
  {{'B','L'},{{ 0,1},{ 0, 1}},{{"A L'A'" ,"L'A'B'A B L" ,"A L'A'L2"},{"B A B'A'","O'L2O"       ,      NULL}},{{1,2,6},{2,6,0}}}  // BL is fixed during edge = 6, so this set is complete. (4)(5)
};

// (1): Note that A'R2A R   swaps RA and RO, but that is OK since it is only used once RA and RO both already contain fixed edges, so the set of the entire edges (minus corners) {RA, RO} can be permuted without breaking anything.
// (2): Note that A'R A R2  cycles RA, RO, and RV, but that is OK since it is only used once RA, RO, and RV all already contain fixed edges, so the set {RA, RO, RV} can be permuted without breaking anything.
// (3): Note that O R2O'    swaps RA and RV, but that is OK since it is only used in 2 cases: (1) when neither RA nor RV contains fixed edges yet; (2) once both LA and LV contain fixed edges.
// (4): Note that A L'A'L2  cycles LA, LO, and LV, but that is OK since it is only used once LA, LO, and LV all already contain fixed edges.
// (5): Note that O'L2O     swaps LA and LV, but that is OK since it is only used once LA and LV both already contain fixed edges.

static struct EDGE3CYCLE
{ DWORD axis[8]; // Note that AxisL = 0 and AxisV = 2.
  long  slicecode[8];
  DWORD numtimes[8];
} Edge3Cycle[5] =
{ {{0,2,0,2,0,2,0,2},{ 1,-1, 0,-1, 1,-1, 0,-1},{3,3,3,1,1,3,1,1}},
  {{0,2,0,2,0,2,0,2},{-1,-1,-1, 1,-1,-1,-1, 1},{3,1,1,1,3,3,1,3}},
  {{2,0,2,0,2,0,2,0},{ 1, 0,-1, 0, 1, 0,-1, 0},{3,3,3,1,1,3,1,1}},
  {{0,2,0,2,0,2,0,2},{ 0,-1, 0, 1, 0,-1, 0, 1},{3,3,1,3,3,1,1,1}},
  {{2,0,2,0,2,0,2,0},{ 1,-1,-1,-1, 1,-1,-1,-1},{1,3,1,1,3,3,3,1}}
};

static DWORD LastEdge3Cycle;

// Although my NxNxN solver by itself is perfectly capable of solving a 4x4x4, I have included some code to make 4x4x4 solutions shorter on average.
// See also the definition of USE4X4X4CODE above.
static BYTE *ASN4ptr;
extern void  BJW4Initialise (int mem_n, char *facelist, BYTE **asnptr);
extern DWORD BJW4SolveOFace (BYTE thecolour);
extern DWORD BJW4SolveLARFaces (BYTE *colours);
extern DWORD BJW4SolveBVFaces (BYTE thecolour);
extern DWORD BJW4SolveEdges1Through8 ();
extern DWORD BJW4SolveEdges11And12 (BYTE parity, WORD **solution, WORD **solutionptr);

// Interfaces to my 2x2x2 and 3x3x3 solvers.
extern int   BJWSolve2CubeFromRubix (int mem_n, char *facelist, unsigned short *rotlist, int quality);
extern int   BJWSolve3CubeFromRubix (unsigned short *rotlist, int quality);
extern BYTE  Get3x3x3Parity (BYTE *rubixcodes);

// Declared in rubix.c.
extern char  message[1024];
extern void  rotate (long axis, long slice, long numtimes);

/********************************************************/
static __forceinline BYTE GetColour (DWORD face, DWORD x, DWORD y)
{ return CubeFaceColours[(face * MaxDim + x) * MaxDim + y];
} // GetColour

/********************************************************/
static __forceinline void SetColour (DWORD face, DWORD x, DWORD y, BYTE colour)
{ CubeFaceColours[(face * MaxDim + x) * MaxDim + y] = colour;
} // SetColour

/********************************************************/
static BYTE GetColoursEdgeB (DWORD n, DWORD otherface, BOOL swapped)
{ BYTE c1,c2;
  DWORD bx,by,ox,oy;
  // For 0 < n < N-1:
  // BV: B,  n,  0 and V,n,0.
  // BL: B,  0,  n and L,0,n.
  // BA: B,  n,N-1 and A,n,0.
  // BR: B,N-1,  n and R,0,n.

  if (otherface == FaceV)  { bx = ox = n; by = oy = 0; } else
  if (otherface == FaceL)  { bx = ox = 0; by = oy = n; } else
  if (otherface == FaceA)  { bx = ox = n; by = N1; oy = 0; } else
  /* (otherface == FaceR)*/{ bx = N1; ox = 0; by = oy = n; }
  c1 = GetColour(FaceB,bx,by) - 1;
  c2 = GetColour(otherface,ox,oy) - 1;
  return (swapped) ? c2*6+c1 : c1*6+c2;
} // GetColoursEdgeB

/********************************************************/
static void DoTurn (DWORD axis, DWORD slice, DWORD numtimes)
{ DWORD code;

  if (axis == AxisO) slice = N1-slice;
  rotate(axis,slice,numtimes);
  if (!DoNotCombine)
  { // Before storing the turn, see if we can combine it with the last turn.
    if (SolutionPtr > Solution)
    { code = (DWORD)*(SolutionPtr-1);
      if ((((code >> 2) & 3) == axis) && ((code >> 4) == slice))
      { numtimes = (numtimes + code) & 3;
        SolutionPtr--;
      }
    }
  }
  if (numtimes) *SolutionPtr++ = (WORD)((slice << 4) + (axis << 2) + numtimes);
} // DoTurn

/********************************************************/
static void UndoTurns (WORD *srcptr)
{ DWORD code,axis,slice;

  while (SolutionPtr > srcptr)
  { code = *--SolutionPtr;
    axis = (code >> 2) & 3;
    slice = code >> 4;
    rotate(axis,slice,-(long)code & 3);
  }
} // UndoTurns

/********************************************************/
static void RemoveUndesiredEndTurns (DWORD axis, DWORD slice)
{ long code;
  // (DWORD)(-1) removes all slices of the specified axis.
  // Note that this function gets called around 1400 times for a 37000 turn solution on a 64x64x64, so not much to be gained here.

  if (slice != (DWORD)(-1)) if (axis == AxisO) slice = N1-slice;
  while (SolutionPtr > Solution)
  { code = *(SolutionPtr-1);
    if (slice == (DWORD)(-1))
    { if (((DWORD)code & 12) != (axis << 2)) return; } else
    { if (((DWORD)code & ~3) != (axis << 2) + (slice << 4)) return; }
    SolutionPtr--;
    rotate((code >> 2) & 3,code >> 4,-code & 3);
  }
} // RemoveUndesiredEndTurns

/********************************************************/
static void DoASN4Turns (DWORD len)
{ DWORD i;

  for (i = 0; i < len; i++) DoTurn(ASN4ptr[i*3+0],ASN4ptr[i*3+1],ASN4ptr[i*3+2]);
} // DoASN4Turns

/********************************************************/
static void DoFormula (char *fptr)
{ DWORD axis,slice,numtimes;

  while (*fptr)
  { switch (*fptr++)
    { case 'L': axis = AxisL; slice =  0; break;
      case 'R': axis = AxisL; slice = N1; break;
      case 'O': axis = AxisO; slice =  0; break;
      case 'B': axis = AxisO; slice = N1; break;
      case 'V': axis = AxisV; slice =  0; break;
      case 'A': axis = AxisV; slice = N1; break;
    }
    switch (*fptr++)
    { case '\0': fptr--; // Fall through. This is so that we can write "R B" instead of "R B ".
      case '1' : // Fall through.
      case ' ' : numtimes = 1; break;
      case '2' : numtimes = 2; break;
      case '3' : // Fall through.
      case '\'': numtimes = 3; break;
    }
    if (slice == N1) numtimes = 4-numtimes;
    DoTurn(axis,slice,numtimes);
  }
} // DoFormula

/********************************************************/
static void DoEdge3Cycle (DWORD idx, DWORD numslices)
{ long slicecode;
  DWORD i,k,axis,slice,numtimes;

  for (k = 0; k < 8; k++)
  { axis = Edge3Cycle[idx].axis[k];
    slicecode = Edge3Cycle[idx].slicecode[k];
    numtimes = Edge3Cycle[idx].numtimes[k];
    if (slicecode == 1)
    { // Turn several slices simultaneously.
      for (i = 0; i < numslices; i++) DoTurn(axis,SliceNumbers[i],numtimes);
    } else
    { slice = 0; if (slicecode < 0) slice = N1;
      DoTurn(axis,slice,numtimes);
    }
  }
  LastEdge3Cycle = idx;
} // DoEdge3Cycle

/********************************************************/
static DWORD NormaliseSolution ()
{ WORD t,*srcptr,*dstptr;
  DWORD j,k,n,len,newlen,axis,lastaxis,slice,numtimes,code;

  newlen = (DWORD)(SolutionPtr - Solution);

  do
  { if (newlen < 2) return newlen;
    lastaxis = (DWORD)(-1);
    Solution[len=newlen] = (WORD)(-1); // End marker to make things more convenient.
    srcptr = Solution;
    do
    { n = 1;
      while ((axis = (*srcptr++ >> 2) & 3) == lastaxis) n++;
      if (n > 1)
      { dstptr = srcptr-n-1;
        for (j = n-1; j > 0; j--) for (k = 0; k < j; k++) if (dstptr[k] > dstptr[k+1]) { t = dstptr[k]; dstptr[k] = dstptr[k+1]; dstptr[k+1] = t; }
      }
      lastaxis = axis;
    } while (axis != 3);
    srcptr = dstptr = Solution+1;
    while ((code = *srcptr++) != (WORD)(-1))
    { axis = (code >> 2) & 3;
      slice = code >> 4;
      numtimes = code & 3;
      if (dstptr > Solution)
      { code = (DWORD)*(dstptr-1);
        if ((((code >> 2) & 3) == axis) && ((code >> 4) == slice))
        { numtimes = (numtimes + code) & 3;
          dstptr--;
        }
      }
      if (numtimes) *dstptr++ = (WORD)((slice << 4) + (axis << 2) + numtimes);
    }
    newlen = (DWORD)(dstptr - Solution);
  } while (newlen < len);
  SolutionPtr = Solution + newlen;

  return newlen;
} // NormaliseSolution

/********************************************************/
static BOOL AdjustSolutionForBestXYZ (WORD *solutionptr, int len, BOOL do3x3x3adjustment)
{ int k;
  BOOL adjustmentdone;
  DWORD i,j,n,axis,slice,rot;

  if ((N & 1) == 0) return FALSE; // Does not apply to even cubes.
  adjustmentdone = FALSE;
  for (j = 0; j < 3; j++)
  { if ((n = (BestXYZ[j]+1) & 3) == 0) continue;
    for (k = 0; k < len; k++)
    { rot = solutionptr[k];
      axis = (rot >> 2) & 3;
      slice = rot >> 4;
      if (do3x3x3adjustment) if (slice == 2) slice = N1;
      rot &= 3;
      for (i = 0; i < n; i++)
      { switch (j)
        { case 0: if (axis == AxisL) { axis = AxisO; slice = N1-slice; } else if (axis == AxisO) { axis = AxisL; rot = -(long)rot & 3; } break;
          case 1: if (axis == AxisL) { axis = AxisV; } else if (axis == AxisV) { axis = AxisL; slice = N1-slice; rot = -(long)rot & 3; } break;
          case 2: if (axis == AxisV) { axis = AxisO; slice = N1-slice; } else if (axis == AxisO) { axis = AxisV; rot = -(long)rot & 3; } break;
        }
      }
      solutionptr[k] = (WORD)((slice << 4) + (axis << 2) + rot);
    }
    adjustmentdone = TRUE;
    do3x3x3adjustment = FALSE;
  }
  return adjustmentdone;
} // AdjustSolutionForBestXYZ

/********************************************************/
static BYTE *Extract3x3x3Cube (BYTE *resultptr)
{ DWORD face,x,y,index[3];

  index[0] = 0; index[1] = HalfN; index[2] = N1;
  for (face = 0; face < 6; face++) for (y = 0; y < 3; y++) for (x = 0; x < 3; x++) *resultptr++ = GetColour(face,index[x],index[y]);
  return resultptr - 6*3*3;
} // Extract3x3x3Cube

/********************************************************/
static void SolveOFaceCentreSlice (BYTE thecolour)
{ BOOL changed1,changed2;
  DWORD i,j,k,numcorrect,turnskept[3],attempt1face[3],attempt1slice[3],attempt2axis[3],attempt2slice[3],attempt3face[2],attempt3slice[2],attempt4slice[3];
  // Make a slice running from V to A of centre facelets. On even cubes, this will be the slice in the O-face directly right of the centre.

  attempt1slice[0] = HalfN1; attempt1face[0] = FaceR;
  attempt1slice[1] = HalfN1; attempt1face[1] = FaceB;
  attempt1slice[2] = HalfN;  attempt1face[2] = FaceL;
  attempt2slice[0] = N1;     attempt2axis[0] = AxisL;
  attempt2slice[1] = N1;     attempt2axis[1] = AxisO;
  attempt2slice[2] = 0;      attempt2axis[2] = AxisL;
  attempt3slice[0] = HalfN;  attempt3face[0] = FaceV;
  attempt3slice[1] = HalfN1; attempt3face[1] = FaceA;
  attempt4slice[0] = 0;
  attempt4slice[1] = N1;

  do // In the few cases the first iteration does not solve it, the second iteration will almost always solve it with a few extra turns, and so on.
  { numcorrect = 0;
    changed2 = FALSE;
    // See if we can place single facelets in one turn each.
    for (i = 1; i < N1; i++)
    { if (GetColour(FaceO,HalfN,i) == thecolour)
      { if (++numcorrect == N2) return; } else
      { for (j = 0; j < 3; j++)
        { if (GetColour(attempt1face[j],attempt1slice[j],i) == thecolour)
          { DoTurn(AxisV,i,j+1);
            if (++numcorrect == N2) return;
            changed2 = TRUE;
            break;
          }
        }
      }
    }
    // See if we can place single facelets in one turn each after a turn of the R, B, or L face.
    turnskept[0] = turnskept[1] = turnskept[2] = 0;
    for (k = 1; k < 4; k++)
    { for (j = 0; j < 3; j++)
      { changed1 = FALSE;
        DoTurn(attempt2axis[j],attempt2slice[j],k-turnskept[j]);
        for (i = 1; i < N1; i++)
        { if (GetColour(FaceO,HalfN,i) == thecolour) continue;
          if (GetColour(attempt1face[j],attempt1slice[j],i) == thecolour)
          { DoTurn(AxisV,i,j+1);
            if (++numcorrect == N2) return;
            changed1 = changed2 = TRUE;
          }
        }
        if (changed1) turnskept[j] = k; else DoTurn(attempt2axis[j],attempt2slice[j],-(long)(k-turnskept[j]) & 3); // The DoTurn() is actually an undo, happening literally at most once or twice.
      }
    }
    // After an O turn, see if we can place single facelets in one turn each by L-slice turns, taking things out of the V or A faces.
    DoTurn(AxisO,0,1);
    for (i = 1; i < N1; i++)
    { if (GetColour(FaceO,i,HalfN) == thecolour) continue;
      for (j = 0; j < 2; j++)
      { if (GetColour(attempt3face[j],i,attempt3slice[j]) == thecolour)
        { DoTurn(AxisL,i,(j << 1) + 1);
          if (++numcorrect == N2) { DoTurn(AxisO,0,3); return; }
          changed2 = TRUE;
          break;
        }
      }
    }
    // Do a V or A turn first.
    turnskept[0] = turnskept[1] = turnskept[2] = 0;
    for (k = 1; k < 4; k++)
    { for (j = 0; j < 2; j++)
      { changed1 = FALSE;
        DoTurn(AxisV,attempt4slice[j],k-turnskept[j]);
        for (i = 1; i < N1; i++)
        { if (GetColour(FaceO,i,HalfN) == thecolour) continue;
          if (GetColour(attempt3face[j],i,attempt3slice[j]) == thecolour)
          { DoTurn(AxisL,i,(j << 1) + 1);
            if (++numcorrect == N2) { DoTurn(AxisO,0,3); return; }
            changed1 = changed2 = TRUE;
          }
        }
        if (changed1) turnskept[j] = k; else DoTurn(AxisV,attempt4slice[j],-(long)(k-turnskept[j]) & 3); // The DoTurn() is actually an undo, happening literally at most once or twice.
      }
    }
    DoTurn(AxisO,0,3); // The DoTurn() may or may not actually be an undo.
  } while (changed2);

  // This point will never be reached. It would mean that missing facelets are somewhere in the O face, because we handle all other faces in the code above.
  // There are 4 of each type of facelet, so for a missing one, there are always 4 facelets that can be placed there. Clearly, if all 4 of them were in the
  // O face, then one of them would actually be in the correct spot, so there is no missing one then. A contradiction, so not all 4 can be in the O face.
  // So at least one has to be in another face but we have already handled all other faces. So we never reach this point.

} // SolveOFaceCentreSlice

/********************************************************/
static void SolveOFaceRemainingSlices (BYTE thecolour)
{ BOOL changed;
  char formula[3];
  DWORD i,j,k,maxk,face,maxface,x,y,xx,slice,lastnum,num,maxnum,numcorrect,faces[6];
  // We create vertical slices for the O face one by one in the V face.

  formula[2] = '\0';
  // Try them in the cheapest order.
  faces[0] = FaceV;
  faces[1] = FaceO;
  faces[2] = FaceB;
  faces[3] = FaceL;
  faces[4] = FaceR;
  faces[5] = FaceA;
  for (slice = 1; slice < N1; slice++)
  { // Find the best slice from all faces and turn it so that it is vertically in the V face.
    if (slice == HalfN) continue; // Already done.
    maxnum = 0;
    for (face = 0; face < 6; face++)
    { for (k = 0; k < 4; k++)
      { for (i = 1, num = 0; i < N1; i++)
        { switch (k)
          { case 0: x = slice; y = i; break;
            case 1: x = i; y = slice; break;
            case 2: x = N1-slice; y = i; break;
            case 3: x = i; y = N1-slice; break;
          }
          if (GetColour(faces[face],x,y) == thecolour) num++;
        }
        if (num > maxnum)
        { maxk = k;
          maxnum = num;
          maxface = faces[face];
        }
        if (faces[face] == FaceO) break; // Only do k = 0 for the O face.
      }
    }
    // Do the turns to place it vertically in the V face.
    if (OFaceSliceTurns[maxface][maxk]) DoFormula(OFaceSliceTurns[maxface][maxk]);
    if (maxface == FaceL) { DoTurn(AxisO,slice,1); DoFormula("V"); } else
    if (maxface == FaceR) { DoTurn(AxisO,slice,3); DoFormula("V"); } else
    if (maxface == FaceB) { DoTurn(AxisL,slice,1); } else
    if (maxface == FaceO) { DoTurn(AxisL,slice,3); } else
    if (maxface == FaceA) { DoTurn(AxisO,slice,2); DoFormula("V"); }

placemore:
    // See if we can place single facelets in one turn each from the L, A, R faces.
    for (i = 1, numcorrect = 0; i < N1; i++)
    { if (GetColour(FaceV,slice,i) == thecolour)
      { if (++numcorrect == N2) goto slicedone; } else
      { for (j = 0; j < 3; j++)
        { switch (j)
          { case 0: face = FaceL; x = i; y = N1-slice; break;
            case 1: face = FaceA; x = N1-slice; y = i; break;
            case 2: face = FaceR; x = i; y = slice; break;
          }
          if (GetColour(face,x,y) == thecolour)
          { DoTurn(AxisO,N1-i,j+1);
            if (++numcorrect == N2) goto slicedone;
            break;
          }
        }
      }
    }
    // See if we can place single facelets in one turn each after a turn of the L, A, or R face.
    for (i = 1; i < N1; i++)
    { if (GetColour(FaceV,slice,i) == thecolour) continue;
      for (j = 0; j < 3; j++)
      { switch (j)
        { case 0: face = FaceL; x = N1-slice; y = N1-i    ; formula[0] = 'L'; break;
          case 1: face = FaceA; x = N1-i    ; y = N1-slice; formula[0] = 'A'; break;
          case 2: face = FaceR; x = N1-slice; y = i       ; formula[0] = 'R'; break;
        }
        for (k = 0; k < 3; k++)
        { if (GetColour(face,x,y) == thecolour)
          { formula[1] = (char)(k+'1');
            DoFormula(formula);
            goto placemore;
          }
          switch (j)
          { case 0: xx = x; x = y; y = N1-xx; break;
            case 1: // Fall through.
            case 2: xx = x; x = N1-y; y = xx; break;
          }
        }
      }
    }
    // See if we can get something out of the V face itself.
    for (i = 1, k = 0; i < N1; i++)
    { if (GetColour(FaceV,slice,i) == thecolour) continue;
      // We try to put it in the FaceL,i,N-1-slice position so that it can then be placed in a single turn.
      if ((slice != N1-i) && (GetColour(FaceV,N1-i,slice) == thecolour)) { k = N1-i; num = 3; } else
      if ((slice != N1-slice) && (GetColour(FaceV,N1-slice,N1-i) == thecolour)) { if (GetColour(FaceV,slice,N1-i) == thecolour) { k = slice; num = 1; } else { k = N1-i; num = 2; } } else
      if ((slice != i) && (GetColour(FaceV,i,N1-slice) == thecolour)) { k = N1-i; num = 1; }
      if (k)
      { DoTurn(AxisV,0,num);
        DoTurn(AxisO,k,3);
        DoTurn(AxisV,0,4-num);
        goto placemore;
      }
    }
    // Try to place as many as possible from the B face in a single turn after a V' turn. Then try to get as many as possible again after doing a B turn. Then again B. Then again B.
    // Note that we do not actually do any of these turns unless they result in a situation in which we can place something correctly.
    for (j = 0; j < 4; j++)
    { for (i = 1; i < N1; i++)
      { if (GetColour(FaceV,slice,i) == thecolour) continue;
        switch (j)
        { case 0: x = i; y = slice; break;
          case 1: x = N1-slice; y = i; break;
          case 2: x = N1-i; y = N1-slice; break;
          case 3: x = slice; y = N1-i; break;
        }
        if (GetColour(FaceB,x,y) == thecolour) goto foundb;
      }
    }
foundb:
    if (j < 4)
    { if (j) DoTurn(AxisO,N1,4-j);
      num = 0;
      DoTurn(AxisV,0,3);
      do
      { changed = FALSE;
        for (j = lastnum = 0; j < 4; j++)
        { for (i = 1; i < N1; i++)
          { if (GetColour(FaceV,i,N1-slice) == thecolour) continue;
            switch (j-lastnum)
            { case 0: x = i; y = slice; break;
              case 1: x = N1-slice; y = i; break;
              case 2: x = N1-i; y = N1-slice; break;
              case 3: x = slice; y = N1-i; break;
            }
            if (GetColour(FaceB,x,y) == thecolour)
            { if (lastnum != j) { DoTurn(AxisO,N1,4-(j-lastnum)); lastnum = j; }
              DoTurn(AxisL,i,1);
              numcorrect++;
              if ((i < slice) || (i == HalfN)) SliceNumbers[num++] = i; // No need to turn it back if this slice was not yet fixed.
              changed = TRUE;
            }
          }
        }
      } while (changed);
      DoTurn(AxisV,0,1);
      for (i = 0; i < num; i++) DoTurn(AxisL,SliceNumbers[i],3);
      if (numcorrect == N2) goto slicedone;
      goto placemore;
    }
    // See if we can get something out of the O face.
    for (i = 1, k = 0; i < N1; i++)
    { if (GetColour(FaceV,slice,i) == thecolour) continue;
      if (GetColour(FaceO,slice,i) == thecolour) k = slice; else
      if ((N1-i >= slice) && (N1-i != HalfN) && (GetColour(FaceO,N1-i,slice) == thecolour)) k = N1-i; else
      if ((N1-slice >= slice) && (N1-slice != HalfN) && (GetColour(FaceO,N1-slice,N1-i) == thecolour)) k = N1-slice; else
      if ((i >= slice) && (i != HalfN) && (GetColour(FaceO,i,N1-slice) == thecolour)) k = i;
      if (k)
      { DoFormula("O");
        DoTurn(AxisV,k,1);
        DoTurn(AxisL,0,2+(((N & 1)) && (k == HalfN)));
        DoTurn(AxisV,k,3);
        DoFormula("O'");
        goto placemore;
      }
    }
slicedone:
    // Place the slice.
    DoTurn(AxisL,slice,1);
  }
} // SolveOFaceRemainingSlices

/********************************************************/
static void SolveOFace ()
{ BYTE thecolour;
  // Note: We leave the edges until later.

  thecolour = Colours[FaceO];

#ifdef USE4X4X4CODE
  if (N == 4)
  { // We use a more efficient way for the 4x4x4.
    DoASN4Turns(BJW4SolveOFace(thecolour));
    return;
  }
#endif

  SolveOFaceCentreSlice(thecolour);
  SolveOFaceRemainingSlices(thecolour);
} // SolveOFace

/********************************************************/
static BOOL SolveLARFacesAux (DWORD face, DWORD x, DWORD y, DWORD limitation, BYTE thecolour)
{ DWORD numtimes;

  if (face == FaceV) { if (y == limitation) return FALSE; }
  else if (face == FaceA) { if (y >= limitation) return FALSE; }
  else { if (x >= limitation) return FALSE; }
  if (GetColour(face,x,y) != thecolour) return FALSE;
  // Turn it into the B face.
  if (face == FaceL)
  { numtimes = 1 + (((N & 1) == 0) || (x != HalfN));
    DoTurn(AxisL,0,1); // It is located at (N-1-y,x) now.
    DoTurn(AxisV,x,1);
    DoTurn(AxisO,N1,numtimes);
    DoTurn(AxisV,x,3);
    DoTurn(AxisL,0,3);
  }
  else if (face == FaceA)
  { numtimes = 1 + (((N & 1) == 0) || (y != HalfN));
    DoTurn(AxisV,N1,3); // It is located at (y,N-1-x) now.
    DoTurn(AxisL,y,1);
    DoTurn(AxisO,N1,numtimes);
    DoTurn(AxisL,y,3);
    DoTurn(AxisV,N1,1);
  }
  else if (face == FaceR)
  { numtimes = 1 + (((N & 1) == 0) || (N1-x != HalfN));
    DoTurn(AxisL,N1,3); // It is located at (y,N-1-x) now.
    DoTurn(AxisV,N1-x,3);
    DoTurn(AxisO,N1,numtimes);
    DoTurn(AxisV,N1-x,1);
    DoTurn(AxisL,N1,1);
  }
  else // if (face == FaceV)
  { numtimes = 1 + (((N & 1) == 0) || (N1-y != HalfN));
    DoTurn(AxisV,0,1); // It is located at (N-1-y,x) now.
    DoTurn(AxisL,N1-y,3);
    DoTurn(AxisO,N1,numtimes);
    DoTurn(AxisL,N1-y,1);
    DoTurn(AxisV,0,3);
  }
  return TRUE;
} // SolveLARFacesAux

/********************************************************/
static void SolveLARFaces ()
{ BYTE thecolour;
  BOOL changed1,changed2;
  DWORD i,j,k,x,y,slice,invalid,numtimes,maxxL,maxyA,maxxR,notyV,num,numcorrect,side,faces[3];
  // Note: We leave the edges until later.
  // Solve first slice of L (from the bottom, not counting edges), first slice of A, first slice of R. Then the same for second slices. And so on. We use the V face as a "scratchpad".

#ifdef USE4X4X4CODE
  if (N == 4)
  { // We use a more efficient way for the 4x4x4.
    DoASN4Turns(BJW4SolveLARFaces(Colours));
    return;
  }
#endif

  faces[0] = FaceL;
  faces[1] = FaceA;
  faces[2] = FaceR;

  for (slice = 1; slice < N1; slice++)
  { // On an odd cube, we want the centre of the L face in the V face. That way, it can be treated the same way as the other slices.
    if (((N & 1)) && (slice == HalfN)) while (GetColour(FaceV,HalfN,HalfN) != Colours[faces[0]]) DoTurn(AxisO,HalfN,1);
    for (side = 0; side < 3; side++) // L, A, R.
    { // Find the best slice already in the V face and put it running vertically on the "left". This may require doing a V face turn first.
      thecolour = Colours[faces[side]];
      numcorrect = numtimes = 0;
      for (i = 1, k = 0; i < N1; i++) if (GetColour(FaceV,slice,i) == thecolour) k++;
      if (k > numcorrect) { numcorrect = k; numtimes = 0; }
      for (i = 1, k = 0; i < N1; i++) if (GetColour(FaceV,i,N1-slice) == thecolour) k++;
      if (k > numcorrect) { numcorrect = k; numtimes = 1; }
      for (i = 1, k = 0; i < N1; i++) if (GetColour(FaceV,N1-slice,i) == thecolour) k++;
      if (k > numcorrect) { numcorrect = k; numtimes = 2; }
      for (i = 1, k = 0; i < N1; i++) if (GetColour(FaceV,i,slice) == thecolour) k++;
      if (k > numcorrect) { numcorrect = k; numtimes = 3; }
      if (numtimes) DoTurn(AxisV,0,numtimes);
      if (numcorrect == N2)
      { DoTurn(AxisV,0,3);
        goto slicedone;
      }
      do
      { // Try to get additional facelets out of the L, A, R faces.
        do
        { changed2 = FALSE;
          numtimes = N1-slice + (side == 0);
          for (i = 1; i < numtimes; i++)
          { if (GetColour(FaceV,slice,i) == thecolour) continue;
            for (j = 0; j < 3; j++)
            { switch (j)
              { case 0: x = i; y = N1-slice; break;
                case 1: x = N1-slice; y = i; break;
                case 2: x = i; y = slice; break;
              }
              if (GetColour(faces[j],x,y) == thecolour) { DoTurn(AxisO,N1-i,j+1); changed2 = TRUE; break; }
            }
          }
          // Do a V2 turn and try to get more out of the L, A, R faces.
          DoTurn(AxisV,0,2);
          for (i = 1; i < numtimes; i++)
          { if (GetColour(FaceV,N1-slice,i) == thecolour) continue;
            for (j = 0; j < 3; j++)
            { switch (j)
              { case 0: x = i; y = slice; break;
                case 1: x = slice; y = i; break;
                case 2: x = i; y = N1-slice; break;
              }
              if (GetColour(faces[j],x,y) == thecolour) { DoTurn(AxisO,N1-i,j+1); changed2 = TRUE; break; }
            }
          }
          if (changed2) DoTurn(AxisV,0,2);
        } while (changed2);
        // Try to get easy ones out of our own V face. Several might be done simultaneously.
        do
        { changed2 = FALSE;
          for (j = 1; j <= 3; j += 2) // For j = 1 and j = 3.
          { for (i = 1, numcorrect = numtimes = 0; i < N1; i++)
            { if (GetColour(FaceV,N1-slice,i) == thecolour) { numcorrect++; continue; }
              switch (j)
              { case 1: x =    i; y =    slice; break;
                case 3: x = N1-i; y = N1-slice; break;
              }
              if ((x != N1-slice) && (GetColour(FaceV,x,y) == thecolour)) SliceNumbers[numtimes++] = x;
            }
            if (numtimes)
            { for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],1);
              DoTurn(AxisV,0,4-j);
              for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],3);
              DoTurn(AxisV,0,j);
              changed2 = TRUE;
            }
            if (numcorrect + numtimes == N2)
            { // Our slice must be running horizontally for where we jump to.
              DoTurn(AxisV,0,1);
              goto slicedone;
            }
          }
        } while (changed2);
        // Do a V turn to orient the slice horizontally and try to get more out of the B face.
        DoTurn(AxisV,0,1);
        maxxL = N-slice;
        maxyA = N1-slice + (side <= 1);
        maxxR = N1-slice + (side == 0);
        notyV = N1-slice;
        do
        { changed1 = FALSE;
          for (j = 0; j < 4; j++)
          { if (j) DoTurn(AxisO,N1,3);
            do
            { changed2 = FALSE;
              // Try putting several facelets in place simultaneously.
              num = 1;
              invalid = (DWORD)(-1);
              for (i = 1, numcorrect = numtimes = 0; i < N1; i++)
              { if (GetColour(FaceV,i,N1-slice) == thecolour) { numcorrect++; continue; }
                if ((i != invalid) && (GetColour(FaceB,i,slice) == thecolour))
                { SliceNumbers[numtimes++] = i;
                  if (i == slice)
                  { invalid = N1-slice;
                    num = 3;
                  }
                  else if (i == N1-slice) invalid = slice;
                }
              }
              if (numtimes)
              { for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],1);
                DoTurn(AxisV,0,num);
                for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],3);
                DoTurn(AxisV,0,-(long)num & 3);
                changed1 = changed2 = TRUE;
              }
              if (numcorrect + numtimes == N2) goto slicedone;
            } while (changed2);
          }
          RemoveUndesiredEndTurns(AxisO,N1);
        } while (changed1);
        // Missing ones are somewhere in the side faces (L, A, R, V). Get one of them out into the B face. Then use the above code to place it.
        for (i = 1; i < N1; i++)
        { if (GetColour(FaceV,i,N1-slice) == thecolour) continue;
          // Try all possible locations where it can be.
          if (SolveLARFacesAux(FaceR,slice,N1-i,maxxR,thecolour)) break;
          if (SolveLARFacesAux(FaceR,N1-i,N1-slice,maxxR,thecolour)) break;
          if (SolveLARFacesAux(FaceR,N1-slice,i,maxxR,thecolour)) break;
          if (SolveLARFacesAux(FaceR,i,slice,maxxR,thecolour)) break;

          if (SolveLARFacesAux(FaceA,N1-i,N1-slice,maxyA,thecolour)) break;
          if (SolveLARFacesAux(FaceA,N1-slice,i,maxyA,thecolour)) break;
          if (SolveLARFacesAux(FaceA,i,slice,maxyA,thecolour)) break;
          if (SolveLARFacesAux(FaceA,slice,N1-i,maxyA,thecolour)) break;

          if (SolveLARFacesAux(FaceL,slice,i,maxxL,thecolour)) break;
          if (SolveLARFacesAux(FaceL,N1-i,slice,maxxL,thecolour)) break;
          if (SolveLARFacesAux(FaceL,N1-slice,N1-i,maxxL,thecolour)) break;
          if (SolveLARFacesAux(FaceL,i,N1-slice,maxxL,thecolour)) break;

          if (SolveLARFacesAux(FaceV,slice,i,notyV,thecolour)) break;
          if (SolveLARFacesAux(FaceV,N1-i,slice,notyV,thecolour)) break;
          if (SolveLARFacesAux(FaceV,N1-slice,N1-i,notyV,thecolour)) break;
        }
        DoTurn(AxisV,0,1);
      } while (TRUE);
slicedone:
      // Turn it into the R face. After doing all this 3 times, all 3 slices will be in the correct place.
      DoTurn(AxisO,slice,1);
    }
  }
} // SolveLARFaces

/********************************************************/
static void SolveBVFaces ()
{ WORD *solptr;
  BYTE thecolour;
  BOOL changed,dodiagonal;
  DWORD i,j,k,m,y,xb,yb,sb,slice,numtimes,numalreadythere,numcorrect,maxnum,bestj,bestk,bestslice;
  // Note: We leave the edges until later.

  thecolour = Colours[FaceV];

#ifdef USE4X4X4CODE
  if (N == 4)
  { // We use a more efficient way for the 4x4x4.
    DoASN4Turns(BJW4SolveBVFaces(thecolour));
    return;
  }
#endif

  // Step 1: Build a slice in the V face that belongs in the B face. Then move it into the B face.
  // This is cheap and can place a lot of facelets, but most of the time it will not be able to take care of everything.
  DoNotCombine = TRUE;
  for (slice = 1; slice < N1; slice++)
  { // We are going to build FaceB,slice,i. First count how many are already there.
    solptr = SolutionPtr;
    for (i = 1, numalreadythere = 0; i < N1; i++) if (GetColour(FaceB,slice,i) != thecolour) numalreadythere++;
    // Now find the best candidate in the V face.
    for (i = 1, numcorrect = 0; i < N1; i++) if (GetColour(FaceV,i,N1-slice) != thecolour) numcorrect++;
    bestslice = 0; maxnum = numcorrect;
    for (i = 1, numcorrect = 0; i < N1; i++) if (GetColour(FaceV,N1-slice,i) != thecolour) numcorrect++;
    if (numcorrect > maxnum) { bestslice = 1; maxnum = numcorrect; }
    if (((N & 1) == 0) || (slice != HalfN)) // On an odd cube, the centre slice has only 2 possibilities.
    { for (i = 1, numcorrect = 0; i < N1; i++) if (GetColour(FaceV,i,slice) != thecolour) numcorrect++;
      if (numcorrect > maxnum) { bestslice = 2; maxnum = numcorrect; }
      for (i = 1, numcorrect = 0; i < N1; i++) if (GetColour(FaceV,slice,i) != thecolour) numcorrect++;
      if (numcorrect > maxnum) { bestslice = 3; maxnum = numcorrect; }
    }
    if (bestslice) DoTurn(AxisV,0,bestslice); // Position the slice as V,i,N-1-slice.
    // Now move facelets from the B face into it. Then do V2 and try to move more. Then move it into the B face.
    memset(SliceNumbers,0,sizeof(DWORD)*N);
    for (j = 0, y = N1-slice; j < 2; j++)
    { changed = FALSE;
      if (j == 1) DoTurn(AxisV,0,2);
      for (i = slice; i < N1; i++)
      { if (SliceNumbers[i]) continue; // We can turn each slice only once.
        if ((GetColour(FaceV,i,y) == thecolour) && (GetColour(FaceB,i,N1-y) != thecolour))
        { DoTurn(AxisL,i,1);
          SliceNumbers[i] = 1;
          maxnum++;
          changed = TRUE;
        }
      }
      y = slice;
    }
    // After all this work, we may find that the slice that was in the B face to start with was at least as good. Fortunately, this happens very rarely.
    if (numalreadythere >= maxnum)
    { // The original B face slice was at least as good. Undo.
      UndoTurns(solptr);
      continue;
    }
    // Now put it in the B face.
    if (SliceNumbers[slice])
    { // Our "transport" is already in the V face.
      DoTurn(AxisV,0,3);
    } else
    { // Our "transport" is not there yet. Normally, we would have to (1) put the current slice aside, (2) fetch the transport, (3) enter the transport, and (4) transport.
      // One facelet would get messed up if we did not put the current slice aside (step 1). However, if it gets replaced by one that is at least as good, then we do not have to step aside.
      numtimes = 3; y = slice;
      if (!changed) { DoTurn(AxisV,0,2); numtimes = 1; y = N1-slice; } // Nothing was placed in the second iteration, so undo the V2.
      if ((GetColour(FaceV,slice,y) == thecolour) || (GetColour(FaceB,slice,N1-y) != thecolour))
      { DoTurn(AxisL,slice,1);
        DoTurn(AxisV,0,numtimes);
      } else
      { DoTurn(AxisV,0,4-numtimes);
        DoTurn(AxisL,slice,1);
        DoTurn(AxisV,0,2);
      }
      SliceNumbers[slice] = 1;
    }
    for (i = 1; i < N1; i++) if (SliceNumbers[i]) DoTurn(AxisL,i,3);
  }
  DoNotCombine = FALSE;

  // Step 2: Place the remaining facelets. This may require a turn of the B face first. We distinguish between facelets that lie on the diagonals and ones that do not lie on the diagonals.
  do
  { changed = FALSE;
    for (m = 0; m < 2; m++)
    { // m = 0: Find the best slice.
      // m = 1: Actually place the best slice.
      if (m == 0) maxnum = 0;
      for (j = 0; j < 4; j++)
      { for (k = 1; k < 5; k += 2)
        { for (slice = 1; slice < N1; slice++)
          { if (m == 1)
            { j = bestj;
              k = bestk;
              slice = bestslice;
            }
            for (i = 1, numtimes = 0; i < N1; i++)
            { if (((N & 1)) && (slice == HalfN) && (i == HalfN)) continue;
              sb = i;
              switch (j)
              { case 0: xb = i; yb = slice; break;
                case 1: xb = slice; yb = N1-i; break;
                case 2: xb = N1-i; yb = N1-slice; break;
                case 3: xb = N1-slice; yb = i; break;
              }
              if (k == 3) { xb = N1-xb; yb = N1-yb; sb = N1-sb; }
              // Make sure not to do diagonals here.
              if ((sb != slice) && (GetColour(FaceV,slice,i) != thecolour) && (GetColour(FaceB,xb,yb) == thecolour))
              { if (m == 1) SliceNumbers[numtimes] = sb;
                numtimes++;
              }
            }
            if (m == 0)
            { if (numtimes > maxnum)
              { bestj = j;
                bestk = k;
                bestslice = slice;
                maxnum = numtimes;
              }
            } else
            { if (numtimes)
              { if (j) DoTurn(AxisO,N1,j);
                // If we are placing only one and it can be placed as a diagonal, then use a shorter way to place it.
                dodiagonal = FALSE;
                if ((numtimes == 1) && (SliceNumbers[0] == N1-slice))
                { for (i = 1; i < N1; i++) if (GetColour(FaceV,slice,i) != thecolour) y = i;
                  dodiagonal = ((y == slice) || (y == N1-slice));
                }
                // Pieces placed on a diagonal take 8 turns. They are placed only one at a time. Other pieces, though, can be placed simultaneously. Given n pieces, this takes 4n+6 turns.
                if (dodiagonal)
                { DoTurn(AxisO,N1,2);
                  DoTurn(AxisL,slice,3);
                  DoTurn(AxisO,N1,4-k);
                  DoTurn(AxisL,slice,1);
                  DoTurn(AxisO,N1,4-k);
                  DoTurn(AxisL,slice,3);
                  DoTurn(AxisO,N1,2);
                  DoTurn(AxisL,slice,1);
                } else
                { DoTurn(AxisL,slice,3);
                  for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],3);
                  DoTurn(AxisO,N1,k);
                  for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],1);
                  DoTurn(AxisO,N1,4-k);
                  DoTurn(AxisL,slice,1);
                  DoTurn(AxisO,N1,k);
                  for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],3);
                  DoTurn(AxisO,N1,4-k);
                  for (i = 0; i < numtimes; i++) DoTurn(AxisL,SliceNumbers[i],1);
                }
                changed = TRUE;
              }
              goto donebest;
            }
          }
        }
      }
    }
donebest: ;
  } while (changed);
} // SolveBVFaces

/********************************************************/
static void FindBestEdgeInB (DWORD numdone, DWORD *bestface, BYTE *bestcolourpair)
{ BYTE cp,maxcp;
  BOOL skipface[4];
  DWORD i,face,maxface,num,maxnum,faces[4],cpcounts[4][36];

  faces[0] = FaceV;
  faces[1] = FaceL;
  faces[2] = FaceA;
  faces[3] = FaceR;
  memset(cpcounts,0,sizeof(cpcounts));
  memset(skipface,0,sizeof(skipface));
  if (numdone >= 1)
  { // This means BA is done.
    skipface[2] = TRUE;
    if (numdone >= 2)
    { // This means BA and BV are done.
      skipface[0] = TRUE;
    }
  }
  for (face = maxnum = 0; face < 4; face++)
  { if (skipface[face]) continue;
    for (i = 1; i < N1; i++)
    { cp = GetColoursEdgeB(i,faces[face],FALSE);
      num = ++cpcounts[face][cp];
      if (num > maxnum)
      { maxcp = cp;
        maxnum = num;
        maxface = face;
      }
    }
  }
  *bestface = faces[maxface];
  *bestcolourpair = maxcp;
} // FindBestEdgeInB

/********************************************************/
static void SolveEdges1Through8 ()
{ BYTE c1,c2,cc1,cc2;
  char *fptr,*minfptr;
  struct EDGESOLVER *es;
  DWORD i,j,x1,x2,y1,y2,idx,edge,face1,face2,slice,minslice,numturns,numcorrect,maxnum,len,minlen,cpcounts[36];

  // Note: I probably would have done things differently if I had had more experience with cubes of higher order than 5x5x5 before I wrote this code.

#ifdef USE4X4X4CODE
  if (N == 4)
  { // We use a more efficient way for the 4x4x4.
    DoASN4Turns(BJW4SolveEdges1Through8());
    return;
  }
#endif

  for (edge = 0; edge < 8; edge++)
  { // Fix the edge that is now in the VB position. Match everything to the combination that occurs most in VB.
    memset(cpcounts,0,sizeof(cpcounts));
    for (slice = 1, maxnum = 0; slice < N1; slice++)
    { numcorrect = ++cpcounts[((cc1=GetColour(FaceV,slice,0))-1)*6+((cc2=GetColour(FaceB,slice,0))-1)];
      if (numcorrect > maxnum)
      { c1 = cc1;
        c2 = cc2;
        maxnum = numcorrect;
      }
    }
    do
    { for (slice = 1, numcorrect = 0; slice < N1; slice++)
      { for (i = 0; i < 4; i++)
        { switch (i)
          { case 0: face1 = FaceV; y1 =  0; face2 = FaceB; y2 =  0; break;
            case 1: face1 = FaceB; y1 = N1; face2 = FaceA; y2 =  0; break;
            case 2: face1 = FaceA; y1 = N1; face2 = FaceO; y2 = N1; break;
            case 3: face1 = FaceO; y1 =  0; face2 = FaceV; y2 = N1; break;
          }
          if ((GetColour(face1,slice,y1) == c1) && (GetColour(face2,slice,y2) == c2))
          { if (i) DoTurn(AxisL,slice,i);
            if (++numcorrect == N2) goto edgedone;
            break;
          }
        }
      }
      // The remainder has to come from flipped edgelets in the horizontal edges and from the R and L faces. Determine the cheapest way of getting one or more.
      minlen = (DWORD)(-1);
      // Try to find flipped edgelets.
      for (slice = 1; slice < N1; slice++)
      { for (i = 0; i < 4; i++)
        { switch (i)
          { case 0: face1 = FaceV; y1 =  0; face2 = FaceB; y2 =  0; break;
            case 1: face1 = FaceB; y1 = N1; face2 = FaceA; y2 =  0; break;
            case 2: face1 = FaceA; y1 = N1; face2 = FaceO; y2 = N1; break;
            case 3: face1 = FaceO; y1 =  0; face2 = FaceV; y2 = N1; break;
          }
          if ((GetColour(face1,slice,y1) == c2) && (GetColour(face2,slice,y2) == c1))
          { len = 4;
            if (i == 0) len = 5;
            if (len < minlen)
            { minlen = len;
              minslice = slice;
              minfptr = (char *)(size_t)i;
            }
          }
        }
      }
      // Try to find edgelets in the R and L faces.
      for (i = 0, es = EdgeSolver; i < 8; i++, es++)
      { for (slice = 1; slice < N1; slice++)
        { x1 = slice; if (es->codes[0][0] != 1) x1 = es->codes[0][0];
          y1 = slice; if (es->codes[0][1] != 1) y1 = es->codes[0][1];
          x2 = slice; if (es->codes[1][0] != 1) x2 = es->codes[1][0];
          y2 = slice; if (es->codes[1][1] != 1) y2 = es->codes[1][1];
          cc1 = GetColour(es->faces[0],x1,y1);
          cc2 = GetColour(es->faces[1],x2,y2);
          if ((cc1 == c2) && (cc2 == c1)) idx = 0; else if ((cc1 == c1) && (cc2 == c2)) idx = 1; else continue;
          for (j = 0; (j < 3) && ((fptr = es->formulas[idx][j])) && (es->safeedges[idx][j] < edge); j++) ;
          if ((j < 3) && (fptr))
          { if ((len = (DWORD)((strlen(fptr) + 1) >> 1)) < minlen)
            { minlen = len;
              minfptr = fptr;
            }
          }
        }
      }
      // Use the cheapest way to get more available for the "1 slice turn" code above.
      if ((size_t)minfptr <= 3)
      { // Flipped edgelet.
        i = (DWORD)(size_t)minfptr;
        if (i == 0)
        { DoTurn(AxisL,minslice,3);
          // If there are more flipped ones in VB, then get those out to be flipped as well.
          for (j = minslice+1; j < N1; j++) if ((GetColour(FaceV,j,0) == c2) && (GetColour(FaceB,j,0) == c1)) DoTurn(AxisL,j,3);
        }
        if (i == 3) DoFormula("O2A2O2A2"); else DoFormula("A2O2A2O2");
      } else
      { // From the R or L face.
        DoFormula(minfptr);
      }
    } while (TRUE);
edgedone:
    // Turn it into a safe place. The first 3 are turned into the L face, the next 3 into the R face, the 7th is put in the L face, the 8th in the R face.
    if ((edge < 3) || (edge == 6))
    { slice = 0;
      numturns = 3;
    } else
    { slice = N1;
      numturns = 1;
    }
    if (edge >= 6) DoTurn(AxisL,slice,1); // L  or R'.
    DoTurn(AxisO,N1,numturns);            // B  or B'.
    DoTurn(AxisL,slice,3);                // L' or R.
    DoTurn(AxisO,N1,4-numturns);          // B' or B.
  }
  // Restore the slices.
  c1 = Colours[FaceV];
  for (slice = 1; slice < N1; slice++) while (GetColour(FaceV,slice,1) != c1) DoTurn(AxisL,slice,1);
  DoFormula("B V2A2"); // To put the remaining ones in the B face. We use the B face as our "main" face from now on.
} // SolveEdges1Through8

/********************************************************/
static void SolveEdges9Through12 ()
{ BYTE thecolourpair;
  BOOL changed1,changed2;
  DWORD i,j,edge,face,slice,numturns,numcorrect,faces[5];

  // Edges 9 and 10: BA and BV.
  faces[0] = FaceV;
  faces[1] = faces[2] = FaceL;
  faces[3] = faces[4] = FaceR;
  for (edge = 8; edge < 10; edge++)
  { LastEdge3Cycle = (DWORD)(-1);
    FindBestEdgeInB(edge-8,&face,&thecolourpair);
    // Put it in BA. If this is the second iteration, then we also have to move BA somewhere safe at the same time.
    // When we start on edge 10 in BA, the other 2 unfixed edges have to be in BR and BL.
    if (edge == 8)
    { numturns = 0; if (face == FaceR) numturns = 1; else if (face == FaceV) numturns = 2; else if (face == FaceL) numturns = 3;
      if (numturns) DoTurn(AxisO,N1,numturns);
    } else
    { // Move the best face to BA, while making sure the other 2 unfixed edges are in BR and BL.
      if (face == FaceV)   DoFormula("B2"); else
      if (face == FaceR)   DoFormula("L B'L'"); else
      /* (face == FaceL)*/ DoFormula("R'B R ");
    }
    do
    { changed1 = FALSE;
      do
      { changed2 = FALSE;
        for (i = 0; i < 5; i++)
        { // Try placing from VB, BL, LB, BR, RB to BA, respectively.
          for (slice = 1, numturns = 0; slice < N1; slice++) if (GetColoursEdgeB(slice,faces[i],((i & 1) == 0)) == thecolourpair) SliceNumbers[numturns++] = slice;
          if (numturns)
          { DoEdge3Cycle(i,numturns);
            changed2 = TRUE;
          }
        }
      } while (changed2);
      // There might be some in BA itself that are flipped. Move them to one of the side faces. (We choose to move them to RB.)
      for (slice = 1, numturns = 0; slice < N1; slice++) if (GetColoursEdgeB(slice,FaceA,TRUE) == thecolourpair) SliceNumbers[numturns++] = slice;
      if (numturns)
      { DoEdge3Cycle(1,numturns);
        changed1 = TRUE;
      } else
      { // Finally, there might be some in BV that have to go to BA. We do not have a formula for that, so we simply flip the entire BV edge.
        // This does not apply when doing edge 10 because BV is fixed then already.
        for (slice = 1, numturns = 0; slice < N1; slice++)
        { if (GetColoursEdgeB(slice,FaceV,FALSE) == thecolourpair)
          { DoFormula("V'B L'B'");
            changed1 = TRUE;
            break;
          }
        }
      }
    } while (changed1);
    // The last formula was almost always a 3-cycle on the edges. In case it was the one that ends in A', we do not need that final A' turn.
    if (LastEdge3Cycle == 0) RemoveUndesiredEndTurns(AxisV,N1);
  }

#ifdef USE4X4X4CODE
  if (N == 4)
  { // We use a more efficient way for the 4x4x4.
    DoASN4Turns(BJW4SolveEdges11And12(0xff,&Solution,&SolutionPtr));
    DoASN4Turns(BJW4SolveEdges11And12(Get3x3x3Parity(Extract3x3x3Cube(InputFor3x3x3)),&Solution,&SolutionPtr));
    return;
  }
#endif

  // Edge 11: BL.
  if ((N & 1))
  { // On odd cubes, to avoid problems, we adjust to the centre edgelet.
    thecolourpair = GetColoursEdgeB(HalfN,FaceL,FALSE);
  } else
  { FindBestEdgeInB(edge-8,&face,&thecolourpair);
    if (face == FaceR) DoTurn(AxisO,N1,2);
  }
  do
  { do
    { // BR places all the ones it can in BL, while BL sends all its own flipped edgelets to BR.
      // Note that we cannot do slice and N-1-slice simultaneously, so in that case we have to do it in two steps.
      changed1 = FALSE;
      for (slice = 1, numturns = 0; slice < N1; slice++)
      { // BR placing in BL.
        if (GetColoursEdgeB(slice,FaceR,TRUE) == thecolourpair)
				{ for (j = 0; (j < numturns) && (SliceNumbers[j] != slice); j++) ;
					if (j == numturns) SliceNumbers[numturns++] = N1-slice;
				}
				// BL sending flipped edgelets to BR. Note that some of these may already happen as a result of "BR placing in BL".
				if (GetColoursEdgeB(slice,FaceL,TRUE) == thecolourpair)
				{ for (j = 0; (j < numturns) && (SliceNumbers[j] != slice) && (SliceNumbers[j] != N1-slice); j++) ;
					if (j == numturns) SliceNumbers[numturns++] = N1-slice;
				}
			}
			if (numturns)
			{ for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],3);
				DoFormula("B2");
				for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],3);
				DoFormula("B2R2");
				for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],3);
				DoFormula("R2");
				for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,N1-SliceNumbers[slice],3);
				DoFormula("B2");
				for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,N1-SliceNumbers[slice],1);
				DoFormula("B2");
				for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],2);
				changed1 = TRUE;
			}
		} while (changed1);
    for (slice = 1, numcorrect = 0; slice < N1; slice++) if (GetColoursEdgeB(slice,FaceL,FALSE) == thecolourpair) numcorrect++;
    if (numcorrect == N2) break; // We will always break either the first or the second time we get here.
    // Flip BR and use the code above to send the flipped ones to BL. These are ones BR already had and ones that BL sent. So after the code above places them, we are done.
    DoFormula("R'B V'B'");
  } while (TRUE);

  // Edge 12: BR. Some may be flipped. We can flip one set or the opposite set. To save parity fixing in the next phase, we decide based on the 3x3x3 parity.
  thecolourpair = GetColoursEdgeB(HalfN,FaceR,FALSE);
  if ((Get3x3x3Parity(Extract3x3x3Cube(InputFor3x3x3)) & 2)) // Note that on valid odd cubes, we will always get a parity of 0.
  { // Flip should follow the opposite orientation.
    thecolourpair = (thecolourpair % 6) * 6 + (thecolourpair / 6);
  }
  for (slice = 1, numturns = 0; slice < HalfN; slice++) if (GetColoursEdgeB(slice,FaceR,TRUE) == thecolourpair) SliceNumbers[numturns++] = slice;
  if (numturns)
  { for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],2);
    DoFormula("L2B2");
    for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,N1-SliceNumbers[slice],1);
    DoFormula("B2");
    for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],1);
    DoFormula("B2");
    for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],3);
    DoFormula("B2R2");
    for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],3);
    DoFormula("R2");
    for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,N1-SliceNumbers[slice],3);
    DoFormula("L2");
    for (slice = 0; slice < numturns; slice++) DoTurn(AxisV,SliceNumbers[slice],2);
  }
} // SolveEdges9Through12

/********************************************************/
static void SolveEdges ()
{ // Remove the final L-slice turns from the previous phase because we are going to do L-slice turns here.
  RemoveUndesiredEndTurns(AxisL,(DWORD)(-1));
  SolveEdges1Through8();
  SolveEdges9Through12();
} // SolveEdges

/********************************************************/
static void SolveParity ()
{ DWORD slice;

  // Thanks to what we did at the end of SolveEdges9Through12(), we can only have a swap parity problem here (parity = 1) and only on even cubes.
  if (Get3x3x3Parity(Extract3x3x3Cube(InputFor3x3x3)) == 0) return;  // This includes the 4x4x4 since its optimised code has already fixed all parity problems.
  for (slice = 1; slice < HalfN; slice++) DoTurn(AxisV,N1-slice,2); // Chosen this way so that hopefully a few turns cancel out against the last step of solving the edges.
  for (slice = 1; slice < HalfN; slice++) DoTurn(AxisL,slice,2);
  DoTurn(AxisV,0,2);
  for (slice = 1; slice < HalfN; slice++) DoTurn(AxisL,slice,2);
  DoTurn(AxisV,0,2);
  for (slice = 1; slice < HalfN; slice++) DoTurn(AxisL,slice,2);
  for (slice = 1; slice < HalfN; slice++) DoTurn(AxisV,N1-slice,2);
  Extract3x3x3Cube(InputFor3x3x3);
} // SolveParity

/********************************************************/
static void SolveAs3x3x3 (int *len)
{ int i;
  WORD rotationlist[64];
  BOOL done3x3x3adjustment;
  DWORD code,axis,slice,numtimes;

  Get3x3x3Parity(InputFor3x3x3); // So that the 3x3x3 solver has the current situation.
  *len = BJWSolve3CubeFromRubix(rotationlist,3);
  if (*len < 0) return; // This means the user did not have, or did not want to create, a valid BJWSOLVE.333.
  done3x3x3adjustment = AdjustSolutionForBestXYZ(rotationlist,*len,TRUE);
  // Append it to the solution, converting it to this NxNxN cube if necessary.
  for (i = 0; i < *len; i++)
  { code = rotationlist[i];
    axis = (code >> 2) & 3;
    slice = code >> 4;
    numtimes = code & 3;
    if (!done3x3x3adjustment) if (slice == 2) slice = N1;
    if (axis == AxisO) slice = N1-slice; // Because DoTurn() converts it back again.
    DoTurn(axis,slice,numtimes);
  }
} // SolveAs3x3x3

/********************************************************/
static int BJWSolveNCubeFromRubix ()
{ BYTE t;
  int len;
  BOOL solved,try24;
  DWORD i,x,y,z,bestlen,face;

  // Check if the cube is already solved.
  for (face = 0, solved = TRUE; face < 6; face++) for (y = 0; y < N; y++) for (x = 0; x < N; x++) if (GetColour(face,x,y) != Colours[face]) { solved = FALSE; goto checkdone; }
checkdone:
  if (solved) return 0;


  // For cubes up to 25x25x25, we try all 24 possible orientations of the cube.
  try24 = (N <= 25);
  bestlen = (DWORD)(-1);
  BestXYZ[0] = BestXYZ[1] = BestXYZ[2] = 3; // This way there will be no adjustment when (!try24).
  for (x = 0; x < 2; x++)
  { if (try24) { t = Colours[3]; Colours[3] = Colours[5]; Colours[5] = Colours[2]; Colours[2] = Colours[4]; Colours[4] = t; }
    for (y = 0; y < 4; y++)
    { if (try24) { t = Colours[5]; Colours[5] = Colours[0]; Colours[0] = Colours[4]; Colours[4] = Colours[1]; Colours[1] = t; }
      if ((x == 1) && ((y & 1) == 0)) continue;
      for (z = 0; z < 4; z++)
      { if (try24)
        { t = Colours[0]; Colours[0] = Colours[3]; Colours[3] = Colours[1]; Colours[1] = Colours[2]; Colours[2] = t;
          if ((N & 1))
          { for (i = 0; i < N; i++) rotate(AxisL,i,3-x);
            if (y != 3) for (i = 0; i < N; i++) rotate(AxisO,i,3-y);
            if (z != 3) for (i = 0; i < N; i++) rotate(AxisV,i,z+1);
          }
        }
        SolveOFace();
        SolveLARFaces();
        SolveBVFaces();
        SolveEdges();
        SolveParity();
        len = NormaliseSolution();
        if (!try24) goto done;
        if ((DWORD)len < bestlen)
        { memcpy(BestSolution,Solution,len*sizeof(Solution[0]));
          memcpy(BestInputFor3x3x3,InputFor3x3x3,sizeof(InputFor3x3x3));
          BestXYZ[2] = x;
          BestXYZ[1] = y;
          BestXYZ[0] = z;
          bestlen = (DWORD)len;
        }
        SolutionPtr = Solution;
        memcpy(CubeFaceColours,SavedCubeFaceColours,6*MaxDim*MaxDim);
      }
    }
  }
  len = (int)bestlen;
  SolutionPtr = Solution + len;
  memcpy(Solution,BestSolution,len*sizeof(Solution[0]));
  memcpy(InputFor3x3x3,BestInputFor3x3x3,sizeof(InputFor3x3x3));
  AdjustSolutionForBestXYZ(Solution,len,FALSE);
done:
  SolveAs3x3x3(&len);

  return (len < 0) ? len : NormaliseSolution();
} // BJWSolveNCubeFromRubix

/********************************************************/
static void GetConnections (DWORD *faceptr, DWORD *xptr, DWORD *yptr)
{ DWORD face,x,y;
  // For a given (face,x,y) facelet, returns the other facelets that are on the same cubelet. In the case of corners, we make sure to give them in clockwise order.
  // Note that the caller has to put face, x, y in faceptr[0], xptr[0], yptr[0].

  face = *faceptr++; x = *xptr++; y = *yptr++;
  if ((x != 0) && (x != N1) && (y != 0) && (y != N1)) return; // Not an edge or corner piece, so no connections.

  if (face == FaceL)
  { if ((x ==  0) && (y == N1))
    { // To make sure it is clockwise. For the other corners, the "else" is in the correct order.
      *faceptr++ = FaceA; *xptr++ =  0; *yptr++ =  x;
      *faceptr++ = FaceB; *xptr++ =  0; *yptr++ =  y;
    } else
    { if (x ==  0) { *faceptr++ = FaceB; *xptr++ =  0; *yptr++ =  y; }
      if (y ==  0) { *faceptr++ = FaceV; *xptr++ =  0; *yptr++ =  x; }
      if (x == N1) { *faceptr++ = FaceO; *xptr++ =  0; *yptr++ =  y; }
      if (y == N1) { *faceptr++ = FaceA; *xptr++ =  0; *yptr++ =  x; }
    }
  } else
  if (face == FaceR)
  { if ((x == N1) && (y == N1))
    { // To make sure it is clockwise. For the other corners, the "else" is in the correct order.
      *faceptr++ = FaceA; *xptr++ = N1; *yptr++ =  x;
      *faceptr++ = FaceO; *xptr++ = N1; *yptr++ =  y;
    } else
    { if (x == N1) { *faceptr++ = FaceO; *xptr++ = N1; *yptr++ =  y; }
      if (y ==  0) { *faceptr++ = FaceV; *xptr++ = N1; *yptr++ =  x; }
      if (x ==  0) { *faceptr++ = FaceB; *xptr++ = N1; *yptr++ =  y; }
      if (y == N1) { *faceptr++ = FaceA; *xptr++ = N1; *yptr++ =  x; }
    }
  } else
  if (face == FaceB)
  { if ((x ==  0) && (y ==  0))
    { // To make sure it is clockwise. For the other corners, the "else" is in the correct order.
      *faceptr++ = FaceV; *xptr++ =  x; *yptr++ =  0;
      *faceptr++ = FaceL; *xptr++ =  0; *yptr++ =  y;
    } else
    { if (x ==  0) { *faceptr++ = FaceL; *xptr++ =  0; *yptr++ =  y; }
      if (y == N1) { *faceptr++ = FaceA; *xptr++ =  x; *yptr++ =  0; }
      if (x == N1) { *faceptr++ = FaceR; *xptr++ =  0; *yptr++ =  y; }
      if (y ==  0) { *faceptr++ = FaceV; *xptr++ =  x; *yptr++ =  0; }
    }
  } else
  if (face == FaceO)
  { if ((x == N1) && (y ==  0))
    { // To make sure it is clockwise. For the other corners, the "else" is in the correct order.
      *faceptr++ = FaceV; *xptr++ =  x; *yptr++ = N1;
      *faceptr++ = FaceR; *xptr++ = N1; *yptr++ =  y;
    } else
    { if (x == N1) { *faceptr++ = FaceR; *xptr++ = N1; *yptr++ =  y; }
      if (y == N1) { *faceptr++ = FaceA; *xptr++ =  x; *yptr++ = N1; }
      if (x ==  0) { *faceptr++ = FaceL; *xptr++ = N1; *yptr++ =  y; }
      if (y ==  0) { *faceptr++ = FaceV; *xptr++ =  x; *yptr++ = N1; }
    }
  } else
  if (face == FaceV)
  { if ((x ==  0) && (y ==  0))
    { // To make sure it is clockwise. For the other corners, the "else" is in the correct order.
      *faceptr++ = FaceL; *xptr++ =  y; *yptr++ =  0;
      *faceptr++ = FaceB; *xptr++ =  x; *yptr++ =  0;
    } else
    { if (y ==  0) { *faceptr++ = FaceB; *xptr++ =  x; *yptr++ =  0; }
      if (x == N1) { *faceptr++ = FaceR; *xptr++ =  y; *yptr++ =  0; }
      if (y == N1) { *faceptr++ = FaceO; *xptr++ =  x; *yptr++ =  0; }
      if (x ==  0) { *faceptr++ = FaceL; *xptr++ =  y; *yptr++ =  0; }
    }
  } else
  // if (face == FaceA)
  { if ((x ==  0) && (y == N1))
    { // To make sure it is clockwise. For the other corners, the "else" is in the correct order.
      *faceptr++ = FaceL; *xptr++ =  y; *yptr++ = N1;
      *faceptr++ = FaceO; *xptr++ =  x; *yptr++ = N1;
    } else
    { if (y == N1) { *faceptr++ = FaceO; *xptr++ =  x; *yptr++ = N1; }
      if (x == N1) { *faceptr++ = FaceR; *xptr++ =  y; *yptr++ = N1; }
      if (y ==  0) { *faceptr++ = FaceB; *xptr++ =  x; *yptr++ = N1; }
      if (x ==  0) { *faceptr++ = FaceL; *xptr++ =  y; *yptr++ = N1; }
    }
  }
} // GetConnections

/********************************************************/
static DWORD GetDifferingColourAndFaceIfTwoMatchLBV (DWORD face, DWORD x, DWORD y)
{ BYTE c,colours[3];
  BOOL found,foundface[6];
  DWORD i,ff,idx,facenum,num,faces[3],xs[3],ys[3];

  facenum = (DWORD)(-1);
  foundface[FaceL] = foundface[FaceB] = foundface[FaceV] = FALSE;
  faces[0] = face; xs[0] = x; ys[0] = y;
  GetConnections(faces,xs,ys);
  for (i = num = 0; i < 3; i++)
  { c = colours[i] = GetColour(faces[i],xs[i],ys[i]);
    for (ff = 0, found = FALSE; ff < 6; ff += 2) if (c == Colours[ff]) { num++; found = foundface[ff] = TRUE; }
    if (!found) idx = i;
  }
  for (ff = 0; ff < 6; ff += 2) if (!foundface[ff]) facenum = ff+1;

  return ((num == 2) && (facenum != (DWORD)(-1))) ? colours[idx]*6+facenum : 0;
} // GetDifferingColourAndFaceIfTwoMatchLBV

/********************************************************/
static int CheckValidity ()
{ BYTE c,thecolour,csearch[3],cfound[3],colours[6],colourpermutation[8];
  DWORD i,j,k,x,y,cf,ff,face,numconnections,numfound,type,numsfound[3],parities[3],xx[4],yy[4],fsearch[3],xsearch[3],ysearch[3],ffound[3],xfound[3],yfound[3];
  // -1: Invalid colours.
  // -2: Invalid corner parity.
  // -3: Invalid edge parity.
  // -4: Invalid swap parity.
  // -5: BJWSOLVE.333 is incorrect or does not exist. This value may be returned by BJWSolve3CubeFromRubix().

  // Determine the correct colour for each face. Note that Rubix ensures that colours are always in the range 1..6.
  if ((N & 1))
  { // N odd. Use the centres.
    for (face = 0; face < 6; face++) Colours[face] = GetColour(face,HalfN,HalfN);
  } else
  { // N even. Derive the colours from the corner cubelets.
    memset(Colours,0,sizeof(Colours));
    // Get the colours from the cubelet located at LBV.
    for (face = 0; face < 6; face += 2) Colours[face] = GetColour(face,0,0);
    // We now have 3 colours, for faces 0, 2, and 4. Use other corners to derive the colours for 1, 3, 5.
    // We try to find 3 corners that have 2 colours in common with the LBV cubelet. The one colour that is different gives us the opposite then.
    for (face = numfound = 0; face < 2; face++)
    { for (i = 0; i < 4; i++)
      { if ((face | i) == 0) continue; // Skip LBV.
        if ((cf = GetDifferingColourAndFaceIfTwoMatchLBV(face,(i >> 1) * N1,(i & 1) * N1)))
        { Colours[cf % 6] = (BYTE)(cf / 6);
          if (++numfound == 3) goto endofcoloursearch;
        }
      }
    }
endofcoloursearch:
    if (numfound != 3) return -1;
  }

  // We have to have all 6 colours.
  memset(colours,0,sizeof(colours));
  for (face = 0; face < 6; face++)
  { if ((c=Colours[face]-1) > 5) return -1;
    if (colours[c]) return -1;
    colours[c] = 1;
  }

  // Now try to find every possible piece. For ones we have found, we set the colour to 0 so that we do not use it again.
  // This code does some duplicate location checks, but that is OK. We also keep track of some parities here.
  parities[0] = parities[1] = parities[2] = numsfound[0] = numsfound[1] = numsfound[2] = 0; // Corners, edges, single facelets.
  for (face = 0; face < 6; face++)
  { thecolour = Colours[face];
    for (x = 0; x < N; x++)
    { for (y = 0; y < N; y++)
      { type = 2; numconnections = 1; // Assume it is a single facelet.
        if ((x == 0) || (x == N1) || (y == 0) || (y == N1))
        { // Edge or corner.
          if (((x == 0) || (x == N1)) && ((y == 0) || (y == N1)))
          { // Corner.
            if (face >= 2) goto trynext; // Make sure we look for each corner piece only once.
            type = 0; numconnections = 3;
          } else
          { // Edge.
            if ((face >= 4) || ((face >= 2) && (x-1 >= N2))) goto trynext; // Make sure we look for each edge piece only once.
            type = 1; numconnections = 2;
          }
        }
        fsearch[0] = face; xsearch[0] = x; ysearch[0] = y;
        GetConnections(fsearch,xsearch,ysearch);
        for (j = 0; j < numconnections; j++) csearch[j] = Colours[fsearch[j]];
        for (ff = 0; ff < 6; ff++)
        { switch (ff)
          { case 0: xx[0] = yy[1] = x; yy[0] = xx[3] = y; xx[1] = yy[2] = N1-y; xx[2] = yy[3] = N1-x; break;
            case 1: for (i = 0; i < 4; i++) yy[i] = N1-yy[i]; break;
            case 2: break;
            case 3: for (i = 0; i < 4; i++) xx[i] = N1-xx[i]; break;
            case 4: break;
            case 5: for (i = 0; i < 4; i++) xx[i] = N1-xx[i]; break;
          }
          for (i = 0; i < 4; i++)
          { ffound[0] = ff; xfound[0] = xx[i]; yfound[0] = yy[i];
            GetConnections(ffound,xfound,yfound);
            for (j = 0; j < numconnections; j++) cfound[j] = GetColour(ffound[j],xfound[j],yfound[j]);
            for (k = 0; k < numconnections; k++)
            { for (j = 0; (j < numconnections) && (csearch[j] == cfound[(j+k) % numconnections]); j++) ;
              if (j == numconnections)
              { for (j = 0; j < numconnections; j++) SetColour(ffound[j],xfound[j],yfound[j],0);
                parities[type] += k;
                numsfound[type]++;
                goto trynext;
              }
            }
          }
        }
        if (ff == 6) return -1; // Piece not found.
trynext: ;
      }
    }
  }
  memcpy(CubeFaceColours,SavedCubeFaceColours,6*MaxDim*MaxDim);

  if (numsfound[0] !=       8) return -1;
  if (numsfound[1] !=   12*N2) return -1;
  if (numsfound[2] != 6*N2*N2) return -1;

  // Parity checks.
  if ((parities[0] % 3)) return -2;
  if ((N & 1))
  { // On odd cubes, check the parity of the 12 centre edges and the swap parity as well.
    // Many thanks to Ron van Bruchem for explaining to me why a 2 corner or 2 centre edge swap is impossible on odd cubes.
    parities[0] = Get3x3x3Parity(Extract3x3x3Cube(InputFor3x3x3));
    if ((parities[0] & 2)) return -3;
    if ((parities[0] & 1)) return -4;
  }
  if ((parities[1] & 1)) return -1; // This is not really a parity problem because a cube cannot be assembled this way; it really is a sticker swap.

  // The 2x2x2 solver uses the fact that if face n (for even n) has colour c (and c is always odd then),
  // then face n+1 has colour ((c + 1) & ~1) - ((c + 1) & 1), so permute the colours to satisfy this requirement.
  if (N == 2)
  { for (face = 0; face < 6; face++) colourpermutation[Colours[face]] = (BYTE)(face+1);
    for (face = 0; face < 6; face++) for (y = 0; y < 2; y++) for (x = 0; x < 2; x++) SetColour(face,x,y,colourpermutation[GetColour(face,x,y)]);
  }

  return 0;
} // CheckValidity

/********************************************************/
static void Initialise (int n, int mem_n, char *facelist, unsigned short *rotlist)
{ DWORD i,j,k;
  struct EDGESOLVER *es;
  struct EDGESOLVERTEMPLATE *est;

  N2 = (N1 = (N = n) - 1) - 1;
  HalfN = N >> 1;
  HalfN1 = N1 >> 1;
  MaxDim = (DWORD)mem_n;
  CubeFaceColours = (BYTE *)facelist;
  SolutionPtr = Solution = rotlist;
  DoNotCombine = FALSE;

  SavedCubeFaceColours = (BYTE *)malloc(6*MaxDim*MaxDim);
  if (CubeFaceColours) memcpy(SavedCubeFaceColours,CubeFaceColours,6*MaxDim*MaxDim); // CubeFaceColours should possibly only be NULL during development.
  SliceNumbers = (DWORD *)malloc(sizeof(DWORD)*N);

  es  = EdgeSolver;
  est = EdgeSolverTemplate;
  for (i = 0; i < 8; i++, es++, est++)
  { for (j = 0; j < 2; j++)
    { switch (est->faces[j])
      { case 'L': es->faces[j] = FaceL; break;
        case 'R': es->faces[j] = FaceR; break;
        case 'B': es->faces[j] = FaceB; break;
        case 'O': es->faces[j] = FaceO; break;
        case 'V': es->faces[j] = FaceV; break;
        case 'A': es->faces[j] = FaceA; break;
      }
      for (k = 0; k < 2; k++)
      { switch (est->codes[j][k])
        { case -1: es->codes[j][k] = N1; break;
          case  0: es->codes[j][k] =  0; break;
          case  1: es->codes[j][k] =  1; break;
        }
      }
      for (k = 0; k < 3; k++)
      { es->formulas[j][k] = est->formulas[j][k];
        es->safeedges[j][k] = est->safeedges[j][k];
      }
    }
  }

#ifdef USE4X4X4CODE
  if (N == 4) BJW4Initialise(mem_n,facelist,&ASN4ptr);
#endif

} // Initialise

/********************************************************/
static void Cleanup ()
{ free(SliceNumbers);
  memcpy(CubeFaceColours,SavedCubeFaceColours,6*MaxDim*MaxDim);
  free(SavedCubeFaceColours);
} // Cleanup

/********************************************************/
static void RadixExchangeSortAux (BYTE *arr, DWORD num, DWORD valuesize, DWORD formulalength, DWORD bitmask)
{ // Pre: num >= 1.
  DWORD i,j;

  do
  { i = 0;
    j = num-1;
    do
    { while ((i < j) && ((*(DWORD *)(arr+i*valuesize+formulalength) & bitmask) == 0)) i++;
      while ((i < j) && ((*(DWORD *)(arr+j*valuesize+formulalength) & bitmask) != 0)) j--;
      if (i >= j) break;
      // Swap elements i and j.
      __asm
      { push ebx
        push esi
        mov  ebx, arr
        mov  ecx, valuesize
        mov  eax, i
        mul  ecx
        lea  esi, [eax+ebx]
        mov  eax, j
        mul  ecx
        add  eax, ebx
swloop: dec  ecx
        mov  bl, [eax+ecx]
        mov  bh, [esi+ecx]
        mov  [eax+ecx], bh
        mov  [esi+ecx], bl
        jnz  swloop
        pop  esi
        pop  ebx
      }
    } while (++i < --j);
    if ((i == j) && ((*(DWORD *)(arr+i*valuesize+formulalength) & bitmask) == 0)) i++;
    if ((bitmask >>= 1) == 0) return;
    // Do the smaller partition recursively and the larger one iteratively (saving quite a bit of stack space).
    if (i < num-i)
    { if (i > 1) RadixExchangeSortAux(arr+0*valuesize,i,valuesize,formulalength,bitmask);
      arr += i*valuesize;
      num -= i;
    } else
    { if (num-i > 1) RadixExchangeSortAux(arr+i*valuesize,num-i,valuesize,formulalength,bitmask);
      num = i;
    }
  } while (num > 1);
} // RadixExchangeSortAux

/********************************************************/
void BJWRadixExchangeSort (BYTE *arr, DWORD num, DWORD valuesize)
{ DWORD a,i,numbits,formulalength;

  if (num <= 1) return;
  formulalength = valuesize-4;
  // Determine highest used bit.
  for (i = a = 0; i < num; i++) a |= *(DWORD *)(arr+i*valuesize+formulalength);
  numbits = 32;
  while (((a & 0x80000000) == 0) && (numbits > 0))
  { a <<= 1;
    numbits--;
  }
  if (numbits == 0) return;
  RadixExchangeSortAux(arr,num,valuesize,formulalength,1 << (numbits-1));
} // BJWRadixExchangeSort

/********************************************************/
// This is the interface with Ken Silverman's Rubix.
//        n: cube size (n >= 1; an n*n*n cube)
//    mem_n: index pitch for facelist. mem_n >= n (default:MAXCDIM (=64))
// facelist: index like this: [(face*mem_n + x{0..n-1})*mem_n + y{0..n-1}] (same order as .SAV file)
//  rotlist: (slice{0..n-1}<<4) + (axis{0..2}<<2) + numtimes{1,2,3}
//  quality: {0..5} 0=fastest/highest#, 5=slowest/lowest#, but note that this differs per cube size.
//
// Note that n, mem_n, and facelist correspond with cdim, MAXCDIM, and cubefacecol in rubix.c.
int rubixsolve_bjw (int n, int mem_n, char *facelist, unsigned short *rotlist, int quality)
{ int len;

  if (n == 1) return 0; // A 1x1x1 cube...

  Initialise(n,mem_n,facelist,rotlist);
  // Note that Initialise() assigns n, mem_n, facelist, and rotlist to our static variables N, MaxDim, CubeFaceColours, and Solution, respectively.
  // That is why some of these parameters are not passed to the BJWSolve?CubeFromRubix() functions below.
  if ((len = CheckValidity()) == 0)
  { switch (n)
    { case 2 : len = BJWSolve2CubeFromRubix(mem_n,facelist,rotlist,quality); break; // quality: 0..1.
      case 3 : len = BJWSolve3CubeFromRubix(rotlist,quality); break; // quality: 0..5.
      default: len = BJWSolveNCubeFromRubix(); break; // quality is ignored.
    }
  }
  Cleanup();

  switch (len)
  { case -1: strcpy(message,"Invalid colours."); break;
    case -2: strcpy(message,"Invalid corner parity."); break;
    case -3: strcpy(message,"Invalid edge parity."); break;
    case -4: strcpy(message,"Invalid swap parity."); break;
    case -5: strcpy(message,"BJWSOLVE.333 is incorrect or does not exist."); break;
    default: message[0] = '\0';
  }

  return len;
} // rubixsolve_bjw

/********************************************************/
