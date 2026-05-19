#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::UI::Windowing;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUINotes::implementation
{
MainWindow::MainWindow()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

    const OverlappedPresenter presenter = OverlappedPresenter::Create();
    presenter.PreferredMinimumWidth(600);
    presenter.PreferredMinimumHeight(400);
    AppWindow().SetPresenter(presenter);

    ExtendsContentIntoTitleBar(true);
    SetTitleBar(AppTitleBar());
}

void MainWindow::AppTitleBar_BackRequested([[maybe_unused]] const TitleBar &sender,
                                           [[maybe_unused]] const IInspectable &args)
{
    if (rootFrame().CanGoBack())
    {
        rootFrame().GoBack();
    }
}
} // namespace winrt::WinUINotes::implementation
