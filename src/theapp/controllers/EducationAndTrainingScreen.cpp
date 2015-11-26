// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/EducationAndTrainingScreen.hpp"
#include "theapp/models/EducationAndTraining.hpp"
#include "taugen/TauWorldsCache.hpp"

namespace TheApp
{

    static void SetupList( const Tau::Vector< EducationAndTraining::DataSourcePtr >& model, Tau::ListView* view )
    {
        A::educationAndTraining->SetModel( model, view );
        view->Owner->GetChild( "topFadeOut" )->SetActive( false );
        view->Owner->GetChild( "topFadeOut" )->SetActive( false );
    }

    void EducationAndTrainingScreen::Start()
    {
        CVMenuScreen::Start();

        SetupList( A::educationAndTraining->Schools, M::educationList );
        SetupList( A::educationAndTraining->Courses, M::trainingList );
    }

    void EducationAndTrainingScreen::OnSpriteUp( Tau::AbstractSprite* sprite, const Tau::String& name )
    {
        CVMenuScreen::OnSpriteUp( sprite, name );

        const EducationAndTraining::DataSource* dataSource = this->ListView_GetDataSource< EducationAndTraining::DataSource >( sprite );

        if( dataSource )
        {
            this->Navigation_ShiftTo( "educationAndTrainingDetailsScreen", dataSource );
        }
    }

}
