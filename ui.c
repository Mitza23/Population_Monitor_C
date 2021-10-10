//
// Created by mitza on 05-Mar-21.
//

#include "ui.h"
#include "utils.h"
#include "undo_service.h"
#include <stdlib.h>
#include <stdio.h>

UI* create_ui() {
    Service* service = create_service();
    //Undo_service* undo_service = create_undo_service();
    UI* ui = (UI*)malloc(sizeof(UI));
    ui->service = service;
    return ui;
}

void generate_entries(UI *u) {
    char* continents[5] = {"Europe", "America", "Asia", "Africa", "Australia"};
    char* names[15] = {"Nauru", "Swahili", "Tanganyika", "Rhodesia", "Nagaland", "Aiud", "Pata", "Juc", "Turda", "Taga",
                       "Sic", "Dej", "Chinteni", "Cluj-Blanoca", "Manhattanstur"};
    int i, c_index, n_index;
    double pop;
    for(i = 0 ; i < 10 ; i++){
        c_index = RandomInteger(0, 4);
        n_index = RandomInteger(0, 14);
        pop = RandomReal(0.02, 20.0);
        while(add_country(u->service->repo, names[n_index], continents[c_index], pop) != 0){
            c_index = RandomInteger(0, 4);
            n_index = RandomInteger(0, 14);
            pop = RandomReal(0.02, 20.0);
        }
    }
}

void read_name(char* name){
    printf("Country's name(string):\n");
    //getchar();
    fgets(name, 100, stdin);
    name[strlen(name)-1] = '\0';
}

void read_continent(char* continent){
    printf("Country's continent(string in Europe, Asia, Africa, America, Australia):\n");
    fgets(continent, 100, stdin);
    continent[strlen(continent)-1] = '\0';

    while(!valid_continent(continent)){
        printf("Country's continent(string in Europe, Asia, Africa, America, Australia):\n");
        fgets(continent, 100, stdin);
        continent[strlen(continent)-1] = '\0';
    }
}

void get_country_ui(char *name, char *continent) {
    read_name(name);
    read_continent(continent);
}

double get_double(){
    char nr[100];
    printf("Population:\n");
    fgets(nr, 100, stdin);
    nr[strlen(nr)-1] = '\0';
    double d = atof(nr);
    while(d < 0){
        printf("Population invalid!\n");
        d = get_double();
    }
    return d;
}

void add_country_ui(UI *u) {
    char name[30], continent[30];
    double population;
    get_country_ui(name, continent);
    //printf("|%s| |%s|\n", name, continent);

    population = get_double();
    //population += 0.0;

    //printf("%f\n", population);

    if(add_country_service(u->service, name, continent, population) == 0)
        printf("Country added successfully\n");
    else
        printf("Country couldn't be added, attributes do not respect the conventions!\n");
}

void delete_country_ui(UI *u) {
    char name[30];
    read_name(name);
    if(delete_country_service(u->service, name) == 0)
        printf("Country deleted successfully\n");
    else
        printf("Country couldn't be deleted, not found in repo!\n");
}

void update_country_name_ui(UI *u) {
    char name[30];

    printf("What country would you like to update?\n");
    read_name(name);

    char new_name[30];
    printf("Country's new name(string):\n");
    read_name(new_name);

    Country* c = find_country_service(u->service, name);
    if(c != NULL) {
        if(set_name_service(u->service, c, new_name) == 0)
            printf("Country name updated successfully\n");
        else
            printf("New name is not valid!\n");
    }
    else
        printf("Country couldn't be found!\n");
}

void update_country_continent_ui(UI *u) {
    char name[30];

    printf("What country would you like to update?\n");
    read_name(name);

    char new_continent[30];
    printf("Country's new continent(string):\n");
    read_continent(new_continent);

    Country* c = find_country_service(u->service, name);
    if(c != NULL) {
        if(set_continent_service(u->service, c, new_continent) == 0)
            printf("Country continent updated successfully\n");
        else
            printf("New continent is not valid!\n");
    }
    else
        printf("Country couldn't be found!\n");
}

