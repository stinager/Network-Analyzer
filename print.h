#include <stdio.h>
#include <stdint.h>
#include <linux/if_ether.h>
#include <sys/types.h>

extern int verbosity;

#define printf1(format, ...) if(verbosity >= 1) {printf(format, __VA_ARGS__);}
#define printf2(format, ...) if(verbosity >= 2) {printf(format, __VA_ARGS__);}
#define printf3(format, ...) if(verbosity >= 3) {printf(format, __VA_ARGS__);}

void putchar1(int c);
void putchar2(int c);
void putchar3(int c);

void print1(const char *str);
void print2(const char *str);
void print3(const char *str);

void print_ether_address1(u_int8_t ether_addr[ETH_ALEN]);
void print_ether_address2(u_int8_t ether_addr[ETH_ALEN]);
void print_ether_address3(u_int8_t ether_addr[ETH_ALEN]);

void print_ip_addr1(int32_t ip);
void print_ip_addr2(int32_t ip);
void print_ip_addr3(int32_t ip);

void print_ascii3(const unsigned char *str,size_t len);

void print_hex3(const unsigned char *str,size_t len);

