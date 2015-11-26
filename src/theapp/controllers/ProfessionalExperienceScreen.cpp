// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/ProfessionalExperienceScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/Camera.hpp"

namespace TheApp
{

    void ProfessionalExperienceScreen::Deserialize( const Tau::Deserializer& d )
    {
        CVMenuScreen::Deserialize( d );

        M::pageButtons->StateChangedEvent += EventHandler( ProfessionalExperienceScreen, OnRadioButtonStateChanged, const Tau::RadioButtonGroup::StateChangedInfo& );
    }

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

        if( sprite == M::pageButton1 )
        {
            Slide( false );
        }
        else if( sprite == M::pageButton2 )
        {
            Slide( true );
        }
        else if( sprite == M::employersButton )
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

    void ProfessionalExperienceScreen::Slide( bool forth )
    {
        Tau::Interpolator::Interpolate< Tau::RelaxedInterpolator >( this, forth ? Tau::Real::ZERO : -Tau::Camera::Get()->ProjectionRect.Val().Width, forth ? -Tau::Camera::Get()->ProjectionRect.Val().Width : Tau::Real::ZERO, C::interpolationSlideTime.Get(), C::interpolationSlideType.Get(), EventHandlerSetX( M::professionalExperiencePageSlideTransition ) );
    }

    void ProfessionalExperienceScreen::OnRadioButtonStateChanged( const Tau::RadioButtonGroup::StateChangedInfo& info )
    {
        Tau::Interpolator::Interpolate( this, info.active ? C::interpolationRadioButtonDisabledAlpha.Get() : 1, info.active ? 1 : C::interpolationRadioButtonDisabledAlpha.Get(), info.init ? 0 : C::interpolationRadioButtonTime.Get(), C::interpolationRadioButtonType.Get(), EventHandlerSetAlpha( info.sprite ) );
    }

}
