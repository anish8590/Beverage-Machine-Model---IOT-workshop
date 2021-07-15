/*************************************************
* Include Libraries
*************************************************/
#include "UbidotaESPMQTT.h"
#include "pubSubClient.h"

/************************************************
*Define Constants
************************************************/
#include<NTPClient.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiUdp.h>

int count =0;
#define Relay1				D6
#define Relay2				D5
#define Relay3				D2
#define Relay4				D1
#define TOKEN "BBFF-hb9cb0FTTg4jYoQWZzvNADW32MH3x8"	 //Your Ubidots TOKEN
#define WIFI_SSID "Vibha"  //Your SSID
#define WIFI_PASS "vibha123"   //Your WiFi Pass
#define AIO_SERVER			"io.adafruit.com"
#define AIO_SERVERPORT   1883						//use 8883 for SSL 
#define AIO_USERNAME     "RahulBabu"				//Replce it with your username
#define AIO_KEY         "17eb583bfc4a4d7fa6cd4c94d6742664"		//Replace with your project Auth Key

WiFiClint client1;
Ubidots clint(TOKEN);

Adafruit_MQTT_Client mqtt(&client1,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);
Adafruit_MQTT_Client mqtt(&client1,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);
Adafruit_MQTT_subscriber Light1 = Adafruit_MQTT_subscriber(&mqtt, AIO_USERNAME  "/feeds/Relay1");  //FeedName
Adafruit_MQTT_subscriber Light2 = Adafruit_MQTT_subscriber(&mqtt, AIO_USERNAME  "/feeds/Relay2");
Adafruit_MQTT_subscriber Light3 = Adafruit_MQTT_subscriber(&mqtt, AIO_USERNAME  "/feeds/Relay3");
Adafruit_MQTT_subscriber Light4 = Adafruit_MQTT_subscriber(&mqtt, AIO_USERNAME  "/feeds/Relay4");

conat long utc0ffsetInSeconds = 19800;

// Define NIP Clients to get time
WiFiUDP ntpUDP;
NTPClients timeClent(ntpUDP, "pool.ntp.org", utc0ffsetInSeconds);

/*********************************************
* Auxiliar Functions
*********************************************/

void callback(char* topic, byte* payload, unsigned int length)  {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("]");
	for (int i=0;i<length;i++); {
		Serial.print((char)payload(i));
	}
	Serial.println();
}
void MQTT_connect();
/*********************************************
* Main Functions
*********************************************/

void setup() {
	//put your setup code here ,to run once:
	//client.ubiotaSetBroker("induatrial.ap1.ubidots.com"); //Seta the broker properly for the industrial account
	client.setDebug(true): //Pass a true or false bool value to activate debug messages
	Serial.begin(9600);
	client.wifiConnection(WIFI_SSID,WIFI_PASS);
	timeClient.begin();

	pinmode(Relay1, OUTPUT);
	pinmode(Relay2, OUTPUT);
	pinmode(Relay3, OUTPUT);
	pinmode(Relay4, OUTPUT);

	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(WIFI_SSID);
	WiFi.begin(WIFI_SSID,  WIFI_PASS);
	WHILE (WIFI.STATUS() !=WL_CONNECTED) {
	  delay(500);
	  Serial.println(",");
	}
	Serial.println();
	
	Serial.println("WiFI connected");
	Serial.println("IP address: ");
	Serial.println(wiFi.localIP());

	//Setup MQTT subscription for onoff feed.
	nqtt.subscribe(&Light1);
	nqtt.subscribe(&Light2);
	nqtt.subscribe(&Light3);
	nqtt.subscribe(&Light4);

	client.begin(callback);
}

nqtt.subscMribe(&Light4);

	
void loop(){
	MQTT_connect();
	// put your main code here, to run repeatedly:
	if(!client.connected()) {
	 client.reconnect();
	}
Adafruit_MQTT_Subscribe *subscription;
while (subscrition=mqtt.readSubscription(2000))) {
if (subscription==&Light) {
    Serial.print(F("Got: "));
    Serial.println((char *)Light1.lastread);
    int Light1_State=atoi(char *)Light1. lastread);
    digitalwrite(Relay1,Light1_State);
    delay(100000);
    digitalWrite(Relay1,LOW);


    }
    if (subscription ==&Light2) {
    	serial.print(F("Got: "));
    	Serial.println((char *)Light2.lastread);
    	int Light1_State=atoi(char *)Light2. lastread);
    	digitalwrite(Relay2,Light2_State);
    	delay(100000);
    	digitalWrite(Relay2,LOW);
    }
    if (subscription ==&Light3) {
    	serial.print(F("Got: "));
    	Serial.println((char *)Light3.lastread);
    	int Light1_State=atoi(char *)Light3. lastread);
    	digitalwrite(Relay3,Light3_State);
    	delay(100000);
    	digitalWrite(Relay3,LOW);
    }
    if (subscription ==&Light4) {
    	serial.print(F("Got: "));
    	Serial.println((char *)Light4.lastread);
    	int Light1_State=atoi(char *)Light4. lastread);
    	digitalwrite(Relay4,Light4_State);
    	delay(100000);
    	digitalWrite(Relay4,LOW);
    }
   }
   float value1= timeClient.getSecond();
   client.add("Time",value1);
   client.ubiodotPublish("Coffee");
   clint.loop;
 }

 void MQTT_connect() {
 int8_t ret;
 //Stop if already connected
 if (mqtt.connected()) {
 return;
 } 
 Serial.print("Connecting to MQTT....");
 unit8_ retries=3;

 while ((ret=mqtt.connect())!=0) {
 	Serial.println(mqtt.connectErrorString(ret));
 	Serial.println("Retrying MQTT connection in 5 seconds....");
 	mqtt.disconnect();
 	delay(50000);
 	if (retries==o) {
 	while(1);
   }
 }
Serial.println("MQTT Connected!");
}