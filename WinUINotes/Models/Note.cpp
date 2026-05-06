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
    fileName = std::format(L"notes {:%Y-%m-%d %H:%M:%S}.txt", winrt::clock::to_sys(winrt::clock::now()));
}

winrt::Windows::Foundation::IAsyncAction implementation::Note::SaveAsync()
{
    StorageFile noteFile = (co_await storageFolder.TryGetItemAsync(fileName)).as<StorageFile>();
    if (!noteFile)
    {
        storageFolder.CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting);
    }

    co_await FileIO::WriteTextAsync(noteFile, text);
}

winrt::Windows::Foundation::IAsyncAction implementation::Note::DeleteAsync()
{
    StorageFile noteFile = (co_await storageFolder.TryGetItemAsync(fileName)).as<StorageFile>();
    if (!noteFile)
    {
        co_await noteFile.DeleteAsync();
    }
}
} // namespace winrt::WinUINotes::Models::implementation
