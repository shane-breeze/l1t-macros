#ifndef DEBUGHANDLER_H
#define DEBUGHANDLER_H

#include <string>
#include <cstdlib>
#include <iostream>

#include <TFile.h>

namespace DebugHandler
{
    void ErrorCheck(const bool & isError, const std::string & output, const std::string & file, const int & line)
    {
        if( isError )
        {
            std::cerr << "\nError in " << file << " on Line " << line << std::endl;
            std::cerr << "\t" << output << std::endl;
            exit(-1);
        }
    }
    
    void CheckTFile(TFile * testFile, const std::string & file, const int & line)
    {
        if( !testFile->IsOpen() )
        {
            std::cerr << "\nError in " << file << " on Line " << line << std::endl;
            std::cerr << "\tThe file " << testFile->GetName() << " is not open!" << std::endl;
            exit(-1);
        }
        if( !testFile->IsZombie() )
        {
            std::cerr << "\nError in " << file << " on Line " << line << endl;
            std::cerr << "\tZombie file " << string(testFile->GetName()) << std::endl;
            exit(-1);
        }
    }
}

#endif
