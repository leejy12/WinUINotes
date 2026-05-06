#include "pch.h"
#include "AllNotesModel.h"
#if __has_include("Models/AllNotesModel.g.cpp")
#include "Models/AllNotesModel.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Storage;

namespace winrt::WinUINotes::Models::implementation
{
AllNotesModel::AllNotesModel() : notes(winrt::single_threaded_observable_vector<winrt::WinUINotes::Models::NoteModel>())
{
    LoadNotes();
}

IAsyncAction AllNotesModel::LoadNotes()
{
    notes.Clear();
    StorageFolder storageFolder = ApplicationData::Current().LocalFolder();
    co_await GetFilesInFolderAsync(storageFolder);
}

IAsyncAction AllNotesModel::GetFilesInFolderAsync(StorageFolder folder)
{
    const IVectorView<StorageFile> files = co_await folder.GetFilesAsync();
    for (const StorageFile &file : files)
    {
        winrt::WinUINotes::Models::NoteModel note;
        note.FileName(file.Name());
        note.Text(co_await FileIO::ReadTextAsync(file));
        note.Date(file.DateCreated());
        notes.Append(note);
    }
}

} // namespace winrt::WinUINotes::Models::implementation
