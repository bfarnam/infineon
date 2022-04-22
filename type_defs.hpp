
#ifndef TYPE_DEFS_HPP_
#define TYPE_DEFS_HPP_

// type alias for older c++ to be removed in IDE
using uint16_t = unsigned short;
using uint8_t = int;

namespace infineon
{
	enum BTxFamily_t
	{
		BTS700X,						/**< PROFET+2 12V family */
		BTS5001X,						/**< Power PROFET family */
		BTT60X0							/**< PROFET+ 24V family */
	};

	struct BTxChip_t
	{
		BTxFamily_t     family;			/**< PROFET Family of the chosen High side switch */
		const uint16_t  kilis;			/**< Current sense ratio */
		float           iisFault;		/**< Current in case of fault event */
		float           iisOl;			/**< Current in case of an open load */
		float           iisEn;			/**< Leakage current when channel is enabled */
		float           iisO;			/**< Sense offset */
		const uint8_t	nChannels;		/**< Number of channels in package */
		const uint16_t  rSense;			/**< Diagnosis current sense resistor */
	};

	extern BTxChip_t BTS7002;
	extern BTxChip_t BTS7004;
	extern BTxChip_t BTS7006;
	extern BTxChip_t BTS7008;

	extern BTxChip_t BTT6010_1ERB;
	extern BTxChip_t BTT6010_1ERA;
	extern BTxChip_t BTT6020_1ERA;
	extern BTxChip_t BTT6030_1ERA;
	extern BTxChip_t BTT6030_2ERB;
	extern BTxChip_t BTT6030_2ERA;
	extern BTxChip_t BTT6050_1ERA;
	extern BTxChip_t BTT6050_2ERA;
	extern BTxChip_t BTT6070_2ERV;

	extern BTxChip_t BTS50010;
	extern BTxChip_t BTS50015;

	enum Error_t
	{
		OK						=  0,	/**< No error */
		INTF_ERROR				= -1,	/**< Interface error */
		CONF_ERROR				= -2,	/**< Configuration error */
		READ_ERROR				= -3,	/**< Read error */
		WRITE_ERROR				= -4,	/**< Write error */
		NULLPTR_ERROR			= -5,	/**< Null pointer error */
		INVALID_CH_ERROR		= -6,	/**< Invalid channel error */
		UNSUPPORTED_OP_ERROR	= -7,	/**< Invalid channel error */
		INIT_ERROR				= -8 	/**< Not initialized */
	};

	enum Channel_t
	{
		CHANNEL0				= 0,	/**< Channel 1 : Valid for BTT shields */
		CHANNEL1				= 1,	/**< Channel 2 : Valid for BTT shields */
		ALL_CHANNELS			= 2,	/**< Select all channels : Valid for BTT shields */
		NO_CHANNEL				= 3		/**< No channel to select */
	};

	enum Status_t
	{
		UNINITED				= 0,	/**< Not initialized */
		INITED					= 1,	/**< Initialized */
		POWER_ON				= 2,	/**< Power on */
		POWER_OFF				= 3		/**< Power off */
	};

	enum DiagEnable_t
	{
		DIAG_EN					= 0,	/**< Enabled */
		DIAG_DIS				= 1		/**< Disabled */
	};

	enum DiagStatus_t
	{
		DIAG_READ_ERROR			= -1,	/**< Read Error */
		NOT_ENABLED				= -2,	/**< Diagnosis not enabled */
		NORMAL					= 0,	/**< Switch works correctly */
		FAULT					= 1,	/**< Switch is in a Fault Condition (Is_fault at IS pin), which can mean "Short to GND", "Over Temperature" or "Overload" */
		FAULT_OL_IC				= 2,	/**< Switch is is either in Open Load (while channel enabled) or inverse current is flowing */
		SHORT_TO_GND_OR_OT		= 3,	/**< Short to Ground or Over Temperature Detected*/
		SHORT_TO_VSS			= 5,	/**< Short to Supply Voltage Detected */
		OPEN_LOAD				= 6		/**< Open Load Detected */
	};

	/**
	* BTS7002 Is rated for nominal 21 A and is the PROFET with the highest useable power
	*/
	BTxChip_t BTS7002 = {
		.family					= BTS700X,
		.kilis					= 22700,
		.iisFault				= 0.0044,
		.iisOl					= 0.0018,
		.iisEn					= 0.000002,
		.nChannels				= 1,
		.rSense					= 1000
	};

	/**
	* BTS7002 Is rated for nominal 15 A
	*/
	BTxChip_t BTS7004 = {
		.family					= BTS700X,
		.kilis					= 20000,
		.iisFault				= 0.0044,
		.iisOl					= 0.0018,
		.iisEn					= 0.000002,
		.nChannels				= 1,
		.rSense					= 1000
	};

