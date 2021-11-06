#pragma once
#include "BikaHttpClient.g.h"

namespace winrt::bikabika::implementation
{
	struct BikaHttpClient : BikaHttpClientT<BikaHttpClient>
	{
		BikaHttpClient() = default;

		winrt::hstring Authorization();
		void Authorization(winrt::hstring const& value);
		winrt::hstring SetRaw(winrt::hstring strAPI, winrt::hstring uid, time_t t, winrt::hstring method, winrt::hstring apiKey);
		winrt::hstring BikaEncryption(winrt::hstring strAPI, winrt::hstring uid, time_t t, winrt::hstring method, winrt::hstring apiKey, winrt::hstring strKey);
		winrt::Windows::Web::Http::Headers::HttpRequestHeaderCollection SetHeader(winrt::Windows::Web::Http::Headers::HttpRequestHeaderCollection headers, winrt::hstring strAPI, winrt::guid uuid, time_t t, winrt::hstring method);
		winrt::Windows::Web::Http::HttpResponseMessage GET(winrt::Windows::Foundation::Uri requestUri, winrt::hstring strAPI, winrt::guid uuid, winrt::hstring apiKey, winrt::hstring strKey);
		winrt::Windows::Web::Http::HttpResponseMessage POST(winrt::Windows::Foundation::Uri requestUri, winrt::Windows::Web::Http::HttpStringContent jsonContent, winrt::hstring strAPI, winrt::guid uuid);
		winrt::Windows::Web::Http::HttpResponseMessage Login(winrt::hstring account, winrt::hstring password);
	private:
		winrt::hstring m_authorization;
	};
}
namespace winrt::bikabika::factory_implementation
{
	struct BikaHttpClient : BikaHttpClientT<BikaHttpClient, implementation::BikaHttpClient>
	{
	};
}
