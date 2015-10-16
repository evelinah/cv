// rev: 89281ca, exported: 2015-10-16 23:24:12

#include "theapp/models/CVDataSource.hpp"

#include "components/graphics/Frame.hpp"
#include "components/graphics/Layouter.hpp"
#include "components/graphics/Sprite.hpp"
#include "components/graphics/TextSprite.hpp"

namespace TheApp
{

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
