// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/ProfessionalExperienceCategoryDetailsScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/Camera.hpp"
#include "components/graphics/Layouter.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    void ProfessionalExperienceCategoryDetailsScreen::Deserialize( const Tau::Deserializer& d )
    {
        CVMenuScreen::Deserialize( d );

        Website = Tau::WeakPtr< Tau::TextSprite >( M::professionalExperienceCategoryDetailsWebsite->GetChild( "value" )->GetComponent( Tau::TextSprite ) );
    }

    void ProfessionalExperienceCategoryDetailsScreen::Navigation_Setup( const Tau::Any& data )
    {
        const SetupData& setupData = data.Cast< SetupData >();

        DataSource = setupData.dataSource;

        this->Navigation_SetTabsTexts( C::uiProfessionalExperienceNavigationTabs.Get() + '/' + A::professionalExperience->CategoriesMap.Get( setupData.categoryName )->DisplayName.Val() + '/' + DataSource->DisplayName.Val() );
        this->Navigation_SetAnalyticsName( setupData.categoryName + ", " + DataSource->Name );

        M::professionalExperienceCategoryDetailsIcon->SetImage( DataSource->Icon );
        M::professionalExperienceCategoryDetailsName->SetText( DataSource->DisplayName );
        M::professionalExperienceCategoryDetailsTimeFrame->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( DataSource->GetFirstUsed() + " - " + DataSource->GetLastUsed() );

        Website->SetWidth( Tau::Camera::Get()->ProjectionRect.Val().Width - C::uiMargin10.Get() - Website->GetPosition().X + Tau::Camera::Get()->ProjectionRect.Val().X, false );
        Website->SetEllipsis( true, false );
        Website->SetText( DataSource->DisplayUrl );
        Website->SetPivot( Tau::Vector2D( Website->GetTextWidth() / ( 2 * Website->Width ), 0.5 ) );
        Website->GetComponent( Tau::Layouter )->Align();
        Website->SetTouchable( DataSource->Url.Val().HasLength() );

        M::professionalExperienceCategoryDetailsProjects->SetText( Tau::Dictionary::Get()->GetText( "TEXT_PROJECTS_COUNT_COLON" ).Replace( DataSource->Projects.Size() ) );

        Projects.Clear();
        A::professionalExperience->Projects.Select( Projects, TAU_DELEGATE( bool, ProfessionalExperienceCategoryDetailsScreen, SelectProject, ProfessionalExperience::ProjectPtr ) );
        A::professionalExperience->SetProjectsModel( Projects, M::professionalExperienceCategoryDetailsList );
        ListView->GetComponent( Tau::ListViewScroller )->Reset();
    }

    void ProfessionalExperienceCategoryDetailsScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == Website )
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
