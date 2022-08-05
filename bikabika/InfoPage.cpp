#include "pch.h"
#include "InfoPage.h"
#if __has_include("InfoPage.g.cpp")
#include "InfoPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::Data::Json;
using namespace Windows::UI::Input;

namespace winrt::bikabika::implementation
{
    InfoPage::InfoPage()
    {
        InitializeComponent();
    }
    bikabika::CommentView InfoPage::GetCommentView()
    {
        return m_commentView;
    }

    Windows::Foundation::IAsyncAction InfoPage::Comment(int32_t const& page)
    {
        auto res = co_await rootPage.HttpClient().Comments(m_id, page);
        if (res.Code() == -1)
        {
            rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
        }
        else if (res.Code() == 200)
        {
            if (!m_isTop && res.TopComments().Size() > 0)
            {
                m_isTop = true;
                for (auto x : res.TopComments())
                {
                    m_commentView.Comments().Append(x);
                }
            }
            for (auto y : res.Comments())
            {
                m_commentView.Comments().Append(y);
            }

            m_commentsPages = res.Pages();
            m_commentsPage = res.Page();
            m_commentsContinue = false;
        }
        else if (res.Code() == 401 && res.Error() == L"1005")
        {
            rootPage.ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
        }
        else
        {
            rootPage.ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
        }
    }
    Windows::Foundation::IAsyncOperation<uint32_t> InfoPage::Eps(int32_t const& page)
    {
        auto res = co_await rootPage.HttpClient().Episodes(m_id, page);
        if (res.Code() == -1)
        {
            rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
        }
        else if (res.Code() == 200)
        {
            for (auto x : res.Episodes())
            {

                m_eps.Append(x);
            }
            m_total = res.Total();
            EpisodesListV().ItemsSource(box_value(m_eps));
            co_return res.Pages();
        }
        else if (res.Code() == 401 && res.Error() == L"1005")
        {
            rootPage.ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
        }
        else
        {
            rootPage.ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
        }
        co_return 0;
    }