void update_country_population_ui(UI *u) {
    char name[30];

    printf("What country would you like to update?\n");
    read_name(name);

    double new_population;
    printf("Country's new population(double):\n");
    new_population = get_double();

    Country* c = find_country_service(u->service, name);
    if(c != NULL) {
        if(set_population_service(u->service, c, new_population) == 0)
            printf("Country population updated successfully\n");
        else
            printf("New population is not valid!\n");
    }
    else
        printf("Country couldn't be found!\n");
}

void list_all(UI *u) {
    int i;
    Country** list = get_list_ui(u);
    Repo* r = get_repo_ui(u);
    for(i = 0 ; i < r->size ; i++){
        printf("%d. %s %s %f\n", i+1, get_name(list[i]),
               get_continent(list[i]), get_population(list[i]));
    }
}

void list_repo(Repo* r){
    int i;
    Country** list = r->list;
    for(i = 0 ; i < r->size ; i++){
        printf("%d. %s %s %f\n", i+1, get_name(list[i]),
               get_continent(list[i]), get_population(list[i]));
    }
}

Country **get_list_ui(UI *u) {
    return get_list_service(u->service);
}

Repo *get_repo_ui(UI *u) {
    return get_repo_service(u->service);
}

void print_menu(UI *u) {
    printf("1. Add\n");
    printf("2. Delete\n");
    printf("3. List all\n");
    printf("4. Update\n");
    printf("5. Filter\n");
    printf("6. Undo\n");
    printf("7. Redo\n");
    printf("x. Exit\n");
}

void print_update_menu(UI *u) {
    printf("1. Name\n");
    printf("2. Continent\n");
    printf("3. Population\n");
    printf("4. Migrate\n");
}

void print_filter_menu(UI *u) {
    printf("1. Name\n");
    printf("2. Continent\n");
    printf("3. Population\n");
    printf("4. Sort ascending\n");
    printf("5. Sort descending\n");
    printf("6. Continent ascending by name\n");
}

int get_command_numeric() {
    char command[10];
    printf(">>\n");
    fgets(command, 10, stdin);
    command[strlen(command)-1] = '\0';
    if(strcmp(command, "x")==0)
        return -1;
    return atoi(command);

}

void migrate_ui(UI *u) {
    //char s_name[30], s_continent[30], d_name[30], d_continent[30];
    char s_name[30], d_name[30];
    read_name(s_name);
    read_name(d_name);
    double population;
    population = get_double();
    if(population > 0) {
        if (migrate_service(u->service, s_name, d_name, population) == 0)
            printf("Migration successful\n");
        else
            printf("Migrating population is larger than country's population\n");
    }
    else
        printf("Population invalid\n");
}


void update_ui(UI *u) {
    print_update_menu(u);
    int command = get_command_numeric();
    switch (command) {
        case 1:
            update_country_name_ui(u);
            break;
        case 2:
            update_country_continent_ui(u);
            break;
        case 3:
            update_country_population_ui(u);
            break;
        case 4:
            migrate_ui(u);
            break;
        default:
            printf("Invalid command!\n");
            break;
    }
}

void filter_name_ui(UI* u){
    char name[30];
    read_name(name);
    Repo* filtered_repo = filter_countries_name(u->service, name);
    list_repo(filtered_repo);
    free(filtered_repo->list);
    free(filtered_repo);
    //delete_repo(filtered_repo);
}

void filter_continent_ui(UI* u){
    char continent[30];
    read_continent(continent);
    Repo* filtered_repo = filter_countries_continent(u->service, continent);
    list_repo(filtered_repo);
    free(filtered_repo->list);
    free(filtered_repo);
    //delete_repo(filtered_repo);
}

void filter_population_ui(UI* u){
    double population;
    population = get_double();
    Repo* filtered_repo = filter_countries_population(u->service, population);
    list_repo(filtered_repo);
    free(filtered_repo->list);
    free(filtered_repo);
    //delete_repo(filtered_repo);
}

void filter_continent_name_ui(UI* u){
    char continent[30];
    read_continent(continent);
    Repo* filtered_repo = filter_countries_continent(u->service, continent);
    //sort_name_ascending(filtered_repo);
    sort_ascending(u->service, name_comparison);
    list_repo(filtered_repo);
    free(filtered_repo->list);
    free(filtered_repo);
}

