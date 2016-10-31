#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Utilities/TL1DateTime.C"
#include "../Plotting/TL1Turnon.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/sumTurnons_cfg.h"

#include "../Debug/DebugHandler.h"

// CHUNK = which chunk of root-files to run over
// NFILES = numbers of root-files
// NJOBS = number of jobs to submit
void makeTurnons(const int & CHUNK, const int & NJOBS, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1Turnon* > turnons = sumTurnons(dataset);

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/Turnons/" );
    if(!COMBINE) outDir = dataset->outDir + Form("_CHUNK%i/Turnons/",CHUNK);
    else inDir.clear();
    TL1EventClass * event(new TL1EventClass(inDir));

    // Begin
    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        it->second->SetSample(dataset->sampleName, dataset->sampleTitle);
        it->second->SetTrigger(dataset->triggerName, dataset->triggerTitle);
        it->second->SetRun(dataset->run);
        it->second->SetOutDir(outDir);
        it->second->SetPuType(dataset->puType);
        it->second->SetPuBins(dataset->puBins);
        //if( dataset->sampleName != "Data" ) it->second->SetPuFile(dataset->puFilename);
        if( !COMBINE ) it->second->InitPlots();
        else it->second->OverwritePlots();
    }

    unsigned NEntries(0), start(0), end(0);
    if( !COMBINE )
    {
        NEntries = event->GetPEvent()->GetNEntries();
        unsigned NEvents(NEntries / NJOBS);
        start = CHUNK * NEvents;
        end   = (CHUNK+1) * NEvents;
        if( CHUNK == NJOBS-1 ) end = NEntries;
    }
    cout << "NEntries = " << NEntries << endl;

    // Loop
    for(int i=start; i<end && !COMBINE; ++i)
    {
        event->GetEntry(i);
        TL1Progress::PrintProgressBar(i-start, end-start);

        // Skip events that don't meet the selection criteria
        if( dataset->triggerName == "SingleMu" )
            if( !event->fMuonFilterPassFlag ) 
                continue;
        
        // Get the relevant event parameters
        int pu = 0;//event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        double l1MetBE = event->fL1Met;
        double caloMetBE = sums->caloMetBE;
        double l1Htt = event->fL1Htt;
        double recoHtt = sums->Ht;

        //----- MET -----//
        if( event->fMetFilterPassFlag )
            if( turnons.find("metBE") != turnons.end() )
                turnons["metBE"]->Fill(caloMetBE, l1MetBE);

        //----- HTT -----//
        if( turnons.find("htt") != turnons.end() )
            turnons["htt"]->Fill(recoHtt, l1Htt);
    }

    // End
    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        it->second->DrawPlots();
        it->second->DrawTurnons();
    }
    cout << "Output saved in:\n" << outDir << endl;
}
