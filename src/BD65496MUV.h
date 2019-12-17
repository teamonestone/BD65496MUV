/**
 * @file BD65496MUV.h
 * @brief The header file of the Arduino library for the BD65496MUV Single Brushed DC Motor Driver.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author 
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 17 December 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef BD65496MUV_h
#define BD65496MUV_h

// includes
#include <inttypes.h>
#include <Arduino.h>

// defines
#define _BD65496MUV_LIB_VERSION 100	///< The version number of the library.

/**
 * @class BD65496MUV
 * @brief The main class of the Arduino library for the BD65496MUV Single Brushed DC Motor Driver.
 */
class BD65496MUV {
// Begin PUBLIC ------------------------------------------------------------------
    public:

        enum Mode {H_Bridge, Speed_n_Dir};

        // constructors
        BD65496MUV(Mode mode, uint8_t pinInA, uint8_t pinInB);                          // Constructor of the BD65496MUV class without the pwm mode pin.
        BD65496MUV(Mode mode, uint8_t pinInA, uint8_t pinInB, uint8_t pinPwmMode);      // Constructor of the BD65496MUV class with the pwm mode pin.
        ~BD65496MUV();                                                                  // Main destructor  of the BD65496MUV class.

        // functions
        uint16_t get_version();         // Get the version of the library.

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------        
    private:

        // variables
        Mode _driverMode;
        uint8_t _pinInA;
        uint8_t _pinInB;
        uint8_t _pinPwmMode;

        // functions 
        void _initDriverPins();


// End PRIVATE -------------------------------------------------------------------
};

#endif