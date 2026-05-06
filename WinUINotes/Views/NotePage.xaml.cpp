#include "pch.h"
#include "NotePage.xaml.h"
#if __has_include("Views/NotePage.g.cpp")
#include "Views/NotePage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUINotes::Views::implementation
{

IAsyncAction NotePage::SaveButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    co_return;
}

IAsyncAction NotePage::DeleteButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    co_return;
}
} // namespace winrt::WinUINotes::Views::implementation
