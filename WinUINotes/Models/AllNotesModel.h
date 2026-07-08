#pragma once

import winrt.Windows.Foundation;
import winrt.Windows.Storage;

#include <wil/cppwinrt.h>
#include <wil/cppwinrt_helpers.h>
#include <wil/cppwinrt_authoring.h>

#define WINRT_IMPORT_MODULE

#include "Models/NoteModel.h"

#include "Models/AllNotesModel.g.h"

namespace winrt::WinUINotes::Models::implementation
{

struct AllNotesModel : AllNotesModelT<AllNotesModel>
{
  private:
    winrt::Windows::Foundation::IAsyncAction LoadNotes();
    winrt::Windows::Foundation::IAsyncAction GetFilesInFolderAsync(winrt::Windows::Storage::StorageFolder folder);

  public:
    AllNotesModel();

    wil::single_threaded_rw_property<
        winrt::Windows::Foundation::Collections::IVector<winrt::WinUINotes::Models::NoteModel>>
        Notes;
};
} // namespace winrt::WinUINotes::Models::implementation

namespace winrt::WinUINotes::Models::factory_implementation
{
struct AllNotesModel : AllNotesModelT<AllNotesModel, implementation::AllNotesModel>
{
};
} // namespace winrt::WinUINotes::Models::factory_implementation
