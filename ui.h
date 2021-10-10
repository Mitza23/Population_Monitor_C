//
// Created by mitza on 05-Mar-21.
//

#ifndef A23_MITZA23_UI_H
#define A23_MITZA23_UI_H

#endif //A23_MITZA23_UI_H

#include "service.h"
#include "utils.h"

typedef struct ui{
    Service* service;
} UI;

UI* create_ui();

void delete_ui(UI* u);

void generate_entries(UI* u);

void get_country_ui(char* name, char* continent);

void add_country_ui(UI* u);

void delete_country_ui(UI* u);

void update_country_name_ui(UI* u);

void update_country_continent_ui(UI* u);

void update_country_population_ui(UI* u);

Country** get_list_ui(UI* u);

Repo* get_repo_ui(UI* u);

void list_all(UI* u);

void print_menu(UI* u);

void print_update_menu(UI* u);

void print_filter_menu(UI* u);

int get_command_numeric();

void update_ui(UI* u);

void filter_ui(UI* u);

void migrate_ui(UI* u);

void undo_ui(UI* u);

void redo_ui(UI* u);

void start(UI* u);