#ifndef AVECTOR_H
#define AVECTOR_H

#include "timeS.h"

class aVec{
public:
        aVec(){
                data = new timeS[2];
                capacity = 2;
                curSize = 0;
        }
        uint8_t size(){
                return curSize;
        }
        void push_back(const timeS &item){
                data[curSize] = item;
                curSize++;

                if(curSize == capacity)
                        resize();
        }
        void insert_ordered(const timeS &item){
                uint8_t position;
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
                        for(uint8_t i = curSize; i > position; i++){
                                data[i] = data[i - 1];
                        }
                        data[position] = item;
                        if(curSize == capacity)
                                resize();
                }
        }
        const timeS & operator [](uint8_t i) const {return data[i];}
        timeS & operator [](uint8_t i) {return data[i];}
        void erase(const uint8_t &i){
                if(i >= curSize)
                        return;
                else if(i == (curSize - 1))
                        curSize--;
                else{
                        for(uint8_t pos = i; pos < curSize - 1; pos++)
                                data[pos] = data[pos + 1];

                        curSize--;
                }
        }
        void resize(const uint8_t &size = 2){
                timeS *temp = data;

                data = new timeS[capacity + size];
                for(uint8_t i = 0; i < capacity; i++)
                        data[i] = temp[i];

                capacity += size;
                delete [] temp;
        }
private:
        uint8_t curSize;
        uint8_t capacity;
        timeS *data;
};

#endif
