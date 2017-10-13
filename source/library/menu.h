#ifndef MENU_H
#define MENU_H

#include <avr/pgmspace.h>
#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"

extern display disp;
extern clockLib clk;
extern Buttons buttons;
extern state *newState;
extern uint8_t signal;

enum OptionModes {FUNC, SET, MOD, INC, DECR, EXT};

template<class T>
class menu{
public:
        typedef void (T::*func_ptr)();

        menu();
        ~menu();
        void setMenuName(const __FlashStringHelper *);
        void setMenuName(const char *);
        void setupMenu(const __FlashStringHelper *, const T *);
        void addOption(const __FlashStringHelper *, func_ptr);
        void addOption(const __FlashStringHelper *, uint8_t *, uint8_t, uint8_t);

        void update();
        void draw() const;
private:

        struct option{
                option(const __FlashStringHelper *m, func_ptr a){
                        action = a;
                        staticText = strlen_PF(m);
                        text = new char[staticText + 1];
                        strcpy_PF(text, m);
                        mode = FUNC;
                }
                option(const __FlashStringHelper *msg, uint8_t *v, uint8_t m, uint8_t c){
                        staticText = strlen_PF(msg);
                        text = new char[staticText + 1];
                        strcpy_PF(text, msg);
                        mode = m;
                        var = v;
                        change = c;
                }
                option(func_ptr a, func_ptr d){
                        action = a;
                        display = d;
                }
                ~option(){
                        if(text)
                                delete [] text;
                }
                uint8_t staticText;
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
        uint8_t staticMenu;
};

template<class T> menu<T>::menu(){
        options = nullptr;
        title = new char[3];
        staticMenu = 2;
        strcpy(title, "e ");
}

template<class T> menu<T>::~menu(){
        Serial.print(F("menuD\n"));
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

template<class T> void menu<T>::setMenuName(const __FlashStringHelper *text){
        if(title)
                delete [] title;

        staticMenu = strlen_PF(text);
        title = new char[staticMenu + 1];
        strcpy_PF(title, text);
        disp.clearScrollingText(display::TOP);
}

template<class T> void menu<T>::setMenuName(const char *text){
        if(title)
                delete [] title;

        staticMenu = strlen(text);
        title = new char[staticMenu + 1];
        strcpy(title, text);
        disp.clearScrollingText(display::TOP);
}

template<class T> void menu<T>::setupMenu(const __FlashStringHelper *text, const T *other){
        if(title)
                delete [] title;

        relatedObject = other;
        staticMenu = strlen_PF(text);
        title = new char[staticMenu + 1];
        strcpy_PF(title, text);
        disp.clearScrollingText(display::TOP);
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

template<class T> void menu<T>::addOption(const __FlashStringHelper *text, func_ptr action){
        option *newOption = new option(text, action);
        __addToList(newOption);
}

template<class T> void menu<T>::addOption(const __FlashStringHelper *text, uint8_t *v, uint8_t mode, uint8_t change){
        option *newOption = new option(text, v, mode, change);
        __addToList(newOption);
}

template<class T> void menu<T>::update(){
        int input = buttons.getInput();
        if(options == nullptr && input){ //if there aren't any options, quit
                signal = stateStack::EXIT;
                return;
        }

        switch(input){
        case 0: disp.clearScrollingText(display::BOT);
                options = options->next;
                break;
        case 1: disp.clearScrollingText(display::BOT);
                options = options->prev;
                break;
        case 2: disp.clearScrollingText(display::BOT);
                __executeOption();
                break;
        }
}

template<class T> void menu<T>::draw() const{
        disp.clear();
        if(staticMenu > 4)
                disp.scrollingText(title, 0, CRGB::Aqua, CRGB::Blue);
        else
                disp.staticText(title, display::TOP, staticMenu, CRGB::Aqua, CRGB::Blue);

        switch(options->mode){
        case EXT: (relatedObject->*(options->display))();
                  break;
        default : if(options->staticText > 4)
                        disp.scrollingText(options->text, display::BOT, CRGB::Blue, CRGB::Green);
                  else
                        disp.staticText(options->text, display::BOT, options->staticText, CRGB::Aqua, CRGB::Blue);
        }
}

template<class T> void menu<T>::__executeOption(){
        switch(options->mode){
        case FUNC: (relatedObject->*(options->action))();
                   break;
        case EXT : (relatedObject->*(options->action))();
                   break;
        case SET : *(options->var) = options->change;
                   break;
        case MOD : *(options->var) += options->change;
                   break;
        case INC : *(options->var)++;
                   break;
        case DECR: *(options->var)--;
                   break;
        }
}

#endif
