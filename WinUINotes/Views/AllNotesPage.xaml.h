#pragma once

#include "Views/AllNotesPage.g.h"

namespace winrt::WinUINotes::Views::implementation
{
    struct AllNotesPage : AllNotesPageT<AllNotesPage>
    {
        AllNotesPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::WinUINotes::Views::factory_implementation
{
    struct AllNotesPage : AllNotesPageT<AllNotesPage, implementation::AllNotesPage>
    {
    };
}
