#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> // version 5

const char* ssid = "Arduino Wifi";
const char* password = "t*******1";
const char* url = "https://luckpool.net/verus/miner/R9QnyT5j4515RZnwg6T8KYAp7EskoWgfGT";
const char* crypto = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,bitget-token,cardano,ethereum,litecoin,ripple,solana,verus-coin,worldcoin-wld&vs_currencies=usd";

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
    
    Serial.println("LuckPoolRig: R9QnyT5j4515RZnwg6T8KYAp7EskoWgfGT");
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
	//lcd.setCursor(0,1);lcd.print("    Verus r-addr");
	float Verus = Paid + 0.0321854;
	lcd.setCursor(3,1);lcd.print(String(Verus,6)+" VRSC");
	float vrscUSD = Verus * verusPrice ;
	lcd.setCursor(5,3);lcd.print("USDT "+ String(vrscUSD,2));
	
	Serial.println("Verus r-addr Bal : " + String(Verus,6) + " VRSC =" + " USDT  "+ String(vrscUSD,2));
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
    while(client.connected() || client.available()) 
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
    float bgbPrice = root["bitget-token"]["usd"];
	  float ethPrice = root["ethereum"]["usd"];
	  float adaPrice = root["cardano"]["usd"];
	  float ltcPrice = root["litecoin"]["usd"];
	  float solPrice = root["solana"]["usd"];
	  
	  float xrpPrice = root["ripple"]["usd"];
	  float wldPrice = root["worldcoin-wld"]["usd"];
	  verusPrice = root["verus-coin"]["usd"];
  
    Serial.println("coingecko.com");
     
    Serial.print("BTC " + btcPrice);
    Serial.print("  ETH " + String(ethPrice,2));
    Serial.println("  SOL " + String(solPrice,2));
    Serial.print("  ADA " + String(adaPrice,2));
    
    Serial.print("  BGB " + String(bgbPrice,2));
    
    
    Serial.print("XRP " + String(xrpPrice,2));
    Serial.print("  WLD " + String(wldPrice,2));
    Serial.print("  VRSC " + String(verusPrice,2));
    Serial.println("  LTC " + String(ltcPrice,2));
    Serial.println("====================================================================================");
   
    lcd.clear();
    lcd.setCursor(0,0);lcd.print("BTC " + btcPrice);
    lcd.setCursor(10,0);lcd.print("ETH " + String{ethPrice,1});
    lcd.setCursor(0,1);lcd.print("SOL " + String(solPrice,1));
    lcd.setCursor(10,1);lcd.print("XRP " + String(xrpPrice,2));
    lcd.setCursor(0,2);lcd.print("ADA " + String(adaPrice,2));
    lcd.setCursor(10,2);lcd.print("WLD " + String(wldPrice,2));
    lcd.setCursor(0,3);lcd.print("VRC " + String(verusPrice,2));
    lcd.setCursor(10,3);lcd.print("LTC " + String(ltcPrice,2));
    
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
