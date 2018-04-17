#include<ESP8266WiFi.h>
#include<PubSubClient.h>
#define BAUD_RATE 9600

// MQTT parameters
#define MQTT_SERVER "192.168.43.1"
const char* ssid = "Akash";
const char* password = "astr1x2096";
const char* mqtt_username = "astr1x";
const char* mqtt_password = "astr1x2096";

// Topic to subscribe to for the commands
char* subTopic = "RCTank/ctrl";

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();


// Bot parameters
#define enMotorR 5
#define MotorR1 13
#define MotorR2 14
#define MotorL1 15
#define MotorL2 2
#define enMotorL 4

#define maxPWM 1023
#define chillPWM 768

String selectPWM = "chill";
String botPower = "off";

String cmd = "", runner = "";

WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, 1883, callback, wifiClient);

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(enMotorR, OUTPUT);
  pinMode(enMotorL, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  reconnect();

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(200);

  Serial.println("Setup Complete.");
}

void loop() {
  // Reconnect if connection is lost
  if (!client.connected() && WiFi.status() == 3)
    reconnect();

   botRunner();
   client.loop();
   // Must delay to allow ESP8266 WIFI functions to run
  delay(10);
}

void forward() {
  if(botPower == "on") {
    if(selectPWM == "max") {
      analogWrite(enMotorL, maxPWM);
      analogWrite(enMotorR, maxPWM);
    }
    else if(selectPWM == "chill") {
      analogWrite(enMotorL, chillPWM);
      analogWrite(enMotorR, chillPWM);
    }
    else {}
  
    digitalWrite(MotorR1, HIGH);
    digitalWrite(MotorR2, LOW);
  
    digitalWrite(MotorL1, HIGH);
    digitalWrite(MotorL2, LOW);
  }
  else if(botPower == "off")
    halt();
}

void reverse() {
  if(botPower == "on") {
    if(selectPWM == "max") {
      analogWrite(enMotorL, maxPWM);
      analogWrite(enMotorR, maxPWM);
    }
    else if(selectPWM == "chill") {
      analogWrite(enMotorL, chillPWM);
      analogWrite(enMotorR, chillPWM);
    }
    else {}
  
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, HIGH);
  
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, HIGH);
  }
  else if(botPower == "off")
    halt();
}

void left() {
  if(botPower == "on") {
    if(selectPWM = "max") {
      analogWrite(enMotorL, maxPWM);
      analogWrite(enMotorR, maxPWM);
    }
    else if(selectPWM == "chill") {
      analogWrite(enMotorL, chillPWM);
      analogWrite(enMotorR, chillPWM);
    }
    else {}
  
    digitalWrite(MotorR1, HIGH);
    digitalWrite(MotorR2, LOW);
  
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, HIGH);
  }
  else if(botPower == "off")
    halt();
}

void right() {
  if(botPower == "on") {
    if(selectPWM == "max") {
      analogWrite(enMotorL, maxPWM);
      analogWrite(enMotorR, maxPWM);
    }
    else if(selectPWM == "chill") {
      analogWrite(enMotorL, chillPWM);
      analogWrite(enMotorR, chillPWM);
    }
    else {}
  
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, HIGH);
  
    digitalWrite(MotorL1, HIGH);
    digitalWrite(MotorL2, LOW);
  }
  else if(botPower == "off")
    halt();
}

void halt() {
  analogWrite(enMotorL, 0);
  analogWrite(enMotorR, 0);
  
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
  
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
}

void botRunner() {
  if(runner == "F")
    forward();
  else if(runner == "B")
    reverse();
  else if(runner == "R")
    right();
  else if(runner == "L")
    left();
   else
    halt();
}

void reconnect() {

  //attempt to connect to the wifi if connection is lost
  if(WiFi.status() != WL_CONNECTED) {

    //loop while we wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      // Serial.print(".");
    }
  }

  //make sure we are connected to WIFI before attemping to reconnect to MQTT
  if(WiFi.status() == WL_CONNECTED){
  // Loop until we're reconnected to the MQTT server
    while (!client.connected()) {

      // Generate client name based on MAC address and last 8 bits of microsecond counter
      String clientName;
      clientName += "RCTankBot";

      //if connected, subscribe to the topic(s) we want to be notified about
      if (client.connect((char*) clientName.c_str(), mqtt_username, mqtt_password)) {
        //Serial.print("\tMQTT Connected");
        client.subscribe(subTopic);
      }
    }
  }
}

// MQTT callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // Convert topic to string to make it easier to work with
  String topicStr = topic;
  // We expect a reply 
  cmd = String((char *)payload).substring(0, length);
  Serial.println(cmd);
  if(cmd == "F") {
    runner = cmd;
  }
  else if(cmd == "B") {
    runner = cmd;
  }
  else if(cmd == "R") {
    runner = cmd;
  }
  else if(cmd == "L") {
    runner = cmd;
  }
  else if(cmd == "on") {
    botPower = cmd;
  }
  else if(cmd == "off") {
    botPower = cmd;
  }
  else if(cmd == "chill") {
    selectPWM = cmd;
  }
  else if(cmd == "max") {
    selectPWM = cmd;
  }
  yield();
}

