#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::ViewManagement;

namespace winrt::bikabika::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
        
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    Windows::UI::Composition::ContainerVisual MainPage::GetVisual(Windows::UI::Xaml::UIElement element)
    {
        // 获取Xaml内的元素
        auto hostVisual = ElementCompositionPreview::GetElementVisual(element);
        auto root = hostVisual.Compositor().CreateContainerVisual();
        ElementCompositionPreview::SetElementChildVisual(element, root);
        return root;
    }

 
    

    



}



