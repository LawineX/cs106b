// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "stack.h"
#include "queue.h"
#include "hashset.h"
#include "filelib.h"
#include "lexicon.h"

using namespace std;
void welcome(string &);
int SetTargetAndBegin(string &, string &, Lexicon &);
void corefun_out(Queue<Stack<string> > &queue, HashSet<string> &hashset, Lexicon &lex, string target);
void PopInReverse(Stack<string> &stack);
void corefun_inner(Queue<Stack<string> > &queue, HashSet<string> &hashset, Lexicon &lex, string target, Stack<string> &working_stack);
int flag=1;

int main() {
    Stack <string> stack;
    Queue <Stack<string>> queue;
    string target,begin,filename;
    HashSet <string> hashset;
    welcome(filename);
    Lexicon my_dict(filename);
    while(1){
        int ret = SetTargetAndBegin(target,begin,my_dict);
        if(ret==1){
            break;
        }else if(ret==0){
            stack.push(begin);
            queue.enqueue(stack);
            corefun_out(queue,hashset,my_dict,target);
            stack.clear();
            queue.clear();
            flag=1;
        }
    }
    cout <<"Have a nice day." << endl;
    return 0;
}

void welcome(string &filename){
    cout<<"Welcome to CS 106B Word Ladder."<<endl;
    cout<<"Please give me tow English words, and I will change the"<<endl;
    cout<<"first into the second by changing one letter at a time."<<endl;
    cout<<endl;
    auto checkname=[&filename](){
        cout<<"Dictionary file name?";
        cin>>filename;
        cin.get();
        if(fileExists(filename)){
            return 0;
        } else{
            cout<<"unable to open that file. Try again.";
            cout<<"Dictionary file name?"<<endl;
            return 1;
        }
    };
    while(checkname());
}

int SetTargetAndBegin(string &target, string &begin, Lexicon &lex) {
    cout << "Word #1 (or Enter to quit): ";
    getline(cin,target);
    if (target == "") return 1;
    target = toLowerCase(target);
    cout << "Word #2 (or Enter to quit): ";
    getline(cin,begin);
    if (begin == "") return 1;
    begin = toLowerCase(begin);

    if (target.size() != begin.size()) {
        cout << "The two words must be the same length." << endl;
        return -1;
    } else if (target == begin) {
        cout << "The two words must be different" << endl;
        return -1;
    } else if (!(lex.contains(target) && lex.contains(begin))) {
        cout << "The two words must be found in the dictionary." << endl;
        return -1;
    } else {
        cout << "A ladder from " << begin << " to " << target << " :" << endl;
    }
    return 0;
}

void corefun_out(Queue <Stack <string>> &queue,HashSet <string> &hashset,Lexicon &lex,string target){

    while(!queue.isEmpty()&&flag){
        Stack <string> working_stack=queue.dequeue();
        corefun_inner(queue,hashset,lex,target,working_stack);
    }
}
void corefun_inner(Queue <Stack <string>> &queue,HashSet <string> &hashset,Lexicon &lex,string target, Stack<string> &inner_stack){
    string mid_word=inner_stack.peek();
    if(mid_word==target){
        PopInReverse(inner_stack);
        flag =0;
        return;
    }else{
        hashset.add(mid_word);
        for(char &c:mid_word){
            char save_c=c;
            for(c='a';c>='a'&&c<='z';){
                if(lex.contains(mid_word)&& !hashset.contains(mid_word)){
                    Stack <string> temp_stack=inner_stack;
                    temp_stack.push(mid_word);
                    queue.enqueue(temp_stack);
                }
                c++;
            }
            c=save_c;
        }
    }
}
void PopInReverse(Stack <string> &stack){
    Stack <string> temp;
    while (!stack.isEmpty()) {
        temp.push(stack.pop());
    }
    while (!temp.isEmpty()) {
        string word=temp.pop();
        cout<<word<<" ";
    }
    cout<<endl;
}
