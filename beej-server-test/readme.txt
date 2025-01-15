Testing Beej's Guide to Network Programming on AWS EC2 t2.nano
------------------------------------------------------------------

from https://beej.us/guide/bgnet/html/index-wide.html#a-simple-stream-server

This are notes about what was done.  

Successfully run the stream server example from Beej's Guide and test using Telnet on an EC2 t2.nano instance.

Launch a new ec2 instance.  I chose the cheapest t2.nano with AWS Linux.  Create a public-private security key or associated an existing one that you have.  I'm using a pem file.

I opened ports for http and https serving for future use and 
had to create a security group for port 3490 which is used in this example.
security groups > create new > add a rule to let through the firewall inbound tcp traffic from any ip address going through port [port].  tcp [port] 0.0.0.0/0.

Then you gotta add that security rule to the instance.
Go to instances section.  Actions > security > change security group.  You can just add this additional security group.  An instance can have multiple.

Check to see that your security group and instance are in the same VPC - virtual private cloud.  Mine seemed to be by default.  Apparently this is best practice.

To ssh into the elastic compute instance use ssh with a pem key that you should have created or associated with it when it was created or something.  


ssh -i [publickey].pem ec2-user@[ip-or-url]

The public security key needs the proper access permissions before doing it.  
chmod 400 [publickey].pem

On the server get your c compiler.

sudo yum install gcc

I use nano to create the c file for the server. 
nano server.c

gcc server.c
./a.out

The server should be running on the ...server.

If you run this from another computer it should send you hello world :)
telnet [ip-address-or-url] [port]

Amazon calls the url a dns (domain name system) which I guess is technically correct.


Trying [ip address]...
Connected to [dns]
Escape character is '^]'.
Hello, world!Connection closed by foreign host.



To keep a program running after you exit the ssh session use nohup or perhaps screen.
This will also keep it running after you exit the terminal.  


# Testing in unix terminal

gcc server.c; ./a.out &; PID=$!;
telnet localhost 3490

...
kill $PID






File descriptors are unix abstractions for things that can be written to and read from
like files, sockets, devices, processes, etc.  Plan 9 (the unix successor that never took off)
uses an even more filey interface for interacting with these kinds of things.

Anyway, this is the quintessential network socket server which uses 'two' main file descriptors
a listen file descriptor and a new file descriptor that is created for each incoming tcp connection.
So in the end you get the original listen file descriptor plus an additional file descriptor per open connection.

The program accepts an incoming connection on the 'listen' file descriptor.
It then creates a new file descriptor for the incoming connection to communicate on and deals with it in a new process,
leaving the original program to go back to listening for other incoming connections.





Nohup Basic Usage
---------------------------------------------------------------

To run it with nohup

nohup ./a.out &

See output of program
tail nohup.out

This will avoid the program exiting when you exit the terminal session.

Kill the background process with something like

Get the process id (pid) with something like 
ps | grep a.out

Kill the background process with
kill [pid]





Screen - Basic Usage
---------------------------------------------------------------


Here's how to use screen with its most basic functionality:

Start a Session:
Type screen in your terminal to start a new session.
Detach from Session:
Press Ctrl + A then D to detach and leave the session running in the background.
List Running Sessions:
Type screen -ls to see all your running screen sessions.
Reattach to a Session:
Use screen -r to reattach to the session if there's only one, or screen -r <sessionID> if you have multiple.
End a Session:
From within the session, type exit or press Ctrl + D.

This covers the essentials for using screen to manage a single terminal session.
