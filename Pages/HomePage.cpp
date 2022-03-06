#include "pch.h"
#include "HomePage.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    HomePage::HomePage()
    {
        InitializeComponent();
    }

    int32_t HomePage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void HomePage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void HomePage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
   
        Button().Content(box_value(L"Clicked"));
        /*Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
        loginData.Values().Insert(L"token", box_value(L"sadf"));*/

    }
	
}
