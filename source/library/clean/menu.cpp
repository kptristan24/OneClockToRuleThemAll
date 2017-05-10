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
        if(options == nullptr && input){
                signal = 2;
                return;
        }

        switch(input){
        case 0: 
                break;
        case 1:
                break;
        case 2:

                break;
        }
}

void menu::draw(){

}
