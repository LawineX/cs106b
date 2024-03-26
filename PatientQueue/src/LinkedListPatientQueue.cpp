// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    // TODO: write this constructor
    head=nullptr;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    // TODO: write this destructor
    PatientNode *tail;
    while(head!=nullptr){
        tail=head;
        head=head->next;
        delete(tail);
    }
}

void LinkedListPatientQueue::clear() {
    // TODO: write this function
    PatientNode *tmp;
    while(head!=nullptr){
        tmp=head;
        head=head->next;
        delete(tmp);
    }
}

string LinkedListPatientQueue::frontName() {
    // TODO: write this function
    if(head==nullptr){
        throw string("I must abort!");
    }else{
        return head->name;
    }
    // this is only here so it will compile
}

int LinkedListPatientQueue::frontPriority() {
    // TODO: write this function
    if(head==nullptr){
        throw string("I must abort!");
    }else{
        return head->priority;
    }
    // this is only here so it will compile
}

bool LinkedListPatientQueue::isEmpty() {
    // TODO: write this function
    return head==nullptr;   // this is only here so it will compile
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    PatientNode *p=new PatientNode(name,priority);
    if(head==nullptr){
        head=p;
        tail=p;
    }else{
        if(head->priority>priority){
            p->next=head;
            head=p;
            return;
        }
        PatientNode *first=head->next,*second=head;
        while(first!=nullptr&&first->priority<=priority){
            first=first->next;
            second=second->next;
        }
        second->next=p;
        p->next=first;
    }
}

string LinkedListPatientQueue::processPatient() {
    // TODO: write this function
    if(head==nullptr){
        throw string("I must abort!");
    }else{
        string ret=head->name;
        PatientNode *p=head;
        head=head->next;
        delete(p);
        return ret;
    }
    // this is only here so it will compile
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    if(head->name==name){
        PatientNode *tmp=head;
        head=head->next;
        delete(tmp);
        this->newPatient(name,newPriority);
        return;
    }
    PatientNode *first=head->next,*second=head;
    while(first!=nullptr){
        if(first->name==name){
            second->next=first->next;
            delete(first);
            this->newPatient(name,newPriority);
            return;
        }
        first=first->next;
        second=second->next;
    }
    throw string("I must abort!");
}

string LinkedListPatientQueue::toString() {
    // TODO: write this function
    string ret="{";
    PatientNode *p=head;
    while(p!=nullptr){
        ret+=to_string(p->priority);
        ret+=':';
        ret+=p->name;
        ret+=',';
        p=p->next;
    }
    ret[ret.size()-1]='}';
    return ret; // this is only here so it will compile
}
