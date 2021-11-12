#include "pch.h"
#include "BikaHttp.h"
#include "BikaHttp.g.cpp"
using namespace winrt;
using namespace std;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;
using namespace Windows::Security::Cryptography::Core;
using namespace Windows::Security::Cryptography;
using namespace Windows::Storage::Streams;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Headers;

namespace winrt::bikabika::implementation
{
	hstring BikaHttp::Auth()
	{
		return m_auth;
	}
	void BikaHttp::Auth(hstring const& value)
	{
		if (m_auth != value) m_auth = value;
	}
	hstring BikaHttp::SetRaw(hstring strAPI, hstring uid, time_t t, hstring method, hstring apiKey)
	{   // 原始URL地址
		hstring raw = strAPI + to_hstring(t) + uid + method + apiKey;
		string ras = to_string(raw);
		transform(ras.begin(), ras.end(), ras.begin(), ::tolower);
		raw = to_hstring(ras);
		return raw;
	}
	hstring BikaHttp::BikaEncryption(hstring strAPI, hstring uid, time_t t, hstring method, hstring apiKey, hstring strKey)
	{   //HMAC-SHA256签名验证
		auto encoding = BinaryStringEncoding::Utf8;
		IBuffer buffMsg = CryptographicBuffer::ConvertStringToBinary(SetRaw(strAPI, uid, t, method, apiKey), encoding);
		std::wcout << SetRaw(strAPI, uid, t, method, apiKey).c_str() << std::endl;
		IBuffer buffPublicKey = CryptographicBuffer::ConvertStringToBinary(strKey, encoding);
		MacAlgorithmProvider objMacProv = MacAlgorithmProvider::OpenAlgorithm(MacAlgorithmNames::HmacSha256());
		auto hash = objMacProv.CreateHash(buffPublicKey);
		hash.Append(buffMsg);
		hstring res = CryptographicBuffer::EncodeToHexString(hash.GetValueAndReset());
		wcout << res.c_str() << endl;
		return res;
	}
	HttpRequestHeaderCollection BikaHttp::SetHeader(HttpRequestHeaderCollection headers, hstring strAPI, guid uuid, time_t t, hstring method)
	{   //生成请求头
		string uid = to_string(to_hstring(uuid)).substr(1, 36);
		remove(uid.begin(), uid.end(), '-');
		uid.substr(1, 32);
		headers.Insert(L"api-key", L"C69BAF41DA5ABD1FFEDC6D2FEA56B");
		headers.Insert(L"accept", L"application/vnd.picacomic.com.v1+json");
		headers.Insert(L"app-channel", L"2");
		headers.Insert(L"time", to_hstring(t));
		headers.Insert(L"signature", L"encrypt");
		headers.Insert(L"app-version", L"2.2.1.2.3.4");
		headers.Insert(L"nonce", to_hstring(uid));
		headers.Insert(L"app-uuid", L"418e56fb-60fb-352b-8fca-c6e8f0737ce6");
		headers.Insert(L"app-platform", L"android");
		headers.Insert(L"app-build-version", L"45");
		headers.Insert(L"User-Agent", L"okhttp/3.8.1");
		headers.Insert(L"signature", BikaEncryption(strAPI, to_hstring(uid), t, method, L"C69BAF41DA5ABD1FFEDC6D2FEA56B", L"~d}$Q7$eIni=V)9\\RK/P.RM4;9[7|@/CA}b~OW!3?EV`:<>M7pddUBL5n|0/*Cn"));
		return headers;
	}
	IAsyncOperation<hstring> BikaHttp::GET(Uri requestUri, hstring strAPI, guid uuid, hstring apiKey, hstring strKey)
	{   //GET类型
		HttpClient httpClient;
		HttpRequestMessage httpRequestMessage;
		HttpResponseMessage httpResponseMessage;
		time_t t = time(NULL);
		httpRequestMessage.Method(HttpMethod::Get());
		httpRequestMessage.RequestUri(requestUri);
		httpRequestMessage.Headers() = SetHeader(httpRequestMessage.Headers(), strAPI, uuid, t, L"GET");
		try
		{
			HttpResponseMessage res{ co_await httpClient.SendRequestAsync(httpRequestMessage) };
			co_return co_await res.Content().ReadAsStringAsync();
		}
		catch (winrt::hresult_error const& ex)
		{
			winrt::hstring message = ex.message();
			winrt::hresult hr = ex.code(); // HRESULT_FROM_WIN32(WININET_E_CANNOT_CONNECT).
			if (hr == WININET_E_CANNOT_CONNECT) {
				OutputDebugStringW(message.c_str());
				co_return L"[ERROR]" + message;
			}
			else
			{
				co_return L"[ERROR]"+ message;
			}
		}
	}
	IAsyncOperation<hstring>  BikaHttp::POST(Uri requestUri, HttpStringContent jsonContent, hstring strAPI, guid uuid)
	{   //POST类型
		HttpClient httpClient;
		HttpRequestMessage httpRequestMessage;
		//HttpResponseMessage httpResponseMessage;
		time_t t = time(NULL);
		httpRequestMessage.Method(HttpMethod::Post());
		httpRequestMessage.RequestUri(requestUri);
		httpRequestMessage.Headers() = SetHeader(httpRequestMessage.Headers(), strAPI, uuid, t, L"POST");
		httpRequestMessage.Content(jsonContent);
		try
		{
			HttpResponseMessage res{ co_await httpClient.SendRequestAsync(httpRequestMessage) };
			co_return co_await res.Content().ReadAsStringAsync();
		}
		catch (winrt::hresult_error const& ex)
		{
			winrt::hstring message = ex.message(); 
			winrt::hresult hr = ex.code(); // HRESULT_FROM_WIN32(WININET_E_CANNOT_CONNECT).
			if (hr == WININET_E_CANNOT_CONNECT) {
				OutputDebugStringW(message.c_str());
				co_return L"[ERROR]" + message;
			}
			else
			{
				co_return L"[ERROR]" + message;
			}
		}
		
	}
	IAsyncOperation<hstring> BikaHttp::Login(hstring account, hstring password)
	{   //登陆获取token
		Uri requestUri{ L"https://picaapi.picacomic.com/auth/sign-in" };
		guid uuid = GuidHelper::CreateNewGuid();
		HttpStringContent jsonContent(
			L"{ \"email\": \"" + account + L"\", \"password\": \"" + password + L"\" }",
			UnicodeEncoding::Utf8,
			L"application/json");
		co_return co_await POST(requestUri, jsonContent, L"auth/sign-in", uuid);
	}
}
