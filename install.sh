dir=$(pwd)
chmod +x main.sh
mv main.sh seatbelt
su -c "mv \"$dir/seatbelt\" /usr/local/bin/"
