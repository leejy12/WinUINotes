#include "pch.h"
#include "Note.h"
#if __has_include("Models/Note.g.cpp")
#include "Models/Note.g.cpp"
#endif

using namespace winrt::Windows::Storage;

namespace winrt::WinUINotes::Models::implementation
{
Note::Note()
{
    fileName = std::format(L"notes-{}.txt", winrt::clock::now().time_since_epoch().count());
}

winrt::Windows::Foundation::IAsyncAction implementation::Note::SaveAsync()
{
    IStorageItem item = co_await storageFolder.TryGetItemAsync(fileName);
    StorageFile noteFile = item.try_as<StorageFile>();

    if (!noteFile)
    {
        noteFile = co_await storageFolder.CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting);
    }

    co_await FileIO::WriteTextAsync(noteFile, text);
}

winrt::Windows::Foundation::IAsyncAction implementation::Note::DeleteAsync()
{
    IStorageItem item = co_await storageFolder.TryGetItemAsync(fileName);
    StorageFile noteFile = item.try_as<StorageFile>();
    if (noteFile)
    {
        co_await noteFile.DeleteAsync();
    }
}
} // namespace winrt::WinUINotes::Models::implementation
