#include "pch.h"
#include "ComicBlock.h"
#include "ComicBlock.g.cpp"


namespace winrt::bikabika::implementation
{
   

	ComicBlock::ComicBlock(winrt::Windows::Data::Json::JsonObject const& json)
	{
		m_json = json;
		extern winrt::hstring serverStream;
		hstring path = serverStream + L"/static/" + json.GetNamedObject(L"thumb").GetNamedString(L"path");

		m_id = json.GetNamedString(L"_id");
		m_title = json.GetNamedString(L"title");
		if (auto x = json.TryLookup(L"author")) m_author = x.GetString();
		if (auto y = json.TryLookup(L"totalLikes"))
		{
			if (y.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
				m_totalLikes = y.GetNumber();
			else if(y.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
				m_totalLikes = atoi(to_string(y.GetString()).c_str());
			
		}
		if (auto z = json.TryLookup(L"totalViews")) 
		{
			if (z.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
				m_totalViews = z.GetNumber();
			else if (z.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
				m_totalLikes = atoi(to_string(z.GetString()).c_str());
		}
		if (auto j = json.TryLookup(L"pagesCount")) m_pageCount = j.GetNumber();
		if (auto k = json.TryLookup(L"epsCount")) m_epsCount = k.GetNumber();
		if (json.GetNamedBoolean(L"finished"))
		{
			m_finished = winrt::Windows::UI::Xaml::Visibility::Visible;
		}
		else
		{
			m_finished = winrt::Windows::UI::Xaml::Visibility::Collapsed;
		}
		for (auto x : json.GetNamedArray(L"categories"))
		{
			m_categories.Append(winrt::make<TagBlock>(x.GetString()));
			m_category = m_category + x.GetString() + L"  ";
		}
		 
		m_thumb = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ path} };
		if (auto l = json.TryLookup(L"likesCount"))
		{
			if (l.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
				m_likesCount = l.GetNumber();
			else if (l.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
				m_likesCount = atoi(to_string(l.GetString()).c_str());
		}
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
	Windows::UI::Xaml::Visibility ComicBlock::Finished()
	{
		return m_finished;
	}
	void ComicBlock::Finished(Windows::UI::Xaml::Visibility value)
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

	winrt::Windows::Data::Json::JsonObject ComicBlock::GetJsonObject()
	{
		return m_json;
	}
	
}
