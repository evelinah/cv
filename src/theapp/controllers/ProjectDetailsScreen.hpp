// rev: 89281ca, exported: 2015-10-16 23:24:12

#ifndef __INCLUDED_THE_APP_PROJECT_DETAILS_SCREEN_HPP__
#define __INCLUDED_THE_APP_PROJECT_DETAILS_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"

#include "components/graphics/AbstractSprite.hpp"

namespace TheApp
{

    class ProjectDetailsScreen: public CVMenuScreen
    {
        TAU_COMPONENT( ProjectDetailsScreen )

    protected:
        virtual void Navigation_Setup( const Tau::Any& data ) _override;

    private:
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        template< class T >
        void SetIcons( const Tau::Vector< T >& items, Tau::String (*extractIcon)( const Tau::Vector< T >&, int ), Tau::Entity* container );

        Property::Pointer< const ProfessionalExperience::Project, ProjectDetailsScreen > Project_;
        Tau::Vector< ProfessionalExperience::PlatformPtr > Platforms;
        Tau::Vector< ProfessionalExperience::DeviceClassPtr > DeviceClasses;
        Tau::Vector< ProfessionalExperience::MiddlewarePtr > Middlewares;
        Tau::Vector< ProfessionalExperience::ProgrammingLanguagePtr > ProgrammingLanguages;
    };

}

#endif
