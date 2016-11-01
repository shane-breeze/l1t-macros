#include "../Config/ntuple_cfg.h"
#include "../Event/TL1EventClass.h"

#include "../Debug/DebugHandler.h"

void getNEntries()
{
    ntuple_cfg * dataset = new ntuple_cfg( GetNtuple_cfg() );
    std::vector<std::string> inDir( dataset->inFiles );
    TL1EventClass * event( new TL1EventClass(inDir) );
    unsigned NEntries( event->GetPEvent()->GetNEntries() );

    std::cout << "NEntries = " << NEntries << std::endl;
}
