#include "pch.h"
#include "ClassBlockViewModel.h"
#include "ClassBlockViewModel.g.cpp"


namespace winrt::bikabika::implementation
{

	ClassBlockViewModel::ClassBlockViewModel()
	{
		m_classBlocks = winrt::single_threaded_observable_vector<bikabika::ClassBlock>();
		//m_classBlocks.Append(winrt::make<bikabika::implementation::ClassBlock>(L"???",L"userlogo.png"));
		/*for (auto e : jsonArray)
		{
			Windows::Data::Json::JsonObject categories = e.GetObject();
			hstring title = categories.GetNamedString(L"title");
			Windows::Data::Json::JsonObject thumb = categories.GetNamedObject(L"thumb");
			hstring path = thumb.GetNamedString(L"path");
			hstring fileServer = thumb.GetNamedString(L"fileServer");
			auto block = winrt::make<bikabika::implementation::ClassBlock>(title, fileServer + L"/static/" + path);
			m_classBlocks.Append(block);
		}*/
	}
	winrt::bikabika::ClassBlock ClassBlockViewModel::DefaultClassBlock()
	{
		m_defaultClassBlock = winrt::make<ClassBlock>(L"", L"userlogo.png");
		return m_defaultClassBlock;
	}
	Windows::Foundation::Collections::IObservableVector<bikabika::ClassBlock> ClassBlockViewModel::ClassBlocks()
	{ 
		return m_classBlocks; 
	}


}
