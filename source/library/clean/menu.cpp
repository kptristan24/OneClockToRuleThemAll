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
                temp = options.next;
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
                (option->next)->prev = newOption;
                option->next = newOption;
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
        case 0: options = options->next;
                break;
        case 1: options = options->prev;
                break;
        case 2: __executeOption();
                break;
        }
}

void menu::draw(){
        disp->scrollingText(title, 0, CRGB::Red, CRGB::Fuchsia);
        switch(options->mode){
        case option::EXT: options->display();
                          break;
        case default    : disp->scrollingText(options->text, 1, CRGB::Blue, CRGB::Aqua);
                          break;
        }
}

void menu::__executeOption(){
        switch(options->mode){
        case option::FUNC: options->action();
                           break;
        case option::EXT : options->action();
                           break;
        case option::SET : *(options->v) = change;
                           break;
        case option::MOD : *(options->v) += change;
                           break;
        case option::INC : *(options->v)++;
                           break;
        case option::DEC : *(options->v)--;
                           break;
        }
}
