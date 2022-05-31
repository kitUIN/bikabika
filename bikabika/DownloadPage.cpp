#include "pch.h"
#include "DownloadPage.h"
#if __has_include("DownloadPage.g.cpp")
#include "DownloadPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    DownloadPage::DownloadPage()
    {
        InitializeComponent();
    }

    int32_t DownloadPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void DownloadPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void DownloadPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
