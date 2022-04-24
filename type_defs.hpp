
#ifndef TYPE_DEFS_HPP_
#define TYPE_DEFS_HPP_

#include <stdint.h>

// type alias for older c++ to be removed in IDE
//using uint16_t = unsigned short;
//using uint8_t = int;

namespace infineon
{
    enum BTxFamily_t
    {
        BTS700X,                         /**< PROFET+2 12V family */
        BTS5001X,                        /**< Power PROFET family */
        BTT60X0                          /**< PROFET+ 24V family */
    };

    struct BTxChip_t
    {
            BTxFamily_t     family;      /**< PROFET Family of the chosen High side switch */
            const int        kilis;       /**< Current sense ratio */
            float           iisFault;    /**< Current in case of fault event */
            float           iisOl;       /**< Current in case of an open load */
            float           iisEn;       /**< Leakage current when channel is enabled */
            float           iisO;        /**< Sense offset */
            uint8_t         nChannels;   /**< Number of channels in package */
            const int        rSense;      /**< Diagnosis current sense resistor */
    };

    extern BTxChip_t BTS7002;
    extern BTxChip_t BTS7004;
    extern BTxChip_t BTS7006;
    extern BTxChip_t BTS7008;

    extern BTxChip_t BTT60101ERB;
    extern BTxChip_t BTT60101ERA;
    extern BTxChip_t BTT60201ERA;
    extern BTxChip_t BTT60301ERA;
    extern BTxChip_t BTT60302ERB;
    extern BTxChip_t BTT60302ERA;
    extern BTxChip_t BTT60501ERA;
    extern BTxChip_t BTT60502ERA;
    extern BTxChip_t BTT60702ERV;

    extern BTxChip_t BTS50010;
    extern BTxChip_t BTS50015;

    enum Error_t
    {
        OK                      =  0,    /**< No error */
        INTF_ERROR              = -1,    /**< Interface error */
        CONF_ERROR              = -2,    /**< Configuration error */
        READ_ERROR              = -3,    /**< Read error */
        WRITE_ERROR             = -4,    /**< Write error */
        NULLPTR_ERROR           = -5,    /**< Null pointer error */
        INVALID_CH_ERROR        = -6,    /**< Invalid channel error */
        UNSUPPORTED_OP_ERROR    = -7,    /**< Invalid channel error */
        INIT_ERROR              = -8     /**< Not initialized */
    };

    enum Channel_t
    {
        CHANNEL0                = 0,     /**< Channel 1 : Valid for BTT shields */
        CHANNEL1                = 1,     /**< Channel 2 : Valid for BTT shields */
        ALL_CHANNELS            = 2,     /**< Select all channels : Valid for BTT shields */
        NO_CHANNEL              = 3      /**< No channel to select */
    };

    enum Status_t
    {
        UNINITED                = 0,     /**< Not initialized */
        INITED                  = 1,     /**< Initialized */
        POWER_ON                = 2,     /**< Power on */
        POWER_OFF               = 3      /**< Power off */
    };

    enum DiagEnable_t
    {
        DIAG_EN                 = 0,     /**< Enabled */
        DIAG_DIS                = 1      /**< Disabled */
    };

    enum DiagStatus_t
    {
        DIAG_READ_ERROR         = -1,    /**< Read Error */
        NOT_ENABLED             = -2,    /**< Diagnosis not enabled */
        NORMAL                  = 0,     /**< Switch works correctly */
        FAULT                   = 1,     /**< Switch is in a Fault Condition (Is_fault at IS pin), which can mean "Short to GND", "Over Temperature" or "Overload" */
        FAULT_OL_IC             = 2,     /**< Switch is is either in Open Load (while channel enabled) or inverse current is flowing */
        SHORT_TO_GND_OR_OT      = 3,     /**< Short to Ground or Over Temperature Detected*/
        SHORT_TO_VSS            = 5,     /**< Short to Supply Voltage Detected */
        OPEN_LOAD               = 6      /**< Open Load Detected */
    };

} /**< end namespace infineon */

#define BTX_ASSERT_RET(x)       if( x != OK ) { return x; }

#define BTX_ASSERT_NULLPTR(x)   if( x == nullptr ) { return NULLPTR_ERROR; }

#endif /**< TYPE_DEFS_HPP_ */
