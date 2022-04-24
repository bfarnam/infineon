
#include "type_defs.hpp"

namespace infineon
{
    /**
     * BTS7002 Is rated for nominal 21 A and is the PROFET with the highest useable power
     */
    BTxChip_t BTS7002 = {
            .family         = BTS700X,
            .kilis          = 22700,
            .iisFault       = 0.0044,
            .iisOl          = 0.0018,
            .iisEn          = 0.000002,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1000
    };

    /**
     * BTS7002 Is rated for nominal 15 A
     */
    BTxChip_t BTS7004 = {
            .family         = BTS700X,
            .kilis          = 20000,
            .iisFault       = 0.0044,
            .iisOl          = 0.0018,
            .iisEn          = 0.000002,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1000
    };

    /**
     * BTS7006 Is rated for nominal 12.5 A
     */
    BTxChip_t BTS7006 = {
            .family         = BTS700X,
            .kilis          = 17700,
            .iisFault       = 0.0044,
            .iisOl          = 0.0018,
            .iisEn          = 0.000002,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1000
    };

    /**
     * BTS7008 Is rated for nominal 11 A
     */
    BTxChip_t BTS7008 = {
            .family         = BTS700X,
            .kilis          = 14500,
            .iisFault       = 0.0044,
            .iisOl          = 0.0018,
            .iisEn          = 0.000002,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1000
    };

    /**
     * BTS50010-1TAD Is rated for nominal 40 A
     */

    BTxChip_t BTS50010 = {
            .family         = BTS5001X,
            .kilis          = 52100,
            .iisFault       = 0.0035,
            .iisOl          = 0.0,
            .iisEn          = 0.0,
            .iisO           = 0.000008,
            .nChannels      = 1,
            .rSense         = 1000
    };

    /**
     * BTS50015-1TAD Is rated for nominal 33 A
     */
    BTxChip_t BTS50015 = {
            .family         = BTS5001X,
            .kilis          = 51500,
            .iisFault       = 0.0035,
            .iisOl          = 0.0,
            .iisEn          = 0.0,
            .iisO           = 0.000005,
            .nChannels      = 1,
            .rSense         = 1000
    };

    /**
     * BTT6010-1ERB Is rated for nominal 9 A
     */
    BTxChip_t BTT60101ERB = {
            .family         = BTT60X0,
            .kilis          = 3900,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.00001,      /** Il(ol) 10-50mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1200
    };

    /**
     * BTT6010-1ERA Is rated for nominal 9 A with higher max Is
     */
    BTxChip_t BTT60101ERA = {
            .family         = BTT60X0,
            .kilis          = 3900,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.00001,      /** Il(ol) 10-50mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1200
    };

    /**
     * BTT6020-1ERA Is rated for nominal 7 A
     */
    BTxChip_t BTT60201ERA = {
            .family         = BTT60X0,
            .kilis          = 2950,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.000004,     /** Il(ol) 4-25mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1200
    };

    /**
     * BTT6030-1ERA Is rated for nominal 6 A
     */
    BTxChip_t BTT60301ERA = {
            .family         = BTT60X0,
            .kilis          = 2200,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.000004,     /** Il(ol) 4-25mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1200
    };

    /**
     * BTT6030-2ERB Is rated for nominal 6A one channel or 4A both channels
     */
    BTxChip_t BTT60302ERB = {
            .family         = BTT60X0,
            .kilis          = 2240,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.000004,     /** Il(ol) 4-25mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 2,
            .rSense         = 1200
    };

    /**
     * BTT6030-2ERA Is rated for nominal 6A one channel or 4A both channels with higher max Is
     */
    BTxChip_t BTT60302ERA = {
            .family         = BTT60X0,
            .kilis          = 2240,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.000004,     /** Il(ol) 4-25mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 2,
            .rSense         = 1200
    };

    /**
     * BTT6050-1ERA Is rated for nominal 4.5A
     */
    BTxChip_t BTT60501ERA = {
            .family         = BTT60X0,
            .kilis          = 1500,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.000004,     /** Il(ol) 4-25mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 1,
            .rSense         = 1200
    };

    /**
     * BTT6050-2ERA Is rated for nominal 4.5A one channel or 3A both channels
     */
    BTxChip_t BTT60502ERA = {
            .family         = BTT60X0,
            .kilis          = 1460,
            .iisFault       = 0.006,        /** Iis(fault) 6-40mA **/
            .iisOl          = 0.000004,     /** Il(ol) 4-25mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 2,
            .rSense         = 1200
    };

    /**
     * BTT6070-2ERV Is rated for nominal 3A per channel or 2.3A both channels
     */
    BTxChip_t BTT60702ERV = {
            .family         = BTT60X0,
            .kilis          = 1730,
            .iisFault       = 0.006,        /** Iis(fault) 6-30mA **/
            .iisOl          = 0.000005,     /** Il(ol) 5-35mA **/
            .iisEn          = 0.0,
            .iisO           = 0.0,
            .nChannels      = 2,
            .rSense         = 1200
    };

} /**< end namespace infineon >**/
