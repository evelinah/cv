// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_PROJECTS_SCREEN_HPP__
#define __INCLUDED_THE_APP_PROJECTS_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class ProjectsScreen: public CVMenuScreen
    {
        TAU_COMPONENT( ProjectsScreen )

    private:
        virtual void Start() _override;
        virtual void OnShowStarted( const Tau::String& prevScreen ) _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        void Sort( const Tau::String by, bool init );

        template< class T >
        void HandleLabels( const Tau::Vector< T >& labels, Tau::String (*extractText)( const Tau::Vector< T >&, int ), const Tau::Map_< int, int >& labelShifts, bool init );

        bool CompareDate( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
        bool CompareName( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
        bool ComparePublisher( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );

        virtual Tau::Point3D ListView_GetSortedCellPosition( const Tau::ListViewSorter::MoveInfo& info ) const _override;

        enum SortBy
        {
            SORT_BY_DATE,
            SORT_BY_NAME,
            SORT_BY_PUBLISHER
        };

        Property::Real< ProjectsScreen > BasicCellHeight;
        Property::Real< ProjectsScreen > LabelHeight;
        Property::Real< ProjectsScreen > HeightDiff;

        Property::Enum< SortBy, ProjectsScreen > SortBy_;
        Tau::Vector< Tau::Entity* > SortLabels;

        Tau::Map_< int, int > GroupLabelShifts;
        Tau::Map_< int, int > PublisherLabelShifts;
    };

}

#endif
