# Setting up to Build Applications


## Setting up Ethernet Drivers
To build ESP32 for commissioning, we have set up some settings to get ethernet enabled and working.   
To begin, first download the [NetworkCommissioningDriver_Ethernet.cpp](https://github.com/znicholson17/P-Linked/blob/main/nodes/ethernet/driver/NetworkCommissioningDriver_Ethernet.cpp).
Afterwards place the driver into   
`/PATH/TO/MATTER/esp-matter/connecthomeip/connecthomeip/src/platform/ESP32/`   
and replace the file from there.

## Setting up idf.py menuconfig
To set up the idf.py menuconfig, first go to the application examples, which is located in
`/PATH/TO/MATTER/esp-matter/examples`.
Then go to run 
```bash 
idf.py menuconfig
```
From there change some 
