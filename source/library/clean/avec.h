#ifndef AVECTOR_H
#define AVECTOR_H

#include "timeS.h"

//alarm vector

class aVec{
public:
        aVec(){
                data = new timeS[2];
                capacity = 2;
                curSize = 0;
        }
        int size(){
                return curSize;
        }
        void push_back(const timeS &item){
                data[curSize] = item;
                curSize++;

                if(curSize == capacity)
                        resize();
        }
        void insert_ordered(const timeS &item){
                int position;
                for(int i = 0; i < curSize; i++){
                        if(item < data[i])
                                position = i;
                        else
                                position = curSize;
                }

                if(position == curSize){
                        push_back(item);
                }
                else{
                        for(int i = curSize; i > position; i++){
                                data[i] = data[i - 1];
                        }
                        data[position] = item;
                        if(curSize == capacity)
                                resize();
                }
        }
        const timeS & operator [](int i) const {return data[i];}
        timeS & operator [](int i) {return data[i];}
        void erase(const int &i) const {
                if(i >= curSize)
                        return;
                else if(i == (curSize - 1))
                        curSize--;
                else{
                        for(int pos = i; pos < curSize - 1; pos++)
                                data[pos] = data[pos + 1];

                        curSize--;
                }
        }
        void resize(const int &size = 2){
                timeS *temp = data;

                data = new timeS[capacity + size];
                for(int i = 0; i < capacity; i++)
                        data[i] = temp[i];

                capacity += size;
                delete [] temp;
        }
private:
        int curSize;
        int capacity
        timeS *data;
};

#endif
