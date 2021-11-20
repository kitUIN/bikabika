﻿#pragma once
#include <windows.h>
#include <unknwn.h>
#include <iostream>
#include <utility>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Resources.h>
#include "winrt/Microsoft.UI.Xaml.Automation.Peers.h"
#include "winrt/Microsoft.UI.Xaml.Controls.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "winrt/Microsoft.UI.Xaml.Media.h"
#include "winrt/Microsoft.UI.Xaml.XamlTypeInfo.h"
#include "winrt/Microsoft.UI.Xaml.Controls.h"
#include "winrt/Microsoft.UI.Xaml.XamlTypeInfo.h"
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Web.Syndication.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Headers.h>
extern winrt::hstring token = L"";
extern winrt::hstring imageQuality = L"medium";
extern winrt::hstring userName = L"Unknown";
extern winrt::hstring userLevel = L"Lv.5";
extern winrt::hstring userImage = L"ms-appx:///gray.png";
extern winrt::hstring serverStream = L"https://storage1.picacomic.com";