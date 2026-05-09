#include "pch.h"
#include "AllNotesPage.xaml.h"
#if __has_include("Views/AllNotesPage.g.cpp")
#include "Views/AllNotesPage.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::WinUINotes::Models;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUINotes::Views::implementation
{
void AllNotesPage::NewNoteButton_Click([[maybe_unused]] const IInspectable &sender,
                                       [[maybe_unused]] const RoutedEventArgs &e)
{
    Frame().Navigate(winrt::xaml_typename<NotePage>());
}

void AllNotesPage::ItemsView_ItemInvoked([[maybe_unused]] const ItemsView &sender,
                                         const ItemsViewItemInvokedEventArgs &args)
{
    Frame().Navigate(winrt::xaml_typename<NotePage>(), args.InvokedItem());
}

IAsyncAction AllNotesPage::NoteMenuFlyoutItem_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    const MenuFlyoutItem item = sender.as<MenuFlyoutItem>();
    const NoteModel note = item.Tag().as<NoteModel>();
    IStorageItem storageItem = co_await ApplicationData::Current().LocalFolder().TryGetItemAsync(note.FileName());
    if (const StorageFile noteFile = storageItem.try_as<StorageFile>())
    {
        co_await noteFile.DeleteAsync();
    }

    winrt::WinUINotes::Models::implementation::AllNotesModel::RemoveCachedNote(note.FileName());
}

} // namespace winrt::WinUINotes::Views::implementation
