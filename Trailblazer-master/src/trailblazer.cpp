// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "trailblazer.h"
#include "queue.h"
#include "set.h"
#include "pqueue.h"
#include "point.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

// this makes Path an alias for the type Vector<Vertex*>
typedef Vector<Vertex*> Path;

// the minimum difference for an alternate route
const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)

    if(start==end){
        Path ret;
        ret.add(start);
        return ret;
    }
    unordered_map<Vertex*,Vertex*> hash_map;
    unordered_set<Vertex*> check;
    queue<Vertex*> my_queue;
    Path ret,tmp;
    my_queue.push(start);
    check.insert(start);
    while(!my_queue.empty()){
        Vertex* cur_node=my_queue.front();
        my_queue.pop();
        if(cur_node==end){
           Vertex* parent;
            while((parent=hash_map[cur_node])!=start){
                tmp.add(parent);
                cur_node=parent;
            }
            tmp.add(start);
            for(int i=tmp.size()-1;i>=0;i--){
                ret.add(tmp[i]);
            }
            return ret;
        }
        for(auto &node:graph.getNeighbors(cur_node)){
            if(check.find(node)==check.end()){
                my_queue.push(node);
                hash_map[node]=cur_node;
                check.insert(node);
            }
        }

    }
    return {};
}

Path dijkstrasAlgorithm(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Path emptyPath;
    return emptyPath;
}


Path aStar(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Path emptyPath;
    return emptyPath;
}

Path alternativeRoute(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Path emptyPath;
    return emptyPath;
}

