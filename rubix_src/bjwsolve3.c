#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Copyright by Ben Jos Walbeehm. Written January-February 2007.
// A few adjustments made later to integrate it with my NxNxN solver.
// Some tiny changes that do not affect the lengths of 3x3x3 solutions made in April 2012.
// Licence: This code may be used for non-commercial purposes as long as the author (Ben Jos Walbeehm) is clearly credited.

// Note that we use Dutch notation for the cube faces:
//   Dutch  English
//     R       R
//     B       U
//     V       F
//     L       L
//     O       D
//     A       B

// Opposite colours: white-yellow, orange-red, green-blue.
//
// Turn the cube such that top is white, front is orange, right is green. Then the following numbers are assigned:
//
//          ________________________
//         /       /       /       /|
//        /  01   /  05   /  02   / |
//       /______ /______ /______ /  |
//      /       /       /       /|18|
//     /  04   /  48   /  06   / |  |
//    /______ /______ /______ /  | /|
//   /       /       /       /|21|/ |
//  /  00   /  07   /  03   / |  /  |
// /_______/_______/_______/  | /|22|
// |       |       |       |17|/ | /|
// |       |       |       |  /  |/ |
// |  09   |  13   |  10   | /|50/  |
// |_______|_______|_______|/ | /|19/
// |       |       |       |20|/ | /
// |       |       |       |  /  |/
// |  12   |  49   |  14   | /|23/
// |_______|_______|_______|/ | /
// |       |       |       |16|/
// |       |       |       |  /
// |  08   |  15   |  11   | /
// |_______|_______|_______|/
//
//
// Turn the cube such that top is yellow, front is blue, right is red. Then the following numbers are assigned:
//
//          ________________________
//         /       /       /       /|
//        /  42   /  46   /  43   / |
//       /______ /______ /______ /  |
//      /       /       /       /|24|
//     /  45   /  53   /  47   / |  |
//    /______ /______ /______ /  | /|
//   /       /       /       /|31|/ |
//  /  41   /  44   /  40   / |  /  |
// /_______/_______/_______/  | /|28|
// |       |       |       |27|/ | /|
// |       |       |       |  /  |/ |
// |  35   |  39   |  32   | /|51/  |
// |_______|_______|_______|/ | /|25/
// |       |       |       |30|/ | /
// |       |       |       |  /  |/
// |  38   |  52   |  36   | /|29/
// |_______|_______|_______|/ | /
// |       |       |       |26|/
// |       |       |       |  /
// |  34   |  37   |  33   | /
// |_______|_______|_______|/

// Note that I had already chosen my own representation of the cube and written a lot of the code before I decided to interface this code with Ken Silverman's Rubix.
// That is why the conversion between the two representations is awkward.

static BYTE CrossEdges[24]   = { 4, 5, 6, 7,12,13,14,15,20,21,22,23,28,29,30,31,36,37,38,39,44,45,46,47};
static BYTE F2L1Corners[24]  = { 0, 1, 2, 3, 8, 9,10,11,16,17,18,19,24,25,26,27,32,33,34,35,40,41,42,43};
static BYTE F2L1Edges[16]    = {12,14,15,20,22,23,28,30,31,36,38,39,44,45,46,47};
static BYTE F2L2aCorners[18] = { 1, 2, 8,11,16,18,19,24,25,26,27,32,33,35,40,41,42,43};
static BYTE F2L2aEdges[12]   = {15,22,23,28,30,31,36,39,44,45,46,47};
static BYTE F2L2bCorners[18] = { 1, 3, 8,10,11,16,17,19,24,26,27,32,33,35,40,41,42,43};
static BYTE F2L2bEdges[12]   = {14,15,20,23,30,31,36,39,44,45,46,47};
static BYTE L3Corners[12]    = { 8,11,16,19,24,27,32,35,40,41,42,43};
static BYTE L3Edges[8]       = {15,23,31,39,44,45,46,47};

static BYTE CrossFacelets[4] = {4,5,6,7};
static BYTE F2L1aFacelets[4] = {0,3,12,14};
static BYTE F2L1bFacelets[4] = {0,2,12,22};
static BYTE F2L2aFacelets[4] = {2,1,22,30};
static BYTE F2L2bFacelets[4] = {3,1,14,30};
static BYTE L3Facelets[8]    = {40,41,42,43,44,45,46,47};

static BYTE  FaceletsToTrackA[20] = {40,41,42,43,44,45,46,47,  2,1,22,30,  0,3,12,14,  4,5,6,7};
static BYTE  FaceletsToTrackB[20] = {40,41,42,43,44,45,46,47,  3,1,14,30,  0,2,12,22,  4,5,6,7};
static BYTE  FaceletsToTrack[20];
static DWORD NumFaceletsToTrack;

static DWORD IdxCrossEdges  [48];
static DWORD IdxF2L1Corners [48];
static DWORD IdxF2L1Edges   [48];
static DWORD IdxF2L2aCorners[48];
static DWORD IdxF2L2aEdges  [48];
static DWORD IdxF2L2bCorners[48];
static DWORD IdxF2L2bEdges  [48];
static DWORD IdxL3Corners   [48];
static DWORD IdxL3Edges     [48];

static DWORD SeqSitCrossEdges  [24*24*24*24]; // 1,327,104 bytes.
static DWORD SeqSitF2L1Corners [24*24];       //     2,304 bytes.
static DWORD SeqSitF2L1Edges   [16*16];       //     1,024 bytes.
static DWORD SeqSitF2L2aCorners[18*18];       //     1,296 bytes.
static DWORD SeqSitF2L2aEdges  [12*12];       //       576 bytes.
static DWORD SeqSitF2L2bCorners[18*18];       //     1,296 bytes.
static DWORD SeqSitF2L2bEdges  [12*12];       //       576 bytes.
static DWORD SeqSitL3Corners   [12*12*12*12]; //    82,944 bytes.
static DWORD SeqSitL3Edges     [ 8* 8* 8* 8]; //    16,384 bytes.

// For each facelet, list facelets that are on the same cubelet. 0xff is used to indicate EndOfList.
// Note that in the case of corners, the order of the connections (e.g. {34, 9}) should NOT be changed. We need the given order for parity checking.
static BYTE Connections[54][2] =
{ /* 0*/ {34, 9},
  /* 1*/ {26,33},
  /* 2*/ {18,25},
  /* 3*/ {10,17},
  /* 4*/ {37,0xff},
  /* 5*/ {29,0xff},
  /* 6*/ {21,0xff},
  /* 7*/ {13,0xff},
  /* 8*/ {35,41},
  /* 9*/ { 0,34},
  /*10*/ {17, 3},
  /*11*/ {42,16},
  /*12*/ {38,0xff},
  /*13*/ { 7,0xff},
  /*14*/ {20,0xff},
  /*15*/ {45,0xff},
  /*16*/ {11,42},
  /*17*/ { 3,10},
  /*18*/ {25, 2},
  /*19*/ {43,24},
  /*20*/ {14,0xff},
  /*21*/ { 6,0xff},
  /*22*/ {28,0xff},
  /*23*/ {46,0xff},
  /*24*/ {19,43},
  /*25*/ { 2,18},
  /*26*/ {33, 1},
  /*27*/ {40,32},
  /*28*/ {22,0xff},
  /*29*/ { 5,0xff},
  /*30*/ {36,0xff},
  /*31*/ {47,0xff},
  /*32*/ {27,40},
  /*33*/ { 1,26},
  /*34*/ { 9, 0},
  /*35*/ {41, 8},
  /*36*/ {30,0xff},
  /*37*/ { 4,0xff},
  /*38*/ {12,0xff},
  /*39*/ {44,0xff},
  /*40*/ {32,27},
  /*41*/ { 8,35},
  /*42*/ {16,11},
  /*43*/ {24,19},
  /*44*/ {39,0xff},
  /*45*/ {15,0xff},
  /*46*/ {23,0xff},
  /*47*/ {31,0xff},
  /*48*/ {0xff,0xff},
  /*49*/ {0xff,0xff},
  /*50*/ {0xff,0xff},
  /*51*/ {0xff,0xff},
  /*52*/ {0xff,0xff},
  /*53*/ {0xff,0xff}
};

static BYTE  Cube[54],SavedCube[54];
static BYTE *TempPtr,*FormulaPtr,Formula[256];

// Note that the final 6 facelets are the centre ones; we ignore these for R, B, V, L, O, A turns.

// T[ 0][][]: R (Rechts - Right).
// T[ 1][][]: B (Boven  - Up).
// T[ 2][][]: V (Voor   - Front).
// T[ 3][][]: L (Links  - Left).
// T[ 4][][]: O (Onder  - Down).
// T[ 5][][]: A (Achter - Back).
// And "special" turns:
// T[ 6][][]: M (Middle  -- equal to R L'X'). ("Turn middle down.")     So R L' = R L'X'X  = M X.
// T[ 7][][]: E (Equator -- equal to B O'Y'). ("Turn equator right.")   So B O' = R L'Y'Y  = E Y.
// T[ 8][][]: S (Slice   -- equal to V'A Z ). ("Turn slice clockwise.") So V'A  = V'A Z Z' = S Z'.
// And turning the entire cube:
// T[ 9][][]: X: Rotate the ENTIRE cube in the same direction as a turn R.
// T[10][][]: Y: Rotate the ENTIRE cube in the same direction as a turn B.
// T[11][][]: Z: Rotate the ENTIRE cube in the same direction as a turn V.
// When displaying a formula, one more "turn" may be displayed: "I", the identity (0 turns).

