#include "pch.h"
#include "AllNotesPage.xaml.h"
#if __has_include("Views/AllNotesPage.g.cpp")
#include "Views/AllNotesPage.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::WinUINotes::Models;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUINotes::Views::implementation
{
void AllNotesPage::NewNoteButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    Frame().Navigate(winrt::xaml_typename<NotePage>());
}

void AllNotesPage::ItemsView_ItemInvoked(const ItemsView &sender, const ItemsViewItemInvokedEventArgs &args)
{
    Frame().Navigate(winrt::xaml_typename<NotePage>(), args.InvokedItem());
}

void AllNotesPage::NoteMenuFlyoutItem_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    const MenuFlyoutItem item = sender.as<MenuFlyoutItem>();
    const winrt::hstring fileName = item.Tag().as<winrt::hstring>();
    const auto &notes = allNotes.Notes();
    const auto it = std::ranges::find_if(notes, [&fileName](const NoteModel &n) { return n.FileName() == fileName; });
    const std::uint32_t idx = static_cast<std::uint32_t>(std::distance(notes.begin(), it));
    notes.RemoveAt(idx);

    // TODO: Actually delete the file.
}

} // namespace winrt::WinUINotes::Views::implementation
