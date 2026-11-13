dir=$(pwd)
gcc main.c -o main
chmod +x main
mv main.sh seatbelt
su -c "mv \"$dir/seatbelt\" /usr/local/bin/"
