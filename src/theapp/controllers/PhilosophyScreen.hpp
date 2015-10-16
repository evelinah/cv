// rev: 89281ca, exported: 2015-10-16 23:24:12

#ifndef __INCLUDED_THE_APP_PHILOSOPHY_SCREEN_HPP__
#define __INCLUDED_THE_APP_PHILOSOPHY_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class PhilosophyScreen: public CVMenuScreen
    {
        TAU_COMPONENT( PhilosophyScreen )

    private:
        virtual void Start() _override;
    };

}

#endif
