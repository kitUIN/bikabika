#pragma once
#include "FileCheckTool.g.h"


namespace winrt::bikabika::implementation
{
    struct FileCheckTool : FileCheckToolT<FileCheckTool>
    {
        FileCheckTool() = default;
        
        Windows::Foundation::IAsyncOperation<bool> CheckFile(hstring const& fileName);
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct FileCheckTool : FileCheckToolT<FileCheckTool, implementation::FileCheckTool>
    {
    };
}
