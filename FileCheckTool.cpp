#include "pch.h"
#include "FileCheckTool.h"
#include "FileCheckTool.g.cpp"

namespace winrt::bikabika::implementation
{
	// 检测数据文件
	Windows::Foundation::IAsyncOperation<bool> FileCheckTool::CheckFile(hstring const& fileName)
	{

		bool f = false;

		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		Windows::Storage::StorageFolder folderDB{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };

		for (auto const& folder : co_await localFolder.GetFoldersAsync())
		{
			if (folder.Name() == L"bikabikadb")
			{
				for (auto const& file : co_await folderDB.GetFilesAsync())
				{
					if (file.Name() == fileName)
					{
						f = true;
						break;
					}
				}
				break;
			}
			
		}
		co_return f;


	}
}
