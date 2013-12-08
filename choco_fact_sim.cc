/**
 * File:          choco_fact_sim.cc
 * Version:       0.0.0.0
 * Start date:    06-12-2013
 * Last update:   08-12-2013
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
//{{{  -  Folding marker

/**
 * Enumeration types used for addressing array values below.
 */

enum chocolate_type {
  WHITE = 0,
  MILK,
  DARK,
};


enum order_chances_type {
  TAKING_REST = 0,
  TRYING_COMPETITION,
  TRYING_COMPETITION2,
};


enum store_occupancy_type {
  MIN_OCCUPANCY = 0,
  ADEQUATE_OCCUPANCY,
};


enum machine_type {
  CLEANING = 0,
  ROASTING,
  SHELLING,
  GRINDING,
  REFINING,
  DEFATTING,
  CAKE_GRINDING,
  REMIXING,
  CONCHING,
  TEMPERING,
  MOLDING,
};

enum gauss_params {
  MEAN_VAL,
  DISPER,
};


/**
 * Percentage values used for determining the decisions made by the customer (= new order).
 */
double order_chances[][4] = {
  {31, 48, 27},
  {28, 54, 33},
  {30, 51, 29},
};


/**
 * Percentages which control if there will be any new batch created because of store
 * running below this values.
 */
double store_occupancy[][2] = {
  {20, 70},
  {25, 80},
  {20, 30},
};


/**
 * Maintenance times (in minutes) for each batch facility used in batch
 * process. 1st value is equal to mean value, 2nd value is equal to
 * dispersion value - both used for normal (Gauss) distribution.
 */
double maintenance_times[][2] = {
  {15, 5},      /* Cleaning. */
  {45, 10},     /* Roasting. */
  {20, 5},      /* Shelling. */
  {10, 5},      /* Grinding. */
  {30, 10},     /* Refining. */
  {30, 10},     /* Defatting. */
  {15, 5},      /* Cake grinding. */
  {20, 5},      /* Remixing. */
  {90, 10},     /* Conching. */
  {60, 10},     /* Tempering. */
  {30, 5},      /* Molding. */
};


static const double NEW_ORDER_WHITE_CHANCE = 13;
static const double NEW_ORDER_MILK_CHANCE = NEW_ORDER_WHITE_CHANCE + 49;

// }}}  -  End of folding marker.


/* *********************************************************************************************************************************************************** *
 ~ ~~~[ PROCESSES & FACILITIES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~
 * *********************************************************************************************************************************************************** */

class storehouse : public Facility {
  private:
    unsigned max_capacity;                      /* Maximum capacity of this store. */
    unsigned act_capacity;                      /* Actual capacity of this store */
    enum chocolate_type store_type;             /* Type of chocolate stored here. */

  public:
    /**
     * Storehouse constructor.
     */
    storehouse(const char *name, enum chocolate_type type, unsigned max_cap, unsigned init_cap) : Facility(name)
    {{{
      this->store_type = type;
      this->max_capacity = max_cap;
      this->act_capacity = init_cap;
    }}}

    /**
     * Only way how to access private member of this class and increase actual capacity.
     */
    void deposit(unsigned amount)
    {{{
      this->act_capacity += amount;

      return;
    }}}

    /**
     * Only way how to withdraw given amount of chocolate from storehouse.
     * Method returns EXIT_FAILURE if the given amount is not in the storehouse
     * right now. Upon successful withdraw method returns EXIT_SUCCESS. It also
     * creates new chocolate batches if the actual capacity drops under
     * predefined values after the withdrawal.
     */
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

      return EXIT_SUCCESS;
    }}}
};

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

/* 
 * Global instances of chocolate stores. 
 */
storehouse white_store("White chocolate store", WHITE, 750, 0);
storehouse milk_store(" Milk chocolate store", MILK, 2000, 0);
storehouse dark_store(" Dark chocolate store", DARK, 1500, 0);

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

class machine;          /* To solve cross-references of machine & machine_maintenance classes. */

/**
 * Process class for simulation of maintenance of facility which will be 
 * released.
 */
class machine_maintenance : public Process {
  private:
     machine *p_machine;

  public:
    machine_maintenance(machine *p_machine, Priority_t priority) : Process(priority)
    {{{
      this->p_machine = p_machine;

      return;
    }}}
  
    void Behavior(void);
};

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

class machine : public Facility {
  private:
    unsigned use_counter;                     /* Especially used by shelling machine. */
    unsigned char maintenance_priority;       /* Maintenance process priority. */

  public:
    enum machine_type type;

    
    /**
     * Machine constructors. 1st is to avoid errors during compilation.
     */
    machine(void) {};

    machine(const char* name, enum machine_type type, unsigned char priority) : Facility(name)
    {{{
      this->type = type;
      this->maintenance_priority = priority;

      this->use_counter = 0;

      return;
    }}}

    
    /**
     * Method for wrapping simulation of maintenance done on current facility.
     * This method should be called before releasing this facility by standard
     * process, so we are sure that because of increased process priority it 
     * will be first to run after the following release.
     */
    void maintenance(void)
    {{{
     (new machine_maintenance(this, this->maintenance_priority))->Activate();

      return;
    }}}
};


/**
 * Definition of purely virtual method of machine_maintenance process. Because
 * of cross-reference dependencies between classes this has to be after the
 * definition of machine class.
 */
void machine_maintenance::Behavior(void)
{{{
  Seize(*p_machine);
  Wait(Normal(maintenance_times[p_machine->type][MEAN_VAL], maintenance_times[p_machine->type][DISPER]));
  Release(*p_machine);

  return;
}}}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

/*
 * Global instances of other facilities, used during new batch process.
 */
machine cleaning("Cleaning of chocolate beans", CLEANING, 1);
machine roasting("Roasting of chocolate beans", ROASTING, 1);
machine shell_removing("Removing cocoa beans' shells", SHELLING, 1);
machine beans_grinding("Grinding of cocoa nibs or chocolate paste", GRINDING, 2);
machine refining("Refining of cocoa brash/chocolate paste", REFINING, 2);
machine defatting("Defatting of cocoa liquor", DEFATTING, 1);
machine cake_grinding("Grinding of cocoa press cake", CAKE_GRINDING, 1);
machine remixing("Chocolate paste remixing", REMIXING, 1);
machine conching("Chocolate paste conching", CONCHING, 1);
machine tempering("Chocolate tempering", TEMPERING, 1);
machine molding("Chocolate molding into blocks", MOLDING, 1);

/* Packing does not have maintenance, therefore simple Facility is sufficient. */
Facility packing("Chocolate blocks packing");


// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

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
    // TODO: FINISH THIS!
    }}}
};

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

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

