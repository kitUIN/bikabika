#pragma once
#include "CreaterBlock.g.h"
#include "TagBlock.h"

namespace winrt::bikabika::implementation
{
	struct CreaterBlock : CreaterBlockT<CreaterBlock>
	{
		CreaterBlock(winrt::Windows::Data::Json::JsonObject const& json);
		hstring ID();
		void ID(hstring const& value);
		hstring Gender();
		void Gender(hstring const& value);
		hstring Name();
		void Name(hstring const& value);
		hstring CharactersString();
		void CharactersString(hstring const& value);
		hstring Role();
		void Role(hstring const& value);
		hstring Title();
		void Title(hstring const& value);
		hstring Slogan();
		void Slogan(hstring const& value);
		hstring Character();
		void Character(hstring const& value);
		int32_t Exp();
		void Exp(int32_t value);
		int32_t Level();
		void Level(int32_t value);

		
		winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Thumb();
		void Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
		winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> Characters();
		void Characters(winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> const& value);
		
		bool Verified();
		void Verified(bool value);
		
		winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
		void PropertyChanged(winrt::event_token const& token) noexcept;
	private:
		hstring m_id;
		hstring m_gender;
		hstring m_name;
		int32_t m_exp;
		int32_t m_level;
		hstring m_role;
		winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_thumb;
		winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> m_characters= winrt::single_threaded_observable_vector<bikabika::TagBlock>();
		hstring m_charactersString;
		bool m_verified;
		hstring m_title;
		hstring m_slogan;
		hstring m_character;
		winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}
namespace winrt::bikabika::factory_implementation
{
	struct CreaterBlock : CreaterBlockT<CreaterBlock, implementation::CreaterBlock>
	{
	};
}
