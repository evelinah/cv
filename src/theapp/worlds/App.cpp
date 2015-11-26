// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

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

        Tau::Real aspectRatio = Tau::Screen::GetAspectRatio( false );
        Tau::Real appWidth = Tau::Camera::Get()->Canvas.Val().Y * aspectRatio;
        Tau::Real contentWidth = Math::Min< Tau::Real >( appWidth, C::uiMaxContentWidth.Get() );
        Tau::Real contentShift = ( Tau::Camera::Get()->Canvas.Val().X - contentWidth ) * 0.5;

        if( aspectRatio < 1 )
        {
            Tau::Camera::Get()->SetProjectionResolution( appWidth );
        }

        Tau::System::AddWorldGlobal( "appWidth", Tau::StringUtils::String( appWidth ) );
        Tau::System::AddWorldGlobal( "contentWidth", Tau::StringUtils::String( contentWidth ) );
        Tau::System::AddWorldGlobal( "textWidth10", Tau::StringUtils::String( contentWidth - 2 * C::uiMargin10.Get() ) );
        Tau::System::AddWorldGlobal( "textWidth12", Tau::StringUtils::String( contentWidth - 2 * C::uiMargin12.Get() ) );
        Tau::System::AddWorldGlobal( "listGradientSize", Tau::StringUtils::String( contentWidth ) + " " + C::uiListGradientHeight.Get() );
        Tau::System::AddWorldGlobal( "genericCategoryCellNameWidth", Tau::StringUtils::String( contentWidth - Tau::StringUtils::To< Tau::Point2D >( C::uiBasicCellNamePadding.Get() ).X - C::uiProjectsLabelSectionWidth.Get() ) );
        Tau::System::AddWorldGlobal( "professionalExperiencePagePadding", Tau::StringUtils::String( appWidth ) + " 0" );
        Tau::System::AddWorldGlobal( "aboutButtonPadding", Tau::StringUtils::String( -contentShift ) + " 36" );
        Tau::System::AddWorldGlobal( "footerTextPadding", Tau::StringUtils::String( -contentShift ) + " 12" );
    }

    void App::Start()
    {
        Tau::Camera::Get()->ResetPosition();
    }

}
