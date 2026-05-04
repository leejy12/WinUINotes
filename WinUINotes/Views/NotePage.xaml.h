#pragma once

#include "Views/NotePage.g.h"

namespace winrt::WinUINotes::Views::implementation
{
struct NotePage : NotePageT<NotePage>
{
  private:
    winrt::Windows::Storage::StorageFolder storageFolder =
        winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
    std::optional<winrt::Windows::Storage::StorageFile> noteFile;
    winrt::hstring fileName = L"note.txt";

  public:
    NotePage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    winrt::Windows::Foundation::IAsyncAction NotePage_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
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
