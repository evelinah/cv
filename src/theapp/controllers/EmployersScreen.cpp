// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/EmployersScreen.hpp"
#include "theapp/controllers/ProfessionalExperienceCategoryDetailsScreen.hpp"
#include "taugen/TauWorldsCache.hpp"

namespace TheApp
{

    void EmployersScreen::Start()
    {
        CVMenuScreen::Start();

        A::professionalExperience->SetEmployersModel( A::professionalExperience->Employers, M::employersList );
    }

    void EmployersScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        const ProfessionalExperience::DataSourceProjects* dataSource = this->ListView_GetDataSource< ProfessionalExperience::DataSourceProjects >( sprite );

        if( dataSource )
        {
            this->Navigation_ShiftTo( "professionalExperienceCategoryDetailsScreen", ProfessionalExperienceCategoryDetailsScreen::SetupData( ProfessionalExperience::Category::EMPLOYERS, dataSource ) );
        }
    }

}
