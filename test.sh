#!/bin/bash

# IRC server information
SERVER="localhost"
PORT=6667
CHANNEL="#cha1"
MESSAGE="Hello from the script!"

# Function to connect to IRC and send a message
connect_and_send() {
  { 
    echo "PASS pass"
    echo "NICK $1"
    echo "USER $1 0 * :$1"
    sleep 2  # Give time for server processing

    echo "JOIN $CHANNEL"
    sleep 2  # Give time for channel join

    echo "PRIVMSG $CHANNEL :$MESSAGE"
    sleep 2  # Give time for message to be sent

    echo "QUIT"
  } | nc $SERVER $PORT
}

# Run 100 instances in the background
for i in {1..10}; do
  connect_and_send "User$i" &
done

# Wait for all background processes to finish
wait

dfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfddfd