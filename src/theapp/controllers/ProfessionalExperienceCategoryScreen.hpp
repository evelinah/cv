// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_CATEGORY_SCREEN_HPP__
#define __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_CATEGORY_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"

namespace TheApp
{

    class ProfessionalExperienceCategoryScreen: public CVMenuScreen
    {
        TAU_COMPONENT( ProfessionalExperienceCategoryScreen )

    protected:
        virtual void Navigation_Setup( const Tau::Any& data ) _override;

    private:
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        void Sort( const Tau::String by, bool init );
        bool CompareName( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
        bool CompareFirstUsed( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
        bool CompareLastUsed( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );
        bool CompareProjects( const Tau::SortAdapter< Tau::Entity* >::CompareInfo& info );

        Property::String< ProfessionalExperienceCategoryScreen > CategoryName;
    };

}

#endif
