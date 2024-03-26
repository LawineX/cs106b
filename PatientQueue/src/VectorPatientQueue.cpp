// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "VectorPatientQueue.h"

VectorPatientQueue::VectorPatientQueue() {
    // TODO: write this constructor
    time=0;
    myvec.clear();
}

VectorPatientQueue::~VectorPatientQueue() {
    // TODO: write this destructor
}

void VectorPatientQueue::clear() {
    // TODO: write this function
    myvec.clear();
}

string VectorPatientQueue::frontName() {
    // TODO: write this function
    if(myvec.isEmpty()){
        throw string("I must abort!");
    }
    patient_node ret=myvec[0];
    for(auto &s:myvec){
        if(s.priority<ret.priority|| s.priority==ret.priority && s.time_in<ret.time_in){
            ret=s;
        }
    }
    return ret.name;   // this is only here so it will compile
}

int VectorPatientQueue::frontPriority() {
    // TODO: write this function
    if(myvec.isEmpty()){
        throw string("I must abort!");
    }
    patient_node ret=myvec[0];
    for(auto &s:myvec){
        if(s.priority<ret.priority|| s.priority==ret.priority && s.time_in<ret.time_in){
            ret=s;
        }
    }
    return ret.priority;   // this is only here so it will compile
}

bool VectorPatientQueue::isEmpty() {
    // TODO: write this function
    return myvec.isEmpty();   // this is only here so it will compile
}

void VectorPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    patient_node tmp={name,priority,time+1};
    time++;
    myvec.add(tmp);
}

string VectorPatientQueue::processPatient() {
    // TODO: write this function
    if(myvec.isEmpty()){
        throw string("I must abort!");
    }
    int index=0;
    patient_node tmp=myvec[0];
    for(int i=1;i<myvec.size();i++){
        if(myvec[i].priority<tmp.priority || myvec[i].priority==tmp.priority&&myvec[i].time_in<tmp.time_in){
            tmp=myvec[i];
            index=i;
        }
    }
    string ret=myvec[index].name;
    myvec.remove(index);
    return ret;   // this is only here so it will compile
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    int index=-1;
    for(int i=0;i<myvec.size();i++){
        if(name==myvec[i].name){
            if(index==-1){
                index=i;
            }else if(myvec[i].priority<myvec[index].priority){
                index=i;
            }
        }
    }
    if(index==-1){
        throw string("I must abort!");
    }else{
        myvec[index].priority=newPriority;
    }
}

string VectorPatientQueue::toString() {
    // TODO: write this function
    auto cmp=[](patient_node x, patient_node y){
        if(x.priority==y.priority){
            return x.time_in>y.time_in;
        }else{
            return x.priority>y.priority;
        }
    };
    priority_queue<patient_node,vector<patient_node>,decltype(cmp)> pq(cmp);
    for(auto node:myvec){
        pq.push(node);
    }
    patient_node tmp;
    string ret="{";
    while(!pq.empty()){
        tmp=pq.top();
        ret+=to_string(tmp.priority);
        ret+=':';
        ret+=tmp.name;
        ret+=",";
        pq.pop();
    }
    ret[ret.size()-1]='}';

    return ret; // this is only here so it will compile
}
