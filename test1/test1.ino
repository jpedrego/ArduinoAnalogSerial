// I found I have to give admin rights in Lubuntu 18.10:
// sudo chmod a+rw /dev/ttyUSB0

// The pin where there is the analog input:
const int analogPin = A0; 

// Number of microsecond in 1h:
const unsigned long t_1hr = 3600000000;

unsigned long t, dt;
int t_ht, V;
byte buf2[2],buf1[4];

//-------------------------------
void setup() {
  
// 128 prescaler for 9.6 KHz  DEFAULT
// 64 prescaler for 19.2 KHz
// 32 prescaler for 38.4 KHz
// 16 prescaler for 76.8 KHz
// 8 prescaler for 153 KHz
// 4 prescaler for 307 KHz
// 2 prescaler for 615 KHz
  set_prescaler(128);
  
  t = micros();
  t_ht = -1;
  
  Serial.begin(115200);
}
//-------------------------------
void loop() {
    dt = micros()-t;  // calculate elapsed time
    V  = analogRead(analogPin);

// Because we would like to run over the acquisition over long times, 
// I have created a variable to record 'hours'. I store it as a negative 
// number so it helps me on the Python side.
// I send only the first byte as I do not exprec to run for more than 253 hours!!!
    t += dt;
    if (t >= t_1hr) { t_ht += 1; t = t-t_1hr;};
    Serial.write(t_ht);

// The time-stamp comes a type 'long', so 4 bytes:
    buf1[0] = t & 255;
    buf1[1] = (t >> 8)  & 255;
    buf1[2] = (t >> 16) & 255;
    buf1[3] = (t >> 24) & 255;
    Serial.write(buf1, 4);

// The analogRead() gives a 'int' in the present case as resolution of the UNO is 0-1023 (10Bits)
// 'int' is 2 bytes, so:
    buf2[0] = V & 255;
    buf2[1] = (V >> 8)  & 255;
    Serial.write(buf2, 2);         
}

void set_prescaler(int prescaler){
  // For Arduino Uno. The ADC clock of the UNO runs at 16MHz
  // One ADC conversion takes 13 clock cycles (not the main clock!)
  // Sampling rate is = [ADC clock] / [prescaler] / [conversion clock cycles]
  switch (prescaler){
    case 128:
      // 128 prescaler for 9.6 KHz  DEFAULT
      bitWrite(ADCSRA,ADPS2,1);
      bitWrite(ADCSRA,ADPS1,1);
      bitWrite(ADCSRA,ADPS0,1);
      break;
    case 64:
      // 64 prescaler for 19.2 KHz
      bitWrite(ADCSRA,ADPS2,1);
      bitWrite(ADCSRA,ADPS1,1);
      bitWrite(ADCSRA,ADPS0,0);
      break;
    case 32:
      // 32 prescaler for 38.4 KHz
      bitWrite(ADCSRA,ADPS2,1);
      bitWrite(ADCSRA,ADPS1,0);
      bitWrite(ADCSRA,ADPS0,1);
      break;
    case 16:
      // 16 prescaler for 76.8 KHz
      bitWrite(ADCSRA,ADPS2,1);
      bitWrite(ADCSRA,ADPS1,0);
      bitWrite(ADCSRA,ADPS0,0);
      break;
    case 8:
      // 8 prescaler for 153 KHz
      bitWrite(ADCSRA,ADPS2,0);
      bitWrite(ADCSRA,ADPS1,1);
      bitWrite(ADCSRA,ADPS0,1);
      break;
    case 4:
      // 4 prescaler for 307 KHz
      bitWrite(ADCSRA,ADPS2,0);
      bitWrite(ADCSRA,ADPS1,1);
      bitWrite(ADCSRA,ADPS0,0);
      break;
    case 2:
      // 2 prescaler for 615 KHz
      bitWrite(ADCSRA,ADPS2,0);
      bitWrite(ADCSRA,ADPS1,0);
      bitWrite(ADCSRA,ADPS0,1);
      break;
    default:
      // 128 prescaler for 9.6 KHz  DEFAULT
      bitWrite(ADCSRA,ADPS2,1);
      bitWrite(ADCSRA,ADPS1,1);
      bitWrite(ADCSRA,ADPS0,1);
      break;
  }
}
