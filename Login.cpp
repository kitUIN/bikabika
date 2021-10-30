#include "pch.h"
#include "Login.h"
#if __has_include("Login.g.cpp")
#include "Login.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::ViewManagement;
using namespace Windows::Foundation;

namespace winrt::bikabika::implementation
{
    Login::Login()
    {
        InitializeComponent();

        
    }

    int32_t Login::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Login::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Login::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
        Window::Current().Close();
    }
}
