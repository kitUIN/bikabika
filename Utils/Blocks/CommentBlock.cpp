#include "pch.h"
#include "CommentBlock.h"
#include "CommentBlock.g.cpp"


namespace winrt::bikabika::implementation
{
    CommentBlock::CommentBlock(winrt::Windows::Data::Json::JsonObject const& json)
    {
        
        m_content = json.GetNamedString(L"content");
        m_commentsCount = json.GetNamedNumber(L"commentsCount");
        m_likesCount = json.GetNamedNumber(L"likesCount");
        m_createdAt = BikaDate(json.GetNamedString(L"created_at")).GetDateTime();
        if (json.GetNamedBoolean(L"hide"))
        {
            m_hide = Windows::UI::Xaml::Visibility::Collapsed;
        }
        else 
        {
            m_hide = Windows::UI::Xaml::Visibility::Visible;
        }
        if (json.GetNamedBoolean(L"isLiked"))
        {
            m_hide = Windows::UI::Xaml::Visibility::Visible;
        }
        else
        {
            m_hide = Windows::UI::Xaml::Visibility::Collapsed;
        }
        m_isTop = json.GetNamedBoolean(L"isTop");
        m_creater = CreaterBlock(json.GetNamedObject(L"_user"));

    }
    hstring CommentBlock::Content()
    {
        return m_content;
    }
    void CommentBlock::Content(hstring const& value)
    {
        if (m_content != value) {
            m_content = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::UI::Xaml::Visibility CommentBlock::Top()
    {
        return m_top;
    }
    void CommentBlock::Top(winrt::Windows::UI::Xaml::Visibility const& value)
    {
        if (m_top != value) {
            m_top = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    bool CommentBlock::IsTop()
    {
        return m_isTop;
    }
    void CommentBlock::IsTop(bool const& value)
    {
        if (m_isTop != value) {
            m_isTop = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::UI::Xaml::Visibility CommentBlock::Hide()
    {
        return m_hide;;
    }
    void CommentBlock::Hide(winrt::Windows::UI::Xaml::Visibility const& value)
    {
        if (m_hide != value) {
            m_hide = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring CommentBlock::CreatedAt()
    {
        return m_createdAt;
    }
    void CommentBlock::CreatedAt(hstring const& value)
    {
        if (m_createdAt != value) {
            m_createdAt = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t CommentBlock::LikesCount()
    {
        return m_likesCount;
    }
    void CommentBlock::LikesCount(int32_t value)
    {
        if (m_likesCount != value) {
            m_likesCount = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t CommentBlock::CommentsCount()
    {
        return m_commentsCount;
    }
    void CommentBlock::CommentsCount(int32_t value)
    {
        if (m_commentsCount != value) {
            m_commentsCount = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    bikabika::CreaterBlock CommentBlock::Creater()
    {
        return m_creater;
    }
    void CommentBlock::Creater(bikabika::CreaterBlock value)
    {
        if (m_creater != value) {
            m_creater = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::UI::Xaml::Visibility CommentBlock::IsLiked()
    {
        return m_isLiked;
    }
    void CommentBlock::IsLiked(winrt::Windows::UI::Xaml::Visibility value)
    {
        if (m_isLiked != value) {
            m_isLiked = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::Data::Json::JsonObject CommentBlock::GetJsonObject()
    {
        throw hresult_not_implemented();
    }
    winrt::event_token CommentBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void CommentBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
