#pragma once
#include "FileCheckTool.g.h"


namespace winrt::bikabika::implementation
{
    struct FileCheckTool : FileCheckToolT<FileCheckTool>
    {
        FileCheckTool() = default;
        
        Windows::Foundation::IAsyncOperation<bool> CheckFileAccount();
        Windows::Foundation::IAsyncOperation<bool> CheckHistory();
        Windows::Foundation::IAsyncOperation<bool> CheckFileUser();
        Windows::Foundation::IAsyncOperation<bool> CheckFileKeywords();
        Windows::Foundation::IAsyncOperation<bool> CheckFileSettings();
        Windows::Foundation::IAsyncOperation<bool> CheckFileSearchHistory();
        Windows::Foundation::IAsyncOperation <Windows::Data::Json::JsonObject> GetAccount();
        Windows::Foundation::IAsyncAction SetAccount(Windows::Data::Json::JsonObject value);
        Windows::Foundation::IAsyncOperation <Windows::Data::Json::JsonObject> GetUser();
        Windows::Foundation::IAsyncAction SetUser(Windows::Data::Json::JsonObject value);
        Windows::Foundation::IAsyncOperation <Windows::Data::Json::JsonObject> GetKeywords();
        Windows::Foundation::IAsyncAction SetKeywords(Windows::Data::Json::JsonObject value);
        Windows::Foundation::IAsyncOperation <Windows::Data::Json::JsonObject> GetSettings();
        Windows::Foundation::IAsyncAction SetSettings(Windows::Data::Json::JsonObject value);
        Windows::Foundation::IAsyncOperation <Windows::Data::Json::JsonArray> GetHistory();
        Windows::Foundation::IAsyncAction SetHistory(Windows::Data::Json::JsonObject value);
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct FileCheckTool : FileCheckToolT<FileCheckTool, implementation::FileCheckTool>
    {
    };
}
