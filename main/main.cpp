#define FASTLED_RMT_BUILTIN_DRIVER 1
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "esp_spi_flash.h"
#define ESP32
#include "FastLED.h"

#define NUM_LEDS 144
#define DATA_PIN 13
#define CLOCK_PIN 12
CRGB leds[NUM_LEDS];


extern "C" {
  void app_main();
}

void blinkLeds(void *pvParameters){
  while(1){
    for( int i = 0; i < NUM_LEDS; i++) {
    	leds[i] = CRGB::Blue;
    }
    FastLED.show();
    delay(600);
  }


}


void app_main() {
  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1000);
  xTaskCreatePinnedToCore(&blinkLeds, "blinkLeds", 4000, NULL, 5, NULL, 0);
  
}
