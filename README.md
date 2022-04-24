# infineon
Custom Infineon PROFET Library for Embedded Applications using the AVR Platform.

The supplied Infineon Libraries for the PROFET swithces, namely the PROFET+ 24V Shield, is a large and cumberson platform of code which is nice for doing raw testing on a supplied Infineon Shield, but is actually horrible if you wish to take your test platform and make something useful out of it.

The original library can be referenced at the GitHub repository [Smart High-Side Switch Arduino Library](https://github.com/Infineon/arduino-high-side-switch)

Additional, depreciated libraries, which were used to create this library can be referenced here:

[Smart High-Side Switch](https://github.com/Infineon/high-side-switch)

[PROFET-2-12V-Arduino-Shield](https://github.com/Infineon/PROFET-2-12V-Arduino-Shield)

[24V_SHIELD_BTT6030](https://github.com/OlafFilies/24V_SHIELD_BTT6030)

Infineon's Documentation can be referenced at [readthedocs.io](https://high-side-switch.readthedocs.io/en/latest/index.html)

## Major Changes
Infineon's library requires almost ALL of the Arduino UNO's pins and thus all the GPIO in an embedded platform, making this useless to most people.

Addtionally, differences between the datasheets and the library documentation vs. the actual code in the library make the implementation very cumbersone.

The official Infineon Hackster page has an entry talking about [direct access](https://www.hackster.io/Infineon_Team/24v-protected-switch-shield-with-btt6030-2era-and-btt6020-1e-64ed44#toc-manually-controlling-the-shield-without-the-use-of-the-library-8) and they state that you have to use a PWM signal.
>To control your output channels you'll have to send a pulse width modulated signal to each individual output channel pin.

**This is incorrect.**

The datasheet for the PROFET+ 24V High-side switch, such as the [BTT6030-2ERA](https://www.infineon.com/dgdl/Infineon-BTT6030-2ERA-DS-v01_00-EN.pdf?fileId=5546d46269e1c019016a21fa44260d82) states that the input is:
>is either OFF or ON but cannot be in a linear or undefined state.  The input circuitry is compatible with PWM applications.

If you finally trace ALL the library functions to the actual call which turns on the output you see that it performs an Arduino digitialWrite which is simply an ON/OFF.

From one of Infineon's example files:
```
    /** Turn on the selected channel */
    Serial.println("\nTurning on selected switch...");
    HSS.switchHxOn(switch_no);
```

This in turn resolves through many layers to _Btt60xxShield::switchesHxOn_ and performs:
```
if(h0_0 == true){
    HSS_ASSERT_NULLPTR(switches[0]);
    err = switches[0]->enable();
    HSS_ASSERT_RET(err);
}
```
The actual call is _enable()_ which can be found hidden inside hss-pal-gpio-ino.cpp:
```
Error_t GPIOIno::enable()
{
    if(this->logic == POSITIVE){
        digitalWrite(this->pin, GPIO_HIGH);
    }
    else if(this->logic == NEGATIVE){
        digitalWrite(this->pin, GPIO_LOW);
    }
    return OK;
}
```
A simple LOW to HIGH transition will activate the selected BTx input.  Additionally, this has been confirmed to work with GPIO expanders such as the TCA9534/PCA9534 which is an open-drain with internal pull-up output and the TCA9538/PCA9538 which is a push-pull (totem pole) style ourput with no internal pull-up.

### Revisions
This is merely the first rough draft (beta) after extracting the needed library functions for my needs.  Some of the private and protected functions were made public since a lot of the original library was tossed.  As I get time to clean and polish this up I will.

The original libraries are comprised of 33 files which take approximately 100KB of space before compile.  After dumping most of the wrappers and getting to the root of the function calls I ended up with 8 files which take approximately 22KB of space.

### Implementation
For simple switch activation, you can ommit the library and just call the pins directly.  However, if you want to accurately read the current sense and used advanced features such as diagnostics, you will need eithier this library or the official libraries.  Most importantly, there is an exponential filter which is utilized to get the calibrated amperage return.

The main method of implemenation is as follows:
```
#include "infineon.hpp"
using namespace infineon;
BTx _myFriendlyName_;
BTx();
```
The PROFETS that you will be utilizing are defined in outputs.cpp to make referencing them easier in your code and the struct is described and defined in outputs.hpp.  Currently this is not a dynamic struct array and the number is limited to no more than SIX outputs from any combination of PROFET devices.  The output names are hard defined in outputs.hpp as:
- OUT10
- OUT11
- OUT20
- OUT21
- OUT30
- OUT31

You will need to change the output definitions in outputs.cpp in order to utilize the advanced functions.  The struct is as follows:
```
OutputConfig_t OUT10 = {
        .in          = {3,0x27},
        .den         = {0,0x27},
        .dsel        = {2,0x99,LOW},
        .is          = {A0,0x99},
        .chipType    = &BTT60302ERA
};
```
Above the output OUT10 is configured for a 2 channel device but only defines the first channel.
- **.in** is the High Side Switch (HSS) input channel GPIO target pin and the HEX address of the device used to access the HSS.  A HEX value of 0x99 assumes that the GPIO is handled natively.
- **.den** is the HSS Diagnostic ENable (DEN) input.  A HEX value of 0x99 assumes that the GPIO is handled natively.
- **.dsel** is the HSS Diagnostic SELection (DSEL) input and valid for 2 channel devices.  This is active LOW for the first channel and active HIGH for the second channel.  Since we are not creating an array that keeps track of this (takes too much memory) we pass to the handler the output value to select the channel described.  A HEX value of 0x99 assumes that the GPIO is handled natively.
- **.is** is the sense current output from the HSS.  This must pass to an analog input.  A HEX value of 0x99 assumes that the GPIO is handled natively.
- **.chipType** is the referenced struct for the actual HSS device.  These are defined in type_defs.cpp and have all of the information required for the current sense to work correctly.

In order to define the second channel you would define OUT11 as follows:
```
OutputConfig_t OUT11 = {
        .in          = {4,0x27},
        .den         = {0,0x27},
        .dsel        = {2,0x99,HIGH},
        .is          = {A0,0x99},
        .chipType    = &BTT60302ERA
};
```
The method of implementation allows for your local code (or sub code) to perform the basic IO and uses the library for the advanced functions.

You will need a minimum of one local wrapper (function) in you main code or through a linked C++ file.  The local function takes the output name and utilizes the stuct (described above) to pass the required inputs to the main libraries.
```
float readCurrent(OutputConfig_t &output)
{
    float readAmps = 0.0;
    for (int i = 0; i < 10; i++) {                    // Measure more than once to make use of the internal exponential filter
            diag_enable(&output, HIGH);
            diag_select(&output);
            //Serial.println(output.chipType->rSense);
            readAmps = _myFriendlyName_.readIs(output.chipType, output.is[0], output.den[0], 0);     // dsel = 0 requires manual activation of den and dsel
            diag_enable(&output, LOW);
    }
    return readAmps;
}
```
When calling this from you main code you would utilize:
```
nowAmps[2] = readCurrent(OUT20);
```
nowAmps[] is my local array name and index location and OUT20 is the defined output from outputs.cpp.  You can pass the return to any variable of type float.

In the above example I utilize 2 local fucntions to enable/disable the DEN and DSEL becuase I am running this through an i2c bus.

diag_enable:
```
void diag_enable(OutputConfig_t *output, bool bOut)
{
    //Serial.println(String(output->den[1], HEX));
    if (output->den[1] == 0x99) {
            if (output->den[0] != 99) {digitalWrite(output->den[0], bOut);}
    } else {
            if (output->den[0] != 99) { i2c.digitalWrite(output->den[0], bOut, output->den[1]);}
    }
    //msg = "DEN to 0x"+String(output->den[1], HEX)+":"+String(output->den[0],HEX)+" value "+String(bOut)+"\t@:"+String(millis());
    //Serial.println(msg);
}
```

diag_select:
```
void diag_select(OutputConfig_t *output)
{
    //Serial.println(String(output->dsel[1], HEX));
    bool bOut = HIGH;
    if (output->dsel[2]==0) { bOut = LOW; }
    //Serial.println(bOut);
    if (output->dsel[1] == 0x99) {
            if (output->dsel[0] != 99) { digitalWrite(output->dsel[0], bOut); }
    } else {
            if (output->dsel[0] != 99) { i2c.digitalWrite(output->dsel[0], bOut, output->dsel[1]);}
    }
    //msg = "DSEL to 0x"+String(output->dsel[1], HEX)+":"+String(output->dsel[0],HEX)+" value "+String(bOut)+"\t@:"+String(millis());
    //Serial.println(msg);
}
```
_myFriendlyName_.readIs which is found in infineon.cpp will not attempt to enable DEN and DSEL if DSEL=0 hence the reason I have the local functions above.

### Calibrated Current Sense
The official Infineon library uses an exponential filter, the current sense ratio (kilis), and rSense values to display accurate amperage values.  The exponential filter is substantiated when the first call to BTx(); is made.   

Kilis values are unique to each HSS type, are listed on the datasheets, and are stored inside a struct and defined in type_defs.cpp.  

Rsense is a bit more confusing.  The output sense value supplied via the IS pin needs to be tied to ground in order to work properly.  On the shield documentation, schematic, and the provided library, this is referred to as Rsense.  However, in the datasheets, this is actually called Ris.  In both events, this is the value in Ohms of whatever resistor you have chosen to tie the IS pin to ground.  On the 24V shield this value is 1200 which is what is recommended on the datasheet.  This may differ if you custom implement this device.

I have added all of the BTT60xx models and populated the kilis from the datasheets.  I have also added some other struct members so the default types file (hss-types.cpp) from the official libraries is not compatible with this version.

### Diagnostics
Work in Progress



<!-- 
# Smart High-Side Switch Arduino Library

Arduino library for Infineon's Arduino shields for **PROFET™ Smart High-Side Power Switches** Automotive grade

## Supported Products

<table>
    <tr>
        <td><img src="images/BTT6020-1EKA.jpg?raw=true" width="300"></td>
        <td><img src="images/BTS50015-1TAD.jpg?raw=true" width="300"></td>
        <td><img src="images/Profet+2.png?raw=true" width="300"></td>
    </tr>
    <tr>
        <td style="test-align : center"><a href="https://high-side-switch.readthedocs.io/en/latest/hw-platforms.html#profettrade-24v-family">PROFET™+ 24V BTT60xx Arduino Shield</a></td>
        <td style="test-align : center"><a href="https://high-side-switch.readthedocs.io/en/latest/hw-platforms.html#power-profettrade-family">Power PROFET™ BTS5001x-1TAD Arduino Shield</a></td>
        <td style="test-align : center"><a href="https://high-side-switch.readthedocs.io/en/latest/hw-platforms.html#profettrade-2-12v-family">PROFET™+2 12V BTS700x-1EPP Arduino Shield</a></td>
    </tr>
</table>

## Supported Frameworks

The library should be supported by any Arduino platform based on the reference Arduino cores. 

Check in this [link](https://high-side-switch.readthedocs.io/en/latest/sw-frmwk/arduino/arduino-compatible-kits.html) the already verified (at least successfully built) platforms.

## More information

The complete documentation of the library as well as detailed information about the PROFET-shield, can be found in the [Wiki](https://high-side-switch.readthedocs.io/en/latest/index.html).


### Getting Started

Find a getting started tutorial using the XMC1100 Boot Kit [here](https://high-side-switch.readthedocs.io/en/latest/sw-frmwk/arduino/arduino-getting-started.html).

### More information

The complete relevant Arduino documentation (and more) can be found in the base XFP library [Wiki](https://high-side-switch.readthedocs.io/en/latest/index.html):

* <a href="https://high-side-switch.readthedocs.io/en/latest/sw-frmwk/arduino/arduino-lib-installation.html"> Arduino Lib Installation</a><br> 
* <a href="https://high-side-switch.readthedocs.io/en/latest/sw-frmwk/arduino/arduino-examples.html"> Examples</a><br>
* <a href="https://high-side-switch.readthedocs.io/en/latest/sw-frmwk/arduino/arduino-api.html">Arduino API</a><br>
* <a href="https://high-side-switch.readthedocs.io/en/latest/sw-frmwk/arduino/arduino-platformio.html">PlatformIO</a><br>

### Contributing

This is a release repository for the Arduino framework. The code base is maintained and developed in the High-side Switch Cross-Framework-Platform (XFP) library [repository](https://github.com/infineon/high-side-switch). 

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

-->
