// rev: 89281ca, exported: 2015-10-16 23:24:12

#include "theapp/controllers/EducationAndTrainingDetailsScreen.hpp"
#include "theapp/models/EducationAndTraining.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/Camera.hpp"
#include "components/graphics/Layouter.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    void EducationAndTrainingDetailsScreen::Navigation_Setup( const Tau::Any& data )
    {
        DataSource = data.Cast< const EducationAndTraining::DataSource* >();

        this->Navigation_SetTabsTexts( C::uiEducationAndTrainingNavigationTabs.Get() + '/' + DataSource->DisplayName.Val() );
        this->Navigation_SetAnalyticsName( DataSource->Name );

        M::educationAndTrainingDetailsIcon->SetImage( DataSource->Icon );
        M::educationAndTrainingDetailsIcon->SetHeight( M::educationAndTrainingDetailsIcon->GetComponent( Tau::Frame )->Height );
        M::educationAndTrainingDetailsName->SetText( DataSource->DisplayName );
        M::educationAndTrainingDetailsName->SetWidth( Tau::Camera::Get()->ProjectionResolution - C::uiMargin10.Get() - M::educationAndTrainingDetailsName->GetPosition().X + Tau::Camera::Get()->ProjectionRect.Val().X );
        M::educationAndTrainingDetailsName->SetPivot( M::educationAndTrainingDetailsName->GetTextWidth() / ( 2 * M::educationAndTrainingDetailsName->Width ) );
        M::educationAndTrainingDetailsName->GetComponent( Tau::Layouter )->Align();
        M::educationAndTrainingDetailsInfo->SetText( DataSource->Info );
        M::educationAndTrainingDetailsInfoShift->GetTransform().SetY( ( 1 - M::educationAndTrainingDetailsInfo->Lines ) * M::educationAndTrainingDetailsInfo->GetLineHeight() );
        M::educationAndTrainingDetailsTimeFrame->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( DataSource->StartDate + " - " + DataSource->EndDate );
        M::educationAndTrainingDetailsLocation->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( DataSource->Location );

        M::educationAndTrainingDetailsFrame->SetWidth( M::educationAndTrainingDetailsName->GetPosition().X + M::educationAndTrainingDetailsName->GetWidth() - M::educationAndTrainingDetailsIcon->GetPosition().X );
        M::educationAndTrainingDetailsFrame->SetTouchable( DataSource->Url.Val().HasLength() );
    }

    static Tau::AbstractSprite* SubstituteFrame( Tau::AbstractSprite* sprite )
    {
        return sprite == M::educationAndTrainingDetailsFrame ? M::educationAndTrainingDetailsName : sprite;
    }

    void EducationAndTrainingDetailsScreen::OnSelectSprite( Tau::AbstractSprite* sprite, const Tau::String& name, bool select )
    {
        sprite = SubstituteFrame( sprite );
        CVMenuScreen::OnSelectSprite( sprite, sprite->Owner->Name, select );
    }

    void EducationAndTrainingDetailsScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( sprite == M::educationAndTrainingDetailsFrame )
        {
            A::analytics->Log( "go to item url", DataSource->Name + ", " + DataSource->Url );
            Tau::SystemUtils::OpenWebBrowser( DataSource->Url );
        }
    }

}
