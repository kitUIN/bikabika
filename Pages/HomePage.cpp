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
    Windows::Foundation::IAsyncAction HomePage::ContentDialogShow(hstring const& mode, hstring const& message)
    {
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        if (mode == L"Timeout") {
            auto show{ PicErrorDialog().ShowAsync() };
        }
        else {
            HttpContentDialog().Title(box_value(resourceLoader.GetString(L"FailHttpTitle")));
            HttpContentDialog().CloseButtonText(resourceLoader.GetString(L"FailCloseButtonText"));
            if (mode == L"Error")
            {
                HttpContentDialog().Content(box_value(message));
                auto show{ co_await HttpContentDialog().ShowAsync() };

            }
            else if (mode == L"Unknown")
            {
                Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(message);
                HttpContentDialog().Content(box_value(to_hstring(resp.GetNamedNumber(L"code")) + L":" + resp.GetNamedString(L"message")));
                auto show{ co_await HttpContentDialog().ShowAsync() };

            }
            else if (mode == L"1005")
            {
                HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailAuth")));
                extern bool m_login;
                m_login = false;
                auto show{ co_await HttpContentDialog().ShowAsync() };
                if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None)
                {
                    auto loginTeachingTip = Frame().Parent().as<Microsoft::UI::Xaml::Controls::NavigationView>().Parent().as<Windows::UI::Xaml::Controls::Grid>().Children().GetAt(3).as<Microsoft::UI::Xaml::Controls::TeachingTip>();
                    Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
                    loginTeachingTip.Title(resourceLoader.GetString(L"LoginButton/Content"));
                    loginTeachingTip.IsOpen(true);
                }
            }
        }

    }
}
