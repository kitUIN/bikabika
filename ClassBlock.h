#pragma once
#include "ClassBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct ClassBlock : ClassBlockT<ClassBlock>
    {
        ClassBlock() = default;

        ClassBlock(hstring const& className, hstring const& classPic);
        hstring ClassName();
        hstring ClassPic();
    private:
        hstring m_className;
        hstring m_classPic;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ClassBlock : ClassBlockT<ClassBlock, implementation::ClassBlock>
    {
    };
}
