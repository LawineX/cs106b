// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"
using namespace std;

void welcome();
int CheckFilenamAndOpen(string &filename, ifstream &input);
int SelectNAndProcessFile(ifstream &input, int &n_gram, Map<Vector<string>,Vector<string>> &map);
int createTxt(int n_gram, Map<Vector<string>, Vector<string> > &map);

int main() {
    // TODO: Finish the program!
    string filename;
    ifstream input;
    Map<Vector<string>,Vector<string>> map;
    int n_gram;
    welcome();
    while(CheckFilenamAndOpen(filename,input)) ;
    while(SelectNAndProcessFile(input,n_gram,map)) ;
    while(createTxt(n_gram,map));

    cout << "Exiting." << endl;
    return 0;

}

void welcome(){
    cout<<"Welcome to CS 106B Random Writer ('N-Grams')."<<endl<<"This program makes random text based on a document."<<endl
       <<"Give me an input file and an 'N' value for groups"<<endl<<"of words, and I'll create random text for you."<<endl<<endl;
}

int CheckFilenamAndOpen(string & filename,ifstream &input){
    cout<<"Input file name?";
    cin>>filename;
    if(fileExists(filename)){
        input.open(filename);
        return 0;
    }
    cout<<"Unable to open that file. Try again."<<endl;
    return 1;
}

int SelectNAndProcessFile(ifstream &input, int &n_gram,Map<Vector<string>,Vector<string>> &map){
    cin.get();
    n_gram=getInteger("Value of N?");
    if(n_gram<2){
        cout<<"N must be 2 or greater."<<endl;
        return 1;
    }
    string word;
    Vector<string> windows;
    Vector<string> topN;
    for(int i=0;i<n_gram;++i){
        input>>word;
        windows.add(word);
        topN.add(word);
    }
    while(input>>word){
        if(map.containsKey(windows)){
            map.get(windows).add(word);
        }else{
            Vector<string> temp={word};
            map.put(windows,temp);
        }
        windows.remove(0);
        windows.add(word);
    }
    for(string word:topN){
         if(map.containsKey(windows)){
            map.get(windows).add(word);
        }else{
            Vector<string> temp={word};
            map.put(windows,temp);
        }
        windows.remove(0);
        windows.add(word);
    }
    return 0;
}

int createTxt(int n_gram,Map<Vector<string>,Vector<string>> &map){
    int sentence_length=getInteger("# of random words to generate(0 to quit)?");
    if(sentence_length==0){
        return 0;
    }else if(sentence_length<n_gram){
        cout<<"Must be at least "<<n_gram<<"word."<<endl;
        return 1;
    }
    Vector<string> vec=map.keys()[randomInteger(0,map.keys().size()-1)];
    Vector<string> temp=vec;
    while(sentence_length-n_gram>0){
        string word =map.get(temp)[randomInteger(0,map.get(vec).size()-1)];
        vec.add(word);
        temp.remove(0);
        temp.add(word);
        --sentence_length;
    }
    cout<<"...";
    for(string word:vec){
        cout<<word<<" ";
    }
    cout<<"..."<<endl;
    return 0;
}
