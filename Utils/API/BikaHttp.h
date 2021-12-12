#pragma once
#include "BikaHttp.g.h"


namespace winrt::bikabika::implementation
{
    struct BikaHttp : BikaHttpT<BikaHttp>
    {
        BikaHttp() = default;

        // ԭʼURL��ַ
        winrt::hstring SetRaw(winrt::hstring strAPI, winrt::hstring uid, time_t t, winrt::hstring method, winrt::hstring apiKey);
        //HMAC-SHA256ǩ����֤
        winrt::hstring BikaEncryption(winrt::hstring strAPI, winrt::hstring uid, time_t t, winrt::hstring method, winrt::hstring apiKey, winrt::hstring strKey);
        //��������ͷ
        winrt::Windows::Web::Http::Headers::HttpRequestHeaderCollection SetHeader(winrt::Windows::Web::Http::Headers::HttpRequestHeaderCollection headers, winrt::hstring strAPI, winrt::guid uuid, time_t t, winrt::hstring method);
        //GET����
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> GET(winrt::Windows::Foundation::Uri requestUri, winrt::hstring strAPI, winrt::guid uuid);
        //POST����
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring>  POST(winrt::Windows::Foundation::Uri requestUri, winrt::Windows::Web::Http::HttpStringContent jsonContent, winrt::hstring strAPI, winrt::guid uuid);
        void HttpLogOut(winrt::hstring s1, winrt::hstring s2);
        //��½��ȡtoken
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> Login(winrt::hstring account, winrt::hstring password);
        //��ȡ������Ϣ
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> PersonInfo();
        // ��ȡ��Ŀ¼
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> Categories();
        // ��Ҷ����ѵĹؼ���
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> Keywords();
        // ����
        Windows::Foundation::IAsyncOperation<hstring> Comics(int32_t page, hstring title, hstring sort);
        // ��ϸ
        Windows::Foundation::IAsyncOperation<hstring> BookInfo(hstring bookId);
        // �ֻ�
        Windows::Foundation::IAsyncOperation<hstring> Episodes(hstring bookId, int32_t page);
        // ����
        Windows::Foundation::IAsyncOperation<hstring> Picture(hstring bookId, int32_t epsId, int32_t page);
        // �ҵ��ղ�
        Windows::Foundation::IAsyncOperation<hstring> PersonFavourite(hstring sort, int32_t page);
        // �ҵ�����
        Windows::Foundation::IAsyncOperation<hstring> PersonComment(int32_t page);
        // ����
        Windows::Foundation::IAsyncOperation<hstring> Search(hstring keywords,hstring sort,Windows::Data::Json::JsonArray categories,int32_t page);



    
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct BikaHttp : BikaHttpT<BikaHttp, implementation::BikaHttp>
    {
    };
}
