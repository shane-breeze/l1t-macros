#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1Rates.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/jetDist_cfg.h"

#include "../Debug/DebugHandler.h"

// CHUNK = which chunk of root-files to run over
// NJOBS = number of jobs to submit
void makeJetDist(const int & CHUNK, const int & NJOBS, const int & NENT, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.08, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    dataset->puType = {};
    dataset->puBins = {};
    std::map< std::string, TL1Dist* > dists = jetDist(dataset);

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

        // Get the relevant event parameters
        //int pu = event->GetPEvent()->fVertex->nVtx;
        auto l1JetEts = event->fL1JetEt;
        double maxL1JetEt(0.0);
        for(auto it=l1JetEts.begin(); it!=l1JetEts.end(); ++it)
            if( *it > maxL1JetEt )
                maxL1JetEt = *it;
        int nL1Jets = l1JetEts.size();

        if( nL1Jets >= 1 )
            if( dists.find("singleJets") != dists.end() )
                dists["singleJets"]->Fill(maxL1JetEt, 0.0);
        if( nL1Jets >= 2 )
            if( dists.find("doubleJets") != dists.end() )
                dists["doubleJets"]->Fill(maxL1JetEt, 0.0);
        if( nL1Jets >= 3 )
            if( dists.find("tripleJets") != dists.end() )
                dists["tripleJets"]->Fill(maxL1JetEt, 0.0);
        if( nL1Jets >= 4 )
            if( dists.find("quadJets") != dists.end() )
                dists["quadJets"]->Fill(maxL1JetEt, 0.0);
    }

    for(auto it=dists.begin(); it!=dists.end(); ++it)
        it->second->DrawPlots();
    std::cout << "Output saved in:\n\t" << outDir << std::endl;
}
