#pragma once
#include "BikaHttp.g.h"


namespace winrt::bikabika::implementation
{
    struct BikaHttp : BikaHttpT<BikaHttp>
    {
        BikaHttp() = default;

        hstring Auth();
        void Auth(hstring const& value);
        hstring SetRaw(hstring strAPI, hstring uid, time_t t, hstring method, hstring apiKey);
        hstring BikaEncryption(hstring strAPI, hstring uid, time_t t, hstring method, hstring apiKey, hstring strKey);
        Windows::Web::Http::Headers::HttpRequestHeaderCollection SetHeader(Windows::Web::Http::Headers::HttpRequestHeaderCollection headers, hstring strAPI, guid uuid, time_t t, hstring method);
        Windows::Web::Http::HttpResponseMessage GET(Windows::Foundation::Uri requestUri, hstring strAPI, guid uuid, hstring apiKey, hstring strKey);
        Windows::Foundation::IAsyncOperation<hstring> POST(Windows::Foundation::Uri requestUri, Windows::Web::Http::HttpStringContent jsonContent, hstring strAPI, guid uuid);
        Windows::Foundation::IAsyncOperation<hstring> Login(hstring account, hstring password);
    private:
        winrt::hstring m_auth;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct BikaHttp : BikaHttpT<BikaHttp, implementation::BikaHttp>
    {
    };
}
