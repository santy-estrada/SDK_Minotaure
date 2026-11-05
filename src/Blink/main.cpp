#include <Arduino.h>
#include "pico/stdlib.h" // Gives access to native SDK functions like sleep_ms()

void setup() {
  // Arduino-style initialization for the serial monitor
  Serial.begin(115200);
  
  // Native SDK-style initialization for the LED
  gpio_init(LED_BUILTIN);
  gpio_set_dir(LED_BUILTIN, GPIO_OUT);
}

void loop() {
  // Native SDK syntax to turn the LED on
  gpio_put(LED_BUILTIN, 1);
  Serial.println("LED on via native SDK Otro2"); 
  sleep_ms(1000); // Native SDK delay

  // Arduino syntax to turn the LED off
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED off via Arduino command Otro2");
  delay(1000); // Arduino delay
}
