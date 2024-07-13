//#include <stdio.h>
#include "..\components\AAM\Header\main_prm.h"

void app_main(void)
{
    INITIALIZE_TASKS();

    //Loop Eterno
    for(;;)
    {
        ALL_SLOTS_TASKS();
    }
}
