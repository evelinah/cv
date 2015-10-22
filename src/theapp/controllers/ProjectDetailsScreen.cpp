// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/controllers/ProjectDetailsScreen.hpp"
#include "theapp/controllers/ProfessionalExperienceCategoryDetailsScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/base/Dictionary.hpp"
#include "components/graphics/Layouter.hpp"
#include "components/graphics/Frame.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    static Tau::String GetAppStoreIcon( const Tau::Vector< ProfessionalExperience::Project::Link >& links, int i )
    {
        return A::professionalExperience->AppStoresMap.Get( links[i].store )->Icon;
    }

    template< class T >
    static Tau::String GetIconFromModel( const Tau::Vector< T >& items, int i )
    {
        return items[i]->Icon;
    }

    static Tau::String Translate( ProfessionalExperience::ProjectStatus projectStatus )
    {
        switch( projectStatus )
        {
            case ProfessionalExperience::PROJECT_STATUS_LIVE: return "TEXT_EMPTY";
            case ProfessionalExperience::PROJECT_STATUS_UNAVAILABLE: return "TEXT_UNAVAILABLE";
            case ProfessionalExperience::PROJECT_STATUS_INTERNAL: return "TEXT_INTERNAL_PROJECT";
            case ProfessionalExperience::PROJECT_STATUS_CANCELLED: return "TEXT_CANCELLED";
            case ProfessionalExperience::PROJECT_STATUS_DEMO: return "TEXT_DEMO";

            default:
                TAU_ASSERT( false )
                return "TEXT_EMPTY";
        }
    }

    static Tau::Entity* GetNoneText( Tau::Entity* container )
    {
        return container->GetChild( "icons" )->GetChild( "noneText" );
    }

    void ProjectDetailsScreen::Navigation_Setup( const Tau::Any& data )
    {
        const Tau::String& projectName = data.Cast< Tau::String >();

        Project_ = A::professionalExperience->ProjectsMap.Get( projectName );

        this->Navigation_SetTabsTexts( C::uiProjectsNavigationTabs.Get() + '/' + Project_->DisplayName.Val() );
        this->Navigation_SetAnalyticsName( projectName );

        M::projectDetailsIcon->SetImage( Project_->Icon );
        M::projectDetailsIcon->SetHeight( M::projectDetailsIcon->GetComponent( Tau::Frame )->Height );
        M::projectDetailsName->SetText( Project_->DisplayName );
        M::projectDetailsDescription->SetText( Project_->Description );
        M::projectDetailsDescriptionShift->GetTransform().SetY( ( 1 - M::projectDetailsDescription->Lines ) * M::projectDetailsDescription->GetLineHeight() );
        M::projectDetailsTimeFrame->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( Project_->StartDate + " - " + Project_->EndDate );
        M::projectDetailsPublisher->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( Project_->Publisher );

        Platforms = A::professionalExperience->Filter( A::professionalExperience->Platforms, projectName );
        DeviceClasses = A::professionalExperience->Filter( A::professionalExperience->DeviceClasses, projectName );
        Middlewares = A::professionalExperience->Filter( A::professionalExperience->Middlewares, projectName );
        ProgrammingLanguages = A::professionalExperience->Filter( A::professionalExperience->ProgrammingLanguages, projectName );

        SetIcons( Project_->Links, GetAppStoreIcon, M::projectDetailsAppStores );
        SetIcons( Platforms, GetIconFromModel< ProfessionalExperience::PlatformPtr >, M::projectDetailsPlatforms );
        SetIcons( Middlewares, GetIconFromModel< ProfessionalExperience::MiddlewarePtr >, M::projectDetailsMiddleware );
        SetIcons( ProgrammingLanguages, GetIconFromModel< ProfessionalExperience::ProgrammingLanguagePtr >, M::projectDetailsLanguages );
        SetIcons( DeviceClasses, GetIconFromModel< ProfessionalExperience::DeviceClassPtr >, M::projectDetailsDeviceClasses );

        GetNoneText( M::projectDetailsAppStores )->GetComponent( Tau::TextSprite )->SetText( Translate( Project_->Status ) );
    }

    static int GetIconIndex( const Tau::String& name )
    {
        return Tau::StringUtils::To< int >( Tau::StringUtils::GetAfter( name, "icon", false ) ) - 1;
    }

    void ProjectDetailsScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( Tau::StringUtils::StartsWith( name, "icon" ) )
        {
            Tau::Entity* e = sprite->Owner->Parent->Parent;

            if( e == M::projectDetailsAppStores )
            {
                A::analytics->Log( "go to project app store", Project_->Links[ GetIconIndex( name ) ].url );
                Tau::SystemUtils::OpenWebBrowser( Project_->Links[ GetIconIndex( name ) ].url );
            }
            else if( e == M::projectDetailsPlatforms )
            {
                A::analytics->Log( "go to project platfrom", Project_->Name + ", " + Platforms[ GetIconIndex( name ) ]->Name );
                this->Navigation_ShiftTo( "professionalExperienceCategoryDetailsScreen", ProfessionalExperienceCategoryDetailsScreen::SetupData( ProfessionalExperience::Category::PLATFORMS, Platforms[ GetIconIndex( name ) ] ) );
            }
            else if( e == M::projectDetailsDeviceClasses )
            {
                A::analytics->Log( "go to project device class", Project_->Name + ", " + DeviceClasses[ GetIconIndex( name ) ]->Name );
                this->Navigation_ShiftTo( "professionalExperienceCategoryDetailsScreen", ProfessionalExperienceCategoryDetailsScreen::SetupData( ProfessionalExperience::Category::DEVICE_CLASSES, DeviceClasses[ GetIconIndex( name ) ] ) );
            }
            else if( e == M::projectDetailsMiddleware )
            {
                A::analytics->Log( "go to project middleware", Project_->Name + ", " + Middlewares[ GetIconIndex( name ) ]->Name );
                this->Navigation_ShiftTo( "professionalExperienceCategoryDetailsScreen", ProfessionalExperienceCategoryDetailsScreen::SetupData( ProfessionalExperience::Category::MIDDLEWARE, Middlewares[ GetIconIndex( name ) ] ) );
            }
            else if( e == M::projectDetailsLanguages )
            {
                A::analytics->Log( "go to project language", Project_->Name + ", " + ProgrammingLanguages[ GetIconIndex( name ) ]->Name );
                this->Navigation_ShiftTo( "professionalExperienceCategoryDetailsScreen", ProfessionalExperienceCategoryDetailsScreen::SetupData( ProfessionalExperience::Category::PROGRAMMING_LANGUAGES, ProgrammingLanguages[ GetIconIndex( name ) ] ) );
            }
        }
    }

    static Tau::Sprite* GetIcon( Tau::Entity* container, int i )
    {
        return container->GetChild( "icons" )->GetChild( "icon" + Tau::StringUtils::String( i ) )->GetComponent( Tau::Sprite );
    }

    template< class T >
    void ProjectDetailsScreen::SetIcons( const Tau::Vector< T >& items, Tau::String (*extractIcon)( const Tau::Vector< T >&, int ), Tau::Entity* container )
    {
        static const Tau::Real HEIGHT = Tau::StringUtils::To< Tau::Real >( C::uiProjectDetailsIconHeight.Get() );
        static const Tau::Real MAX_WIDTH = HEIGHT * C::uiProjectDetailsIconMaxWidthFactor.Get();

        Tau::Real shift = 0;

        for( int i = 0; i < items.Size(); i++ )
        {
            Tau::Sprite* icon = GetIcon( container, i + 1 );
            icon->SetVisible( true );
            icon->SetImage( extractIcon( items, i ) );
            icon->SetHeight( HEIGHT );
            if( icon->GetWidth() > MAX_WIDTH ) { icon->SetWidth( MAX_WIDTH ); }

            icon->GetComponent( Tau::Layouter )->SetPaddingX( shift );
            icon->GetComponent( Tau::Layouter )->Align();

            shift += icon->GetWidth() + C::uiProjectDetailsIconPadding.Get();
        }

        for( int i = items.Size() + 1; i <= C::uiProjectDetailsIconCount.Get(); i++ )
        {
            Tau::Sprite* icon = GetIcon( container, i );
            icon->SetVisible( false );
            icon->SetImage( "images/menu/empty.png" );
        }

        GetNoneText( container )->SetActive( items.IsEmpty() );
    }

}
