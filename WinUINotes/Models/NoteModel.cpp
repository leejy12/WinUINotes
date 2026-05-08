#include "pch.h"
#include "NoteModel.h"
#if __has_include("Models/NoteModel.g.cpp")
#include "Models/NoteModel.g.cpp"
#endif

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Globalization::DateTimeFormatting;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt::WinUINotes::Models::implementation
{
NoteModel::NoteModel()
{
    if (fileName.empty())
    {
        date = winrt::clock::now();
    }
}

winrt::hstring NoteModel::DateText() const
{
    const DateTimeFormatter formatter(L"shortdate shorttime");
    return formatter.Format(date);
}
} // namespace winrt::WinUINotes::Models::implementation
