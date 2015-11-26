// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_SCREEN_HPP__
#define __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class ProfessionalExperienceScreen: public CVMenuScreen
    {
        TAU_COMPONENT( ProfessionalExperienceScreen )

    private:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        void Slide( bool forth );

        void OnRadioButtonStateChanged( const Tau::RadioButtonGroup::StateChangedInfo& info );
    };

}

#endif
