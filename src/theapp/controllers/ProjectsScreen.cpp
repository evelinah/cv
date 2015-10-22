// rev: 524a6b2, exported: 2015-10-22 11:19:28

#include "theapp/controllers/ProjectsScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauWorldsCache.hpp"
#include "taugen/TauSettingsCache.hpp"

namespace TheApp
{

    void ProjectsScreen::Start()
    {
        CVMenuScreen::Start();

        A::professionalExperience->SetProjectsModel( A::professionalExperience->Projects, M::projectsList );

        GroupLabelShifts.Add( 0, 0 );
        PublisherLabelShifts.Add( 0, 0 );

        for( Tau::Vector< ProfessionalExperience::ProjectPtr >::const_iterator it = A::professionalExperience->Projects.begin(); it != A::professionalExperience->Projects.end(); it++ )
        {
            GroupLabelShifts.Add( (*it)->GroupIndex + 1, 0, true )++;
            PublisherLabelShifts.Add( (*it)->PublisherIndex + 1, 0, true )++;
        }

        for( int i = 1; i < A::professionalExperience->ProjectGroups.Size(); i++ )
        {
            GroupLabelShifts.Get( i ) += GroupLabelShifts.Get( i - 1 );
        }

        for( int i = 1; i < A::professionalExperience->Publishers.Size(); i++ )
        {
            PublisherLabelShifts.Get( i ) += PublisherLabelShifts.Get( i - 1 );
        }

        BasicCellHeight = Tau::StringUtils::To< Tau::Real >( C::uiBasicCellHeight.Get() );
        LabelHeight = Tau::StringUtils::To< Tau::Real >( C::uiProjectsLabelHeight.Get() );
        HeightDiff = LabelHeight - BasicCellHeight;
    }

    void ProjectsScreen::OnShowStarted( const Tau::String& prevScreen )
    {
        CVMenuScreen::OnShowStarted( prevScreen );

        Sort( S::projectsSortBy.Get(), true );
        M::projectsRadioButtons->SelectSprite( this->FindComponent< Tau::Frame >( "projectsSortBy" + S::projectsSortBy.Get() + ".Frame" ), true );
    }

    static bool IsSortButton( Tau::AbstractSprite* sprite )
    {
        return sprite == M::projectsSortByDate || sprite == M::projectsSortByName || sprite == M::projectsSortByPublisher;
    }

