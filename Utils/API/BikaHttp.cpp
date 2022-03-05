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
	unsigned char ToHex(unsigned char x)
	{
		return  x > 9 ? x + 55 : x + 48;
	}

	unsigned char FromHex(unsigned char x)
	{
		unsigned char y;
		if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
		else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
		else if (x >= '0' && x <= '9') y = x - '0';
		else assert(0);
		return y;
	}

	std::string UrlEncode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (isalnum((unsigned char)str[i]) ||
				(str[i] == '-') ||
				(str[i] == '_') ||
				(str[i] == '.') ||
				(str[i] == '~'))
				strTemp += str[i];
			else if (str[i] == ' ')
				strTemp += "+";
			else
			{
				strTemp += '%';
				strTemp += ToHex((unsigned char)str[i] >> 4);
				strTemp += ToHex((unsigned char)str[i] % 16);
			}
		}
		return strTemp;
	}
	
	hstring BikaHttp::SetRaw(hstring strAPI, hstring uid, time_t t, hstring method, hstring apiKey)
	{   // ԭʼURL��ַ
		hstring raw = strAPI + to_hstring(t) + uid + method + apiKey;
		string ras = to_string(raw);
		transform(ras.begin(), ras.end(), ras.begin(), ::tolower);
		raw = to_hstring(ras);
		return raw;
	}
	hstring BikaHttp::BikaEncryption(hstring strAPI, hstring uid, time_t t, hstring method, hstring apiKey, hstring strKey)
	{   //HMAC-SHA256ǩ����֤
		auto encoding = BinaryStringEncoding::Utf8;
		IBuffer buffMsg = CryptographicBuffer::ConvertStringToBinary(SetRaw(strAPI, uid, t, method, apiKey), encoding);
		//std::wcout << SetRaw(strAPI, uid, t, method, apiKey).c_str() << std::endl;
		IBuffer buffPublicKey = CryptographicBuffer::ConvertStringToBinary(strKey, encoding);
		MacAlgorithmProvider objMacProv = MacAlgorithmProvider::OpenAlgorithm(MacAlgorithmNames::HmacSha256());
		auto hash = objMacProv.CreateHash(buffPublicKey);
		hash.Append(buffMsg);
		hstring res = CryptographicBuffer::EncodeToHexString(hash.GetValueAndReset());
		wcout << res.c_str() << endl;
		return res;
	}
	HttpRequestHeaderCollection BikaHttp::SetHeader(HttpRequestHeaderCollection headers, hstring strAPI, guid uuid, time_t t, hstring method)
	{   //��������ͷ
		string uid = to_string(to_hstring(uuid)).substr(1, 36);
		remove(uid.begin(), uid.end(), '-');
		uid.substr(1, 32);
		Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
		extern winrt::hstring imageQuality;
		headers.Insert(L"api-key", L"C69BAF41DA5ABD1FFEDC6D2FEA56B");
		headers.Insert(L"accept", L"application/vnd.picacomic.com.v1+json");
		headers.Insert(L"app-channel", L"3");
		headers.Insert(L"time", to_hstring(t));
		headers.Insert(L"signature", L"encrypt");
		headers.Insert(L"app-version", L"2.2.1.2.3.4");
		headers.Insert(L"nonce", L"b1ab87b4800d4d4590a11701b8551afa");
		headers.Insert(L"app-uuid", L"defaultUuid");//418e56fb-60fb-352b-8fca-c6e8f0737ce6
		headers.Insert(L"app-platform", L"android");
		headers.Insert(L"image-quality", imageQuality);
		headers.Insert(L"app-build-version", L"45");
		headers.Insert(L"User-Agent", L"okhttp/3.8.1");
		//headers.Insert(L"Content-Type", L"application/json; charset=UTF-8");
		headers.Insert(L"signature", BikaEncryption(strAPI, L"b1ab87b4800d4d4590a11701b8551afa", t, method, L"c69baf41da5abd1ffedc6d2fea56b", L"~d}$Q7$eIni=V)9\\RK/P.RM4;9[7|@/CA}b~OW!3?EV`:<>M7pddUBL5n|0/*Cn"));
		if (auto s =loginData.Values().TryLookup(L"token"))
		{	
			headers.Insert(L"Authorization", unbox_value<hstring>(s));
		}
		return headers;
	}
	IAsyncOperation<hstring> BikaHttp::GET(Uri requestUri, hstring strAPI, guid uuid)
	{   //GET����
		HttpClient httpClient;
		HttpRequestMessage httpRequestMessage;
		HttpResponseMessage httpResponseMessage;
		time_t t = time(NULL);
		httpRequestMessage.Method(HttpMethod::Get());
		httpRequestMessage.RequestUri(requestUri);
		httpRequestMessage.Headers() = SetHeader(httpRequestMessage.Headers(), strAPI, uuid, t, L"GET");
		//httpRequestMessage.Content().Headers().ContentType(HttpMediaTypeHeaderValue(L"application/json; charset=UTF-8"));

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
				co_return L"[TimeOut]" + message;
			}
			else
			{
				co_return L"[ERROR]" + message;
			}
		}
	}
	IAsyncOperation<hstring>  BikaHttp::POST(Uri requestUri, HttpStringContent jsonContent, hstring strAPI, guid uuid)
	{   //POST����
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
				co_return L"[TimeOut]" + message;
			}
			else
			{
				co_return L"[ERROR]" + message;
			}
		}
		
	}
	IAsyncOperation<hstring>  BikaHttp::PUT(Uri requestUri, HttpStringContent jsonContent, hstring strAPI, guid uuid)
	{   //POST����
		HttpClient httpClient;
		HttpRequestMessage httpRequestMessage;
		//HttpResponseMessage httpResponseMessage;
		time_t t = time(NULL);
		httpRequestMessage.Method(HttpMethod::Put());
		httpRequestMessage.RequestUri(requestUri);
		httpRequestMessage.Headers() = SetHeader(httpRequestMessage.Headers(), strAPI, uuid, t, L"PUT");
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
				co_return L"[TimeOut]" + message;
			}
			else
			{
				co_return L"[ERROR]" + message;
			}
		}

	}
	//��½��ȡtoken
	IAsyncOperation<hstring> BikaHttp::Login(hstring account, hstring password)
	{   
		Uri requestUri{ L"https://picaapi.picacomic.com/auth/sign-in" };
		guid uuid = GuidHelper::CreateNewGuid();
		HttpStringContent jsonContent(
			L"{ \"email\": \"" + account + L"\", \"password\": \"" + password + L"\" }",
			UnicodeEncoding::Utf8,
			L"application/json");
		auto ress = co_await POST(requestUri, jsonContent, L"auth/sign-in", uuid);
		HttpLogOut(L"[POST]->/auth/sign-in\nReturn:", ress.c_str());
		co_return ress;
	}
	void BikaHttp::HttpLogOut(hstring s1, hstring s2)
	{
		OutputDebugStringW(L"\n");
		OutputDebugStringW(s1.c_str());
		OutputDebugStringW(L"\n");
		OutputDebugStringW(s2.c_str());
		OutputDebugStringW(L"\n");
	}
	//��ȡ������Ϣ
	IAsyncOperation<hstring> BikaHttp::PersonInfo()
	{   /*
		{
		"code":200,
		"message":"success",
		"data":
		{
			"user":
			{
				"_id":"  ",
				"birthday":"1999-03-02T00:00:00.000Z",
				"email":"kuluju",
				"gender":"m",
				"name":"��¶��",
				"slogan":"ֻҪ�岻�����������",
				"title":"����",
				"verified":false,
				"exp":1320,
				"level":4,
				"characters":[],
				"created_at":"2018-03-02T15:39:24.530Z",
				"avatar":
				{
					"fileServer":"https://storage1.picacomic.com",
					"path":"81e4-46a5-9206-c424226bed07.jpg",
					"originalName":"avatar.jpg"
				},
				"isPunched":false,
				"character":"https://pica-web.wakamoment.tk/images/halloween_m.png"
			}
		}
		}
		*/
		
		Uri requestUri{ L"https://picaapi.picacomic.com/users/profile" };
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(requestUri, L"users/profile", uuid);
		HttpLogOut(L"[GET]->/users/profile\nReturn:", res.c_str());
		co_return res;
		
	}
	// ��ȡ��Ŀ¼
	IAsyncOperation<hstring> BikaHttp::Categories()
	{	
		Uri requestUri{ L"https://picaapi.picacomic.com/categories" };
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(requestUri, L"categories", uuid);
		HttpLogOut(L"[GET]->/categories\nReturn:", res.c_str());
		co_return res;
	}
	// ��Ҷ����ѵĹؼ���
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Keywords()
	{
		
		Uri requestUri{ L"https://picaapi.picacomic.com/keywords" };
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(requestUri, L"keywords", uuid);
		HttpLogOut(L"[GET]->/keywords\nReturn:", res.c_str());
		co_return res;
	}
	// ����
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Comics(int32_t page,hstring title,hstring sort)
	{
		
		 
		
		hstring api = L"comics?page=" + to_hstring(page) + L"&c=" + to_hstring(UrlEncode(to_string(title))) + L"&s=" + sort;
		Uri uri = Uri{ L"https://picaapi.picacomic.com/"+api};
		//OutputDebugStringW(api.c_str());
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(uri, api, uuid);
		HttpLogOut(L"[GET]->/" + api + L"\nReturn:", res.c_str());
		co_return res;
	}
	// ����
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::BookInfo(hstring bookId)
	{

		hstring api = L"comics/" + bookId;
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };

		//OutputDebugStringW(api.c_str());
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(uri, api, uuid);
		HttpLogOut(L"[GET]->/"+ api+L"\nReturn:", res.c_str());
		co_return res;
	}
	// �ֻ�
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Episodes(hstring bookId,int32_t page)
	{

		hstring api = L"comics/" + bookId+L"/eps?page="+to_hstring(page);
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };

		//OutputDebugStringW(api.c_str());
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(uri, api, uuid);
		HttpLogOut(L"[GET]->/" + api + L"\nReturn:", res.c_str());
		co_return res;
	}
	// ��������
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Picture(hstring bookId, int32_t epsId, int32_t page)
	{

		hstring api = L"comics/" + bookId + L"/order/" + to_hstring(epsId) +L"/pages?page="+ to_hstring(page);
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };

		//OutputDebugStringW(api.c_str());
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(uri, api, uuid);
		HttpLogOut(L"[GET]->/" + api + L"\nReturn:", res.c_str());
		co_return res;
	}
	// �ҵ��ղ�
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::PersonFavourite(hstring sort, int32_t page)
	{
		hstring api = L"users/favourite?s="+sort+ L"&page=" + to_hstring(page);
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		//OutputDebugStringW(api.c_str());
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(uri, api, uuid);
		HttpLogOut(L"[GET]->/" + api + L"\nReturn:", res.c_str());
		co_return res;
	}
	// �ҵ�����
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::PersonComment(int32_t page)
	{
		hstring api = L"users/my-comments?page=" + to_hstring(page);
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		//OutputDebugStringW(api.c_str());
		guid uuid = GuidHelper::CreateNewGuid();
		hstring res = co_await GET(uri, api, uuid);
		HttpLogOut(L"[GET]->/" + api + L"\nReturn:", res.c_str());
		co_return res;
	}
	// ����
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Search(hstring keywords, hstring sort, Windows::Data::Json::JsonArray categories, int32_t page)
	{

		hstring api = L"comics/advanced-search?page=" + to_hstring(page);
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		guid uuid = GuidHelper::CreateNewGuid();
		Windows::Data::Json::JsonObject json;
		json.SetNamedValue(L"keyword", Windows::Data::Json::JsonValue::CreateStringValue(keywords));
		if (categories.Size() > 0)
		{
			json.SetNamedValue(L"categories", categories);
		}
		json.SetNamedValue(L"sort", Windows::Data::Json::JsonValue::CreateStringValue(sort));
		HttpStringContent jsonContent(
			json.ToString(),
			UnicodeEncoding::Utf8,
			L"application/json");
		auto ress = co_await POST(uri, jsonContent, api, uuid);
		HttpLogOut(L"[Post]->/" + api + L"\nReturn:", ress.c_str());
		co_return ress;
	}
	// �ղ�
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Favourite(hstring bookId)
	{

		hstring api = L"comics/"+ to_hstring(bookId)+L"/favourite" ;
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		guid uuid = GuidHelper::CreateNewGuid();
		HttpStringContent jsonContent(
			L"",
			UnicodeEncoding::Utf8,
			L"application/json");
		auto ress = co_await POST(uri, jsonContent, api, uuid);
		HttpLogOut(L"[Post]->/" + api + L"\nReturn:", ress.c_str());
		co_return ress;
	}
	// ����
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Like(hstring bookId)
	{

		hstring api = L"comics/" + to_hstring(bookId) + L"/like";
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		guid uuid = GuidHelper::CreateNewGuid();
		HttpStringContent jsonContent(
			L"",
			UnicodeEncoding::Utf8,
			L"application/json");
		auto ress = co_await POST(uri, jsonContent, api, uuid);
		HttpLogOut(L"[Post]->/" + api + L"\nReturn:", ress.c_str());
		co_return ress;
	}
	// ��ȡ����
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::Comments(hstring bookId, int32_t page)
	{
		hstring api = L"comics/" + to_hstring(bookId) + L"/comments?page="+ to_hstring(page);
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		guid uuid = GuidHelper::CreateNewGuid();
		auto ress = co_await GET(uri, api, uuid);
		HttpLogOut(L"[Get]->/" + api + L"\nReturn:", ress.c_str());
		co_return ress;
	}
	// ��������
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::SendComments(hstring bookId, hstring content)
	{
		hstring api = L"comics/" + to_hstring(bookId) + L"/comments";
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		guid uuid = GuidHelper::CreateNewGuid();
		HttpStringContent jsonContent(
			L"{\"content\":\""+content+L"\"}",
			UnicodeEncoding::Utf8,
			L"application/json");
		auto ress = co_await POST(uri, jsonContent, api, uuid);
		HttpLogOut(L"[Post]->/" + api + L"\nReturn:", ress.c_str());
		co_return ress;
	}
	// ��
	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::PunchIn()
	{
		hstring api = L"users/punch-in";
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		guid uuid = GuidHelper::CreateNewGuid();
		HttpStringContent jsonContent(
			L"",
			UnicodeEncoding::Utf8,
			L"application/json");
		auto ress = co_await POST(uri, jsonContent, api, uuid);
		HttpLogOut(L"[Post]->/" + api + L"\nReturn:", ress.c_str());
		co_return ress;
	}

	Windows::Foundation::IAsyncOperation<hstring> BikaHttp::SetSlogan(hstring slogan)
	{

		hstring api = L"users/profile";
		Uri uri = Uri{ L"https://picaapi.picacomic.com/" + api };
		guid uuid = GuidHelper::CreateNewGuid();
		HttpStringContent jsonContent(
			L"{\"slogan\":\"" + slogan + L"\"}",
			UnicodeEncoding::Utf8,
			L"application/json");
		auto ress = co_await PUT(uri, jsonContent, api, uuid);
		HttpLogOut(L"[Put]->/" + api + L"\nReturn:", ress.c_str());
		co_return ress;
	}

}
