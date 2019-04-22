// sudo chmod a+rw /dev/ttyUSB0

const int analogPin = A0;
const unsigned long t_1hr = 3600000000;

const int buf0_size = 256;
const int buf1_size = 4*buf0_size;
const int buf2_size = 2*buf0_size;
byte buf1[buf1_size],buf2[buf2_size];

unsigned long t, dt;
int t_ht, V;
int k1, k2;

//-------------------------------
void setup() {
  Serial.begin(115200);

  set_prescaler(128);

  t = micros();
  t_ht = -1;
  k1 = 0;
  k2 = 0;
}
//-------------------------------
void loop() {
    dt = micros()-t;  // calculate elapsed time
    V  = analogRead(analogPin);

    t += dt;    

    buf1[0+k1] = t & 255;
    buf1[1+k1] = (t >> 8)  & 255;
    buf1[2+k1] = (t >> 16) & 255;
    buf1[3+k1] = (t >> 24) & 255;
    k1 += 4;
    
    buf2[0+k2] = V & 255;
    buf2[1+k2] = (V >> 8)  & 255;
    k2 += 2;

    if (k1 == buf1_size) {
      if (t >= t_1hr) { t_ht += 1; t = t-t_1hr;};
      Serial.write(t_ht);
      Serial.write(buf1,buf1_size);
      Serial.write(buf2,buf2_size);
      k1 = 0;
      k2 = 0;
      }
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
