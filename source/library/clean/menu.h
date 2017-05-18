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

enum OptionModes {FUNC, SET, MOD, INC, DECR, EXT};

template<class T>
class menu{
public:
        typedef void (T::*func_ptr)();

        menu();
        ~menu();
        void setMenuName(const char *);
        void setupMenu(const char *, const T *);
        void addOption(const char *, func_ptr);
        void addOption(const char *, uint8_t *, uint8_t, uint8_t);

        void update();
        void draw();
private:

        struct option{
                enum MODES {FUNC, SET, MOD, INC, DECR, EXT};

                option(const char *m, func_ptr a){
                        action = a;
                        text = new char[strlen(m)];
                        strcpy(text, m);
                        mode = FUNC;
                }
                option(const char *m, uint8_t *v, uint8_t mode, uint8_t change){
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
                uint8_t *var;
                uint8_t mode;
                uint8_t change;
                char *text;
                func_ptr action;
                func_ptr display;

                option *prev;
                option *next;
        };

        void __addToList(option *);
        void __executeOption();

        T *relatedObject;
        char *title;
        option *options;
};

template<class T> menu<T>::menu(){
        options = nullptr;
        title = new char[7];
        strcpy(title, "empty ");
}

template<class T> menu<T>::~menu(){
        if(title)
                delete [] title;

        option *temp;
        while(options){
                temp = options->next;
                if(temp == options)
                        temp = nullptr;
                delete options;
                options = temp;
        }
}

template<class T> void menu<T>::setMenuName(const char *text){
        if(title)
                delete [] title;
        title = new char[strlen(text) + 1];
        strcpy(title, text);
}

template<class T> void menu<T>::setupMenu(const char *text, const T *other){
        if(title)
                delete [] title;
        title = new char[strlen(text) + 1];
        strcpy(title, text);
}

template<class T> void menu<T>::__addToList(option *newOption){
        if(options == nullptr){
                newOption->next = newOption;
                newOption->prev = newOption;
                options = newOption;
        }
        else{
                newOption->prev = options;
                newOption->next = options->next;
                (options->next)->prev = newOption;
                options->next = newOption;
                options = newOption;
        }
}

template<class T> void menu<T>::addOption(const char *text, func_ptr action){
        option *newOption = new option(text, action);
        __addToList(newOption);
}

template<class T> void menu<T>::addOption(const char *text, uint8_t *v, uint8_t mode, uint8_t change){
        option *newOption = new option(text, v, mode, change);
        __addToList(newOption);
}

template<class T> void menu<T>::update(){
        int input = buttons->getInput();
        if(options == nullptr && input){ //if there aren't any options, quit
                signal = 2;
                return;
        }

        switch(input){
        case 0: disp->clearScrollingText(display::BOT);
                options = options->next;
                break;
        case 1: disp->clearScrollingText(display::BOT);
                options = options->prev;
                break;
        case 2: disp->clearScrollingText(display::BOT);
                __executeOption();
                break;
        }
}

template<class T> void menu<T>::draw(){
        disp->scrollingText(title, 0, CRGB::Red, CRGB::Fuchsia);
        switch(options->mode){
        case option::EXT: (relatedObject->*(options->display))();
                          break;
        default         : disp->scrollingText(options->text, 1, CRGB::Blue, CRGB::Aqua);
                          break;
        }
}

template<class T> void menu<T>::__executeOption(){
        switch(options->mode){
        case option::FUNC: (relatedObject->*(options->action))();
                           break;
        case option::EXT : (relatedObject->*(options->action))();
                           break;
        case option::SET : *(options->var) = options->change;
                           break;
        case option::MOD : *(options->var) += options->change;
                           break;
        case option::INC : *(options->var)++;
                           break;
        case option::DECR: *(options->var)--;
                           break;
        }
}

#endif

/*
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
        option(const char *m, uint8_t *v, uint8_t mode, uint8_t change){
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
        uint8_t *var;
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
        void addOption(const char *, uint8_t *, uint8_t, uint8_t);

        void update();
        void draw();
private:
        void __addToList(const option *);
        void __executeOption();
        char *title;
        option *options;
};

#endif
*/
