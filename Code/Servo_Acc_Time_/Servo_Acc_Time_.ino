#include <Wire.h>
#include <Servo.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x69

int pos = 0;
int time_deploy = 8000;
Servo myservo;
int count = 0;
int dead_mode = 50000;
bool flag = false;

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

void setup() {
  //delay(2000); // maybe needed for some MCUs, in particular for startup after power off
  Wire.begin();
  Serial.begin(115200);
  myservo.attach(5);
  myservo.write(0);

  while(!Serial) {}
  
  if(!myIMU.init()){
    Serial.println("ICM20948 does not respond");
  }
  else{
    Serial.println("ICM20948 is connected");
  }

  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);    
  myIMU.setGyrDLPF(ICM20948_DLPF_6);  
  myIMU.setTempDLPF(ICM20948_DLPF_6);
}

void loop() {
  xyzFloat gValue;
  xyzFloat gyr;

  
  myIMU.readSensor();
  myIMU.getGValues(&gValue);
  myIMU.getGyrValues(&gyr);
  
  float temp = myIMU.getTemperature();
  float resultantG = myIMU.getResultantG(&gValue);


    if (flag == false) {
      count = millis();
      Serial.println("Il counter è a:");
      Serial.print(count);
      Serial.println("\n");
      if (millis() > time_deploy) {
        myservo.write(90);
        flag = true;
      }
  }

    if (flag == true) {
    count++;
    if (count > dead_mode) {
      while (true) {
        // non fare nulla
      }
    }
  }
  
  Serial.println("Acceleration in g (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);
  Serial.print("Resultant g: ");
  Serial.println(resultantG);

  Serial.println("Gyroscope data in degrees/s: ");
  Serial.print(gyr.x);
  Serial.print("   ");
  Serial.print(gyr.y);
  Serial.print("   ");
  Serial.println(gyr.z);

  Serial.print("Temperature in °C: ");
  Serial.println(temp);

  Serial.println("********************************************");

  delay(1000);

  
}
