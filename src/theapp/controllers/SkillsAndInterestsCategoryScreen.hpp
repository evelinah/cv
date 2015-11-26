// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

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
