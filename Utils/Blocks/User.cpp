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
	hstring User::CreatedAt()
	{
		return m_createAt;
	}
	void User::CreatedAt(hstring const& value)
	{
		bikabika::BikaDate datetime{ value };
		m_createAt = datetime.GetDateTime();
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"CreatedAt" });
	}
	hstring User::Birthday()
	{
		return m_birthday;
	}
	void User::Birthday(hstring const& value)
	{
		bikabika::BikaDate datetime{ value };
		m_birthday = datetime.GetDateTime();
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Birthday" });
	}
	hstring User::Email()
	{
		return m_email;
	}
	void User::Email(hstring const& value)
	{
		if (m_email != value)
		{
			m_email = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Email" });
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
			m_levelString = L"Lv."+value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"LevelString" });
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Level" });
		}
	}
	bool User::IsPunched()
	{
		return m_isPunched;
	}
	void User::IsPunched(bool const& value)
	{
		if (value)
		{
			m_isPunchedString = resourceLoader.GetString(L"PunchIned");
		}
		else
		{
			m_isPunchedString =resourceLoader.GetString(L"UnPunchIned");
		}
		m_isPunched = value;
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"IsPunched" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"IsPunchedString" });
	}
	bool User::Verified()
	{
		return m_verified;
	}
	void User::Verified(bool const& value)
	{
		if (value)
		{
			m_verifiedString = resourceLoader.GetString(L"Verified");
		}
		else 
		{
			m_verifiedString = resourceLoader.GetString(L"UnVerified");
		}
		m_verified = value;
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Verified" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"VerifiedString" });
	}
	hstring User::IsPunchedString()
	{
		return m_isPunchedString;
	}
	void User::IsPunchedString(hstring const& value)
	{
		if (value == L"true")
		{
			m_isPunchedString = resourceLoader.GetString(L"PunchIned");
		}
		else
		{
			m_isPunchedString =resourceLoader.GetString(L"UnPunchIned");
		}
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"IsPunchedString" });
	}
	hstring User::VerifiedString()
	{
		return m_verifiedString;
	}
	void User::VerifiedString(hstring const& value)
	{
		if (value==L"true")
		{
			m_verifiedString = resourceLoader.GetString(L"Verified");
		}
		else 
		{
			m_verifiedString = resourceLoader.GetString(L"UnVerified");
		}
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"VerifiedString" });
	}
	hstring User::ID()
	{
		return m_id;
	}
	void User::ID(hstring const& value)
	{
		if (m_id != value)
		{
			m_id = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ID" });
		}
	}
	hstring User::Gender()
	{
		return m_gender;
	}
	void User::Gender(hstring const& value)
	{
		if (m_gender != value)
		{
			m_gender = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Gender" });
		}
	}
	hstring User::LevelString()
	{
		return m_levelString;
	}
	void User::LevelString(hstring const& value)
	{
		if (m_levelString != value)
		{
			m_levelString = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"LevelString" });
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
	int32_t User::Percent()
	{
		return m_percent;
	}
	void User::Percent(int32_t const& value)
	{
		if (m_percent != value)
		{
			m_percent = value;
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Percent" });
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
	void User::Clear()
	{
		m_title = L"";
		m_gender = L"";
		m_id = L"";
		m_verified = false;
		m_verifiedString = L"";
		m_isPunched = false;
		m_isPunchedString = L"";
		m_createAt = L"";
		m_birthday = L"";
		m_slogan = L"";
		m_levelExp = L"(? / ?)";
		m_exp = 0;
		m_percent = 100;
		m_name = L"Gentleman";
		m_email = L"";
		m_levelString = L"Lv.0";
		m_level = L"";
		winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_img{ Windows::Foundation::Uri{ L"ms-appx:///gray.png" } };
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ID" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"CreatedAt" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Birthday" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Email" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"LevelString" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"IsPunchedString" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"VerifiedString" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Gender" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Img" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Slogan" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"LevelExp" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Title" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Percent" });
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
