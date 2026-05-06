#include "pch.h"
#include "AllNotesPage.xaml.h"
#if __has_include("Views/AllNotesPage.g.cpp")
#include "Views/AllNotesPage.g.cpp"
#endif

using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUINotes::Views::implementation
{
void implementation::AllNotesPage::NewNoteButton_Click(const winrt::Windows::Foundation::IInspectable &sender,
                                                       const winrt::Microsoft::UI::Xaml::RoutedEventArgs &e)
{
    Frame().Navigate(winrt::xaml_typename<NotePage>());
}
} // namespace winrt::WinUINotes::Views::implementation
