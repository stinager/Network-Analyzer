#include "print.h"
#include "ip.h"
#include "ethernet.h"
#include "ascii.h"


void putchar1(int c) {
    if(verbosity >= 1 && c != '\r') putchar(c);
}

void putchar2(int c) {
    if(verbosity >= 2 && c != '\r') putchar(c);
}

void putchar3(int c) {
    if(verbosity >= 3 && c != '\r') putchar(c);
}

void print1(const char *str) {
    if(verbosity >= 1) {printf("%s",str);}
}

void print2(const char *str) {
    if(verbosity >= 2) {printf("%s",str);}
}

void print3(const char *str) {
    if(verbosity >= 3) {printf("%s",str);}
}

/*Fonction qui permet l'affichage de l'adresse mac en verbosité 1*/
void print_ether_address1(u_int8_t *ether_addr) {
    if(verbosity >= 1) print_ether_address(ether_addr);
}

/*Fonction qui permet l'affichage de l'adresse mac en verbosité 2 */
void print_ether_address2(u_int8_t *ether_addr) {
    if(verbosity >= 2) print_ether_address(ether_addr);
}

/*Fonction qui permet l'affichage de l'adresse mac en verbosité 3 */
void print_ether_address3(u_int8_t *ether_addr) {
    if(verbosity >= 3) print_ether_address(ether_addr);
}

/*Fonction qui permet l'affichage de l'adresse ip en verbosité 1*/
void print_ip_addr1(int32_t ip) {
    if(verbosity >= 1) print_ip_addr(ip);
}

/*Fonction qui permet l'affichage de l'adresse ip en verbosité 2*/
void print_ip_addr2(int32_t ip) {
    if(verbosity >= 2) print_ip_addr(ip);
}

/*Fonction qui permet l'affichage de l'adresse ip en verbosité 3 */
void print_ip_addr3(int32_t ip) {
    if(verbosity >= 3) print_ip_addr(ip);
}

/*Fonction qui permet l'affichage du contenu en ascii en verbosité 3 */
void print_ascii3(const unsigned char *str,size_t len){
  if(verbosity >= 3) print_ascii(str, len);
}

/*Fonction qui permet l'affichage du contenu en héxadécimal en verbosité 3 */
void print_hex3(const unsigned char *str,size_t len){
  if(verbosity >= 3) print_hex(str, len);
}
