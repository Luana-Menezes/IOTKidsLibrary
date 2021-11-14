#include "IOTKidsLibrary.h"
#include <Wire.h>
#include "Adafruit_SI1145.h"

Sensor_UVM30A::Sensor_UVM30A(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
};

int Sensor_UVM30A::measure_UVindex()
{
  int valor_uv_sensor = analogRead(_pin);
  int tensao = (valor_uv_sensor * (5.0 / 1023.0)) * 1000;
  if (tensao == 0)
  {
    return 0;
  }
  else if (tensao > 0 && tensao <= 227)
  {
    return 0;
  }
  else if (tensao > 227 && tensao <= 318)
  {
    return 1;
  }
  else if (tensao > 318 && tensao <= 408)
  {
    return 2;
  }
  else if (tensao > 408 && tensao <= 503)
  {
    return 3;
  }
  else if (tensao > 503 && tensao <= 606)
  {
    return 4;
  }
  else if (tensao > 606 && tensao <= 696)
  {
    return 5;
  }
  else if (tensao > 696 && tensao <= 795)
  {
    return 6;
  }
  else if (tensao > 795 && tensao <= 881)
  {
    return 7;
  }
  else if (tensao > 881 && tensao <= 976)
  {
    return 8;
  }
  else if (tensao > 976 && tensao <= 1079)
  {
    return 9;
  }
  else if (tensao > 1079 && tensao <= 1170)
  {
    return 10;
  }
  else if (tensao > 1170)
  {
    return 11;
  }
}

void data_transfer_speed(int value)
{
  Serial.begin(value);
}

void delay_seconds(float sec)
{
  delay(sec * 1000);
}

Sensor_SI1145::Sensor_SI1145()
{
  _SI1145 = Adafruit_SI1145();
}

uint16_t Sensor_SI1145::measure_UVindex()
{
  return (_SI1145.readUV() / 100);
}

uint16_t Sensor_SI1145::measure_visible_light()
{
  return _SI1145.readVisible();
}

uint16_t Sensor_SI1145::measure_infrared()
{
  return _SI1145.readIR();
}

boolean Sensor_SI1145::begin(uint8_t addr, TwoWire *pBus)
{
  return _SI1145.begin(addr, pBus);
}

LedBar::LedBar(int led_pins[], int n)
{
  _led_pins_size = n;

  if (_led_pins_size == 1 || _led_pins_size == 3 || _led_pins_size == 6)
  {
    _led_pins = led_pins;
    init();
  }
}

void LedBar::init()
{
  for (int i = 0; i < _led_pins_size; i++)
  {
    pinMode(_led_pins[i], OUTPUT);
  }
  off_all();
}

void LedBar::show(int uv_index_value)
{
  off_all();
  if (uv_index_value != 0)
  {
    if (_led_pins_size == 1)
    {
      if (_uv_config[uv_index_value] == UV_HIGH ||
          _uv_config[uv_index_value] == UV_VHIGH || _uv_config[uv_index_value] == UV_EXTREME)
      {
        on_until(1);
      }
    }

    if (_led_pins_size == 3)
    {
      if (_uv_config[uv_index_value] == UV_LOW)
      {
        on_until(1);
      }
      else if (_uv_config[uv_index_value] == UV_MED)
      {
        on_until(2);
      }
      else if (_uv_config[uv_index_value] == UV_HIGH || _uv_config[uv_index_value] == UV_VHIGH ||
               _uv_config[uv_index_value] == UV_EXTREME)
      {
        on_until(3);
      }
    }
    else if (_led_pins_size == 6)
    {
      if (uv_index_value == 1)
      {
        on_until(1);
      }
      else if (uv_index_value == 2)
      {
        on_until(2);
      }
      else if (uv_index_value == 3)
      {
        on_until(3);
      }
      else if (uv_index_value == 4 || uv_index_value == 5)
      {
        on_until(4);
      }
      else if (uv_index_value == 6 || uv_index_value == 7 || uv_index_value == 8)
      {
        on_until(5);
      }
      else if (uv_index_value == 9 || uv_index_value == 10 || uv_index_value == 11)
      {
        on_until(6);
      }
    }
  }
}

void LedBar::off_all()
{
  for (int i = 0; i < _led_pins_size; i++)
  {
    digitalWrite(_led_pins[i], LOW);
  }
}

void LedBar::on_until(int until)
{
  for (int i = 0; i < until; i++)
  {
    digitalWrite(_led_pins[i], HIGH);
  }
}

