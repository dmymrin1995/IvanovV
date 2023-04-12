#include <Servo.h>
#include <CurieBLE.h>

BLEPeripheral blePeripheral;
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

Servo myservo;  
Servo myservo1; 

void setup() {
  myservo.attach(9);
  myservo1.attach(11);

  Serial.begin(9600);
  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);
  switchCharacteristic.setValue(0);
  blePeripheral.begin();
  Serial.println("BLE LED Peripheral");

}

void loop() {
  BLECentral central = blePeripheral.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    while (central.connected()) {
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value() == 1) {   
          myservo.write(90);                  
        } 
        else if (switchCharacteristic.value() == 2) {                              
          myservo.write(0);    
        }
        else if (switchCharacteristic.value() == 3) {   
          myservo1.write(90);                  
        } 
        else if (switchCharacteristic.value() == 4) {                              
          myservo1.write(0);    
        }
      }
    }
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}                            // waits for the servo to get there

