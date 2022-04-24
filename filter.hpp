
#ifndef EXP_FILTER_HPP_
#define EXP_FILTER_HPP_

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

namespace infineon
{

    class ExponentialFilter
    {
        public:

            ExponentialFilter();
            ExponentialFilter(float y);
            ExponentialFilter(float y, uint16_t t);

            void setFilter(float y, uint16_t t);
            void setTau(uint16_t t);
            void setToNewValue(float y);
            void input(float x);
            float output();
            uint16_t pow2(uint16_t p);

        private:

            uint16_t tau;   /**< Time constant >**/

            float y;        /**< Output value >**/
            float y_last;   /**< Last output value >**/
            float x;        /**< Input value>**/
    };

} /**< end namespace infineon >**/

#endif /**< FILTER_HPP_ >**/
