//
// Created by mitza on 03-Mar-21.
//

#ifndef A23_MITZA23_DOMAIN_H
#define A23_MITZA23_DOMAIN_H



/*
 * Country is the structure that represents a country as an entity having
 * name - char*
 * continent - char*
 * population - double
 */
typedef struct country{
    char* name;
    char* continent;
    double population;
} Country;


/// Creates a new Country
/// \param name name of the country - char*
/// \param continent continent of the country - char*
/// \param population population of the country - double
/// \return a pointer to the newly created country - Country*
Country* create_country(char* name, char* continent, double population);


/// Deletes a country and frees all the space occupied by it
/// \param c pointer to the country to be deleted - Country*
void delete_country(Country* c);


/// Updates the name of a given country
/// \param c pointer to the country to be updated - Country*
/// \param name new name of the country - char*
/// \return 0 if the operation was successful | 1 otherwise
int set_name(Country *c, char* name);


/// Updates the continent of a given country
/// \param c pointer to the country to be updated - Country*
/// \param continent new continent of the country - char*
/// \return 0 if the operation was successful | 1 otherwise
int set_continent(Country* c, char* continent);


/// Updates the population of a given country
/// \param c pointer to the country to be updated - Country*
/// \param population new population of the country - double
/// \return 0 if the operation was successful | 1 otherwise
int set_population(Country* c, double population);


/// Gets the name of the country
/// \param c country whose name is retrieved - Country*
/// \return the name of the country - char*
char* get_name(Country* c);


/// Gets the continent of the country
/// \param c country whose continent is retrieved - Country*
/// \return the continent of the country - char*
char* get_continent(Country* c);


/// Gets the population of the country
/// \param c country whose population is retrieved - Country*
/// \return the population of the country - double
double get_population(Country* c);
#endif //A23_MITZA23_DOMAIN_H