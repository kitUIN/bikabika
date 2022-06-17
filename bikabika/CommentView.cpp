#include "pch.h"
#include "CommentView.h"
#include "CommentView.g.cpp"


namespace winrt::bikabika::implementation
{
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CommentBlock> CommentView::Comments()
    {
        return m_comment;
    }
}
