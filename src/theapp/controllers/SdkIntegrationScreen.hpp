// rev: 89281ca, exported: 2015-10-16 23:24:12

#ifndef __INCLUDED_THE_APP_SDK_INTEGRATION_SCREEN_HPP__
#define __INCLUDED_THE_APP_SDK_INTEGRATION_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class SdkIntegrationScreen: public CVMenuScreen
    {
        TAU_COMPONENT( SdkIntegrationScreen )

    private:
        virtual void Start() _override;
        virtual void OnShowStarted( const Tau::String& prevScreen ) _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        void Sort( const Tau::String by, bool init );
        bool CompareName( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
        bool CompareDate( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
        bool ComparePlatform( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
    };

}

#endif
