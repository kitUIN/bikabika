#include "pch.h"
#include "ClassBlockViewModel.h"
#include "ClassBlockViewModel.g.cpp"


namespace winrt::bikabika::implementation
{

	ClassBlockViewModel::ClassBlockViewModel()
	{
		m_classBlocks = winrt::single_threaded_observable_vector<bikabika::ClassBlock>();
		auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/support"), L"cat_support.jpg",L"1"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/leaderboard"), L"cat_leaderboard.jpg", L"1"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/game"), L"cat_game.jpg", L"1"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/help"), L"chat_bg_image.png", L"1"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/smalltool"), L"cat_love_pica.jpg", L"1"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/forum"), L"cat_forum.jpg", L"1"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/latest"), L"cat_latest.jpg", L"1"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/random"), L"cat_random.jpg", L"1"));
	}
	winrt::bikabika::ClassBlock ClassBlockViewModel::DefaultClassBlock()
	{
		m_defaultClassBlock = winrt::make<ClassBlock>(L"", L"userlogo.png", L"1");
		return m_defaultClassBlock;
	}
	Windows::Foundation::Collections::IObservableVector<bikabika::ClassBlock> ClassBlockViewModel::ClassBlocks()
	{ 
		return m_classBlocks; 
	}


}
