//
// Created by mitza on 05-Mar-21.
//

#include <stdio.h>
#include "service.h"

Service* create_service() {
    Service* s = (Service*)malloc(sizeof(Service));
    Repo* r = create_repo();
    s->repo = r;
    s->undo_service = create_undo_service();
    return s;
}

void delete_service(Service *s) {
    delete_repo(s->repo);
    delete_undo_service(s->undo_service);
    free(s);
}

int add_country_service(Service *s, char *name, char *continent, double population) {

    int success = add_country(s->repo, name, continent, population);

    if(success == 0) {
        Country* c = find_country_service(s, name);
        delete_parameters *undo_parameters = malloc(sizeof(struct delete_parameters));
        undo_parameters->repo = s->repo;
        undo_parameters->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(undo_parameters->name, name);

        add_parameters *redo_parameters = malloc(sizeof(struct add_parameters));
        redo_parameters->repo = s->repo;
        redo_parameters->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(redo_parameters->name, name);
        redo_parameters->continent = (char*)malloc(sizeof(char)*(strlen(continent)+1));
        strcpy(redo_parameters->continent, continent);
        redo_parameters->population = population;

        //printf("Service %s |\n", redo_parameters->name);

        Operation *o = create_operation(delete_country_repo, undo_parameters, add_country, redo_parameters);
        add_operation(s->undo_service, o);
    }
    return success;
}

int delete_country_service(Service *s, char *name) {
    Country* c = find_country_service(s, name);
    char continent[100];
    double population = c->population;
    strcpy(continent, c->continent);

    int success = delete_country_repo(s->repo, name);

    if(success == 0) {
        delete_parameters *redo_parameters = malloc(sizeof(struct delete_parameters));
        redo_parameters->repo = s->repo;
        redo_parameters->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(redo_parameters->name, name);

        add_parameters *undo_parameters = malloc(sizeof(struct add_parameters));
        undo_parameters->repo = s->repo;
        undo_parameters->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(undo_parameters->name, name);
        undo_parameters->continent = (char*)malloc(sizeof(char)*(strlen(continent)+1));
        strcpy(undo_parameters->continent, continent);
        undo_parameters->population = population;

        Operation *o = create_operation(add_country, undo_parameters, delete_country_repo, redo_parameters);
        add_operation(s->undo_service, o);
    }

    return success;
}

int set_name_service(Service *s, Country *c, char *name) {
    char initial_name[100];
    strcpy(initial_name, c->name);

    int success = set_name_repo(s->repo, c, name);

    if(success == 0){
        set_name_parameters* undo_parameters = malloc(sizeof(set_name_parameters));
        undo_parameters->repo = s->repo;
        undo_parameters->name = (char*)malloc(sizeof(char)*(strlen(initial_name)+1));
        strcpy(undo_parameters->name, initial_name);
        undo_parameters->c = c;

        set_name_parameters* redo_parameters = malloc(sizeof(set_name_parameters));
        redo_parameters->repo = s->repo;
        redo_parameters->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(redo_parameters->name, name);
        redo_parameters->c = c;

        Operation *o = create_operation(set_name_repo, undo_parameters, set_name_repo, redo_parameters);
        add_operation(s->undo_service, o);
    }

    return success;
}

int set_continent_service(Service *s, Country *c, char *continent) {
    char initial_continent[100];
    strcpy(initial_continent, c->continent);

    int success = set_continent_repo(s->repo, c, continent);

    if(success == 0){
        set_continent_parameters* undo_parameters = malloc(sizeof(set_continent_parameters));
        undo_parameters->repo = s->repo;
        undo_parameters->continent = (char*)malloc(sizeof(char)*(strlen(initial_continent)+1));
        strcpy(undo_parameters->continent, initial_continent);
        undo_parameters->c = c;

        set_continent_parameters* redo_parameters = malloc(sizeof(set_continent_parameters));
        redo_parameters->repo = s->repo;
        redo_parameters->continent = (char*)malloc(sizeof(char)*(strlen(continent)+1));
        strcpy(redo_parameters->continent, continent);
        redo_parameters->c = c;

        Operation *o = create_operation(set_continent_repo, undo_parameters, set_continent_repo, redo_parameters);
        add_operation(s->undo_service, o);
    }

    return success;

}

int set_population_service(Service *s, Country *c, double population) {
    double initial_population = c->population;
    int success = set_population_repo(s->repo, c, population);

    if(success == 0){
        set_population_parameters* undo_parameters = malloc(sizeof(set_population_parameters));
        undo_parameters->repo = s->repo;
        undo_parameters->population = initial_population;
        undo_parameters->c = c;

        set_population_parameters* redo_parameters = malloc(sizeof(set_population_parameters));
        redo_parameters->repo = s->repo;
        redo_parameters->population = population;
        redo_parameters->c = c;

        Operation *o = create_operation(set_population_repo, undo_parameters, set_population_repo, redo_parameters);
        add_operation(s->undo_service, o);
    }

    return success;
}

