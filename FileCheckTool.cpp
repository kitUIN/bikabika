#include "pch.h"
#include "FileCheckTool.h"
#include "FileCheckTool.g.cpp"

using namespace winrt;
using namespace Windows::Data::Json;
namespace winrt::bikabika::implementation
{
	// 检测Account文件
	Windows::Foundation::IAsyncOperation<bool> FileCheckTool::CheckFileAccount()
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
					if (file.Name() == L"account.json")
					{
						
						f = true;
						break;
					}
				}
				break;
			}
			
		}
		if (!f)
		{
			Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
			OutputDebugStringW(L"\n[Error] account file is not exist -> Get New\n\n");
			Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			auto accountFile{ co_await folder.CreateFileAsync(L"account.json", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			Windows::Data::Json::JsonObject account;
			account.SetNamedValue(L"email", JsonValue::CreateStringValue(L""));
			account.SetNamedValue(L"password", JsonValue::CreateStringValue(L""));
			account.SetNamedValue(L"isChecked", JsonValue::CreateBooleanValue(false));
			account.SetNamedValue(L"token", JsonValue::CreateStringValue(L""));
			hstring data = account.Stringify();
			co_await Windows::Storage::FileIO::WriteTextAsync(accountFile, data);
		}
		

		co_return f;


	}
	// 检测User文件
	Windows::Foundation::IAsyncOperation<bool> FileCheckTool::CheckFileUser()
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
					if (file.Name() == L"user.json")
					{

						f = true;
						break;
					}
				}
				break;
			}

		}
		if (!f)
		{
			Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
			OutputDebugStringW(L"\n[Error] user file is not exist -> Get New\n\n");
			Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			auto accountFile{ co_await folder.CreateFileAsync(L"user.json", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			// user文件
			Windows::Data::Json::JsonObject user, avatar;
			avatar.SetNamedValue(L"fileServer", JsonValue::CreateStringValue(L""));
			avatar.SetNamedValue(L"path", JsonValue::CreateStringValue(L""));
			avatar.SetNamedValue(L"originalName", JsonValue::CreateStringValue(L""));
			Windows::Data::Json::JsonArray jsonArry;
			user.SetNamedValue(L"_id", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"birthday", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"email", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"gender", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"name", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"slogan", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"title", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"verified", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"exp", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"level", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"characters", jsonArry);
			user.SetNamedValue(L"created_at", JsonValue::CreateStringValue(L""));
			user.SetNamedValue(L"avatar", avatar);
			user.SetNamedValue(L"isPunched", JsonValue::CreateBooleanValue(false));
			user.SetNamedValue(L"character", JsonValue::CreateStringValue(L""));
			

			hstring data = user.Stringify();
			co_await Windows::Storage::FileIO::WriteTextAsync(accountFile, data);
		}


		co_return f;


	}
}
