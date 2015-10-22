// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/worlds/Menu.hpp"
#include "theapp/controllers/CVMenuScreen.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

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
        A::screenDimmer->StartBrighten( Tau::Color::BLACK, C::interpolationStartBrightenTime.Get(), C::interpolationStartBrightenType.Get() )->SetOnFinished( EventHandlerVoid( Menu, PreloadTextures, const Tau::Any& ) );
    }

    void Menu::PreloadTextures()
    {
        Tau::AtlasSystem::PreloadAllSurfaces();
    }

}
