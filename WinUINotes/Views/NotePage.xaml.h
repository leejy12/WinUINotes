#pragma once

#include "Models/NoteModel.h"

#include "Views/NotePage.g.h"

namespace winrt::WinUINotes::Views::implementation
{
struct NotePage : NotePageT<NotePage>
{
  private:
    winrt::WinUINotes::Models::NoteModel note;

  public:
    winrt::WinUINotes::Models::NoteModel Note()
    {
        return note;
    };

    void Note(const winrt::WinUINotes::Models::NoteModel &_note)
    {
        note = _note;
    }

  public:
    NotePage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    winrt::Windows::Foundation::IAsyncAction SaveButton_Click(const winrt::Windows::Foundation::IInspectable &sender,
                                                              const winrt::Microsoft::UI::Xaml::RoutedEventArgs &e);
    winrt::Windows::Foundation::IAsyncAction DeleteButton_Click(const winrt::Windows::Foundation::IInspectable &sender,
                                                                const winrt::Microsoft::UI::Xaml::RoutedEventArgs &e);
};
} // namespace winrt::WinUINotes::Views::implementation

namespace winrt::WinUINotes::Views::factory_implementation
{
struct NotePage : NotePageT<NotePage, implementation::NotePage>
{
};
} // namespace winrt::WinUINotes::Views::factory_implementation
