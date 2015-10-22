// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/models/CVDataSource.hpp"

#include "components/graphics/Frame.hpp"
#include "components/graphics/Layouter.hpp"
#include "components/graphics/Sprite.hpp"
#include "components/graphics/TextSprite.hpp"

namespace TheApp
{

    Tau::String CVDataSource::GetDisplayUrl( const Tau::String& url )
    {
        return !url.HasLength() ? (Tau::String)Tau::Dictionary::Get()->GetText( "TEXT_NONE" ) : Tau::StringUtils::Has( url, "wikipedia" ) ? (Tau::String)Tau::Dictionary::Get()->GetText( "TEXT_WIKIPEDIA_PAGE" ) : url;
    }

    void CVDataSource::ValidateTimeFrame( const Tau::String& startDate, const Tau::String& endDate )
    {
        TAU_ASSERT( endDate == "now" || endDate == '-' || endDate >= startDate );
    }

    // ---------------- //

    void CVModels::SetBasicCell( Tau::Entity* cell, const CVDataSource* dataSource )
    {
        Tau::TextSprite* name = cell->GetChild( "name" )->GetComponent( Tau::TextSprite );
        name->SetText( dataSource->DisplayName );

        if( dataSource->Icon.Val().HasLength() )
        {
            Tau::Sprite* icon = cell->GetChild( "icon" )->GetComponent( Tau::Sprite );
            icon->SetImage( dataSource->Icon );
            icon->SetHeight( icon->GetComponent( Tau::Frame )->Height );
            icon->GetComponent( Tau::Layouter )->Align();
        }
    }

}
