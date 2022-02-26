#pragma once
#include "CommetsViewModel.g.h"
#include "CommentBlock.h"
namespace winrt::bikabika::implementation
{
    struct CommetsViewModel : CommetsViewModelT<CommetsViewModel>
    {
        CommetsViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::CommentBlock> CommentBlock();
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::CommentBlock> m_comments = winrt::single_threaded_observable_vector<bikabika::CommentBlock>();

    };
}
namespace winrt::bikabika::factory_implementation
{
    struct CommetsViewModel : CommetsViewModelT<CommetsViewModel, implementation::CommetsViewModel>
    {
    };
}