int migrate_service(Service *s, char *s_name, char *d_name, double population) {
    Country* src = find_country_service(s, s_name);
    Country* dest = find_country_service(s, d_name);
    //printf("%lf\n", src->population - population);
    int success = migrate_repo(s->repo, src, dest, population);

    if(success == 0){
        migrate_parameters* undo_parameters = (migrate_parameters*)malloc(sizeof(migrate_parameters));
        undo_parameters->repo = s->repo;
        undo_parameters->src = dest;
        undo_parameters->dest = src;
        undo_parameters->population = population;

        migrate_parameters* redo_parameters = (migrate_parameters*)malloc(sizeof(migrate_parameters));
        redo_parameters->repo = s->repo;
        redo_parameters->src = src;
        redo_parameters->dest = dest;
        redo_parameters->population = population;
    }

    return success;
}

Repo* filter_countries_name(Service *s, char *name) {
    Repo* filtered_repo = create_repo();
    int i;
    for (i = 0; i < s->repo->size; i++) {
        if (strstr(s->repo->list[i]->name, name) != NULL)
            append_country(filtered_repo, s->repo->list[i]);
    }
    return filtered_repo;
}

Repo *filter_countries_continent(Service *s, char *continent) {
    Repo* filtered_repo = create_repo();
    int i;
    for (i = 0; i < s->repo->size; i++) {
        if (strstr(s->repo->list[i]->continent, continent) != NULL)
            append_country(filtered_repo, s->repo->list[i]);
    }
    return filtered_repo;
}

Repo *filter_countries_population(Service *s, double population) {
    Repo* filtered_repo = create_repo();
    int i;
    for (i = 0; i < s->repo->size; i++) {
        if (s->repo->list[i]->population > population)
            append_country(filtered_repo, s->repo->list[i]);
    }
    return filtered_repo;
}

int partition(Service *s, int l, int r, int (*cmp)(Country*, Country*)) {
    int pivot = r, i, j = l;
    Country* aux;
    Country** list = get_list_repo(get_repo_service(s));
    for(i = l ; i < r ; i++){
        if(cmp(list[i], list[pivot]) < 0){
            aux = list[i];
            list[i] = list[j];
            list[j] = aux;
            j++;
        }
    }
    aux = list[pivot];
    list[pivot] = list[j];
    list[j] = aux;
    return j;
}

void quick_sort(Service *s, int l, int r, int (*cmp)(Country*, Country*)) {
    if(l<r){
        int pivot = partition(s, l, r, cmp);
        quick_sort(s, l, pivot-1, cmp);
        quick_sort(s, pivot+1, r, cmp);
    }
}

void sort_ascending(Service *s, int (*cmp)(Country *, Country *)) {
    quick_sort(s, 0, get_repo_service(s)->size-1, cmp);
}

void sort_descending(Service *s, int (*cmp)(Country *, Country *)) {
    quick_sort(s, 0, get_repo_service(s)->size-1, cmp);
//    Repo* repo = get_repo_service(s);
//    Country** list = get_list_repo(get_repo_service(s));
//    int i;
//    Country* aux;
//    int n = repo->size;
//    for(i = 0 ; i < n/2 ; i++){
//        aux = list[i];
//        list[i] = list[n-i-1];
//        list[n-i-1] = aux;
//    }
}

int partition_name(Repo* repo, int l, int r) {
    int pivot = r, i, j = l;
    Country* aux;
    Country** list = get_list_repo(repo);
    for(i = l ; i < r ; i++){
        if(strcmp(list[i]->name, list[pivot]->name) < 0){
            aux = list[i];
            list[i] = list[j];
            list[j] = aux;
            j++;
        }
    }
    aux = list[pivot];
    list[pivot] = list[j];
    list[j] = aux;
    return j;
}

void quick_sort_name(Repo* repo, int l, int r) {
    if(l<r){
        int pivot = partition_name(repo, l, r);
        quick_sort_name(repo, l, pivot-1);
        quick_sort_name(repo, pivot+1, r);
    }
}

void sort_name_ascending(Repo* r){
    quick_sort_name(r, 0, r->size-1);
}

Country *find_country_service(Service *s, char *name) {
    return find_country(s->repo, name);
}

Country **get_list_service(Service *s) {
    return get_list_repo(s->repo);
}

Repo *get_repo_service(Service *s) {
    return s->repo;
}

int name_comparison(Country *a, Country *b) {
    return strcmp(a->name, b->name);
}

int continent_comparison(Country *a, Country *b) {
    return strcmp(a->continent, b->continent);
}

int population_comparison(Country *a, Country *b) {
    if(a->population < b->population)
        return -1;
    return 1;
}

int reverse_population_comparison(Country* a, Country* b){
    return -population_comparison(a, b);
}

Undo_service *get_undo_service(Service *s) {
    return s->undo_service;
}

//int main(){
//    char s[] = "ana are mere";
//    printf("%s", strstr(s, ""));
//}