// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/AboutScreen.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    void AboutScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == M::tauIcon )
        {
            A::analytics->Log( "tau clicked" );
            this->Navigation_ShiftTo( "projectDetailsScreen", Tau::String( "Tau" ) );
        }
        else if( sprite == M::appIcon )
        {
            A::analytics->Log( "go to github" );
            Tau::SystemUtils::OpenWebBrowser( C::uiAboutGithubUrl.Get() );
        }
    }

}
