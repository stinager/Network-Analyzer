#include <ctype.h>
#include <stdio.h>
#include "ascii.h"
#include "print.h"

#define ASCII_MAX_COLS 80
#define HEX_COLS 16

/**
 *param const unsigned char *str, int len
 * -> Fonction qui permet l'affichage en ascii 
 */

void print_ascii(const unsigned char *str, int len) {
int i = 0;
	while (i<len){
		if (i%47==0){
			printf("\n\t\t");
		}
		if(isprint(str[i])){
			printf3("%c", str[i]);
		}
		else{
			print3(".");
		}
		i++;
	}
print3("\n");
}

/**
 *param const unsigned char *bytes, size_t len
 * -> Fonction qui permet l'affichage en héxadécimal
 */

void print_hex(const unsigned char *str, size_t len) {
    size_t lines = 0;
    int cols=0;
    print3("\n");
    while(1) {
	print3("                ");
        for(cols = 0; cols < HEX_COLS; cols++) {
            if(lines * HEX_COLS + cols >= len) {
		print3("      ");
                putchar('\n');
                return;
            }	
	    
            printf3("%02x ", str[lines * HEX_COLS + cols]);
        }
		
        lines++;	
        putchar('\n');
    }
}
