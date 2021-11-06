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
    Windows::Foundation::IAsyncAction HomePage::ExampleCoroutineAsync()
    {

        Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
        Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };

        co_await folder.CreateFileAsync(L"account.json", Windows::Storage::CreationCollisionOption::OpenIfExists);

    }
    void HomePage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {

        Button().Content(box_value(L"Clicked"));
        auto processOp{ ExampleCoroutineAsync() };
    }
    
}
