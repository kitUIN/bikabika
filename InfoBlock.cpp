#include "pch.h"
#include "InfoBlock.h"
#include "InfoBlock.g.cpp"


namespace winrt::bikabika::implementation
{
    InfoBlock::InfoBlock(winrt::Windows::Data::Json::JsonObject const& json)
    {
        m_id = json.GetNamedString(L"_id");
        m_title = json.GetNamedString(L"title");
        m_creater = winrt::make<CreaterBlock>(json.GetNamedObject(L"_creator"));
        m_description = json.GetNamedString(L"description");
        extern winrt::hstring serverStream;
        hstring path = serverStream + L"/static/" + json.GetNamedObject(L"thumb").GetNamedString(L"path");
        m_thumb = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ path} };
        m_author = json.GetNamedString(L"author");
        m_chineseTeam = json.GetNamedString(L"chineseTeam");
        for (auto x : json.GetNamedArray(L"categories"))
        {
            m_categories.Append(winrt::make<TagBlock>(x.GetString()));
            m_categoriesString = m_categoriesString + x.GetString() + L"  ";
        }
        m_pagesCount = json.GetNamedNumber(L"pagesCount");
        m_epsCount = json.GetNamedNumber(L"epsCount");
        if (json.GetNamedBoolean(L"finished"))
        {
            m_finished = winrt::Windows::UI::Xaml::Visibility::Visible;
        }
        else
        {
            m_finished = winrt::Windows::UI::Xaml::Visibility::Collapsed;
        }
        m_updatedAt = json.GetNamedString(L"updated_at");
        m_createdAt = json.GetNamedString(L"created_at");
        m_allowDownload = json.GetNamedBoolean(L"allowDownload");
        m_allowComment = json.GetNamedBoolean(L"allowComment");
        m_totalLikes = json.GetNamedNumber(L"totalLikes");
        m_totalViews = json.GetNamedNumber(L"totalViews");
        m_viewsCount = json.GetNamedNumber(L"viewsCount");
        m_likesCount = json.GetNamedNumber(L"likesCount");
        m_isFavourite = json.GetNamedBoolean(L"isFavourite");
        m_isLiked = json.GetNamedBoolean(L"isLiked");
        m_commentsCount = json.GetNamedNumber(L"commentsCount");

    }
    hstring InfoBlock::ID()
    {
        return m_id;
    }
    void InfoBlock::ID(hstring const& value)
    {
        if (m_id != value) {
            m_id = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::Title()
    {
        return m_title;
    }
    void InfoBlock::Title(hstring const& value)
    {
        if (m_title != value) {
            m_title = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::bikabika::CreaterBlock InfoBlock::Creater()
    {
        return m_creater;
    }
    void InfoBlock::Creater(winrt::bikabika::CreaterBlock const& value)
    {
        if (m_creater != value) {
            m_creater = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::Description()
    {
        return m_description;
    }
    void InfoBlock::Description(hstring const& value)
    {
        if (m_description != value) {
            m_description = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage InfoBlock::Thumb()
    {
        return m_thumb;
    }
    void InfoBlock::Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
    {
        if (m_thumb != value) {
            m_thumb = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::Author()
    {
        return m_author;
    }
    void InfoBlock::Author(hstring const& value)
    {
        if (m_author != value) {
            m_author = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::ChineseTeam()
    {
        return m_chineseTeam;
    }
    void InfoBlock::ChineseTeam(hstring const& value)
    {
        if (m_chineseTeam != value) {
            m_chineseTeam = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> InfoBlock::Categories()
    {
        return m_categories;
    }
    void InfoBlock::Categories(winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> const& value)
    {
        if (m_categories != value) {
            m_categories = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::CategoriesString()
    {
        return m_categoriesString;
    }
    void InfoBlock::CategoriesString(hstring const& value)
    {
        if (m_categoriesString != value) {
            m_categoriesString = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> InfoBlock::Tags()
    {
        return m_tags;
    }
    void InfoBlock::Tags(winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> const& value)
    {
        if (m_tags != value) {
            m_tags = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::TagsString()
    {
        return m_tagsString;
    }
    void InfoBlock::TagsString(hstring const& value)
    {
        if (m_tagsString != value) {
            m_tagsString = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t InfoBlock::PagesCount()
    {
        return m_pagesCount;
    }
    void InfoBlock::PagesCount(int32_t value)
    {
        if (m_pagesCount != value) {
            m_pagesCount = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t InfoBlock::EpsCount()
    {
        return m_epsCount;
    }
    void InfoBlock::EpsCount(int32_t value)
    {
        if (m_epsCount != value) {
            m_epsCount = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::Windows::UI::Xaml::Visibility InfoBlock::Finished()
    {
        return m_finished;

    }
    void InfoBlock::Finished(winrt::Windows::UI::Xaml::Visibility const& value)
    {
        if (m_finished != value) {
            m_finished = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::UpdatedAt()
    {
        return m_updatedAt;
    }
    void InfoBlock::UpdatedAt(hstring const& value)
    {
        if (m_updatedAt != value) {
            m_updatedAt = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    hstring InfoBlock::CreatedAt()
    {
        return m_createdAt;
    }
    void InfoBlock::CreatedAt(hstring const& value)
    {
        if (m_createdAt != value) {
            m_createdAt = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    bool InfoBlock::AllowDownload()
    {
        return m_allowDownload;
    }
    void InfoBlock::AllowDownload(bool value)
    {
        if (m_allowDownload != value) {
            m_allowDownload = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    bool InfoBlock::AllowComment()
    {
        return m_allowComment;
    }
    void InfoBlock::AllowComment(bool value)
    {
        if (m_allowComment != value) {
            m_allowComment = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t InfoBlock::TotalLikes()
    {
        return m_totalLikes;
    }
    void InfoBlock::TotalLikes(int32_t value)
    {
        if (m_totalLikes != value) {
            m_totalLikes = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t InfoBlock::TotalViews()
    {
        return m_totalViews;
    }
    void InfoBlock::TotalViews(int32_t value)
    {
        if (m_totalViews != value) {
            m_totalViews = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t InfoBlock::ViewsCount()
    {
        return m_viewsCount;
    }
    void InfoBlock::ViewsCount(int32_t value)
    {
        if (m_viewsCount != value) {
            m_viewsCount = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t InfoBlock::LikesCount()
    {
        return m_likesCount;
    }
    void InfoBlock::LikesCount(int32_t value)
    {
        if (m_likesCount != value) {
            m_likesCount = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    bool InfoBlock::IsFavourite()
    {
        return m_isFavourite;
    }
    void InfoBlock::IsFavourite(bool value)
    {
        if (m_isFavourite != value) {
            m_isFavourite = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    bool InfoBlock::IsLiked()
    {
        return m_isLiked;
    }
    void InfoBlock::IsLiked(bool value)
    {
        if (m_isLiked != value) {
            m_isLiked = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    int32_t InfoBlock::CommentsCount()
    {
        return m_commentsCount;
    }
    void InfoBlock::CommentsCount(int32_t value)
    {
        if (m_commentsCount != value) {
            m_commentsCount = value;
            //m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Character" });
        }
    }
    winrt::event_token InfoBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void InfoBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
