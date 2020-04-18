/*
    WARNING!!!
    This Example is only used for internal testing of the library.
    It don't represent a propper usecase for this library.
    So please ignore this file!
*/





























































































#include "BD65496MUV.h"

BD65496MUV motA(1, 2);
BD65496MUV motB(1, 2, BD65496MUV::DriverMode::Speed_n_Dir);
BD65496MUV motC(1, 2, 3, BD65496MUV::DriverMode::Speed_n_Dir);
BD65496MUV motD(1, 2, BD65496MUV::DriverMode::Speed_n_Dir,
                  true, 3, 
                  true, 4, BD65496MUV::PowerMode::Running,
                  true, 5, 6, BD65496MUV::SwitchingSpeed::On150_Off50,
                  BD65496MUV::ShortBreakMode::Off);

void setup() {

    motA.setSpeed(1); 
    motA.getSpeed(); 
    motA.setDriverMode(BD65496MUV::DriverMode::Speed_n_Dir);
    motA.getDriverMode();
    motA.setPowerMode(BD65496MUV::PowerMode::Running);
    motA.getPowerMode();
    motA.setSwitchingSpeed(BD65496MUV::SwitchingSpeed::On150_Off50); 
    motA.getSwitchingSpeed();
    motA.setShortBreakMode(BD65496MUV::ShortBreakMode::Off);
    motA.getShortBreakMode();
    motA.getVersion();
}

void loop() {
}
