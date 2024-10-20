#!/bin/sh
sudo apt update -y && sudo apt upgrade -y &&
sudo apt install git build-essential cmake libuv1-dev libssl-dev libhwloc-dev -y &&
git clone https://github.com/xmrig/xmrig.git &&
mkdir xmrig/build && cd xmrig/build &&
cmake .. &&
make -j$(nproc) &&
cd ~

echo '#!/bin/bash' > ltc.sh
echo 'sudo apt update && sudo apt upgrade -y' >> ltc.sh
echo 'cd xmrig/build' >> ltc.sh
echo './xmrig -a gr -o stratum+ssl://ghostrider.unmineable.com:443 -u LTC:MGB9eB42n3RFJZEZf6ni74PKVnGfCeGonG.LTC_LUNO_01#xke0-omvl -p x -t 5' >> ltc.sh
chmod +x ltc.sh

echo '#!/bin/bash' > rtm.sh
echo 'sudo apt update && sudo apt upgrade -y' >> rtm.sh
echo 'cd xmrig/build' >> rtm.sh
echo './xmrig -a gr -o stratum+ssl://ghostrider.unmineable.com:443 -u RTM:RDLQZKbHMjSkhyQUG6u1AD5D8Lhqn6DmzB.RTM_KMD_01#737o-wx6f -p x -t 5' >> rtm.sh
chmod +x rtm.sh
