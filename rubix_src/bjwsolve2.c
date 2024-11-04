#include <stdlib.h>
#include <windows.h>

// Copyright by Ben Jos Walbeehm. Written 1-2 March 2007.
// A few adjustments made later to integrate it with my NxNxN solver.
// Licence: This code may be used for non-commercial purposes as long as the author (Ben Jos Walbeehm) is clearly credited.

// An optimal 2x2x2 cube solver.

// Note that we use Dutch notation for the cube faces:
//   Dutch  English
//     R       R
//     B       U
//     V       F
//     L       L
//     O       D
//     A       B

// It can be easily seen that every formula for the 2x2x2 cube can be rewritten to use only R, B, V face turns (thus eliminating L, O, A face turns). This means
// that the LOA cubelet is fixed then; it never changes position or orientation and can thus be used as the "base" or "origin" for the 2x2x2 cube, similar to how
// the centres of the 3x3x3 are used as the "base" for that cube. So we can assume that the LOA cubelet is in its correct position and orientation and can derive
// from that where every other cubelet needs to go and in which orientation. This also makes it easy to see the number of possible situations. LOA is fixed, so no
// choice there. For positioning the remaining 7 cubelets, there are 7! possibilities. Each of those 7 can have 3 orientations, but to make a "valid" situation,
// the orientation of the last cubelet is dictated by the orientations of the other 7. So there are not 3^7, but only 3^6 orientations. This gives a total number
// of situations of 7! * 3^6 = 5,040 * 729 = 3,674,160.

// For the first turn, there are 9 possibilities. For each additional turn only 6 because we do not do two consecutive turns of the same face. So the number of
// formulas of length n, n >= 1 is 9 * 6^(n-1).
//   0:            1
//   1:            9
//   2:           54
//   3:          324  Identities: R2 B2 R2 = B2 R2 B2,  R2 V2 R2 = V2 R2 V2,  B2 V2 B2 = V2 B2 V2.
//   4:        1,944
//   5:       11,664
//   6:       69,984
//   7:      419,904
//   8:    2,519,424
//   9:   15,116,544
//  10:   90,699,264
//  11:  544,195,584

// Apparently, these are the numbers of minimal solutions per length. I have not verified this!!!
//   0:            1
//   1:            9
//   2:           54
//   3:          321
//   4:        1,847
//   5:        9,992
//   6:       50,136
//   7:      227,536
//   8:      870,072
//   9:    1,887,748
//  10:      623,800
//  11:        2,644
//
// So 82.95% of the possible situations can be solved in 9 turns or less, while 99.93% can be solved in 10 turns or less.

// Our internal representation, carefully chosen so that only facelets 0-6 need to be tracked:
//
//                _____________
//               |5     |1     |
//               |  00  |  01  |
//               |______B______|
//               |4     |0     |
//               |  03  |  02  |
//  _____________|______|______|___________________________
// |5     |4     |4     |0     |0     |1     |1     |5     |
// |  20  |  21  |  08  |  09  |  12  |  13  |  16  |  17  |
// |______L______|______V______|______R______|______A______|
// |7     |6     |6     |2     |2     |3     |3     |7     |
// |  23  |  22  |  11  |  10  |  15  |  14  |  19  |  18  |
// |______|______|______|______|______|______|______|______|
//               |6     |2     |
//               |  04  |  05  |
//               |______O______|
//               |7     |3     |
//               |  07  |  06  |
//               |______|______|
//
// The numbers in the top left corners make it easier to see which facelets are on the same cubelet.

// Conversion of this representation to Ken Silverman's Rubix:

// Rubix representation of a clean cube:
//   1,1
//   1,1
//   ---
//   2,2
//   2,2
//   ---
//   3,3
//   3,3
//   ---
//   4,4
//   4,4
//   ---
//   5,5
//   5,5
//   ---
//   6,6
//   6,6

// 1: L face colour.
// 2: R face colour.
// 3: B face colour.
// 4: O face colour.
// 5: V face colour.
// 6: A face colour.

// Write this as:
//   1a,1b
//   1c,1d
//   -----
//   2a,2b
//   2c,2d
//   -----
//   3a,3b
//   3c,3d
//   -----
//   4a,4b
//   4c,4d
//   -----
//   5a,5b
//   5c,5d
//   -----
//   6a,6b
//   6c,6d

