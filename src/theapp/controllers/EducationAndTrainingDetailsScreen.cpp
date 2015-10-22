// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/controllers/EducationAndTrainingDetailsScreen.hpp"
#include "theapp/models/EducationAndTraining.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/Camera.hpp"
#include "components/graphics/Layouter.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    void EducationAndTrainingDetailsScreen::Deserialize( const Tau::Deserializer& d )
    {
        CVMenuScreen::Deserialize( d );

        Website = Tau::WeakPtr< Tau::TextSprite >( M::educationAndTrainingDetailsWebsite->GetChild( "value" )->GetComponent( Tau::TextSprite ) );
    }

    void EducationAndTrainingDetailsScreen::Navigation_Setup( const Tau::Any& data )
    {
        DataSource = data.Cast< const EducationAndTraining::DataSource* >();

        this->Navigation_SetTabsTexts( C::uiEducationAndTrainingNavigationTabs.Get() + '/' + DataSource->DisplayName.Val() );
        this->Navigation_SetAnalyticsName( DataSource->Name );

        M::educationAndTrainingDetailsIcon->SetImage( DataSource->Icon );
        M::educationAndTrainingDetailsIcon->SetHeight( M::educationAndTrainingDetailsIcon->GetComponent( Tau::Frame )->Height );
        M::educationAndTrainingDetailsName->SetWidth( Tau::Camera::Get()->ProjectionResolution - C::uiMargin10.Get() - M::educationAndTrainingDetailsName->GetPosition().X + Tau::Camera::Get()->ProjectionRect.Val().X, false );
        M::educationAndTrainingDetailsName->SetText( DataSource->DisplayName );
        M::educationAndTrainingDetailsInfo->SetText( DataSource->Info );
        M::educationAndTrainingDetailsInfoShift->GetTransform().SetY( ( 1 - M::educationAndTrainingDetailsInfo->Lines ) * M::educationAndTrainingDetailsInfo->GetLineHeight() );
        M::educationAndTrainingDetailsTimeFrame->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( DataSource->StartDate + " - " + DataSource->EndDate );

        Website->SetWidth( Tau::Camera::Get()->ProjectionResolution - C::uiMargin10.Get() - Website->GetPosition().X + Tau::Camera::Get()->ProjectionRect.Val().X, false );
        Website->SetEllipsis( true, false );
        Website->SetText( DataSource->DisplayUrl );
        Website->SetPivot( Website->GetTextWidth() / ( 2 * Website->Width ) );
        Website->GetComponent( Tau::Layouter )->Align();
        TAU_ASSERT( DataSource->Url.Val().HasLength() )
        Website->SetTouchable( true );

        M::educationAndTrainingDetailsLocation->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( DataSource->Location );

        M::educationAndTrainingDetailsFrame->SetWidth( M::educationAndTrainingDetailsName->GetPosition().X + M::educationAndTrainingDetailsName->GetWidth() - M::educationAndTrainingDetailsIcon->GetPosition().X );
    }

    void EducationAndTrainingDetailsScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == Website )
        {
            A::analytics->Log( "go to item url", DataSource->Name + ", " + DataSource->Url );
            Tau::SystemUtils::OpenWebBrowser( DataSource->Url );
        }
    }

}
