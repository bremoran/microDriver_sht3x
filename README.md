# A SHT3x driver for micro:bit Makecode

A micro:bit driver for Sensirion (SHT3x)[https://www.sensirion.com/en/environmental-sensors/humidity-sensors/digital-humidity-sensors-for-various-applications/] temperature and humidity sensors.

SHT3x sensor boards are available from a variety of manufacturers, such as
[Adafruit](https://www.adafruit.com/product/2857) and (SeeedStudio)[https://www.seeedstudio.com/Grove-I2C-High-Accuracy-Temp-Humi-Sensor-SHT35.html].


This driver is primarily intended as a makecode package for use in the
[Makecode micro:bit editor](makecode.microbit.org). Recognising that the
Makecode interpreter has floating point support, this driver is divided
into two parts: the C++ driver returns raw values and the typescript
shim converts the raw values to floating point to ensure no loss
of precision. This means that some processing is necessary for use
in C++ projects.

This driver uses I2C to read a SHT3x sensor. It uses clock
stretching to wait until the SHT3x finishes a read. The SHT3x is
instructed to use a one-shot high precision measurement. A CRC is
calculated for each measurement.

The temperature and humidity data is stored in the internal raw
variables. It can be queried with `humidity()` and `temperature()`.

The internal status variable is also updated during a read. It can
be queried with `status()`.

## API information

To use this driver, it is important to follow the expected workflow.
Readings are updated when the `update()` call is made. This can fail.
The status of the last update can be checked with the `status()` call.
Once a successful update has occurred, the measurements can be
queried with `temperature()` and `humidity()`.

The normal pattern to use this driver is shown in the example below:

```ts
basic.forever(() => {
    // Update the sensor reading
    sht3xDriver.update(sht3xDriver.sht3xAddr.sht3xAddrA0);
    // Check if the reading was successful
    let status = sht3xDriver.status();
    if (status == 0) {
        // If so, use the data
        let rh = sht3xDriver.humidity();
        let tmp = sht3xDriver.temperature();
        serial.writeLine("%RH: " + rh);
        serial.writeLine("TMP: " + tmp);
    }
    else {
        // If not, handle the error
        serial.writeLine("sht3x Error: "+status);
    }
    basic.pause(1000);
})
```

### Update SHT3x readings #sht3xdriver-update

This driver only communicates with the SHT3x when an update is performed. This saves power and
improves speed. However, this means that the readings must be updated before they are used.

This function initiates an I2C reading of a SHT3x sensor. It takes a 
argument of the SHT3x's I2C address. The supported addressses are:

* A0: 0x44
* A1: 0x45

The driver uses clock
stretching to wait until the SHT3x finishes a read. The SHT3x is
instructed to use a one-shot high precision measurement. A CRC is
calculated for each measurement, both temperature and humidity.

The temperature and humidity data is stored in the internal raw
variables. It can be queried with SHT3xHumidity and SHT3xTemperature.

The internal status variable is also updated by this function. It can
be queried with SHT3xStatus.

status is set to:

* 0 for success
* 1 for failure on i2c write
* 2 for failure on i2c read
* 3 if temperature checksum is invalid
* 4 if humidity checksum is invalid

### Check the status of the last SHT3x update #sht3xdriver-status

This function returns the status of the last update

status is set to:

* 0 for success
* 1 for failure on i2c write
* 2 for failure on i2c read
* 3 if temperature checksum is invalid
* 4 if humidity checksum is invalid

### Return the temperature reading of the last SHT3x update #sht3xdriver-temperature

Report Temperature in degrees celcius from the SHT3x sensor. Returns the last valid
temperature reading in degrees celcius between -45 and 130.

### Return the temperature reading of the last SHT3x update #sht3xdriver-humidity

Report relative humidity in percentage from the SHT3x sensor. Returns the last valid
humidity reading in relative humidity % between 0% and 100%s.

## Use this extension

This repository can be added as an **extension** in MakeCode.

* open [Makecode micro:bit editor](makecode.microbit.org)
* click on **New Project**
* click on **Extensions** under the gearwheel menu
* search for **https://github.com/bremoran/microDriver_sht3x** and import

## Edit this extension ![Build status badge](https://github.com//workflows/MakeCode/badge.svg)

To edit this repository in MakeCode.

* open [Makecode micro:bit editor](makecode.microbit.org)
* click on **Import** then click on **Import URL**
* paste **https://github.com/** and click import

## Attributions

Humidity Icon made by [Pixel perfect](https://www.flaticon.com/authors/pixel-perfect) from [www.flaticon.com].

## Blocks preview

This image shows the blocks code from the last commit in master.
This image may take a few minutes to refresh.

![A rendered view of the blocks](https://github.com/bremoran/raw/master/.github/makecode/blocks.png)

#### Metadata (used for search, rendering)

* for PXT/
<script src="https://makecode.com/gh-pages-embed.js"></script><script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
