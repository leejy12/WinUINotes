#pragma once

#include "Models/NoteModel.g.h"

namespace winrt::WinUINotes::Models::implementation
{
struct NoteModel : NoteModelT<NoteModel>
{
  private:
    winrt::hstring fileName;
    winrt::hstring title;
    winrt::hstring text;
    winrt::Windows::Foundation::DateTime date;

  public:
    winrt::hstring FileName()
    {
        return fileName;
    }

    void FileName(const winrt::hstring &_fileName)
    {
        fileName = _fileName;
    }

    winrt::hstring Title()
    {
        return title;
    }

    void Title(const winrt::hstring &_title)
    {
        title = _title;
    }

    winrt::hstring Text()
    {
        return text;
    }

    void Text(const winrt::hstring &_text)
    {
        text = _text;
    }

    winrt::Windows::Foundation::DateTime Date()
    {
        return date;
    }

    void Date(const winrt::Windows::Foundation::DateTime &_date)
    {
        date = _date; 
    }

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
