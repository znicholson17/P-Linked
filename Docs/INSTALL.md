Last Updated by [Theodore Tang](https://github.com/leunknown) on 2/21/2024

# Overview
This document is a brief summary of the [ESP32-S3 development SDK](https://docs.espressif.com/projects/esp-matter/en/latest/esp32s3/developing.html). If the guide doesn't work or have addition questions, please refer back to this guide.
# Developing with SDK

## Development Setup
This section talks about setting up your development host, fetching the Git repositories, and instructions to build and flash.

## Host Setup
You should install drivers and support packages for your development host. Linux and Mac OS-X are the supported development hosts in Matter, the **recommended host version**s:

- Ubuntu 20.04 or 22.04 LTS
- macOS 10.15 or later

Additionally, we also support developing on Windows Host using WSL.

## Getting Repositories

### Cloning esp-idf
```bash
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf; git checkout v5.1.2; git submodule update --init --recursive;
./install.sh
cd ..
```
### Cloning esp-matter
```bash
cd esp-idf
source ./export.sh
cd ..

git clone --recursive https://github.com/espressif/esp-matter.git
cd esp-matter;git checkout release/v1.2; git submodule update --init --recursive;
./install.sh
cd ..
```

## Configuring the Environment
This should be done each time a new terminal is opened.
```bash
cd esp-idf; source ./export.sh; cd ..
cd esp-matter; source ./export.sh; cd ..
```

###Enable Ccache for faster IDF builds.
Ccache is a compiler cache. Matter builds are very slow and takes a lot of time. Ccache caches the previous compilations and speeds up recompilation in subsequent builds.
```bash
export IDF_CCACHE_ENABLE=1
```

##Flashing Firmware
Choose IDF target
```bash
idf.py set-target esp32s3
```
If idf.py cannot be found, please go to an example to build.
