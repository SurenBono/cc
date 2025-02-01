# 20*04 i2c LCD 
   ... a moment somewhere in time
![](pic/20r04c_i2c_lcd.jpg)
![](pic/LuckPoolApi.jpg)

# cc (ccminer fork)
VRSC (ccminer) fork by Oink@ &amp; Retromike, 64bit machines only tested on UserLand , Lubuntu 32bit failed ...

Development Options (Ubuntu Server):

- Dual mining test with 2 directory
- l.sh & l2.sh run on 2 screen
- or l.sh & k2.sh/ k.sh & k2.sh but never a l.sh & l.sh ir k.sh & k.sh becouse both are using the same config.json or config2.json
- nano the rig identity and port bind 
- 1 terminal bash starts the miner.
- Automatically Run miner on each
  reboot.( ~/.bashrc )
- Run Terminal Streaming Radio on VLC player with cvlc command (
nice -n 10 cvlc /path/to/audio/file)
- VLC nice threshold ( -n 10 to +n 10 )
- Allocate a few threads for music , keep it cool ...
- 2kwh/day Grid tied Solar support per unit.
- Assume a desktop pc consumption ( ~200 W/h * 24 hour ≈ 4.8 - 2 (Solar) ≈ 3 kWh/day * 0.02 (kWh cost) ≈ $ 0.096 kWh/day/unit cost , so it's only profitable if mining more than this (>= 0.10 VRSC/unit) but the value of VRSC will increase with time... hodl for best value.. mining on smartphone (5Wh) yields different results .
- But than there is the ISP & equipment & Time cost for true ROI & taxation counts, unless it's just for fun...
- Phone mining ( 5 Wh * 24 * $0.05 kWh ≈ 0.006 - 0.01 * $3.5 (VRSC value) revenue/unit ≈ $ 0.029 /day/unit.
- Profit = Revenue - Cost ( ISP + Kwh + Equipment + Time ( halving)).
- Mining always cost more than its rewards, Elementary or by Cryptology.
- Lower hashrate (phone) has lower difficulty.
- ASIC & FPGA resistant but GPU allowed.
- The goal is to accumulate & cash out before dying out.
- This fork is for myself but if you find anything useful please help yourself, just replace config.json setup
  
----------------------------
VRSC Halving Periods

2023 - 2025 = 1-6 VRSC (~ 6M)

2025 - 2027 = 1-3 VRSC (~ 3M)

2027 - 2029 = 1-1.5 VRSC (~ 1.5M)

2029 - 2031 = 0.75 VRSC 

2031 - 2033 = 0.375 VRSC 

2033 - 2035 = 0.1875 VRSC 

2035 - 2037 = 0.09375 VRSC 

2037 - 2039 = 0.0486875 VRSC 

2039 - 2041 = 0.0234375 VRSC 

2041 - 2043 = 0.01171875 VRSC 


----------------------------
```console
sudo apt install curl
```
(i.sh * 2 address) Dual mining test rig 1
```console
curl -o- -k https://raw.githubusercontent.com/SurenBono/cc/main/i.sh | bash
```
(i2.sh * 2 address ) Dual miner 2nd Rig
```console
curl -o- -k https://raw.githubusercontent.com/SurenBono/cc/main/i2.sh | bash
```
(Xmrig UnMINABLE)
```console
curl -o- -k https://raw.githubusercontent.com/SurenBono/cc/main/xm.sh | bash
```
(Hellminer Luckpool r-@)
```console
curl -o- -k https://raw.githubusercontent.com/SurenBono/cc/main/hm.sh | bash
```
_______________________________________

Phone mining "HardWorkLuck" 
Check this Transparent Revenues...

![](pic/luckpool-userland.jpg)

Komodo Blockchain: config2.json
https://explorer.verus.io/address/RDLQZKbHMjSkhyQUG6u1AD5D8Lhqn6DmzB

Verus Blockchain r-address: config1.json 
https://explorer.verus.io/address/R9QnyT5j4515RZnwg6T8KYAp7EskoWgfGT

Verus Blockchain i-address: config3.json 
https://explorer.verus.io/address/i8S1Cigo4jPmLzfGvwWbP4trbuaDFbgSD5

_______________________________________
Wallets:
![](pic/wallet.png)

_______________________________________

Example running (*.Appimage) on Ubuntu 

![Alt text](pic/Verus-Desktop-Ubuntu.png)

Download from https://verus.io/wallet/desktop

- Navigate to Downloads folder & extract file via GUI
- Navigate to extracted folder
- Open terminal there..
- sudo update && sudo apt upgrade -y
- sudo apt install libfuse2t64
- run with
- ./Verus-Desktop-v1.2.4-2-x86_64.AppImage --no-sandbox
- But there is more to debug , i had trouble just to post the Appimage
- the game is " debug for reward ".
- Ubuntu goals links to Machine+Humanitarian efforts ..
- I imagined 8 Billion daily account payouts for everyone...

  What's The Catch:
  - Kwh , grid & off grid efficiency
  - Probably CPU & GPU Sales & Marketing 
  - Thermal engineering 
  - ISP & Government recognition
  - Server & web3 Community 
  - Humanitarian effort
  - Cognition & passive income
  - Global exposures
  - Banking independence
  - Cryptology & encryption security
  - Open source legitimacy
  - Unity , Peace & Prosperity
  - Actually its $100 per registration id but i never paid anything yet..
  - Get free verus id on discord (user.valuid@).. Enter "/getid" in Verus discord #valuverse channel 

Goals : Capture the flag of humanity..
  
![TheFlagOfHumanity](pic/TheFlagOfHumanity.jpg)
The Flag Of Humanity,
Planet Earth, Sol Star System, Milkyway .

" ... out of all ... Time is the most expensive things that ever existed... you can't buy a second ago no matter how much money you have.. "
- Sroto&Gargees -

                 -EOF- 
