// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include <vector>
#include <unordered_set>

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter (int row, int col) const;
    bool checkWord(string word) const;
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    void displayed_on_screen()const;
    void humanDfs(string& ans,string&target,int row,int col,vector<vector<bool>>&marked,vector<vector<int>>&direction,int n);
    void computerDfs(Set<string>&ret,string& ans,vector<vector<bool>>& marked,vector<vector<int>> &direction,int row, int col);
    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    void run_computer_search();

private:
    // TODO: add any other member functions/variables necessary
    string my_text;
    Lexicon using_dict;
    unordered_set<string> hash_set;
    Set<string> computer_hash_set;
};

#endif // _boggle_h
