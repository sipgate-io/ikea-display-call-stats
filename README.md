# PyjamaCallStatistics

Project using sipgate.io to display call, fax and sms data on IKEA OBEGRÄNSAD.  
This project utilizes [this repository](https://github.com/ph1p/ikea-led-obegraensad) (Please ensure that you have
followed the instructions of this repository beforehand) and adds sipgate.io functionality.

## How-To-Start (minimum)

Requires a working and properly configured docker installation for more info
click [here](https://docs.docker.com/engine/install/)

- navigate using your shell of choice into a directory
- clone the repository using the following command:  
  ```git clone https://github.com/sipgate/PyjamaCallStatistics```
- jump into the now cloned repository using  
  ```cd PyjamaCallStatistics/```
- using the text editor of your choice edit the .env-template and replace the ```Your Client ID```
  and ```Your Client Secret``` with your client ID and your client secret.  
  You can delete the rest of the file for now.
- (copy and) rename the ```.env-template``` file to just ```.env```
- build and run the docker container using the following command:  
  ```docker compose build && docker compose up -d```

## How-To-Config (maximum)

Create ```include/secrets.h``` file inside the ikea-repo folder.

``` { secrets.h }
#pragma once

#define WIFI_HOSTNAME ""

#ifdef ESP8266
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#endif

#define OTA_USERNAME ""
#define OTA_PASSWORD ""
#define CALL_STATS_SERVER "YOUR_BACKEND_SERVER_IP"
```

When you open the ```.env-template``` file, it should look something like this:

``` { .env }
CLIENT_ID="Your Client ID" 
CLIENT_SECRET="Your Client Secret"
DELAY="10"
START="Your Start Date"
END="Your End Date"
```

- You know ```CLIENT_ID``` and ```CLIENT_SECRET``` from the Start-up Tutorial
- ```DELAY``` is the delay (in seconds) for polling Data from the Rest API, it is only used when ```END``` is not set.
- ```START``` and ```END``` are the interval from which you want to fetch data from.
  The Variables should only and ONLY be set in ISO 8601 (- 2022 in UTC) Time Format!
- It should look something like this: ```2024-05-01T00:00:00Z```
- Please only set END if START is also set accordingly, also note START < END (thank u xx)

## Display of Numbers, Characters and Icons

- Displaying of numbers can be done using the methods Screen.drawBigNumbers() and Screen.drawNumbers()
- Displaying of characters can be done using the method Screen.drawCharacter()
- Displaying of icons can be done using Screen.drawImage()

- BMP file can be passed and is converted into a string. That string can be used to generate a new vector that displays an icon on IKEA OBERGRÄNSAD.

## Display Animation

- use Screen.setPixel() to set a Pixel in a loop to animate.
- use Screen.scrollText() to display a string from left to the right
- Idea: Wipeanimation 
  - using methods like the following in screen.cpp to display our concatinated images:
    - horizontalWipeAnimation(), 
    - verticalWipeAnimation(), 
    - diagonalWipeAnimation() 

## Dependencies

- Node.js
- TypeScript
- docker (optional)

## Known Issues

None so far :D  