void filter_ui(UI *u) {
    print_filter_menu(u);
    int command = get_command_numeric();
    switch (command) {
        case 1:
            filter_name_ui(u);
            break;
        case 2:
            filter_continent_ui(u);
            break;
        case 3:
            filter_population_ui(u);
            break;
        case 4:
            sort_ascending(u->service, population_comparison);
            list_all(u);
            break;
        case 5:
            sort_descending(u->service, reverse_population_comparison);
            list_all(u);
            break;
        case 6:
            filter_continent_name_ui(u);
            break;
        default:
            printf("Invalid command!\n");
            break;
    }
}

void delete_ui(UI *u) {
    delete_service(u->service);
    free(u);
}


void start(UI *u) {
    int done = 0;
    while(!done){
        print_menu(u);
        int command = get_command_numeric();
        //printf("%d", command);
        switch (command) {
            case 1:
                add_country_ui(u);
                break;
            case 2:
                delete_country_ui(u);
                break;
            case 3:
                list_all(u);
                break;
            case 4:
                update_ui(u);
                break;
            case 5:
                filter_ui(u);
                break;
            case 6:
                undo_ui(u);
                break;
            case 7:
                redo_ui(u);
                break;
            case -1:
                done = 1;
                break;
            default:
                printf("Invalid command\n");
                break;
        }
    }
    delete_ui(u);
}

void undo_ui(UI *u) {
    Undo_service* undo_service = get_undo_service(u->service);
    if(undo(undo_service)){
        printf("No more operations left to be undone!\n");
    }
}

void redo_ui(UI *u) {
    Undo_service* undo_service = get_undo_service(u->service);
    if(redo(undo_service)){
        printf("No more operations left to be redone!\n");
    }
}

void test_undo_redo_add(UI* u){
    add_country_service(u->service, "Koreea", "Asia", 34);
    list_all(u);
    printf("\n");
    redo_ui(u);
    undo_ui(u);
    list_all(u);
    printf("\n");
    redo_ui(u);
    list_all(u);
    printf("\n");
}

void test_undo_redo_delete(UI* u){
    add_country_service(u->service, "Korea", "Asia", 34);
    list_all(u);
    printf("\n");
    delete_country_service(u->service, "Korea");
    list_all(u);
    printf("\n");
    printf("UNDO\n");
    undo_ui(u);
    list_all(u);
    printf("\n");
    printf("REDO\n");
    redo_ui(u);
    list_all(u);
    printf("\n");
}

void test_undo_redo_set_name(UI* u){
    add_country_service(u->service, "Korea", "Asia", 34);
    list_all(u);
    printf("\n");
    Country* c = find_country_service(u->service, "Korea");
    set_name_service(u->service, c, "Japonia");
    list_all(u);
    printf("\n");
    printf("UNDO\n");
    undo_ui(u);
    list_all(u);
    printf("\n");
    redo_ui(u);
    printf("REDO\n");
    list_all(u);
    printf("\n");
}

void test_undo_redo_set_continent(UI* u){
    add_country_service(u->service, "Korea", "Asia", 34);
    list_all(u);
    printf("\n");
    Country* c = find_country_service(u->service, "Korea");
    set_continent_service(u->service, c, "Europe");
    list_all(u);
    printf("\n");
    printf("UNDO\n");
    undo_ui(u);
    list_all(u);
    printf("\n");
    redo_ui(u);
    printf("REDO\n");
    list_all(u);
    printf("\n");
}

void test_undo_redo_set_population(UI* u){
    add_country_service(u->service, "Korea", "Asia", 34);
    list_all(u);
    printf("\n");
    Country* c = find_country_service(u->service, "Korea");
    set_population_service(u->service, c, 23);
    list_all(u);
    printf("\n");
    printf("UNDO\n");
    undo_ui(u);
    list_all(u);
    printf("\n");
    redo_ui(u);
    printf("REDO\n");
    list_all(u);
    printf("\n");
}

int main(){
    UI* u = create_ui();
    generate_entries(u);

    //test_undo_redo_add(u);
    //test_undo_redo_delete(u);
    //test_undo_redo_set_name(u);
    //test_undo_redo_set_continent(u);
    //test_undo_redo_set_population(u);

    start(u);
}