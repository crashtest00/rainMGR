# rainMGR
Current Version Number: 0.5
## Release Steps:
1. Update version number in main.cpp comment & variable
1. Update version number in this document
1. Build new firmware
1. Copy firmware.bin file from .pio/build/denky32
1. Upload firmware.bin file to server 
1. Rename firmware.bin to appropriate version number (e.g. `CONTROLLER-v0.4`)
1. Update currentVersion.JSON file to reflect most recent version number
1. Update path in JSON file to reflect most recent version (tip: copy relative path!)

Copy and paste wherever possible to ensure consistent and correct file naming!