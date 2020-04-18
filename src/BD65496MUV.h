/**
 * @file BD65496MUV.h
 * @brief The header file of the Arduino library for the BD65496MUV Single Brushed DC Motor Driver.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author 
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 18 April 2020
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef BD65496MUV_h
#define BD65496MUV_h

//////////////
// includes //
//////////////
#include <inttypes.h>
#include <Arduino.h>


/////////////
// defines //
/////////////


/////////////
// classes //
/////////////

/**
 * @class BD65496MUV
 * @brief The main class of the Arduino library for the BD65496MUV Single Brushed DC Motor Driver.
 */
class BD65496MUV {
// Begin PUBLIC ------------------------------------------------------------------
    public:

        // enums
        enum DriverMode {Speed_n_Dir, H_Bridge};
        enum PowerMode  {Running, Standby};
        enum SwitchingSpeed {On150_Off50, On250_Off70, On350_Off90, On500_Off110};
        enum ShortBreakMode {On, Off};

        // constructors
        BD65496MUV(uint8_t pinInA, uint8_t pinInB, uint8_t pinPwmMode ,DriverMode driverMode = DriverMode::Speed_n_Dir);    // Constructor of the BD65496MUV class with the pwm mode pin.
        BD65496MUV(uint8_t pinInA, uint8_t pinInB, DriverMode driverMode = DriverMode::Speed_n_Dir,                         // Constructor of the BD65496MUV class with all pins (Pro-Mode).
                    bool pinPwmModeDefined = false, uint8_t pinPwmMode = 0,
                    bool pinPsDefined = false, uint8_t pinPs = 0, PowerMode powerMode = PowerMode::Running,
                    bool pinTrDefined = false, uint8_t pinTr1 = 0, uint8_t pinTr2 = 0,
                    SwitchingSpeed switchingSpeed = SwitchingSpeed::On150_Off50,
                    ShortBreakMode shortBreakMode = ShortBreakMode::Off);

        // functions
        void setSpeed(int16_t speed);                           // Set the speed of the motor.
        int16_t getSpeed();                                     // Get the speed of the moter.

        void setDriverMode(DriverMode driverMode);              // Set the driver mode of the driver.
        DriverMode getDriverMode();                             // Get the dirver mdoe of the driver.

        void setPowerMode(PowerMode powerMode);                 // Set the power mode of the driver.
        PowerMode getPowerMode();                               // Get the power mode of the driver.

        void setSwitchingSpeed(SwitchingSpeed switchingSpeed);  // Set the switching speed of the driver.
        SwitchingSpeed getSwitchingSpeed();                     // Get the switching speed of the driver.

        void setShortBreakMode(ShortBreakMode shortBreakMode);  // Set the short break mode of the driver.
        ShortBreakMode getShortBreakMode();                     // Get the short break mode of the dirver.

        uint16_t getVersion();                                  // Get the version of the library.

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------        
    private:

        // enum
        enum TurnDir {CW, CCW};                 // Enum that represents the turn direction of the motor.

        // variables
        DriverMode _driverMode;                 // Var for the driver mode.
        PowerMode _powerMode;                   // Var for the power mode.
        SwitchingSpeed _switchingSpeed;         // Var for the switching speed.
        ShortBreakMode _shortBreakMode;         // Var fot the short break mode.

        bool _pinPwmModeDefined;                // Flag if the pwm mode pin is defined.
        bool _pinPsDefined;                     // Flag if the ps pin is defined.
        bool _pinTrDefined;                     // Flag if the tr pins are defined.

        uint8_t _pinInA;                        // Var for the number of the INA pin.
        uint8_t _pinInB;                        // Var for the number of the INB pin.
        uint8_t _pinPwmMode;                    // Var for the number of the pwm mode pin.
        uint8_t _pinPs;                         // Var for the number of the PS pin.
        uint8_t _pinTr1;                        // Var for the number of the TR1 pin.
        uint8_t _pinTr2;                        // Var for the number of the TR2 pin.

        int16_t _speed;                         // Var for the current motor speed.

        // functions 
        void _initDriverPins();                 // Function to initialize the output pins.

// End PRIVATE -------------------------------------------------------------------
};

#endif