// T[0][1][2] = 24 means that 1 right turn (T[0][][]) moves the facelet at position 2 to position 24. Note that all T[][0][] are the identity. Yes, we are wasting a few bytes of memory here.
// "RB" makes facelet 10 end up at position 3, i.e. after DoFormula("RB"), Cube[10] = 3 holds. Note that these declarations do not initialise the entire T[][][] array. The remainder is
// created during Initialise().
static BYTE T[12][4][54] =
{ /*R*/ {{0},{ 0, 1,24,25, 4, 5,28, 7, 8, 9, 2, 3,12,13, 6,15,17,18,19,16,21,22,23,20,42,43,26,27,46,29,30,31,32,33,34,35,36,37,38,39,40,41,10,11,44,45,14,47,48,49,50,51,52,53}},
  /*B*/ {{0},{ 1, 2, 3, 0, 5, 6, 7, 4, 8,33,34,11,12,37,14,15,16, 9,10,19,20,13,22,23,24,17,18,27,28,21,30,31,32,25,26,35,36,29,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53}},
  /*V*/ {{0},{17, 1, 2,16, 4, 5, 6,20, 9,10,11, 8,13,14,15,12,41,42,18,19,45,21,22,23,24,25,26,27,28,29,30,31,32,33, 3, 0,36,37, 7,39,40,34,35,43,44,38,46,47,48,49,50,51,52,53}},
  /*L*/ {{0},{ 8, 9, 2, 3,12, 5, 6, 7,40,41,10,11,44,13,14,15,16,17,18,19,20,21,22,23,24,25, 0, 1,28,29, 4,31,33,34,35,32,37,38,39,36,26,27,42,43,30,45,46,47,48,49,50,51,52,53}},
  /*O*/ {{0},{ 0, 1, 2, 3, 4, 5, 6, 7,16, 9,10,19,12,13,14,23,24,17,18,27,20,21,22,31,32,25,26,35,28,29,30,39, 8,33,34,11,36,37,38,15,41,42,43,40,45,46,47,44,48,49,50,51,52,53}},
  /*A*/ {{0},{ 0,32,33, 3, 4,36, 6, 7, 8, 9,10,11,12,13,14,15,16,17, 1, 2,20,21, 5,23,25,26,27,24,29,30,31,28,43,40,34,35,47,37,38,39,19,41,42,18,44,45,46,22,48,49,50,51,52,53}},

  /*M*/ {{0},{ 0, 1, 2, 3, 4,13, 6,15, 8, 9,10,11,12,45,14,47,16,17,18,19,20,21,22,23,24,25,26,27,28, 7,30, 5,32,33,34,35,36,37,38,39,40,41,42,43,44,31,46,29,49,53,50,48,52,51}},
  /*E*/ {{0},{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,20,13,22,15,16,17,18,19,28,21,30,23,24,25,26,27,36,29,38,31,32,33,34,35,12,37,14,39,40,41,42,43,44,45,46,47,48,50,51,52,49,53}},
  /*S*/ {{0},{ 0, 1, 2, 3,21, 5,23, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,46,22,44,24,25,26,27,28,29,30,31,32,33,34,35,36, 6,38, 4,40,41,42,43,37,45,39,47,50,49,53,51,48,52}},

  /*X*/ {{0},{26,27,24,25,30,31,28,29, 0, 1, 2, 3, 4, 5, 6, 7,17,18,19,16,21,22,23,20,42,43,40,41,46,47,44,45,35,32,33,34,39,36,37,38, 8, 9,10,11,12,13,14,15,51,48,50,53,52,49}},
  /*Y*/ {{0},{ 1, 2, 3, 0, 5, 6, 7, 4,32,33,34,35,36,37,38,39, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,43,40,41,42,47,44,45,46,48,52,49,50,51,53}},
  /*Z*/ {{0},{17,18,19,16,21,22,23,20, 9,10,11, 8,13,14,15,12,41,42,43,40,45,46,47,44,27,24,25,26,31,28,29,30, 1, 2, 3, 0, 5, 6, 7, 4,33,34,35,32,37,38,39,36,50,49,53,51,48,52}}
};

// Identity: { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53}

static BYTE *SolveCrossPtr[6][2] = {{T[0][0],T[0][0]},{T[9][1],T[9][3]},{T[9][2],T[9][2]},{T[9][3],T[9][1]},{T[11][1],T[11][3]},{T[11][3],T[11][1]}}; // I, X, X2, X', Z, Z'.
static BYTE *SolveF2LPtr[4][2]   = {{T[0][0],T[0][0]},{T[10][1],T[10][3]},{T[10][2],T[10][2]},{T[10][3],T[10][1]}}; // I, Y, Y2, Y'. Only the first two are used for the "b" solutions.
static BYTE  CrossTurnBefore[6]  = {0x00,0x91,0x92,0x93,0xb1,0xb3};
static BYTE  F2LTurnBefore[4]    = {0x00,0xa1,0xa2,0xa3};

static BYTE *TT[256]; // Will be initialised such that for a turn k (0x01, 0x02, 0x03, 0x11, 0x12, ...) TT[k] points to the correct T[][] location.

static BYTE T1[18][48];       // B      is T1[3].              18^1 * 48 =     864 bytes; the results of all 1 turn formulas containing only R, B, V, L, O, A face turns.
static BYTE T2[18*18][48];    // B R2   is T2[3*18+1].         18^2 * 48 =  15,552 bytes; the results of all 2 turn formulas containing only R, B, V, L, O, A face turns.
static BYTE T3[18*18*18][48]; // V B R' is T3[6*18*18+3*18+2]. 18^3 * 48 = 279,936 bytes; the results of all 3 turn formulas containing only R, B, V, L, O, A face turns.

static BYTE TurnCode[36] =
{ 0x01,0x02,0x03,0x11,0x12,0x13,0x21,0x22,0x23,0x31,0x32,0x33,0x41,0x42,0x43,0x51,0x52,0x53,
  0x61,0x62,0x63,0x71,0x72,0x73,0x81,0x82,0x83,0x91,0x92,0x93,0xa1,0xa2,0xa3,0xb1,0xb2,0xb3
};
static BYTE TurnCodeRev[256];
// To convert a turn t (0x01,0x02,0x03,0x11,0x12,0x13,...,0xb1,0xb2,0xb3) to a number from 0 to 35: (t >> 4) * 3 + (t & 3) - 1. Lookup using TurnCodeRev[t] is probably faster.

static BYTE XYZTrans[3][3][6] =
{ {{0x00,0x20,0x40,0x30,0x50,0x10},{0x00,0x40,0x50,0x30,0x10,0x20},{0x00,0x50,0x10,0x30,0x20,0x40}}, // X, X2, X'.
  {{0x50,0x10,0x00,0x20,0x40,0x30},{0x30,0x10,0x50,0x00,0x40,0x20},{0x20,0x10,0x30,0x50,0x40,0x00}}, // Y, Y2, Y'.
  {{0x10,0x30,0x20,0x40,0x00,0x50},{0x30,0x40,0x20,0x00,0x10,0x50},{0x40,0x00,0x20,0x10,0x30,0x50}}  // Z, Z2, Z'.
};

// 1 = Orange, 2 = Red, 3 = Green, 4 = Blue, 5 = Yellow, 6 = White.
// More generally: 1 = V-face colour, 2 = A-face colour, 3 = R-face colour, 4 = L-face colour, 5 = O-face colour, 6 = B-face colour.
static BYTE Colours[54] = {6,6,6,6,6,6,6,6,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,1,3,2,4,5};

// To quickly determine the parity of edge flips and corner twists, imagine a two-colour cube, say black and white, with the B and O faces black,
// as well as the facelets of the edges in the equator slice that lie in the V and A faces. The rest of the cube is white.
static BYTE ParityColours[48];
static BYTE ParityCubelets[48]; // Will be initialised such that for each non-centre facelet it gives a cubelet number. 0..11 for edges. 0..7 for corners.
static BYTE ParityEdges[12]  = { 4, 5, 6, 7,12,14,28,30,44,45,46,47};
static BYTE ParityCorners[8] = { 0, 1, 2, 3,40,41,42,43};

// For input of colours: Enter the colours of the face you are looking at; top row left to right, middle row left to right, bottom row left to right.
// Note that we have already encoded the colours into numbers here. We then make sure we always encode them such that 1-2, 3-4, and 5-6 are opposites
// and such that 6 is B and 1 is V and 3 is R (so that O, A, L are 5, 2, 4, respectively).
// For instance (so the 9 numbers for each face are corner-edge-corner edge-centre-edge corner-edge-corner):
//   V face: 2,5,6,1,1,6,1,3,1,  //  9,13,10,12,49,14, 8,15,11.
// Turn the cube so that that last face is going to the right side (so Y').
//   L face: 4,1,5,2,4,4,5,5,6,  // 33,37,34,36,52,38,32,39,35.
// Turn the cube so that that last face is going to the right side (so Y').
//   A face: 3,5,1,4,2,6,2,2,4,  // 25,29,26,28,51,30,24,31,27.
// Turn the cube so that that last face is going to the right side (so Y').
//   R face: 2,1,5,3,3,6,6,2,6,  // 17,21,18,20,50,22,16,23,19.
// Turn the cube so that that last face is going to the down side (so X').
//   B face: 3,3,5,4,6,1,4,6,1,  //  0, 4, 1, 7,48, 5, 3, 6, 2.
// Do the same cube turn as the last time, but twice (so X2).
//   O face: 3,5,3,2,5,4,4,3,2   // 42,46,43,45,53,47,41,44,40.

static BYTE InputTranslationRev[54];
static BYTE InputTranslation[54] = { 9,13,10,12,49,14, 8,15,11,33,37,34,36,52,38,32,39,35,25,29,26,28,51,30,24,31,27,17,21,18,20,50,22,16,23,19, 0, 4, 1, 7,48, 5, 3, 6, 2,42,46,43,45,53,47,41,44,40};
static BYTE InputCorners[4]      = {0,2,6,8};
static BYTE InputEdges[4]        = {1,3,5,7};
static BYTE InputColourToFace[6] = {8,24,16,32,40,0};

// Conversion of this representation to Ken Silverman's Rubix:
static BYTE Rubix[54] =
{  34,38,35,
   37,52,39,
   33,36,32,
// --------
   17,20,16,
   21,50,23,
   18,22,19,
// --------
    0, 7, 3,
    4,48, 6,
    1, 5, 2,
// --------
   41,45,42,
   44,53,46,
   40,47,43,
// --------
    9,13,10,
   12,49,14,
    8,15,11,
// --------
   26,29,25,
   30,51,28,
   27,31,24
};

static BYTE RubixInputToOurInput[54];
static BYTE RubixRotationTranslation[27] = {35,34,33, 7, 6, 5, 9,10,11, 1, 2, 3,37,38,39,43,42,41,17,18,19,21,22,23,25,26,27}; // R B V L O A M E S.

static DWORD Length;

static BOOL Initialised = FALSE;
static BOOL PartiallyInitialised = FALSE;

// 44,880 bytes hardcoded in bjwhc.c.
extern DWORD BJWF2L11Solutions[2696];
extern DWORD BJWF2L12Solutions[  19];
extern BYTE  BJWPackedL3Solutions[34020];

// To be read from bjwsolve.333 (891,966 bytes).
static DWORD SizeOfCrossSolutionsPacked = 118800;
static DWORD SizeOfF2LSolutionsPacked   = 739142;
static DWORD SizeOfL3SolutionsPacked    = sizeof(BJWPackedL3Solutions);

static BYTE  CrossSolutions[190080];    //   190,080 bytes.
static BYTE  F2L1aSolutions[112896*13]; // 1,467,648 bytes.
static BYTE  F2L1bSolutions[112896*13]; // 1,467,648 bytes.
static BYTE  F2L2aSolutions[ 32400*13]; //   421,200 bytes.
static BYTE  F2L2bSolutions[ 32400*13]; //   421,200 bytes.
static BYTE  L3Formulas[62208*17];      // 1,057,536 bytes.
static BYTE *L3Solutions[746496];       // 2,985,984 bytes.

