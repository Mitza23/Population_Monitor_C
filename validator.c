//
// Created by mitza on 03-Mar-21.
//

#include "validator.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

int valid(char* name, char* continent, double population){
    if(valid_continent(continent) == 1){
        if(strlen(name) < 1)
            return 0;

        if(fabs(population-0.001) < 0) {
            return 0;
        }

        return 1;
    }
    return 0;
}

void test_valid(){
    assert(valid("Alba", "Asia", 23) == 1);
}

int valid_continent(char *continent) {
    char continents[] = "Europe, America, Africa, Australia, Asia,";
    char* location = strstr(continents, continent);
    if(location != NULL) {
        if (*(location + strlen(continent)) == ',')
            return 1;
    }
    return 0;
}

void test_valid_continent(){
    assert(valid_continent("Asia") == 1);
}

//int main(){
//    test_valid();
//    test_valid_continent();
//}