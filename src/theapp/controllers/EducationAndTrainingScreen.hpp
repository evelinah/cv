// rev: 524a6b2, exported: 2015-10-22 11:19:28

#ifndef __INCLUDED_THE_APP_EDUCATION_AND_TRAINING_SCREEN_HPP__
#define __INCLUDED_THE_APP_EDUCATION_AND_TRAINING_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class EducationAndTrainingScreen: public CVMenuScreen
    {
        TAU_COMPONENT( EducationAndTrainingScreen )

    private:
        virtual void Start() _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;
    };

}

#endif
