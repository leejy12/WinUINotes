#pragma once

import winrt.Windows.Foundation;
import winrt.Microsoft.UI.Xaml.Controls;

#define WINRT_IMPORT_MODULE

#include "MainWindow.g.h"

namespace winrt::WinUINotes::implementation
{
struct MainWindow : MainWindowT<MainWindow>
{
    MainWindow();
    void AppTitleBar_BackRequested(const winrt::Microsoft::UI::Xaml::Controls::TitleBar &sender,
                                   const winrt::Windows::Foundation::IInspectable &args);
};
} // namespace winrt::WinUINotes::implementation

namespace winrt::WinUINotes::factory_implementation
{
struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
{
};
} // namespace winrt::WinUINotes::factory_implementation
