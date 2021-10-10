//
// Created by mitza on 03-Mar-21.
//

#ifndef A23_MITZA23_VALIDATOR_H
#define A23_MITZA23_VALIDATOR_H



#include "domain.h"

/// Checks whether the attributes are valid for a Country
/// \param name name of the country - char*
/// \param continent name of the continent - char*
/// \param population population of the country - double
/// \return 1 if the attributes are valid | 0 otherwise
int valid(char* name, char* continent, double population);


/// Checks if a continent is whether "Europe, America, Africa, Australia, Asia"
/// \param continent name of the continent - char*
/// \return 1 if the continent is valid | 0 otherwise
int valid_continent(char* continent);

#endif //A23_MITZA23_VALIDATOR_H