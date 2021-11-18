# BLUETOOTH (Jensen)

Install ESP32
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

Follow Bluetooth tutorial in IDP page under Software section.

### Copied from the IDP moodle:

Requirements:
Arduino IDE (stand alone zip install strongly recommended!)
MegaAVR board package (Board Manager in Tools menu)
ESP32 board package
WiFiNINA library (Manage Libraries in the Tools menu)
Method:
1) Select the Arduino Wifi Rev 2 Board in the tools menu (Tools -> Board -> ArduinoMegaAVR)
2) Open the SerialNINAPassthrough (File -> Examples -> WifiNINA -> Tools)
3) Upload this to the Arduino
4) Select the "U-blox NINA-W10 series" board (Tools -> Board -> ESP32)
5) Open the "SerialToSerialBT" example (File -> Examples -> BluetoothSerial)
6) Modify
SerialBT.begin("ESP32test");
to replace ESP32test with a unique name for your device (e.g. M101Robot)
7) Under the tools menu set upload speed 115200
8) Upload - this step will fail!
9) Look at the error message, there will be a line which shows the upload command which failed.
(if you don't see the error as above go File->Preferences and tick both options for Show verbose output during)
10) Copy the highlighted line (Starts with C:, above red text) to a command window, edit the argument by replacing "--before default_reset" to  "--before no_reset", the command will take some time to run, but should be successful. (If you get an error make sure the Arduino IDE serial monitor isn't open)
11)Switch your board back to the Arduino Wifi Rev 2
12)Create a new project with the following code to test:
void setup() {
     pinMode(NINA_RESETN, OUTPUT);         
     digitalWrite(NINA_RESETN, LOW);

     Serial.begin(115200);
     SerialNina.begin(115200);
}
void loop() {
  if (Serial.available()) {
  SerialNina.write(Serial.read());}
  if (SerialNina.available()) {
  Serial.write(SerialNina.read());}
}
This sets up the NINA_RESTN pin to enable the module, then establishes 2 serial connections, one via bluetooth (SerialNINA) and one over usb serial (Serial). The loop takes any data on either serial connection and copies it to the other.

13) Test - one windows go to your bluetooth devices in control panel and connect to your device. You can then use software such as Bluetooth Serial Terminal to connect your laptop over bluetooth, and the Arduino serial monitor to connect over usb. Any text entered at either terminal should be reproduced at the other



Configuring COM Port (Windows)
In windows control panel search "Bluetooth" and select "Change Bluetooth Settings"
In the COM Ports tab -> Add -> Outgoing Browse and select your robot device.

You will now have a new COM port which is the Bluetooth connection, so you can now use this com port in python for communication with your robot over Bluetooth


C:\Users\jense\Documents\ArduinoData\packages\esp32\tools\esptool_py\3.0.0/esptool.exe --chip esp32 --port COM6 --baud 115200 --before no_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 C:\Users\jense\Documents\ArduinoData\packages\esp32\hardware\esp32\1.0.6/tools/partitions/boot_app0.bin 0x1000 C:\Users\jense\Documents\ArduinoData\packages\esp32\hardware\esp32\1.0.6/tools/sdk/bin/bootloader_dio_40m.bin 0x10000 C:\Users\jense\AppData\Local\Temp\arduino_build_54266/SerialToSerialBT.ino.bin 0x8000 C:\Users\jense\AppData\Local\Temp\arduino_build_54266/SerialToSerialBT.ino.partitions.bin


Code copy:
void setup() {
     pinMode(NINA_RESETN, OUTPUT);         
     digitalWrite(NINA_RESETN, LOW);

     Serial.begin(115200);
     Serial.println("Baud begun at 115200"); // This line is not printing yet, why??
     SerialNina.begin(115200);

     //pinMode(2, OUTPUT);
}
void loop() {
  if (Serial.available()) {
  SerialNina.write(Serial.read());}
  if (SerialNina.available()) {
  Serial.write(SerialNina.read());}

  //int frequency = SerialNina.read();
  //int frequency = frequencyString.toInt();

//  Serial.write(frequency);
//  
//  digitalWrite(2, HIGH);
//  delay(1000/frequency);
//  digitalWrite(2, LOW);
//  delay(1000/frequency);

}
