﻿#include "pch.h"
#include "BlankPage.h"
#if __has_include("BlankPage.g.cpp")
#include "BlankPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    BlankPage::BlankPage()
    {
        InitializeComponent();
    }

    int32_t BlankPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void BlankPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }


}
