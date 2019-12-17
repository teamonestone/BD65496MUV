/**
 * @file BD65496MUV.cpp
 * @brief The source file of the Arduino library for the BD65496MUV Single Brushed DC Motor Driver.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.2
 * @date 30 October 2019
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

//////////////////
// constructors //
//////////////////

/**
 * @brief Constructor of the BD65496MUV class without the pwm mode pin.
 */
BD65496MUV::BD65496MUV(Mode mode, uint8_t pinInA, uint8_t pinInB) {
    
    // setting private variables
    _driverMode = mode;
    _pinInA = pinInA;
    _pinInB = pinInB;
    _pinPwmMode = 0;

    _initDriverPins();
}

/**
 * @brief Constructor of the BD65496MUV class with the pwm mode pin.
 */
BD65496MUV::BD65496MUV(Mode mode, uint8_t pinInA, uint8_t pinInB, uint8_t pinPwmMode) {

    // setting private variables
    _driverMode = mode;
    _pinInA = pinInA;
    _pinInB = pinInB;
    _pinPwmMode = pinPwmMode;

    _initDriverPins();
}

/**
 * @brief Main destructor  of the BD65496MUV class.
 */
BD65496MUV::~BD65496MUV() {
    ;
}

///////////////
// functions //
///////////////

void BD65496MUV::_initDriverPins() {

    // basic pins
    pinMode(_pinInA, OUTPUT);
    pinMode(_pinInB, OUTPUT);
    digitalWrite(_pinInA, 0);
    digitalWrite(_pinInB, 0);

    // mode pin
    if (_pinPwmMode != 0) {

        pinMode(_pinPwmMode, OUTPUT);

        // set the driver mode
        _driverMode == Mode:H_Bridge ? digitalWrite(_pinPwmMode, 0) : digitalWrite(_pinPwmMode, 1);
    }
}

/**
 * @brief Get the version of the library.
 * 
 * @return the current version of the library.
 */
uint16_t BD65496MUV::get_version() {
    return _BD65496MUV_LIB_VERSION;
}