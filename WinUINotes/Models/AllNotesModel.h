#pragma once

#include "Models/NoteModel.h"

#include "Models/AllNotesModel.g.h"

namespace winrt::WinUINotes::Models::implementation
{

struct AllNotesModel : AllNotesModelT<AllNotesModel>
{
  private:
    winrt::Windows::Foundation::Collections::IObservableVector<NoteModel> allNotes;

  public:
    AllNotesModel()
    {
    }

    winrt::Windows::Foundation::Collections::IObservableVector<NoteModel> AllNotes()
    {
        return allNotes;
    }

    void AllNotes(const winrt::Windows::Foundation::Collections::IObservableVector<NoteModel> &_allNotes)
    {
        allNotes = _allNotes;
    }
};
} // namespace winrt::WinUINotes::Models::implementation

namespace winrt::WinUINotes::Models::factory_implementation
{
struct AllNotesModel : AllNotesModelT<AllNotesModel, implementation::AllNotesModel>
{
};
} // namespace winrt::WinUINotes::Models::factory_implementation