// Then this translates to:
//
//                _____________
//               |5     |1     |
//               |  3c  |  3d  |
//               |______B______|
//               |4     |0     |
//               |  3a  |  3b  |
//  _____________|______|______|___________________________
// |5     |4     |4     |0     |0     |1     |1     |5     |
// |  1c  |  1a  |  5a  |  5b  |  2a  |  2c  |  6b  |  6a  |
// |______L______|______V______|______R______|______A______|
// |7     |6     |6     |2     |2     |3     |3     |7     |
// |  1d  |  1b  |  5c  |  5d  |  2b  |  2d  |  6d  |  6c  |
// |______|______|______|______|______|______|______|______|
//               |6     |2     |
//               |  4a  |  4b  |
//               |______O______|
//               |7     |3     |
//               |  4c  |  4d  |
//               |______|______|
//
// The numbers in the top left corners make it easier to see which facelets are on the same cubelet.

static BYTE Rubix[24] =
{  21,22,
   20,23,
// -----
   12,15,
   13,14,
// -----
    3, 2,
    0, 1,
// -----
    4, 5,
    7, 6,
// -----
    8, 9,
   11,10,
// -----
   17,16,
   18,19
};

// Turns:  0..3: R0..R3.  4..7: B0..B3.  8..11: V0..V3.
// The 0 turns were included so that we can use fast mod 4 arithmetic.

// T[0.. 3][]: R (Rechts - Right).
// T[4.. 7][]: B (Boven  - Up).
// T[8..11][]: V (Voor   - Front).

// T[2][12] = 14 means that 2 right turns (R2) moves the facelet at position 12 to position 14. Note that T[0][], T[4][], and T[8][] are the identity.
// "RB" makes facelet 10 end up at position 3, i.e. after DoFormula("RB"), Cube[10] = 3 holds. Note that these declarations do not initialise the entire
// T[][] array. The remainder is created during Initialise().
static BYTE T[12][24] =
{ /*R*/  {0},{ 0,19,16, 3, 4, 9,10, 7, 8, 1, 2,11,13,14,15,12, 6,17,18, 5,20,21,22,23},{0},{0},
  /*B*/  {0},{ 1, 2, 3, 0, 4, 5, 6, 7,20,21,10,11, 8, 9,14,15,12,13,18,19,16,17,22,23},{0},{0},
  /*V*/  {0},{ 0, 1,15,12,21,22, 6, 7, 9,10,11, 8, 5,13,14, 4,16,17,18,19,20, 2, 3,23},{0},{0}
};
// Identity: { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23}

static BYTE RubixRotationTranslation[12] = {0,19,18,17,  0,7,6,5,  0,9,10,11}; // R B V. The zeroes are never used.

static BYTE Cubelets[8][3] =
{ /* 0: RBV */ {12, 2, 9},
  /* 1: RBA */ {13, 1,16},
  /* 2: ROV */ {15, 5,10},
  /* 3: ROA */ {14, 6,19},
  /* 4: LBV */ {21, 3, 8},
  /* 5: LBA */ {20, 0,17},
  /* 6: LOV */ {22, 4,11},
  /* 7: LOA */ {23, 7,18}
};
static BYTE CubeletFaceCodes[8][3] =
{ /* 0: RBV */ {0,1,2},
  /* 1: RBA */ {0,1,5},
  /* 2: ROV */ {0,4,2},
  /* 3: ROA */ {0,4,5},
  /* 4: LBV */ {3,1,2},
  /* 5: LBA */ {3,1,5},
  /* 6: LOV */ {3,4,2},
  /* 7: LOA */ {3,4,5}
};
static BYTE CubeletFaceCodesSorted[8][4] = // We add a zero at the end so we can conveniently treat them as DWORDs.
{ /* 0: RBV */ {0,1,2,0},
  /* 1: RBA */ {0,1,5,0},
  /* 2: RVO */ {0,2,4,0},
  /* 3: ROA */ {0,4,5,0},
  /* 4: BVL */ {1,2,3,0},
  /* 5: BLA */ {1,3,5,0},
  /* 6: VLO */ {2,3,4,0},
  /* 7: LOA */ {3,4,5,0}
};

static DWORD SeqSitLookup[24*24*24*24];   // 1,327,104 bytes.  Situations: 7*6*5*4 * 3^4 = 860 * 81 = 68,040.

