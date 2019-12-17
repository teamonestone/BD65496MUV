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
 * @brief Main construcor of the TCA9548A class.
 */
BD65496MUV::BD65496MUV() {

}

/**
 * @brief Main destructor  of the TCA9548A class.
 */
BD65496MUV::~BD65496MUV() {
    ;
}

///////////////
// functions //
///////////////

/**
 * @brief Get the version of the library.
 * 
 * @return the current version of the library.
 */
uint16_t BD65496MUV::get_version() {
    return _BD65496MUV_LIB_VERSION;
}