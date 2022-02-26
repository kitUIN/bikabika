#pragma once
#include "BikaDate.g.h"

namespace winrt::bikabika::implementation
{
    struct BikaDate : BikaDateT<BikaDate>
    {
        BikaDate() = default;

        BikaDate(hstring const& date);
        hstring SetTimeZone();
        void SetTimeZone(hstring const& value);
        hstring GetDateTime();
    private:
        hstring m_timeZone = L"UTC+8";
        int32_t m_times=8;
        hstring m_dateTime;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct BikaDate : BikaDateT<BikaDate, implementation::BikaDate>
    {
    };
}
