#include "pch.h"
#include "LoginTextBlock.h"
#include "LoginTextBlock.g.cpp"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.

namespace winrt::bikabika::implementation
{
    LoginTextBlock::LoginTextBlock(hstring const& email, hstring const& password)
    {
        
    }
    hstring LoginTextBlock::Email()
    {
        return m_email;
    }
    void LoginTextBlock::Email(hstring const& value)
    {
        if (m_email != value)
        {
            m_email = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"email" });
        }
    }
    hstring LoginTextBlock::Password()
    {
        return m_password;
    }
    void LoginTextBlock::Password(hstring const& value)
    {
        if (m_password != value)
        {
            m_password = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"password" });
        }
    }
    winrt::event_token LoginTextBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void LoginTextBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
