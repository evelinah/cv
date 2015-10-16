// rev: 89281ca, exported: 2015-10-16 23:24:12

#ifndef __INCLUDED_THE_APP_CV_MENU_SCREEN_HPP__
#define __INCLUDED_THE_APP_CV_MENU_SCREEN_HPP__

#include "components/graphics/TextSprite.hpp"
#include "components/ui/MenuScreen.hpp"
#include "components/ui/ListView.hpp"
#include "components/ui/RadioButtonGroup.hpp"

namespace TheApp
{

    // ---------------- //

    class CVMenuScreen_Interpolation: public Tau::MenuScreen
    {
    protected:
        void Interpolation_SetVisible( Tau::AbstractSprite* sprite, bool visible, bool handleTouchable = false );
    };

    // ---------------- //

    class CVMenuScreen_Transition: public CVMenuScreen_Interpolation
    {
    private:
        typedef CVMenuScreen_Interpolation Base;

    protected:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;

        Tau::MenuScreen* Transition_SwitchTo( const Tau::String& screenName, bool back );

        virtual void OnTransition( Tau::Real t ) {}

        Property::WeakPtr< Tau::Entity, CVMenuScreen_Transition > ZoomInTransition;
        Property::WeakPtr< Tau::Entity, CVMenuScreen_Transition > SlideInBottomTransition;

        Property::Pointer< CVMenuScreen_Transition, CVMenuScreen_Transition > NewScreen;
        Property::Bool< CVMenuScreen_Transition > ShiftBack;

    private:
        void Transition_OnProgress( Tau::Real t );
    };

    // ---------------- //

    class CVMenuScreen_ListView: public CVMenuScreen_Transition
    {
    private:
        typedef CVMenuScreen_Transition Base;

    public:
        void ListView_OnRadioButtonStateChanged( const Tau::RadioButtonGroup::StateChangedInfo& info );

    protected:
        virtual void Start() _override;
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void OnShowStarted( const Tau::String& prevScreen ) _override;

        void ListView_Sort( Tau::Delegate< bool, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& > compare, bool instant );
        void ListView_MoveCell( const Tau::ListViewSorter::MoveInfo& info );

        virtual Tau::Point3D ListView_GetSortedCellPosition( const Tau::ListViewSorter::MoveInfo& info ) const { return info.newPosition; }

        Property::WeakPtr< Tau::ListView, CVMenuScreen_ListView > ListView;
        Property::WeakPtr< Tau::RadioButtonGroup, CVMenuScreen_ListView > SortButtons;

    public:
        static Tau::ListViewCell* ListView_GetCell( Tau::AbstractSprite* sprite );

        template< class T >
        static const T* ListView_GetDataSource( Tau::AbstractSprite* sprite )
        {
            Tau::ListViewCell* cell = ListView_GetCell( sprite );
            return cell ? *cell->GetModelItemUnsafe< Tau::SmartPtr< T > >() : reinterpret_cast< T* >( NULL );
        }

        template< class T >
        static const T* ListView_GetDataSource( Tau::Entity* cell )
        {
            return *cell->GetComponent( Tau::ListViewCell )->GetModelItemUnsafe< Tau::SmartPtr< T > >();
        }

    private:
        Property::Bool< CVMenuScreen_ListView > InstantSort;
    };

    // ---------------- //

    class CVMenuScreen_Navigation: public CVMenuScreen_ListView
    {
    private:
        typedef CVMenuScreen_ListView Base;

    public:
        static void Init( const Tau::String& firstScreenName );

    protected:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void OnShowStarted( const Tau::String& prevScreen ) _override;
        virtual void OnSelectSprite( Tau::AbstractSprite* sprite, const Tau::String& name, bool select ) _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        virtual void Navigation_Setup( const Tau::Any& data ) {}

        Tau::MenuScreen* Navigation_ShiftTo( const Tau::String& screenName, const Tau::Any& setupData = Tau::Any::EMPTY ) { return Navigation_ShiftTo( screenName, false, setupData, true ); }
        Tau::MenuScreen* Navigation_ShiftBackTo( const Tau::String& screenName, const Tau::Any& setupData = Tau::Any::EMPTY ) { return Navigation_ShiftTo( screenName, true, setupData, true ); }

        void Navigation_SetTabsTexts( const Tau::String& texts );
        void Navigation_SetAnalyticsName( const Tau::String& analyticsName ) { AnalyticsName = analyticsName; }

        Tau::Vector< Tau::String > NavigationTabsTexts;

    private:
        Tau::MenuScreen* Navigation_ShiftTo( const Tau::String& screenName, bool back, const Tau::Any& setupData, bool addToStack );
        void Navigation_SetupTabs();
        void Navigation_SetupTab( Tau::AbstractSprite* tab, const Tau::String& text, Tau::AbstractSprite* prevTab );
        Tau::TextSprite* Navigation_GetTextSprite( Tau::AbstractSprite* tab );
        Tau::String Navigation_GetMenuScreenName( const Tau::String& tabText );

        Property::String< CVMenuScreen_Navigation > AnalyticsName;

        struct NavigationContext
        {
            NavigationContext( const Tau::String& a_screenName, bool a_back, const Tau::Any& a_setupData ): screenName( a_screenName ), back( a_back ), setupData( a_setupData ) {}

            Tau::String screenName;
            bool back;
            Tau::Any setupData;
        };

        static void Navigation_ValidateStack();
        static void Navigation_UpdateBackButton( bool animate );

        static Tau::Vector< NavigationContext > s_navigationStack;
        static Tau::Map_< Tau::AbstractSprite*, Tau::Vector2D > s_scaleStash;
    };

    // ---------------- //

    class CVMenuScreen: public CVMenuScreen_Navigation {};

}

#endif
