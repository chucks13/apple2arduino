/*

   Chuck Sommerville 2020
   Apple II 2 Arduino glue
   This reads bit banged serial from the Apple II game port and sends it out the USB serial port
   to be captured by a PC.

   pin function
   9    reset - resets the communication
   10   data - the data bit
   11   rdy - indicator that there is a bit ready form the Apple
   13   ack - acknoledge to the Apple that the bit has been read
*/

const int rst = 9;    // (15) c05c c05d
const int dat = 10;    // (13) c058 c059
const int rdy = 11;    // (14) c05a c05b
const int ack = 13;    // (2) c061

void setup() {
  Serial.begin (230400);
  pinMode(ack, OUTPUT);
  pinMode(dat, INPUT);
  pinMode(rdy, INPUT);

}

int readbyte()
{
  int v = 0;
  int i;
  for (i = 0; i < 8; i++)
  {
    while (digitalRead(rdy) == HIGH)
    {
      if (digitalRead(rst) == LOW)
      {
        i = 0;
        v = 0;
      }
    }
    v *= 2;
    if (digitalRead(dat) == HIGH)
    {
      v++;
    }
    digitalWrite(ack, LOW);       // signal got it
    while (digitalRead(rdy) == LOW)
    {
      if (digitalRead(rst) == LOW)
      {
        i = 0;
        v = 0;
      }
    }
    digitalWrite(ack, HIGH);       // signal done
  }
  return v;
}

void loop() {
  Serial.write(readbyte());
}
