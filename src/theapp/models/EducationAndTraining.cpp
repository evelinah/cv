// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/models/EducationAndTraining.hpp"
#include "theapp/models/ProfessionalExperience.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/TextSprite.hpp"
#include "components/graphics/Layouter.hpp"

namespace TheApp
{

    namespace EducationAndTraining
    {

        void DataSource::Deserialize( const Tau::Deserializer& d )
        {
            StartDate = d.Get< Tau::String >( "startDate" );
            EndDate = d.TryGet< Tau::String >( "endDate", StartDate );
            Location = d.Get< Tau::String >( "location" );

            d.GetObjects( "Info", DataSource, DeserializeInfo );
        }

        void DataSource::DeserializeInfo( const Tau::Deserializer& d )
        {
            TAU_ASSERT( !Info.m_v.HasLength() )
            Info = d.Get< Tau::String >( "text" );
        }

        void DataSource::Validate() const
        {
            ValidateTimeFrame( StartDate, EndDate );
            TAU_ASSERT( A::professionalExperience->LocationsMap.Has( Location.m_v ) )
        }

    }

    // ---------------- //

    void EducationAndTrainingModels::Deserialize( const Tau::Deserializer& d )
    {
        Tau::Xml xml = Tau::Xml::FromFile( d.Get< Tau::String >( "file" ) );
        Tau::XmlIt root( xml );

        LoadModel( root.GetChild( "Education" ), Schools );
        LoadModel( root.GetChild( "Training" ), Courses );

        CVModels::FillMap( Schools, SchoolsMap );
        CVModels::FillMap( Courses, CoursesMap );
    }

    void EducationAndTrainingModels::Start()
    {
        for( Tau::Vector< const EducationAndTraining::DataSource* >::const_iterator it = DataSources.begin(); it != DataSources.end(); it++ )
        {
            (*it)->Validate();
        }
    }

    void EducationAndTrainingModels::LoadModel( Tau::XmlIt mit, Tau::Vector< EducationAndTraining::DataSourcePtr >& model )
    {
        for( Tau::XmlIt it = mit.GetChild(); it; it++ )
        {
            EducationAndTraining::DataSource* dataSource = model.Add( CVDataSource::Create< EducationAndTraining::DataSource >( it ) );
            DataSources.Add( dataSource );
            DataSourcesDisplayNames.Add( dataSource->DisplayName );
        }
    }

    void EducationAndTrainingModels::SetModel( const Tau::Vector< EducationAndTraining::DataSourcePtr >& model, Tau::ListView* view )
    {
        view->SetModel( model, EventHandler( EducationAndTrainingModels, SetCell, const Tau::ListView::CellSetterInfo< EducationAndTraining::DataSourcePtr >& ) );
        view->GetComponent( Tau::Layouter )->Align();
    }

    void EducationAndTrainingModels::SetCell( const Tau::ListView::CellSetterInfo< EducationAndTraining::DataSourcePtr >& info )
    {
        CVModels::SetBasicCell( info.cell, info.element );

        info.cell->GetChild( "startDate" )->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( info.element->StartDate );
        info.cell->GetChild( "endDate" )->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( info.element->EndDate );
    }

}
