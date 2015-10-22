// rev: 524a6b2, exported: 2015-10-22 11:19:28

#ifndef __INCLUDED_THE_APP_SKILLS_AND_INTERESTS_CATEGORY_SCREEN_HPP__
#define __INCLUDED_THE_APP_SKILLS_AND_INTERESTS_CATEGORY_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class SkillsAndInterestsCategoryScreen: public CVMenuScreen
    {
        TAU_COMPONENT( SkillsAndInterestsCategoryScreen )

    protected:
        virtual void Navigation_Setup( const Tau::Any& data ) _override;
    };

}

#endif
