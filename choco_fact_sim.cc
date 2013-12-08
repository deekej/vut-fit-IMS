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
 * NOTE:          This source file is written in English, because we both
 *                agreed it's common standard and we don't like source files
 *                using Czech.
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
#include <fstream>
#include <iostream>
#include <string>

/* C header files. */
#include <cmath>
#include <cstdlib>
#include <cstring>

/* SimLib/C++ header file. */
#include <simlib.h>


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ CONSTANTS & DATA TYPES DECLARATIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

enum chocolate_type {
  WHITE = 0,
  MILK,
  DARK,
};


enum order_chances_types {
  TAKING_REST = 0,
  TRYING_COMPETITION,
  TRYING_COMPETITION2,
};


enum store_occupancy_types {
  MIN_OCCUPANCY = 0,
  ADEQUATE_OCCUPANCY,
};


double order_chances[][4] = {
  {31, 48, 27},
  {28, 54, 33},
  {30, 51, 29},
};


double store_occupancy[][2] = {
  {20, 70},
  {25, 80},
  {20, 30},
};


static const double NEW_ORDER_WHITE_CHANCE = 13;
static const double NEW_ORDER_MILK_CHANCE = NEW_ORDER_WHITE_CHANCE + 49;


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ FACILITIES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

class storehouse : public Facility {
  private:
    unsigned max_capacity;
    unsigned act_capacity;
    enum chocolate_type store_type;

  public:

#if 0
  storehouse(enum chocolate_type type, unsigned max_cap, unsigned init_cap) : Facility()
  {{{
    this->store_type = type;
    this->max_capacity = max_cap;
    this->act_capacity = init_cap;
  }}}
#endif

  storehouse(const char *name, enum chocolate_type type, unsigned max_cap, unsigned init_cap) : Facility(name)
  {{{
    this->store_type = type;
    this->max_capacity = max_cap;
    this->act_capacity = init_cap;
  }}}

#if 0
  storehouse(const char *name, Queue *q, enum chocolate_type type, unsigned max_cap, unsigned init_cap) : Facility(name, q)
  {{{
    this->store_type = type;
    this->max_capacity = max_cap;
    this->act_capacity = init_cap;
  }}}
#endif

  int withdraw(unsigned amount)
  {{{
    if (amount > this->max_capacity) {
      std::cerr << "SIMULATION ERROR: Order is not allowed to withdraw bigger from storehouse" << std::endl;
      std::cerr << "                  than is current maximum capacity!" << std::endl;
      std::cerr << "                  Please, FIX your simulation PARAMETERS." << std::endl;

      exit(EXIT_FAILURE);
    }
    else if (amount > this->act_capacity) {
      return EXIT_FAILURE;            /* This amount can't be currently withdraw. */
    }

    this->act_capacity -= amount;
  
    double percentage = static_cast<double>(this->act_capacity) / static_cast<double>(this->max_capacity) * 100;

    if (percentage < store_occupancy[this->store_type][MIN_OCCUPANCY]) {
    }

    if (percentage < store_occupancy[this->store_type][ADEQUATE_OCCUPANCY]) {
    }

    // TODO:
  }}}
};


/* 
 *Global instances of chocolate stores. 
 */
storehouse white_store("White chocolate store", WHITE, 750, 0);
storehouse milk_store(" Milk chocolate store", MILK, 2000, 0);
storehouse dark_store(" Dark chocolate store", DARK, 1500, 0);


/*
 * Global instances of other facilities, used during new batch process.
 */
Facility cleaning("Cleaning of chocolate beans");
Facility roasting("Roasting of chocolate beans");
Facility beans_grinding("Grinding of cocoa nibs or chocolate paste");
Facility refining("Refining of cocoa brash/chocolate paste");
Facility defatting("Defatting of cocoa liquor");
Facility cake_grinding("Grinding of cocoa press cake");
Facility remixing("Chocolate paste remixing");
Facility conching("Chocolate paste conching");
Facility tempering("Chocolate tempering");
Facility molding("Chocolate molding into blocks");
Facility packing("Chocolate blocks packing");


Facility shell_removing("Removing cocoa beans' shells");

/* *********************************************************************************************************************************************************** *
 ~ ~~~[ PROCESSES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

/**
 * Simulation process for new order in the system.
 */
class order : public Process {
  private:
    unsigned order_size;
    enum chocolate_type order_type;
  
  public:
    /*
     * Constructor.
     */
    order(enum chocolate_type type) : Process()
    {{{
      this->order_type = type;

      /* Size from 1 to 100 inclusive. (static_cast rounds downward) */
      this->order_size = static_cast<unsigned>(Uniform(1,101));
    }}}

    void Behavior(void)
    {{{

    }}}
};


/**
 * Simulation process for new chocolate batch.
 */
class batch : public Process {
  private:
    unsigned quantity;
    enum chocolate_type batch_type;

  public:
    void Behavior(void)
    {{{

    }}}
};


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ EVENTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

/**
 * New orders generator for the chocolate factory system.
 */
class generator : public Event {
  void Behavior(void)
  {{{
    double roll = Uniform(0,100);

    if (roll <= NEW_ORDER_WHITE_CHANCE) {
      (new order(WHITE))->Activate();
    }
    else if (roll <= NEW_ORDER_MILK_CHANCE) {
      (new order(MILK))->Activate();
    }
    else {
      (new order(DARK))->Activate();
    }

    this->Activate(Time + Exponential(90));
  }}}
};


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ AUXILIARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

void display_help(const char *prg_name)
{{{
  std::cout << prg_name << " - implementation of stochastic simulation of hypothetical chocolate" << std::endl;
  std::cout << "factory queuing system. This is the result of team project of IMS course in" << std::endl;
  std::cout << "year 2013 @ Faculty of Information Technology, Brno University of Technology," << std::endl;
  std::cout << "Czech Republic.\n" << std::endl;
  std::cout << "Authors:\tDaniela Srubarova (aka Aileen) [team-leader]" << std::endl;
  std::cout << "\t\tDavid Kaspar (aka Dee'Kej)\n" << std::endl;
  std::cout << "Contact:\txsruba01@stud.fit.vutbr.cz" << std::endl;
  std::cout << "\t\txkaspa34@stud.fit.vutbr.cz\n" << std::endl;
  std::cout << "This program is based upon SimLib/C++ (version 3) simulation library." << std::endl;
  std::cout << "If you want to start the simulation and see the results, run this program" << std::endl;
  std::cout << "without any parameters.\n" << std::endl;
  std::cout << "For more info visit: http://perchta.fit.vutbr.cz:8000/vyuka-ims/31" << std::endl;

  return;  
}}}


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ MAIN FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

int main(int argc, char* argv[])
{{{
  
  /* Any parameter used? */
  if (argc > 1) {
    display_help(argv[0]);

    if ((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
      return EXIT_SUCCESS;  
    }
    
    return EXIT_FAILURE;
  }

  // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

  long seed_value;
  std::ifstream seed;
  
  seed.open("/dev/urandom", std::ifstream::binary);

  seed.read(reinterpret_cast<char *>(&seed_value), sizeof(long));
  RandomSeed(seed_value);

  // // // // // // // // // // // // // // // // // // // // // // /

  seed.close();

  return EXIT_SUCCESS;
}}}


/* *********************************************************************************************************************************************************** *
 * ***[ EMD OF CHOCO_FACT_SIM.CC ]**************************************************************************************************************************** *
 * *********************************************************************************************************************************************************** */

