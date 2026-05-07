#include "pch.h"
#include "AllNotesPage.xaml.h"
#if __has_include("Views/AllNotesPage.g.cpp")
#include "Views/AllNotesPage.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUINotes::Views::implementation
{
void AllNotesPage::NewNoteButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    Frame().Navigate(winrt::xaml_typename<NotePage>());
}

void AllNotesPage::ItemsView_ItemInvoked(const ItemsView &sender,
                                                         const ItemsViewItemInvokedEventArgs &args)
{
    Frame().Navigate(winrt::xaml_typename<NotePage>(), args.InvokedItem());
}

} // namespace winrt::WinUINotes::Views::implementation
