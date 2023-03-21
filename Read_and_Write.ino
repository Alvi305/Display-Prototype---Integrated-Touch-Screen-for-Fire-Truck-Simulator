

const int bufferSize = 9;

//Read Buffer
byte Read_Buffer[bufferSize];

//Ack Buffer
byte Ack_Buffer[bufferSize];




void setup() {

  Serial1.begin(115200);
  Serial.begin(115200);

}

byte Read_from_Display(byte* Buffer, int Size) {
  
    for (int i = 0; i < Size ; i++) {
    Buffer[i] = Serial1.read();
    
    }
    Serial1.flush();

    byte result = Buffer[8];

    return result;
    
}




void loop() {
  // put your main code here, to run repeatedly:

  
  // Read Data from Serial1 port connected to display if there is data available

  if (Serial1.available() > 0) {
    delay(3);
    byte value = Read_from_Display(Read_Buffer,bufferSize);
    Serial.println(char(value));

  }


}
