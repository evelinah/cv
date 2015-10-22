// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/controllers/SdkIntegrationScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauWorldsCache.hpp"
#include "taugen/TauSettingsCache.hpp"

#include "extensions_platform/SystemUtils.hpp"

namespace TheApp
{

    void SdkIntegrationScreen::Start()
    {
        CVMenuScreen::Start();

        A::professionalExperience->SetSdkIntegrationsModel( A::professionalExperience->SdkIntegrations, M::sdkIntegrationList );
    }

    void SdkIntegrationScreen::OnShowStarted( const Tau::String& prevScreen )
    {
        CVMenuScreen::OnShowStarted( prevScreen );

        Sort( S::sdkIntegrationSortBy.Get(), true );
        M::sdkIntegrationRadioButtons->SelectSprite( this->FindComponent< Tau::Frame >( "sdkIntegrationSortBy" + S::sdkIntegrationSortBy.Get() + ".Frame" ), true );
    }

    static bool IsSortButton( Tau::AbstractSprite* sprite )
    {
        return sprite == M::sdkIntegrationSortByName || sprite == M::sdkIntegrationSortByDate || sprite == M::sdkIntegrationSortByPlatform;
    }

    void SdkIntegrationScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( IsSortButton( sprite ) )
        {
            Sort( Tau::StringUtils::ReplaceFirst( name, "sdkIntegrationSortBy", "" ), false );
        }
        else
        {
            const ProfessionalExperience::SdkIntegration* sdkIntegration = this->ListView_GetDataSource< ProfessionalExperience::SdkIntegration >( sprite );

            if( sdkIntegration )
            {
                A::analytics->Log( "go to sdk url", sdkIntegration->Name + ", " + sdkIntegration->Platform );
                Tau::SystemUtils::OpenWebBrowser( sdkIntegration->Url );
            }
        }
    }

    void SdkIntegrationScreen::Sort( const Tau::String by, bool init )
    {
        if( !init )
        {
            A::analytics->Log( "sort", "SdkIntegration by " + by );
            S::sdkIntegrationSortBy.Set( by );
        }

        if( by == "Name" )
        {
            this->ListView_Sort( TAU_DELEGATE( bool, SdkIntegrationScreen, CompareName, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
        }
        else if( by == "Date" )
        {
            this->ListView_Sort( TAU_DELEGATE( bool, SdkIntegrationScreen, CompareDate, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
        }
        else if( by == "Platform" )
        {
            this->ListView_Sort( TAU_DELEGATE( bool, SdkIntegrationScreen, ComparePlatform, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
        }
        else
        {
            TAU_ASSERT( false )
        }
    }

    static Tau::String GetNameText( Tau::Entity* cell )
    {
        return Tau::StringUtils::Uncapitalize( CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::SdkIntegration >( cell )->DisplayName );
    }

    static Tau::String GetDateText( Tau::Entity* cell )
    {
        return CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::SdkIntegration >( cell )->Date;
    }

    static Tau::String GetPlatformText( Tau::Entity* cell )
    {
        return Tau::StringUtils::Uncapitalize( CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::SdkIntegration >( cell )->Platform );
    }

    bool SdkIntegrationScreen::CompareName( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetNameText( info.element1 ) < GetNameText( info.element2 );
    }

    bool SdkIntegrationScreen::CompareDate( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetDateText( info.element1 ) > GetDateText( info.element2 );
    }

    bool SdkIntegrationScreen::ComparePlatform( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetPlatformText( info.element1 ) < GetPlatformText( info.element2 );
    }

}
