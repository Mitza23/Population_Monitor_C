//
// Created by mitza on 03-Mar-21.
//

#include <string.h>
#include "validator.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

Country* create_country(char* name, char* continent, double population)
{
    if(valid(name, continent, population) == 1) {
        Country *c = (Country *) malloc(sizeof(Country));
        //strcpy(c->name, name);
        c->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(c->name, name);
        //strcpy(c->continent, continent);
        c->continent = (char*)malloc(sizeof(char)*(strlen(continent)+1));
        strcpy(c->continent, continent);
        c->population = population;
        return c;
    }
    //printf("Country couldn't be created!\n");
    return NULL;
}

void delete_country(Country *c) {
    free(c->name);
    free(c->continent);
    free(c);
}

//void test_delete_country(){
//    Country* c = create_country("Alba", "Asia", 23);
//    delete_country(c);
//    assert(c == NULL);
//}

int set_name(Country *c, char *name) {
    if(strlen(name) > 0) {
        free(c->name);
        c->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(c->name, name);
        return 0;
    }
    return 1;
}

int set_continent(Country *c, char *continent) {
    if(valid_continent(continent)){
        free(c->continent);
        c->continent = (char*)malloc(sizeof(char)*(strlen(continent)+1));
        strcpy(c->continent, continent);
        return 0;
    }
    //printf("Continent not valid!\n");
    return 1;
}

int set_population(Country *c, double population) {
    if(fabs(population-0.01) > 0){
        c->population = population;
        return 0;
    }
    //printf("Population not valid!\n");
    return 1;
}

char *get_name(Country *c) {
    return c->name;
}

char *get_continent(Country *c) {
    return c->continent;
}

double get_population(Country *c) {
    return c->population;
}

