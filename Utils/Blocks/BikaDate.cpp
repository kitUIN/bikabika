#include "pch.h"
#include "BikaDate.h"
#include "BikaDate.g.cpp"
#pragma warning( disable : 4996 )
namespace winrt::bikabika::implementation
{
    BikaDate::BikaDate(hstring const& date)
    {
        std::tm t = {};
        std::string dateTime = to_string(date);
        hstring format = L"%Y-%b-%d %H:%M:%S";
        std::istringstream ss(dateTime.substr(0, 10) + " " + dateTime.substr(11, 8));
        ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
        char myStr[255] = "\0";
        time_t times = std::mktime(&t);
        times += 60 * 60 * m_times;
        std::wstringstream wss;
        wss << std::put_time(std::localtime(&times), L"%Y-%m-%d %H:%M:%S");
        winrt::hstring hs{ wss.str() };
        m_dateTime = hs;
        
    }
    hstring BikaDate::SetTimeZone()
    {
        return m_timeZone;
    }
    void BikaDate::SetTimeZone(hstring const& value)
    {
        if (value == L"+12") 
        {
            m_timeZone = L"UTC+12"; 
            m_times = 12;
        }
        else if (value == L"+11")
        {
            m_timeZone = L"UTC+11"; 
            m_times = 11;
        }
        else if (value == L"+10") 
        {
            m_timeZone = L"UTC+10"; 
            m_times = 10;
        }
        else if (value == L"+9") 
        {
            m_timeZone = L"UTC+9"; 
            m_times = 9;
        }
        else if (value == L"+8") 
        { 
            m_timeZone = L"UTC+8"; 
            m_times = 8;
        }
        else if (value == L"+7") 
        { 
            m_timeZone = L"UTC+7"; 
            m_times = 7; }
        else if (value == L"+6")
        {
            m_timeZone = L"UTC+6";
            m_times = 6;
        }
        else if (value == L"+5") 
        {
            m_timeZone = L"UTC+5";
            m_times = 5;
        }
        else if (value == L"+4") 
        {
            m_timeZone = L"UTC+4"; 
            m_times = 4;
        }
        else if (value == L"+3") {
            m_timeZone = L"UTC+3"; 
            m_times = 3;
        }
        else if (value == L"+2") { m_timeZone = L"UTC+2"; m_times = 2; }
        else if (value == L"+1") { m_timeZone = L"UTC+1"; m_times = 1; }
        else if (value == L"+0") { m_timeZone = L"UTC"; m_times = 0; }
        else if (value == L"-1") { m_timeZone = L"UTC-1"; m_times = -1; }
        else if (value == L"-2") { m_timeZone = L"UTC-2"; m_times = -2; }
        else if (value == L"-3") { m_timeZone = L"UTC-3"; m_times = -3; }
        else if (value == L"-4") { m_timeZone = L"UTC-4"; m_times = -4; }
        else if (value == L"-5") { m_timeZone = L"UTC-5"; m_times = -5; }
        else if (value == L"-6") { m_timeZone = L"UTC-6"; m_times = -6; }
        else if (value == L"-7") { m_timeZone = L"UTC-7"; m_times = -7; }
        else if (value == L"-8") { m_timeZone = L"UTC-8"; m_times = -8; }
        else if (value == L"-9") { m_timeZone = L"UTC-9"; m_times = -9; }
        else if (value == L"-10") { m_timeZone = L"UTC-10"; m_times = -10; }
        else if (value == L"-11") { m_timeZone = L"UTC-11"; m_times = -11; }
        else if (value == L"-12") { m_timeZone = L"UTC-12"; m_times = -12; }
    }
    hstring BikaDate::GetDateTime()
    {
        return m_dateTime + L" (" + m_timeZone + L")";
    }
}
