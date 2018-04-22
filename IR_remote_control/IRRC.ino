/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <WString.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

String getRCKey(unsigned int val)
{
  unsigned int codes[] = {0xA25D, 0x629D, 0xE21D,
                          0x22DD, 0x02FD, 0xC23D,
                          0xE01F, 0xA857, 0x906F,
                          0x6897, 0x9867, 0xB04F,
                                  0x18E7,
                          0x10EF, 0x38C7, 0x5AA5,
                                  0x4AB5,
                                  0xFFFF};
  String commands[]   =  {"ONE",  "TWO",  "THREE",
                          "FOUR", "FIVE", "SIX",
                          "SEVEN","EIGHT","NINE",
                          "STAR", "ZERO", "POUND",
                                  "FORWARD",
                          "LEFT", "OK",   "RIGHT",
                                  "BACKWARD",
                                  "REPEAT"};
  
  int i;
  String str = "";
  for (i=0; i< sizeof(codes); i++)
  {
    if (val == codes[i])
    {
      str = commands[i];
      break;
    }
  }
  return str;  
}

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Serial.println(results.value, HEX);
    Serial.println(getRCKey(0xFFFF & results.value));
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
