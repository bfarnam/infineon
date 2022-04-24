
#ifndef EXP_FILTER_HPP_
#define EXP_FILTER_HPP_

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

// type alias for older c++ to be removed in IDE
//using uint16_t = unsigned short;
//using uint8_t = int;

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

            uint16_t tau;   /**< Time constant */

            float y;        /**< Output value */
            float y_last;   /**< Last output value */
            float x;        /**< Input value*/
    };

}

#endif /** FILTER_HPP_ **/