static BYTE  PackedBuffer[739142];      //   739,142 bytes. The size of the largest packed table read from bjwsolve.333.

static BYTE  Prefix1[18*1];             //        18 bytes.
static BYTE  Prefix2[243*2];            //       486 bytes.
static BYTE  Prefix3[3240*3];           //     9,720 bytes.
static BYTE  Prefix4[43254*4];          //   173,016 bytes.
static BYTE  Prefix5[577368*5];         // 2,886,840 bytes.
static BYTE *Prefixes[6]       = {NULL,Prefix1,Prefix2,Prefix3,Prefix4,Prefix5};
static DWORD PrefixesSizeOf[6] = {0,sizeof(Prefix1),sizeof(Prefix2),sizeof(Prefix3),sizeof(Prefix4),sizeof(Prefix5)};
static DWORD NumOfPrefixes[6]  = {1,18,243,3240,43254,577368};

static BYTE NumBytesForLengthF2L[13] = {1,2,2,2,3,3,4,4,5,5,6,6,7};
static BYTE NumBytesForLengthL3[17]  = {1,2,2,3,3,4,4,5,5,5,6,6,7,7,8,8,9};

static DWORD CrossCount;
static DWORD CrossCounts[9] = {1,16,174,1568,11377,57758,155012,189978,190080};

static DWORD F2L1aCount;
static DWORD F2L1bCount;
static DWORD F2L2aCount;
static DWORD F2L2bCount;
static DWORD F2L1aCounts[13] = {1,1,1,13,47,273,1378,6682,28138,80161,111473,112896,112896};
static DWORD F2L1bCounts[13] = {1,1,1,13,45,248,1304,6230,26391,77443,111159,112894,112896};
static DWORD F2L2aCounts[13] = {1,1,1,13,37,124, 532,1962, 6184,17272, 29893, 32390, 32400};
static DWORD F2L2bCounts[13] = {1,1,1,13,33, 86, 478,1915, 5960,17060, 29759, 32380, 32400};

extern void BJWRadixExchangeSort (BYTE *arr, DWORD num, DWORD valuesize);

// These are only used when creating bjwsolve.333.
static DWORD  FnSizeOf[7] = {1*4+4,18*5+5,243*6+6,3240*7+7,43254*8+8,577368*9+9,7706988*10+10};  // (NumOfPrefixes[n]*(n+4))+(n+4). Well, we do not have NumOfPrefixes[6].
static BYTE  *FnPointers[7]; // FnPointers[6] will be allocated FnSizeOf[6] = 77,069,890 bytes.
static BYTE **FnSituations;  // Will be used as "BYTE *FnSituations[7][190080];". 5,322,240 bytes.
static BYTE   FaceletsToTrackF2L[8] = {2,1,22,30,0,3,12,14};
static DWORD  PrefixIndex;
static DWORD *PrefixIndices[6];  // PrefixIndices[5] will be allocated 18^5 * sizeof(DWORD) = 7,558,272 bytes.

static DWORD LookupFileVersion = 10;
static DWORD LookupFileSize    = 891966;
static char *LookupFileName    = "bjwsolve.333";

/********************************************************/
static DWORD EliminateXYZ (BYTE *f, DWORD len, DWORD start)
{ DWORD i,j;
  BYTE *ptr;

  for (i = start; i > 0; )
  { if (f[--i] > 0x90)
    { if (i < --len)
      { ptr = XYZTrans[(f[i] - 0x90) >> 4][(f[i] & 3) - 1];
        for (j = i; j < len; j++) f[j] = ptr[f[j+1] >> 4] + (f[j+1] & 3);
      }
    }
  }
  f[len] = 0;
  return len;
} // EliminateXYZ

/********************************************************/
static DWORD CompactFormula (BYTE *f, DWORD newlen, DWORD start)
{ DWORD i,j;

  for (i = j = start; j < newlen; i++) if (f[i] != 0xff) f[j++] = f[i];
  f[newlen] = 0;
  return newlen;
} // CompactFormula

/********************************************************/
static DWORD NormaliseFormula (BYTE *f, DWORD len)
{ BYTE t,fi,fj;
  BOOL changed,flipped;
  DWORD i,j,minidx,start,maxidx,end,newlen;

  // Change things like "A V" to "V A", "V A V'A" to "A2", "V A R B B'R'V'A" to "A2", "L R B B'R L'" to "R2", "L R B B'R L" to "R2L2", and so on.
  if (len < 2) return len;
  start = 0;
  end = newlen = len;
  do
  { changed = flipped = FALSE;
    minidx = (DWORD)(-1);
    maxidx = 0;
    fi = f[i=start+0];
    j = start + 1;
    do
    { fj = f[j];
      while ((t = (fi & 0xf0) - (fj & 0xf0)) == 0x30)
      { if (i < minidx) minidx = i;
        if (j > maxidx) maxidx = j;
        flipped = TRUE;
        f[i] = fj;
        f[i=j] = fi;
        if (++j >= end) goto BREAK; // I do not like it, but there is no elegant way to break out of these two loops...
        fj = f[j];
      }
      if (t == 0)
      { changed = TRUE;
        if ((t = (fi + fj) & 3) == 0)
        { // Eliminate.
          f[i] = f[j] = 0xff;
          if (i < minidx) minidx = i;
          if (j > maxidx) maxidx = j;
          if (((newlen -= 2) < 2) || (++j >= end)) break;
          if (i == 0) fi = f[i=j++]; else fi = f[--i];
        } else
        { // Combine.
          f[i] = fi = (fi & 0xf0) + t;
          if (j < minidx) minidx = j;
          if (j > maxidx) maxidx = j;
          f[j++] = 0xff;
          if (--newlen < 2) break;
        }
      } else
      { fi = fj;
        i = j++;
      }
    } while (j < end);
    if (!(changed | flipped)) break;
BREAK:
    if (changed) len = CompactFormula(f,newlen,minidx);
    if ((len < 2) || (minidx == len-1)) break;
    if ((start=minidx)) start--;
    if ((end=maxidx) > len) end = len;
  } while (end > start+1);
  return len;
} // NormaliseFormula

/********************************************************/
static DWORD NormaliseSliceTurns (BYTE *formula, DWORD len, DWORD minlen)
{ DWORD numslicesfound;
  BYTE i,j,t,last,*ptr,tempformula[64],indices[64];
  // Assumes NormaliseFormula() has been called before.

  if (len < 2) return len;
  numslicesfound = 0;
  for (i = j = 0; i < len; i++, j++)
  { t = tempformula[i] = formula[i];
    if (i < len-1)
    { if ((((formula[i+1] & 0xf0) - (t & 0xf0) == 0x30)) && (((formula[i+1] + t) & 3) == 0))
      { tempformula[last = ++i] = t + 0x90;
        indices[numslicesfound++] = j;
      }
    }
  }
  if ((numslicesfound == 0) || (len - numslicesfound > minlen)) return len;
  tempformula[len] = 0;
  len = EliminateXYZ(tempformula,len,last+1);
  for (i = 0; i < numslicesfound; i++)
  { t = *(ptr = tempformula+indices[i]);
    if (t > 0x30) t = (t & 0xf0) - 0x30 + (-(signed char)t & 3);
    if ((t & 0xf0) == 0x20) t = (t & 0xf0) + (-(signed char)t & 3);
    *ptr = t + 0x60;
  }
  memcpy(formula,tempformula,len+1);
  return len;
} // NormaliseSliceTurns

/********************************************************/
#pragma warning (disable: 4731) // "frame pointer register 'ebp' modified by inline assembly code".

