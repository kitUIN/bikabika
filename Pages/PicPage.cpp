#include "pch.h"
#include "PicPage.h"
#if __has_include("PicPage.g.cpp")
#include "PicPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    PicPage::PicPage()
    {
        InitializeComponent();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<bikabika::PicturesBlock> PicPage::PicturesBlocks()
    {
        return m_picturesBlocks;
    }
    Windows::Foundation::IAsyncAction PicPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        auto params = winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>(e.Parameter());
        m_bookId = params.GetAt(0).as<hstring>();
        m_id = params.GetAt(1).as<hstring>();
        m_order = params.GetAt(2).as<int32_t>();
        m_epsTotal = params.GetAt(3).as<int32_t>();
        __super::OnNavigatedTo(e);
        co_await Goto(m_order, 1);
        
    }
   
    Windows::Foundation::IAsyncAction PicPage::Goto(int32_t const& order, int32_t const& page)
    {
        
        auto res{ co_await m_bikaHttp.Picture(m_bookId, order, page) };
        if (res[1] == 'T')
        {
            rootPage.ContentDialogShow(L"Timeout", L"");
        }
        else if (res[1] == 'E') {
            rootPage.ContentDialogShow(L"Error", res);
        }
        else
        {
            Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(res);
            double code = resp.GetNamedNumber(L"code");
            if (code == (double)200)
            {
                Windows::Data::Json::JsonObject ca = resp.GetNamedObject(L"data");
                Windows::Data::Json::JsonObject json = ca.GetNamedObject(L"pages");
                m_pageTotal = json.GetNamedNumber(L"total");
                m_pageLimit = json.GetNamedNumber(L"limit");
                m_page = json.GetNamedNumber(L"page");
                m_pages = json.GetNamedNumber(L"pages");
                for (auto x : json.GetNamedArray(L"docs"))
                {
                    auto docs = x.GetObject();
                    Windows::Storage::ApplicationDataContainer serversSettings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Servers", Windows::Storage::ApplicationDataCreateDisposition::Always);
                    hstring path = unbox_value<winrt::hstring>(serversSettings.Values().Lookup(L"picServersCurrent")) + L"/static/" + docs.GetNamedObject(L"media").GetNamedString(L"path");
                    auto pic = winrt::make<PicturesBlock>(path);
                    pic.Order(to_hstring(m_pageOrder));
                    m_picturesBlocks.Append(pic);
                    m_pageOrder++;
                }
                if (m_page < m_pages)
                {
                    co_await Goto(m_order, m_page + 1);
                }
                
            }
            else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
            {
                rootPage.ContentDialogShow(L"1005", L"");
            }
            //未知
            else
            {
                rootPage.ContentDialogShow(L"Unknown", res);
            }
        }
    }
    void winrt::bikabika::implementation::PicPage::ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e)
    {
        auto sv = sender.as<winrt::Windows::UI::Xaml::Controls::ScrollViewer>();
        if (sv.VerticalOffset() + sv.ActualHeight() + 2 >= sv.ExtentHeight()) {
            if (m_order < m_epsTotal)
            {
                DownEps().IsOpen(true);
            }
        }
       
    }
    Windows::Foundation::IAsyncAction winrt::bikabika::implementation::PicPage::DownEps_ActionButtonClick(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& sender, winrt::Windows::Foundation::IInspectable const& args)
    {
        m_order++;
        m_pageOrder = 1;
        m_picturesBlocks.Clear();
        co_await Goto(m_order, 1);
        DownEps().IsOpen(false);
    }
}






