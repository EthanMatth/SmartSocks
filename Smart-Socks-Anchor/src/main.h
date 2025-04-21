#include <SPI.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include "DW1000Ranging.h"     //https://github.com/thotro/arduino-dw1000

#define ANCHOR_ADD "83:17:5B:D5:A9:9A:E2:9C"
 
#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

const uint8_t Analog_0 = 35;
const uint8_t Analog_1 = 36;
const uint8_t Analog_2 = 39;



typedef struct force_data {
    int Big;
    int Little;
    int Heel;
} force_data;

force_data a_data;
force_data t_data;
double distance = 1.4;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  memcpy(&t_data, incomingData, sizeof(t_data));
}

void newRange()
{
    Serial.print("from: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    Serial.print("\t Range: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getRange());
    distance = DW1000Ranging.getDistantDevice()->getRange();
    Serial.print(" m");
    Serial.print("\t RX power: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
    Serial.println(" dBm");
}
 
void newBlink(DW1000Device *device)
{
    Serial.print("blink; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}
 
void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}

void DW1000Setup()
{
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
    //define the sketch as anchor. It will be great to dynamically change the type of module
    DW1000Ranging.useRangeFilter(true);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newBlink);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    
 
    //we start the module as an anchor
    // DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
 
    DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
}