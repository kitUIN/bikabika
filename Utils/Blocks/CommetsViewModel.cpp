#include "pch.h"
#include "CommetsViewModel.h"
#include "CommetsViewModel.g.cpp"

namespace winrt::bikabika::implementation
{
    CommetsViewModel::CommetsViewModel()
    {
        
     }
    winrt::Windows::Foundation::Collections::IObservableVector<bikabika::CommentBlock> CommetsViewModel::CommentBlock()
    {
        return m_comments;
    }
}
