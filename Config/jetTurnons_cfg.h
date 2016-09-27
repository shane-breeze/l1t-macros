#ifndef JETTURNONS_CFG_H
#define JETTURNONS_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Turnon.h"

std::map<std::string &, TL1Turnon *> jetTurnons(const std::string & triggerName, const bool & doFit);
TL1Turnon jetEtBarrel(const std::string & triggerName, const bool & doFit);
TL1Turnon jetEtEndCap(const std::string & triggerName, const bool & doFit);
TL1Turnon jetEtCentral(const std::string & triggerName, const bool & doFit);
TL1Turnon jetEtHF(const std::string & triggerName, const bool & doFit);
std::vector<double> bins();

#endif
