//
// Created by mitza on 13-Mar-21.
//

#include <stdio.h>
#include "undo_service.h"

Operation *create_operation(int (*undo)(), void *undo_parameters, int (*redo)(), void *redo_parameters) {
    Operation* o = (Operation*)malloc(sizeof(Operation));
    o->undo = undo;
    //o->undo_parameters = (void*)malloc(sizeof(undo_parameters));
    o->undo_parameters = undo_parameters;
    o->redo = redo;
   // o->redo_parameters = (void*)malloc(sizeof(redo_parameters));;
    o->redo_parameters = redo_parameters;
    return o;
}

void delete_operation(Operation *o) {
    delete_undo_parameters(o);
    delete_redo_parameters(o);
    //printf("Deleted %p\n", o->undo);
    free(o);
}

Undo_service *create_undo_service() {
    Undo_service* s = (Undo_service*)malloc(sizeof(Undo_service));
    s->list = (Operation**)malloc(sizeof(Operation*)*10);
    s->size = 0;
    s->capacity = 10;
    s->pos = -1;
    return s;
}

void delete_undo_service(Undo_service *s) {
    int i;
    for(i = 0 ; i < s->size ; i++)
        delete_operation(s->list[i]);
    free(s->list);
    free(s);
}

void add_operation(Undo_service *s, Operation *o) {
    s->pos++;
    int i;
    for(i = s->pos ; i < s->size ; i++){
        //printf("for\n");
        delete_operation(s->list[i]);
    }
    s->size = s->pos+1;
    if(s->size == s->capacity){
        s->capacity*=2;
        Operation** aux = (Operation**)malloc(sizeof(Operation)*s->capacity);
        for(i = 0 ; i < s->size ; i++){
            aux[i] = s->list[i];
        }
        free(s->list);
        s->list = aux;
    }
    s->list[s->pos] = o;
}

int undo(Undo_service *s) {
    //printf("%d %d\n", s->pos, s->size);
    if(s->pos < 0){
        return 1;
    }
    Operation* o = s->list[s->pos];
    s->pos--;
    if(o->undo == add_country){
        add_parameters* p = (add_parameters*)o->undo_parameters;
        add_country(p->repo, p->name, p->continent, p->population);
    }
    if(o->undo == delete_country_repo){
        delete_parameters* p = (delete_parameters*)o->undo_parameters;
        //printf("Deleting %s\n", p->name);
        delete_country_repo(p->repo, p->name);
    }
    if(o->undo == set_name_repo){
        set_name_parameters* p = (set_name_parameters*)o->undo_parameters;
        set_name_repo(p->repo, p->c, p->name);
    }
    if(o->undo == set_continent_repo){
        set_continent_parameters* p = (set_continent_parameters*)o->undo_parameters;
        set_continent_repo(p->repo, p->c, p->continent);
    }
    if(o->undo == set_population_repo){
        set_population_parameters* p = (set_population_parameters*)o->undo_parameters;
        set_population_repo(p->repo, p->c, p->population);
    }
    if(o->undo == migrate_repo){
        migrate_parameters* p = (migrate_parameters*)o->undo_parameters;
        migrate_repo(p->repo, p->src, p->dest, p->population);
    }
    return 0;
}

int redo(Undo_service *s) {
    //printf("%d %d\n", s->pos, s->size);
    if(s->pos == s->size-1){
        return 1;
    }
    s->pos++;
    Operation* o = s->list[s->pos];
    //printf("Redo\n");
    if(o->redo == add_country){
        add_parameters* p = (add_parameters*)o->redo_parameters;
        //printf("Redoing %s %s %lf\n", p->name, p->continent, p->population);
        add_country(p->repo, p->name, p->continent, p->population);
    }
    if(o->redo == delete_country_repo){
        delete_parameters* p = (delete_parameters*)o->redo_parameters;
        //printf("Deleting %s\n", p->name);
        delete_country_repo(p->repo, p->name);
    }
    if(o->redo == set_name_repo){
        set_name_parameters* p = (set_name_parameters*)o->redo_parameters;
        set_name_repo(p->repo, p->c, p->name);
    }
    if(o->redo == set_continent_repo){
        set_continent_parameters* p = (set_continent_parameters*)o->redo_parameters;
        set_continent_repo(p->repo, p->c, p->continent);
    }
    if(o->redo == set_population_repo){
        set_population_parameters* p = (set_population_parameters*)o->redo_parameters;
        set_population_repo(p->repo, p->c, p->population);
    }
    if(o->redo == migrate_repo){
        migrate_parameters* p = (migrate_parameters*)o->redo_parameters;
        migrate_repo(p->repo, p->src, p->dest, p->population);
    }
    return 0;
}

void delete_undo_parameters(Operation *o) {
    if(o->undo == add_country){
        add_parameters* p = (add_parameters*) o->undo_parameters;
        free(p->name);
        free(p->continent);
        free(p);
    }
    if(o->undo == delete_country_repo){
        delete_parameters* p = (delete_parameters*)o->undo_parameters;
        free(p->name);
        free(p);
    }
    if(o->undo == set_name_repo){
        set_name_parameters* p = (set_name_parameters*)o->undo_parameters;
        free(p->name);
        free(p);
    }
    if(o->undo == set_continent_repo){
        set_continent_parameters* p = (set_continent_parameters*)o->undo_parameters;
        free(p->continent);
        free(p);
    }
    if(o->undo == set_population_repo){
        set_population_parameters* p = (set_population_parameters*)o->undo_parameters;
        free(p);
    }
    if(o->undo == migrate_repo){
        migrate_parameters* p = (migrate_parameters*)o->undo_parameters;
        free(p->src);
        free(p->dest);
    }
}

void delete_redo_parameters(Operation *o) {
    if(o->redo == add_country){
        add_parameters* p = (add_parameters*) o->redo_parameters;
        free(p->name);
        free(p->continent);
        free(p);
    }
    if(o->redo == delete_country_repo){
        delete_parameters* p = (delete_parameters*)o->redo_parameters;
        free(p->name);
        free(p);
    }
    if(o->redo == set_name_repo){
        set_name_parameters* p = (set_name_parameters*)o->redo_parameters;
        free(p->name);
        free(p);
    }
    if(o->redo == set_continent_repo){
        set_continent_parameters* p = (set_continent_parameters*)o->redo_parameters;
        free(p->continent);
        free(p);
    }
    if(o->redo == set_population_repo){
        set_population_parameters* p = (set_population_parameters*)o->redo_parameters;
        free(p);
    }
    if(o->redo == migrate_repo){
        migrate_parameters* p = (migrate_parameters*)o->redo_parameters;
        free(p->src);
        free(p->dest);
    }
}
