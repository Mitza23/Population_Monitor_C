//
// Created by mitza on 16-Mar-21.
//

#include <assert.h>
#include "service.h"

void test_create_country(){
    Country* c = create_country("Alba", "Asia", 23);
    assert(c->population == 23);
    assert(strcmp(c->name, "Alba") == 0 );
    delete_country(c);
}

void test_set_name(){
    Country* c = create_country("Alba", "Asia", 23);
    set_name(c, "Iulia");
    assert(strcmp(c->name, "Iulia") == 0 );
    delete_country(c);
}

void test_set_continent(){
    Country* c = create_country("Alba", "Asia", 23);
    set_continent(c, "Europe");
    assert(strcmp(c->continent, "Europe") == 0 );
    delete_country(c);
}

void test_set_population(){
    Country* c = create_country("Alba", "Asia", 23);
    set_population(c, 33);
    assert(c->population == 33 );
    delete_country(c);
}

void test_get_name(){
    Country* c = create_country("Alba", "Asia", 23);
    assert(strcmp(get_name(c), "Alba") == 0);
    delete_country(c);
}

void test_get_continent(){
    Country* c = create_country("Alba", "Asia", 23);
    assert(strcmp(get_continent(c), "Asia") == 0);
    delete_country(c);
}

void test_get_population(){
    Country* c = create_country("Alba", "Asia", 23);
    assert(get_population(c) == 23);
    delete_country(c);
}

//int main(){
//    test_create_country();
//    //test_delete_country();
//    test_set_continent();
//    test_set_name();
//    test_set_population();
//    test_get_continent();
//    test_get_name();
//    test_get_population();
//    return 0;
//}