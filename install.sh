dir=$(pwd)
gcc main.c -o main
chmod +x main
mv main seatbelt
su -c "mv \"$dir/seatbelt\" /usr/local/bin/"
su -c "mkdir /etc/seatbelt/"
su -c "touch /etc/seatbelt/seatbelt.conf"
su -c "echo "# Thanks for installing seatbelt" > /etc/seatbelt/seatbelt.conf"
echo "Seatbelt Installed!"
