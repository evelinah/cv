// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

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