static BYTE  Suffix1[(9+1)*(4+1)];        //        50 bytes.
static BYTE  Suffix2[(54+1)*(4+2)];       //       330 bytes.
static BYTE  Suffix3[(324+1)*(4+3)];      //     2,275 bytes.  324 formulas of length 3. 3 bytes for the formula, 4 bytes for the situation. The additional entry is "situation" 0xffffffff, which makes things more convenient.
static BYTE  Suffix4[(1944+1)*(4+4)];     //    15,560 bytes.
static BYTE  Suffix5[(11664+1)*(4+5)];    //   104,985 bytes.
static BYTE *SuffixSituations[6][68040];  // 1,632,960 bytes.
static BYTE *Suffixes[6]       = {NULL,Suffix1,Suffix2,Suffix3,Suffix4,Suffix5};
static DWORD SuffixesSizeOf[6] = {0,sizeof(Suffix1),sizeof(Suffix2),sizeof(Suffix3),sizeof(Suffix4),sizeof(Suffix5)};

static BYTE  Cube[24];
static BYTE *MinFormula,Formula[16];

static DWORD Length,MinLength,MinLen180;

static BOOL  Minimise180;

static BYTE *TempPtr;

extern void BJWRadixExchangeSort (BYTE *arr, DWORD num, DWORD valuesize);

/********************************************************/
static void ConvertRubixCodesToSituation (BYTE *srcrubixcodes, BYTE *dstcube)
{ DWORD i,j,k;
  BYTE c,t,a[4],facecodes[3],colourcodes[24],coloursrev[7];

  for (i = 0; i < 24; i++) colourcodes[Rubix[i]] = srcrubixcodes[i];
  // Determine the colours for R B V L O A if this cube were solved. Take L O A from our fixed "base" cubelet. The colours for R B V are the opposite ones.
  for (i = 0; i < 3; i++)
  { c = colourcodes[Cubelets[7][i]];
    coloursrev[c] = (BYTE)(3+i);
    c = ((c + 1) & ~1) - ((c + 1) & 1);
    coloursrev[c] = (BYTE)i;
  }
  // Our fixed cubelet is always in the same, solved, spot.
  for (i = 0; i < 3; i++) dstcube[Cubelets[7][i]] = Cubelets[7][i];
  // Now locate the other 7 cubelets.
  a[3] = 0;
  for (c = 0; c < 7; c++)
  { for (i = 0; i < 3; i++) a[i] = facecodes[i] = coloursrev[colourcodes[Cubelets[c][i]]];
    // Sort them.
    for (j = 3-1; j > 0; j--) for (k = 0; k < j; k++) if (a[k] > a[k+1]) { t = a[k]; a[k] = a[k+1]; a[k+1] = t; }
    for (k = 0; *(DWORD *)CubeletFaceCodesSorted[k] != *(DWORD *)a; k++) ;
    for (i = 0; i < 3; i++)
    { t = facecodes[i];
      for (j = 0; CubeletFaceCodes[k][j] != t; j++) ;
      dstcube[Cubelets[k][j]] = Cubelets[c][i];
    }
  }
} // ConvertRubixCodesToSituation

/********************************************************/
static DWORD SequentialSituation ()
{ return SeqSitLookup[((Cube[0] * 24 + Cube[1]) * 24 + Cube[2]) * 24 + Cube[3]];
} // SequentialSituation

/********************************************************/
static void SuffixGeneratorAux (DWORD numturns, BYTE *formulaptr, BYTE lastturn)
{ BYTE i,facecode,*tptr;

  facecode = lastturn >> 2;
  tptr = T[lastturn];

  // Note that unrolling the following speeds things up by about 10%.
  for (i = 0; i < 4; i++)
  { Cube[0] = tptr[Cube[0]]; Cube[1] = tptr[Cube[1]]; Cube[2] = tptr[Cube[2]]; Cube[3] = tptr[Cube[3]];
    // If this is the 4th iteration, then we have just done the turn again to restore the situation, so we do not do the rest of this code.
    if (i < 3)
    { *formulaptr = (lastturn & ~3) + (-(signed char)lastturn & 3); // Store the inverse so that our table contains the solution (not the generator) for each situation.
      lastturn++;
      if (numturns == 1)
      { // Suffix generated.
        memcpy(TempPtr,Formula,Length);
        *(DWORD *)(TempPtr+Length) = SequentialSituation();
        TempPtr += Length+4;
      } else
      { if (facecode != 0) SuffixGeneratorAux(numturns-1,formulaptr-1,4*0+1);
        if (facecode != 1) SuffixGeneratorAux(numturns-1,formulaptr-1,4*1+1);
        if (facecode != 2) SuffixGeneratorAux(numturns-1,formulaptr-1,4*2+1);
      }
    }
  }

} // SuffixGeneratorAux

