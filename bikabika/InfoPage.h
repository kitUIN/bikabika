#pragma once

#include "InfoPage.g.h"

namespace winrt::bikabika::implementation
{
    struct InfoPage : InfoPageT<InfoPage>
    {
        InfoPage();


    };
}

namespace winrt::bikabika::factory_implementation
{
    struct InfoPage : InfoPageT<InfoPage, implementation::InfoPage>
    {
    };
}
