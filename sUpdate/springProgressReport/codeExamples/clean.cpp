void loop() {
        //update hardware and run top state for a frame
        clk->update();
        buttons->update();
        if(!clk->checkAlarms()){ //can generate a state transistion if an alarm goes off
                (*top)->curState->handleInput();
                (*top)->curState->runLogic();
                (*top)->curState->drawFrame();
        }
        //Statemachine manager
        switch(signal){
        case stateStack::NOTHING: break;                  //nothing requested
        case stateStack::NEW    : stk->push(newState);     //add new state requested.
                                  break;
        case stateStack::EXIT   : stk->pop();              //exit top state
                                  break;
        case stateStack::REPLACE: stk->pop();              //replace top state
                                  stk->push(newState);
                                  break;
        }
        //things that need to be cleaned up if a state change occured
        if(signal){
                top = stk->accessStack();
                signal = stateStack::NOTHING;
                newState = nullptr;
                disp->clearScrollingText(2);
        }
}
