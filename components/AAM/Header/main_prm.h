#ifndef MAIN_PRM_H_
#define MAIN_PRM_H_
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "Hal.h"
#include "Appl.h"

//-------------------------------------- Defines ----------------------------------------------------------------

#define INITIALIZE_TASKS()\
{\
    Hal_Initialize();\
    Appl_Initialize();\
}

#define ALL_SLOTS_TASKS()\
{\
    Appl_Handler();\
}

#define SLOT_1_TASKS()\
{\
}

#define SLOT_2_TASKS()\
{\
}

#endif /* MAIN_PRM_H_ */