    void ProjectsScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        if( IsSortButton( sprite ) )
        {
            Sort( Tau::StringUtils::ReplaceFirst( name, "projectsSortBy", "" ), false );
        }
        else
        {
            const ProfessionalExperience::DataSource* dataSource = this->ListView_GetDataSource< ProfessionalExperience::DataSource >( sprite );

            if( dataSource )
            {
                this->Navigation_ShiftTo( "projectDetailsScreen", dataSource->Name.Val() );
            }
        }
    }

    void TerminateLabel( const Tau::Any& label )
    {
        label.Cast< Tau::Entity* >()->Terminate();
    }

    static Tau::String GetTextFromGroup( const Tau::Vector< Tau::String >& groups, int i )
    {
        return groups[i];
    }

    static Tau::String GetTextFromPublisher( const Tau::Vector< ProfessionalExperience::PublisherPtr >& publishers, int i )
    {
        return publishers[i]->DisplayName;
    }

    void ProjectsScreen::Sort( const Tau::String by, bool init )
    {
        if( !init )
        {
            A::analytics->Log( "sort", "Projects by " + by );
            S::projectsSortBy.Set( by );
        }

        for( Tau::Vector< Tau::Entity* >::const_iterator it = SortLabels.begin(); it != SortLabels.end(); it++ )
        {
            Tau::Interpolator::Interpolate( this, (*it)->GetTransform().GetX(), (*it)->GetTransform().GetX() - (*it)->GetComponent( Tau::Frame )->Width * C::interpolationSortSlideInFactor.Get(), init ? 0 : C::interpolationSortTime.Get(), C::interpolationSortType.Get(), EventHandlerSetX( *it ), TAU_COMPLETION_HANDLER_STATIC( TerminateLabel, Tau::Any, *it ) );
        }

        SortLabels.Clear();

        if( by == "Date" )
        {
            SortBy_ = SORT_BY_DATE;
            this->ListView_Sort( TAU_DELEGATE( bool, ProjectsScreen, CompareDate, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
            HandleLabels( A::professionalExperience->ProjectGroups, GetTextFromGroup, GroupLabelShifts, init );
        }
        else if( by == "Name" )
        {
            SortBy_ = SORT_BY_NAME;
            this->ListView_Sort( TAU_DELEGATE( bool, ProjectsScreen, CompareName, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
            ListView->SetOverridenContentHeight( Tau::Nullable< Tau::Real >::EMPTY );
        }
        else if( by == "Publisher" )
        {
            SortBy_ = SORT_BY_PUBLISHER;
            this->ListView_Sort( TAU_DELEGATE( bool, ProjectsScreen, ComparePublisher, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& ), init );
            HandleLabels( A::professionalExperience->Publishers, GetTextFromPublisher, PublisherLabelShifts, init );
        }
        else
        {
            TAU_ASSERT( false )
        }
    }

    template< class T >
    void ProjectsScreen::HandleLabels( const Tau::Vector< T >& labels, Tau::String (*extractText)( const Tau::Vector< T >&, int ), const Tau::Map_< int, int >& labelShifts, bool init )
    {
        ListView->SetOverridenContentHeight( this->ListView->GetRawContentHeight() + labels.Size() * LabelHeight - HeightDiff );

        for( int i = 0; i < labels.Size(); i++ )
        {
            Tau::Entity* label = SortLabels.Add( this->ListView->Owner->GetChild( "cellContainer" )->InstantiateChild( "projectsLabelText", false ) );
            label->GetTransform().SetY( this->ListView->CalcCellPosition( 0 ) - labelShifts.Get( i ) * BasicCellHeight - i * LabelHeight );

            Tau::TextSprite* text = label->GetChild( "text" )->GetComponent( Tau::TextSprite );
            text->SetText( extractText( labels, i ) );

            if( !init )
            {
                Tau::Interpolator::Interpolate( this, label->GetTransform().GetX() - label->GetComponent( Tau::Frame )->Width * C::interpolationSortSlideInFactor.Get(), label->GetTransform().GetX(), C::interpolationSortTime.Get(), C::interpolationSortType.Get(), EventHandlerSetX( label ) );
            }
        }
    }

    static Tau::String GetDateText( Tau::Entity* cell )
    {
        return CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::Project >( cell )->StartDate;
    }

    static Tau::String GetNameText( Tau::Entity* cell )
    {
        return Tau::StringUtils::Uncapitalize( CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::Project >( cell )->DisplayName );
    }

    static Tau::String GetPublisherText( Tau::Entity* cell )
    {
        return Tau::StringUtils::Uncapitalize( CVMenuScreen_ListView::ListView_GetDataSource< ProfessionalExperience::Project >( cell )->Publisher );
    }

    bool ProjectsScreen::CompareDate( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetDateText( info.element1 ) > GetDateText( info.element2 );
    }

    bool ProjectsScreen::CompareName( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetNameText( info.element1 ) < GetNameText( info.element2 );
    }

    bool ProjectsScreen::ComparePublisher( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info )
    {
        return GetPublisherText( info.element1 ) < GetPublisherText( info.element2 );
    }

    Tau::Point3D ProjectsScreen::ListView_GetSortedCellPosition( const Tau::ListViewSorter::MoveInfo& info ) const
    {
        const ProfessionalExperience::Project* project = *info.cell->GetComponent( Tau::ListViewCell )->GetModelItem< ProfessionalExperience::ProjectPtr >();

        switch( SortBy_ )
        {
            case SORT_BY_DATE: return info.newPosition - Tau::Point3D( 0, ( project->GroupIndex + 1 ) * LabelHeight - HeightDiff, 0 );
            case SORT_BY_NAME: return info.newPosition;
            case SORT_BY_PUBLISHER: return info.newPosition - Tau::Point3D( 0, ( project->PublisherIndex + 1 ) * LabelHeight - HeightDiff, 0 );

            default:
                TAU_ASSERT( false )
                return info.newPosition;
        }
    }

}
