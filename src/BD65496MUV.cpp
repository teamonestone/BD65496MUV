/**
 * @file BD65496MUV.cpp
 * @brief The source file of the Arduino library for the BD65496MUV Single Brushed DC Motor Driver.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 18 April 2020
 * @copyright This project is released under the GNU General Public License v3.0
 */

/**
 * @mainpage Arduino library for the BD65496MUV Single Brushed DC Motor Driver.
 *
 * @section intro_sec Introduction
 *
 * ...
 *
 * @section dependencies Dependencies
 *
 * -
 *
 * @section author Author
 *
 * Written by:
 * - Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * - Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a> 
 * 
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 *
 * @section license License
 *
 * This project is released under the GNU General Public License v3.0
 * 
*/

/////////////
// include //
/////////////
#include "BD65496MUV.h"


/////////////
// defines //
/////////////
#define _BD65496MUV_LIB_VERSION 100     ///< The version number of the library.


//////////////////
// constructors //
//////////////////

/**
 * @brief Constructor of the BD65496MUV class with the pwm mode pin.
 * 
 * @param driverMode The driver mode of the driver (Speed_n_Dir or H_Bridge).
 * @param pinInA The pin number to which the INA pin is connected.
 * @param pinInB The pin number to which the INB pin is connected.
 * @param pinPwmMode The pin number to wicht the pmw mode pin is connected.
 */
BD65496MUV::BD65496MUV(uint8_t pinInA, uint8_t pinInB, uint8_t pinPwmMode, DriverMode driverMode) {

    // setting private variables
    _driverMode = driverMode;
    _powerMode = PowerMode::Running;
    _switchingSpeed = SwitchingSpeed::On150_Off50;
    _shortBreakMode = ShortBreakMode::Off;
    _pinPwmModeDefined = true;
    _pinPsDefined = false;
    _pinTrDefined = false;
    _pinInA = pinInA;
    _pinInB = pinInB;
    _pinPwmMode = pinPwmMode;
    _pinPs = 0;
    _pinTr1 = 0;
    _pinTr2 = 0;
    _speed = 0;

    // init pins
    _initDriverPins();
}

/**
 * @brief Constructor of the BD65496MUV class with all pins (Pro-Mode).
 * 
 * @param driverMode The driver mode of the driver (Speed_n_Dir or H_Bridge).
 * @param pinInA The pin number to which the INA pin is connected.
 * @param pinInB The pin number to which the INB pin is connected.
 * @param pinPwmModeDefined Flag that defines if the pwm mode pin is connected.
 * @param pinPwmMode The pin number to which the pmw mode pin is connected.
 * @param pinPsDefined Flag that defines if the PS pin is connected.
 * @param pinPs The pin number to which the PS pin is connected.
 * @param powerMode The power mode of the driver (Running or Standby).
 * @param pinTrDefined Flag that defines if the TR pins are connected.
 * @param pinTr1 The pin number to which the TR1 pin is connected.
 * @param pinTr2 The pin number to which the TR2 pin is connected.
 * @param On150_Off50 The switching speed of the driver (On150_Off50, On250_Off70, On350_Off90, On500_Off110).
 * @param shortBreakMode The short break mode of the driver (On or Off).
 */
BD65496MUV::BD65496MUV(uint8_t pinInA, uint8_t pinInB, DriverMode driverMode, 
                    bool pinPwmModeDefined, uint8_t pinPwmMode,
                    bool pinPsDefined, uint8_t pinPs, PowerMode powerMode,
                    bool pinTrDefined, uint8_t pinTr1, uint8_t pinTr2,
                    SwitchingSpeed switchingSpeed,
                    ShortBreakMode shortBreakMode) {

    // setting private variables
    _driverMode = driverMode;
    _powerMode = powerMode;
    _switchingSpeed = switchingSpeed;
    _shortBreakMode = shortBreakMode;
    _pinPwmModeDefined = pinPwmModeDefined;
    _pinPsDefined = pinPsDefined;
    _pinTrDefined = pinTrDefined;
    _pinInA = pinInA;
    _pinInB = pinInB;
    _pinPwmMode = pinPwmMode;
    _pinPs = pinPs;
    _pinTr1 = pinTr1;
    _pinTr2 = pinTr2;
    _speed = 0;

    // init pins
    _initDriverPins();
}


//////////////////////
// public functions //
//////////////////////

/**
 * @brief Set the speed of the motor.
 * 
 * @param speed The speed of the motor (from -255 to 255).
 */
void BD65496MUV::setSpeed(int16_t speed) {

    // get trun direction
    TurnDir trunDir;
    if (speed < 0) {
        
        speed = speed * (-1);
        trunDir = TurnDir::CCW;
    }
    else {

        trunDir = TurnDir::CW;
    }

    // check speed
    if (speed > 255) return;

    switch (_driverMode)
    {
        case Speed_n_Dir:
        
            // check for short break mode on and speed 0
            if (_shortBreakMode == ShortBreakMode::On && speed == 0) {
                
                digitalWrite(_pinInA, 0);
                digitalWrite(_pinInB, 0);
            }
            // normale mode
            else {
                
                analogWrite(_pinInA, speed);
                digitalWrite(_pinInB, trunDir == TurnDir::CW ? 0 : 1);
            }

        break;
    
        case H_Bridge:

            // check for short break mode on and speed 0
            if (_shortBreakMode == ShortBreakMode::On && speed == 0) {
                
                digitalWrite(_pinInA, 1);
                digitalWrite(_pinInB, 1);
            }
            // check for short break mode off and speed 0
            else if (_shortBreakMode == ShortBreakMode::Off && speed == 0) {
                
                digitalWrite(_pinInA, 0);
                digitalWrite(_pinInB, 0);
            }
            else {
                
                // check trun dir
                if (trunDir == TurnDir::CW) {
                    
                    analogWrite(_pinInA, speed);
                    digitalWrite(_pinInB, 0);
                }
                else {

                    digitalWrite(_pinInA, 0);
                    analogWrite(_pinInB, speed);
                }
            }

        break;
    }
}

