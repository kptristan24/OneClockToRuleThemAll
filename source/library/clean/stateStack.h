#ifndef STATESTACK_H
#define STATESTACK_H

#include "state.h"
#include "node.h"

class stateStack{
public:
        enum Transition {NOTHING, EXIT, NEW, REPLACE};
        stateStack(){
                size = 0;
                stack = nullptr;
        };
        ~stateStack(){
                while(size){
                        pop();
                }
        };
        node* accessStack(){
                return stack;
        };
        void push(state *newS){
                node *temp = new node(newS, stack);
                stack = temp;
                size++;
        };
        void pop(){
                node *temp = stack;
                stack = temp->next;
                delete temp;
                size--;
                if(!size){
                        stack = nullptr;
                }
        };
private:
        node *stack;
        uint8_t size;
};

#endif
