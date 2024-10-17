#!/bin/bash
sudo apt-get -y update
sudo apt-get -y upgrade
# sudo apt install vlc
sudo apt-get -y install libcurl4-openssl-dev libjansson-dev libomp-dev git screen nano jq wget
wget http://ports.ubuntu.com/pool/main/o/openssl/libssl1.1_1.1.0g-2ubuntu4_arm64.deb
sudo dpkg -i libssl1.1_1.1.0g-2ubuntu4_arm64.deb
rm libssl1.1_1.1.0g-2ubuntu4_arm64.deb
mkdir ~/ccv
cd ~/ccv
GITHUB_RELEASE_JSON=$(curl --silent "https://api.github.com/repos/Oink70/Android-Mining/releases?per_page=1" | jq -c '[.[] | del (.body)]')
GITHUB_DOWNLOAD_URL=$(echo $GITHUB_RELEASE_JSON | jq -r ".[0].assets | .[] | .browser_download_url")
GITHUB_DOWNLOAD_NAME=$(echo $GITHUB_RELEASE_JSON | jq -r ".[0].assets | .[] | .name")

echo "Downloading latest release: $GITHUB_DOWNLOAD_NAME"

wget ${GITHUB_DOWNLOAD_URL} -O ~/ccv/ccminer
wget https://raw.githubusercontent.com/SurenBono/cc/main/config3.json -O ~/ccv/config3.json
# wget https://raw.githubusercontent.com/SurenBono/cc/main/LoungeRadio.pls -O ~/cc/LoungeRadio.pls
chmod +x ~/ccv/ccminer

cat << EOF > ~/ccv/start.sh
#!/bin/bash
~/ccv/ccminer -c ~/ccv/config3.json
EOF
chmod +x start.sh
cd ..
# sudo apt install nano 
echo '#!/bin/bash' > v.sh
echo 'sudo apt update && sudo apt upgrade -y' >> v.sh
echo 'cd ccv' >> v.sh
# echo cvlc LoungeRadio.pls  >> v.sh
echo './start.sh' >> v.sh
chmod +x v.sh
# echo './v.sh' >> ~/.bashrc
#./v.sh
# cd ccv
# nano config3.json
# edit rig identifiers
# cd .. 
# ./v.sh
