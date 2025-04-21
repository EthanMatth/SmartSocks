/*
Smart Socks Tag Module
Used for Left foot
*/

#include "main.h"


 
void setup()
{
    Serial.begin(115200);
    while(!Serial);
    //init the configuration
    //DW1000Setup();
    WiFi.mode(WIFI_STA);

    if(esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing");
        return;
    }

    esp_now_register_send_cb(OnDataSent);

    memcpy(peerInfo.peer_addr, anchorAddr, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if(esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }

}
 
void loop()
{
    //DW1000Ranging.loop();
    t_data.Big = analogRead(Analog_0);
    t_data.Little = analogRead(Analog_1);
    t_data.Heel = analogRead(Analog_2);

    esp_err_t result = esp_now_send(anchorAddr, (uint8_t*) &t_data, sizeof(t_data));

    if(result == ESP_OK)
    {
        Serial.println("Success");
    } else
        Serial.println("Error");
  
    delay(1000);
}

