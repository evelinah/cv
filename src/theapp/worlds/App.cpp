// rev: 89281ca, exported: 2015-10-16 23:24:12

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

        Tau::String appWidth = Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution );
        Tau::System::AddWorldGlobal( "appWidth", appWidth );
        Tau::System::AddWorldGlobal( "textWidth10", Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution - 2 * C::uiMargin10.Get() ) );
        Tau::System::AddWorldGlobal( "textWidth12", Tau::StringUtils::String( Tau::Camera::Get()->ProjectionResolution - 2 * C::uiMargin12.Get() ) );
        Tau::System::AddWorldGlobal( "listGradientSize", appWidth + " " + C::uiListGradientHeight.Get() );
    }

    void App::Start()
    {
        Tau::Camera::Get()->ResetPosition();
    }

}
