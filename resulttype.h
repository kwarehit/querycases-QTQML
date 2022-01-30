#ifndef RESULTTYPE_H
#define RESULTTYPE_H

#include <map>
#include <string>
#include <functional>

#include <QMetaType>

#include "casedetails.h"

using ResultType = std::map<std::string, std::map<std::string, std::map<unsigned int, CaseDetails, std::greater<unsigned int>>>>;

Q_DECLARE_METATYPE(ResultType)


#endif // RESULTTYPE_H
