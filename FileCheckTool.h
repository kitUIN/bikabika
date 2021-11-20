#pragma once
#include "FileCheckTool.g.h"


namespace winrt::bikabika::implementation
{
    struct FileCheckTool : FileCheckToolT<FileCheckTool>
    {
        FileCheckTool() = default;
        
        Windows::Foundation::IAsyncOperation<bool> CheckFileAccount();
        Windows::Foundation::IAsyncOperation<bool> CheckFileUser();
        Windows::Foundation::IAsyncOperation <Windows::Data::Json::JsonObject> GetAccount();
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct FileCheckTool : FileCheckToolT<FileCheckTool, implementation::FileCheckTool>
    {
    };
}
