display disp;
clockLib clk;
stateStack stk;

state *runningState;
state *newState;
uint8_t signal;

void loop() {
        clk.update();

        if(!clk.checkAlarms()){ //run top program unless alarm happened
                runningState->handleInput();
                runningState->runLogic();
                runningState->drawFrame();
        }
        else{ //an alarm went off!
                newState = new alarmState(getCurrentTime());
                signal = stateStack::NEW;
        }

        switch(signal){ //Statemachine manager
        case stateStack::NEW    : stk.push(newState);
                                  break;
        case stateStack::EXIT   : stk.pop();
                                  break;
        case stateStack::REPLACE: stk.pop();
                                  stk.push(newState);
                                  break;
        }

        if(signal){ cleanup after state change
                runningState = stk.accessStack()->curState;
                signal = stateStack::NOTHING;
                newState = nullptr;
                disp.clearScrollingText(display::ALL);
                disp.clear();
        }
}
