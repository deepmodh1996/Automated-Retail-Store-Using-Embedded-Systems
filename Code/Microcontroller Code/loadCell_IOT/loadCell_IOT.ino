#include <AWS_IOT.h>
#include <WiFi.h>

#include "HX711.h" 
 
#define DOUT  4
#define CLK  2
 
HX711 scale(DOUT, CLK);

float calibration_factor = -156650; 
float prevWeight = 0;
float currWeight = 0;
float offSet = 0;
int quantity = 0;

AWS_IOT hornbill;

char WIFI_SSID[]="vivo 1713";
char WIFI_PASSWORD[]="123456789a";
char HOST_ADDRESS[]="ahmo7im3cb470.iot.ap-southeast-1.amazonaws.com";
char CLIENT_ID[]= "4";
char TOPIC_NAME[]= "weightHello";


int status = WL_IDLE_STATUS;
int tick=0,msgCount=0,msgReceived = 0;
char payload[4096];
char rcvdPayload[4096];
char wifiSignal[512];

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}

String getRSSI() {
  byte available_networks = WiFi.scanNetworks();
String answer = "[";
  for (int network = 0; network < available_networks && network < 2; network++) {
    if (network != 0) {answer = String(answer + ",");}
    answer = String(answer + "{'BSSID':'");
   answer = String(answer + WiFi.BSSIDstr(network));
answer = String(answer + "','strength':");
   answer = String(answer + String(WiFi.RSSI(network)));
   answer = String(answer + "}");
   
  }
  answer = String(answer + "]");
  return answer;
}

void setup() {
    Serial.begin(9600);
    delay(2000);

    scale.set_scale();
  scale.tare(); //Reset the scale to 0
 
  long zero_factor = scale.read_average(); //Get a baseline reading
scale.set_scale(calibration_factor); //Adjust to this calibration factor
    Serial.println("HX711 Calibration done");


    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(WIFI_SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        // wait 5 seconds for connection:
        delay(5000);
    }

    Serial.println("Connected to wifi");

    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0)
    {
        Serial.println("Connected to AWS");
        delay(1000);

        if(0==hornbill.subscribe(TOPIC_NAME,mySubCallBackHandler))
        {
            Serial.println("Subscribe Successfull");
        }
        else
        {
            Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
            while(1);
        }
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(2000);
offSet = scale.get_units();
tick = 5;

}

void loop() {
Serial.print("Reading: ");
scale.set_scale(calibration_factor);
currWeight = scale.get_units() - offSet;
  Serial.print(currWeight);
  Serial.print(" kg"); 
  Serial.println();
  if( currWeight < 4 && currWeight > -0.20 && (currWeight - prevWeight)*(currWeight - prevWeight)>0.25 && (currWeight < prevWeight)) { // 4 : maximum weight possible on shelf (here 4 bottles)
    // 0.25 
    Serial.println("picked something");
    quantity = (prevWeight - currWeight)/0.8; // 0.8 is weight of water bottle
    tick = 2;
  }
  
  
    if(msgReceived == 1)
    {
        msgReceived = 0;
        Serial.print("Received Message:");
        Serial.println(rcvdPayload);
    }
    if(tick == 5) {
      tick = 5;
    }
    else{
     
    tick = 2; 
    }
if (tick < 3)
    {
        tick=5;


String RSSIvalues = getRSSI();
        String payLoadJson = "{'messageType':'weightChange','productID':'Bottle','quantity':";
        payLoadJson = String(payLoadJson + String(quantity));
        payLoadJson = String(payLoadJson  + ",'wifiSignal':");
        payLoadJson = String(payLoadJson + RSSIvalues);
        payLoadJson = String(payLoadJson + "}");
        char tpayload[payLoadJson.length()+1];
        payLoadJson.toCharArray(tpayload, sizeof(tpayload));

        if(hornbill.publish(TOPIC_NAME,tpayload) == 0)
        {        
            Serial.print("Publish Message:");
            Serial.println(tpayload);
        }
        else
        {
            Serial.println("Publish failed");
            tick = 2;
        }
    }  
    vTaskDelay(1000 / portTICK_RATE_MS); 

if (currWeight < 4 && currWeight > -0.20) {
prevWeight = currWeight;
}
}