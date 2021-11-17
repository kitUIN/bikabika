#pragma once

#include "HomePage.g.h"
#include "Login.h"
namespace winrt::bikabika::implementation
{
	struct HomePage : HomePageT<HomePage>
	{
		HomePage();

		Windows::Foundation::IAsyncAction ExampleCoroutineAsync();
		void SetText(hstring str);
		void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
	};
}

namespace winrt::bikabika::factory_implementation
{
	struct HomePage : HomePageT<HomePage, implementation::HomePage>
	{
	};
}
