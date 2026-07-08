#pragma once

import winrt.Microsoft.UI.Xaml;

#define WINRT_IMPORT_MODULE

#include "App.xaml.g.h"

namespace winrt::WinUINotes::implementation
{
struct App : AppT<App>
{
    App();

    void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const &);

  private:
    winrt::Microsoft::UI::Xaml::Window window{nullptr};
};
} // namespace winrt::WinUINotes::implementation
