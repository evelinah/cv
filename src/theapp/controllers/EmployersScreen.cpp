// rev: 524a6b2, exported: 2015-10-22 11:19:28

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
