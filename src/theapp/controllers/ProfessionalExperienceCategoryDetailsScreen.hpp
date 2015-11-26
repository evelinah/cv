// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

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
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name ) _override;

        bool SelectProject( ProfessionalExperience::ProjectPtr project );

        Property::Pointer< const ProfessionalExperience::DataSourceProjects, ProfessionalExperienceCategoryDetailsScreen > DataSource;
        Property::WeakPtr< Tau::TextSprite, ProfessionalExperienceCategoryDetailsScreen > Website;
        Tau::Vector< ProfessionalExperience::ProjectPtr > Projects;
    };

}

#endif
