#include "pch.h"
#include "ClassificationPage.h"
#if __has_include("ClassificationPage.g.cpp")
#include "ClassificationPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    ClassificationPage::ClassificationPage()
    {
        InitializeComponent();
    }

    int32_t ClassificationPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ClassificationPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ClassificationPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
