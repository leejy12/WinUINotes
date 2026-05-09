#include "pch.h"
#include "NotePage.xaml.h"
#include "Models/AllNotesModel.h"
#if __has_include("Views/NotePage.g.cpp")
#include "Views/NotePage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;
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
    if (HasNoContent(note.Title()))
    {
        ContentDialog dialog;
        dialog.XamlRoot(this->XamlRoot());
        dialog.Content(winrt::box_value(L"Title can not be empty."));
        dialog.CloseButtonText(L"Ok");
        co_await dialog.ShowAsync();
        co_return;
    }

    // Saving a note for the first time.
    winrt::hstring fileName = note.FileName();
    if (fileName.empty())
    {
        fileName = std::format(L"notes-{}.txt", winrt::clock::now().time_since_epoch().count());
    }
    note.FileName(fileName);

    IStorageItem item = co_await storageFolder.TryGetItemAsync(fileName);
    StorageFile noteFile = item.try_as<StorageFile>();

    if (!noteFile)
    {
        noteFile = co_await storageFolder.CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting);
    }

    co_await FileIO::WriteTextAsync(noteFile, note.Title());
    co_await FileIO::AppendTextAsync(noteFile, L"\r");
    co_await FileIO::AppendTextAsync(noteFile, note.Text());

    winrt::WinUINotes::Models::implementation::AllNotesModel::UpsertCachedNote(note);
}

IAsyncAction NotePage::DeleteButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    IStorageItem item = co_await storageFolder.TryGetItemAsync(note.FileName());
    StorageFile noteFile = item.try_as<StorageFile>();

    if (noteFile)
    {
        co_await noteFile.DeleteAsync();
    }

    winrt::WinUINotes::Models::implementation::AllNotesModel::RemoveCachedNote(note.FileName());

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
        note = noteModel;
    }
}
} // namespace winrt::WinUINotes::Views::implementation
