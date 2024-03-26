// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;
void welcome();
int checkname(string&,ifstream&);
void handle_file(ifstream &stream, Grid<int> &table);
void display_func(Grid<int> & table);
int around_ack();
int console_board();
void evolve(Grid<int> &table);
void animate(Grid<int> &table);
int main() {
    string filename;
    Grid <int> table;
    ifstream input;
    int ack=-1;
    int using_around_grid;
    welcome();
    while(!checkname(filename,input));
    handle_file(input,table);
    using_around_grid=around_ack();
    display_func(table);
    while(ack){
        ack = console_board();
        if(ack==0){
            break;
        }else if(ack==2){
            evolve(table);
            display_func(table);
        }else{
            animate(table);
        }
    }
    cout << "Have a nice Life!" << endl;
    return 0;
}

void welcome(){
    cout<<"welcome to the cs106b game of life!"<<endl;
    cout<<"Grid input file name:";
}

int checkname(string &filename,ifstream &input){
    cin>>filename;
   if(fileExists(filename)){
      openFile(input,filename);
      return 1;
   } else{
       cout<<"unable to find the file "<<filename<<endl;
       cout<<"Grid input file name:";
       return 0;
   }
}

void handle_file(ifstream &stream,Grid <int> &table){
    int row,col;
    string str;
    getline(stream,str);
    row=stringToInteger(str);
    getline(stream,str);
    col=stringToInteger(str);
    table.resize(row,col);
    table.fill(0);
    int current_row =0;
    int current_col=0;
    while (getline(stream,str)) {
        str=str.substr(0,col);
        for(char c:str){
            if(c=='X'){
                table[current_row][current_col]=1;
            }
            ++current_col;
        }
        ++current_row;
        current_col=0;
    }
}

void display_func(Grid <int> &table){
    cout<<table.toString()<<endl;
}

int around_ack(){
    cout<<"Should the simulation wrap around the grid (y/n)? ";
    string c;
    cin>>c;
    c=toLowerCase(c);
    while (c!="y"&&c!="n") {
        cout<<"Should the simulation wrap around the grid (y/n)? ";
        cin>>c;
        c=toLowerCase(c);
    }
    if(c=="y"){
        return 1;
    }else{
        return 0;
    }
}

int console_board(){
    string c;
    cout<<"a)nimate, t)ick, q)uit? ";
    cin>>c;
    c=toLowerCase(c);
    while (c!="a"&&c!="t"&&c!="q") {
        cout<<"a)nimate, t)ick, q)uit? ";
        cin>>c;
        c=toLowerCase(c);
    }
    if(c=="a"){
        return 1;
    }else if(c=="t"){
        return 2;
    }else{
        return 0;
    }

}

void evolve(Grid <int> &table){
    int row =table.numRows();
    int col =table.numCols();
    Grid <int> newtable(row,col,0);
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            int total=-table[i][j];
            for(int bias_row=-1;bias_row<2;++bias_row){
                for(int bias_col=-1;bias_col<2;++bias_col){
                    if((i+bias_row)<=(row-1)&&(i+bias_row)>=0&&(j+bias_col)>=0&&(j+bias_col)<=(col-1)){
                        total+=table[i+bias_row][j+bias_col];
                    }
                }
            }
            if(total==2&&table[i][j]==1 || total==3){
                newtable[i][j]=1;
            }
        }
    }
    table=newtable;
}

void animate(Grid <int> &table){
    int num =getInteger("how many frame?");
    for(int i=0;i<num;++i){
        evolve(table);
        display_func(table);
        pause(500);
        clearConsole();
    }
}
