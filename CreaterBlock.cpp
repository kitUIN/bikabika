#include "pch.h"
#include "CreaterBlock.h"
#include "CreaterBlock.g.cpp"

namespace winrt::bikabika::implementation
{

    CreaterBlock::CreaterBlock(winrt::Windows::Data::Json::JsonObject const& json)
    {
        m_id = json.GetNamedString(L"_id");
        m_gender = json.GetNamedString(L"gender");
        m_name = json.GetNamedString(L"name");
        m_exp = json.GetNamedNumber(L"exp");
        m_level = json.GetNamedNumber(L"level");
        m_role = json.GetNamedString(L"role");
        extern winrt::hstring serverStream;
        if (auto s = json.TryLookup(L"avatar"))
        {
            hstring path = serverStream + L"/static/" + s.GetObject().GetNamedString(L"path");
            m_thumb = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ path} };
        }
        for (auto x : json.GetNamedArray(L"characters"))
        {
            m_characters.Append(winrt::make<TagBlock>(x.GetString()));
            m_charactersString = m_charactersString + x.GetString() + L"  ";
        }
        if (auto s = json.TryLookup(L"verified")) m_verified = s.GetBoolean();
        if (auto x = json.TryLookup(L"character")) m_character = x.GetString();
        if (auto y = json.TryLookup(L"title")) m_title = y.GetString();
        if (auto z = json.TryLookup(L"slogan")) m_slogan = z.GetString();
    }
    hstring CreaterBlock::ID()
    {
        return m_id;
    }
    void CreaterBlock::ID(hstring const& value)
    {
        if (m_id != value) {
            m_id = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring CreaterBlock::Gender()
    {
        return m_gender;
    }
    void CreaterBlock::Gender(hstring const& value)
    {
        if (m_gender != value) {
            m_gender = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring CreaterBlock::Name()
    {
        return m_name;
    }
    void CreaterBlock::Name(hstring const& value)
    {
        if (m_name != value) {
            m_name = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t CreaterBlock::Exp()
    {
        return m_exp;
    }
    void CreaterBlock::Exp(int32_t value)
    {
        if (m_exp != value) {
            m_exp = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t CreaterBlock::Level()
    {
        return m_level;
    }
    void CreaterBlock::Level(int32_t value)
    {
        if (m_level != value) {
            m_level = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring CreaterBlock::Role()
    {
        return m_role;
    }
    void CreaterBlock::Role(hstring const& value)
    {
        if (m_role != value) {
            m_role = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring CreaterBlock::CharactersString()
    {
        return m_charactersString;
    }
    void CreaterBlock::CharactersString(hstring const& value)
    {
        if (m_charactersString != value) {
            m_charactersString = value;
            
        }
    }
    hstring CreaterBlock::Title()
    {
        return m_title;
    }
    void CreaterBlock::Title(hstring const& value)
    {
        if (m_title != value) {
            m_title = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring CreaterBlock::Slogan()
    {
        return m_slogan;
    }
    void CreaterBlock::Slogan(hstring const& value)
    {
        if (m_slogan != value) {
            m_slogan = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring CreaterBlock::Character()
    {
        return m_character;
    }
    void CreaterBlock::Character(hstring const& value)
    {
        if (m_character != value) {
            m_character = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage CreaterBlock::Thumb()
    {
        return m_thumb;
    }
    void CreaterBlock::Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
    {
        if (m_thumb != value) {
            m_thumb = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> CreaterBlock::Characters()
    {
        return m_characters;
    }
   
    void CreaterBlock::Characters(winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> const& value)
    {
        if (m_characters != value) {
            m_characters = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    
    bool CreaterBlock::Verified()
    {
        return m_verified;
    }
    void CreaterBlock::Verified(bool value)
    {
        if (m_verified != value) {
            m_verified = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    
    winrt::event_token CreaterBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void CreaterBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