/**
 * @brief Get the speed of the moter.
 * 
 * @return The current speed of the motor.
 */
int16_t BD65496MUV::getSpeed() {
    return _speed;
}

/**
 * @brief Set the driver mode of the driver.
 * 
 * @param driverMode The driver mode (Speed_n_Dir or H_Bridge).
 */
void BD65496MUV::setDriverMode(BD65496MUV::DriverMode driverMode) {
    
    // set private vars
    _driverMode = driverMode;

    // check if the needed pins are defined
    if (_pinPwmModeDefined) {

        // set output to set the driver mode
        _driverMode == DriverMode::H_Bridge ? digitalWrite(_pinPwmMode, 0) : digitalWrite(_pinPwmMode, 1);
    }
}

/**
 * @brief Get the dirver mdoe of the driver.
 * 
 * @return The current driver mode of the driver.
 */
BD65496MUV::DriverMode BD65496MUV::getDriverMode() {
    return _driverMode;
}

/**
 * @brief Set the power mode of the driver.
 * 
 * @param powerMode The power mode (Running or Standby).
 */
void BD65496MUV::setPowerMode(BD65496MUV::PowerMode powerMode) {

    // set private vars
    _powerMode = powerMode;

    // check if the needed pins are defined
    if (_pinPsDefined) {

        // set output to set the power mode
        _powerMode == PowerMode::Running ? digitalWrite(_pinPs, 1) : digitalWrite(_pinPs, 0);
    }
}

/**
 * @brief Get the power mode of the driver.
 * 
 * @return The current power mode of the driver.
 */
BD65496MUV::PowerMode BD65496MUV::getPowerMode() {
    return _powerMode;
}

/**
 * @brief Set the switching speed of the driver.
 * 
 * @param switchingSpeed The switching speed (On150_Off50, On250_Off70, On350_Off90, On500_Off110).
 */
void BD65496MUV::setSwitchingSpeed(BD65496MUV::SwitchingSpeed switchingSpeed) {

    // set private vars
    _switchingSpeed = switchingSpeed;

    // check if the needed pins are defined
    if (_pinTrDefined) {

        // set output to set the switching speed
        switch (_switchingSpeed) {

            case SwitchingSpeed::On150_Off50 :
                digitalWrite(_pinTr1, 0);
                digitalWrite(_pinTr2, 0);
            break;

            case SwitchingSpeed::On250_Off70 :
                digitalWrite(_pinTr1, 1);
                digitalWrite(_pinTr2, 0);
            break;

            case SwitchingSpeed::On350_Off90 :
                digitalWrite(_pinTr1, 0);
                digitalWrite(_pinTr2, 1);
            break;

            case SwitchingSpeed::On500_Off110 :
                digitalWrite(_pinTr1, 1);
                digitalWrite(_pinTr2, 1);
            break;
        }
    }
}

/**
 * @brief Get the switching speed of the driver.
 * 
 * @return The current switching speed of the driver.
 */
BD65496MUV::SwitchingSpeed BD65496MUV::getSwitchingSpeed() {
    return _switchingSpeed;
}

/**
 * @brief Set the short break mode of the driver.
 * 
 * @param shortBreakMode The short break mode (On or Off).
 */
void BD65496MUV::setShortBreakMode(BD65496MUV::ShortBreakMode shortBreakMode) {
    _shortBreakMode = shortBreakMode;
}

/**
 * @brief Get the short break mode of the dirver.
 * 
 * @return The current short break mode of the driver.
 */
BD65496MUV::ShortBreakMode BD65496MUV::getShortBreakMode() {
    return _shortBreakMode;
}

/**
 * @brief Get the version of the library.
 * 
 * @return The current version of the library.
 */
uint16_t BD65496MUV::getVersion() {
    return _BD65496MUV_LIB_VERSION;
}


///////////////////////
// private functions //
///////////////////////

/**
 * @brief Init the gpio pins to which the driver is connected to.
 */
void BD65496MUV::_initDriverPins() {

    // basic pins
    pinMode(_pinInA, OUTPUT);
    pinMode(_pinInB, OUTPUT);
    digitalWrite(_pinInA, 0);
    digitalWrite(_pinInB, 0);

    // mode pin
    if (_pinPwmModeDefined) {

        // set pin mode
        pinMode(_pinPwmMode, OUTPUT);

        // set the driver mode
        setDriverMode(_driverMode);
    }

    // ps pin
    if (_pinPsDefined) {
        
        // set pin mode
        pinMode(_pinPs, OUTPUT);

        // set the power mode
        setPowerMode(_powerMode);
    }

    // tr pins
    if (_pinTrDefined) {

        // set pin mode
        pinMode(_pinTr1, OUTPUT);
        pinMode(_pinTr2, OUTPUT);

        // set the switching speed
        setSwitchingSpeed(_switchingSpeed);
    }
}