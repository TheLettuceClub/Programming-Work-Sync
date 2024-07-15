#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include <iostream>
#include "ComputerAI.h"

void ComputerAI::doMove() {
	//optionally send text to hwEdit
    if (gameOver) { return; }
	if (!doIHaveWinningMove()) {
		int currents[] = {currGreen, currYellow, currOrange};
		int index = rand() % 3; //should be between 0 and 2
		if (currents[index] == 0) {
			index = rand() % 3;
			if (currents[index] == 0) {
				index = rand() % 3;
			}
		}
		int newVal = rand() % (currents[index] + 1) + 1;
		//figure out how to call regCptrMove() from here, IDK how
        regCptrMove(index, currents[index] - newVal);
	}
}

bool ComputerAI::doIHaveWinningMove() {
    if (nimSum(currGreen, currYellow, currOrange) != 0) {
        int ns2AB = nimSum(currGreen, currYellow);
        int ns2AC = nimSum(currGreen, currOrange);
        int ns2BC = nimSum(currYellow, currOrange);
        if (currOrange > ns2AB) {
            //remove enough markers from C to equal ns2AB and we win
            regCptrMove(2, currOrange - ns2AB);
        }
        else if (currYellow > ns2AC) {
            //remove enough markers from B to equal ns2AC and we win
            regCptrMove(1, currYellow - ns2AC);
        }
        else if (currGreen > ns2BC) {
            //remove enough markers from A to equal ns2BC and we win
            regCptrMove(0, currGreen - ns2BC);
        }
        else {
            //just in case the nimsum of the game is a 0, but none of the individual ones are.
            //likely just at the end of games to make sure the computer does a move
            return false;
        }
        return true;
    }
    return false;
}

int ComputerAI::nimSum(int a, int b, int c) {
    return a ^ b ^ c;
}

int ComputerAI::nimSum(int a, int b) {
    return a ^ b;
}

void ComputerAI::regCptrMove(int index, int newVal) {
    wchar_t msg[41];
    swprintf_s(msg, L"reducing index %d by value %d\r\n", index, newVal);
    OutputDebugString(msg);
    switch (index) {
    case 0:
        currGreen -= newVal;
        break;
    case 1:
        currYellow -= newVal;
        break;
    case 2:
        currOrange -= newVal;
        break;
    }
}