static __declspec(naked) void DoFormula (BYTE *fptr)
{ // Note that we should never call this for formulas containing M, E, S, X, Y, Z turns!

  // DWORD n;
  // BYTE b,*tptr;

  // Slower code, doing one turn at a time:
  //  for ( ; (b = *fptr); fptr++)
  //  { tptr = TT[b];
  //    // Note that unrolling the below loop makes things a few percent faster.
  //    for (i = 0; i < 48; i++) Cube[i] = tptr[Cube[i]];
  //  }

  // Doing up to 3 turns at a time.
/*
  if ((NumFaceletsToTrack == 0) || (*fptr == 0)) return;

  for (b = *fptr; b; )
  { tptr = T1[n = TurnCodeRev[b]];
    if ((b = *++fptr))
    { tptr = T2[n = 18*n+TurnCodeRev[b]];
      if ((b = *++fptr))
      { tptr = T3[18*n+TurnCodeRev[b]];
        b = *++fptr;
      }
    }
    // Note that using a huge switch statement for each of the 36 different cases, thus eliminating the use of the facelets[] array, does not speed things up significantly.
    Cube[FaceletsToTrack[ 0]] = tptr[Cube[FaceletsToTrack[ 0]]]; Cube[FaceletsToTrack[ 1]] = tptr[Cube[FaceletsToTrack[ 1]]];
    Cube[FaceletsToTrack[ 2]] = tptr[Cube[FaceletsToTrack[ 2]]]; Cube[FaceletsToTrack[ 3]] = tptr[Cube[FaceletsToTrack[ 3]]];
    if (NumFaceletsToTrack > 4)
    { Cube[FaceletsToTrack[ 4]] = tptr[Cube[FaceletsToTrack[ 4]]]; Cube[FaceletsToTrack[ 5]] = tptr[Cube[FaceletsToTrack[ 5]]];
      Cube[FaceletsToTrack[ 6]] = tptr[Cube[FaceletsToTrack[ 6]]]; Cube[FaceletsToTrack[ 7]] = tptr[Cube[FaceletsToTrack[ 7]]];
      if (NumFaceletsToTrack > 8)
      { Cube[FaceletsToTrack[ 8]] = tptr[Cube[FaceletsToTrack[ 8]]]; Cube[FaceletsToTrack[ 9]] = tptr[Cube[FaceletsToTrack[ 9]]];
        Cube[FaceletsToTrack[10]] = tptr[Cube[FaceletsToTrack[10]]]; Cube[FaceletsToTrack[11]] = tptr[Cube[FaceletsToTrack[11]]];
        if (NumFaceletsToTrack > 12)
        { Cube[FaceletsToTrack[12]] = tptr[Cube[FaceletsToTrack[12]]]; Cube[FaceletsToTrack[13]] = tptr[Cube[FaceletsToTrack[13]]];
          Cube[FaceletsToTrack[14]] = tptr[Cube[FaceletsToTrack[14]]]; Cube[FaceletsToTrack[15]] = tptr[Cube[FaceletsToTrack[15]]];
          if (NumFaceletsToTrack > 16)
          { Cube[FaceletsToTrack[16]] = tptr[Cube[FaceletsToTrack[16]]]; Cube[FaceletsToTrack[17]] = tptr[Cube[FaceletsToTrack[17]]];
            Cube[FaceletsToTrack[18]] = tptr[Cube[FaceletsToTrack[18]]]; Cube[FaceletsToTrack[19]] = tptr[Cube[FaceletsToTrack[19]]];
          }
        }
      }
    }
  }
*/

  __asm
  { // eax: Temporary. Its value is not important between pieces of code separated by a blank line.
    // ebx: Temporary. Its value is not important between pieces of code separated by a blank line.
    // ecx: cl: b. ch: NumFaceletsToTrack.
    // edx: tptr.
    // esi: Temporary. Its value is not important between pieces of code separated by a blank line.
    // edi: Temporary. Its value is not important between pieces of code separated by a blank line.
    // ebp: fptr.
            mov   ch, BYTE PTR NumFaceletsToTrack
            mov   edx, [esp+4]   // fptr.
            test  ch, ch
            mov   cl, [edx]
            jz    SHORT done
            test  cl, cl
            jz    SHORT done

            push  ebp
            push  ebx
            push  esi
            push  edi
            mov   ebp, edx

looptop:    movzx eax, cl
            mov   cl, [ebp+1]
            movzx edx, TurnCodeRev[eax]
            inc   ebp
            mov   esi, edx
            shl   edx, 4              // *16.
            test  cl, cl
            lea   edx, T1[edx*2+edx]  // *48.
            jz    SHORT doturns
              // esi contains n. Do not trash.
            movzx eax, cl
            lea   esi, [esi*8+esi]    //  9*n.
            movzx edx, TurnCodeRev[eax]
            mov   cl, [ebp+1]
            lea   edx, [esi*2+edx]    // 18*n + TurnCodeRev[b].
            inc   ebp
            mov   esi, edx
            shl   edx, 4              // *16.
            test  cl, cl
            lea   edx, T2[edx*2+edx]  // *48.
            jz    SHORT doturns
              // esi contains n. Do not trash.
            movzx eax, cl
            lea   esi, [esi*8+esi]    //  9*n.
            movzx edx, TurnCodeRev[eax]
            mov   cl, [ebp+1]
            lea   edx, [esi*2+edx]    // 18*n + TurnCodeRev[b].
            inc   ebp
            shl   edx, 4              // *16.
            lea   edx, T3[edx*2+edx]  // *48.

doturns:    cmp   ch, 4

            movzx esi, FaceletsToTrack+ 0
            movzx edi, FaceletsToTrack+ 1
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            movzx esi, FaceletsToTrack+ 2
            movzx edi, FaceletsToTrack+ 3
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            jng   SHORT loopbottom
            cmp   ch, 8

            movzx esi, FaceletsToTrack+ 4
            movzx edi, FaceletsToTrack+ 5
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            movzx esi, FaceletsToTrack+ 6
            movzx edi, FaceletsToTrack+ 7
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            jng   SHORT loopbottom
            cmp   ch, 12

            movzx esi, FaceletsToTrack+ 8
            movzx edi, FaceletsToTrack+ 9
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            movzx esi, FaceletsToTrack+10
            movzx edi, FaceletsToTrack+11
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            jng   SHORT loopbottom
            cmp   ch, 16

            movzx esi, FaceletsToTrack+12
            movzx edi, FaceletsToTrack+13
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            movzx esi, FaceletsToTrack+14
            movzx edi, FaceletsToTrack+15
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            jng   SHORT loopbottom

            movzx esi, FaceletsToTrack+16
            movzx edi, FaceletsToTrack+17
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

            movzx esi, FaceletsToTrack+18
            movzx edi, FaceletsToTrack+19
            movzx eax, Cube[esi]
            movzx ebx, Cube[edi]
            mov   al, [edx+eax]
            mov   bl, [edx+ebx]
            mov   Cube[esi], al
            mov   Cube[edi], bl

loopbottom: test  cl, cl
            jnz   looptop

            pop   edi
            pop   esi
            pop   ebx
            pop   ebp

done:       ret
  }
} // DoFormula

#pragma warning (default: 4731)

/********************************************************/
static void DoSolution (BYTE *solptr, BYTE *turnsbefore)
{ DWORD len;
  BYTE *ptr,*fptr;

  if (solptr == NULL) return; // This should never happen. (User input error.)
  fptr = FormulaPtr;
  for (ptr = turnsbefore; *ptr; ) *FormulaPtr++ = *ptr++;
  for (len = *solptr++; len > 0; len--) *FormulaPtr++ = *solptr++;
  *FormulaPtr = 0;
  if (turnsbefore[0]) FormulaPtr = fptr + EliminateXYZ(fptr,FormulaPtr-fptr,ptr-turnsbefore);
  DoFormula(fptr);
} // DoSolution

/********************************************************/
static BOOL DoPrefix (BYTE **prefixptr, DWORD searchdepth, BYTE *cube)
{ NumFaceletsToTrack = 20;
  if (searchdepth == 0)
  { if (*prefixptr) return FALSE;
    memcpy(Cube,cube,48);
    *prefixptr = (BYTE *)1;
    *(FormulaPtr = Formula) = 0;
    return TRUE;
  }
  if (*prefixptr == NULL) *prefixptr = Prefixes[searchdepth];
  if (*prefixptr - Prefixes[searchdepth] == (int)PrefixesSizeOf[searchdepth]) return FALSE;
  memcpy(Formula,*prefixptr,searchdepth);
  *(FormulaPtr = Formula+searchdepth) = 0;
  memcpy(Cube,cube,48);
  DoFormula(Formula);
  *prefixptr += searchdepth;
  return TRUE;
} // DoPrefix

/********************************************************/
static void ConvertColourCodesToSituation (BYTE *srccolourcodes, BYTE *dstcube)
{ BYTE i,j,k,it,idx,face,c0,c1,c2,*ptr,colourpermutation[8],possibilities[54],resolved[54],colourcodes[54];

  // Indices for centres: 4, and +9, +18, +27, +36, +45.
  // Indices for corners: 0,2,6,8, and +9, +18, +27, +36, +45.
  // Indices for edges  : 1,3,5,7, and +9, +18, +27, +36, +45.
  memset(dstcube,0xff,54);
  memset(resolved,0,54);
  // Make sure we have 6 1 3 5 2 4 for B V R O A L.
  colourpermutation[srccolourcodes[4+0*9]] = 1;
  colourpermutation[srccolourcodes[4+1*9]] = 4;
  colourpermutation[srccolourcodes[4+2*9]] = 2;
  colourpermutation[srccolourcodes[4+3*9]] = 3;
  colourpermutation[srccolourcodes[4+4*9]] = 6;
  colourpermutation[srccolourcodes[4+5*9]] = 5;
  for (i = 0; i < 54; i++) colourcodes[i] = colourpermutation[srccolourcodes[i]];
  // Resolve centres.
  for (i = 0; i < 6; i++)
  { idx = 9*i + 4;
    dstcube[InputTranslation[idx]] = (InputColourToFace[colourcodes[idx]-1] >> 3) + 48;
    resolved[idx] = 1;
  }
  // Resolve corners and edges. Step 1 of 2.
  for (i = 0; i < 2*4; i += 4)
  { ptr = (i == 0) ? InputCorners : InputEdges;
    for (j = 0; j < 6*9; j += 9)
    { for (k = 0; k < 4; k++)
      { idx = ptr[k] + j;
        face = InputColourToFace[colourcodes[idx]-1] + i;
        possibilities[idx] = face; // face+0 through face+3 are the possibilities.
      }
    }
  }
  // Resolve corners and edges. Step 2 of 2.
  for (c0 = 0; c0 < 54; c0++)
  { if (resolved[c0]) continue;
    if (((c0 % 9) & 1))
    { // Edge.
      it = InputTranslation[c0];
      c1 = InputTranslationRev[Connections[it][0]];
      // Resolve from possibilities[c0]+0..3 and possibilities[c1]+0..3.
      for (i = 0; i < 4; i++)
      { face = possibilities[c0] + i;
        if ((j = Connections[face][0] - possibilities[c1]) < 4) break;
      }
      dstcube[possibilities[c1]+j] = Connections[it][0];
      resolved[c0] = resolved[c1] = 1;
    } else
    { // Corner.
      it = InputTranslation[c0];
      c1 = InputTranslationRev[Connections[it][0]];
      c2 = InputTranslationRev[Connections[it][1]];
      // Resolve from possibilities[c0]+0..3 and possibilities[c1]+0..3 and possibilities[c2]+0..3.
      for (i = 0; i < 4; i++)
      { face = possibilities[c0] + i;
        if ((j = Connections[face][0] - possibilities[c1]) < 4)
        { if ((k = Connections[face][1] - possibilities[c2]) < 4)
          { dstcube[possibilities[c1]+j] = Connections[it][0];
            dstcube[possibilities[c2]+k] = Connections[it][1];
            break;
          }
        } else
        { if ((j = Connections[face][0] - possibilities[c2]) < 4)
          { if ((k = Connections[face][1] - possibilities[c1]) < 4)
            { dstcube[possibilities[c2]+j] = Connections[it][1];
              dstcube[possibilities[c1]+k] = Connections[it][0];
              break;
            }
          }
        }
      }
      resolved[c0] = resolved[c1] = resolved[c2] = 1;
    }
    dstcube[face] = it;
  }
} // ConvertColourCodesToSituation

/********************************************************/
static void ConvertRubixCodesToSituation (BYTE *srcrubixcodes, BYTE *dstcube)
{ BYTE i,colourcodes[54];

  for (i = 0; i < 54; i++) colourcodes[RubixInputToOurInput[i]] = srcrubixcodes[i];
  ConvertColourCodesToSituation(colourcodes,dstcube);
} // ConvertRubixCodesToSituation

/********************************************************/
static DWORD SequentialSituation (DWORD *indextable, DWORD valueslength, BYTE *situation, DWORD situationlength, DWORD *seqsittable)
{ if (situationlength == 2) return seqsittable[indextable[situation[0]] * valueslength + indextable[situation[1]]];
  // situationlength == 4.
  return seqsittable[((indextable[situation[0]] * valueslength + indextable[situation[1]]) * valueslength + indextable[situation[2]]) * valueslength + indextable[situation[3]]];
} // SequentialSituation

/********************************************************/
static void PrefixGeneratorAux (DWORD numturns, BYTE *formulaptr, BYTE lastturn)
{ BYTE i,facecode;

  facecode = lastturn & 0xf0;
  for (i = 0; i < 3; i++)
  { *formulaptr = lastturn++;
    if (numturns == 1)
    { // Prefix generated.
      memcpy(TempPtr,Formula,Length);
      TempPtr += Length;
    } else
    { // Skip the 3 turns of this face in case it is the same face or an opposing face in case of L, O, A.
      if (facecode != 0x30)
      { if (facecode != 0x00) PrefixGeneratorAux(numturns-1,formulaptr+1,0x01);
        PrefixGeneratorAux(numturns-1,formulaptr+1,0x31);
      }
      if (facecode != 0x40)
      { if (facecode != 0x10) PrefixGeneratorAux(numturns-1,formulaptr+1,0x11);
        PrefixGeneratorAux(numturns-1,formulaptr+1,0x41);
      }
      if (facecode != 0x50)
      { if (facecode != 0x20) PrefixGeneratorAux(numturns-1,formulaptr+1,0x21);
        PrefixGeneratorAux(numturns-1,formulaptr+1,0x51);
      }
    }
  }
} // PrefixGeneratorAux

