//
// Created by mitza on 04-Mar-21.
//

#ifndef A23_MITZA23_REPOSITORY_H
#define A23_MITZA23_REPOSITORY_H



#include "validator.h"
#include <stdlib.h>
#include <string.h>


/*
 * Repo represents a repository for Country
 * capacity - int
 * size - int
 * list - Country**
 */
typedef struct repository{
    int capacity;
    int size;
    Country** list;
} Repo;


/// Creates an empty repo
/// \return pointer to the newly created empty repo - Repo*
Repo* create_repo();


/// Deletes a specified repo by freeing all the space occupied by it
/// \param r pointer to the repo to be deleted - Repo*
void delete_repo(Repo* r);


/// Finds a country inside a repo by name
/// \param r pointer to the repo in which the search is done - Repo*
/// \param name name of the country that is searched - char*
/// \return pointer to the country - Country* | NULL if not found
Country *find_country(Repo *r, char *name);


/// Finds the position of a country inside a repo by name
/// \param r pointer to the repo in which the search is done - Repo*
/// \param name name of the country that is searched - char*
/// \return position of the country inside the list - int | -1 if not found
int find_country_position(Repo *r, char *name);


/// Appends a Country to the repo list
/// \param r pointer to the repo - Repo*
/// \param c pointer to the country to be added - Country*
void append_country(Repo* r, Country* c);


/// Adds a Country to the repo
/// \param r repo where the country is added - Repo*
/// \param name name of the country to be added - char*
/// \param continent continent of the country to be added - char*
/// \param population population of the country to be added - double
/// \return 0 if country successfully added | 1 if not
int add_country(Repo* r, char* name, char* continent, double population);


/// Removes a country from the repo
/// \param r repo from which the country is removed - Repo*
/// \param name name of the country to be deleted
/// \return 0 if the country has been successfully removed | 1 otherwise
int delete_country_repo(Repo *r, char *name);


/// Updates the name of a country
/// \param r repo from where the country is updated - Repo*
/// \param c country to be updated - Country*
/// \param name new name of the country - char*
/// \return 0 if the update has been successful | 1 otherwise
int set_name_repo(Repo* r, Country *c, char *name);


/// Updates the continent of a country
/// \param r repo from where the country is updated - Repo*
/// \param c country to be updated - Country*
/// \param continent new continent of the country - char*
/// \return 0 if the update has been successful | 1 otherwise
int set_continent_repo(Repo* r, Country *c, char *continent);


/// Updates the population of a country
/// \param r repo from where the country is updated - Repo*
/// \param c country to be updated - Country*
/// \param population new continent of the country - double
/// \return 0 if the update has been successful | 1 otherwise
int set_population_repo(Repo* r, Country *c, double population);


int migrate_repo(Repo* r, Country* src, Country* dest, double population);

/// Gets the list of countries from the repo
/// \param r repo from which the list is taken - Repo*
/// \return list of countries from the repo - Country**
Country** get_list_repo(Repo* r);

#endif //A23_MITZA23_REPOSITORY_H