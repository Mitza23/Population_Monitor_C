//
// Created by mitza on 13-Mar-21.
//

#ifndef A23_MITZA23_UNDO_SERVICE_H
#define A23_MITZA23_UNDO_SERVICE_H

#include "repository.h"

/**
 * Structure for enclosing the parameters of add_country function
 * repo: the repo in which the country is added - Repo*
 * name: the the name of the country - char*
 * continent: the continent of the country - char*
 * population: the population of the country - double
 */
typedef struct add_parameters{
    Repo* repo;
    char* name;
    char* continent;
    double population;
} add_parameters;


/**
 * Structure for enclosing the parameters of delete_country function
 * repo: the repo in which the country is deleted - Repo*
 * name: the the name of the country - char*
 */
typedef struct delete_parameters{
    Repo* repo;
    char* name;
} delete_parameters;


/**
 * Structure for enclosing the parameters of set_name function
 * repo: the repo in which the country is updated - Repo*
 * c: address of the country to be updated - Country*
 * name: the new name of the country - char*
 */
typedef struct set_name_parameters{
    Repo* repo;
    Country* c;
    char* name;
}set_name_parameters;


/**
 * Structure for enclosing the parameters of set_continent function
 * repo: the repo in which the country is updated - Repo*
 * c: address of the country to be updated - Country*
 * continent: the new continent of the country - char*
 */
typedef struct set_continent_parameters{
    Repo* repo;
    Country* c;
    char* continent;
}set_continent_parameters;


/**
 * Structure for enclosing the parameters of set_population function
 * repo: the repo in which the country is updated - Repo*
 * c: address of the country to be updated - Country*
 * population: the new population of the country - double
 */
typedef struct set_population_parameters{
    Repo* repo;
    Country* c;
    double population;
}set_population_parameters;


/**
 * Structure for enclosing the parameters of migrate function
 * repo: the repo in which the country is updated - Repo*
 * src: address of the country from where te population emigrates - Country*
 * dest: address of the country in which te population immigrates - Country*
 * population: the population migrating - double
 */
typedef struct migrate_parameters{
    Repo* repo;
    Country* src;
    Country* dest;
    double population;
}migrate_parameters;

/**
 * Structure for enclosing the parameters of an operation executed in the repo
 * undo: address of the function executed for undoing the operation - int
 * undo_parameters: pointer to structure enclosing the parameters of undo function - void*
 * redo: address of the function executed for redoing the operation - int
 * redo_parameters: pointer to structure enclosing the parameters of redo function - void*
 */
typedef struct operation{
    int (*undo)();
    void* undo_parameters;
    int (*redo)();
    void* redo_parameters;
} Operation;

/**
* Structure for enclosing the undo service
* list: list of executed operation - Operation**
* size: size of the list - int
* capacity: capacity of the list - int
* position: position in the list - int
*/
typedef struct undo_service{
    Operation** list;
    int size;
    int capacity;
    int pos;
} Undo_service;

/// Creates an operation to be added to the list for undo-ing or redo-ing
/// \param undo the undo function - int
/// \param undo_parameters the parameters for undoing - void*
/// \param redo the redo function - int
/// \param redo_parameters the parameters for redoing - void*
/// \return an operation containing the specified properties - Operation*
Operation* create_operation(int (*undo)(), void* undo_parameters, int (*redo)(), void* redo_parameters);


/// Frees all the undo parameters of operation
/// \param o the operation whose parameters are deleted - Operation*
void delete_undo_parameters(Operation* o);


/// Frees all the redo parameters of operation
/// \param o the operation whose parameters are deleted - Operation*
void delete_redo_parameters(Operation* o);


/// Deletes an operation
/// \param o the operation to be deleted - Operation*
void delete_operation(Operation* o);


/// Creates an empty undo service
/// \return the service - Undo_service*
Undo_service* create_undo_service();


/// Deletes an empty undo service
/// \param s the service to be deleted - Undo_service*
void delete_undo_service(Undo_service* s);


/// Adds a new operation to the list
/// \param s the service in which is added - Undo_service*
/// \param o The operation to be added - Operation*
void add_operation(Undo_service* s, Operation* o);


/// Undoes the last operation performed
/// \param s the service in which the undo is executed - Undo_service*
/// \return 0 if it was performed successfully | 1 otherwise
int undo(Undo_service* s);


/// Redoes the last operation performed
/// \param s the service in which the redo is executed - Undo_service*
/// \return 0 if it was performed successfully | 1 otherwise
int redo(Undo_service* s);

#endif //A23_MITZA23_UNDO_SERVICE_H
