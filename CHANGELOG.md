# changelog



## Unreleased



## 0.1.0 - 2022-04-01

### Added
- Basic support for [Adafruit 128x64 OLED display](https://www.adafruit.com/product/4650) stacked on mainboard.
- Splash image for display (*Flying Umbrella Dude Man Guy* is based on an original work by [ThePpeGFX](https://www.deviantart.com/theppegfx) and is used with permission).
- Variable splash display time.



## 0.2.0 - 2022-04-01

### Added
- Basic support for [Adafruit DPS310 Barometer](https://www.adafruit.com/product/4494), attached via Stemma QT.
- Error codes to quickly describe errors with the barometer.
- Two quick and dirty pressure to altitude approximations, which will be evaluated for speed and accuracy.

### Changed
- List of required hardware.

### Fixed
- Version number typo in readme.



## 0.2.1 - 2022-04-12

### Added
- Added a function to set the screen cursor position based on what data should be displayed.

### Changed
- Error codes are no longer returned by initialization functions.
- Getter functions now return bools instead of specific error codes.



## 0.3.0 - 2022-

### Added 
- Implemented state machine.
- A method to determine initial/ground altitude by taking altitude averages during initialization.
- DataPoint class for storing points of data with timestamps.
- CraftInfo class for organzing info about the craft.
- Method in barometer to "calibrate" ground altitude by averaging readings.

### Changed
- There is now only one method available for converting pressure and temperature into altitude.
- Tickrate has been changed from 10Hz to 4Hz for testing.

### Removed
- 

### Fixed
- Cleaned up includes.
