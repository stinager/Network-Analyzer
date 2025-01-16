# Network-Analyzer - School Project

## Code Usage:
To generate and build the executable:
```bash
make
```

To execute the program:
```bash
 ./all -i <interface> -v<1 2 or 3> -o <filename> -f <filter> 
```
However, it is not mandatory to include all options. In this case, default parameters will be applied.

### Features:
The following four options -i, -o, -v, and -f are available:

- -o: Allows reading a pcap file and decoding frames (useful for testing specific protocols).
- -i: Allows you to choose the interface to listen on.
- -v: Allows you to select the verbosity level (1: very concise by default).
- -f: Allows you to filter traffic.
  
### Supported Protocols:
The following protocols are supported and processed:

- Ethernet
- IP
- UDP
- TCP
- ICMP
- ARP
- BOOTP and DHCP
- DNS
- HTTP(S)
- FTP (server and client)
- SMTP(S)
- Telnet
- POP/IMAP (detection and hexadecimal/ASCII display)

