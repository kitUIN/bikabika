#include "pch.h"
#include "MainPage.h"

#include "MainPage.g.cpp"
#include "Login.h"


using namespace std;
using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Numerics;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;

namespace winrt::bikabika::implementation
{
    ;
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

        auto Views = CoreApplication::Views();
        if (Views.Size() == 2)
            return;
        CoreDispatcher MainDispatcher =
            CoreApplication::GetCurrentView().Dispatcher();
        int32_t  ViewId = 0;
        // Create a new window.
        
        CoreApplicationView View = CoreApplication::CreateNewView();
        co_await resume_foreground(View.Dispatcher());

        // Show the "Loading..." screen.
        Windows::UI::Xaml::Controls::Frame f;
        f.Navigate(xaml_typename<bikabika::Login>(), nullptr);
        Window::Current().Content(f);
        
        //ApplicationView::PreferredLaunchViewSize();
        //ApplicationView::PreferredLaunchWindowingMode(ApplicationViewWindowingMode::Auto);
        Window::Current().Activate();

        //Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TryResizeView(Size(600, 400));
        
        ViewId = ApplicationView::GetForCurrentView().Id();
        
        // Activate the new window.
        co_await resume_foreground(MainDispatcher);
        
        co_await ApplicationViewSwitcher::TryShowAsStandaloneAsync(ViewId);
        
        // Start the emulation in the new window.
        co_await resume_foreground(View.Dispatcher());
        co_await ApplicationViewSwitcher::SwitchAsync(ViewId);

        //ApplicationView::GetForCurrentView().ExitFullScreenMode();
    }

  


    



 
    

    



}