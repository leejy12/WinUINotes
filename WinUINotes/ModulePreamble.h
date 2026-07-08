#pragma once

#include <Windows.h>
#include <hstring.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <unknwn.h>

#include <coroutine>
#include <cstdint>
#include <format>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <ranges>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#undef GetCurrentTime

#define WINRT_IMPORT_MODULE

import std;
import winrt_base;
import winrt.Windows.Foundation;
import winrt.Windows.Foundation.Collections;
import winrt.Windows.Globalization.DateTimeFormatting;
import winrt.Windows.Storage;
import winrt.Windows.Storage.FileProperties;
import winrt.Windows.System;
import winrt.Windows.UI.Xaml.Interop;
import winrt.Microsoft.UI.Composition;
import winrt.Microsoft.UI.Composition.SystemBackdrops;
import winrt.Microsoft.UI.Dispatching;
import winrt.Microsoft.UI.Windowing;
import winrt.Microsoft.UI.Xaml;
import winrt.Microsoft.UI.Xaml.Controls;
import winrt.Microsoft.UI.Xaml.Controls.Primitives;
import winrt.Microsoft.UI.Xaml.Data;
import winrt.Microsoft.UI.Xaml.Interop;
import winrt.Microsoft.UI.Xaml.Markup;
import winrt.Microsoft.UI.Xaml.Navigation;
import winrt.Microsoft.UI.Xaml.XamlTypeInfo;
import winrt.WinUINotes;
import winrt.WinUINotes.Models;
import winrt.WinUINotes.Views;

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/WinUINotes.h>
#include <winrt/WinUINotes.Models.h>
#include <winrt/WinUINotes.Views.h>

#include <wil/cppwinrt.h>
#include <wil/cppwinrt_helpers.h>
#include <wil/cppwinrt_authoring.h>
