#!/usr/bin/env bash

if [ $# -ne 3 ]; then
    echo "$0: usage: port jobs simultaneous_connections"
    exit 1
fi

./tcp_echo_server "$1" "$2" "$3" &

for _ in $(eval echo {1.."$2"});
do
./tcp_echo_client localhost "$1" "Hello World!" &
done
