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
IAsyncAction NotePage::NotePage_Loaded(const IInspectable &sender, const RoutedEventArgs &e)
{
    auto item = co_await storageFolder.TryGetItemAsync(fileName);
    noteFile = item ? std::optional{item.as<StorageFile>()} : std::nullopt;

    if (noteFile.has_value())
    {
        NoteEditor().Text(co_await FileIO::ReadTextAsync(noteFile.value()));
    }
}

IAsyncAction NotePage::SaveButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    if (!noteFile.has_value())
    {
        noteFile = co_await storageFolder.CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting);
    }
    co_await FileIO::WriteTextAsync(noteFile.value(), NoteEditor().Text());
}

IAsyncAction NotePage::DeleteButton_Click(const IInspectable &sender, const RoutedEventArgs &e)
{
    if (noteFile.has_value())
    {
        co_await noteFile.value().DeleteAsync();
        noteFile.reset();
        NoteEditor().Text(L"");
    }
}
} // namespace winrt::WinUINotes::Views::implementation
