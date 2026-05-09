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
