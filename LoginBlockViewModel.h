#pragma once
#include "LoginBlockViewModel.g.h"
#include "LoginTextBlock.h"
// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.

namespace winrt::bikabika::implementation
{
    struct LoginBlockViewModel : LoginBlockViewModelT<LoginBlockViewModel>
    {
        LoginBlockViewModel();

        bikabika::LoginTextBlock LoginTextBlock();
    private:
        bikabika::LoginTextBlock m_loginTextBlock{ nullptr };
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct LoginBlockViewModel : LoginBlockViewModelT<LoginBlockViewModel, implementation::LoginBlockViewModel>
    {
    };
}
