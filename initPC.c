//
// Created by pierre on 08/03/19.
//

#include <sys/socket.h>
#include <stdio.h>
#include "initPC.h"
#include "primitives.h"
#include "string.h"
#include <stdlib.h>

char *initPC(int numPC, bool local) {
    char *serialInitPC = calloc(256, sizeof(char));
    for (int i = 0; i < 256; ++i) {
        serialInitPC[i] = 0;
    }
    int priseEmission, priseReception;
    int PORT_EMISSION = 19000 + (1 + numPC) * 50;
    int PORT_RECEPTION = 19000 + numPC * 50;

    char charNumPCSender[1];
    char charNumPCReceiver[1];
    char charPriseEmission[1];
    char charPriseReception[1];
    char charPortReception[5];
    char charPortEmission[5];
    char *ADRESSE_EMETTEUR = malloc(9 * sizeof(char));
    char *ADRESSE_RECEPTEUR = malloc(9 * sizeof(char));

    if (local) {

        strcpy(ADRESSE_EMETTEUR, "127.0.0.1");
        strcpy(ADRESSE_RECEPTEUR, "127.0.0.1");
        sprintf(charNumPCSender, "%d", numPC);
        sprintf(charNumPCReceiver, "%d", numPC + 1);
    } else {
        sprintf(charNumPCSender, "%d", numPC);
        sprintf(charNumPCReceiver, "%d", numPC + 1);
        if (numPC < 9) {
            ADRESSE_EMETTEUR[10] = charNumPCSender[0];
            ADRESSE_RECEPTEUR[10] = charNumPCReceiver[0];
        } else {
            printf("Too much hosts, not supported yet");
            return NULL;
        }
    }

    priseReception = creePriseReception(PORT_RECEPTION);
    priseEmission = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);

    sprintf(charPriseEmission, "%d", priseEmission);
    sprintf(charPriseReception, "%d", priseReception);
    sprintf(charPortReception, "%d", PORT_RECEPTION);
    sprintf(charPortEmission, "%d", PORT_EMISSION);


    strncat(serialInitPC, charNumPCSender, 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPriseEmission, 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPriseReception, 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, ADRESSE_EMETTEUR, 9);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, ADRESSE_RECEPTEUR, 9);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPortReception, 5);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPortEmission, 5);


    return serialInitPC;
}