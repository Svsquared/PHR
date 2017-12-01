#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
  unsigned long timeInitial = 0;
  unsigned long timeCurrent = millis();
  unsigned long exposure;
  int session = 0;
  boolean sessionEnd;
  boolean once = true;
  File dataFile;
  String fileName = "data.txt";
  String dataLine = "***************************";
  
void setup() {
  // put your setup code here, to run once:
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  if(sensorValue != 0)
  {
    
    sessionEnd = false;
    if(once == true)
    {
    timeCurrent = millis();
    timeInitial = timeCurrent;
    //Serial.println("meh");
    once = false;
    }
    if(SD.exists("datalog.txt"))
    {
    }
    else
    {
      Serial.println("ERROR OPENING FILE");
    }

  }
  else
  {
    if(once == false)
    {
    session++;
    timeCurrent = millis();
    exposure = timeCurrent - timeInitial;
    dataLine += timeCurrent;
    dataLine += ",";
    dataLine += exposure;
    dataLine +=",";
    dataLine += session;
    //dataLine += "\n******************************";

    // open file, write, then close  
    dataFile = SD.open("datalog.txt", FILE_WRITE);
    dataFile.println(dataLine);
    dataFile.close();
    //dataFile.println("****************************************");
    
    //Serial.print(timeCurrent);
    //Serial.print(",");
    //Serial.print(exposure);
    //Serial.print(",");
    //Serial.println(session);

    Serial.println(dataLine);
    //Serial.println("\n******************************************");
    
    exposure = 0;
    //once = true;
    }
    sessionEnd = true;
    once = true;
    dataLine = "";
  }

  delay(5);
  }


