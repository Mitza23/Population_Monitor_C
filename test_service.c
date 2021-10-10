//
// Created by mitza on 16-Mar-21.
//
#include <assert.h>
#include "service.h"

void test_add_country_service(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    assert(s->repo->size == 1);
    delete_service(s);
}

void test_delete_country_service(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    delete_country_service(s, "Alba");
    assert(s->repo->size == 0);
    delete_service(s);
}

void test_find_country_service(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    Country* c = find_country_service(s, "Alba");
    assert(strcmp(c->continent, "Asia") == 0);
    delete_service(s);
}

void test_set_name_service(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    Country* c = find_country_service(s, "Alba");
    set_name_service(s, c, "Iulia");
    assert(strcmp(c->name, "Iulia") == 0);
    delete_service(s);
}

void test_set_continent_service(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    Country* c = find_country_service(s, "Alba");
    set_continent_service(s, c, "Europe");
    assert(strcmp(c->continent, "Europe") == 0);
    delete_service(s);
}

void test_set_population_service(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    Country* c = find_country_service(s, "Alba");
    set_population_service(s, c, 5);
    assert(c->population == 5);
    delete_service(s);
}

void test_migrate_service(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    add_country(s->repo, "Iulia", "Asia", 23);
    migrate_service(s, "Alba", "Iulia", 10);
    Country* c = find_country_service(s, "Alba");
    assert(c->population == 13);
    Country* c1 = find_country_service(s, "Iulia");
    assert(c1->population == 33);
    delete_service(s);
}

void test_filter_countries_name(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    add_country(s->repo, "Iulia", "Asia", 23);
    add_country(s->repo, "Cluj", "Asia", 23);
    add_country(s->repo, "Turda", "Asia", 23);
    add_country(s->repo, "Turna", "Asia", 23);
    add_country(s->repo, "Turba", "Asia", 23);
    Repo* r = filter_countries_name(s, "Tur");
    assert(r->size == 3);
    delete_repo(r);
    delete_service(s);
}

void test_filter_countries_continent(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 23);
    add_country(s->repo, "Iulia", "Asia", 23);
    add_country(s->repo, "Cluj", "Europe", 23);
    add_country(s->repo, "Turda", "Africa", 23);
    add_country(s->repo, "Turna", "Australia", 23);
    add_country(s->repo, "Turba", "Asia", 23);
    Repo* r = filter_countries_continent(s, "As");
    assert(r->size == 3);
    delete_repo(r);
    delete_service(s);
}

void test_filter_countries_population(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 3);
    add_country(s->repo, "Iulia", "Asia", 23);
    add_country(s->repo, "Cluj", "Europe", 15);
    add_country(s->repo, "Turda", "Africa", 45);
    add_country(s->repo, "Turna", "Australia", 23);
    add_country(s->repo, "Turba", "Asia", 65);
    Repo* r = filter_countries_population(s, 50);
    assert(r->size == 1);
    delete_repo(r);
    delete_service(s);
}

void test_sort_ascending(){
    Service* s = create_service();
    add_country(s->repo, "Alba", "Asia", 3);
    add_country(s->repo, "Iulia", "Asia", 23);
    add_country(s->repo, "Cluj", "Europe", 15);
    add_country(s->repo, "Turda", "Africa", 45);
    add_country(s->repo, "Turna", "Australia", 23);
    add_country(s->repo, "Turba", "Asia", 65);

    sort_ascending(s, name_comparison);

    int i;
    for(i = 0 ; i < s->repo->size-1 ; i++){
        assert(strcmp(s->repo->list[i]->name, s->repo->list[i+1]->name) <= 0);
    }

    sort_ascending(s, population_comparison);

    for(i = 0 ; i < s->repo->size-1 ; i++){
        assert(s->repo->list[i]->population < s->repo->list[i+1]->population);
    }

    delete_service(s);
}

//int main(){
//    test_add_country_service();
//    test_delete_country_service();
//    test_find_country_service();
//    test_set_name_service();
//    test_set_continent_service();
//    test_set_population_service();
//    test_migrate_service();
//    test_filter_countries_name();
//    test_filter_countries_continent();
//    test_filter_countries_population();
//    test_sort_ascending();
//}