    winrt::event_token InfoPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void InfoPage::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
    BikaClient::Blocks::BookBlock InfoPage::Book()
    {
        return m_book;
    }
    void InfoPage::Book(BikaClient::Blocks::BookBlock const& value)
    {
        m_book = value;
        m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Book" });
    }
    Windows::Foundation::IAsyncAction InfoPage::Recommend()
    {
        auto res = co_await rootPage.HttpClient().Recommend(m_id);
        if (res.Code() == -1)
        {
            rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
        }
        else if (res.Code() == 200)
        {
            if (res.Comics().Size()>0)
            {
                for (auto x : res.Comics())
                {
                    m_comics.Append(x);
                }
                ComicsGridV().ItemsSource(box_value(m_comics));
            }
            else
            {
                ImageEmpty().Visibility(Visibility::Visible);
                BlockEmpty().Visibility(Visibility::Visible);
            }

        }
        else if (res.Code() == 401 && res.Error() == L"1005")
        {
            rootPage.ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
        }
        else
        {
            rootPage.ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
        }
    }
    Windows::Foundation::IAsyncAction InfoPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        auto params = winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>(e.Parameter());
        auto img = winrt::unbox_value<winrt::Windows::UI::Xaml::Media::ImageSource>(params.GetAt(0));
        m_id = winrt::unbox_value<ComicArgs>(params.GetAt(1)).BookId();
        __super::OnNavigatedTo(e);
        UserThumb().ProfilePicture(rootPage.User().Thumb().Img());
        auto anim = winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().GetAnimation(L"ForwardConnectedAnimation");
        Img().Source(img);
        if (anim) anim.TryStart(Img());
        auto res = co_await rootPage.HttpClient().BookInfo(m_id);
        if (res.Code() == -1)
        {
            rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
        }
        else if (res.Code() == 200)
        {
            auto book = res.BookInfos();
            Book(book);
            for (auto x : book.Tags())
            {
                m_tags.Append(x);
            }
            TagsContent().ItemsSource(box_value(m_tags));
            auto pages = co_await Eps(1);
            for (uint32_t i = 2; i <= pages; i++)
            {
                co_await Eps(i);
            }
            co_await Recommend();
            co_await Comment(m_commentsPage);
        }
        else if (res.Code() == 401 && res.Error() == L"1005")
        {
            rootPage.ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
        }
        else
        {
            rootPage.ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
        }
    }

}
Windows::Foundation::IAsyncAction winrt::bikabika::implementation::InfoPage::Like_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

    auto res = co_await rootPage.HttpClient().Like(m_id);
    if (res.Code() == 200)
    {
        if (m_book.IsLiked())
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"BlockLike/Text"), resourceLoader.GetString(L"Message/Book/Success"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
        }
        else
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"Message/Like/Cancel"), resourceLoader.GetString(L"Message/Book/Success"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
        }
    }
    else
    {
        m_book.IsLiked(!sender.as<ToggleButton>().IsChecked().Value());
        if (m_book.IsLiked())
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"BlockLike/Text"), resourceLoader.GetString(L"Message/Book/Fail"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
        }
        else
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"Message/Like/Cancel"), resourceLoader.GetString(L"Message/Book/Fail"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
        }
    }
}
Windows::Foundation::IAsyncAction winrt::bikabika::implementation::InfoPage::Favourite_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

    auto res = co_await rootPage.HttpClient().Favourite(m_id);
    if (res.Code() == 200)
    {
        if (m_book.IsFavourite())
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"BlockFavourite/Text"), resourceLoader.GetString(L"Message/Book/Success"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
        }
        else
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"Message/Favourite/Cancel"), resourceLoader.GetString(L"Message/Book/Success"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
        }
    }
    else {
        m_book.IsFavourite(!sender.as<ToggleButton>().IsChecked().Value());
        if (m_book.IsFavourite())
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"BlockFavourite/Text"), resourceLoader.GetString(L"Message/Book/Fail"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
        }
        else
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"Message/Favourite/Cancel"), resourceLoader.GetString(L"Message/Book/Fail"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
        }
    }

}
/// <summary>
/// 标签点击
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::TagButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    auto text = sender.as<Button>().Content().as<hstring>();
    winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
    symbol.Symbol(Symbol::Find);
    winrt::Windows::UI::Xaml::Controls::Frame frame;
    frame.Navigate(winrt::xaml_typename<bikabika::ComicPage>(), box_value(ComicArgs{ ComicsType::SEARCH, text, BikaClient::Utils::BikaSort{ BikaClient::Utils::SortMode::DD } }));
    rootPage.CreateNewTab(frame, text, symbol);
}
void winrt::bikabika::implementation::InfoPage::Author_Drop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::Title_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{

}
/// <summary>
/// 点击搜索用户
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::UsersName_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    PointerPoint currentPoint = e.GetCurrentPoint(NULL);
    PointerPointProperties props = currentPoint.Properties();
    if (props.IsRightButtonPressed()) {

    }
    else
    {
        auto text = sender.as<TextBlock>().Text();
        winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
        symbol.Symbol(Symbol::Find);
        winrt::Windows::UI::Xaml::Controls::Frame frame;
        frame.Navigate(winrt::xaml_typename<bikabika::ComicPage>(), box_value(ComicArgs{ ComicsType::SEARCH, text, BikaClient::Utils::BikaSort{ BikaClient::Utils::SortMode::DD } }));
        rootPage.CreateNewTab(frame, text, symbol);
    }
}
void winrt::bikabika::implementation::InfoPage::CommentFlyout_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
{

}
void winrt::bikabika::implementation::InfoPage::CommentSubmit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::MainGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e)
{

}
/// <summary>
/// 用户详情
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::CreaterBorder_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{

    ToggleThemeTeachingTip1().Title(m_book.Creater().Role());
    UsersTitle().Text(m_book.Creater().Title());
	UsersName().Text(m_book.Creater().Name());
    UsersLevel().Text(m_book.Creater().LevelString());
    UsersPic().ProfilePicture(m_book.Creater().Thumb().Img());
    UserInfomation().Text(m_book.Creater().Slogan());
    ToggleThemeTeachingTip1().Target(sender.as<FrameworkElement>());
    ToggleThemeTeachingTip1().IsOpen(true);
}

