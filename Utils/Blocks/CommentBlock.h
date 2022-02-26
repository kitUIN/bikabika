#pragma once
#include "CommentBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct CommentBlock : CommentBlockT<CommentBlock>
    {
        CommentBlock() = default;

        CommentBlock(winrt::Windows::Data::Json::JsonObject const& json);
        hstring Content();
        void Content(hstring const& value);
        winrt::Windows::UI::Xaml::Visibility Top();
        void Top(winrt::Windows::UI::Xaml::Visibility const& value);
        bool IsTop();
        void IsTop(bool const& value);
        winrt::Windows::UI::Xaml::Visibility Hide();
        void Hide(winrt::Windows::UI::Xaml::Visibility const& value);
        hstring CreatedAt();
        void CreatedAt(hstring const& value);
        int32_t LikesCount();
        void LikesCount(int32_t value);
        int32_t CommentsCount();
        void CommentsCount(int32_t value);
        bikabika::CreaterBlock Creater();
        void Creater(bikabika::CreaterBlock value);
        Windows::UI::Xaml::Visibility IsLiked();
        void IsLiked(Windows::UI::Xaml::Visibility value);
        winrt::Windows::Data::Json::JsonObject GetJsonObject();
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring m_content;
        Windows::UI::Xaml::Visibility m_isLiked = Windows::UI::Xaml::Visibility::Collapsed;
        Windows::UI::Xaml::Visibility m_top = Windows::UI::Xaml::Visibility::Collapsed;
        Windows::UI::Xaml::Visibility m_hide= Windows::UI::Xaml::Visibility::Visible;
        hstring m_createdAt;
        int32_t m_commentsCount;
        int32_t m_likesCount;
        bool m_isTop;
        bikabika::CreaterBlock m_creater{nullptr};
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct CommentBlock : CommentBlockT<CommentBlock, implementation::CommentBlock>
    {
    };
}
