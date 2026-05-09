#include "pch.h"
#include "NoteModel.h"
#include "Models/AllNotesModel.h"
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

winrt::hstring NoteModel::DateText() const
{
    const DateTimeFormatter formatter(L"shortdate shorttime");
    return formatter.Format(date);
}

IAsyncAction NoteModel::SaveAsync()
{
    StorageFolder storageFolder = ApplicationData::Current().LocalFolder();

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

    co_await FileIO::WriteTextAsync(noteFile, title);
    co_await FileIO::AppendTextAsync(noteFile, L"\r");
    co_await FileIO::AppendTextAsync(noteFile, text);

    winrt::WinUINotes::Models::implementation::AllNotesModel::UpsertCachedNote(*this);
}

IAsyncAction NoteModel::DeleteAsync()
{
    if (fileName.empty())
    {
        co_return;
    }

    StorageFolder storageFolder = ApplicationData::Current().LocalFolder();
    IStorageItem item = co_await storageFolder.TryGetItemAsync(fileName);
    StorageFile noteFile = item.try_as<StorageFile>();

    if (noteFile)
    {
        co_await noteFile.DeleteAsync();
    }

    winrt::WinUINotes::Models::implementation::AllNotesModel::RemoveCachedNote(fileName);
}
} // namespace winrt::WinUINotes::Models::implementation