	/**
	* BTS7006 Is rated for nominal 12.5 A
	*/
	BTxChip_t BTS7006 = {
		.family					= BTS700X,
		.kilis					= 17700,
		.iisFault				= 0.0044,
		.iisOl					= 0.0018,
		.iisEn					= 0.000002,
		.nChannels				= 1,
		.rSense					= 1000
	};

	/**
	* BTS7008 Is rated for nominal 11 A
	*/
	BTxChip_t BTS7008 = {
		.family					= BTS700X,
		.kilis					= 14500,
		.iisFault				= 0.0044,
		.iisOl					= 0.0018,
		.iisEn					= 0.000002,
		.nChannels				= 1,
		.rSense					= 1000
	};

	/**
	* BTS50010-1TAD Is rated for nominal 40 A
	*/

	BTxChip_t BTS50010 = {
		.family					= BTS5001X,
		.kilis					= 52100,
		.iisFault				= 0.0035,
		.iisOl					= 0.0,
		.iisEn					= 0.0,
		.iisO					= 0.000008,
		.nChannels				= 1,
		.rSense					= 1000
	};

	/**
	* BTS50015-1TAD Is rated for nominal 33 A
	*/
	BTxChip_t BTS50015 = {
		.family					= BTS5001X,
		.kilis					= 51500,
		.iisFault				= 0.0035,
		.iisOl					= 0.0,
		.iisEn					= 0.0,
		.iisO					= 0.000005,
		.nChannels				= 1,
		.rSense					= 1000
	};

	/**
	* BTT6010-1ERB Is rated for nominal 9 A
	*/
	BTxChip_t BTT6010_1ERB = {
		.family					= BTT60X0,
		.kilis					= 3900,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.00001,		/** Il(ol) 10-50mA */
		.nChannels				= 1,
		.rSense					= 1200
	};

	/**
	* BTT6010-1ERA Is rated for nominal 9 A with higher max Is
	*/
	BTxChip_t BTT6010_1ERA = {
		.family					= BTT60X0,
		.kilis					= 3900,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.00001,		/** Il(ol) 10-50mA */
		.nChannels				= 1,
		.rSense					= 1200
	};

	/**
	* BTT6020-1ERA Is rated for nominal 7 A
	*/
	BTxChip_t BTT6020_1ERA = {
		.family					= BTT60X0,
		.kilis					= 2950,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.000004,		/** Il(ol) 4-25mA */
		.nChannels				= 1,
		.rSense					= 1200
	};

	/**
	* BTT6030-1ERA Is rated for nominal 6 A
	*/
	BTxChip_t BTT6030_1ERA = {
		.family					= BTT60X0,
		.kilis					= 2200,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.000004,		/** Il(ol) 4-25mA */
		.nChannels				= 1,
		.rSense					= 1200
	};

	/**
	* BTT6030-2ERB Is rated for nominal 6A one channel or 4A both channels
	*/
	BTxChip_t BTT6030_2ERB = {
		.family					= BTT60X0,
		.kilis					= 2240,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.000004,		/** Il(ol) 4-25mA */
		.nChannels				= 2,
		.rSense					= 1200
	};

	/**
	* BTT6030-2ERA Is rated for nominal 6A one channel or 4A both channels with higher max Is
	*/
	BTxChip_t BTT6030_2ERA = {
		.family					= BTT60X0,
		.kilis					= 2240,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.000004,		/** Il(ol) 4-25mA */
		.nChannels				= 2,
		.rSense					= 1200
	};

	/**
	* BTT6050-1ERA Is rated for nominal 4.5A
	*/
	BTxChip_t BTT6050_1ERA = {
		.family					= BTT60X0,
		.kilis					= 1500,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.000004,		/** Il(ol) 4-25mA */
		.nChannels				= 1,
		.rSense					= 1200
	};

	/**
	* BTT6050-2ERA Is rated for nominal 4.5A one channel or 3A both channels
	*/
	BTxChip_t BTT6050_2ERA = {
		.family					= BTT60X0,
		.kilis					= 1460,
		.iisFault				= 0.006,		/** Iis(fault) 6-40mA */
		.iisOl					= 0.000004,		/** Il(ol) 4-25mA */
		.nChannels				= 2,
		.rSense					= 1200
	};

	/**
	* BTT6070-2ERV Is rated for nominal 3A per channel or 2.3A both channels
	*/
	BTxChip_t BTT6070_2ERV = {
		.family					= BTT60X0,
		.kilis					= 1730,
		.iisFault				= 0.006,		/** Iis(fault) 6-30mA */
		.iisOl					= 0.000005,		/** Il(ol) 5-35mA */
		.nChannels				= 2,
		.rSense					= 1200
	};

} /**< end namespace infineon */

#define BTX_ASSERT_RET(x)       if( x != OK ) { return x; }

#define BTX_ASSERT_NULLPTR(x)   if( x == nullptr ) { return NULLPTR_ERROR; }

#endif /**< TYPE_DEFS_HPP_ */
