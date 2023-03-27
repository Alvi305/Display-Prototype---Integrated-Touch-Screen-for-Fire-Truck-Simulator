

constexpr int bufferSize = 9;
constexpr int bufferSizeUE5 = 1;


//Read Buffer for data from display

byte readBufferDisplay[bufferSize];

//Ack Buffer after sending dataframe to display
byte ackBuffer[bufferSize];

// Read Buffer Unreal
byte readBufferUE5[bufferSizeUE5];

// variable to store what data is to be sent to the display
byte byteToBeSent;

// Write Buffer for writing dataframe to display
byte writeDataDisplayBuffer[8] =  {0x5a, 0xa5, 0x05, 0x82, 0x50, 0x00, 0x00, byteToBeSent};


// variable to store data from 8th byte of dataframe
byte valueFromDisplay;
  



bool newInfoFromDisplay = false;




void setup() 
{

  Serial1.begin(115200);
  Serial.begin(115200);

  pinMode(2,OUTPUT);

}


// Read  data from Display 

void ReadFromDisplay(byte buffer[bufferSize],byte& value,bool& newInfo) 
{
   if (Serial1.available() > 0) 
   {
    delay(3);
  
    for (int i = 0; i < bufferSize ; i++) {
    buffer[i] = Serial1.read();
    
    }
    

    value = buffer[8];

    newInfo = true;

    
   }
    
}

// Read data from UE5

byte ReadFromUE5(byte  buffer[bufferSizeUE5]) 
{

   
  
    for (int i = 0; i < bufferSizeUE5 ; i++) {
      buffer[i] = Serial.read();
    }

   byte data = buffer[0];
    return data;    

}

// Send data to UE5 

void WriteToUE5 (const byte& value, bool&   newInfo) 
{

  // //dataframe to be sent 
  // byte send_frame_UE5[2] = {17,0};

  // send_frame_UE5[1] = value_to_send;

  // if (send_frame_UE5[0] == 17) 

   if (Serial.available() == 0 & newInfo) 
  {
 
  Serial.println(char(value));  // TODO: remove the char type conversion when piping to UE5.
  delay(10);

  Serial.flush();
  newInfo = false;
  }


}

// Send data to the display

void WriteToDisplay (byte writeDataDisplayBuffer[8], byte& sendData) {

 if (Serial1.availableForWrite()>8) {

   writeDataDisplayBuffer[7] = sendData;
   Serial1.write(writeDataDisplayBuffer,8);
   Serial1.flush();

 }

 // Receive acknowledgement after writing to the display

 for ( int i=0; i < bufferSize;i++) 
 {
   ackBuffer[i] = Serial1.read();
   delay(1);
 }


}







void loop() 
{
  // put your main code here, to run repeatedly:

  byte valueFromUE5 =  byte(0);
  // Read Data from Serial1 port connected to display if there is data available
  ReadFromDisplay(readBufferDisplay, valueFromDisplay, newInfoFromDisplay);
  WriteToUE5(valueFromDisplay,newInfoFromDisplay);


   valueFromUE5=ReadFromUE5(readBufferUE5);

   if (valueFromUE5%byte(2)==0)
    {
    WriteToDisplay(writeDataDisplayBuffer,valueFromUE5);
    }
   







  
  
  //  valueFromUE5 = ReadFromUE5(readBufferUE5,bufferSizeUE5);
  
   
  // if (valueFromUE5 ==  byte(22)) 
  //   {
  //   digitalWrite(2,HIGH);
  //   delay(1000);
  //   digitalWrite(2,LOW);
  //   delay(1000);

  //   }
  

}
