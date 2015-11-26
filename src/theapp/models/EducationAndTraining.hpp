// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_EDUCATION_AND_TRAINING_HPP__
#define __INCLUDED_THE_APP_EDUCATION_AND_TRAINING_HPP__

#include "theapp/models/CVDataSource.hpp"

namespace TheApp
{

    namespace EducationAndTraining
    {

        class DataSource: public CVDataSource
        {
        public:
            virtual void Deserialize( const Tau::Deserializer& d ) _override;

            void Validate() const;

            Property::String< DataSource > StartDate;
            Property::String< DataSource > EndDate;
            Property::String< DataSource > Location;
            Property::String< DataSource > Info;

        private:
            void DeserializeInfo( const Tau::Deserializer& d );
        };

        TAU_SMART_PTR( DataSource )

    }

    // ---------------- //

    class EducationAndTrainingModels: public Tau::Component
    {
        TAU_COMPONENT( EducationAndTrainingModels )

    public:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void Start() _override;

        void SetModel( const Tau::Vector< EducationAndTraining::DataSourcePtr >& model, Tau::ListView* view );

        Tau::Vector< EducationAndTraining::DataSourcePtr > Schools;
        Tau::Vector< EducationAndTraining::DataSourcePtr > Courses;

        Tau::Map< const EducationAndTraining::DataSource* > SchoolsMap;
        Tau::Map< const EducationAndTraining::DataSource* > CoursesMap;

        Tau::Vector< const EducationAndTraining::DataSource* > DataSources;
        Tau::Set< Tau::String > DataSourcesDisplayNames;

    private:
        void LoadModel( Tau::XmlIt it, Tau::Vector< EducationAndTraining::DataSourcePtr >& model );

        void SetCell( const Tau::ListView::CellSetterInfo< EducationAndTraining::DataSourcePtr >& info );
    };

}

#endif
