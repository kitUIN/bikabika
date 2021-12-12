#include "pch.h"
#include "User.h"
#include "User.g.cpp"


namespace winrt::bikabika::implementation
{
	User::User(hstring const& name, hstring const& level):m_name { name },m_level{ level }
	{	
	}
	hstring User::Name()
	{
		return m_name;
	}
	void User::Name(hstring const& value)
	{
		if (m_name != value)
		{
			m_name = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
		}
			
	}
	hstring User::Level()
	{
		return m_level;
	}
	void User::Level(hstring const& value)
	{
		if (m_level != value)
		{
			m_level = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Level" });
		}
	}
	winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage User::Img()
	{
		
		return m_img;
	}
	void User::Img(Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
	{
		if (m_img != value)	
		{
			m_img = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Img" });
		}
	}
	hstring User::ImageSource()
	{
		return m_imageSource;
	}
	void User::ImageSource(hstring const& value)
	{
		if (m_imageSource != value)
		{
			m_imageSource = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ImageSource" });
		}
	}
	hstring User::Slogan()
	{
		return m_slogan;
	}
	void User::Slogan(hstring const& value)
	{
		if (m_slogan != value)
		{
			m_slogan = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Slogan" });
		}
	}
	int32_t User::Exp()
	{
		return m_exp;
	}
	void User::Exp(int32_t const& value)
	{
		if (m_exp != value)
		{
			m_exp = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Exp" });
		}
	}
	hstring User::LevelExp()
	{
		return m_levelExp;
	}
	void User::LevelExp(hstring const& value)
	{
		if (m_levelExp != value)
		{
			m_levelExp = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"LevelExp" });
		}
	}
	hstring User::Title()
	{
		return m_title;
	}
	void User::Title(hstring const& value)
	{
		if (m_title != value)
		{
			m_title = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Title" });
		}
	}
	winrt::event_token User::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}
	void User::PropertyChanged(winrt::event_token const& token) noexcept
	{
		m_propertyChanged.remove(token);
	}
}
