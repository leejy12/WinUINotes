#pragma once

#include "MainWindow.g.h"

namespace winrt::WinUINotes::implementation
{
struct MainWindow : MainWindowT<MainWindow>
{
    MainWindow()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }
};
} // namespace winrt::WinUINotes::implementation

namespace winrt::WinUINotes::factory_implementation
{
struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
{
};
} // namespace winrt::WinUINotes::factory_implementation
