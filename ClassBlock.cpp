#include "pch.h"
#include "ClassBlock.h"
#include "ClassBlock.g.cpp"

namespace winrt::bikabika::implementation
{
	
	ClassBlock::ClassBlock(hstring const& className, hstring const& classPic, hstring const& classType)
	{
		m_className = className;
		m_classPic = classPic;
		m_classType = classType;
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ClassName" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"ClassPic" });
	}

	hstring ClassBlock::ClassName()
	{
		return m_className;
	}
	hstring ClassBlock::ClassPic()
	{
		return m_classPic;
	}
	hstring ClassBlock::ClassType()
	{
		return m_classType;
	}
	winrt::event_token ClassBlock::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}
	void ClassBlock::PropertyChanged(winrt::event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
}
