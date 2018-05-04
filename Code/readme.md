Technologies Used 
------------------- 
 
+   JAVA 
+   Python 
+   Android 
+   Specialized Hardware (Load Cell)
+	ADC amplifiers
+	Wifi fingerprinting 
+	Amazon Web Services (IoT, Cognito)
 
Installation Instructions 
========================= 
 
Python for Serial I/O : http://docs.python-guide.org/en/latest/starting/install3/linux/
Arduino for esp32 cod : https://www.arduino.cc/en/Guide/ArduinoUno
Espresso libraries sp : https://github.com/espressif/arduino-esp32
Amplifiers of espress : https://www.hackster.io/MOHAN_CHANDALURU/hx711-load-cell-amplifier-interface-with-arduino-fa47f3
AWS setup in esp32 ad : https://github.com/ExploreEmbedded/Hornbill-Examples/tree/master/arduino-esp32/AWS_IOT
JAVA for Android stdo : https://docs.oracle.com/javase/8/docs/technotes/guides/install/install_overview.html
Android Studio for UI : https://developer.android.com/studio/install
AWS setup for Android : https://github.com/awslabs/aws-sdk-android-samples/tree/master/AndroidPubSub

After the installations are done successfully upload the code for 'loadCell_IOT' from the Microcontroller Code on to an esp-32 using the Arduino IDE. Also run the code for 'AndroidPubSub' from UI Code using Android Studio IDE to maintain contact.

You may need to change the Wifi SSID and password for both the codes to connect to AWS. You can also conduct individual testing of the different steps of Load cell caliberation, AWS publications, AWS Subscriptions, Wifi router strength verification, etc. from the individual separate codes provided.
 
The only installation for our project is Android Studio and Arduino, even for those two it is just downloading the package and extracting it to any suitable folder(Ubuntu), followed by importing the project provided and running it. Thats all.
Hence the link for installation of Android Studio is given
https://www.youtube.com/watch?v=7vvMltQtfxY.

References 
=========== 
 
Please give references to importance resources.  
 
+ [Python](http://docs.python-guide.org) 
+ [Arduino](http://www.arduino.cc) 
+ [AWS/Esp32](http://github.com)
+ [HX711](http://www.hackster.io) 
+ [JAVA sdk](http://docs.oracle.com) 
+ [Android](http://developer.android.com) 
