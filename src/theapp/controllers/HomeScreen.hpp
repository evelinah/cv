// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_HOME_SCREEN_HPP__
#define __INCLUDED_THE_APP_HOME_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class HomeScreen: public CVMenuScreen
    {
        TAU_COMPONENT( HomeScreen )

    private:
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;
        virtual void OnTransition( Tau::Real t ) _override;
    };

}

#endif
