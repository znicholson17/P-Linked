Last Updated by Theo Tang on 2/9/2024


## Prerequisite



* Ubuntu 20.04 LTS or higher
* [esp-matter](https://github.com/espressif/esp-matter)
* [esp-idf](https://github.com/espressif/esp-idf) (V5.1)
* [ConnectHomeIP (CHIP)](https://github.com/project-chip/connectedhomeip)
* Be on a 2.4 Ghz Wifi network

Follow the steps stated [here](https://docs.espressif.com/projects/esp-matter/en/latest/esp32/developing.html) to install.


### What to do before flashing application onto ESP32

<span style="text-decoration:underline;">When flashing ESP32S3 for the first time, please run the following code:</span>

`idf.py erase-flash`


## Commissioning Matter Device(s) to Home Assistant


### Traversing to add Matter Device(s)

To commission a ESP32 node using the Matter Protocol, First open the Home Assistant app on your mobile device. Go to Settings > Devices & services. On the Devices tab, select the Add device button and select Add Matter Device. From there, follow the instructions for QR Code or Manual Pairing Code.


### QR Code

Scan QR Code given for the specified device. Afterwards, follow the instructions stated for the IOS or Android App. If the QR Code fails to work, try manually pairing using the Pairing Code.


### Pairing Code

To pair, enter the pairing code. The pairing code is a 11 digit code that follows the format of

XXXX - XXX - XXXX

Once entered, follow the remaining instructions on your mobile device.


## How to Generate a New bin file to Commission device.

To find the program that does bin file generation, go to /{ESP-MATTER PATH}/tools/mfg_tool and run the program: 

`./mfg_tool.py`

This tool generates both the QR code and manual pairing codes. **There is no need to generate QR code or manual pairing code** unless you are only given the discriminator, passcode, Vendor ID, and Product ID. You are also able to generate multiple commission files at once.

<span style="text-decoration:underline;">Main commands **NEED** to state:</span>



1. -cn
    1. Common name prefix of subject of PAI cert
2. -v
    2. Vendor ID, usually hex code identifying manufacturer of device.
3. --pai
    3. Input certificate as PAI certificate
4. -k
    4. Input key file
5. -c
    5. Certification file (usually link to it)
6. -cd
    6. Certification declaration file
7. -dm 
    7. Discovery mode: 0:WiFi-SoftAP, 1:BLE, 2:On-network.
    8. Default is BLE, but set to mode to be On-network

To see other commands:



1. -h


### Example



* Please note the file as to be pai

`./mfg_tool.py -cn "Device Name" -v 0xFFF1 -p 0x8000 -dm 2 --pai -k /PATH/TO/MATTER/esp-matter/connectedhomeip/connectedhomeip/credentials/test/attestation/Chip-Test-PAI-FFF1-8000-Key.pem -c /PATH/TO/MATTER/esp-matter/connectedhomeip/connectedhomeip/credentials/test/attestation/Chip-Test-PAI-FFF1-8000-Cert.pem -cd /PATH/TO/MATTER/esp-matter/connectedhomeip/connectedhomeip/credentials/test/attestation/Chip-Test-PAI-FFF1-8000-Cert.der`

With this example, it chooses a random discriminator and passcode for the generated bin file and outputs it in its own folder.


### Output

Output will be under:

`/{ESP-MATTER PATH}/tools/mfg_tool/out`

The folder name will be dependent on Vendor ID and Product ID, naming would be the hex number of those two combined.

**Ex:** FFF2_8001 for the Vendor ID 0xFFF2 and Product ID 0x8001

The bin file, manual pairing code, and generated QR Code will be located in the random letter folder. Once the code was entered, it tells you where the code was generated.



![stuff](https://github.com/znicholson17/P-Linked/blob/main/Docs/Images/Bin_File_Demo.png)

## Flashing Bin file onto ESP32S3

After generating the bin file, to flash the file onto the ESP32.

Run: `./esptool.py` 

Commands:



* Write_flash 

The example command is to flash data onto the ota_data (over the air) section of the [partition table](https://blog.espressif.com/how-to-use-custom-partition-tables-on-esp32-69c0f3fa89c8)


### Example Flash

`./esptool.py write_flash 0x1000 {path to bin file}`

`./esptool.py write_flash 0x10000 /PATH/TO/MATTER/esp-matter/tools/mfg_tool/out/fff1_8000/848358cf-1f9e-4c2a-9ebc-b021db4fe434/848358cf-1f9e-4c2a-9ebc-b021db4fe434-partition.bin`

Afterwards: this is what it should look like:



![Example ESPTOOL Flash](https://github.com/znicholson17/P-Linked/blob/main/Docs/Images/esptool_flash.png)



## Generating QR Code

To generate a QR Code, go to: 

/{CONNECTHOMEIP PATH}/src/setup_payload/python

Run `./generate_setup_payload.py`

Commands:



1. -h
    1. Lists commands to use
2. -d DISCRIMINATOR
    2. Write discriminator for pairing, range: 0x00-0x0FFF 
3. -vid VENDOR_ID
    3. Vendor ID
4. -pid PRODUCT_ID
    4. Product ID
5. -cf
    5. Commissioning flow: 0: Standard, 1: User-Intent, 2: Custom Default: 0
6. -dm
    6. Commissionable device discovery
    7. 0: SoftAP 1: BLE, 2: OnNetwork. Default: OnNetwork
7. -p
    8. Passcode

Commands 2-6 must be stated. We will be using -cf 0 and -dm 1


### Example Generating Script

`./generate_setup_payload.py -d 0x0AA4 -vid 0xFFF2 -pid 0x8001 -cf 0 -dm 1 -p 47239151`


### 


### Output

The output will be two items: 



1. Manual Code will be given as well as 

Ex:



![Generated QR Demo](https://github.com/znicholson17/P-Linked/blob/main/Docs/Images/Generate_setup_payload.png)


Manualcode : 23684728836

QRCode 	: MT:634J0EP114-UZ05Z.00

<span style="text-decoration:underline;">QR Code can be generated by putting at the end of this link:</span>

https://project-chip.github.io/connectedhomeip/qrcode.html?data={INSERT QR CODE code}


### Example Printing Out QR Code

[https://project-chip.github.io/connectedhomeip/qrcode.html?data=MT:634J0EP114-UZ05Z.00](https://project-chip.github.io/connectedhomeip/qrcode.html?data=MT:634J0EP114-UZ05Z.00)

This prints out QR code for the code MT:634J0EP114-UZ05Z.00:


![QR Code Link](https://github.com/znicholson17/P-Linked/blob/main/Docs/Images/demo_QR_Code.png)


## Appendix


#### Failed to record BootReason event: 3

If this error occurs on idf.py monitor, erase flash memory by running:

`./idf.py erase-flash`


#### ESP32 is bootlooping

Reflash the ESP32 and flash the bin with the starting address of 0x10000. If you follow the instructions from [connecthomeip](https://github.com/project-chip/connectedhomeip.git), it overwrites the partition table, causing a bootloop.


#### Cannot re-pair device after deleting or resetting.

To re-pair a device that was already paired, please go to settings and delete the matter accessory that is being recommissioned.

As your device may not delete the paired matter device data on your phone. This may not allow you to pair the device again with the QR code or pairing code that was previously used.


#### Using Same QR/Pairing Code more than once.

As one QR/Pairing Code can be used once to pair, it should not be for more than once device. Each matter node must have their own unique QR Code.

*Note: If the pairing data was deleted from the device, it can be used again.
