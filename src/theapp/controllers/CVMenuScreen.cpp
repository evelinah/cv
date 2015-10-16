// rev: 89281ca, exported: 2015-10-16 23:24:12

#include "theapp/controllers/CVMenuScreen.hpp"
#include "theapp/models/EducationAndTraining.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "theapp/models/SkillsAndInterests.hpp"
#include "theapp/worlds/Menu.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/Camera.hpp"
#include "components/graphics/Frame.hpp"
#include "components/graphics/Layouter.hpp"
#include "components/graphics/SpriteGroup.hpp"
#include "components/graphics/TextSprite.hpp"

#include "core/application/Application.hpp"
#include "core/application/System.hpp"

namespace TheApp
{

    void CVMenuScreen_Interpolation::Interpolation_SetVisible( Tau::AbstractSprite* sprite, bool visible, bool handleTouchable )
    {
        Tau::Interpolator::Interpolate( M::menu, sprite->Alpha, visible ? 1 : 0, C::interpolationSetVisibleTime.Get(), C::interpolationSetVisibleType.Get(), EventHandlerSetAlpha( sprite ) );

        if( handleTouchable )
        {
            sprite->SetTouchable( visible );
        }
    }

    // ---------------- //

    void CVMenuScreen_Transition::Deserialize( const Tau::Deserializer& d )
    {
        Base::Deserialize( d );

        this->TryCache( this->Owner->Name + "ZoomInTransition", ZoomInTransition.m_v );
        this->TryCache( this->Owner->Name + "SlideInBottomTransition", SlideInBottomTransition.m_v );
    }

    Tau::MenuScreen* CVMenuScreen_Transition::Transition_SwitchTo( const Tau::String& screenName, bool back )
    {
        ShiftBack = back;
        NewScreen = static_cast< CVMenuScreen_Transition* >( this->SwitchTo( screenName, 0.2, EventHandler( CVMenuScreen_Transition, Transition_OnProgress, Tau::Real ) ) );
        return NewScreen;
    }

    void CVMenuScreen_Transition::Transition_OnProgress( Tau::Real t )
    {
        M::fadeOut->SetAlpha( ShiftBack ? 1 - t : t );
        M::fadeIn->SetAlpha( ShiftBack ? 1 - t : t );

        Tau::Real zoomZ = Tau::Camera::Get()->ProjectionCenter.Val().Z * C::transitionZoomInFactor.Get();
        if( ZoomInTransition ) { ZoomInTransition->GetTransform().SetZ( ( ShiftBack ? zoomZ : -zoomZ ) * t ); }
        if( NewScreen->ZoomInTransition ) { NewScreen->ZoomInTransition->GetTransform().SetZ( ( ShiftBack ? -zoomZ : zoomZ ) * ( 1 - t ) ); }

        Tau::Real slideY = -M::footer->Height * C::transitionSlideInBottomFactor.Get();
        if( SlideInBottomTransition ) { SlideInBottomTransition->GetTransform().SetY( slideY * t ); }
        if( NewScreen->SlideInBottomTransition ) { NewScreen->SlideInBottomTransition->GetTransform().SetY( slideY * ( 1 - t ) ); }

        OnTransition( 1 - t );
        NewScreen->OnTransition( t );
    }

    // ---------------- //

    void CVMenuScreen_ListView::Deserialize( const Tau::Deserializer& d )
    {
        Base::Deserialize( d );

        this->TryCache( d.TryGet( "listView", Tau::String::EMPTY ), ListView.m_v );
        this->TryCache( d.TryGet( "sortButtons", Tau::String::EMPTY ), SortButtons.m_v );

        if( SortButtons )
        {
            SortButtons->StateChangedEvent += EventHandler( CVMenuScreen_ListView, ListView_OnRadioButtonStateChanged, const Tau::RadioButtonGroup::StateChangedInfo& );
        }
    }

    static Tau::Real GetSortButtonWidth( const Tau::Frame* frame )
    {
        Tau::TextSprite* text = frame->Owner->GetChild( "buttonText" )->GetComponent( Tau::TextSprite );
        return text->GetPosition().X + text->GetWidth() - frame->Owner->GetChild( "buttonIcon" )->GetComponent( Tau::Sprite )->GetPosition().X;
    }

