#include <iostream>

namespace TL1Progress
{
    void PrintProgressBar(unsigned pos, unsigned max)
    {
        if( pos % (max/100) == 0 )
        {
            float fraction = (float)pos/(float)max;
            std::cout << "[";
    
            for(unsigned i=0; i<20; ++i)
            {
                if( i < (unsigned)(fraction*20-1) ) std::cout << "=";
                else if( i < (unsigned)(fraction*20) ) std::cout << ">";
                else std::cout << " ";
            }
    
            std::cout << "] " << (unsigned)(fraction*100) << "% " << pos << "/" << max << std::endl;
            std::cout << "\033[A";
        }
    }
}