/********************************************************/
static void SuffixGenerator (DWORD numturns, BYTE *tableptr)
{ BYTE i,*ptr;
  DWORD recsize,sit,lastsit;

  Length = numturns;
  TempPtr = tableptr;
  Cube[0] = 0; Cube[1] = 1; Cube[2] = 2; Cube[3] = 3;
  for (i = 1; i < 12; i += 4) SuffixGeneratorAux(Length,Formula+Length-1,(BYTE)i);
  // Sort on sequential situation.
  BJWRadixExchangeSort(Suffixes[Length],SuffixesSizeOf[Length] / (Length+4) - 1,Length+4);
  *(DWORD *)(Suffixes[Length]+SuffixesSizeOf[Length]-4) = (DWORD)(-1);
  // Create lookup pointers.
  recsize = Length + 4;
  ptr = Suffixes[Length];
  lastsit = (DWORD)(-1);
  while ((sit = *(DWORD *)(ptr+Length)) != (DWORD)(-1))
  { if (sit != lastsit) SuffixSituations[Length][sit] = ptr;
    lastsit = sit;
    ptr += recsize;
  }
} // SuffixGenerator

/********************************************************/
static void InitSeqSitLookup ()
{ DWORD i,j,k,m,num;
  BYTE *ptr,connections[24][2];

  for (i = 0; i < 8; i++)
  { ptr = Cubelets[i];
    connections[ptr[0]][0] = ptr[1];
    connections[ptr[0]][1] = ptr[2];
    connections[ptr[1]][0] = ptr[0];
    connections[ptr[1]][1] = ptr[2];
    connections[ptr[2]][0] = ptr[0];
    connections[ptr[2]][1] = ptr[1];
  }
  for (i = num = 0; i < 24; i++)
  { if ((i == Cubelets[7][0]) || (i == Cubelets[7][1]) || (i == Cubelets[7][2])) continue;
    for (j = 0; j < 24; j++)
    { if ((j == Cubelets[7][0]) || (j == Cubelets[7][1]) || (j == Cubelets[7][2])) continue;
      if (j == i) continue;
      if (connections[j][0] == i) continue;
      if (connections[j][1] == i) continue;
      for (k = 0; k < 24; k++)
      { if ((k == Cubelets[7][0]) || (k == Cubelets[7][1]) || (k == Cubelets[7][2])) continue;
        if ((k == i) || (k == j)) continue;
        if ((connections[k][0] == i) || (connections[k][0] == j)) continue;
        if ((connections[k][1] == i) || (connections[k][1] == j)) continue;
        for (m = 0; m < 24; m++)
        { if ((m == Cubelets[7][0]) || (m == Cubelets[7][1]) || (m == Cubelets[7][2])) continue;
          if ((m == i) || (m == j) || (m == k)) continue;
          if ((connections[m][0] == i) || (connections[m][0] == j) || (connections[m][0] == k)) continue;
          if ((connections[m][1] == i) || (connections[m][1] == j) || (connections[m][1] == k)) continue;
          SeqSitLookup[((i * 24 + j) * 24 + k) * 24 + m] = num++;
        }
      }
    }
  }
} // InitSeqSitLookup

/********************************************************/
static void Initialise ()
{ BYTE c[24];
  DWORD i,k,n;

  // Initialise T[][].
  for (n = 0; n < 12; n += 4)
  { for (i = 0; i < 24; i++) c[i] = T[n+1][i];
    for (k = 2; k <= 4; k++) for (i = 0; i < 24; i++) T[n+(k & 3)][i] = c[i] = T[n+1][c[i]];
  }
  // Initialise SeqSitLookup[].
  InitSeqSitLookup();
  // Initialise the Suffix*[] arrays. This requires the T[][] and SeqSitLookup[] arrays to be initialised first.
  memset(SuffixSituations,0,sizeof(SuffixSituations));
  for (i = 1; i <= 5; i++) SuffixGenerator(i,Suffixes[i]);
} // Initialise

/********************************************************/
static BOOL ProcessSolution ()
{ DWORD i,len180;

  if (MinLength == (DWORD)(-1)) MinLength = Length;
  len180 = 0; // Note that this acts both as initialisation and as an early-out in case !Minimise180. And in case Minimise180 but there are no 180 degree turns, it is an early-out as well.
  if (Minimise180) for (i = 0; i < Length; i++) if ((Formula[i] & 3) == 2) len180++;
  if (len180 < MinLen180)
  { MinLen180 = len180;
    memcpy(MinFormula,Formula,Length);
    MinFormula[Length] = 0;
  }
  return (len180 == 0);
} // ProcessSolution

