#pragma once
#include "SortMode.g.h"

namespace winrt::bikabika::implementation
{
    struct SortMode : SortModeT<SortMode>
    {
        SortMode() = default;

        hstring Tile();
        void Tile(hstring const& value);
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct SortMode : SortModeT<SortMode, implementation::SortMode>
    {
    };
}
