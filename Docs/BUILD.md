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
cd<your_app>
idf.py menuconfig
```
In the configuration menu, set the following additional configuration to use custom factory partition and different values for Data and Device Info Providers.

1. Enable **`ESP32 Factory Data Provider`** [Component config → CHIP Device Layer → Commissioning options → Use ESP32 Factory Data Provider]
   > Enable config option [`CONFIG_ENABLE_ESP32_FACTORY_DATA_PROVIDER`](https://github.com/project-chip/connectedhomeip/blob/master/config/esp32/components/chip/Kconfig#L645) to use ESP32 specific implementation of CommissionableDataProvider and DeviceAttestationCredentialsProvider.
2. Enable **`ESP32 Device Instance Info Provider`** [Component config → CHIP Device Layer → Commissioning options → Use ESP32 Device Instance Info Provider]
   > Enable config option [`ENABLE_ESP32_DEVICE_INSTANCE_INFO_PROVIDER`](https://github.com/project-chip/connectedhomeip/blob/master/config/esp32/components/chip/Kconfig#L655) to get device instance info from factory partition.
3. Enable **`Attestation - Factory`** [ Component config → ESP Matter → DAC Provider options → Attestation - Factory]
   > Enable config option `CONFIG_FACTORY_PARTITION_DAC_PROVIDER` to use DAC certificates from the factory partition during Attestation.
4. Set **`chip-factory namespace partition label`** [Component config → CHIP Device Layer → Matter Manufacturing Options → chip-factory namespace partition label]
   > Set config option [`CHIP_FACTORY_NAMESPACE_PARTITION_LABEL`](https://github.com/project-chip/connectedhomeip/blob/master/config/esp32/components/chip/Kconfig#L856) to choose the label of the partition to store key-values in the "chip-factory" namespace. The default chosen partition label is `nvs`.

5. Change the **`Network Telemetry Option`** to **`Enable Ethernet Telemetry`** and disable any other telemetries (ie: WiFi, Thread, Full Thread, etc) in [Component config → CHIP Device Layer → Network Telemetry Options → Enable Ethernet Telemetry
   > Change to Ethernet Telemetry to be able to use ethernet and  OnNetwork for comissioning.


### Author
- [Theodore Tang]([github.com/leunknown](https://github.com/leunknown)https://github.com/leunknown)
