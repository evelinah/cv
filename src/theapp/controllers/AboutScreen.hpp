// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_ABOUT_SCREEN_HPP__
#define __INCLUDED_THE_APP_ABOUT_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class AboutScreen: public CVMenuScreen
    {
        TAU_COMPONENT( AboutScreen )

    private:
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;
    };

}

#endif
