#include <memory>
#include <string>
#include <iostream>

#include "TL1EventClass.h"

void testTL1EventClass()
{
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));
}
