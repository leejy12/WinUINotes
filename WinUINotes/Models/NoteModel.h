#pragma once

#include "Models/NoteModel.g.h"

namespace winrt::WinUINotes::Models::implementation
{
struct NoteModel : NoteModelT<NoteModel>
{
  public:
    wil::single_threaded_rw_property<winrt::hstring> FileName;
    wil::single_threaded_rw_property<winrt::hstring> Title;
    wil::single_threaded_rw_property<winrt::hstring> Text;
    wil::single_threaded_rw_property<winrt::Windows::Foundation::DateTime> Date;

    NoteModel();
    winrt::hstring DateText() const;
    winrt::Windows::Foundation::IAsyncAction SaveAsync();
    winrt::Windows::Foundation::IAsyncAction DeleteAsync();
};
} // namespace winrt::WinUINotes::Models::implementation

namespace winrt::WinUINotes::Models::factory_implementation
{
struct NoteModel : NoteModelT<NoteModel, implementation::NoteModel>
{
};
} // namespace winrt::WinUINotes::Models::factory_implementation
