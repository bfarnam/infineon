
#include <Arduino.h> // for pin functions while testing
#include "outputs.hpp"

namespace infineon
{
    OutputConfig_t OUT10 = {
            .in          = {3,0x27},
            .den         = {0,0x27},
            .dsel        = {2,0x99,LOW},
            .is          = {A0,0x99},
            .chipType    = &BTT60302ERA
    };

    OutputConfig_t OUT11 = {
            .in          = {4,0x27},
            .den         = {0,0x27},
            .dsel        = {2,0x99,HIGH},
            .is          = {A0,0x99},
            .chipType    = &BTT60302ERA
    };

    OutputConfig_t OUT20 = {
            .in          = {5,0x27},
            .den         = {1,0x27},
            .dsel        = {3,0x99,LOW},
            .is          = {A1,0x99},
            .chipType    = &BTT60302ERA
    };

    OutputConfig_t OUT21 = {
            .in          = {6,0x27},
            .den         = {1,0x27},
            .dsel        = {3,0x99,HIGH},
            .is          = {A1,0x99},
            .chipType    = &BTT60302ERA
    };

    OutputConfig_t OUT30 = {
            .in          = {7,0x27},
            .den         = {2,0x27},
            .dsel        = {99,0,0},
            .is          = {A2,0x99},
            .chipType    = &BTT60201ERA
    };

    OutputConfig_t OUT31 = {
            .in          = {99,0},
            .den         = {99,0},
            .dsel        = {99,0,0},
            .is          = {99,0},
            .chipType    = &BTT60201ERA
    };

} /**< end namespace infineon >**/
