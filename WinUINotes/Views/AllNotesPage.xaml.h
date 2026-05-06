#pragma once

#include "Models/AllNotesModel.h"

#include "Views/AllNotesPage.g.h"

namespace winrt::WinUINotes::Views::implementation
{
struct AllNotesPage : AllNotesPageT<AllNotesPage>
{
  public:
    winrt::WinUINotes::Models::AllNotesModel allNotes;

  public:
    AllNotesPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    winrt::WinUINotes::Models::AllNotesModel AllNotes()
    {
        return allNotes;
    }

    void AllNotes(const winrt::WinUINotes::Models::AllNotesModel &_allNotes)
    {
        allNotes = _allNotes;
    }
};
} // namespace winrt::WinUINotes::Views::implementation

namespace winrt::WinUINotes::Views::factory_implementation
{
struct AllNotesPage : AllNotesPageT<AllNotesPage, implementation::AllNotesPage>
{
};
} // namespace winrt::WinUINotes::Views::factory_implementation
