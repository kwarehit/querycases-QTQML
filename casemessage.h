#pragma once

#include <string>
#include <map>

#include "casedetails.h"

struct CaseMessage 
{
    std::string caseType;
    std::string caseName;
    std::map<unsigned int, CaseDetails, std::greater<unsigned int>> results;
};
