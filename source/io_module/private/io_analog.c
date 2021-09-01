
#include "io_module.h"

// This will be something similar to io_digital.c.
// Left as an exercise to the student.


//---------------- Private Declarations ------------------//


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
int io_RegAnaInputCallback(ana_input_t which, io_AnaInputCallback_t fp)
{
    (void)which;
    (void)fp;

    return RS_PASS;
}

//--------------------------------------------------------//
int io_SetAnaOutput(ana_output_t which, uint16_t value)
{
    (void)which;
    (void)value;

    return RS_PASS;
}

//--------------------------------------------------------//
int io_GetAnaInput(ana_input_t which, uint16_t* value)
{
    (void)which;
    (void)value;

    return RS_PASS;
}


//---------------- Private Implementation ----------------//

