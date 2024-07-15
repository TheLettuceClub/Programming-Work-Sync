#pragma once
const int maxGreen = 3;
const int maxYellow = 7;
const int maxOrange = 5;
extern int currGreen;
extern int currYellow;
extern int currOrange;
extern bool currentPlayer; //always player first
extern bool gameOver;
//void regCptrMove(int index, int newVal);

class ComputerAI {
public:
	ComputerAI() {}
	void doMove();

private:
	bool doIHaveWinningMove();
	int nimSum(int a, int b, int c);
	int nimSum(int a, int b);
	void regCptrMove(int index, int newVal);
};