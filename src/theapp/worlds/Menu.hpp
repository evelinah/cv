// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

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
