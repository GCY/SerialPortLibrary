bool adc_out = false;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
    Serial.print(c);
    if(c == 0xC){
      adc_out ^= true;
    }
  }
  if(adc_out){
    Serial.println(analogRead(A0));
  }
}
