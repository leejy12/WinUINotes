#include "../ModulePreamble.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

#include "NoteModel.h"
#include "Models/AllNotesModel.h"
#if __has_include("Models/NoteModel.g.cpp")
#include "Models/NoteModel.g.cpp"
#endif

namespace winrt::WinUINotes::Models::implementation
{
NoteModel::NoteModel()
{
    if (FileName().empty())
    {
        Date = winrt::clock::now();
    }
}

winrt::hstring NoteModel::DateText() const
{
    const DateTimeFormatter formatter(L"shortdate shorttime");
    return formatter.Format(Date());
}

IAsyncAction NoteModel::SaveAsync()
{
    StorageFolder storageFolder = ApplicationData::Current().LocalFolder();

    if (FileName().empty())
    {
        FileName = std::format(L"notes-{}.txt", Date().time_since_epoch().count());
    }

    IStorageItem item = co_await storageFolder.TryGetItemAsync(FileName());
    StorageFile noteFile = item.try_as<StorageFile>();

    if (!noteFile)
    {
        noteFile = co_await storageFolder.CreateFileAsync(FileName(), CreationCollisionOption::ReplaceExisting);
    }

    co_await FileIO::WriteTextAsync(noteFile, Title());
    co_await FileIO::AppendTextAsync(noteFile, L"\r");
    co_await FileIO::AppendTextAsync(noteFile, Text());
}

IAsyncAction NoteModel::DeleteAsync()
{
    if (FileName().empty())
    {
        co_return;
    }

    StorageFolder storageFolder = ApplicationData::Current().LocalFolder();
    IStorageItem item = co_await storageFolder.TryGetItemAsync(FileName());
    StorageFile noteFile = item.try_as<StorageFile>();

    if (noteFile)
    {
        co_await noteFile.DeleteAsync();
    }
}
} // namespace winrt::WinUINotes::Models::implementation
