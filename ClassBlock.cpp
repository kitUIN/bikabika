#include "pch.h"
#include "ClassBlock.h"
#include "ClassBlock.g.cpp"

namespace winrt::bikabika::implementation
{
    ClassBlock::ClassBlock(hstring const& className, hstring const& classPic) 
    {
        m_className = className;
        m_classPic = classPic;
    }
    
    
    hstring ClassBlock::ClassName()
    {
        return m_className;
    }
    hstring ClassBlock::ClassPic()
    {
        return m_classPic;
    }
}
