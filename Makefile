all : main.o ethernet.o ip.o tcp.o udp.o arp.o ftp.o ascii.o bootp.o dns.o http.o icmp.o print.o telnet.o smtp.o
	gcc main.o ethernet.o ip.o tcp.o udp.o ftp.o arp.o ascii.o bootp.c dns.o http.o icmp.o print.o telnet.o smtp.o -o all -Wall -Wextra -Werror -lpcap -g 

main.o : main.c ethernet.h ip.h
	gcc -c main.c -o main.o 

print.o : print.c print.h ip.h ethernet.h
	gcc -c print.c -o print.o

ethernet.o : ethernet.c ethernet.h ip.h print.h arp.h
	gcc -c ethernet.c -o ethernet.o

ip.o : ip.c ip.h udp.h tcp.h print.h icmp.h
	gcc -c ip.c -o ip.o

tcp.o : tcp.c tcp.h print.h http.h
	gcc -c tcp.c -o tcp.o

udp.o : udp.c udp.h print.h bootp.h dns.h 
	gcc -c udp.c -o udp.o

icmp.o : icmp.c icmp.h print.h
	gcc -c icmp.c -o icmp.o

http.o : http.c http.h print.h ip.h ascii.h
	gcc -c http.c -o http.o

ftp.o : ftp.c ftp.h print.h ip.h ascii.h
	gcc -c ftp.c -o ftp.o

smtp.o : smtp.c smtp.h ip.h print.h ascii.h
	gcc -c smtp.c -o smtp.o

arp.o : arp.c arp.h print.h ethernet.h ip.h
	gcc -c arp.c -o arp.o

dns.o : dns.c dns.h ip.h print.h
	gcc -c dns.c -o dns.o

bootp.o : bootp.c bootp.h print.h ip.h
	gcc -c bootp.c -o bootp.o

ascii.o : ascii.c ascii.h print.h
	gcc -c ascii.c -o ascii.o

telnet.o : telnet.c telnet.h print.h ip.h ascii.h
	gcc -c telnet.c -o telnet.o


clean:
	rm -rf *.o
