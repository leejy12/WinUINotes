#include "pch.h"
#include "NotePage.xaml.h"
#if __has_include("Views/NotePage.g.cpp")
#include "Views/NotePage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace WinUINotes::Models;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

bool HasNoContent(const winrt::hstring &str)
{
    return str.empty() || std::ranges::all_of(str, [](wchar_t c) { return c == L' '; });
}

namespace winrt::WinUINotes::Views::implementation
{

IAsyncAction NotePage::SaveButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    if (HasNoContent(Note().Title()))
    {
        ContentDialog dialog;
        dialog.XamlRoot(this->XamlRoot());
        dialog.Content(winrt::box_value(L"Title can not be empty."));
        dialog.CloseButtonText(L"Ok");
        co_await dialog.ShowAsync();
        co_return;
    }

    co_await Note().SaveAsync();
}

IAsyncAction NotePage::DeleteButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    co_await Note().DeleteAsync();

    if (Frame().CanGoBack())
    {
        Frame().GoBack();
    }

    co_return;
}

void NotePage::OnNavigatedTo(const NavigationEventArgs &args)
{
    const NoteModel noteModel = args.Parameter().try_as<NoteModel>();
    if (noteModel)
    {
        Note = noteModel;
    }
}
} // namespace winrt::WinUINotes::Views::implementation
