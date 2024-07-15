
using System.Reflection.Metadata.Ecma335;
using System.Runtime.ConstrainedExecution;
using System.Security.Cryptography.X509Certificates;

namespace CsharpTest;

class nQueens
{

    private int n;
    private int[] board;

    public nQueens(int iN, int[] brd) {
        n = iN;
        board = brd;
    }

    public nQueens(int iN) {
        n = iN;
        board = new int[n];
        board[0] = 1;
    }

    static void Main(string[] args)
    {
        Console.WriteLine("Hello, World!");
        nQueens nq = new nQueens(8, [1, 6, 8, 3, 7, 4, 2, 5]);
        Console.WriteLine(nq.isLegalPosition());
        nq = new nQueens(8, [1, 6, 8, 3, 7, 0, 0, 0]);
        Console.WriteLine(nq.isLegalPosition());
        nq = new nQueens(8, [1, 6, 8, 3, 5, 0, 0, 0]);
        Console.WriteLine(nq.isLegalPosition());
        nq = new nQueens(8, [1, 0, 8, 3, 5, 0, 0, 0]);
        Console.WriteLine(nq.isLegalPosition());
        nq = new nQueens(8, [1, 0, 0, 0, 0, 0, 0, 0]);
        Console.WriteLine(nq.isLegalPosition());

        nq = new nQueens(8, [1, 6, 8, 3, 5, 0, 0, 0]);
        Console.WriteLine("[{0}]", string.Join(", ", nq.nextLegalPosition(true)));
        nq = new nQueens(8, [1, 6, 8, 3, 7, 0, 0, 0]);
        Console.WriteLine("[{0}]", string.Join(", ", nq.nextLegalPosition(true)));
        nq = new nQueens(8, [1, 6, 8, 3, 7, 4, 2, 5]);
        Console.WriteLine("[{0}]", string.Join(", ", nq.nextLegalPosition(true)));

        for (int i = 4; i <= 14; i++) {
            nq = new nQueens(i);
            Console.WriteLine("[{0}]", string.Join(", ", nq.findFullSolution()));
            Console.WriteLine(nq.numSolutions());
        }
    }


    public int[] findFullSolution() {
        board = nextLegalPosition(true);
        while (boardNotFull()) {
            board = nextLegalPosition(true);
        }
        return board;
    }

    private Boolean boardNotFull() {
        if (board == null) {
            return false;
        }
        foreach (int i in board) {
            if (i == 0) {
                return true;
            }
        }
        return false;
    }

    public int numSolutions() {
        if (board == null) {
            Console.WriteLine("Run findFullSolution first!!!!");
            return -1;
        }
        int numSolutions = 1;
        while (findFullSolution() != null) {
            numSolutions++;
        }
        return numSolutions;
    }

    public Boolean isLegalPosition() {
        Boolean result = true;
        for (int i = 0; i < n; i++) {
            int currCol = board[i];
            if (currCol == 0) {
                for (int k = i+1; k<n; k++) {
                    if (board[k]!=0) {
                        return false;
                    }
                }
                return result;
            }
            for (int j = 1; j <= i; j++) {
                int otherCol = board[i-j];
                if (otherCol == currCol || otherCol == currCol-j || otherCol == currCol+j) {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

    public int[] nextLegalPosition(Boolean first) {
        if (board == null) {
            return board;
        }

        int row = lastQueen();
        if (isLegalPosition()) {
            if (!first) {
                return board;
            }
            if (row < n-1) {
                board[row+1]++;
                return nextLegalPosition(false);
            } else {
                board[row]=0;
                board = successor(row);
                return nextLegalPosition(true);
            }
        } else {
            if (board[row]+1 <= n) {
                board[row]++;
            } else {
                board[row]=0;
                board = successor(row);
                //should we recurse here??
            }
            return nextLegalPosition(false);
        }
    }

    private int[] successor(int row) {
        if (board[row-1]+1 <=n) {
            board[row-1]++;
            return board;
        } else {
            board[row-1] = 0;
            if (row-1 < 1) {
                return null;
            }
            return successor(row-1);
        }
    }

    private int lastQueen() {
        int index = 0;
        for (int i = 0; i < board.Length; i++) {
            if (board[i] > 0) {
                index = i;
            }
        }
        return index;
    }
}