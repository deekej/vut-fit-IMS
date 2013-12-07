/**
 * File:          choco_fact_sim.cc
 * Version:       0.0.0.0
 * Start date:    06-12-2013
 * Last update:   06-12-2013
 *
 * Course:        IMS (winter semester, 2013)
 * Project:       Stochastic simulation of queuing system. [Assignment #4.]
 *
 * Authors:       Daniela Srubarova (aka Aileen), 3BIT, [team-leader]
 *                David Kaspar (aka Dee'Kej), 3BIT
 * 
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies,
 *                Czech Republic
 *
 * E-mails:       xsruba01@stud.fit.vutbr.cz
 *                xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Implementation of stochastic simulation of hypothetical
 *                chocolate factory queuing system. This implementation
 *                uses SimLib/C++ simulation library (version 3), which
 *                is distributed by GPLv1 license.
 *
 * More info @:   http://perchta.fit.vutbr.cz:8000/vyuka-ims/31
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc (GCC) 4.8.0
 */


/* *********************************************************************************************************************************************************** *
 * ***[ START OF CHOCO_FACT_SIM.CC ]************************************************************************************************************************** *
 * *********************************************************************************************************************************************************** */


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

/* C++ header files. */
#include <iostream>
#include <sstream>
#include <string>

/* C header files. */
#include <cstdblib>

/* SimLib/C++ header file. */
#include <simlib.h>


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ CONSTANTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */



/* *********************************************************************************************************************************************************** *
 ~ ~~~[ DATA TYPES DECLARATIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */



/* *********************************************************************************************************************************************************** *
 ~ ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */



/* *********************************************************************************************************************************************************** *
 ~ ~~~[ AUXILIARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

void display_help(const char *prg_name)
{{{
  std::cout << prg_name << " - implementation of stochastic simulation of hypothetical chocolate factory queuing system." << std::endl;
  std::cout << "This is the result of team project of IMS course in year 2013 @ Faculty of Information Technology," << std::endl;
  std::cout << "Brno University of Technology, Czech Republic.\n" << std::endl;
  std::cout << "Authors:\tDaniela Srubarova (aka Aileen)" << std::endl;
  std::cout << "\t\tDavid Kaspar (aka Dee'Kej)\n" << std::endl;
  std::cout << "Contact:\txsruba01@stud.fit.vutbr.cz" << std::endl;
  std::cout << "\t\txkaspa34@stud.fit.vutbr.cz" << std::endl;

  return;  
}}}


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ MAIN FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

int main(int argc, char *argv[])
{{{

  return EXIT_SUCCESS;
}}}


/* *********************************************************************************************************************************************************** *
 * ***[ EMD OF CHOCO_FACT_SIM.CC ]**************************************************************************************************************************** *
 * *********************************************************************************************************************************************************** */
