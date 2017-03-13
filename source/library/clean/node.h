#ifndef NODE_H
#define NODE_H

class state;

struct node{
        node(state *newState, node *next){
                curState = newState;
                this->next = next;
        };
        ~node(){
                delete curState;
        };
        state *curState;
        node *next;
};

#endif
