#include "pch.h"
#include "SettingsPage.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
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
    winrt::event_token SettingsPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void SettingsPage::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

}


void winrt::bikabika::implementation::SettingsPage::BackGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e)
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


void winrt::bikabika::implementation::SettingsPage::SettingBikaClientFlow_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
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


void winrt::bikabika::implementation::SettingsPage::SettingBikaClientFlow_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    m_flows.Append(resourceLoader.GetString(L"Keyword/Flow/One"));
    m_flows.Append(resourceLoader.GetString(L"Keyword/Flow/Two"));
    m_flows.Append(resourceLoader.GetString(L"Keyword/Flow/Three"));
    sender.as<ComboBox>().ItemsSource(box_value(m_flows));
    sender.as<ComboBox>().SelectedIndex(0);
}
