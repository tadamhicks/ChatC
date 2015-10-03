README

Included are a server and a client for 2-way TCP/IP chat.

"make"or "make all" will create binaries for both.  "make clean" will remove the
binaries.

Set up the server first, it listens on port 8888 by default, and echoes back
the host ip address when run.

Connect the client by passing the argument as follows:
./client <$HOSTNAME> 8888

If interfacing with other servers then specify requisite port numbers to
interface with them.


