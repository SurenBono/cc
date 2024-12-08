#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> // version 5

const char* ssid = "Arduino Wifi";
const char* password = "xxxxxxxx";
const char* url = "https://luckpool.net/verus/miner/RDLQZKbHMjSkhyQUG6u1AD5D8Lhqn6DmzB";
const char* crypto = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,cardano,coinex-token,curve-dao-token,komodo,litecoin,matic-network,stellar,verus-coin&vs_currencies=usd";

//const char fingerprint[] PROGMEM = "2c ec 15 a1 14 bd 14 78 a8 63 4d 7d 23 c3 7e 6b 38 87 05 ae";

LiquidCrystal_I2C lcd(0x27, 20, 4);
WiFiClientSecure client;

String result,price,jsonData,jsonPrice;
float verusPrice;
int cursorPosition=0;

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  lcd.print("   Connecting...");
  Serial.println("Connecting...");
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);lcd.setCursor(cursorPosition,1); 
    lcd.print(".");cursorPosition++;Serial.print('>');
    }
	
  lcd.clear();
  lcd.print("     Connected!");
  lcd.setCursor(1,1);
  delay(1000);
  lcd.setCursor(1,2);
  lcd.print("  Fetching Data..");
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("====================================================================================");

  //client.setFingerprint(fingerprint);
  client.setInsecure();
}

void fetchRig() {
  
  if (client.connect("luckpool.net", 443)) {
    
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: luckpool.net\r\n" + "User-Agent: ArduinoWiFi/1.1\r\n"+ 
                 "Connection: close\r\n\r\n");}  

    else {Serial.println("connection failed");lcd.setCursor(0,2);lcd.print("   luckpool.net!");}

    while(client.connected() && !client.available()) delay(1); 
    while (client.connected() || client.available()) 
    {char c = client.read(); result = result+c;}

    client.stop();
    jsonData = extractRIG(result); 
    //Serial.println(jsonData);

    char jsonArray [jsonData.length()+1];
    jsonData.toCharArray(jsonArray,sizeof(jsonArray));
    jsonArray[jsonData.length() + 1] = '\0';

  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);
  if (!root.success())
  {Serial.println("...Rig parse failed!");lcd.clear();("...reparsing rig data");}

    else {
    String Hash  = root["hashrateString"];
    float Share = root["shares"];
    float Immature = root["immature"];
    float Unpaid = root["balance"];
    float Paid = root["paid"];
    
    Serial.println("LuckPoolRig: RDLQZKbHMjSkhyQUG6u1AD5D8Lhqn6DmzB");
    Serial.print  ("Hash: " + Hash);
    Serial.print  ("  Share: " + String(Share,2));
    Serial.print  ("  Immature: " + String(Immature,4));
    Serial.print  ("  Unpaid: "   + String(Unpaid,4));
    Serial.println("  Paid: "     + String(Paid,4));
    Serial.println("====================================================================================");
   
    lcd.clear();
    lcd.setCursor(0,0);lcd.print(Hash);
    lcd.setCursor(9,0);lcd.print("Shr: "+ String(Share,0));
    lcd.setCursor(0,1);lcd.print("Imt  : " + String(Immature,8));
    lcd.setCursor(0,2);lcd.print("Bal  : "  + String(Unpaid,8));
    lcd.setCursor(0,3);lcd.print("Paid : " + String(Paid,8));

	delay(40000);
	
	lcd.clear();
	//lcd.setCursor(0,1);lcd.print("    Komodo Wallet");
	float Komodo = Paid - 0.58374849;
	lcd.setCursor(3,1);lcd.print(String(Komodo,6)+" VRSC");
	float vrscUSD = Komodo * verusPrice ;
	lcd.setCursor(5,3);lcd.print("USDT "+ String(vrscUSD,2));
	
	Serial.println("Komodo Wallet Bal : " + String(Komodo,6) + " VRSC =" + " USDT  "+ String(vrscUSD,2));
        Serial.println("====================================================================================");

	delay(10000);}
   
  price="";jsonPrice="";result="";jsonData ="";
   
  } 

void fetchPrice(){

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
    jsonPrice = extractPrice(price);  
    //Serial.println(price);
    
    char jsonArray2 [jsonPrice.length()+1];
    jsonPrice.toCharArray(jsonArray2,sizeof(jsonArray2));
    jsonArray2[jsonPrice.length() + 1] = '\0';

  StaticJsonBuffer<500> json_buf2;
  JsonObject &root = json_buf2.parseObject(jsonArray2);
  if (!root.success())
  {Serial.println("...parse price failed!");Serial.println();lcd.clear();("...reparsing price");}

else{
  
    String btcPrice = root["bitcoin"]["usd"];
	  float adaPrice = root["cardano"]["usd"];
	  float cexPrice = root["coinex-token"]["usd"];
	  float crvPrice = root["curve-dao-token"]["usd"];
	  float matPrice = root["matic-network"]["usd"];
	  float xlmPrice = root["stellar"]["usd"];
	  float kmdPrice = root["komodo"]["usd"];
    float litecoinPrice = root["litecoin"]["usd"];
          verusPrice = root["verus-coin"]["usd"];
  
    Serial.println("coingecko.com");
     
    Serial.print("BTC " + btcPrice);
    Serial.print("  ADA " + String(adaPrice,2));
    Serial.print("  KMD " + String(kmdPrice,2));
    Serial.print("  CEX " + String(cexPrice,2));
    Serial.println("  CRV " + String(crvPrice,2));
    Serial.print("MAT " + String(matPrice,2));
    Serial.print("  XLM " + String(xlmPrice,2));
    Serial.print("  VRSC " + String(verusPrice,2));
    Serial.println("  LTC " + String(litecoinPrice,2));
    Serial.println("====================================================================================");
   
    lcd.clear();
    lcd.setCursor(0,0);lcd.print("CPTO/USD ");
    lcd.setCursor(10,0);lcd.print("BTC " + btcPrice);
    lcd.setCursor(0,1);lcd.print("ADA " + String(adaPrice,2));
    lcd.setCursor(10,1);lcd.print("KMD " + String(kmdPrice,2));
    lcd.setCursor(0,2);lcd.print("CRV " + String(crvPrice,2));
    lcd.setCursor(10,2);lcd.print("CEX " + String(cexPrice,2));
    lcd.setCursor(0,3);lcd.print("VRC " + String(verusPrice,2));
    lcd.setCursor(10,3);lcd.print("LTC " + String(litecoinPrice,2));
    
    delay(15000);
    }
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

void loop() {fetchPrice();fetchRig();}

// -EOF-
