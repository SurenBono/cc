#!/bin/bash
sudo apt-get -y update
sudo apt-get -y upgrade
# sudo apt install vlc
sudo apt-get install screen
sudo apt-get -y install libcurl4-openssl-dev libjansson-dev libomp-dev git screen nano jq wget
wget http://ports.ubuntu.com/pool/main/o/openssl/libssl1.1_1.1.0g-2ubuntu4_arm64.deb
sudo dpkg -i libssl1.1_1.1.0g-2ubuntu4_arm64.deb
rm libssl1.1_1.1.0g-2ubuntu4_arm64.deb
mkdir ~/cc
cd ~/cc
GITHUB_RELEASE_JSON=$(curl --silent "https://api.github.com/repos/Oink70/Android-Mining/releases?per_page=1" | jq -c '[.[] | del (.body)]')
GITHUB_DOWNLOAD_URL=$(echo $GITHUB_RELEASE_JSON | jq -r ".[0].assets | .[] | .browser_download_url")
GITHUB_DOWNLOAD_NAME=$(echo $GITHUB_RELEASE_JSON | jq -r ".[0].assets | .[] | .name")

echo "Downloading latest release: $GITHUB_DOWNLOAD_NAME"

wget ${GITHUB_DOWNLOAD_URL} -O ~/cc/ccminer
wget https://raw.githubusercontent.com/SurenBono/cc/main/config.json -O ~/cc/config.json
wget https://raw.githubusercontent.com/SurenBono/cc/main/config2.json -O ~/cc/config2.json
# wget https://raw.githubusercontent.com/SurenBono/cc/main/LoungeRadio.pls -O ~/cc/LoungeRadio.pls
chmod +x ~/cc/ccminer

cat << EOF > ~/cc/start.sh
#!/bin/bash
~/cc/ccminer -c ~/cc/config.json
EOF
chmod +x start.sh
cd ..
# sudo apt install nano 
echo '#!/bin/bash' > l.sh
echo 'sudo apt update && sudo apt upgrade -y' >> l.sh
echo 'cd cc' >> l.sh
# echo cvlc LoungeRadio.pls  >> l.sh
echo './start.sh' >> l.sh
chmod +x l.sh

cat << EOF > ~/k.sh
#!/bin/bash
sudo apt update && sudo apt upgrade -y
~/cc/ccminer -c ~/cc/config2.json
EOF
chmod +x k.sh

# echo './l.sh' >> ~/.bashrc
#./l.sh
# cd cc
# nano config.json
# edit rig identifiers
# cd .. 
# ./l.sh

