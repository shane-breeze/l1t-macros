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
