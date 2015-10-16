// rev: 89281ca, exported: 2015-10-16 23:24:12

#ifndef __INCLUDED_THE_APP_MENU_HPP__
#define __INCLUDED_THE_APP_MENU_HPP__

#include "core/world/Component.hpp"

namespace TheApp
{

    class Menu: public Tau::Component
    {
        TAU_COMPONENT( Menu )

    public:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void Start() _override;

    private:
        void PreloadTextures();
    };

}

#endif
