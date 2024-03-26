// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need

Map<int, int> buildFrequencyTable(istream& input) {
    // TODO: implement this function
    Map<int, int> freqTable;   // this is just a placeholder so it will compile
    int c;
    while((c=input.get())!=-1){
        freqTable[c]++;
    }
    freqTable[PSEUDO_EOF]++;
    return freqTable;          // this is just a placeholder so it will compile
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // TODO: implement this function
    HuffmanNode *root;
//    auto cmp=[](HuffmanNode &x,HuffmanNode &y){
//        return x.count>y.count;
//    };
    PriorityQueue<HuffmanNode> pq;
    for(auto key:freqTable){
        pq.enqueue(HuffmanNode(key,freqTable[key]),freqTable[key]);
    }
    while(pq.size()>1){
        HuffmanNode *left,*right;
        left = new HuffmanNode(pq.peek());
        pq.dequeue();
        right = new HuffmanNode(pq.peek());
        pq.dequeue();
        pq.enqueue(HuffmanNode{NOT_A_CHAR,left->count+right->count,left,right},left->count+right->count);
    }
    root=new HuffmanNode(pq.peek());
    return root;   // this is just a placeholder so it will compile
}
void dfs(string &pre_str, Map<int,string> &ret, HuffmanNode* cur){
    if(cur!=nullptr){
        if(cur->character!=NOT_A_CHAR){
            ret[cur->character]=pre_str;
        }
        pre_str.push_back('0');
        dfs(pre_str,ret,cur->zero);
        pre_str.pop_back();
        pre_str.push_back('1');
        dfs(pre_str,ret,cur->one);
        pre_str.pop_back();
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    string empty="";
    dfs(empty,encodingMap,encodingTree);
    return encodingMap;             // this is just a placeholder so it will compile
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
    int cur_in;
    string cur_out;
    while((cur_in=input.get())!=-1){
        cur_out=encodingMap[cur_in];
        for(char c:cur_out){
            output.writeBit(c-'0');
        }
    }
    string end_of_file=encodingMap[PSEUDO_EOF];
    for(char c:end_of_file){
        output.writeBit(c-'0');
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
    int cur_bit;
    HuffmanNode *cur_p=encodingTree;
    while((cur_bit=input.readBit())!=-1){
        if(cur_p->character!=NOT_A_CHAR){
            if(cur_p->character==PSEUDO_EOF){
                break;
            }
            output.put((char)cur_p->character);
            cur_p=cur_bit?encodingTree->one:encodingTree->zero;
        }else{
            if(cur_bit==1){
                cur_p=cur_p->one;
            }else{
                cur_p=cur_p->zero;
            }
        }
    }
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    global_root= buildEncodingTree(buildFrequencyTable(input));
    rewindStream(input);
    encodeData(input,buildEncodingMap(global_root),output);
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    rewindStream(input);
    decodeData(input,global_root,output);
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
    if(node==nullptr){
        return;
    }
    freeTree(node->zero);
    freeTree(node->one);
    delete(node);
}