    void CVMenuScreen_ListView::Start()
    {
        Base::Start();

        if( SortButtons )
        {
            const Tau::Vector< Tau::WeakPtr< Tau::AbstractSprite > >& buttons = SortButtons->GetComponent( Tau::SpriteGroup )->GetSprites();
            Tau::Vector< Tau::Real > buttonWidths;

            for( Tau::Vector< Tau::WeakPtr< Tau::AbstractSprite > >::const_iterator it = buttons.begin(); it != buttons.end(); it++ )
            {
                buttonWidths.Add( GetSortButtonWidth( it->Cast< const Tau::Frame >() ) );
            }

            Tau::Real space = ( Tau::Camera::Get()->ProjectionResolution - Tau::ContainerUtils::Sum< Tau::Real >( buttonWidths ) ) / ( buttons.Size() + 1 );
            Tau::Real x = space;

            for( int i = 0; i < buttons.Size(); i++ )
            {
                Tau::Frame* frame = buttons[i].Cast< Tau::Frame >();
                frame->GetTransform().SetX( x );
                frame->SetWidth( buttonWidths[i] );
                x += frame->Width + space;
            }
        }
    }

    void CVMenuScreen_ListView::OnShowStarted( const Tau::String& prevScreen )
    {
        Base::OnShowStarted( prevScreen );

        if( ListView )
        {
            ListView->GetComponent( Tau::ListViewScroller )->Stop();
        }
    }

    void CVMenuScreen_ListView::ListView_OnRadioButtonStateChanged( const Tau::RadioButtonGroup::StateChangedInfo& info )
    {
        info.sprite->SetTouchable( !info.active );

        Tau::Sprite* icon = info.sprite->Owner->GetChild( "buttonIcon" )->GetComponent( Tau::Sprite );
        Tau::Interpolator::Interpolate( this, icon->Alpha, info.active ? C::interpolationSortDisabledAlpha.Get() : 1, info.init ? 0 : C::interpolationSortTime.Get(), C::interpolationSortType.Get(), EventHandlerSetAlpha( icon ) );

        Tau::TextSprite* text = info.sprite->Owner->GetChild( "buttonText" )->GetComponent( Tau::TextSprite );
        Tau::Interpolator::Interpolate( this, text->Alpha, info.active ? C::interpolationSortDisabledAlpha.Get() : 1, info.init ? 0 : C::interpolationSortTime.Get(), C::interpolationSortType.Get(), EventHandlerSetAlpha( text ) );
    }

    void CVMenuScreen_ListView::ListView_Sort( Tau::Delegate< bool, const Tau::SortAdapter< Tau::Entity* >::CompareInfo& > compare, bool instant )
    {
        InstantSort = instant;
        ListView->GetComponent( Tau::ListViewSorter )->Sort( compare, TAU_DELEGATE( void, CVMenuScreen_ListView, ListView_MoveCell, const Tau::ListViewSorter::MoveInfo& ) );
    }

    void CVMenuScreen_ListView::ListView_MoveCell( const Tau::ListViewSorter::MoveInfo& info )
    {
        Tau::Interpolator::Interpolate< Tau::Vector3DInterpolator >( this, info.cell->GetTransform().GetPosition(), ListView_GetSortedCellPosition( info ), InstantSort ? 0 : C::interpolationSortTime.Get(), C::interpolationSortType.Get(), EventHandlerSetPosition( info.cell ) );
    }

    Tau::ListViewCell* CVMenuScreen_ListView::ListView_GetCell( Tau::AbstractSprite* sprite )
    {
        return sprite && sprite->Owner->Parent ? sprite->Owner->Parent->TryGetComponent( Tau::ListViewCell ) : NULL;
    }

    // ---------------- //

    Tau::Vector< CVMenuScreen_Navigation::NavigationContext > CVMenuScreen_Navigation::s_navigationStack;
    Tau::Map_< Tau::AbstractSprite*, Tau::Vector2D > CVMenuScreen_Navigation::s_scaleStash;

    void CVMenuScreen_Navigation::Init( const Tau::String& firstScreenName )
    {
        Tau::MenuScreen::Activate( M::menu, firstScreenName );

        s_navigationStack.Clear();
        s_navigationStack.Add( NavigationContext( firstScreenName, false, Tau::Any::EMPTY ) );
        Navigation_UpdateBackButton( false );
    }

    void CVMenuScreen_Navigation::Deserialize( const Tau::Deserializer& d )
    {
        Base::Deserialize( d );

        Navigation_SetTabsTexts( d.Get< Tau::String >( "navigationTabs" ) );
    }

    void CVMenuScreen_Navigation::OnShowStarted( const Tau::String& prevScreen )
    {
        Base::OnShowStarted( prevScreen );

        A::analytics->Log( "show screen", this->Owner->Name + ( AnalyticsName.m_v.HasLength() ? ", " + AnalyticsName : Tau::String::EMPTY ) );

        Navigation_SetupTabs();
    }

