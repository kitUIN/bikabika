#include "pch.h"
#include "MainPage.h"

#include "MainPage.g.cpp"
#include "Login.h"

using namespace std;
using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace std;

namespace winrt::bikabika::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
        
        Window::Current().SetTitleBar(AppTitleBar());
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    

    // List of ValueTuple holding the Navigation Tag and the relative Navigation Page
    std::vector<std::pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>> m_pages;

    void MainPage::NavView_Loaded(
        Windows::Foundation::IInspectable const& /* sender */,
        Windows::UI::Xaml::RoutedEventArgs const& /* args */)
    {
        
        NavView().MenuItems().Append(muxc::NavigationViewItemSeparator());
        muxc::NavigationViewItem navigationViewItem;
        navigationViewItem.Content(winrt::box_value(L"My content"));
        navigationViewItem.Icon(wuxc::SymbolIcon(static_cast<wuxc::Symbol>(0xF1AD)));
        navigationViewItem.Tag(winrt::box_value(L"content"));

        NavView().MenuItems().Append(navigationViewItem);
        

        NavView().SelectedItem(NavView().MenuItems().GetAt(0));
        NavView_Navigate(L"home",
            Windows::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());

    }

    void MainPage::NavView_ItemInvoked(
        Windows::Foundation::IInspectable const& /* sender */,
        muxc::NavigationViewItemInvokedEventArgs const& args)
    {
        if (args.IsSettingsInvoked())
        {
            NavView_Navigate(L"settings", args.RecommendedNavigationTransitionInfo());
        }
        else if (args.InvokedItemContainer())
        {
            NavView_Navigate(
                winrt::unbox_value_or<winrt::hstring>(
                    args.InvokedItemContainer().Tag(), L"").c_str(),
                args.RecommendedNavigationTransitionInfo());
        }
    }

    // NavView_SelectionChanged is not used in this example, but is shown for completeness.
    // You will typically handle either ItemInvoked or SelectionChanged to perform navigation,
    // but not both.
    void MainPage::NavView_SelectionChanged(
        muxc::NavigationView const& /* sender */,
        muxc::NavigationViewSelectionChangedEventArgs const& args)
    {
        if (args.IsSettingsSelected())
        {
            NavView_Navigate(L"settings", args.RecommendedNavigationTransitionInfo());
        }
        else if (args.SelectedItemContainer())
        {
            NavView_Navigate(
                winrt::unbox_value_or<winrt::hstring>(
                    args.SelectedItemContainer().Tag(), L"").c_str(),
                args.RecommendedNavigationTransitionInfo());
        }
    }

    void MainPage::NavView_Navigate(
        std::wstring navItemTag,
        Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo)
    {
        Windows::UI::Xaml::Interop::TypeName pageTypeName;
        if (navItemTag == L"settings")
        {
           
        }
        else
        {
            for (auto&& eachPage : m_pages)
            {
                if (eachPage.first == navItemTag)
                {
                    pageTypeName = eachPage.second;
                    break;
                }
            }
        }
        // Get the page type before navigation so you can prevent duplicate
        // entries in the backstack.
        Windows::UI::Xaml::Interop::TypeName preNavPageType =
            ContentFrame().CurrentSourcePageType();

        // Navigate only if the selected page isn't currently loaded.
        if (pageTypeName.Name != L"" && preNavPageType.Name != pageTypeName.Name)
        {
            ContentFrame().Navigate(pageTypeName, nullptr, transitionInfo);
        }
    }


    Windows::Foundation::IAsyncAction MainPage::CreateLoginPage(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        OutputDebugStringW((L"\n Entered the function : " + std::to_wstring(GetCurrentThreadId()) + L"\n").c_str());

        auto coreView = winrt::Windows::ApplicationModel::Core::CoreApplication::CreateNewView();

        OutputDebugStringW((L"\n Created the view : " + std::to_wstring(GetCurrentThreadId()) + L"\n").c_str());

        co_await resume_foreground(coreView.Dispatcher());
        auto appView = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();
        auto m_window_debug = Windows::UI::Core::CoreWindow::GetForCurrentThread();
        OutputDebugStringW((L"\n Switched thread : " + std::to_wstring(GetCurrentThreadId()) + L"\n").c_str());

        hstring newTitle = L"my new window";
        appView.Title(newTitle);
        OutputDebugStringW((L"\n Set new title : " + std::to_wstring(GetCurrentThreadId()) + L"\n").c_str());
        m_window_debug.Activate();
        OutputDebugStringW((L"\n Registered the callback : " + std::to_wstring(GetCurrentThreadId()) + L"\n").c_str());
        co_await resume_foreground(coreView.Dispatcher());
        Windows::UI::Core::CoreWindow::GetForCurrentThread().Activate();
        OutputDebugStringW((L"\n After activation : " + std::to_wstring(static_cast<int>(m_window_debug.ActivationMode())) + L"\n").c_str());

    }

  


    



 
    

    



}