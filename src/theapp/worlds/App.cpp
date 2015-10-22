// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/worlds/App.hpp"
#include "taugen/TauWorldsCache.hpp"
#include "taugen/TauSettingsCache.hpp"

#include "components/graphics/Camera.hpp"

#include "core/application/System.hpp"
#include "core/graphics/Screen.hpp"

namespace TheApp
{

    void App::Deserialize( const Tau::Deserializer& d )
    {
        A::Init( this );
        C::Init( this );
        S::Init( this );

        Tau::Camera::Get()->SetProjectionResolution( Tau::Camera::Get()->Canvas.Val().X * ( 16.0f / 9 ) * Tau::Screen::GetAspectRatio( false ) );

        Tau::System::AddWorldGlobal( "appWidth", Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution ) );
        Tau::System::AddWorldGlobal( "textWidth10", Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution - 2 * C::uiMargin10.Get() ) );
        Tau::System::AddWorldGlobal( "textWidth12", Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution - 2 * C::uiMargin12.Get() ) );
        Tau::System::AddWorldGlobal( "listGradientSize", Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution ) + " " + C::uiListGradientHeight.Get() );
        Tau::System::AddWorldGlobal( "genericCategoryCellNameWidth", Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution - Tau::StringUtils::To< Tau::Point2D >( C::uiBasicCellNamePadding.Get() ).X - C::uiProjectsLabelSectionWidth.Get() ) );
    }

    void App::Start()
    {
        Tau::Camera::Get()->ResetPosition();
    }

}
