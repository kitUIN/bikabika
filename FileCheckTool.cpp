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
	// 检测Keywords文件
	Windows::Foundation::IAsyncOperation<bool> FileCheckTool::CheckFileKeywords()
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
					if (file.Name() == L"keywords.json")
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
			OutputDebugStringW(L"\n[Error] keywords file is not exist -> Get New\n\n");
			Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			auto keywordsFile{ co_await folder.CreateFileAsync(L"keywords.json", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			// user文件
			Windows::Data::Json::JsonObject keywords;
			Windows::Data::Json::JsonArray jsonArray;
			jsonArray.Append(JsonValue::CreateStringValue(L"C96"));
			jsonArray.Append(JsonValue::CreateStringValue(L"嗶咔團長推薦"));
			jsonArray.Append(JsonValue::CreateStringValue(L"肥宅"));
			jsonArray.Append(JsonValue::CreateStringValue(L"老師"));
			jsonArray.Append(JsonValue::CreateStringValue(L"校園"));
			jsonArray.Append(JsonValue::CreateStringValue(L"校服"));
			jsonArray.Append(JsonValue::CreateStringValue(L"廁所"));
			jsonArray.Append(JsonValue::CreateStringValue(L"水平線"));
			jsonArray.Append(JsonValue::CreateStringValue(L"冰菓"));
			jsonArray.Append(JsonValue::CreateStringValue(L"一拳超人"));
			jsonArray.Append(JsonValue::CreateStringValue(L"遊戲王"));
			jsonArray.Append(JsonValue::CreateStringValue(L"小梅けいと"));
			jsonArray.Append(JsonValue::CreateStringValue(L"40010"));
			jsonArray.Append(JsonValue::CreateStringValue(L"ホムンクルス"));
			keywords.SetNamedValue(L"keywords", jsonArray);
			hstring data = keywords.Stringify();
			co_await Windows::Storage::FileIO::WriteTextAsync(keywordsFile, data);
		}
		co_return f;
	}
	Windows::Foundation::IAsyncOperation<bool> FileCheckTool::CheckFileSettings()
	{
		return Windows::Foundation::IAsyncOperation<bool>();
	}
	Windows::Foundation::IAsyncOperation<bool> FileCheckTool::CheckFileSearchHistory()
	{
		return Windows::Foundation::IAsyncOperation<bool>();
	}
	Windows::Foundation::IAsyncOperation<Windows::Data::Json::JsonObject> FileCheckTool::GetAccount()
	{
		bool f{ co_await CheckFileAccount() };
		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		Windows::Storage::StorageFolder folderDB{ co_await localFolder.GetFolderAsync(L"bikabikadb") };
		auto accountFile{ co_await folderDB.GetFileAsync(L"account.json") };
		co_return Windows::Data::Json::JsonObject::Parse(co_await Windows::Storage::FileIO::ReadTextAsync(accountFile));

	}
	Windows::Foundation::IAsyncAction FileCheckTool::SetAccount(Windows::Data::Json::JsonObject value)
	{
		return Windows::Foundation::IAsyncAction();
	}
	Windows::Foundation::IAsyncOperation<Windows::Data::Json::JsonObject> FileCheckTool::GetUser()
	{
		return Windows::Foundation::IAsyncOperation<Windows::Data::Json::JsonObject>();
	}
	Windows::Foundation::IAsyncAction FileCheckTool::SetUser(Windows::Data::Json::JsonObject value)
	{
		return Windows::Foundation::IAsyncAction();
	}
	Windows::Foundation::IAsyncOperation<Windows::Data::Json::JsonObject> FileCheckTool::GetKeywords()
	{
		bool f{ co_await CheckFileKeywords() };
		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		Windows::Storage::StorageFolder folderDB{ co_await localFolder.GetFolderAsync(L"bikabikadb") };
		auto keywordsFile{ co_await folderDB.GetFileAsync(L"keywords.json") };
		co_return Windows::Data::Json::JsonObject::Parse(co_await Windows::Storage::FileIO::ReadTextAsync(keywordsFile));
	}
	Windows::Foundation::IAsyncAction FileCheckTool::SetKeywords(Windows::Data::Json::JsonObject value)
	{
		bool f{ co_await CheckFileKeywords() };
		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
		auto keywordsFile{ co_await folder.CreateFileAsync(L"keywords.json", Windows::Storage::CreationCollisionOption::OpenIfExists) };
		hstring data = value.Stringify();
		co_await Windows::Storage::FileIO::WriteTextAsync(keywordsFile, data);
	}
	Windows::Foundation::IAsyncOperation<Windows::Data::Json::JsonObject> FileCheckTool::GetSettings()
	{
		return Windows::Foundation::IAsyncOperation<Windows::Data::Json::JsonObject>();
	}
	Windows::Foundation::IAsyncAction FileCheckTool::SetSettings(Windows::Data::Json::JsonObject value)
	{
		return Windows::Foundation::IAsyncAction();
	}
}
