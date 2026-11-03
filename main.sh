

RED="\e[31m"
GREEN="\e[32m"
ENDCOLOR="\e[0m"

if [ "$1" = "-h" ]; then
  echo ""
  echo "Seatbelt - Slackware package tool"
  echo "---------------------------------"
  echo "-h = shows this"
  echo "-g = gets and installs"
  echo ""
fi

# Main Script
if [ "$1" = "-g" ]; then
  echo Connecting to Slackbuilds...
  ping -c 4 slackbuilds.org
  if [ $? -ne 0 ]; then
    echo -e "${RED}Couldn't connect to Slackbuilds, It could be at your end or Theirs ${ENDCOLOR}"
    exit 1
  fi
  cd /tmp/seatbelt
  if [ $? -ne 0 ]; then
    cd /tmp/
    mkdir seatbelt
    cd seatbelt/
  fi
  echo -e "${GREEN}DOWNLOAD THE SOURCE CODE AND THE SLACKBUILD${ENDCOLOR}"
  sleep 1
  links $2
  
fi