    static void OnSprite( Tau::AbstractSprite* sprite, const Tau::Vector2D& scale, bool hightlightCell )
    {
        if( !sprite ) { return; }

        sprite->SetScale( scale );

        // button
        {
            Tau::Entity* buttonText = sprite->Owner->GetChild( "buttonText", true );
            if( buttonText ) { buttonText->GetComponent( Tau::TextSprite )->SetScale( scale ); }
        }

        // list view cell
        {
            Tau::ListViewCell* cell = CVMenuScreen_ListView::ListView_GetCell( sprite );

            if( cell )
            {
                Tau::RectangleSprite* highlight = cell->Owner->GetChild( "highlight" )->GetComponent( Tau::RectangleSprite );
                highlight->SetAlpha( hightlightCell ? 1 : 0 );
                highlight->SetScale( 1 );
            }
        }
    }

    static Tau::AbstractSprite* SubstituteFrame( Tau::AbstractSprite* sprite )
    {
        return sprite == M::backButtonFrame ? M::backButton : sprite;
    }

    void CVMenuScreen_Navigation::OnSelectSprite( Tau::AbstractSprite* sprite, const Tau::String& name, bool select )
    {
        Base::OnSelectSprite( sprite, name, select );

        sprite = SubstituteFrame( sprite );

        if( select )
        {
            s_scaleStash.Add( sprite, sprite->Scale );
            OnSprite( sprite, sprite->Scale * C::navigationPressedButtonScale.Get(), true );
        }
        else
        {
            OnSprite( sprite, s_scaleStash.Get( sprite ), false );
            s_scaleStash.Remove( sprite );
        }
    }

    static bool IsNavigationTab( Tau::AbstractSprite* sprite )
    {
        return sprite == M::navigationTab1 || sprite == M::navigationTab2 ||
               sprite == M::navigationTab3 || sprite == M::navigationTab4;
    }

    void CVMenuScreen_Navigation::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        Base::OnSpriteUp( sprite, name );

