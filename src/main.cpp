#include "mbed.h"

Serial pc(PA_9, PA_10);
DigitalOut led1(PC_13);

// температурный градиент
const float AVG_SLOPE = 4.3E-03;

// напряжение сенсора при температуре  25°C
const float V25 = 1.43;

// Задействуем встроенный датчик температуры используя класс
AnalogIn sensor(ADC_TEMP);

// напряжение сенсора (вольт)
float vSense;
// температура сенсора
float temp;

int main()
{
    while (true)
    {
        // считываем напряжение на выходе сенсора температуры
        vSense = sensor.read() * 3.3;

        // выводит в терминал выходное напряжение  сенсора
        pc.printf("vSense = %3.2fV\r\n", vSense);

        // конвертируем напряжение в температуру
        temp = (V25 - vSense) / AVG_SLOPE + 25.0f;

        // выводим в терминал значение температуры
        pc.printf("temp = %3.1f%cC\r\n", temp, 176);

        led1 = !led1;
        wait_ms(1000);
    }
}