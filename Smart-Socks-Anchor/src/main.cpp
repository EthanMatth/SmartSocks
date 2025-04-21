/*
Smart Socks Anchor Module
Used for Right foot
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
    
  esp_now_register_recv_cb(OnDataRecv);

}
 
void loop()
{
  //DW1000Ranging.loop();
  a_data.Big = analogRead(Analog_0);
  a_data.Little = analogRead(Analog_1);
  a_data.Heel = analogRead(Analog_2);

  Serial.printf("%d:%d:%d:%d:%d:%d:%.2f\n", 
  a_data.Big, a_data.Heel, a_data.Little, t_data.Big, t_data.Heel, t_data.Little, distance);

  delay(100);
}