/********************************************************/
static void PrefixGenerator (DWORD numturns, BYTE *tableptr)
{ BYTE i;

  Length = numturns;
  TempPtr = tableptr;
  for (i = 0; i < 6; i++) PrefixGeneratorAux(numturns,Formula,(BYTE)((i << 4) + 1));
} // PrefixGenerator

/********************************************************/
static BOOL ProcessF2LSolution (BYTE *ptr, BYTE *ptr2, BOOL dofilecreation)
{ ULONGLONG code;
  DWORD i,j,k,n,idx,len,sit;
  BYTE t,*fptr,*found1a,*found2a,*found1b,*found2b,facelets[4],formula[16],inverseformula[16],originalformula[16];

  if (dofilecreation)
  { n = 0;
    if ((len = Length) > 6)
    { n = len - 6;
      len = 6;
    }
    for (i = 0, fptr = formula; i < len; i++) *fptr++ = ptr[i];
    for (i = n; i > 0; )
    { t = ptr2[--i];
      *fptr++ = (t & 0xf0) + (-(signed char)t & 3);
    }
    *fptr = 0;
    len = Length;
  } else
  { len = (DWORD)ptr2;
    for (i = 0; i < len; i++) formula[len-i-1] = (ptr[i] & 0xf0) + (-(signed char)ptr[i] & 3);
    formula[len] = 0;
  }

  found1a = found2a = found1b = found2b = (BYTE *)1;
  for (k = 0; k < 3; k++)
  { if (k == 1)
    { if ((!found1a) && (!found2a)) continue;
      // Do mirror formula for "a".
      for (i = 0; i < len; i++)
      { t = originalformula[i];
        if (((t & 0xf0) == 0x00) || ((t & 0xf0) == 0x30)) t ^= 0x30;
        formula[i] = (t & 0xf0) + (-(signed char)t & 3);
      }
    }
    else if (k == 2)
    { if ((!found1b) && (!found2b)) continue;
      // Do Y2 formula for "b".
      for (i = 0; i < len; i++) formula[i] = (XYZTrans[1][1][originalformula[i] >> 4]) + (originalformula[i] & 3);
    }
    for (i = 0; i < 8; i++) Cube[FaceletsToTrack[i]] = FaceletsToTrack[i];
    DoFormula(formula);
    if (k <= 1) // 0,1.
    { // 1a.
      if (found1a)
      { found1a = NULL;
        if (F2L1aCount < F2L1aCounts[len])
        { for (i = 0; i < 4; i++) facelets[i] = Cube[F2L1aFacelets[i]];
          sit = SequentialSituation(IdxF2L1Corners,24,facelets,2,SeqSitF2L1Corners) + SequentialSituation(IdxF2L1Edges,16,facelets+2,2,SeqSitF2L1Edges);
          if (F2L1aSolutions[sit] == 0xff) // Note that if F2L1aSolutions[sit] equals len, then it is a same-length alternative for this situation.
          { *(found1a = &F2L1aSolutions[sit]) = (BYTE)len;
            F2L1aCount++;
          }
        }
      }
      // 2a.
      if (found2a)
      { found2a = NULL;
        if (F2L2aCount < F2L2aCounts[len]) if ((Cube[0] == 0) && (Cube[12] == 12) && (Cube[3] == 3) && (Cube[14] == 14))
        { for (i = 0; i < 4; i++) facelets[i] = Cube[F2L2aFacelets[i]];
          sit = SequentialSituation(IdxF2L2aCorners,18,facelets,2,SeqSitF2L2aCorners) + SequentialSituation(IdxF2L2aEdges,12,facelets+2,2,SeqSitF2L2aEdges);
          if (F2L2aSolutions[sit] == 0xff) // Note that if F2L2aSolutions[sit] equals len, then it is a same-length alternative for this situation.
          { *(found2a = &F2L2aSolutions[sit]) = (BYTE)len;
            F2L2aCount++;
          }
        }
      }
      if ((k == 1) && (!found1a) && (!found2a)) continue;
    }
    if ((k & 1) == 0) // 0,2.
    { // 1b.
      if (found1b)
      { found1b = NULL;
        if (F2L1bCount < F2L1bCounts[len])
        { for (i = 0; i < 4; i++) facelets[i] = Cube[F2L1bFacelets[i]];
          sit = SequentialSituation(IdxF2L1Corners,24,facelets,2,SeqSitF2L1Corners) + SequentialSituation(IdxF2L1Edges,16,facelets+2,2,SeqSitF2L1Edges);
          if (F2L1bSolutions[sit] == 0xff) // Note that if F2L1bSolutions[sit] equals len, then it is a same-length alternative for this situation.
          { *(found1b = &F2L1bSolutions[sit]) = (BYTE)len;
            F2L1bCount++;
          }
        }
      }
      // 2b.
      if (found2b)
      { found2b = NULL;
        if (F2L2bCount < F2L2bCounts[len]) if ((Cube[0] == 0) && (Cube[12] == 12) && (Cube[2] == 2) && (Cube[22] == 22))
        { for (i = 0; i < 4; i++) facelets[i] = Cube[F2L2bFacelets[i]];
          sit = SequentialSituation(IdxF2L2bCorners,18,facelets,2,SeqSitF2L2bCorners) + SequentialSituation(IdxF2L2bEdges,12,facelets+2,2,SeqSitF2L2bEdges);
          if (F2L2bSolutions[sit] == 0xff) // Note that if F2L2bSolutions[sit] equals len, then it is a same-length alternative for this situation.
          { *(found2b = &F2L2bSolutions[sit]) = (BYTE)len;
            F2L2bCount++;
          }
        }
      }
      if ((k == 2) && (!found1b) && (!found2b)) continue;
    }
    if ((k == 0) || (!dofilecreation))
    { if ((!found1a) && (!found2a) && (!found1b) && (!found2b)) return FALSE;
      if ((k == 0) || ((k == 1) && ((found1a) || (found2a))) || ((k == 2) && ((found1b) || (found2b))))
      { if (k == 0) memcpy(originalformula,formula,len+1);
        inverseformula[len] = 0;
        for (i = 0; i < len; i++) inverseformula[len-i-1] = (formula[i] & 0xf0) + (-(signed char)formula[i] & 3);
        NormaliseFormula(inverseformula,len);
      }
      if (dofilecreation)
      { // Pack inverseformula and store the result.
        i = len;
        code = 0;
        fptr = inverseformula;
        while (i > 0)
        { if ((n = i) > 5) n = 5;
          for (j = idx = 0; j < n; j++, fptr++) idx = 18*idx + TurnCodeRev[*fptr];
          code = code * NumOfPrefixes[n] + PrefixIndices[n][idx];
          i -= n;
        }
        code = (code << 4) + len;
        memcpy(TempPtr,&code,NumBytesForLengthF2L[len]);
        TempPtr += NumBytesForLengthF2L[len];
      } else
      { // Store inverseformula.
        if ((k == 0) || ((k == 1) && ((found1a) || (found2a))))
        { if (found1a) memcpy(found1a+1,inverseformula,len);
          if (found2a) memcpy(found2a+1,inverseformula,len);
        }
        if ((k == 0) || ((k == 2) && ((found1b) || (found2b))))
        { if (found1b) memcpy(found1b+1,inverseformula,len);
          if (found2b) memcpy(found2b+1,inverseformula,len);
        }
      }
    }
  }
  return ((F2L2bCount == F2L2bCounts[len]) && (F2L2aCount == F2L2aCounts[len]) && (F2L1bCount == F2L1bCounts[len]) && (F2L1aCount == F2L1aCounts[len])); // To allow early-out.
} // ProcessF2LSolution

/********************************************************/
static void ProcessL3Solution (BYTE *formula, DWORD len)
{ DWORD i,j,k,sit;
  BYTE t,*ptr,facelets[8],inverseformula[20],tempformula[20];

  inverseformula[len] = tempformula[len] = 0;
  for (i = 0; i < 4; i++)
  { // Do a Y turn i times.
    for (j = 0; j < 4; j++)
    { // Do nothing, inverse, mirror, mirror-inverse.
      switch (j)
      { case 0: // Nothing.
          memcpy(tempformula,formula,len);
          break;
        case 1: // Inverse.
          for (k = 0; k < len; k++) tempformula[len-k-1] = (formula[k] & 0xf0) + (-(signed char)formula[k] & 3);
          break;
        case 2: // Mirror.
          for (k = 0; k < len; k++)
          { t = formula[k];
            if (((t & 0xf0) == 0x00) || ((t & 0xf0) == 0x30)) t ^= 0x30;
            tempformula[k] = (t & 0xf0) + (-(signed char)t & 3);
          }
          break;
        case 3: // Mirror-inverse.
          for (k = 0; k < len; k++)
          { t = formula[k];
            if (((t & 0xf0) == 0x00) || ((t & 0xf0) == 0x30)) t ^= 0x30;
            tempformula[len-k-1] = t;
          }
          break;
      }

      for (k = 0; k < 8; k++) Cube[FaceletsToTrack[k]] = FaceletsToTrack[k];
      DoFormula(tempformula);
      for (k = 0; k < 8; k++) facelets[k] = Cube[FaceletsToTrack[k]];

      sit = SequentialSituation(IdxL3Corners,12,facelets,4,SeqSitL3Corners) + SequentialSituation(IdxL3Edges,8,facelets+4,4,SeqSitL3Edges);
      if (L3Solutions[sit]) continue; // Meaning it is an alternative for this situation.
      for (k = 0; k < len; k++) inverseformula[len-k-1] = (tempformula[k] & 0xf0) + (-(signed char)tempformula[k] & 3);
      NormaliseFormula(inverseformula,len);
      ptr = inverseformula;
      if (len > 3)
      { // Change "formula starting with O face" to "ending with O face" (so change "On P" to "Py' On", AND ALSO "Bn On P" to "Bn Py' On").
        // Note that this improves the cancelling out of turns, and that if not doing this, it will never get worse. This is because solutions
        // up to this point will never end in a turn of the O face because the previous stage would already have been solved without that
        // final O face turn.
        if ((ptr[0] & 0xf0) == 0x40)
        { ptr[len] = t = ptr[0];
          ptr++;
        } else
        if (((ptr[0] & 0xf0) == 0x10) && ((ptr[1] & 0xf0) == 0x40))
        { t = ptr[1];
          ptr[1] = ptr[0];
          ptr[len] = t;
          ptr++;
        }
        if (ptr > inverseformula)
        { t = (t & 3) ^ 3;
          for (k = 0; k < len; k++) ptr[k] = (XYZTrans[1][t][ptr[k] >> 4]) + (ptr[k] & 3);
          NormaliseFormula(ptr,len);
        }
      }
      L3Solutions[sit] = FormulaPtr;
      *FormulaPtr = (BYTE)len;
      memcpy(FormulaPtr+1,ptr,len);
      FormulaPtr += 17;
    }
    // Do Y.
    if (i < 3) for (k = 0; k < len; k++) formula[k] = (XYZTrans[1][0][formula[k] >> 4]) + (formula[k] & 3);
  }
} // ProcessL3Solution

