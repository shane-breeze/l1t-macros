#ifndef DEBUGHANDLER_H
#define DEBUGHANDLER_H

#include <string>

#include <TFile.h>

namespace DebugHandler
{
    void Throw(const bool & throwTest, const std::string & output)
    {
        if( !throwTest )
            throw output;
    }
    
    void CheckTFile(TFile * testFile)
    {
        if( !testFile->IsOpen() )
            throw "Error: The file "+testFile->GetName()+" is not open!";
        if( !testFile->IsZombie() )
            throw "Error: Zombie file "+testFile->GetName();
    }
}

#endif
