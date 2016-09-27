#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Utilities/TL1DateTime.C"
#include "../Plotting/TL1Turnon.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/jetTurnons_cfg.h"

vector<double> bins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

// CHUNK = which chunk of root-files to run over
// NFILES = numbers of root-files
// NJOBS = number of jobs to submit
void makeJetTurnons(const int & CHUNK, const int & NFILES, const int & NJOBS, const bool & COMBINE)
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map<std::string &, TL1Turnon *> turnons = jetTurnons(dataset.triggerName, dataset.doFit);

    // Check CHUNK < NJOBS
    if( CHUNK >= NJOBS ) throw "The CHUNK number exceeds the number of jobs";

    std::vector<std::string> inDir;
    std::string outDir("");
    if(!COMBINE)
    {
        outDir = dataset.outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+\
            "_"+"run-"+run+"_"+triggerName+Form("_CHUNK%i/TurnonsJets/",CHUNK);

        // Split the files into CHUNKS:
        // 1 to n; n+1 to 2n; 2n+1 to 3n ... NJOBS*n to NFILES
        // n = nFilesPerJob
        // The final job is typically larger than the others (never smaller)
        int nFilesPerJob( NFILES / NJOBS );
        int finalFile( nFilesPerJob*(1+CHUNK) );
        if( CHUNK == NJOBS-1 ) finalFile = NFILES;

        for(int i=1+(CHUNK*nFilesPerJob); i<=finalFile; ++i)
            inDir.push_back(Form(dataset.inFiles.c_str(),i));
    }
    else
    {
        outDir = dataset.outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+\
                 "_"+"run-"+run+"_"+triggerName+"_hadd/TurnonsJets/";
    }

    TL1EventClass * event(new TL1EventClass(inDir));
    std::string baseOWdir = dataset.baseOWdir + "/TurnonsJets/";

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        it->second->SetSample(dataset.sampleName, dataset.sampleTitle);
        it->second->SetTrigger(dataset.triggerName, dataset.triggerTitle);
        it->second->SetRun(dataset.run);
        it->second->SetOutDir(outDir);
        it->second->SetPuType(dataset.puType);
        it->second->SetPuBins(dataset.puBins);
        if( dataset.sampleName != "Data" ) it->second->SetPuFile(dataset.puFilename);
        if( !COMBINE ) it->second->InitPlots();
        else it->second->OverwritePlots();
    }

    unsigned NEntries(0);
    if( !COMBINE ) NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        if( !event->fIsLeadingRecoJet ) continue;
        if( !event->fIsMatchedL1EmuJet ) continue;

        int pu = event->GetPEvent()->fVertex->nVtx;
        auto recoJet = event->GetPEvent()->fJets;

        double recoEt = recoJet->etCorr[event->fLeadingRecoJetIndex];
        double recoEta = recoJet->eta[event->fLeadingRecoJetIndex];
        double recoPhi = recoJet->phi[event->fLeadingRecoJetIndex];

        double l1Et = event->fL1EmuJetEt[event->fMatchedL1EmuJetIndex];
        double l1Eta = event->fL1EmuJetEta[event->fMatchedL1EmuJetIndex];
        double l1Phi = event->fL1EmuJetPhi[event->fMatchedL1EmuJetIndex];

        if( abs(recoEta) <= 1.479 )
        {
            if( ! (turnons.find("jetEtBarrel") == turnons.end()) )
                turnons["jetEtBarrel"]->Fill(recoEt, l1Et, pu);
            if( ! (turnons.find("jetEtCentral") == turnons.end()) )
                turnons["jetEtCentral"]->Fill(recoEt, l1Et, pu);
        }
        else if( abs(recoEta) <= 3.0 )
        {
            if( ! (turnons.find("jetEtEndcap") == turnons.end()) )
                turnons["jetEtEndcap"]->Fill(recoEt, l1Et, pu);
            if( ! (turnons.find("jetEtCentral") == turnons.end()) )
                turnons["jetEtCentral"]->Fill(recoEt, l1Et, pu);
        }
        else
        {
            if( ! (turnons.find("jetEtHF") == turnons.end()) )
                turnons["jetEtHF"]->Fill(recoEt, l1Et, pu);
        }
    }

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        it->second->DrawPlots();
        it->second->DrawTurnons();
    }

    cout << "Output saved in:\n" << outDir << endl;
}

vector<double> bins()
{
    vector<double> temp;
    for(double binLowerEdge=  0.0; binLowerEdge< 100.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge< 200.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge< 300.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge< 400.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=400.0; binLowerEdge< 500.1; binLowerEdge+=25.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 2.5) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 70.0; binLowerEdge<200.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=200.0; binLowerEdge<300.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=300.0; binLowerEdge<400.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    return temp;
}

void SetMyStyle(int palette, double rmarg, TStyle * myStyle)
{
    myStyle->SetCanvasDefW(800);
    myStyle->SetCanvasDefH(600);
    myStyle->SetNumberContours(255);
    myStyle->SetPalette(palette);
    myStyle->SetPadRightMargin(rmarg);
    myStyle->cd();
}
