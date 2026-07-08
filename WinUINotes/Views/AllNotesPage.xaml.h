#pragma once

#include "Models/AllNotesModel.h"

#include "Views/AllNotesPage.g.h"

namespace winrt::WinUINotes::Views::implementation
{
struct AllNotesPage : AllNotesPageT<AllNotesPage>
{
  public:
    wil::single_threaded_rw_property<winrt::WinUINotes::Models::AllNotesModel> AllNotes;

  public:
    AllNotesPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    void NewNoteButton_Click(const winrt::Windows::Foundation::IInspectable &sender,
                             const winrt::Microsoft::UI::Xaml::RoutedEventArgs &e);

    void ItemsView_ItemInvoked(const winrt::Microsoft::UI::Xaml::Controls::ItemsView &sender,
                               const winrt::Microsoft::UI::Xaml::Controls::ItemsViewItemInvokedEventArgs &args);

    winrt::Windows::Foundation::IAsyncAction NoteMenuFlyoutItem_Click(
        const winrt::Windows::Foundation::IInspectable &sender, const winrt::Microsoft::UI::Xaml::RoutedEventArgs &e);
};
} // namespace winrt::WinUINotes::Views::implementation

namespace winrt::WinUINotes::Views::factory_implementation
{
struct AllNotesPage : AllNotesPageT<AllNotesPage, implementation::AllNotesPage>
{
};
} // namespace winrt::WinUINotes::Views::factory_implementation
