//
// Created by mitza on 05-Mar-21.
//

#ifndef A23_MITZA23_SERVICE_H
#define A23_MITZA23_SERVICE_H



#include "repository.h"
#include "undo_service.h"

/*
 * Service is a structure that wraps around the repo
 * repo - Repo*
 */
typedef struct service{
    Repo* repo;
    Undo_service* undo_service;
}Service;

/// Creates a new service
/// \return the newly created service - Service*
Service* create_service();


/// Destroys a service
/// \param s service to be destroyed - Service*
void delete_service(Service* s);


/// Adds a new country to the list of countries
/// \param s service to whose repo the country is added - Service*
/// \param name name of the new country - char*
/// \param continent continent of the new country - char*
/// \param population population of the new country - double
/// \return 0 if country successfully added | 1 otherwise
int add_country_service(Service* s, char* name, char* continent, double population);


/// Removes a country from the list of countries
/// \param s service from whose repo the country is removed - Service*
/// \param name name of the country to be removed - char*
/// \return 0 if successfully deleted | 1 otherwise
int delete_country_service(Service *s, char *name);


/// Updates the name of a country
/// \param s service from whose repo the country is updated - Service*
/// \param c the country to be updated - Country*
/// \param name new name of the country - char*
/// \return o if updated successful | 1 otherwise
int set_name_service(Service* s, Country* c, char* name);


/// Updates the continent of a country
/// \param s service from whose repo the country is updated - Service*
/// \param c the country to be updated - Country*
/// \param continent new continent of the country - char*
/// \return o if updated successful | 1 otherwise
int set_continent_service(Service* s, Country* c, char* continent);


/// Updates the population of a country
/// \param s service from whose repo the country is updated - Service*
/// \param c the country to be updated - Country*
/// \param population new population of the country - double
/// \return o if updated successful | 1 otherwise
int set_population_service(Service* s, Country* c, double population);


/// Filters the list of countries that have a certain substring in their name
/// \param s service from whose list of countries is filtered - Service*
/// \param name substring searched in countries name - char*
/// \return a repo containing the filtered countries - Repo*
Repo* filter_countries_name(Service* s, char* name);


/// Filters the list of countries that have a certain substring in their continent
/// \param s service from whose list of countries is filtered - Service*
/// \param continent substring searched in countries continent - char*
/// \return a repo containing the filtered countries - Repo*
Repo* filter_countries_continent(Service* s, char* continent);


/// Filters the list of countries that have more than a certain population
/// \param s service from whose list of countries is filtered - Service*
/// \param population limit population - double
/// \return a repo containing the filtered countries - Repo*
Repo* filter_countries_population(Service* s, double population);


/// Places the last element inside the bounds of the list inside the service determined by l and r in the position it
/// would be if that array would be already sorted by population in increasing order
/// \param s service in whose list the partition is done - Service*
/// \param l left bound of the list(index) - int
/// \param r right bound of the list(index) - int
/// \return the position of the last element in the initial array in the sorted version - int
int partition(Service *s, int l, int r, int (*cmp)(Country*, Country*));

/// Sorts by QuickSort the list of countries ascending by population in between the bounds l and r
/// \param s  service in whose list the sorting is done - Service*
/// \param l left bound of the list(index) - int
/// \param r right bound of the list(index) - int
void quick_sort(Service *s, int l, int r, int (*cmp)(Country*, Country*));


/// Sorts by QuickSort the list of countries ascending by population
/// \param s  service in whose list the sorting is done - Service*
void sort_ascending(Service *s, int (*cmp)(Country *, Country *));


/// Sorts the list of countries descending by population
/// \param s  service in whose list the sorting is done - Service*
void sort_descending(Service *s, int (*cmp)(Country *, Country *));


/// Finds a country by name inside the list of the service
/// \param s the service in which the country is searched - Service*
/// \param name name of the country by which it's searched
/// \return the address of the country - Country* | NULL if not found
Country *find_country_service(Service *s, char *name);


/// Gets the list of countries of a service
/// \param s the service whose list is get - Service*
/// \return list of countries - Country**
Country** get_list_service(Service* s);


/// Gets the repo of a service
/// \param s the service whose repo is get - Service*
/// \return repo of the service - Repo*
Repo* get_repo_service(Service* s);


/// Migrates population from one country to another
/// \param s the service in which the migration happens
/// \param s_name name of the country from the population emigrates - char*
/// \param d_name name of the country in which the population immigrates - char*
/// \param population the amount of population who changes country - double
/// \return 0 if successful | 1 otherwise
int migrate_service(Service *s, char *s_name, char *d_name, double population);


/// Sorts the population ascending by name
/// \param r repo in which the population is sorted
void sort_name_ascending(Repo* r);


/// Compares the population of 2 countries
/// \param a first country - Country*
/// \param b second country - Country*
/// \return -1 if population of the first one is smaller than the second one's | 1 otherwise
int population_comparison(Country* a, Country* b);


/// Compares the population of 2 countries
/// \param a first country - Country*
/// \param b second country - Country*
/// \return 1 if population of the first one is smaller than the second one's | -1 otherwise
int reverse_population_comparison(Country* a, Country* b);


/// Compares the name of 2 countries
/// \param a first country - Country*
/// \param b second country - Country*
/// \return -1 if name of the first one is lexicographically smaller than the second one's | 1 otherwise
int name_comparison(Country* a, Country*b);


/// Compares the continent of 2 countries
/// \param a first country - Country*
/// \param b second country - Country*
/// \return -1 if continent of the first one is lexicographically smaller than the second one's | 1 otherwise
int continent_comparison(Country* a, Country*b);


///Gets the undo service of the service
/// \param s the service - Service*
/// \return pointer to the undo service - Undo_service*
Undo_service* get_undo_service(Service* s);
#endif //A23_MITZA23_SERVICE_H