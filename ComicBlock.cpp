#include "pch.h"
#include "ComicBlock.h"
#include "ComicBlock.g.cpp"


namespace winrt::bikabika::implementation
{
   

	ComicBlock::ComicBlock(winrt::Windows::Data::Json::JsonObject const& json)
	{
		extern winrt::hstring serverStream;
		hstring path = serverStream + L"/static/" + json.GetNamedObject(L"thumb").GetNamedString(L"path");

		m_id = json.GetNamedString(L"_id");
		m_title = json.GetNamedString(L"title");
		m_author = json.GetNamedString(L"author");
		m_totalLikes = json.GetNamedNumber(L"totalLikes");
		m_totalViews = json.GetNamedNumber(L"totalViews");
		m_pageCount = json.GetNamedNumber(L"pagesCount");
		m_epsCount = json.GetNamedNumber(L"epsCount");
		m_finished = json.GetNamedBoolean(L"finished");
		for (auto x : json.GetNamedArray(L"categories"))
		{
			m_categories.Append(winrt::make<TagBlock>(x.GetString()));
			m_category = m_category + x.GetString() + L"  ";
		}
		 
		m_thumb = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ path} };
		m_likesCount = json.GetNamedNumber(L"likesCount");
	}
	hstring ComicBlock::ID()
	{
		return m_id;
	}
	void ComicBlock::ID(hstring const& value)
	{
		if (value != m_id) m_id = value;
	}
	hstring ComicBlock::Title()
	{
		return m_title;
	}
	void ComicBlock::Title(hstring const& value)
	{
		if (value != m_title) m_title = value;
	}
	hstring ComicBlock::Author()
	{
		return m_author;
	}
	void ComicBlock::Author(hstring const& value)
	{
		if (value != m_author) m_author = value;
	}
	int32_t ComicBlock::TotalViews()
	{
		return m_totalViews;
	}
	void ComicBlock::TotalViews(int32_t value)
	{
		if (value != m_totalViews) m_totalViews = value;
	}
	int32_t ComicBlock::TotalLikes()
	{
		return m_totalLikes;
	}
	void ComicBlock::TotalLikes(int32_t value)
	{
		if (value != m_totalLikes) m_totalLikes = value;
	}
	int32_t ComicBlock::PageCount()
	{
		return m_pageCount;
	}
	void ComicBlock::PageCount(int32_t value)
	{
		if (value != m_pageCount) m_pageCount = value;
	}
	int32_t ComicBlock::EpsCount()
	{
		return m_epsCount;
	}
	void ComicBlock::EpsCount(int32_t value)
	{
		if (value != m_epsCount) m_epsCount = value;
	}
	bool ComicBlock::Finished()
	{
		return m_finished;
	}
	void ComicBlock::Finished(bool value)
	{
		if (value != m_finished) m_finished = value;
	}
	winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> ComicBlock::Categories()
	{
		return m_categories;
	}
	void ComicBlock::Categories(winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> const& value)
	{
		if (value != m_categories) m_categories = value;
	}
	hstring ComicBlock::Category()
	{
		return m_category;
	}
	void ComicBlock::Category(hstring const& value)
	{
		if (value != m_category) m_category = value;
	}
	winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage ComicBlock::Thumb()
	{
		return m_thumb;
	}
	void ComicBlock::Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
	{
		if (value != m_thumb) m_thumb = value;
	}
	int32_t ComicBlock::LikesCount()
	{
		return m_likesCount;
	}
	void ComicBlock::LikesCount(int32_t value)
	{
		if (value != m_likesCount) m_likesCount = value;
	}
	winrt::event_token ComicBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}
	void ComicBlock::PropertyChanged(winrt::event_token const& token) noexcept
	{
		m_propertyChanged.remove(token);
	}
	
}
