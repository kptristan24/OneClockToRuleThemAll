#include "menu.h"

menu::menu(){
        options = nullptr;
        title = new char[7];
        strcpy(title, "empty ");
}

menu::menu(const char *text){
        options = nullptr;
        title = new char[strlen(text) + 1];
        strcpy(title, text);
}

menu::~menu(){
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

void menu::setMenuName(const char *text){
        if(title)
                delete [] title;
        title = new char[strlen(text) + 1];
        strcpy(title, text);
}

void menu::addOption(const char *text, func_ptr action){
        option *newOption = new option(text, action);
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

void menu::update(){
        int input = buttons->getInput();
        if(options == nullptr && input){ //if there aren't any options, quit
                signal = 2;
                return;
        }

        switch(input){
        case 0: disp->clearScrollingText(dispaly::BOT);
                options = options->next;
                break;
        case 1: disp->clearScrollingText(dispaly::BOT);
                options = options->prev;
                break;
        case 2: disp->clearScrollingText(dispaly::BOT);
                __executeOption();
                break;
        }
}

void menu::draw(){
        disp->scrollingText(title, 0, CRGB::Red, CRGB::Fuchsia);
        switch(options->mode){
        case option::EXT: options->display();
                          break;
        default         : disp->scrollingText(options->text, 1, CRGB::Blue, CRGB::Aqua);
                          break;
        }
}

void menu::__executeOption(){
        switch(options->mode){
        case option::FUNC: options->action();
                           break;
        case option::EXT : options->action();
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
