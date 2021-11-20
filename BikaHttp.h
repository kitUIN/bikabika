#pragma once
#include "BikaHttp.g.h"


namespace winrt::bikabika::implementation
{
    struct BikaHttp : BikaHttpT<BikaHttp>
    {
        BikaHttp() = default;

        hstring Auth();
        void Auth(hstring const& value);
        hstring ImageQuality();
        void ImageQuality(hstring const& value);
        
        // 原始URL地址
        winrt::hstring SetRaw(winrt::hstring strAPI, winrt::hstring uid, time_t t, winrt::hstring method, winrt::hstring apiKey);
        //HMAC-SHA256签名验证
        winrt::hstring BikaEncryption(winrt::hstring strAPI, winrt::hstring uid, time_t t, winrt::hstring method, winrt::hstring apiKey, winrt::hstring strKey);
        //生成请求头
        winrt::Windows::Web::Http::Headers::HttpRequestHeaderCollection SetHeader(winrt::Windows::Web::Http::Headers::HttpRequestHeaderCollection headers, winrt::hstring strAPI, winrt::guid uuid, time_t t, winrt::hstring method);
        //GET类型
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> GET(winrt::Windows::Foundation::Uri requestUri, winrt::hstring strAPI, winrt::guid uuid);
        //POST类型
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring>  POST(winrt::Windows::Foundation::Uri requestUri, winrt::Windows::Web::Http::HttpStringContent jsonContent, winrt::hstring strAPI, winrt::guid uuid);
        void HttpLogOut(winrt::hstring s1, winrt::hstring s2);
        //登陆获取token
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> Login(winrt::hstring account, winrt::hstring password);
        //获取个人信息
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> PersonInfo();
        // 获取主目录
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> Categories();
        // 大家都在搜的关键字
        winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> Keywords();

    private:
        winrt::hstring m_auth;
        winrt::hstring m_imageQuality= L"medium";

    };
}
namespace winrt::bikabika::factory_implementation
{
    struct BikaHttp : BikaHttpT<BikaHttp, implementation::BikaHttp>
    {
    };
}
