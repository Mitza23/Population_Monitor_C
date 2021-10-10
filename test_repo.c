//
// Created by mitza on 16-Mar-21.
//

#include "service.h"
#include <assert.h>

void test_create_repo(){
    Repo* r = create_repo();
    assert(r->size == 0);
    assert(r->capacity == 10);
    delete_repo(r);
}

void test_find_country(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    Country* c = find_country(r, "Alba");
    assert(c->population == 23);
    delete_repo(r);
}

void test_find_country_position(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    add_country(r, "Iulia", "Asia", 23);
    int p = find_country_position(r, "Alba");
    assert(p == 0);
    delete_repo(r);
}

void test_append_country(){
    Repo* r = create_repo();
    Country* c = create_country("Alba", "Asia", 23);
    append_country(r, c);
    assert(r->size == 1);
    delete_repo(r);
}

void test_add_country(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    assert(r->size == 1);
    delete_repo(r);
}

void test_delete_country_repo(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    delete_country_repo(r, "Alba");
    assert(find_country_position(r, "Alba") == -1);
    delete_repo(r);
}

void test_set_name_repo(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    set_name_repo(r, find_country(r, "Alba"), "Iulia");
    assert(find_country(r, "Iulia")->population == 23);
    delete_repo(r);
}


void test_set_continent_repo(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    set_continent_repo(r, find_country(r, "Alba"), "Europe");
    assert(strcmp(find_country(r, "Alba")->continent, "Europe") == 0);
    delete_repo(r);
}

void test_set_population_repo(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    set_population_repo(r, find_country(r, "Alba"), 33);
    assert(find_country(r, "Alba")->population == 33);
    delete_repo(r);
}

void test_migrate_repo(){
    Repo* r = create_repo();
    add_country(r, "Alba", "Asia", 23);
    add_country(r, "Iulia", "Asia", 23);
    migrate_repo(r, find_country(r, "Alba"), find_country(r, "Iulia"), 10);
    assert(find_country(r, "Alba")->population == 13);
    assert(find_country(r, "Iulia")->population == 33);
    delete_repo(r);
}

//int main(){
//    test_add_country();
//    test_append_country();
//    test_create_repo();
//    test_delete_country_repo();
//    test_find_country();
//    test_find_country_position();
//    test_migrate_repo();
//    test_set_continent_repo();
//    test_set_name_repo();
//    test_set_population_repo();
//}