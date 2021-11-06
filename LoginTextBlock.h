#pragma once
#include "LoginTextBlock.g.h"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.

namespace winrt::bikabika::implementation
{
    struct LoginTextBlock : LoginTextBlockT<LoginTextBlock>
    {
        LoginTextBlock() = delete;

        LoginTextBlock(hstring const& email, hstring const& password);
        hstring Email();
        void Email(hstring const& value);
        hstring Password();
        void Password(hstring const& value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::hstring m_email;
        winrt::hstring m_password;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct LoginTextBlock : LoginTextBlockT<LoginTextBlock, implementation::LoginTextBlock>
    {
    };
}
