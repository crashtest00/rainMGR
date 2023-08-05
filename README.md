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

## Irrigation Logic
extension recommends an inch of rainfall per week. however we also don't want the yard to get dry over a period of some days in the case of a 1-in rainfall event where the following six days would not require irrigation. so, to avoid this issue we divide the week and assume that we want a third roughly a third of an inch of rainfall every two days 3 in of rainfall every two days. this system looks at the Historical rainfall over the last two days and then adds a one day forecast buffer for today as well as tomorrow and if the cumulative rain fall over the past two days plus the forecasted rain today and or the forecasted rain tomorrow is greater than 3 in than we delay for 24 hours.