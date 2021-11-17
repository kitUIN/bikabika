#include "pch.h"
#include "ClassBlockViewModel.h"
#include "ClassBlockViewModel.g.cpp"


namespace winrt::bikabika::implementation
{
    ClassBlockViewModel::ClassBlockViewModel()
    {
        std::vector<Windows::Foundation::IInspectable> classBlockss;
        classBlockss.push_back(winrt::make<ClassBlock>(L"", L"userlogo.png"));
        m_classBlocks = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>(std::move(classBlockss));
    }
    ClassBlockViewModel::ClassBlockViewModel(Windows::Data::Json::JsonArray jsonArray)
    {
        std::vector<Windows::Foundation::IInspectable> classBlockss;
        classBlockss.push_back(winrt::make<ClassBlock>(L"666", L"userlogo.png"));
        m_classBlocks = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>(std::move(classBlockss));
    }
    winrt::bikabika::ClassBlock ClassBlockViewModel::DefaultClassBlock()
    {
        m_defaultClassBlock = winrt::make<ClassBlock>(L"", L"userlogo.png");
        return m_defaultClassBlock;
    }
    Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> ClassBlockViewModel::ClassBlocks() 
    { 
        return m_classBlocks; 
    }

}
