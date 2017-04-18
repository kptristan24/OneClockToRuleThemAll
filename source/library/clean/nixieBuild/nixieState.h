#ifndef NIXIESTATE_H
#define NIXIESTATE_H

#include "display.h"
#include "timekeeping.h"
#include "state.h"
#include "nixieHeader.h"


class nixieClock : public state{
public:
        nixieClock();

        void handleInput();
        void runLogic();
        void drawFrame();
private:
        void __setTube(const uint8_t &, const uint8_t &);

        uint8_t const **numbers;
};

#endif
