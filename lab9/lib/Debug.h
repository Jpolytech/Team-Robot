/*
Auteurs:
    Andreea Maria Ghioltan
    Maria Bourouisa
    Jean-Philippe Salis Routhier 
    Thibault Delahaie

Description du programme: Permet de retourner au PC des valeurs pouvant être analysées pour aider 
                          au débogage.
                           
Identifications des broches (Broches I/O): Ne s'applique pas.
*/

#pragma once
#include"Uart.h"
#include "stdio.h"

void print(uint16_t number);
void print(const char* message);

#ifdef DEBUG
#define DEBUG_PRINT(message) print(message)
#else
#define DEBUT_PRINT(message) do {} while(0)
#endif
