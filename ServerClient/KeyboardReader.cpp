#include "KeyboardReader.h"

#include <string>
#include <unistd.h>
#include <iostream>
#include <string>

#include "ClientContext.h"

KeyboardReader::KeyboardReader(ClientContext* clientContext, const std::function<void(std::string)>& callBack)
    : core::eventreceiver::ReadEventReceiver("KeyboardReader")
    , callBack(callBack)
    ,clientcontext(clientContext){

    enable(STDIN_FILENO);

}

KeyboardReader::~KeyboardReader(){
    if(clientcontext != nullptr){
        clientcontext->keyboardReaderAway();
    }
}

void KeyboardReader :: readEvent(){
    /*int value;

    std::cin >> value;

    std::cout << "Value entered: " << value << std::endl;
*/



    char buffer[256];

    ssize_t ret =  read(STDIN_FILENO, buffer, 256);

    if(ret > 0){
        if(clientcontext != nullptr){
             callBack(std::string(buffer, ret));
        }
    }else{
        std::cout << "Nothing entered or error" << std::endl;
    }
}

void KeyboardReader :: stop(){
    disable();
}

void KeyboardReader::clientContextAway(){
    clientcontext = nullptr;
}

void KeyboardReader :: unobservedEvent(){
    delete this;
}