/// <summary>
/// 大家都在看点击跳转
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
{
    auto comicBlock = e.ClickedItem().as<BikaClient::Blocks::ComicBlock>();
    auto container = ComicsGridV().ContainerFromItem(e.ClickedItem()).as<winrt::Windows::UI::Xaml::Controls::GridViewItem>();
    FrameworkElement root = container.ContentTemplateRoot().as<FrameworkElement>();
    bikabika::BikaImage bikaImg = root.FindName(L"ConnectedElement2").as<bikabika::BikaImage>();
    if (bikaImg.ImageLoaded()) winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().PrepareToAnimate(L"ForwardConnectedAnimation", bikaImg.as<UIElement>());
    winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
    winrt::Windows::UI::Xaml::Controls::Frame frame;
    symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::PreviewLink);
    frame.Navigate(winrt::xaml_typename<bikabika::InfoPage>(), box_value(single_threaded_vector<winrt::Windows::Foundation::IInspectable>({ box_value(bikaImg.ImgSource()), box_value(bikabika::ComicArgs(comicBlock.ID(),1,1,1)) })), winrt::Windows::UI::Xaml::Media::Animation::SuppressNavigationTransitionInfo());
    frame.Navigate(winrt::xaml_typename<bikabika::InfoPage>(), box_value(single_threaded_vector<winrt::Windows::Foundation::IInspectable>({ box_value(root.FindName(L"ConnectedElement2").as<winrt::Windows::UI::Xaml::Controls::Image>().Source()), box_value(bikabika::ComicArgs(comicBlock.ID(),1,1,1)) })), winrt::Windows::UI::Xaml::Media::Animation::SuppressNavigationTransitionInfo());
    rootPage.CreateNewTab(frame, comicBlock.Title(), symbol);
}
/// <summary>
/// 点击漫画话按钮
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    Windows::Storage::ApplicationDataContainer historys = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Historys", Windows::Storage::ApplicationDataCreateDisposition::Always);
    auto eps = sender.as<Button>().Tag().as<BikaClient::Blocks::EpisodeBlock>();
    bikabika::PicArgs picArgs{ m_id,m_total,eps,m_eps };
    winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
    winrt::Windows::UI::Xaml::Controls::Frame frame;
    symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::Pictures);
    frame.Navigate(winrt::xaml_typename<bikabika::PicPage>(), box_value(picArgs));
    rootPage.CreateNewTab(frame, picArgs.Episode().Title(), symbol);

}

/// <summary>
/// 鼠标进入评论和爱心的响应
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::CommentLike_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    sender.as<Border>().Background(Media::SolidColorBrush{ Windows::UI::Colors::LightGray() });
}

/// <summary>
/// 鼠标离开评论和爱心的响应
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::CommentLike_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    sender.as<Border>().Background(Media::SolidColorBrush{ Windows::UI::Colors::Transparent() });
}

/// <summary>
/// 展开评论的评论
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns></returns>
Windows::Foundation::IAsyncAction winrt::bikabika::implementation::InfoPage::CommentComment_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    auto border = sender.as<Border>();
    auto block = border.Tag().as<BikaClient::Blocks::CommentBlock>();
    InfoReply().Title(resourceLoader.GetString(L"Keyword/Reply") + L":" + block.User().Name());
    InfoReply().Content(box_value(block.Content()));
    m_reply = block.ID();
    InfoReply().IsOpen(true);
    if (block.CommentsCount() > 0)
    {
        if (block.ReplyComments().Size() >0)
        {
            block.ReplyComments().Clear();
            InfoReply().IsOpen(false);
        }
        else
        {
            BikaClient::Responses::CommentsResponse res = co_await rootPage.HttpClient().GetReplyComment(block.ID(), 1);
            if (res.Code() == 200)
            {
                for (auto x : res.Comments())
                {
                    block.ReplyComments().Append(x);
                }
            }
        }
    }

}

