// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/controllers/SkillsAndInterestsScreen.hpp"
#include "theapp/models/SkillsAndInterests.hpp"
#include "taugen/TauWorldsCache.hpp"

namespace TheApp
{

    static Tau::String GetCategoryName( Tau::AbstractSprite* sprite )
    {
             if( sprite == M::traitsButton )    { return SkillsAndInterestsModels::Category::TRAITS; }
        else if( sprite == M::languagesButton ) { return SkillsAndInterestsModels::Category::LANGUAGES; }
        else if( sprite == M::interestsButton ) { return SkillsAndInterestsModels::Category::INTERESTS; }
        {
            return Tau::String::EMPTY;
        }
    }

    void SkillsAndInterestsScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == M::philosophyButton )
        {
            this->Navigation_ShiftTo( "philosophyScreen" );
        }
        else
        {
            Tau::String categoryName = GetCategoryName( sprite );

            if( categoryName.HasLength() )
            {
                this->Navigation_ShiftTo( "skillsAndInterestsCategoryScreen", categoryName );
            }
        }
    }

}
