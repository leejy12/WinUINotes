#include "pch.h"
#include "NoteModel.h"
#if __has_include("Models/NoteModel.g.cpp")
#include "Models/NoteModel.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::WinUINotes::Models::implementation
{
NoteModel::NoteModel()
{
    if (fileName.empty())
    {
        date = winrt::clock::now();
    }
}

IAsyncAction NoteModel::SaveAsync()
{
    // Saving a note for the first time.
    if (fileName.empty())
    {
        fileName = std::format(L"notes-{}.txt", winrt::clock::now().time_since_epoch().count());
    }

    IStorageItem item = co_await storageFolder.TryGetItemAsync(fileName);
    StorageFile noteFile = item.try_as<StorageFile>();

    if (!noteFile)
    {
        noteFile = co_await storageFolder.CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting);
    }

    co_await FileIO::WriteTextAsync(noteFile, text);
}

IAsyncAction NoteModel::DeleteAsync()
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
