#ifndef STATESTACK_H
#define STATESTACK_H

#include "state.h"
#include "node.h"

class stateStack{
public:
        stateStack(){
                size = 0;
                stack = NULL;
                base = NULL;
        };
        ~stateStack(){
                while(size){
                        pop();
                }
        };
        node** accessStack(){
                return &stack;
        };
        node* getBase(){
                return base;
        };
        void push(state *newS){
                node *temp = new node(newS, stack);
                stack = temp;
                size++;
                if(size == 1){
                        base = stack;
                }
        };
        void pop(){
                node *temp = stack;
                stack = temp->next;
                delete temp;
                size--;
                if(!size){
                        base = NULL;
                }
        };
private:
        node *stack;
        node *base;
        int size;
};

#endif
