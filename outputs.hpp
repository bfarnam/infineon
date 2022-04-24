#include <stdint.h>
#include "type_defs.hpp"

// type alias for older c++ to be removed in IDE
//using uint16_t = unsigned short;
//using uint8_t = int;

namespace infineon
{
    struct OutputConfig_t
    {
            uint8_t     in[2];       /**< channel 0 input pin, address */
            uint8_t     den[2];      /**< diagnosis enable pin, address */
            uint8_t     dsel[3];     /**< diagnosis select pin, address */
            uint8_t     is[2];       /**< diagnosis current pin, address */
            BTxChip_t   *chipType;
    };

    extern struct OutputConfig_t OUT10;
    extern struct OutputConfig_t OUT11;
    extern struct OutputConfig_t OUT20;
    extern struct OutputConfig_t OUT21;
    extern struct OutputConfig_t OUT30;
    extern struct OutputConfig_t OUT31;

} /**< end namespace infineon */
