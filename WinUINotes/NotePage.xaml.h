#pragma once

#include "NotePage.g.h"

namespace winrt::WinUINotes::implementation
{
	struct NotePage : NotePageT<NotePage>
	{
	private:
		winrt::Windows::Storage::StorageFolder storageFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
		std::optional<winrt::Windows::Storage::StorageFile> noteFile;
		winrt::hstring fileName = L"note.txt";

	public:
		NotePage()
		{
			// Xaml objects should not call InitializeComponent during construction.
			// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
		}

		int32_t MyProperty();
		void MyProperty(int32_t value);

		winrt::Windows::Foundation::IAsyncAction NotePage_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		winrt::Windows::Foundation::IAsyncAction SaveButton_Click(const winrt::Windows::Foundation::IInspectable& sender, const winrt::Microsoft::UI::Xaml::RoutedEventArgs& e);
		winrt::Windows::Foundation::IAsyncAction DeleteButton_Click(const winrt::Windows::Foundation::IInspectable& sender, const winrt::Microsoft::UI::Xaml::RoutedEventArgs& e);
	};
}

namespace winrt::WinUINotes::factory_implementation
{
	struct NotePage : NotePageT<NotePage, implementation::NotePage>
	{};
}
