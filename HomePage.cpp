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
    Windows::Foundation::IAsyncAction HomePage::ExampleCoroutineAsync()
    {

        Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
        Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };

        co_await folder.CreateFileAsync(L"account.json", Windows::Storage::CreationCollisionOption::OpenIfExists);
        
    }
    void HomePage::SetText(hstring str)
    {
       
        OutputDebugStringW(str.c_str());
    }
    void HomePage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        SetText(winrt::unbox_value<winrt::hstring>(e.Parameter()));

        __super::OnNavigatedTo(e);
    }
}
