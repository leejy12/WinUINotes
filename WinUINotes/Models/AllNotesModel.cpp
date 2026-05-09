#include "pch.h"
#include "AllNotesModel.h"
#if __has_include("Models/AllNotesModel.g.cpp")
#include "Models/AllNotesModel.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::FileProperties;

namespace winrt::WinUINotes::Models::implementation
{
AllNotesModel::AllNotesModel() : notes(CachedNotes())
{
    if (!cachedNotesLoaded && !cachedNotesLoading)
    {
        LoadNotes();
    }
}

IVector<winrt::WinUINotes::Models::NoteModel> AllNotesModel::CachedNotes()
{
    if (!cachedNotes)
    {
        cachedNotes = winrt::single_threaded_observable_vector<winrt::WinUINotes::Models::NoteModel>();
    }

    return cachedNotes;
}

bool AllNotesModel::TryGetCachedNoteIndex(const winrt::hstring &fileName, std::uint32_t &idx)
{
    const auto notes = CachedNotes();
    for (std::uint32_t i = 0; i < notes.Size(); ++i)
    {
        if (notes.GetAt(i).FileName() == fileName)
        {
            idx = i;
            return true;
        }
    }

    return false;
}

void AllNotesModel::UpsertCachedNote(const winrt::WinUINotes::Models::NoteModel &note)
{
    const auto notes = CachedNotes();

    std::uint32_t idx = 0;
    if (TryGetCachedNoteIndex(note.FileName(), idx))
    {
        notes.RemoveAt(idx);
    }

    // Insert at the first position, because the note's modified date
    // will be the latest.
    notes.InsertAt(0, note);
}

void AllNotesModel::RemoveCachedNote(const winrt::hstring &fileName)
{
    std::uint32_t idx = 0;
    if (TryGetCachedNoteIndex(fileName, idx))
    {
        CachedNotes().RemoveAt(idx);
    }
}

IAsyncAction AllNotesModel::LoadNotes()
{
    cachedNotesLoading = true;
    notes.Clear();
    StorageFolder storageFolder = ApplicationData::Current().LocalFolder();
    co_await GetFilesInFolderAsync(storageFolder);
    cachedNotesLoaded = true;
    cachedNotesLoading = false;
}

IAsyncAction AllNotesModel::GetFilesInFolderAsync(StorageFolder folder)
{
    struct FileAndModifiedDate
    {
        StorageFile file;
        DateTime modifiedDate;
    };

    IVectorView<StorageFile> files = co_await folder.GetFilesAsync();

    std::vector<FileAndModifiedDate> sortableFiles;
    sortableFiles.reserve(files.Size());

    for (const StorageFile &file : files)
    {
        const BasicProperties properties = co_await file.GetBasicPropertiesAsync();
        sortableFiles.push_back({
            .file = file,
            .modifiedDate = properties.DateModified(),
        });
    }

    std::ranges::sort(sortableFiles, [](const FileAndModifiedDate &f1, const FileAndModifiedDate &f2) {
        return f1.modifiedDate > f2.modifiedDate;
    });

    for (const auto &[file, _] : sortableFiles)
    {
        winrt::WinUINotes::Models::NoteModel note;
        const winrt::hstring contents = co_await FileIO::ReadTextAsync(file);

        // TextBox internally uses RichEdit to implement all of the complex textbox behavior,
        // and the default behavior of RichEdit is to use just CR at line breaks
        // https://github.com/microsoft/microsoft-ui-xaml/discussions/9545#discussioncomment-9125200
        std::wstring_view sv = static_cast<std::wstring_view>(contents);
        const std::uint32_t cr = static_cast<std::uint32_t>(sv.find(L'\r'));

        // The first line is the title.
        const winrt::hstring title(sv.data(), cr);
        const winrt::hstring text(sv.data() + cr + 1);

        note.FileName(file.Name());
        note.Title(title);
        note.Text(text);
        note.Date(file.DateCreated());
        notes.Append(note);
    }
}

} // namespace winrt::WinUINotes::Models::implementation
