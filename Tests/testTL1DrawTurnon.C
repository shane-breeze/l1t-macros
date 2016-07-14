#include <string>

#include "../Plotting/TL1DrawTurnon.h"

void testTL1DrawTurnon()
{
    std::string rootFilePath = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput/20160614_Data_run-273301-302-450_SingleMu/Turnons/effs_SingleMu_caloMetBE_l1MetSeeds.root";
    TL1DrawTurnon * drawRes(new TL1DrawTurnon(rootFilePath));

    drawRes->SetSample("data","Data");
    drawRes->SetTrigger("singleMu","Single Muon");
    drawRes->SetRun("274199");
    drawRes->SetAddMark("");
    drawRes->SetOutName("test");
    drawRes->SetOutDir(".");
    drawRes->SetMerges(true,true,true);

    drawRes->Draw();
}
