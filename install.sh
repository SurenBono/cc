#!/bin/bash
sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y install libcurl4-openssl-dev libjansson-dev libomp-dev git screen nano jq wget
wget http://ports.ubuntu.com/pool/main/o/openssl/libssl1.1_1.1.0g-2ubuntu4_arm64.deb
sudo dpkg -i libssl1.1_1.1.0g-2ubuntu4_arm64.deb
rm libssl1.1_1.1.0g-2ubuntu4_arm64.deb
mkdir ~/ccminer
cd ~/ccminer
GITHUB_RELEASE_JSON=$(curl --silent "https://api.github.com/repos/Oink70/Android-Mining/releases?per_page=1" | jq -c '[.[] | del (.body)]')
GITHUB_DOWNLOAD_URL=$(echo $GITHUB_RELEASE_JSON | jq -r ".[0].assets | .[] | .browser_download_url")
GITHUB_DOWNLOAD_NAME=$(echo $GITHUB_RELEASE_JSON | jq -r ".[0].assets | .[] | .name")

echo "Downloading latest release: $GITHUB_DOWNLOAD_NAME"

wget ${GITHUB_DOWNLOAD_URL} -O ~/ccminer/ccminer
wget https://raw.githubusercontent.com/SurenBono/cc/main/config2.json -O ~/ccminer/config2.json
chmod +x ~/ccminer/ccminer

cat << EOF > ~/ccminer/start.sh
#!/bin/sh
~/ccminer/ccminer -c ~/ccminer/config2.json
EOF
chmod +x start.sh
cd ..
# sudo apt install nano 
echo '#!/bin/bash' > l2.sh
echo 'sudo apt update && sudo apt upgrade -y' >> l2.sh
echo 'cd ccminer' >> l2.sh
echo './start.sh' >> l2.sh
chmod +x l2.sh
# echo './l2.sh' >> ~/.bashrc
#./l2.sh
# cd ccminer
# nano config2.json
# edit rig identifiers 
# cd .. 
# ./l2.sh
