<h1>This repository contains all the programs I have done in Computer Networks Laboratory Course of 5th Semester.</h1>

**School of Computer Engineering**

**KIIT deemed to be University**

**Laboratory Lesson Plan – Autumn 2024 (5<sup>th</sup> Semester)**

**Discipline:** CS/IT/CSCE/CSSE

**Course name and Code:** Computer Networks Laboratory, CS39003 (L-T-P-Cr:1)

**Course Contents:**

**List of experiments:**

**Lab 1: Week-1: Networking Tools**

**• Assignments**

1. Find the IP address of your computer. Try connecting to different service providers and notice the changes, if any, in the IP address of your machine.
2. How to send exactly 4 packets of size 100 bytes to [www.github.com](http://www.github.com)?
3. Run _traceroute_ via two or more service providers for [www.kiit.ac.in](http://www.kiit.ac.in) and report your observations, like if some paths default to IPv6 then how can you force traceroute to use IPv4, any private IP addresses routers that do not reply to requests, etc.
4. How can you limit the number of hops to 10 in a traceroute command?
5. How can you display statistics for all protocols using the netstat command?
6. Use nslookup to find the IP Address of [www.kiit.ac.in](http://www.kiit.ac.in) and [www.facebook.com](http://www.facebook.com)
7. How can you perform a reverse DNS lookup to find the domain name associated with the IP address 8.8.8.8?
8. How can you use nslookup to query <www.example.com> using the DNS server at 8.8.8.8?
9. How do you use the ipconfig command to display all current TCP/IP network configurations?
10. What are the ipconfig commands to release and renew an IP address on a Windows machine?
11. How do you use iptables to add a rule that allows all incoming HTTP traffic (port 80)?
12. How do you use iptables to block all incoming traffic from the IP address 192.168.1.100?

**Lab 2: Week-2: Overview of C Programming**

**• Assignments**

1\. Write a C program to swap the content of 2 variables entered through the

command line using function and pointer.

2\. Write a C program to assign values to each member of the following structure.

Pass the populated structure to a function Using call-by-value and another

function using call-by-address and print the value of each member of the

structure.

_struct student_info{_

_int roll_no;_

_char name \[50\];_

_float CGPA;_

_struct dob age;_

_};_

3\. Write a C program to extract each byte from a given number and store them in

separate character variables and print the content of those variables.

4\. Write a C Program to enter a number and store the number across the

following structure and print the content of each member of the structure.

Then aggregate each member of the structure to form the original number and

print the same.

_struct pkt {_

_char ch1;_

_char ch2\[2\];_

_char ch3;_

_};_

5\. Write a C program to check whether the Host machine is in Little Endian or

Big Endian. Enter a number, print the content of each byte location and

Convert the Endianness of the same i.e. Little to Big Endian and vice-versa.

**Lab 3: Week-3: Basics of Socket Programming**

**• Assignments**

1\. Write a sender and receiver program in C by passing the IP address and the

port number of each other through the command line arguments using

connection less socket. Both of them will exchange messages with each other

continuously. If any one of them will receive the “exit” message from the

other end then both of them will close the connection. (Assume both the client

and server are running with in the same host)

**Lab 4: Week-4: Connection Oriented Socket Programming**

**• Assignments**

Write a connection-oriented client and server program in C using command line

arguments. At the server side, pass the port number (to whom the server will bind

to) in the command line. At the client side, pass the IP address and the port

number of the server (to whom the client will connect to) as command line

argument and carry out the following tasks.

◦ After establishment of connection print the IP Address and port number of the

client to whom the server is connected now.

◦ Then exchange messages.

◦ After message exchange is over then the client sends a “close” message to the

server to tear down the connection.

**Lab 5: Week-5: Socket Programming with Multiple clients**

**• Assignments**

1\. Design a connection oriented concurrent chat server using fork () in C where

the server will serve multiple chart clients simultaneously. When the chat

server receives a “logout” message from a particular client then it terminates

the respective connection with that chat client.

**Lab 6: Week-6: Packet Analysis using Wireshark**

**• Assignments**

1. Start the Wireshark packet sniffer and start capturing packets. Then open a terminal and execute command **_ping -s 3500 ping-ams1.online.net -c 5._** After execution is complete stop the Wireshark capture and save the file for further analysis.

Answer the following questions based on above obersation -

- 1. How many total IP packets are exchanged in the communication between your host and the remote server representing **ping-ams1.online.net** ?
  2. What is the size of each ping request sent from your host to remote server?
  3. Make a table for each ping request packet sent from your host to remote, the respective field indicating it, if the request packet is fragmented or not. If packet is fragmented (add details of number of IP fragments and on each fragment), Time of sending each individual fragment/packet, length of the individual fragment/packet), time of receiving ping response, the respective field indicating if response packet is fragmented or not, if response packet is fragmented include the number of IP fragments, total actual length of data carried by the respective fragment in respective ping request and response.

1. Start the Wireshark again and execute command **_traceroute -q 5 ping-ams1.online.net 3500_** in the terminal. After execution is complete stop the Wireshark capture and save the file for further analysis.
2. Answer the following questions based on above observation -
    1. How many hops are involved in finding the route to this **ping-ams1.online.net**
    2. How many total IP packets are exchanged in the communication to get the final traceroute output of ping-ams1.online.net? How many of them are sent from client to remote machine (server/router)? How many of them are sent from the remote machine(hop/server/router) to the local client? Tabulate this with an entry for a router/server and the client too.
    3. Which fields in the IP datagram always change from one datagram to the next within this series of IP packets send by your host/client? Which fields stay constant? Which of the fields must stay constant? Which fields must change? Why?

**Lab 7 : Week-7: Introduction to Network Simulators**

**• Assignments**

1\. Simulate routing of packets in a LAN with in the same subnet.

2\. Simulate routing of packets in a LAN with different subnets.

**Lab 8: Week - 8: Simulating network protocols in Network Simulators**

- Cover DHCP Protocol.
- Create a network in simulator and demonstrate DHCP Protocol in that network.

**Lab 9: Week-9**

**• Assignments**

1\. Write a connection-oriented client and server socket program using C where

the client will suppose to send a large buffer to the server. Keeping

fragmentation and reassembly into account the following functionality needs

to be supported.

Fragmentation functionality

• First client needs to find the MTU size of its own and display the same.

• Based on the MTU size it will decide whether to fragment the data or not

and display the message accordingly.

• In case of fragmentation, first find the number of fragments required and

display the same.

• Prepare each fragment with the following information and display the

same.

1\. Id (Identification number)

2\. flag (More fragments flag)

3\. offset (Fragmentation offset)

4\. HL (Header Length)

5\. TL (Total Length)

6\. payload (Data)

• Send all the fragments to the server.

Reassembly functionality

• First server needs to find whether the received datagram is a fragmented

one or not and display the same.

• Continue receiving all the fragments belonging to a fraction of the same

data till the last fragment and display all the fragments data with their

details.

• Then follow the below steps to start the reassembly procedure

1\. first find out the first fragment.

2\. Calculate the offset of the next fragment and check whether the

next fragment is available or not.

3\. If available, repeat step-2 till flag value 0 or else display a

appropriate error.

• Finally display the assembled datagram.

**Lab 10: Week-10**

**• Assignments**

1\. Implement stop-and-wait protocol on top of UDP sockets using C program.

2\. Implement Go-back-N protocol on top of UDP sockets using C program.

**Lab 11: Week-11 (Optional)**

**• Assignments**

Write a connection-oriented client and server program in C using command line

Arguments.

Apply appropriate encryption techniques for secure communication.

**Lab 12: Week-12 (Optional)**

**• Assignments**

1. Compare and analyze different routing protocol using network simulator.
