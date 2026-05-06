#pragma once

#include "Models/Note.g.h"

namespace winrt::WinUINotes::Models::implementation
{
struct Note : NoteT<Note>
{
  private:
    winrt::Windows::Storage::StorageFolder storageFolder =
        winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
    winrt::hstring fileName;
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

    Note();
    winrt::Windows::Foundation::IAsyncAction SaveAsync();
    winrt::Windows::Foundation::IAsyncAction DeleteAsync();
};
} // namespace winrt::WinUINotes::Models::implementation

namespace winrt::WinUINotes::Models::factory_implementation
{
struct Note : NoteT<Note, implementation::Note>
{
};
} // namespace winrt::WinUINotes::Models::factory_implementation
