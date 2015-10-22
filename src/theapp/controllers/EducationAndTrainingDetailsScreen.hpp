// rev: 524a6b2, exported: 2015-10-22 11:19:28

#ifndef __INCLUDED_THE_APP_EDUCATION_AND_TRAINING_DETAILS_SCREEN_HPP__
#define __INCLUDED_THE_APP_EDUCATION_AND_TRAINING_DETAILS_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"
#include "theapp/models/EducationAndTraining.hpp"

namespace TheApp
{

    class EducationAndTrainingDetailsScreen: public CVMenuScreen
    {
        TAU_COMPONENT( EducationAndTrainingDetailsScreen )

    protected:
        virtual void Navigation_Setup( const Tau::Any& data ) _override;

    private:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        Property::Pointer< const EducationAndTraining::DataSource, EducationAndTrainingDetailsScreen > DataSource;
        Property::WeakPtr< Tau::TextSprite, EducationAndTrainingDetailsScreen > Website;
    };

}

#endif
