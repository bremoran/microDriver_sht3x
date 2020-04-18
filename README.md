# A SHT3x driver for micro:bit Makecode

A micro:bit driver for Sensirion SHT3x temperature and humidity sensors.
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

## Blocks preview

This image shows the blocks code from the last commit in master.
This image may take a few minutes to refresh.

![A rendered view of the blocks](https://github.com/bremoran/raw/master/.github/makecode/blocks.png)

#### Metadata (used for search, rendering)

* for PXT/
<script src="https://makecode.com/gh-pages-embed.js"></script><script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
