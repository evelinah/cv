// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/PersonalInformationScreen.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    void PersonalInformationScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite && sprite->Owner->Parent == M::personalInformationEmail )
        {
            A::analytics->Log( "send email" );
            TAU_ASSERT( sprite->Name == "TextSprite" )
            Tau::SystemUtils::OpenEmailClient( static_cast< Tau::TextSprite* >( sprite )->Text );
        }
    }

}
