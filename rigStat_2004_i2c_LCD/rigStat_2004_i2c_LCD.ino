#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* ssid = "Arduino Wifi";
const char* password = "xxxxxxxx";
const char* url = "https://luckpool.net/verus/miner/RDLQZKbHMjSkhyQUG6u1AD5D8Lhqn6DmzB";
const char* crypto = "https://api.coingecko.com/api/v3/simple/price?ids=litecoin,verus-coin&vs_currencies=usd";
//const char fingerprint[] PROGMEM = "2c ec 15 a1 14 bd 14 78 a8 63 4d 7d 23 c3 7e 6b 38 87 05 ae";

LiquidCrystal_I2C lcd(0x27, 20, 4);
WiFiClientSecure client;
String result,price;
int cursorPosition=0;

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  lcd.print("  Connecting...");
  Serial.println("Connecting...");
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);lcd.setCursor(cursorPosition,1); 
    lcd.print(".");
    cursorPosition++;
    Serial.print('>');
    }
  lcd.clear();
  lcd.print("     Connected!");
  lcd.setCursor(0,2);
  lcd.print("   Fetching Data..");
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("------------------------------------------------");

  //client.setFingerprint(fingerprint);
  client.setInsecure();
}

void fetchRig() {
  
  Serial.println("2 min Updates from luckpool.net...");
  if (client.connect("luckpool.net", 443)) {
    
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: luckpool.net\r\n" + "User-Agent: ArduinoWiFi/1.1\r\n"+ 
                 "Connection: close\r\n\r\n");}  

     else {Serial.println("connection failed");lcd.setCursor(0,2);lcd.print("   luckpool.net!");Serial.println();}

    while(client.connected() && !client.available()) delay(1); 
    while (client.connected() || client.available()) 
    {char c = client.read(); result = result+c;}

    client.stop();
    String jsonData = extractRIG(result); 
    //Serial.println(jsonData);
    Serial.println();

    char jsonArray [jsonData.length()+1];
    jsonData.toCharArray(jsonArray,sizeof(jsonArray));
    jsonArray[jsonData.length() + 1] = '\0';

  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);
  if (!root.success())
  {Serial.println(" ...Rig parse failed!");}

    String Hash  = root["hashrateString"];
    float Share = root["shares"];
    float Immature = root["immature"];
    float Unpaid = root["balance"];
    float Paid = root["paid"];
    Serial.println("====================================================================================");
    Serial.println("KomodoWalletRig: RDLQZKbHMjSkhyQUG6u1AD5D8Lhqn6DmzB");
    Serial.print  ("Hash: " + Hash);
    Serial.print  ("  Share: " + String(Share,2));
    Serial.print  ("  Immature: " + String(Immature,4));
    Serial.print  ("  Unpaid: "   + String(Unpaid,4));
    Serial.println("  Paid: "     + String(Paid,4));
    Serial.println("====================================================================================");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(Hash);
    lcd.print(" Shr: "+ String(Share,2));
    lcd.setCursor(0,1);
    lcd.print("Imt  : " + String(Immature,8));
    lcd.setCursor(0,2);
    lcd.print("Bal  : "  + String(Unpaid,8));
    lcd.setCursor(0,3);
    lcd.print("Paid : " + String(Paid,8));
    result="";jsonData ="";
   delay(1000);
  } 

void fetchPrice(){

  //Serial.println();
  //Serial.println("Connecting to coingecko.com...");
  
  if (client.connect("api.coingecko.com", 443)) {
  
      client.print(String("GET ") + crypto +  " HTTP/1.1\r\n" +
                  "Host: api.coingecko.com\r\n" + "User-Agent: ArduinoWiFi/1.1\r\n"+ 
                  "Connection: close\r\n\r\n");}   
   
                   else {Serial.println("connection failed"); Serial.println();}

    while(client.connected() && !client.available()) delay(1); 
    while (client.connected() || client.available()) 
    {char d = client.read(); price = price+d;}

    client.stop();
    String jsonPrice = extractPrice(price);  
    //Serial.println(price);
    
    char jsonArray2 [jsonPrice.length()+1];
    jsonPrice.toCharArray(jsonArray2,sizeof(jsonArray2));
    jsonArray2[jsonPrice.length() + 1] = '\0';

  StaticJsonBuffer<500> json_buf2;
  JsonObject &root = json_buf2.parseObject(jsonArray2);
  if (!root.success())
  {Serial.println("...parse price failed!");Serial.println();}

      float litecoinPrice = root["litecoin"]["usd"];
      float verusPrice = root["verus-coin"]["usd"];
  
      Serial.println("coingecko.com");
      Serial.print("VRSC " + String(verusPrice,2));
      Serial.println("    LTC " + String(litecoinPrice,2));
      Serial.println("====================================================================================");
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("     VRSC " + String(verusPrice,2));
      lcd.setCursor(0,2);
      lcd.print("     LTC " + String(litecoinPrice,2));
      price="";jsonPrice="";
      Serial.println();
      delay(5000);
}

String extractRIG(const String& result) {
  
  int jsonStart = result.indexOf('{');
      if (jsonStart != -1) { return result.substring(jsonStart); }
      return ""; 
}

String extractPrice(const String& price) {
  
  int jsonStart = price.indexOf('{');
      if (jsonStart != -1) {return price.substring(jsonStart); }
  return ""; // Return empty string if no JSON found
}

void loop() {fetchPrice();fetchRig();delay(60000);}

// -EOF-
