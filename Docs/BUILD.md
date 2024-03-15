# Setting up to Build Applications


## Setting up Ethernet Drivers
To build ESP32 for commissioning, we have set up some settings to get ethernet enabled and working.   
To begin, first download the [NetworkCommissioningDriver_Ethernet.cpp](https://github.com/znicholson17/P-Linked/blob/main/nodes/ethernet/driver/NetworkCommissioningDriver_Ethernet.cpp).
Afterwards place the driver into   
```bash
/PATH/TO/MATTER/esp-matter/connecthomeip/connecthomeip/src/platform/ESP32/
```   
and replace the file from there.

## Setting up idf.py menuconfig
To set up the idf.py menuconfig, first go to the application examples, which is located in
`/PATH/TO/MATTER/esp-matter/examples`.
Then run:
```bash
cd <your_app>
idf.py menuconfig
```
In the configuration menu, set the following additional configuration to use custom factory partition and different values for Data and Device Info Providers.

1. Enable**`Use W5500 (MAC RAW)`** [Component config → Ethernet → Support SPI to Ethernet Module → Use W500 (MAC RAW]
   > Enable config option to use W5500 drivers configured for ESP32
2. Enable **`ESP32 Factory Data Provider`** [Component config → CHIP Device Layer → Commissioning options → Use ESP32 Factory Data Provider]
   > Enable config option [`CONFIG_ENABLE_ESP32_FACTORY_DATA_PROVIDER`](https://github.com/project-chip/connectedhomeip/blob/master/config/esp32/components/chip/Kconfig#L645) to use ESP32 specific implementation of CommissionableDataProvider and DeviceAttestationCredentialsProvider.
3. Enable **`ESP32 Device Instance Info Provider`** [Component config → CHIP Device Layer → Commissioning options → Use ESP32 Device Instance Info Provider]
   > Enable config option [`ENABLE_ESP32_DEVICE_INSTANCE_INFO_PROVIDER`](https://github.com/project-chip/connectedhomeip/blob/master/config/esp32/components/chip/Kconfig#L655) to get device instance info from factory partition.
4. Enable **`Attestation - Factory`** [ Component config → ESP Matter → DAC Provider options → Attestation - Factory]
   > Enable config option `CONFIG_FACTORY_PARTITION_DAC_PROVIDER` to use DAC certificates from the factory partition during Attestation.
5. Set **`chip-factory namespace partition label`** [Component config → CHIP Device Layer → Matter Manufacturing Options → chip-factory namespace partition label]
   > Set config option [`CHIP_FACTORY_NAMESPACE_PARTITION_LABEL`](https://github.com/project-chip/connectedhomeip/blob/master/config/esp32/components/chip/Kconfig#L856) to choose the label of the partition to store key-values in the "chip-factory" namespace. The default chosen partition label is `nvs`.

6. Change the **`Network Telemetry Option`** to **`Enable Ethernet Telemetry`** and disable any other telemetries (ie: WiFi, Thread, Full Thread, etc) in [Component config → CHIP Device Layer → Network Telemetry Options → Enable Ethernet Telemetry
   > Change to Ethernet Telemetry to be able to use ethernet and  OnNetwork for comissioning.

## Building application
To build the application, first make sure to select the correct IDF target.
```bash
idf.py set-target esp32s3
```
Afterwards, make run the following command to build the application for the ESP32.
```bash
idf.py build
```
Once built, run this application to flash the firmware.
```bash
idf.py flash
```

Some other helpful **`idf.py`** commands:
- erase-flash
   - Erases entire flash chip
- monitor
  - Display serial output
- menuconfig
  - Runs "menuconfig" project configuration tool.

### Author
- [Theodore Tang]([github.com/leunknown](https://github.com/leunknown)https://github.com/leunknown)
