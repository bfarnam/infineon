// verified uint8_t is an unsigned 8bit int 0-255 same as byte on arduino platform

#ifndef INFINEON_HPP_
#define INFINEON_HPP_

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "type_defs.hpp"
#include "filter.hpp"
#include "outputs.hpp"


namespace infineon
{
    class BTx
    {

        public:
            BTx();
            ~BTx();

            Error_t             enableDiag(uint8_t den);
            Error_t             disableDiag(uint8_t den);
            Status_t            getSwitchStatus(uint8_t pin);
            DiagStatus_t        readDiagX(BTxChip_t *btxchip, uint8_t pin, uint8_t den, uint8_t dsel=0);
            float               readIs(BTxChip_t *btxchip, uint8_t pin, uint8_t den, uint8_t dsel=0);

            void                setCurrentOffset(float offset);
            BTxChip_t           *btxChip;                 /**< BTx switch variant >**/
            OutputConfig_t      *output;

            DiagStatus_t         diagStatus;              /**< Diagnosis status >**/
            DiagStatus_t         diagRead(float senseCurrent, BTxChip_t *btxchip);


        protected:

            ExponentialFilter    *currentFilter;          /**< Current filter >**/

            //BTxChip_t            *btxChip;                /**< BTx switch variant >**/
            Status_t             status;                  /**< Switch status >**/

            DiagEnable_t         diagEnb;                 /**< Diagnosis enabled flag >**/
            //DiagStatus_t         diagStatus;              /**< Diagnosis status >**/
            //DiagStatus_t         diagRead(float senseCurrent, BTxChip_t *btxchip);

            Error_t              setDsel(uint8_t dsel=0);

        private:

            float                currentOffset = 0.0;     /**< Diagnosis current offset >**/

    };

} /**< end namespace infineon >**/

#endif /**< INFINEON_HPP_ >**/
