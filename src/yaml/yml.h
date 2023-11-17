
//
// Created by Theo OMNES on 16/11/2023.
//

#ifndef CLINGS_YML_H
#define CLINGS_YML_H

#include <yaml.h>
#include "katas/katas.h"
#include "stdbool.h"

KataListParsingResult parse_kata_list(char *file_path);

#endif //CLINGS_YML_H
