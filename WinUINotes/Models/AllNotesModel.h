#pragma once

#include "Models/NoteModel.h"

#include "Models/AllNotesModel.g.h"

namespace winrt::WinUINotes::Models::implementation
{

struct AllNotesModel : AllNotesModelT<AllNotesModel>
{
  private:
    winrt::Windows::Foundation::Collections::IVector<winrt::WinUINotes::Models::NoteModel> notes;
    inline static winrt::Windows::Foundation::Collections::IVector<winrt::WinUINotes::Models::NoteModel> cachedNotes =
        nullptr;
    inline static bool cachedNotesLoaded = false;
    inline static bool cachedNotesLoading = false;

    winrt::Windows::Foundation::IAsyncAction LoadNotes();
    winrt::Windows::Foundation::IAsyncAction GetFilesInFolderAsync(winrt::Windows::Storage::StorageFolder folder);
    static winrt::Windows::Foundation::Collections::IVector<winrt::WinUINotes::Models::NoteModel> CachedNotes();
    static bool TryGetCachedNoteIndex(const winrt::hstring &fileName, std::uint32_t &idx);

  public:
    AllNotesModel();
    static void UpsertCachedNote(const winrt::WinUINotes::Models::NoteModel &note);
    static void RemoveCachedNote(const winrt::hstring &fileName);

    winrt::Windows::Foundation::Collections::IVector<winrt::WinUINotes::Models::NoteModel> Notes()
    {
        return notes;
    }

    void Notes(const winrt::Windows::Foundation::Collections::IVector<winrt::WinUINotes::Models::NoteModel> &_notes)
    {
        notes = _notes;
    }
};
} // namespace winrt::WinUINotes::Models::implementation

namespace winrt::WinUINotes::Models::factory_implementation
{
struct AllNotesModel : AllNotesModelT<AllNotesModel, implementation::AllNotesModel>
{
};
} // namespace winrt::WinUINotes::Models::factory_implementation
