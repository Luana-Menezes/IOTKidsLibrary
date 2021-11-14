/*
  IOTKidsLibrary.h - IOT Library for Kids.
  Created by Luana Menezes, 2021.
*/

#ifndef IOTKidsLibrary_h
#define IOTKidsLibrary_h

#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_SI1145.h"

class Sensor_UVM30A{
    public:
        Sensor_UVM30A(int pin);
        int measure_UVindex();
    private:
        int _pin;
};

template <class T>
void print(T content)
{
  Serial.print(content);
}

template <class T>
void println(T content)
{
  Serial.println(content);
}

void data_transfer_speed(int value);
void delay_seconds(float sec);

class Sensor_SI1145{
    public:
        Sensor_SI1145();
        uint16_t measure_UVindex();
        uint16_t measure_visible_light();
        uint16_t measure_infrared();
        boolean begin(uint8_t addr = SI1145_ADDR, TwoWire *pBus = &Wire);
    private:
        Adafruit_SI1145 _SI1145;
};

#define UV_OFF 0
#define UV_LOW 1
#define UV_MED 2
#define UV_HIGH 3
#define UV_VHIGH 4
#define UV_EXTREME 5

class LedBar {
    public:
        LedBar(int led_pins[], int n);
        void init();
        void show(int uv_index_value);
        void off();
        void off_all();
        void on_until(int until);

    private:
        int _led_pins_size;
        int _uv_config[12] = {
            UV_OFF,
            UV_LOW,
            UV_LOW,
            UV_MED,
            UV_MED,
            UV_MED,
            UV_HIGH,
            UV_HIGH,
            UV_VHIGH,
            UV_VHIGH,
            UV_VHIGH,
            UV_EXTREME
        };
        int* _led_pins;
};
#endif