/********************************************************/
static void InitF2LStuff ()
{ memset(F2L1aSolutions,0xff,sizeof(F2L1aSolutions));
  memset(F2L1bSolutions,0xff,sizeof(F2L1bSolutions));
  memset(F2L2aSolutions,0xff,sizeof(F2L2aSolutions));
  memset(F2L2bSolutions,0xff,sizeof(F2L2bSolutions));
  F2L1aCount = F2L1bCount = F2L2aCount = F2L2bCount = 0;
  NumFaceletsToTrack = 8;
  memcpy(FaceletsToTrack,FaceletsToTrackF2L,8);
} // InitF2LStuff

/********************************************************/
static void UnpackFormula (BYTE *dstptr, ULONGLONG code, BYTE length)
{ BYTE n;
  DWORD idx;

  while (length)
  { if ((n = length % 5) == 0) n = 5;
    length -= n;
    idx = (DWORD)(code % NumOfPrefixes[n]);
    code /= NumOfPrefixes[n];
    memcpy(dstptr+length,Prefixes[n]+idx*n,n);
  }
} // UnpackFormula

/********************************************************/
static void UnpackCrossSolutions (DWORD numsituations)
{ DWORD i;
  ULONGLONG code;
  BYTE b,*srcptr,*dstptr;

  srcptr = PackedBuffer;
  dstptr = CrossSolutions;
  numsituations >>= 3;
  do
  { code = *(ULONGLONG *)srcptr;
    for (i = 8; i > 0; i--)
    { if ((b = (BYTE)code & 0x1f)) b = TurnCode[b-1];
      *dstptr++ = b;
      code >>= 5;
    }
    srcptr += 5;
  } while (--numsituations);
} // UnpackCrossSolutions

/********************************************************/
static void UnpackF2LSolutions (DWORD numformulas)
{ ULONGLONG code;
  BYTE len,inc,*srcptr,formula[20];

  InitF2LStuff();
  srcptr = PackedBuffer;
  do
  { code = 0;
    len = *srcptr & 0x0f;
    memcpy(&code,srcptr,inc=NumBytesForLengthF2L[len]);
    UnpackFormula(formula,code >> 4,len);
    ProcessF2LSolution(formula,(BYTE *)len,FALSE);
    srcptr += inc;
  } while (--numformulas);
} // UnpackF2LSolutions

/********************************************************/
static void UnpackL3Solutions (DWORD numformulas)
{ DWORD t,longcode[3];
  BYTE len,inc,*srcptr,formula[20];

  FormulaPtr = L3Formulas;
  NumFaceletsToTrack = 8;
  memcpy(FaceletsToTrack,L3Facelets,8);
  memset(L3Solutions,0,sizeof(L3Solutions));
  srcptr = PackedBuffer;
  do
  { longcode[0] = longcode[1] = longcode[2] = 0;
    len = *srcptr & 0x1f;
    memcpy(longcode,srcptr,inc=NumBytesForLengthL3[len]);
    // Divide longcode by 32.
    t = longcode[1];
    *(ULONGLONG *)longcode >>= 5;
    longcode[1] = t;
    *(ULONGLONG *)(longcode+1) >>= 5;
    // Now, longcode fits in a ULONGLONG.
    UnpackFormula(formula,*(ULONGLONG *)longcode,len);
    ProcessL3Solution(formula,len);
    srcptr += inc;
  } while (--numformulas);
} // UnpackL3Solutions

/********************************************************/
static void ProcessCrossSolution ()
{ BYTE turn;
  DWORD i,idx,situation;

  situation = SequentialSituation(IdxCrossEdges,24,Cube+4,4,SeqSitCrossEdges);
  if (Length <= 6)
  { // Fn*[] stuff.
    memcpy(TempPtr,Formula,Length);
    *(DWORD *)(TempPtr+Length) = situation;
    TempPtr += Length+4;
    if (Length < 6)
    { for (i = idx = 0; i < Length; i++) idx = 18*idx + TurnCodeRev[Formula[i]];
      PrefixIndices[Length][idx] = PrefixIndex++;
    }
  }
  if (CrossSolutions[situation] != 0xff) return; // We already have a solution for this situation.
  CrossCount++;
  if (Length == 0) { CrossSolutions[situation] = 0x00; return; }
  turn = Formula[Length-1];
  if (Length >= 2)
  { // Normalise the inverse because we store the inverse of the last turn.
    if ((turn & 0xf0) - (Formula[Length-2] & 0xf0) == 0x30) turn = Formula[Length-2];
  }
  CrossSolutions[situation] = (turn & 0xf0) + (-(signed char)turn & 3);
} // ProcessCrossSolution

/********************************************************/
static void CrossGeneratorAux (DWORD numturns, BYTE *formulaptr, BYTE lastturn)
{ DWORD savedcube;
  BYTE i,facecode,*tptr;

  if ((Length > 6) && (CrossCount == CrossCounts[Length])) return; // Early-out for > 6; we need <= 6 for the Fn*[] arrays.

  savedcube = *(DWORD *)(Cube+4);
  facecode = lastturn & 0xf0;
  tptr = T[lastturn >> 4][1];

  for (i = 0; i < 3; i++)
  { Cube[4] = tptr[Cube[4]]; Cube[5] = tptr[Cube[5]]; Cube[6] = tptr[Cube[6]]; Cube[7] = tptr[Cube[7]];
    *formulaptr = lastturn++;
    if (numturns == 1)
    { // At this point, we have generated a formula and we can do something with it.
      ProcessCrossSolution();
    } else
    { if (facecode != 0x30)
      { if (facecode != 0x00) CrossGeneratorAux(numturns-1,formulaptr+1,0x01);
        CrossGeneratorAux(numturns-1,formulaptr+1,0x31);
      }
      if (facecode != 0x40)
      { if (facecode != 0x10) CrossGeneratorAux(numturns-1,formulaptr+1,0x11);
        CrossGeneratorAux(numturns-1,formulaptr+1,0x41);
      }
      if (facecode != 0x50)
      { if (facecode != 0x20) CrossGeneratorAux(numturns-1,formulaptr+1,0x21);
        CrossGeneratorAux(numturns-1,formulaptr+1,0x51);
      }
    }
  }
  *(DWORD *)(Cube+4) = savedcube;
} // CrossGeneratorAux

/********************************************************/
static void GenerateCrossFormulas (FILE *f)
{ ULONGLONG result;
  BYTE *srcptr,*dstptr,buf[8];
  DWORD i,recsize,sit,lastsit,len190080;
  // Also generates the Fn*[] arrays since that can be done "almost for free" at the same time.

  CrossCount = 0;
  memset(CrossSolutions,0xff,sizeof(CrossSolutions));
  for (Length = len190080 = 0; Length <= 8; Length++)
  { PrefixIndex = 0;
    if (Length <= 6) TempPtr = FnPointers[Length];
    Cube[4] = 4; Cube[5] = 5; Cube[6] = 6; Cube[7] = 7;
    if (Length == 0)
    { // At this point, we have generated a formula and we can do something with it.
      ProcessCrossSolution();
    } else
    { for (i = 0; i < 6; i++) CrossGeneratorAux(Length,Formula,(BYTE)((i << 4) + 1)); }
    if (Length <= 6)
    { // Fn*[] stuff.
      BJWRadixExchangeSort(FnPointers[Length],FnSizeOf[Length] / (Length+4) - 1,Length+4);
      *(DWORD *)(FnPointers[Length]+FnSizeOf[Length]-4) = (DWORD)(-1);
      // Create lookup pointers.
      recsize = Length + 4;
      srcptr = FnPointers[Length];
      lastsit = (DWORD)(-1);
      while ((sit = *(DWORD *)(srcptr+Length)) != (DWORD)(-1))
      { if (sit != lastsit) FnSituations[len190080+sit] = srcptr;
        lastsit = sit;
        srcptr += recsize;
      }
      len190080 += 190080;
    }
  }
  // Pack them.
  srcptr = CrossSolutions;
  dstptr = PackedBuffer;
  do
  { result = 0;
    memcpy(buf,srcptr,8);
    for (i = 0; i < 8; i++)
    { if (buf[i]) buf[i] = TurnCodeRev[buf[i]]+1;
      result |= ((ULONGLONG)buf[i] << (5*i));
    }
    memcpy(dstptr,&result,5);
    dstptr += 5;
    srcptr += 8;
  } while (srcptr - CrossSolutions != 190080);
  // Write them.
  fwrite(PackedBuffer,1,SizeOfCrossSolutionsPacked,f);
} // GenerateCrossFormulas

/********************************************************/
static void F2LGenerator (DWORD numturns)
{ BYTE ft,ft2,*ptr,*ptr2;
  DWORD n,n190080,sit,recsize,idx,*idxptr;

  // For lengths 0 through 6, we simply use the array of the length in question.
  if (numturns <= 6)
  { recsize = numturns + 4;
    if ((ptr = FnSituations[numturns*190080+0]))
    { while (*(DWORD *)(ptr+numturns) == 0)
      { // This is a cross-invariant formula; do something with it.
        if (ProcessF2LSolution(ptr,NULL,TRUE)) return; // Early-out; nothing more to be found at this length.
        ptr += recsize;
      }
    }
    return;
  }
  // For lengths 7 through 12 (i.e. 6+n (1 <= n <= 6)), we use the array for length 6 and the array for length n.
  if (numturns == 11) idxptr = BJWF2L11Solutions;
  else if (numturns == 12) idxptr = BJWF2L12Solutions;
  n = numturns - 6;
  n190080 = n * 190080;
  recsize = n + 4;
  ptr = FnPointers[6];
  if (numturns >= 11) ptr += idxptr[idx=0];
  while ((sit = *(DWORD *)(ptr+6)) != (DWORD)(-1))
  { ft = ptr[6-1] & 0xf0; // Face turn code.
    if ((ptr2 = FnSituations[n190080+sit]))
    { do
      { // This might be one, but only if its length is really 'numturns', i.e. if no turns cancel each other out. Also never let an "inexpensive" turn be followed by its "expensive" opposite turn.
        ft2 = ft - (ptr2[n-1] & 0xf0);
        if ((ft2 != 0) && (ft2 != 0x30))
        { // This still might not be one because we do not want to combine things like A'O'V' and V A (resulting in A'O'V'A V).
          if ((n == 1) || (ft2 != 0xd0) || ((ptr2[n-1] & 0xf0) - (ptr2[n-2] & 0xf0) != 0x30))
          { // This is a cross-invariant formula; do something with it.
            if (ProcessF2LSolution(ptr,ptr2,TRUE)) return; // Early-out; nothing more to be found at this length.
          }
        }
        ptr2 += recsize;
      } while (*(DWORD *)(ptr2+n) == sit);
    }
    ptr += 6+4;
    if (numturns >= 11) ptr = FnPointers[6] + idxptr[++idx];
  }
} // F2LGenerator

