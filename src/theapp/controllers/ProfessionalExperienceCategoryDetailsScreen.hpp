// rev: 89281ca, exported: 2015-10-16 23:24:12

#ifndef __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_CATEGORY_DETAILS_SCREEN_HPP__
#define __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_CATEGORY_DETAILS_SCREEN_HPP__

#include "theapp/controllers/CVMenuScreen.hpp"
#include "theapp/models/ProfessionalExperience.hpp"

namespace TheApp
{

    class ProfessionalExperienceCategoryDetailsScreen: public CVMenuScreen
    {
        TAU_COMPONENT( ProfessionalExperienceCategoryDetailsScreen )

    public:
        struct SetupData
        {
            SetupData( const Tau::String& a_categoryName, const ProfessionalExperience::DataSourceProjects* a_dataSource )
                : categoryName( a_categoryName )
                , dataSource( a_dataSource )
            {}

            Tau::String categoryName;
            const ProfessionalExperience::DataSourceProjects* dataSource;
        };

    protected:
        virtual void Navigation_Setup( const Tau::Any& data ) _override;

    private:
        virtual void OnSelectSprite( Tau::AbstractSprite* sprite, const Tau::String& name, bool select ) _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        bool SelectProject( ProfessionalExperience::ProjectPtr project );

        Property::Pointer< const ProfessionalExperience::DataSourceProjects, ProfessionalExperienceCategoryDetailsScreen > DataSource;
        Tau::Vector< ProfessionalExperience::ProjectPtr > Projects;
    };

}

#endif
