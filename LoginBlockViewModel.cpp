#include "pch.h"
#include "LoginBlockViewModel.h"
#include "LoginBlockViewModel.g.cpp"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.

namespace winrt::bikabika::implementation
{
    LoginBlockViewModel::LoginBlockViewModel()
    {
        m_loginTextBlock = winrt::make<bikabika::implementation::LoginTextBlock>(L"eeeeemail",L"pppppassword");

    }
    bikabika::LoginTextBlock LoginBlockViewModel::LoginTextBlock()
    {
        return m_loginTextBlock;
    }
}
