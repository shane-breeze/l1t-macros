#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1Dist.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/sumDist_cfg.h"

#include "../Debug/DebugHandler.h"

// CHUNK = which chunk of root-files to run over
// NJOBS = number of jobs to submit
void makeDist(const int & CHUNK, const int & NJOBS, const int & NENT, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.08, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1Dist* > dists = sumDist(dataset);

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/Turnons/" );
    if(!COMBINE) outDir = dataset->outDir + Form("_CHUNK%i/Turnons/",CHUNK);
    else inDir.clear();
    TL1EventClass * event(new TL1EventClass(inDir));

    // Begin
    for(auto it=dists.begin(); it!=dists.end(); ++it)
    {
        it->second->SetSample(dataset->sampleName, dataset->sampleTitle);
        it->second->SetTrigger(dataset->triggerName, dataset->triggerTitle);
        it->second->SetRun(dataset->run);
        it->second->SetOutDir(outDir);
        if( !COMBINE ) it->second->InitPlots();
        else it->second->OverwritePlots();
    }

    unsigned start(0), end(0);
    if( !COMBINE )
    {
        unsigned NEvents(NENT / NJOBS);
        start = CHUNK * NEvents;
        end   = (CHUNK+1) * NEvents;
        if( CHUNK == NJOBS-1 ) end = NENT;
    }

    // Loop
    for(int i=start; i<end && !COMBINE; ++i)
    {
        event->GetEntry(i);
        TL1Progress::PrintProgressBar(i-start, end-start);

        //int pu = event->GetPEvent()->fVertex->nVtx;

        // Get the relevant event parameters
        double l1MetBE = event->fL1Met;
        double l1MetHF = event->fL1MetHF;

        if( dists.find("l1MetBE") != dists.end() )
            dists["l1MetBE"]->Fill(l1MetBE, 0.);
        if( dists.find("l1MetHF") != dists.end() )
            dists["l1MetHF"]->Fill(l1MetHF, 0.);
    }

    for(auto it=dists.begin(); it!=dists.end(); ++it)
        it->second->DrawPlots();
    std::cout << "Output saved in:\n\t" << outDir << std::endl;
}
