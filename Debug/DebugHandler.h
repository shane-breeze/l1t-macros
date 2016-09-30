#ifndef DEBUGHANDLER_H
#define DEBUGHANDLER_H

#include <string>
#include <cstdlib>
#include <iostream>

#include <TFile.h>

#include "../Utilities/colormod.h"

namespace DebugHandler
{
    void ErrorCheck(const bool & isError, const std::string & output, const std::string & file, const int & line)
    {
        if( isError )
        {
            Color::Modifier red(Color::FG_RED);
            Color::Modifier blue(Color::FG_BLUE);
            Color::Modifier def(Color::FG_DEFAULT);

            std::cerr << "\nError in " << blue << file << def;
            std::cerr << " on Line " << red << line << def << std::endl;
            std::cerr << "\t" << output << std::endl;
            exit(-1);
        }
    }
    
    void CheckTFile(TFile * testFile, const std::string & file, const int & line)
    {
        Color::Modifier red(Color::FG_RED);
        Color::Modifier blue(Color::FG_BLUE);
        Color::Modifier def(Color::FG_DEFAULT);

        if( !testFile->IsOpen() )
        {
            std::cerr << "\nError in " << blue << file << def;
            std::cerr << " on Line " << red << line << def << std::endl;
            std::cerr << "\tThe file " << testFile->GetName();
            std::cerr << " is not open!" << std::endl;
            exit(-1);
        }
        if( !testFile->IsZombie() )
        {
            std::cerr << "\nError in " << blue << file << def;
            std::cerr << " on Line " << red << line << def << endl;
            std::cerr << "\tZombie file " << string(testFile->GetName());
            std::cerr << std::endl;
            exit(-1);
        }
    }
}

#endif
