#pragma once
#include "CommentView.g.h"

namespace winrt::bikabika::implementation
{
    struct CommentView : CommentViewT<CommentView>
    {
        CommentView() = default;

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CommentBlock> Comments();
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CommentBlock> m_comment = winrt::single_threaded_observable_vector<winrt::BikaClient::Blocks::CommentBlock>();
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct CommentView : CommentViewT<CommentView, implementation::CommentView>
    {
    };
}
