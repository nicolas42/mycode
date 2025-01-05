# test.sh
# run like 'sh test.sh'
gcc server.c
./a.out &
PID=$!
telnet localhost 3490
kill $PID

