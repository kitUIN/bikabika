/*****************************************************************//**
 * \file   SettingsPage.cpp
 * \brief  设置界面
 *
 * \author kulujun
 * \date   June 2022
 *********************************************************************/
#include "pch.h"
#include "SettingsPage.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::ViewManagement;
namespace winrt::bikabika::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();

    }

    double SettingsPage::SettingWidth()
    {
        return m_settingWidth;
    }
    double SettingsPage::SettingConentWidth()
    {
        return m_settingWidth-50;
    }
    void SettingsPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        __super::OnNavigatedTo(e);
        m_serverFlow = winrt::single_threaded_observable_vector<hstring>({ resourceLoader.GetString(L"Keyword/Flow/One"),resourceLoader.GetString(L"Keyword/Flow/Two"), resourceLoader.GetString(L"Keyword/Flow/Three") });
        m_flows      = winrt::single_threaded_observable_vector<hstring>({ resourceLoader.GetString(L"Keyword/Flow/One"),resourceLoader.GetString(L"Keyword/Flow/Two"), resourceLoader.GetString(L"Keyword/Flow/Three") });
        m_themes     = winrt::single_threaded_observable_vector<hstring>({ resourceLoader.GetString(L"Keyword/Theme/Light"), resourceLoader.GetString(L"Keyword/Theme/Dark") });
        SettingTheme().ItemsSource(box_value(m_themes));
        ElementTheme theme = Window::Current().Content().as<FrameworkElement>().RequestedTheme();
        if (theme == ElementTheme::Dark)
        {
            SettingTheme().SelectedIndex(1);
        }
        else
        {
            SettingTheme().SelectedIndex(0);
        }
        SettingAPPVersion().Content(box_value(rootPage.HttpClient().APPVersion()));
        SettingBikaClientFlow().ItemsSource(box_value(m_flows));
        SettingBikaClientFlow().SelectedIndex(0);
        SettingBikaClientServerFlow().ItemsSource(box_value(m_serverFlow));
        SettingBikaClientServerFlow().SelectedIndex(rootPage.HttpClient().APPChannel() - 1);
        PackageVersion version = Package::Current().Id().Version();
        SettingVersion().Content(box_value(to_hstring(version.Major) + L"." + to_hstring(version.Minor) + L"." + to_hstring(version.Build)));

    }
    winrt::event_token SettingsPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void SettingsPage::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

}


void winrt::bikabika::implementation::SettingsPage::BackGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& /*e*/)
{
    auto width = sender.as<Grid>().ActualWidth();
    if (width > 700)
    {
        m_settingWidth = width-100;

    }
    else m_settingWidth = 600;
    m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"SettingWidth" });
    m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"SettingConentWidth" });
}


void winrt::bikabika::implementation::SettingsPage::SettingBikaClientFlow_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
{

    auto mode = sender.as<ComboBox>().SelectedItem().as<hstring>();
    if (mode == resourceLoader.GetString(L"Keyword/Flow/Two"))
    {
        rootPage.HttpClient().FileServer(BikaClient::FileServerMode::S2);
    }
    else if (mode == resourceLoader.GetString(L"Keyword/Flow/Three"))
    {
        rootPage.HttpClient().FileServer(BikaClient::FileServerMode::S3);
    }
    else rootPage.HttpClient().FileServer(BikaClient::FileServerMode::S1);
}







void winrt::bikabika::implementation::SettingsPage::SettingTheme_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
{
    auto mode = sender.as<ComboBox>().SelectedItem().as<hstring>();
    Windows::Storage::ApplicationDataContainer settings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Settings", Windows::Storage::ApplicationDataCreateDisposition::Always);
    if (mode == resourceLoader.GetString(L"Keyword/Theme/Light"))
    {
        Window::Current().Content().as<FrameworkElement>().RequestedTheme(ElementTheme::Light);
        settings.Values().Insert(L"Theme", box_value(L"Light"));
    }
    else if (mode == resourceLoader.GetString(L"Keyword/Theme/Dark"))
    {
        Window::Current().Content().as<FrameworkElement>().RequestedTheme(ElementTheme::Dark);
        settings.Values().Insert(L"Theme", box_value(L"Dark"));
    }
}



void winrt::bikabika::implementation::SettingsPage::SettingBikaClientServerFlow_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
{
    auto mode = sender.as<ComboBox>().SelectedItem().as<hstring>();
    if (mode == resourceLoader.GetString(L"Keyword/Flow/Two"))
    {

    }
    else if (mode == resourceLoader.GetString(L"Keyword/Flow/Three"))
    {

    }

}


void winrt::bikabika::implementation::SettingsPage::LogButton_Click(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
{

}