/// <summary>
/// 评论的爱心
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns></returns>
Windows::Foundation::IAsyncAction  winrt::bikabika::implementation::InfoPage::CommentLike_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    auto stack = sender.as<Border>().Child().as<StackPanel>();
    auto like = stack.Children().GetAt(0).as<Grid>().Children().GetAt(1).as<FontIcon>();
    auto likeCount = stack.Children().GetAt(1).as<TextBlock>();
    if (like.Visibility() == Visibility::Collapsed)
    {
        like.Visibility(Visibility::Visible);
    }
    else like.Visibility(Visibility::Collapsed);
    auto comment = sender.as<Border>().Tag().as<BikaClient::Blocks::CommentBlock>();
    auto res = co_await rootPage.HttpClient().LikeComments(comment.ID());
    if (res.Code() == 200)
    {
        if (like.Visibility() == Visibility::Visible)
        {
            likeCount.Text(to_hstring(comment.LikesCount() + 1));
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"BlockLike/Text"), resourceLoader.GetString(L"Message/Book/Success"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
        }
        else
        {
            likeCount.Text(to_hstring(comment.LikesCount() - 1));
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"Message/Like/Cancel"), resourceLoader.GetString(L"Message/Book/Success"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
        }
    }
    else {
        if (like.Visibility() == Visibility::Collapsed)
        {
            like.Visibility(Visibility::Visible);
        }
        else like.Visibility(Visibility::Collapsed);
        if (like.Visibility() == Visibility::Visible)
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"BlockLike/Text"), resourceLoader.GetString(L"Message/Book/Fail"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
        }
        else
        {
            rootPage.InfoBarMessageShow(resourceLoader.GetString(L"Message/Like/Cancel"), resourceLoader.GetString(L"Message/Book/Fail"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
        }
    }
}
/// <summary>
/// 评论的自动加载控制
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns></returns>
Windows::Foundation::IAsyncAction  winrt::bikabika::implementation::InfoPage::ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e)
{
    auto sv = sender.as<winrt::Windows::UI::Xaml::Controls::ScrollViewer>();
    if (sv.VerticalOffset() + sv.ActualHeight() + 2 >= sv.ExtentHeight()) {
        if (m_commentsPage < m_commentsPages && !m_commentsContinue)
        {
            m_commentsContinue = true;

            co_await Comment(m_commentsPage + 1);
        }
    }

}
/// <summary>
/// 用户点击详细
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::InfoPage::PersonPicture_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    auto comment = sender.as<PersonPicture>().Parent().as<Grid>().Children().GetAt(4).as<Grid>().Children().GetAt(0).as<StackPanel>().Children().GetAt(0).as<Border>().Tag().as<BikaClient::Blocks::CommentBlock>();

    ToggleThemeTeachingTip1().Title(comment.User().Role());
    UsersTitle().Text(comment.User().Title());
    UsersName().Text(comment.User().Name());
    UsersLevel().Text(comment.User().LevelString());
    UsersPic().ProfilePicture(comment.User().Thumb().Img());
    UserInfomation().Text(comment.User().Slogan());
    ToggleThemeTeachingTip1().Target(sender.as<FrameworkElement>());
    ToggleThemeTeachingTip1().IsOpen(true);
}

/// <summary>
/// 发送评论
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
Windows::Foundation::IAsyncAction winrt::bikabika::implementation::InfoPage::ButtonSend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    auto text = SendContent().Text();
    SendContent().Text(L"");
    if (InfoReply().IsOpen())
    {
        auto res = co_await rootPage.HttpClient().ReplyComment(m_reply, text);
    }
    else
    {
        auto res = co_await rootPage.HttpClient().SendComments(m_id, text);
    }
    m_isTop = false;
    m_commentView.Comments().Clear();
    co_await Comment(1);
}
