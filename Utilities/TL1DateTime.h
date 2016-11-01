#ifndef TL1DATETIME_H
#define TL1DATETIME_H

#include <string>

#include <TDatime.h>

namespace TL1DateTime
{
    std::string GetDate()
    {
        TDatime * date(new TDatime());
        return std::to_string(date->GetDate());
    }
}

#endif