/********************************************************/
static void SolutionGenerator (DWORD numturns, BYTE *formulaptr, BYTE lastturn)
{ DWORD n,sit,recsize,savedcube;
  BYTE i,j,facecode,*ptr,*tptr,*tptr2;
  // Note that this could be made a lot faster by using the suffix tables for lengths < 6 as well, and also by going through all suffix tables at the same time, but both would be at the cost
  // of more code, and while technically a lot faster, a human would not notice the difference...

  if (MinLen180 == 0) return;

  facecode = lastturn >> 2;
  tptr = T[lastturn];

  for (i = 0; i < 4; i++)
  { Cube[0] = tptr[Cube[0]]; Cube[1] = tptr[Cube[1]]; Cube[2] = tptr[Cube[2]]; Cube[3] = tptr[Cube[3]];
    Cube[4] = tptr[Cube[4]]; Cube[5] = tptr[Cube[5]]; Cube[6] = tptr[Cube[6]];
    // If this is the 4th iteration, then we have just done the turn again to restore the situation, so we do not do the rest of this code.
    if (i < 3)
    { *formulaptr = lastturn++;
      if (numturns == 1)
      { if (Length <= 6)
        { if ((*(DWORD *)(Cube+0) == 0x03020100) && (*(DWORD *)(Cube+4) == 0x07060504))
          { // Solution found!
            if (ProcessSolution()) return; // Early-out.
          }
        } else
        { n = Length - 6;
          recsize = n + 4;
          if ((ptr = SuffixSituations[n][sit=SequentialSituation()]))
          { do
            { if (facecode != (*ptr >> 2)) // Skip turns of the same face.
              { // Appending this suffix puts facelets 0-3 in their correct locations. See if it also puts 4-6 in their correct locations.
                savedcube = *(DWORD *)(Cube+4);
                for (j = 0; j < n; j++)
                { tptr2 = T[formulaptr[j+1] = ptr[j]];
                  Cube[4] = tptr2[Cube[4]]; Cube[5] = tptr2[Cube[5]]; Cube[6] = tptr2[Cube[6]];
                }
                if (*(DWORD *)(Cube+4) == 0x07060504)
                { // Solution found!
                  if (ProcessSolution()) return; // Early-out.
                }
                *(DWORD *)(Cube+4) = savedcube;
              }
              ptr += recsize;
            } while (*(DWORD *)(ptr+n) == sit);
          }
        }
      } else
      { if (facecode != 0) SolutionGenerator(numturns-1,formulaptr+1,4*0+1);
        if (facecode != 1) SolutionGenerator(numturns-1,formulaptr+1,4*1+1);
        if (facecode != 2) SolutionGenerator(numturns-1,formulaptr+1,4*2+1);
      }
    }
  }
} // SolutionGenerator

/********************************************************/
static DWORD SolveCube (BOOL minimise180, BYTE *minformula)
{ DWORD i,n;

  for (i = 0; (i < 24) && (Cube[i] == (BYTE)i); i++) ;
  if (i == 24) return 0;

  Minimise180 = minimise180;
  MinFormula = minformula;
  MinLength = MinLen180 = (DWORD)(-1);
  for (Length = 1; Length <= MinLength; Length++)
  { if ((n = Length) > 6) n = 6;
    for (i = 1; i < 12; i += 4) SolutionGenerator(n,Formula,(BYTE)i);
  }

  return MinLength;
} // SolveCube

/********************************************************/
int BJWSolve2CubeFromRubix (int mem_n, char *facelist, unsigned short *rotlist, int quality)
{ int i,x,y,face,len;
  BYTE rubixcodes[24],formula[16];
  // quality == 0: Stop as soon as a minimal solution is found.
  // quality == 1: Of all minimal solutions, return one with the least amount of 180 degree turns.

  static BOOL initialised = FALSE;

  if (!initialised)
  { Initialise();
    initialised = TRUE;
  }

  for (face = i = 0; face < 6; face++) for (y = 0; y < 2; y++) for (x = 0; x < 2; x++) rubixcodes[i++] = facelist[(face * mem_n + x) * mem_n + y];
  ConvertRubixCodesToSituation(rubixcodes,Cube);
  len = (int)SolveCube((BOOL)quality,formula);
  for (i = 0; i < len; i++) rotlist[i] = RubixRotationTranslation[formula[i]];

  return len;
} // BJWSolve2CubeFromRubix

/********************************************************/
