class DwinHandler
{
  private:
    static constexpr int m_bufferSize = 9;
    static constexpr int m_ackBufferSize = 6;
    byte m_writebuffer[8] =  {0x5a, 0xa5, 0x05, 0x82, 0x50, 0x00, 0x00, 0x00};
  public:
    unsigned char ReadBuffer[m_bufferSize];
    unsigned char AckBuffer[m_ackBufferSize];
    byte& AddressHighByte = m_writebuffer[4];
    byte& AddressLowByte = m_writebuffer[5];
    byte& WriteData = m_writebuffer[7];
    byte DwinHighByte[7] = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55,0x57};
    byte DwinLowByte[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00};
    bool HasNewInfo = false;
  public:
    void Read()
    {
      if(Serial1.available())
      {
        delay(1); // Wait for all bytes to get into incoming buffer
        for (int i = 0; i < m_bufferSize; i++)
        {
          ReadBuffer[i] = Serial1.read();
        }
        HasNewInfo = true;
      }
    }
    
    void Write(const byte HighByte, const byte LowByte, const byte Data)
    {
      AddressHighByte = HighByte; //4th byte of dataframe sent to display
      AddressLowByte = LowByte;   //5th byte of dataframe sent to display
      WriteData = Data;           //7th byte of dataframe sent to display
      // Write Data to Address(HighByte, LowByte) 
      while(Serial1.availableForWrite() < 8)
      {

        
        delay(1);
      }
      Serial1.write(m_writebuffer, 8);
      Serial1.flush();

      // Receive acknowledgement
      delay(1);
      for (int i=0; i < m_ackBufferSize;i++) 
        {
          AckBuffer[i] = Serial1.read();
        }
    }
};

class UeHandler
{
  private:
    byte m_writebuffer[2] =  {byte(0),byte(0)};
  public:
    static constexpr int ReadBufferSize = 7; // change this if new vp address is added
    static constexpr int WriteBufferSize = 2;
    unsigned char ReadBuffer[ReadBufferSize];

    byte& Destination = m_writebuffer[0];
    byte& WriteData = m_writebuffer[1];
    bool HasNewInfo = false;

  public:
    void Read()
    {
      if(Serial.available())
      {
        delay(1); // Wait for all bytes to get into incoming buffer
      for (int i = 0; i < ReadBufferSize; i++)
      {
        ReadBuffer[i] = Serial.read();
      }
      HasNewInfo = true;
      }
    }
    
    void Write(const char Dest, const char Data)
    {
      Destination = Dest;
      WriteData = Data;
      // Write Data to Destination 
      while(Serial.availableForWrite() < 2)
      {
        delay(1);
      }

      for(int i = 0; i < WriteBufferSize; i++)
      {
        Serial.print(m_writebuffer[i]);
        Serial.print(',');
      }
      Serial.println();
      Serial.flush();
    }
};

DwinHandler dwin;
UeHandler ue;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // dwin handler unit test code
   dwin.Read();

//for debugging
  // for (int i=0;i< 9;i++) {
  //   Serial.println(dwin.ReadBuffer[i],HEX);
  //   delay(1500);
  // }
  // if(dwin.HasNewInfo) {
  // Serial.println(char(dwin.ReadBuffer[8]));
  // dwin.HasNewInfo = false;
  // }



  if(dwin.HasNewInfo)

   {
    // switch case statement may need to be implemented
    ue.Write(1,dwin.ReadBuffer[8]);
    dwin.HasNewInfo = false;
   }

  ue.Read();
  if(ue.HasNewInfo)
  {
    for(int i = 0; i < ue.ReadBufferSize; i++)
    {
      dwin.Write(dwin.DwinHighByte[i], dwin.DwinLowByte[i], ue.ReadBuffer[i]);
    }
    ue.HasNewInfo = false;
  }
}
