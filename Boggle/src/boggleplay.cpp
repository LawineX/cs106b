// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include "bogglegui.h"
#include "console.h"
#include "simpio.h"

bool using_spec_check();
bool check_valid_boardtext(string &str);
void human_turn(Boggle &boggle);
void computer_turn(Boggle &boggle);

void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    Boggle *my_boggle;
    if(!using_spec_check()){
        string my_spec_dict;
        while(!check_valid_boardtext(my_spec_dict));
        my_boggle= new Boggle(dictionary,my_spec_dict);
    }else{
        my_boggle= new Boggle(dictionary);
    }
    my_boggle->displayed_on_screen();
    human_turn(*my_boggle);
    computer_turn(*my_boggle);
}

bool using_spec_check(){
    char C;
    cout<<"Do you want to generate a random board?";
    cin>>C;
    if(C=='y'||C=='Y'){
        return true;
    }else if(C=='n'||C=='N'){
        return false;
    }else{
        return using_spec_check();
    }
}

bool check_valid_boardtext(string &str){
    cout<<"Type the 16 letters to appear on the board:";
    cin>>str;
    if(str.size()!=16){
        cout<<"That is not a valid 16-letter board string. Try again."<<endl;
        return false;
    }else{
        for(char c:str){
            if(!((c<='z'&&c>='a')||(c<='Z'&&c>='A'))){
                cout<<"That is not a valid 16-letter board string. Try again."<<endl;
                return false;
            }
        }
    }
    return true;
}

void human_turn(Boggle &boggle){
    clearConsole();
    string tmp="It's your turn!";
    BoggleGUI::setStatusMessage(tmp);
    cout<<tmp<<endl;
    cin.get();
    while(1){
        cout<<boggle;
        string word;

        word=getLine("Type a word (or Enter to stop):");
        if(word.empty()){
            break;
        }
        clearConsole();
        if(boggle.checkWord(word)){
            if(boggle.humanWordSearch(word)){
                string temp="You found a new word! \""+word+"\"";
                BoggleGUI::setStatusMessage(temp);
                cout<<temp<<endl;
            }else{
                string temp="That word can't be formed on this board.";
                cout<<temp<<endl;
                BoggleGUI::setStatusMessage(temp);
            }
        }else{
            string temp="You must enter an unfound 4+ letter word from the dictionary.";
            cout<<temp<<endl;
            BoggleGUI::setStatusMessage(temp);
        }
    }
}

void computer_turn(Boggle &boggle){
    string tmp="It's my turn!";
    BoggleGUI::setStatusMessage(tmp);
    cout<<tmp<<endl;
    boggle.run_computer_search();
    if(boggle.getScoreComputer()>boggle.getScoreHuman()){
        tmp="Ha ha ha, I destroyed you. Better luck next time, puny human!";
        BoggleGUI::setStatusMessage(tmp);
        cout<<tmp<<endl;
    }
}
