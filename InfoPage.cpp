#include "pch.h"
#include "InfoPage.h"
#if __has_include("InfoPage.g.cpp")
#include "InfoPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    InfoPage::InfoPage()
    {
        InitializeComponent();
    }

   
    
    
    Windows::Foundation::IAsyncAction InfoPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        auto params = winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>(e.Parameter());

        auto img = winrt::unbox_value<winrt::Windows::UI::Xaml::Media::ImageSource>(params.GetAt(0));
		m_id = winrt::unbox_value<hstring>(params.GetAt(1));
        //OutputDebugStringW(_id.c_str());
        
		
		__super::OnNavigatedTo(e);
		Img().Source(img);
		auto anim = winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().GetAnimation(L"ForwardConnectedAnimation");
		anim.TryStart(Img());
        auto res{ co_await m_bikaHttp.BookInfo(m_id) };
        if (res[1] == 'T') {
            //auto show{ PicErrorDialog().ShowAsync() };
        }
        else if (res[1] == 'E') {
            /*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
            LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
            LoginContentDialog().Content(box_value(res));
            LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
            auto show{ co_await LoginContentDialog().ShowAsync() };*/
        }
        else
        {
            Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(res);
            double code = resp.GetNamedNumber(L"code");
            if (code == (double)200)
            {
                Windows::Data::Json::JsonObject ca = resp.GetNamedObject(L"data");
                Windows::Data::Json::JsonObject json = ca.GetNamedObject(L"comic");
                m_id = json.GetNamedString(L"_id");
                m_title = json.GetNamedString(L"title");
                Title().Text(m_title);
                m_creater = winrt::make<CreaterBlock>(json.GetNamedObject(L"_creator"));
                m_description = json.GetNamedString(L"description");
                extern winrt::hstring serverStream;
                hstring path = serverStream + L"/static/" + json.GetNamedObject(L"thumb").GetNamedString(L"path");
                m_thumb = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ path} };
                m_author = json.GetNamedString(L"author");
                Author().Text(m_author);
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
            else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
            {	//缺少鉴权
                /*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
                LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
                LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginAuthFail/Content")));
                LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
                auto show{ co_await LoginContentDialog().ShowAsync() };
                if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None) Frame().Navigate(winrt::xaml_typename<bikabika::Login>());
                */
            }
            else
            {
                //未知
                /*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
                LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
                LoginContentDialog().Content(box_value(to_hstring(code) + L":" + resp.GetNamedString(L"message")));
                LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
                auto show{ co_await LoginContentDialog().ShowAsync() };
                */
            }
        }
    }
    
}
