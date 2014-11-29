// This script counts the number of rising edge triggers on pin #2 and returns
// the rate every second; the frequency in hertz.

// As a secondary utility it also outputs PWM signals of 
// roughly 1, 19 and 38 khz for testing

#define ONE_SECOND 1000

// Sensing pin is pin 2, using rising interrupt to increment a counter

// 3 Pins will output PWM signals of roughly 1, 19, and 38 khz for testing 
const int PWM_980hz = 5; // 980 Hz @ 50% duty cycle using PWM
const int PWM_19khz = 11; // 19.25 KHz @ 50% duty cycle
const int PWM_38khz = 3; // 38.5 KHz @ 50% duty cycle

volatile int measuredState = LOW;
volatile unsigned long counter = 0;

int outState;
unsigned long lastTimeSecond;

// counter increments on every rising edge on pin 2
void measureTrigger()
{
  counter++;
}

void setup() {
  Serial.begin(115200);
  pinMode(PWM_980hz, OUTPUT);
  pinMode(PWM_19khz, OUTPUT);
  pinMode(PWM_38khz, OUTPUT);

  // Set Fast PWM with OCRA top for pin 3 & 11 and change multiplier
  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS21) | _BV(CS20);  
  OCR2A = 12;
  OCR2B = 6;

  // Pin 3 ~ 38.5 kHz
  analogWrite(5, 255/2); // Pin 5 ~ 980 Hz
  // Pin 11 ~ 19.25 kHz
  
  lastTimeSecond = millis();

  // Set up trigger interrupt on pin 2
  attachInterrupt(0, measureTrigger, RISING);
}

void loop() {
  if (millis() - lastTimeSecond > ONE_SECOND)
  {
    noInterrupts(); // Disable interrupts to stop counter updating
    
    // Display counter & reset
    Serial.println(counter);
    counter = 0;

    lastTimeSecond = millis();
    interrupts(); // Restart interrupts
  }
}
