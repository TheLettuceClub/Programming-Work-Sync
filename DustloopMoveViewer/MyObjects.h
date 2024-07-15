#pragma once
#include <string>
#include <vector>
#include <memory>
#define implementedchars 2

using namespace std;

class Character {
public:
    string name; // real name of character, ex: Sol Badguy
    string dname; // name of char in the dustloop URL, ex: Sol_Badguy
    int numMoves = 0;
    vector<string> moves;

    Character() {}

    void init(string iname, string idname, int inumMoves) {
        name = iname;
        dname = idname;
        numMoves = inumMoves;
        moves.resize(numMoves);
    }

    void InitMoves(nlohmann::json name) {
        for (int i = 0; i < numMoves; i++) {
            auto hate = name[i].template get<std::string>();
            if (hate != "\0" && hate != "") {
                moves[i] = hate;
            }
        }
    }
};

class Game {
public:
    string name; // real name of game, ex: Guilty Gear Strive
    string dname; // dustloop name, ex: GGST
    int numChars = 0;
    vector<shared_ptr<Character>> chars;

    Game(string inName, string inDName, int inNumChars) {
        name = inName;
        dname = inDName;
        numChars = inNumChars;
        chars.resize(numChars);
        for (int i = 0; i < numChars; i++) {
            chars[i] = make_shared<Character>();
        }
    }

    Game() {}

    void InitChars(vector<string>* name, vector<string>* dname, vector<int>* numMoves) {
        for (int i = 0; i < numChars; i++) {
            if (i == implementedchars) { break; } //bc I haven't done all of them yet....
            chars[i]->init((*name)[i], (*dname)[i], (*numMoves)[i]);
        }
    }

    void InitCharMoves(int i, nlohmann::json names) {
        chars[i]->InitMoves(names);
    }
};