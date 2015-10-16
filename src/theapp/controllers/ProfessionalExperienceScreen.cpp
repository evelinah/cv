// rev: 89281ca, exported: 2015-10-16 23:24:12

#include "theapp/controllers/ProfessionalExperienceScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauWorldsCache.hpp"

namespace TheApp
{

    static Tau::String GetCategoryName( Tau::AbstractSprite* sprite )
    {
             if( sprite == M::programmingLanguagesButton ) { return ProfessionalExperience::Category::PROGRAMMING_LANGUAGES; }
        else if( sprite == M::platformsButton )            { return ProfessionalExperience::Category::PLATFORMS; }
        else if( sprite == M::middlewareButton )           { return ProfessionalExperience::Category::MIDDLEWARE; }
        else if( sprite == M::deviceClassesButton )        { return ProfessionalExperience::Category::DEVICE_CLASSES; }
        else if( sprite == M::openSourceLibrariesButton )  { return ProfessionalExperience::Category::OPEN_SOURCE_LIBRARIES; }
        else if( sprite == M::appStoresButton )            { return ProfessionalExperience::Category::APP_STORES; }
        else if( sprite == M::uiTechnologiesButton )       { return ProfessionalExperience::Category::UI_TECHNOLOGIES; }
        else if( sprite == M::mediaTchnologiesButton )     { return ProfessionalExperience::Category::MEDIA_TECHNOLOGIES; }
        else if( sprite == M::webTechnologiesButton )      { return ProfessionalExperience::Category::WEB_TECHNOLOGIES; }
        else if( sprite == M::ideButton )                  { return ProfessionalExperience::Category::IDE; }
        else if( sprite == M::vcsButton )                  { return ProfessionalExperience::Category::VCS; }
        else if( sprite == M::unitAndUITesting )           { return ProfessionalExperience::Category::UNIT_AND_UI_TESTING; }
        else if( sprite == M::dbmsButton )                 { return ProfessionalExperience::Category::DBMS; }
        else if( sprite == M::dataExchangeFormatsButton )  { return ProfessionalExperience::Category::DATA_EXCHANGE_FORMATS; }
        else if( sprite == M::locationsButton )            { return ProfessionalExperience::Category::LOCATIONS; }
        else if( sprite == M::methodologiesButton )        { return ProfessionalExperience::Category::METHODOLOGIES; }
        else if( sprite == M::developmentTeamSizeButton )  { return ProfessionalExperience::Category::DEVELOPMENT_TEAM_SIZE; }
        else if( sprite == M::rolesButton )                { return ProfessionalExperience::Category::ROLES; }
        else
        {
            return Tau::String::EMPTY;
        }
    }

    void ProfessionalExperienceScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == M::employersButton )
        {
            this->Navigation_ShiftTo( "employersScreen" );
        }
        else if( sprite ==  M::projectsButton )
        {
            this->Navigation_ShiftTo( "projectsScreen" );
        }
        else if( sprite ==  M::sdkIntegrationButton )
        {
            this->Navigation_ShiftTo( "sdkIntegrationScreen" );
        }
        else
        {
            Tau::String categoryName = GetCategoryName( sprite );

            if( categoryName.HasLength() )
            {
                this->Navigation_ShiftTo( "professionalExperienceCategoryScreen", categoryName );
            }
        }
    }

}
