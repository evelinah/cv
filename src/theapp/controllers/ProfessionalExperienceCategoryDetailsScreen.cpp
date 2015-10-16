// rev: 89281ca, exported: 2015-10-16 23:24:12

#include "theapp/controllers/ProfessionalExperienceCategoryDetailsScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/base/Dictionary.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    void ProfessionalExperienceCategoryDetailsScreen::Navigation_Setup( const Tau::Any& data )
    {
        const SetupData& setupData = data.Cast< SetupData >();

        DataSource = setupData.dataSource;

        this->Navigation_SetTabsTexts( C::uiProfessionalExperienceNavigationTabs.Get() + '/' + A::professionalExperience->CategoriesMap.Get( setupData.categoryName )->DisplayName.Val() + '/' + DataSource->DisplayName.Val() );
        this->Navigation_SetAnalyticsName( setupData.categoryName + ", " + DataSource->Name );

        M::professionalExperienceCategoryDetailsIcon->SetImage( DataSource->Icon );
        M::professionalExperienceCategoryDetailsIcon->SetHeight( M::professionalExperienceCategoryDetailsIcon->GetComponent( Tau::Frame )->Height );
        M::professionalExperienceCategoryDetailsName->SetText( DataSource->DisplayName );
        M::professionalExperienceCategoryDetailsTimeFrame->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( DataSource->GetFirstUsed() + " - " + DataSource->GetLastUsed() );
        M::professionalExperienceCategoryDetailsProjects->SetText( Tau::Dictionary::Get()->GetText( "TEXT_PROJECTS_COUNT_COLON" ).Replace( DataSource->Projects.Size() ) );

        Projects.Clear();
        A::professionalExperience->Projects.Select( Projects, TAU_DELEGATE( bool, ProfessionalExperienceCategoryDetailsScreen, SelectProject, ProfessionalExperience::ProjectPtr ) );
        A::professionalExperience->SetProjectsModel( Projects, M::professionalExperienceCategoryDetailsList );
        ListView->GetComponent( Tau::ListViewScroller )->Reset();

        M::professionalExperienceCategoryDetailsFrame->SetWidth( M::professionalExperienceCategoryDetailsName->GetPosition().X + M::professionalExperienceCategoryDetailsName->GetWidth() - M::professionalExperienceCategoryDetailsIcon->GetPosition().X );
        M::professionalExperienceCategoryDetailsFrame->SetTouchable( DataSource->Url.Val().HasLength() );
    }

    static Tau::AbstractSprite* SubstituteFrame( Tau::AbstractSprite* sprite )
    {
        return sprite == M::professionalExperienceCategoryDetailsFrame ? M::professionalExperienceCategoryDetailsName : sprite;
    }

    void ProfessionalExperienceCategoryDetailsScreen::OnSelectSprite( Tau::AbstractSprite* sprite, const Tau::String& name, bool select )
    {
        sprite = SubstituteFrame( sprite );
        CVMenuScreen::OnSelectSprite( sprite, sprite->Owner->Name, select );
    }

    void ProfessionalExperienceCategoryDetailsScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == M::professionalExperienceCategoryDetailsFrame )
        {
            A::analytics->Log( "go to item url", DataSource->Name + ", " + DataSource->Url );
            Tau::SystemUtils::OpenWebBrowser( DataSource->Url );
        }
        else
        {
            const ProfessionalExperience::DataSource* dataSource = this->ListView_GetDataSource< ProfessionalExperience::DataSource >( sprite );

            if( dataSource )
            {
                this->Navigation_ShiftTo( "projectDetailsScreen", dataSource->Name.Val() );
            }
        }
    }

    bool ProfessionalExperienceCategoryDetailsScreen::SelectProject( ProfessionalExperience::ProjectPtr project )
    {
        return DataSource->Projects.Has( project->Name.Val() );
    }

}
