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
        option(const char *m, func_ptr a){
                action = a;
                text = new char[strlen(m)];
                strcpy(text, m);
        }
        ~option(){
                if(text)
                        delete [] text;
        }
        char *text;
        func_ptr action;

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

        void update();
        void draw();
private:
        char *title;
        option *options;
};

#endif
