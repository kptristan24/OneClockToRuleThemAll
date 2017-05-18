#ifndef MENU_H
#define MENU_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"

extern display *disp;
extern clockLib *clk;
extern state *newState;
extern uint8_t signal;
extern Buttons *buttons;

typedef void (*func_ptr)();

struct option{
        enum MODES {FUNC, SET, MOD, INC, DECR, EXT};

        option(const char *m, func_ptr a){
                action = a;
                text = new char[strlen(m)];
                strcpy(text, m);
                mode = FUNC;
        }
        option(const char *m, int *v, uint8_t mode, uint8_t change){
                text = new char[strlen(m)];
                strcpy(text, m);
                this->mode = mode;
                var = v;
                this->change = change;
        }
        option(func_ptr a, func_ptr d){
                action = a;
                display = d;
        }
        ~option(){
                if(text)
                        delete [] text;
        }
        int *var;
        uint8_t mode;
        uint8_t change;
        char *text;
        func_ptr action;
        func_ptr display;

        option *prev;
        option *next;
};

class menu{
public:
        menu();
        menu(const char *);
        ~menu();
        void setMenuName(const char *);
        void addOption(const char *, func_ptr);
        void addOption(const char *, int *, uint8_t, uint8_t);

        void update();
        void draw();
private:
        void __executeOption();
        char *title;
        option *options;
};

#endif
