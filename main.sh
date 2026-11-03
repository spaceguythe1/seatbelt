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
  ping -c 4 slacbuilds.org
  if [ $? -ne 0 ]; then
     echo "Couldn't connect to Slackbuilds, It could be at your end or at Theirs"
     exit 1
  fi
fi