/********************************************************/
static void GenerateF2LFormulas (FILE *f)
{ InitF2LStuff();
  TempPtr = PackedBuffer;
  for (Length = 0; Length <= 12; Length++) F2LGenerator(Length);
  // Write them.
  fwrite(PackedBuffer,1,SizeOfF2LSolutionsPacked,f);
} // GenerateF2LFormulas

/********************************************************/
static void GenerateL3Formulas (FILE *f)
{ fwrite(BJWPackedL3Solutions,1,SizeOfL3SolutionsPacked,f);
} // GenerateL3Formulas

/********************************************************/
static void CreateLookupFile ()
{ FILE *f;
  DWORD i,num;

  if (MessageBox(0,"Ben Jos Walbeehm's 3x3x3 solver needs to generate some tables the first time you run it.\n"
     "This may take a few minutes.\n\nContinue?","RUBIX by Ken Silverman",MB_OKCANCEL) == IDCANCEL) return;

  FnSituations = (BYTE **)malloc(7*190080*sizeof(BYTE *));
  memset(FnSituations,0,7*190080*sizeof(BYTE *));
  for (i = 0; i < 7; i++) FnPointers[i] = (BYTE *)malloc(FnSizeOf[i]);
  for (i = 0, num = sizeof(DWORD); i < 6; i++, num *= 18) PrefixIndices[i] = (DWORD *)malloc(num);
  f = fopen(LookupFileName,"wb");
  fwrite(&LookupFileVersion,1,sizeof(LookupFileVersion),f);
  GenerateCrossFormulas(f);
  GenerateF2LFormulas(f);
  GenerateL3Formulas(f);
  fclose(f);
  for (i = 6; i > 0; ) free(PrefixIndices[--i]);
  for (i = 7; i > 0; ) free(FnPointers[--i]);
  free(FnSituations);
} // CreateLookupFile

/********************************************************/
static BOOL CorrectLookupFileExists ()
{ FILE *f;
  BOOL correctexists;
  DWORD numread,version,size;

  if ((f = fopen(LookupFileName,"rb")) == NULL) return FALSE;
  size = _filelength(_fileno(f));
  numread = fread(&version,1,sizeof(LookupFileVersion),f);
  fclose(f);
  correctexists = ((size == LookupFileSize) && (numread == sizeof(LookupFileVersion)) && (version == LookupFileVersion));
  if (!correctexists) remove(LookupFileName);
  return correctexists;
} // CorrectLookupFileExists

/********************************************************/
static void InitIdxAndSeqSit (BYTE *facelets, DWORD numfacelets, DWORD numtopick, DWORD multiplier, DWORD *indextable, DWORD *seqsittable)
{ BYTE bi,bj,bk,bm;
  DWORD i,j,k,m,ij,num;

  for (i = num = 0; i < numfacelets; i++)
  { indextable[facelets[i]] = i;
    bi = facelets[i];
    for (j = 0; j < numfacelets; j++)
    { if (j == i) continue;
      bj = facelets[j];
      if (Connections[bj][0] == bi) continue;
      if (Connections[bj][1] == bi) continue;
      ij = i * numfacelets + j;
      if (numtopick == 2)
      { seqsittable[ij] = num;
        num += multiplier;
      } else
      { // numtopick == 4.
        for (k = 0; k < numfacelets; k++)
        { if ((k == i) || (k == j)) continue;
          bk = facelets[k];
          if ((Connections[bk][0] == bi) || (Connections[bk][0] == bj)) continue;
          if ((Connections[bk][1] == bi) || (Connections[bk][1] == bj)) continue;
          for (m = 0; m < numfacelets; m++)
          { if ((m == i) || (m == j) || (m == k)) continue;
            bm = facelets[m];
            if ((Connections[bm][0] == bi) || (Connections[bm][0] == bj) || (Connections[bm][0] == bk)) continue;
            if ((Connections[bm][1] == bi) || (Connections[bm][1] == bj) || (Connections[bm][1] == bk)) continue;
            seqsittable[(ij * numfacelets + k) * numfacelets + m] = num;
            num += multiplier;
          }
        }
      }
    }
  }
} // InitIdxAndSeqSit

/********************************************************/
static BOOL Initialise (BOOL full)
{ FILE *f;
  BYTE b,c[54];
  DWORD i,j,k,n,version;

  if (!PartiallyInitialised)
  { // Initialise InputTranslationRev[].
    for (i = 0; i < 54; i++) InputTranslationRev[InputTranslation[i]] = (BYTE)i;
    // Initialise RubixInputToOurInput[]. Note that this requires InputTranslationRev[] to be initialised first.
    for (i = 0; i < 54; i++) RubixInputToOurInput[i] = InputTranslationRev[Rubix[i]];
    // Initialise ParityColours[] and ParityCubelets[]. We use 0 for black and 1 for white. These values makes things easier in Get3x3x3Parity().
    memset(ParityColours,1,48);
    for (i = 0; i < 12; i++)
    { b = ParityEdges[i];
      ParityColours[b] = 0;
      ParityCubelets[b] = ParityCubelets[Connections[b][0]] = (BYTE)i;
    }
    for (i = 0; i < 8; i++)
    { b = ParityCorners[i];
      ParityColours[b] = 0;
      ParityCubelets[b] = ParityCubelets[Connections[b][0]] = ParityCubelets[Connections[b][1]] = (BYTE)i;
    }
    PartiallyInitialised = TRUE;
  }
  if (!full) return TRUE;

  // Initialise T[][][].
  for (n = 0; n < 12; n++)
  { for (i = 0; i < 54; i++) c[i] = T[n][1][i];
    for (k = 2; k <= 4; k++) for (i = 0; i < 54; i++) T[n][k&3][i] = c[i] = T[n][1][c[i]];
  }
  // Initialise TT[][]. Note that this requires T[][][] to be initialised first.
  for (i = 0; i < 36; i++)
  { k = TurnCode[i];
    TT[k] = T[k >> 4][k & 3];
  }
  // Initialise T1[][]. Note that this requires T[][][] to be initialised first.
  for (n = i = 0; n < 6; n++)
  { for (k = 1; k < 4; k++)
    { memcpy(T1[i],T[n][k],48);
      i++;
    }
  }
  // Initialise T2[][]. Note that this requires T1[][] to be initialised first.
  for (j = n = 0; j < 18; j++)
  { for (k = 0; k < 18; k++)
    { for (i = 0; i < 48; i++) T2[n][i] = T1[k][T1[j][i]];
      n++;
    }
  }
  // Initialise T3[][]. Note that this requires T1[][] and T2[][] to be initialised first.
  for (j = n = 0; j < 18*18; j++)
  { for (k = 0; k < 18; k++)
    { for (i = 0; i < 48; i++) T3[n][i] = T1[k][T2[j][i]];
      n++;
    }
  }
  // Initialise TurnCodeRev[].
  for (i = 0; i < 36; i++) TurnCodeRev[TurnCode[i]] = (BYTE)i;
  // Initialise the Idx*[] and SeqSit*[] arrays.
  InitIdxAndSeqSit(CrossEdges  ,24,4,              1,IdxCrossEdges  ,SeqSitCrossEdges  );
  InitIdxAndSeqSit(F2L1Corners ,24,2, 8*7 * 2*2 * 13,IdxF2L1Corners ,SeqSitF2L1Corners );
  InitIdxAndSeqSit(F2L1Edges   ,16,2,             13,IdxF2L1Edges   ,SeqSitF2L1Edges   );
  InitIdxAndSeqSit(F2L2aCorners,18,2, 6*5 * 2*2 * 13,IdxF2L2aCorners,SeqSitF2L2aCorners);
  InitIdxAndSeqSit(F2L2aEdges  ,12,2,             13,IdxF2L2aEdges  ,SeqSitF2L2aEdges  );
  InitIdxAndSeqSit(F2L2bCorners,18,2, 6*5 * 2*2 * 13,IdxF2L2bCorners,SeqSitF2L2bCorners);
  InitIdxAndSeqSit(F2L2bEdges  ,12,2,             13,IdxF2L2bEdges  ,SeqSitF2L2bEdges  );
  InitIdxAndSeqSit(L3Corners   ,12,4,4*3*2 * 2*2*2*2,IdxL3Corners   ,SeqSitL3Corners   );
  InitIdxAndSeqSit(L3Edges     , 8,4,              1,IdxL3Edges     ,SeqSitL3Edges     );
  // Initialise the Prefix?[] arrays.
  for (i = 1; i <= 5; i++) PrefixGenerator(i,Prefixes[i]);
  // Initialise the lookup tables. Note that this requires everything else to be initialised first in case the lookup file has to be generated.
  if (!CorrectLookupFileExists()) CreateLookupFile();
  if ((f = fopen(LookupFileName,"rb")) == NULL) return FALSE;
  if ((fread(&version,1,sizeof(LookupFileVersion),f) != sizeof(LookupFileVersion)) || (version != LookupFileVersion)) { fclose(f); return FALSE; }
  if (fread(PackedBuffer,1,SizeOfCrossSolutionsPacked,f) != SizeOfCrossSolutionsPacked) { fclose(f); return FALSE; } // cross.333.
  UnpackCrossSolutions(190080);
  if (fread(PackedBuffer,1,SizeOfF2LSolutionsPacked,f) != SizeOfF2LSolutionsPacked) { fclose(f); return FALSE; }     // F2L.333.
  UnpackF2LSolutions(139572);
  if (fread(PackedBuffer,1,SizeOfL3SolutionsPacked,f) != SizeOfL3SolutionsPacked) { fclose(f); return FALSE; }       // L3.333.
  UnpackL3Solutions(4623);
  fclose(f);

  Initialised = TRUE;
  return TRUE;
} // Initialise

/********************************************************/
static void GetBeforeTurns (DWORD crossnum, DWORD f2lnum, BYTE *turnsbefore)
{ BYTE t;
  DWORD i;

  i = 0;
  if ((t = CrossTurnBefore[crossnum])) turnsbefore[i++] = t;
  if ((t = F2LTurnBefore[f2lnum])) turnsbefore[i++] = t;
  turnsbefore[i] = 0;
} // GetBeforeTurns

