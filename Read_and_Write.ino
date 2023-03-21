

const int bufferSize = 9;

//Read Buffer
byte Read_Buffer[bufferSize];

//Ack Buffer
byte Ack_Buffer[bufferSize];




void setup() {

  Serial1.begin(115200);
  Serial.begin(115200);

}

void Read_from_Display(int Size) {
  
    for (int i = 0; i < Size ; i++) {
    Read_Buffer[i] = Serial1.read();
    
    }
    Serial1.flush();

    Serial.println(char(Read_Buffer[8]));
    Serial.flush();
}




void loop() {
  // put your main code here, to run repeatedly:


  if (Serial1.available() > 0) {
    delay(3);
    Read_from_Display(bufferSize);

  }
  

}
