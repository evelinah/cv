// rev: 89281ca, exported: 2015-10-16 23:24:12

#include "theapp/controllers/HomeScreen.hpp"
#include "taugen/TauWorldsCache.hpp"

namespace TheApp
{

    static bool IsSectionButton( Tau::AbstractSprite* sprite )
    {
        return sprite == M::personalInformationButton || sprite == M::educationAndTrainingButton ||
               sprite == M::professionalExperienceButton || sprite == M::skillsAndInterestsButton;
    }

    void HomeScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == M::aboutButton )
        {
            this->Navigation_ShiftTo( "aboutScreen" );
        }
        else if( IsSectionButton( sprite ) )
        {
            this->Navigation_ShiftTo( Tau::StringUtils::ReplaceFirst( name, "Button", "Screen" ) );
        }
    }

    void HomeScreen::OnTransition( Tau::Real t )
    {
        M::aboutButton->SetAlpha( t );
    }

}