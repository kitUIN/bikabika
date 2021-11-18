#include "pch.h"
#include "ClassBlockViewModel.h"
#include "ClassBlockViewModel.g.cpp"


namespace winrt::bikabika::implementation
{

	ClassBlockViewModel::ClassBlockViewModel()
	{
		m_classBlocks = winrt::single_threaded_observable_vector<bikabika::ClassBlock>();
		auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/support"), L"cat_support.jpg"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/leaderboard"), L"cat_leaderboard.jpg"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/game"), L"cat_game.jpg"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/help"), L"chat_bg_image.png"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/smalltool"), L"cat_love_pica.jpg"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/forum"), L"cat_forum.jpg"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/latest"), L"cat_latest.jpg"));
		m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(resourceLoader.GetString(L"categories/random"), L"cat_random.jpg"));
	}
	winrt::bikabika::ClassBlock ClassBlockViewModel::DefaultClassBlock()
	{
		m_defaultClassBlock = winrt::make<ClassBlock>(L"", L"userlogo.png");
		return m_defaultClassBlock;
	}
	Windows::Foundation::Collections::IObservableVector<bikabika::ClassBlock> ClassBlockViewModel::ClassBlocks()
	{ 
		return m_classBlocks; 
	}


}
