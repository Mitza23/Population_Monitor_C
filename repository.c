//
// Created by mitza on 04-Mar-21.
//

#include <stdio.h>
#include "repository.h"
#include <assert.h>

Repo* create_repo() {
    Repo* r = (Repo*)malloc(sizeof(Repo));
    r->list = (Country**)malloc(sizeof(Country*) * 20);
    r->capacity = 10;
    r->size = 0;
    return r;
}

void delete_repo(Repo *r) {
    int i;
    for(i = 0 ; i < r->size ; i++){
        delete_country(r->list[i]);
    }
    free(r->list);
    free(r);
}

Country *find_country(Repo *r, char *name) {
    int i;
    Country** list = get_list_repo(r);
    for(i = 0 ; i < r->size ; i++){
        if(strcmp(list[i]->name, name) == 0 && strlen(name) == strlen(list[i]->name)){
            return list[i];
        }
    }
    return NULL;
}

int find_country_position(Repo *r, char *name) {
    int i;

    Country** list = get_list_repo(r);
    for(i = 0 ; i < r->size ; i++){
        if(strcmp(list[i]->name, name) == 0){
            return i;
        }
    }
    return -1;
}

void append_country(Repo *r, Country *c) {
    if(r->size == r->capacity){
        r->capacity *= 2;
        Country** new_list = (Country**)malloc(sizeof(Country*) * r->capacity);
        int i;
        for(i = 0 ; i < r->size ; i++){
            new_list[i] = r->list[i];
        }
        free(r->list);
        r->list = new_list;
    }

    r->list[r->size] = c;
    r->size++;
}

int add_country(Repo *r, char *name, char *continent, double population) {
    if(find_country(r, name) == NULL && valid(name, continent, population)){
        Country* c = create_country(name, continent, population);
        //printf("%s %s %f \n", name, continent, population);
        append_country(r, c);
        return 0;
    } else
        return 1;
}

int delete_country_repo(Repo *r, char *name) {
    int position = find_country_position(r, name);
    if(position == -1)
        return 1;
    delete_country(r->list[position]);
    r->list[position] = r->list[r->size-1];
    r->size--;
    return 0;
}

int set_name_repo(Repo *r, Country *c, char *name) {
    if(find_country(r, c->name) != NULL && find_country(r, name) == NULL) {
        return set_name(c, name);
    }
    return 1;
}

int set_continent_repo(Repo *r, Country *c, char *continent) {
    if(find_country(r, c->name) != NULL) {
        return set_continent(c, continent);
    }
    return 1;
}

int set_population_repo(Repo *r, Country *c, double population) {
    if(find_country(r, c->name) != NULL) {
        return set_population(c, population);
    }
    return 1;
}

Country** get_list_repo(Repo *r) {
    return r->list;
}

int migrate_repo(Repo *r, Country *src, Country *dest, double population) {
    if(src->population - population > 0){
        dest->population += population;
        src->population -= population;
        return 0;
    }
    return 1;
}
