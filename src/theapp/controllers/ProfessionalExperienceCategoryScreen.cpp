// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/ProfessionalExperienceCategoryScreen.hpp"
#include "theapp/controllers/ProfessionalExperienceCategoryDetailsScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/TextSprite.hpp"

namespace TheApp
{

    void ProfessionalExperienceCategoryScreen::Navigation_Setup( const Tau::Any& data )
    {
        CategoryName = data.Cast< Tau::String >();

        this->Navigation_SetTabsTexts( C::uiProfessionalExperienceNavigationTabs.Get() + '/' + A::professionalExperience->CategoriesMap.Get( CategoryName )->DisplayName );
        this->Navigation_SetAnalyticsName( CategoryName );

        A::professionalExperience->SetCategoryModel( CategoryName, M::professionalExperienceCategoryList );
        ListView->GetComponent( Tau::ListViewScroller )->Reset();

        Sort( S::categorySortBy.Get(), true );
        M::professionalExperienceCategoryRadioButtons->SelectSprite( this->FindComponent< Tau::Frame >( "professionalExperienceCategorySortBy" + S::categorySortBy.Get() + ".Frame" ), true );
    }

    static bool IsSortButton( Tau::AbstractSprite* sprite )
    {
        return sprite == M::professionalExperienceCategorySortByName || sprite == M::professionalExperienceCategorySortByFirstUsed ||
               sprite == M::professionalExperienceCategorySortByLastUsed || sprite == M::professionalExperienceCategorySortByProjects;
    }

    void ProfessionalExperienceCategoryScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( IsSortButton( sprite ) )
        {
            Sort( Tau::StringUtils::ReplaceFirst( name, "professionalExperienceCategorySortBy", "" ), false );
        }
        else
        {
            const ProfessionalExperience::DataSourceProjects* dataSource = this->ListView_GetDataSource< ProfessionalExperience::DataSourceProjects >( sprite );

            if( dataSource )
            {
                this->Navigation_ShiftTo( "professionalExperienceCategoryDetailsScreen", ProfessionalExperienceCategoryDetailsScreen::SetupData( CategoryName, dataSource ) );
            }
        }
    }

    void ProfessionalExperienceCategoryScreen::Sort( const Tau::String by, bool init )
    {
        if( !init )
        {
            A::analytics->Log( "sort", CategoryName + " by " + by );
            S::categorySortBy.Set( by );
        }

        if( by == "Name" )
        {
            this->ListView_Sort( TAU_DELEGATE( bool, ProfessionalExperienceCategoryScreen, CompareName, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
        }
        else if( by == "FirstUsed" )
        {
            this->ListView_Sort( TAU_DELEGATE( bool, ProfessionalExperienceCategoryScreen, CompareFirstUsed, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
        }
        else if( by == "LastUsed" )
        {
            this->ListView_Sort( TAU_DELEGATE( bool, ProfessionalExperienceCategoryScreen, CompareLastUsed, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
        }
        else if( by == "Projects" )
        {
            this->ListView_Sort( TAU_DELEGATE( bool, ProfessionalExperienceCategoryScreen, CompareProjects, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
        }
        else
        {
            TAU_ASSERT( false )
        }
    }

    static Tau::String GetNameText( Tau::Entity* cell )
    {
        return Tau::StringUtils::Uncapitalize( CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::DataSourceProjects >( cell )->DisplayName );
    }

    static Tau::String GetFirstUsedText( Tau::Entity* cell )
    {
        return cell->GetChild( "firstUsed" )->GetChild( "text" )->GetComponent( Tau::TextSprite )->Text;
    }

    static Tau::String GetLastUsedText( Tau::Entity* cell )
    {
        return cell->GetChild( "lastUsed" )->GetChild( "text" )->GetComponent( Tau::TextSprite )->Text;
    }

    static int GetProjectsCount( Tau::Entity* cell )
    {
        return CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::DataSourceProjects >( cell )->Projects.Size();
    }

    bool ProfessionalExperienceCategoryScreen::CompareName( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetNameText( info.element1 ) < GetNameText( info.element2 );
    }

    bool ProfessionalExperienceCategoryScreen::CompareFirstUsed( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetFirstUsedText( info.element1 ) < GetFirstUsedText( info.element2 );
    }

    bool ProfessionalExperienceCategoryScreen::CompareLastUsed( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetLastUsedText( info.element1 ) > GetLastUsedText( info.element2 );
    }

    bool ProfessionalExperienceCategoryScreen::CompareProjects( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetProjectsCount( info.element1 ) > GetProjectsCount( info.element2 );
    }

}
