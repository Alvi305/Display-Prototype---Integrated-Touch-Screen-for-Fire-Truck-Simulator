

const int bufferSize = 9;
const int bufferSizeUE5 = 1;

//Read Buffer
byte readBuffer[bufferSize];

//Ack Buffer
byte ackBuffer[bufferSize];

// Read Buffer Unreal
byte readBufferUE5[bufferSizeUE5];



bool hasNewInfo = false;
bool infofromue5 = false;



void setup() 
{

  Serial1.begin(115200);
  Serial.begin(115200);

  pinMode(2,OUTPUT);

}


// Read from Display function

byte ReadFromDisplay(byte* buffer, int size) 
{
  
    for (int i = 0; i < size ; i++) {
    buffer[i] = Serial1.read();
    
    }
    Serial1.flush();

    byte result = buffer[8];

    return result;
    
}

// Read data from UE5

byte ReadFromUE5(byte* buffer, int size) 
{

   
  
    for (int i = 0; i < size ; i++) {
      buffer[i] = Serial.read();
    }

   byte data = buffer[0];
   Serial.flush();

    return data;



    // for debugging in unreal
    //TODO: Remove below block of code in final version
    // if (buffer[0] == byte(1) ) {
    //   Serial.println("A on");
    //   Serial.flush();
      
    //   digitalWrite(LED_BUILTIN, HIGH);  
    //   delay(1000);                      
    //   digitalWrite(LED_BUILTIN, LOW); 
    // }

    

}

// Send data to UE5 function

void WriteToUE5 (byte valueToSend) 
{

  // //dataframe to be sent 
  // byte send_frame_UE5[2] = {17,0};

  // send_frame_UE5[1] = value_to_send;

  // if (send_frame_UE5[0] == 17) 
 
  Serial.println(char(valueToSend));  // TODO: remove the char type conversion when piping to UE5.
  delay(1000);

  Serial.flush();
}







void loop() 
{
  // put your main code here, to run repeatedly:

  byte valueFromDisplay;
  byte valueFromUE5 =  byte(253);
  // Read Data from Serial1 port connected to display if there is data available

  if (Serial1.available() > 0) 
  {
    delay(1);
    byte valueFromDisplay = ReadFromDisplay(readBuffer,bufferSize);
    
    hasNewInfo = true;
    
    delay(3);
  }


   if (Serial.available() == 0 & hasNewInfo) 
    { 

   WriteToUE5(valueFromDisplay);
   //Serial.println(valueFromDisplay);
   hasNewInfo = false;
   }

  
  
   valueFromUE5 = ReadFromUE5(readBufferUE5,bufferSizeUE5);
  
   
  if (valueFromUE5 ==  byte(22)) 
    {
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
    delay(1000);

    }
  

}