/********************************************************/
static void GetCubeAdjustment (BYTE *srcfacelets, BYTE *dstfacelets, DWORD numfacelets, DWORD crossnum, DWORD f2lnum)
{ DWORD i;

  for (i = 0; i < numfacelets; i++) dstfacelets[i] = SolveF2LPtr[f2lnum][0][SolveCrossPtr[crossnum][0][Cube[SolveCrossPtr[crossnum][1][SolveF2LPtr[f2lnum][1][srcfacelets[i]]]]]];
} // GetCubeAdjustment

/********************************************************/
static void GetFaceletsToTrack (DWORD crossnum, DWORD f2lnum)
{ DWORD i;

  if (f2lnum < 4)
  { for (i = 0; i < 20; i++) FaceletsToTrack[i] = SolveCrossPtr[crossnum][1][SolveF2LPtr[f2lnum][1][FaceletsToTrackA[i]]]; } else
  { f2lnum -= 4;
    for (i = 0; i < 20; i++) FaceletsToTrack[i] = SolveCrossPtr[crossnum][1][SolveF2LPtr[f2lnum][1][FaceletsToTrackB[i]]];
  }
} // GetFaceletsToTrack

/********************************************************/
static BOOL SolveCross (DWORD crossnum, BYTE turnbefore, DWORD searchdepth)
{ BOOL first;
  BYTE d,t,facelets[4];

  first = TRUE;
  for (;;)
  { GetCubeAdjustment(CrossFacelets,facelets,4,crossnum,0);
    if ((t = *FormulaPtr = CrossSolutions[SequentialSituation(IdxCrossEdges,24,facelets,4,SeqSitCrossEdges)]) == 0x00) break;
    if (turnbefore) t = *FormulaPtr = XYZTrans[(turnbefore - 0x90) >> 4][(turnbefore & 3) - 1][t >> 4] + (t & 3);
    if (first)
    { if ((searchdepth) && (((d = (*(FormulaPtr-1) & 0xf0) - (t & 0xf0)) == 0x00) || (d == 0x30))) return FALSE; // Early-out. We have found or will find this solution elsewhere.
      first = FALSE;
    }
    *++FormulaPtr = 0;
    DoFormula(FormulaPtr-1);
  }
  return TRUE;
} // SolveCross

/********************************************************/
static void SolveF2L1a (DWORD crossnum, DWORD f2lnum, BYTE *turnsbefore)
{ DWORD sit;
  BYTE facelets[4];

  NumFaceletsToTrack = 12;
  GetCubeAdjustment(F2L1aFacelets,facelets,4,crossnum,f2lnum);
  sit = SequentialSituation(IdxF2L1Corners,24,facelets,2,SeqSitF2L1Corners) + SequentialSituation(IdxF2L1Edges,16,facelets+2,2,SeqSitF2L1Edges);
  DoSolution(F2L1aSolutions+sit,turnsbefore);
} // SolveF2L1a

/********************************************************/
static void SolveF2L1b (DWORD crossnum, DWORD f2lnum, BYTE *turnsbefore)
{ DWORD sit;
  BYTE facelets[4];

  NumFaceletsToTrack = 12;
  GetCubeAdjustment(F2L1bFacelets,facelets,4,crossnum,f2lnum);
  sit = SequentialSituation(IdxF2L1Corners,24,facelets,2,SeqSitF2L1Corners) + SequentialSituation(IdxF2L1Edges,16,facelets+2,2,SeqSitF2L1Edges);
  DoSolution(F2L1bSolutions+sit,turnsbefore);
} // SolveF2L1b

/********************************************************/
static void SolveF2L2a (DWORD crossnum, DWORD f2lnum, BYTE *turnsbefore)
{ DWORD sit;
  BYTE facelets[4];

  NumFaceletsToTrack = 8;
  GetCubeAdjustment(F2L2aFacelets,facelets,4,crossnum,f2lnum);
  sit = SequentialSituation(IdxF2L2aCorners,18,facelets,2,SeqSitF2L2aCorners) + SequentialSituation(IdxF2L2aEdges,12,facelets+2,2,SeqSitF2L2aEdges);
  DoSolution(F2L2aSolutions+sit,turnsbefore);
} // SolveF2L2a

/********************************************************/
static void SolveF2L2b (DWORD crossnum, DWORD f2lnum, BYTE *turnsbefore)
{ DWORD sit;
  BYTE facelets[4];

  NumFaceletsToTrack = 8;
  GetCubeAdjustment(F2L2bFacelets,facelets,4,crossnum,f2lnum);
  sit = SequentialSituation(IdxF2L2bCorners,18,facelets,2,SeqSitF2L2bCorners) + SequentialSituation(IdxF2L2bEdges,12,facelets+2,2,SeqSitF2L2bEdges);
  DoSolution(F2L2bSolutions+sit,turnsbefore);
} // SolveF2L2b

/********************************************************/
static void SolveF2L (DWORD crossnum, DWORD f2lnum, BYTE *turnsbefore)
{ if (f2lnum < 4)
  { SolveF2L1a(crossnum,f2lnum,turnsbefore);
    SolveF2L2a(crossnum,f2lnum,turnsbefore);
  } else
  { SolveF2L1b(crossnum,f2lnum-4,turnsbefore);
    SolveF2L2b(crossnum,f2lnum-4,turnsbefore);
  }
} // SolveF2L

/********************************************************/
static void SolveL3 (DWORD crossnum, DWORD f2lnum, BYTE *turnsbefore)
{ DWORD sit;
  BYTE facelets[8];

  NumFaceletsToTrack = 0;
  GetCubeAdjustment(L3Facelets,facelets,8,crossnum,f2lnum);
  sit = SequentialSituation(IdxL3Corners,12,facelets,4,SeqSitL3Corners) + SequentialSituation(IdxL3Edges,8,facelets+4,4,SeqSitL3Edges);
  DoSolution(L3Solutions[sit],turnsbefore);
} // SolveL3

/********************************************************/
// Number of solutions it will try per search depth, if it were not for early-outs. This is equal to NumOfPrefixes[searchdepth] * 36.
//   0:         36
//   1:        648
//   2:      8,748
//   3:    116,640
//   4:  1,557,144
//   5: 20,785,248
static int SolveCube (BYTE *cube, DWORD searchdepth, BYTE *minformula, BOOL sliceis1)
{ DWORD i,k,m,len,minlen,num180,minnum180;
  BYTE *prefixptr,savedcube[48],tcb[4],tb[4];

  for (i = 0; (i < 48) && (cube[i] == i); i++) ;
  if (i == 48) return 0;
  memcpy(savedcube,cube,48);
  minlen = minnum180 = (DWORD)(-1);
  for (k = 0; k < 6; k++)
  { GetBeforeTurns(k,0,tcb);
    for (m = 0; m < 6; m++)
    { GetBeforeTurns(k,m & 3,tb);
      GetFaceletsToTrack(k,m);
      prefixptr = NULL;
      while (DoPrefix(&prefixptr,searchdepth,savedcube))
      { if (!SolveCross(k,tcb[0],searchdepth)) continue; // We have found or will find this solution elsewhere. This makes us skip around 23% of the solutions while still finding the best this algorithm offers!
        SolveF2L(k,m,tb);
        SolveL3(k,m & 3,tb);
        len = NormaliseFormula(Formula,FormulaPtr-Formula);
        if (sliceis1) len = NormaliseSliceTurns(Formula,len,minlen);
        if (len <= minlen)
        { for (i = num180 = 0; i < len; i++) if ((Formula[i] & 3) == 2) num180++;
          if ((len < minlen) || (num180 < minnum180))
          { memcpy(minformula,Formula,len+1);
            minlen = len;
            minnum180 = num180;
            if (minlen <= 4) return (int)minlen; // Use an early-out. If a solution of length <= 4 is found, no shorter solutions are possible.
          }
        }
      }
    }
  }
  return (int)minlen;
} // SolveCube

/********************************************************/
BYTE Get3x3x3Parity (BYTE *rubixcodes)
{ BYTE b,i,num,parity,cubelets[12],cubeletsrev[12];
  // Parity = (CornerParity{0..2} * 3 + EdgeParity{0..1}) * 2 + SwapParity{0..1}. So values 0..15 are possible. Of those 15 values, only a value of 0 means a solvable cube.

  Initialise(FALSE);
  ConvertRubixCodesToSituation(rubixcodes,Cube);
  memcpy(SavedCube,Cube,54);

  // Corner parity. Do a modulo 3 count of the number of clockwise corner twists to make the facelets in the given positions black.
  // The following is a slightly more efficient implementation of that, using the fact that black = 0 and white = 1.
  for (i = num = 0; i < 8; i++) if (ParityColours[b=Cube[ParityCorners[i]]]) num += ParityColours[Connections[b][0]]+1;
  parity = (num % 3) * 3;
  // Edge parity. Do a modulo 2 count of the number of black facelets in the given positions.
  // The following is a slightly more efficient implementation of that (actually counting white), using the fact that black = 0 and white = 1.
  for (i = num = 0; i < 12; i++) num += ParityColours[Cube[ParityEdges[i]]];
  parity += (num & 1);
  // Swap parity. Do a series of swaps between edge cubelets followed by a series of swaps between corner cubelets to put all cubelets in their correct place.
  // Uses the fact that a swap of two corners or a swap of two edges is impossible, but two swaps are not impossible. Take the total number of swaps modulo 2.
  for (i = num = 0; i < 12; i++) cubeletsrev[cubelets[i]=ParityCubelets[Cube[ParityEdges[i]]]] = i;
  for (i = 0; i < 12-1; i++) if (cubelets[i] != i) { cubeletsrev[cubelets[cubeletsrev[i]]=cubelets[i]] = cubeletsrev[i]; num++; }
  for (i = 0; i < 8; i++) cubeletsrev[cubelets[i]=ParityCubelets[Cube[ParityCorners[i]]]] = i;
  for (i = 0; i < 8-1; i++) if (cubelets[i] != i) { cubeletsrev[cubelets[cubeletsrev[i]]=cubelets[i]] = cubeletsrev[i]; num++; }

  return (parity << 1) + (num & 1);
} // Get3x3x3Parity

/********************************************************/
int BJWSolve3CubeFromRubix (unsigned short *rotlist, int quality)
{ int i,len;
  BYTE formula[64];

  if (!Initialised) if (!Initialise(TRUE)) return -5;

  // The CheckValidity() function in bjwsolve.c has already converted the Rubix input into our SavedCube[].
  len = SolveCube(SavedCube,(DWORD)quality,formula,FALSE);
  for (i = 0; i < len; i++) rotlist[i] = RubixRotationTranslation[TurnCodeRev[formula[i]]];

  return len;
} // BJWSolve3CubeFromRubix

/********************************************************/
