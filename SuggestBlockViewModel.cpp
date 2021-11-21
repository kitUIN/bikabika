#include "pch.h"
#include "SuggestBlockViewModel.h"
#include "SuggestBlockViewModel.g.cpp"



namespace winrt::bikabika::implementation
{
    SuggestBlockViewModel::SuggestBlockViewModel()
    {
        m_suggestBlocks = winrt::single_threaded_observable_vector<bikabika::SuggestBlock>();
		m_suggestBlocks.Append(winrt::make<SuggestBlock>(L"关键字",L"说明",L"[类型]", winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource(winrt::Windows::Foundation::Uri(L"ms-appx:///tag.svg"))));

        //auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };

    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::SuggestBlock> SuggestBlockViewModel::SuggestBlocks()
    {
        return m_suggestBlocks;
    }
}
