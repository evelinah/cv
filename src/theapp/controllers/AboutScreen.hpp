// rev: 89281ca, exported: 2015-10-16 23:24:12

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
