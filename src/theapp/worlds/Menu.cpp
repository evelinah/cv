// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/worlds/Menu.hpp"
#include "theapp/controllers/CVMenuScreen.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "core/base/Platform.hpp"
#include "core/graphics/AtlasSystem.hpp"

namespace TheApp
{

    void Menu::Deserialize( const Tau::Deserializer& d )
    {
        M::Init( this );
    }

    void Menu::Start()
    {
        CVMenuScreen::Init( "homeScreen" );
        M::fullscreenButton->Owner->SetActive( Tau::GetPlatform() == Tau::PLATFORM_WINDOWS );
        A::screenDimmer->StartBrighten( Tau::Color::BLACK, C::interpolationStartBrightenTime.Get(), C::interpolationStartBrightenType.Get() )->SetOnFinished( EventHandlerVoid( Menu, PreloadTextures, const Tau::Any& ) );
    }

    void Menu::PreloadTextures()
    {
        Tau::AtlasSystem::PreloadAllSurfaces();
    }

}
