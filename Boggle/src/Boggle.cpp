// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "shuffle.h"
#include "bogglegui.h"
#include <cmath>

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    // TODO: implement
    using_dict=dictionary;
    if(!boardText.size()){
        for(auto &str:CUBES){
            str=shuffle(str);
            my_text+=str[0];
        }
        my_text=shuffle(my_text);
    }else{
        toUpperCaseInPlace(boardText);
        my_text=boardText;
    }
}

char Boggle::getLetter(int row, int col) const{
    // TODO: implement
    return my_text[row*sqrt(my_text.size())+col];   // remove this
}

bool Boggle::checkWord(string word) const {
    // TODO: implement
    toUpperCaseInPlace(word);
    if(word.size()<4||hash_set.count(word)||!using_dict.contains(word)){
        return false;
    }else{
        return true;
    }
}

bool Boggle::humanWordSearch(string word){
    toUpperCaseInPlace(word);
    string ans;
    int num=sqrt(my_text.size());
    vector<vector<bool>>marked(num,vector<bool>(num,0));
    vector<vector<int>> direction{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            humanDfs(ans,word,i,j,marked,direction,0);
        }
    }
    if(hash_set.count(word)){
        return true;
    }else{
        return false;
    }
}

int Boggle::getScoreHuman() {
    // TODO: implement
    int total=0;
    for(auto str:hash_set){
        total+=(str.size()-3);
    }
    BoggleGUI::setScore(total,BoggleGUI::HUMAN);
    return total;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    string word;
    int num=sqrt(my_text.size());
    vector<vector<bool>>marked(num,vector<bool>(num,0));
    vector<vector<int>> direction{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            computerDfs(result,word,marked,direction,i,j);
        }
    }

    return result;        // remove this
}

void Boggle::computerDfs(Set<string>& ret,string& word,vector<vector<bool>>& marked,vector<vector<int>>& direction,int row,int col){
    if(this->using_dict.contains(word)&&word.size()>=4){
        if(!ret.contains(word)){
            ret.add(word);
            BoggleGUI::recordWord(word,BoggleGUI::COMPUTER);
        }
        return;
    }
    if(!marked[row][col]&&(word.size()&&this->using_dict.containsPrefix(word)||(!word.size()))){
        marked[row][col]=1;
        word.push_back(this->getLetter(row,col));
        for(auto dir:direction){
            int new_row=row+dir[0];
            int new_col=col+dir[1];
            if(new_row<4&&new_row>=0&&new_col<4&&new_col>=0){
                computerDfs(ret,word,marked,direction,new_row,new_col);
            }
        }
        word.pop_back();
        marked[row][col]=0;
    }
}

void Boggle::run_computer_search(){
    computer_hash_set=computerWordSearch();
    cout<<"My words ("<<computer_hash_set.size()<<"): "<<computer_hash_set.toString()<<endl;
    cout<<"My score: "<<getScoreComputer()<<endl;
}

int Boggle::getScoreComputer() {
    int total=0;
    for(string word:computer_hash_set){
        total+=word.size()-3;
    }
    BoggleGUI::setScore(total,BoggleGUI::COMPUTER);
    return total;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<boggle.getLetter(i,j);
       }
        cout<<endl;
    }
    cout<<endl;
//    Your words (2): {"FOIL", "ROOF"}

    cout<<"Your words ("<<boggle.hash_set.size()<<"): {";
    int nums=0;
    for(auto it:boggle.hash_set){
        cout<<"\""<<it<<"\"";
        nums++;
        if(nums<boggle.hash_set.size()){
            cout<<", ";
        }else{
            cout<<"}"<<endl;
        }
    }
    cout<<"Your score: "<<boggle.getScoreHuman()<<endl;
    return out;
}

void Boggle::displayed_on_screen()const{
    BoggleGUI::initialize(sqrt(my_text.size()),sqrt(my_text.size()));
    BoggleGUI::labelAllCubes(my_text);
}

void Boggle::humanDfs(string& ans,string&target,int row,int col,vector<vector<bool>>&marked,vector<vector<int>>&direction,int n){
    if(ans==target){
        if(!hash_set.count(ans)){
            hash_set.insert(ans);
            BoggleGUI::recordWord(ans,BoggleGUI::HUMAN);
        }
        return;
    }
    if(n<target.size()&&!marked[row][col]&&getLetter(row,col)==target[n]){

        marked[row][col]=1;
        ans.push_back(getLetter(row,col));
        BoggleGUI::setHighlighted(row,col,true);
        BoggleGUI::setAnimationDelay(100);
        for(auto dir:direction){
            int new_row=row+dir[0];
            int new_col=col+dir[1];
            if(new_row<4&&new_row>=0&&new_col<4&&new_col>=0){
                humanDfs(ans,target,new_row,new_col,marked,direction,n+1);
            }
        }
        ans.pop_back();
        marked[row][col]=0;
        BoggleGUI::setHighlighted(row,col,false);
    }
}
