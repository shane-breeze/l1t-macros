#include <memory>
#include <string>
#include <iostream>

#include "TL1DataClass.h"

void testTL1DataClass()
{
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1DataClass> jetReco(new TL1DataClass("l1JetRecoTree/JetRecoTree",inDir));
    cout << "HERE1" << endl;
}
