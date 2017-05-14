
//setup the three menus
editAlarms::editAlarms(){
        currentState = 0;

        mainMenu.setMenuName("Alarm Menu ");
        mainMenu.addOption("Exit ", &signal, option::SET, stateStack::EXIT);
        mainMenu.addOption("New Alarm ", changeToAdd);
        mainMenu.addOption("Delete Alarm ", changeToDelete);

        //addAlarm.setMenuName("Time ");
        //addAlarm.addOption("Time ");

        deleteAlarm.addOption("Exit ", &currentState, option::SET, 0);
        deleteAlarm.addOption("Next Alarm ", deleteGetNextAlarm);
        deleteAlarm.addOption("Delete ", deleteAlarmResponse);
}

void editAlarms::changeToAdd(){
        currentlySelected = 0;
        alarmTime = clk->getCurrentTime();
        updateTimeString();
        addUpdateColors();
}

void editAlarms::changeToDelete(){
        if(clk->getAlarmTime(0, alarmTime)){
                deleteAlarm.setMenuName(timeStr);
                currentlySelected = 0;
                currentState = 2;
                updateTimeString();
        }
        else{ //no alarms currently set, return to menu
                currentlyState = 0;
        }
}

void editAlarms::handleInput(){
        switch(currentState){
        case 0: mainMenu.update();
                break;
        case 1: addAlarmInput();
                break;
        case 2: deleteAlarm.update();
                break;
        }
}

void editAlarms::addAlarmInput(){
        switch(currentlySelected){
        case 0:
        case 1:
        case 2:
        default:
                currentState = 0;
        }
}

void editAlarms::deleteAlarmResponse(){
        clk->removeAlarm(alarmTime);
        currentlySelected--;
        deleteGetNextAlarm();
}

void editAlarms::deleteGetNextAlarm(){
        currentlySelected++;
        if(!clk->getAlarmTime(currentlySelected, alarmTime)){
                currentlySelected = 0;
                if(!clk->getAlarmTime(currentlySelected, alarmTime)){
                        currentState = 0;
                }
        }
        deleteAlarm.setMenuName(timeStr);
        updateTimeString();
}

void editAlarms::updateTimeString(){
        if(alarmTime.hour > 9){
                timeStr[0] = '1';
                timeStr[1] = (alarmTime.hour - 10) + 48;
        }
        else{
                timeStr[0] = '0';
                timeStr[1] = alarmTime.hour + 48;
        }

        if(alarmTime.minute > 9){
                uint8_t temp = alarmTime.minute / 10;
                timeStr[2] = temp + 48;
                timeStr[3] = (alarmTime.minute - temp * 10) + 48;
        }

        timeStr[4] = '\n';
}

void editAlarms::runLogic(){

}

void editAlarms::drawFrame(){
        switch(currentState){
        case 0: mainMenu.draw();
                break;
        case 1: addAlarm.draw();
                break;
        case 2: deleteAlarm.draw();
                break;
        }
}

void editAlarms::addUpdateColors(){
        switch(currentlySelected){
        case 0: h = CRGB::Red;
                m = CRGB::Green;
                a = CRGB::Green;
                break;
        case 1: h = CRGB::Green;
                m = CRGB::Red;
                a = CRGB::Green;
                break;
        case 2: h = CRGB::Green;
                m = CRGB::Green;
                a = CRGB::Red;
                break;
        }
}

void editAlarms::addDrawTime(){


}