        if( sprite == M::backButtonFrame || name == "backKey" )
        {
            TAU_ASSERT( !s_navigationStack.IsEmpty() )

            if( s_navigationStack.Size() > 1 )
            {
                A::analytics->Log( "back clicked" );
                const NavigationContext& prev = s_navigationStack[ s_navigationStack.Size() - 2 ];
                Navigation_ShiftTo( prev.screenName, !s_navigationStack.Last().back, prev.setupData, false );
                s_navigationStack.RemoveLast();
                Navigation_ValidateStack();
                Navigation_UpdateBackButton( true );
            }
        }
        else if( IsNavigationTab( sprite ) )
        {
            Tau::String tabText = sprite->Owner->GetChild( "buttonText" )->GetComponent( Tau::TextSprite )->Text;
            tabText = A::professionalExperience->CategoryNames.TryGet( tabText, tabText );
            A::analytics->Log( "tab clicked", tabText );
            Tau::String screenName = Navigation_GetMenuScreenName( tabText );
            this->Navigation_ShiftBackTo( screenName.HasLength() ? screenName : "professionalExperienceCategoryScreen", screenName.HasLength() ? Tau::Any::EMPTY : tabText );
        }
    }

    Tau::MenuScreen* CVMenuScreen_Navigation::Navigation_ShiftTo( const Tau::String& screenName, bool back, const Tau::Any& setupData, bool addToStack )
    {
        A::analytics->Log( "navigate", this->Owner->Name + " -> " + screenName );

        static_cast< CVMenuScreen_Navigation* >( FindMenuScreen( this, screenName ) )->Navigation_Setup( setupData );
        Tau::MenuScreen* screen = Transition_SwitchTo( screenName, back );

        if( addToStack )
        {
            s_navigationStack.Add( NavigationContext( screenName, back, setupData ) );
            Navigation_ValidateStack();
            Navigation_UpdateBackButton( true );
        }

        return screen;
    }

    void CVMenuScreen_Navigation::Navigation_SetTabsTexts( const Tau::String& texts )
    {
        NavigationTabsTexts.Clear();
        Tau::StringUtils::Split( texts, NavigationTabsTexts, '/', true );

        for( int i = 0; i < NavigationTabsTexts.Size(); i++ )
        {
            const Tau::String& text = NavigationTabsTexts[i];
            TAU_ASSERT( !text.HasLength() || A::educationAndTraining->DataSourcesDisplayNames.Has( text ) || A::professionalExperience->DataSourcesDisplayNames.Has( text ) || A::skillsAndInterests->Categories.Has( text ) || this->EntityExists( Navigation_GetMenuScreenName( text ) ) )
        }
    }

    void CVMenuScreen_Navigation::Navigation_SetupTabs()
    {
        Tau::Vector< Tau::AbstractSprite* > tabs;
        tabs.Add( M::navigationTab1 );
        tabs.Add( M::navigationTab2 );
        tabs.Add( M::navigationTab3 );
        tabs.Add( M::navigationTab4 );

        TAU_ASSERT( NavigationTabsTexts.Size() >= 1 && NavigationTabsTexts.Size() <= tabs.Size() )

        Navigation_SetupTab( tabs[0], NavigationTabsTexts[0], NULL );

        int i = 1;

        for( ; i < NavigationTabsTexts.Size(); i++ )
        {
            Navigation_SetupTab( tabs[i], NavigationTabsTexts[i], tabs[i-1] );
        }

        tabs[i-1]->SetTouchable( false );

        for( ; i < tabs.Size(); i++ )
        {
            Navigation_SetupTab( tabs[i], Tau::String::EMPTY, NULL );
        }
    }

    void CVMenuScreen_Navigation::Navigation_SetupTab( Tau::AbstractSprite* tab, const Tau::String& text, Tau::AbstractSprite* prevTab )
    {
        Tau::TextSprite* textSprite = Navigation_GetTextSprite( tab );
        bool visible = text.HasLength();
        bool fadeOut = textSprite->Alpha != 0 && visible && text != textSprite->Text;

        if( fadeOut )
        {
            textSprite->SetAlpha( 0 );

            Tau::TextSprite* copy = this->FindEntity( tab->Owner->Name + "FadeOut" )->GetChild( "buttonText" )->GetComponent( Tau::TextSprite );
            copy->Owner->Parent->GetTransform().SetPosition( tab->GetTransform().GetPosition() );
            copy->SetText( textSprite->Text );
            copy->SetAlpha( 1 );
            Interpolation_SetVisible( copy, false );
        }

        if( visible ) { textSprite->SetText( text ); }
        Interpolation_SetVisible( textSprite, visible );

        tab->GetComponent( Tau::Frame )->SetTouchable( visible );

        Tau::AbstractSprite* separator = this->FindComponent< Tau::AbstractSprite >( tab->Owner->Name + "Separator.Sprite", true );

        if( separator )
        {
            if( visible )
            {
                TAU_ASSERT( prevTab )
                Tau::Real separatorX = prevTab->GetTransform().GetX() + ( Navigation_GetTextSprite( prevTab )->GetTextWidth() + separator->GetWidth() ) * 0.5 + C::uiNavigationTabPadding.Get();

                if( fadeOut )
                {
                    separator->SetAlpha( 0 );

                    Tau::Sprite* copy = this->FindEntity( tab->Owner->Name + "FadeOutSeparator" )->GetComponent( Tau::Sprite );
                    copy->GetTransform().SetPosition( separator->GetTransform().GetPosition() );
                    copy->SetAlpha( 1 );
                    Interpolation_SetVisible( copy, false );
                }

                separator->GetTransform().SetX( separatorX );
                tab->GetTransform().SetX( separatorX + ( separator->GetWidth() + textSprite->GetTextWidth() ) * 0.5 + C::uiNavigationTabPadding.Get() );
            }

            Interpolation_SetVisible( separator, visible );
        }
    }

    Tau::TextSprite* CVMenuScreen_Navigation::Navigation_GetTextSprite( Tau::AbstractSprite* tab )
    {
        return tab->Owner->GetChild( "buttonText" )->GetComponent( Tau::TextSprite );
    }

    Tau::String CVMenuScreen_Navigation::Navigation_GetMenuScreenName( const Tau::String& tabText )
    {
        Tau::String name = Tau::StringUtils::ReplaceAll( Tau::StringUtils::ToLowerCamelCase( tabText ), "&", "And", true ) + "Screen";
        TAU_ASSERT( this->EntityExists( name ) || A::professionalExperience->CategoriesMap.Has( tabText ) || A::skillsAndInterests->Categories.Has( tabText ) )
        return this->EntityExists( name ) ? name : Tau::String::EMPTY;
    }

    void CVMenuScreen_Navigation::Navigation_ValidateStack()
    {
        TAU_ASSERT( s_navigationStack.Size() < 2 || s_navigationStack[ s_navigationStack.Size() - 2 ].screenName != s_navigationStack.Last().screenName )
    }

    void CVMenuScreen_Navigation::Navigation_UpdateBackButton( bool animate )
    {
        TAU_ASSERT( !s_navigationStack.IsEmpty() )
        bool active = s_navigationStack.Size() > 1;

        if( Math::Xor( active, M::backButton->Alpha == 1 ) || !animate )
        {
            Tau::Interpolator::Interpolate( M::menu, M::backButton->Alpha, active ? 1 : C::interpolationBackButtonDisabledAlpha.Get(), animate ? C::interpolationBackButtonTime.Get() : 0, C::interpolationBackButtonType.Get(), EventHandlerSetAlpha( M::backButton ) );
            M::backButtonFrame->SetTouchable( active );
        }
    }

}
