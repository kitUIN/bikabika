#pragma once
#include "ClassBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct ClassBlock : ClassBlockT<ClassBlock>
    {
        ClassBlock() = default;

        ClassBlock(hstring const& className, hstring const& classPic, hstring const& classType);
        hstring ClassName();
        hstring ClassPic();
        hstring ClassType();
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);
    private:
        hstring m_className;
        hstring m_classPic;
        hstring m_classType;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ClassBlock : ClassBlockT<ClassBlock, implementation::ClassBlock>
    {
    };
}
