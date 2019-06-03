
#include "io_module.h"

// #include "fsl_gpio.h"
// #include "fsl_port.h"


// This will be something similar to io_digital.c.
// Left as an exercise to the student.



//---------------- Private --------------------------//


//---------------- Public API Implementation -------------//


//--------------------------------------------------------//
status_t io_regAnaInputCallback(anaInput_t which, fpAnaInputCallback fp)
{
    (void)which;
    (void)fp;

    return STATUS_OK;
}

//--------------------------------------------------------//
status_t io_setAnaOutput(anaOutput_t which, uint16_t value)
{
    (void)which;
    (void)value;

    return STATUS_OK;
}

//--------------------------------------------------------//
status_t io_getAnaInput(anaInput_t which, uint16_t* value)
{
    (void)which;
    (void)value;

    return STATUS_OK;
}


//---------------- Private --------------------------//

