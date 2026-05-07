#include "pch.h"
#include "NoteModel.h"
#if __has_include("Models/NoteModel.g.cpp")
#include "Models/NoteModel.g.cpp"
#endif

using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::WinUINotes::Models::implementation
{
NoteModel::NoteModel()
{
    fileName = std::format(L"notes-{}.txt", winrt::clock::now().time_since_epoch().count());
}

winrt::Windows::Foundation::IAsyncAction implementation::NoteModel::SaveAsync()
{
    IStorageItem item = co_await storageFolder.TryGetItemAsync(fileName);
    StorageFile noteFile = item.try_as<StorageFile>();

    if (!noteFile)
    {
        noteFile = co_await storageFolder.CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting);
    }

    co_await FileIO::WriteTextAsync(noteFile, text);
}

winrt::Windows::Foundation::IAsyncAction implementation::NoteModel::DeleteAsync()
{
    IStorageItem item = co_await storageFolder.TryGetItemAsync(fileName);
    StorageFile noteFile = item.try_as<StorageFile>();
    if (noteFile)
    {
        co_await noteFile.DeleteAsync();
    }
}

winrt::hstring NoteModel::DateText() const
{
    const DateTimeFormatter formatter(L"shortdate shorttime");
    return formatter.Format(date);
}
} // namespace winrt::WinUINotes::Models::implementation
