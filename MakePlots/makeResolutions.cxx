#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Utilities/TL1DateTime.C"
#include "../Plotting/TL1Resolution.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/sumResolutions_cfg.h"

#include "../Debug/DebugHandler.h"

double FoldPhi(double phi);

// CHUNK = which chunk of root-files to run over
// NFILES = numbers of root-files
// NJOBS = number of jobs to submit
void makeResolutions(const int & CHUNK, const int & NFILES, const int & NJOBS, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1Resolution* > resolutions = sumResolutions(dataset);

    // Split the files into CHUNKS:
    // 1 to n; n+1 to 2n; 2n+1 to 3n ... NJOBS*n to NFILES
    // n = nFilesPerJob
    // The final job is typically larger than the others (never smaller)
    std::vector<std::string> inDir;
    std::string outDir( dataset->outDir+"_hadd/Resolution/" );
    if( !COMBINE )
    {
        outDir = dataset->outDir;
        if( NJOBS > 1 ) outDir += Form("_CHUNK%i",CHUNK);
        outDir += "/Resolution/";

        int nFilesPerJob( NFILES / NJOBS );
        int finalFile( nFilesPerJob*(1+CHUNK) );
        if( CHUNK == NJOBS-1 ) finalFile = NFILES;

        for(int i=1+(CHUNK*nFilesPerJob); i<=finalFile; ++i)
            inDir.push_back(Form(dataset->inFiles.c_str(),i));
    }
    TL1EventClass * event(new TL1EventClass(inDir));

    // Being
    for(auto it=resolutions.begin(); it!=resolutions.end(); ++it)
    {
        it->second->SetSample(dataset->sampleName,dataset->sampleTitle);
        it->second->SetTrigger(dataset->triggerName,dataset->triggerTitle);
        it->second->SetRun(dataset->run);
        it->second->SetOutDir(outDir);
        it->second->SetPuType(dataset->puType);
        it->second->SetPuBins(dataset->puBins);
        if( dataset->sampleName != "Data" ) it->second->SetPuFile(dataset->puFilename);
        if( !COMBINE ) it->second->InitPlots();
        else it->second->OverwritePlots();
    }

    // Loop
    unsigned NEntries(0);
    if( !COMBINE ) NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() && !COMBINE )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        // Skip events that don't meet the selection criteria
        if( dataset->triggerName == "SingleMu" )
            if( !event->fMuonFilterPassFlag ) 
                continue;

        // Get the relevant event parameters
        int pu = event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        // MET
        double l1MetBE = event->fL1Met;
        double l1MetHF = event->fL1MetHF;
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double l1MetPhiBE = event->fL1MetPhi;
        double l1MetPhiHF = event->fL1MetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;

        // Fill resolutions with event parameters. Includes the fill logic
        if( event->fMetFilterPassFlag )
        {
            if( recoMetBE > 40.0 && l1MetBE > 0.0 )
            {
                if( resolutions.find("caloMetBE_l1MetBE") != resolutions.end() )
                    resolutions["caloMetBE_l1MetBE"]->Fill(recoMetBE, l1MetBE, pu);
                if( resolutions.find("caloMetPhiBE_l1MetPhiBE") != resolutions.end() )
                    resolutions["caloMetPhiBE_l1MetPhiBE"]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1MetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1MetBE > 0.0 )
            {
                if( resolutions.find("caloMetHF_l1MetBE") != resolutions.end() )
                    resolutions["caloMetHF_l1MetBE"]->Fill(recoMetHF, l1MetBE, pu);
                if( resolutions.find("caloMetPhiHF_l1MetPhiBE") != resolutions.end() )
                    resolutions["caloMetPhiHF_l1MetPhiBE"]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1MetHF > 0.0 )
            {
                if( resolutions.find("caloMetHF_l1MetBE") != resolutions.end() )
                    resolutions["caloMetHF_l1MetHF"]->Fill(recoMetHF, l1MetHF, pu);
                if( resolutions.find("caloMetPhiHF_l1MetPhiBE") != resolutions.end() )
                    resolutions["caloMetPhiHF_l1MetPhiHF"]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiHF), pu);
            }
        }
    }

    // End
    for(auto it=resolutions.begin(); it!=resolutions.end(); ++it)
        it->second->DrawPlots();
    cout << "Output saved in:\n\t" << outDir << endl;
}

double FoldPhi(double phi)
{
    return TMath::Min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
}
