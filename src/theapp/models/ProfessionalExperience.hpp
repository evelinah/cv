// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_HPP__
#define __INCLUDED_THE_APP_PROFESSIONAL_EXPERIENCE_HPP__

#include "theapp/models/CVDataSource.hpp"

#include "components/ui/ListView.hpp"

namespace TheApp
{

    namespace ProfessionalExperience
    {

        class DataSource: public CVDataSource
        {
        public:
            virtual void Validate() const {}
        };

        // ---------------- //

        class DataSourceProjects: public DataSource
        {
        public:
            virtual void Deserialize( const Tau::Deserializer& d ) _override;
            virtual void Validate() const _override;

            Tau::String GetFirstUsed() const;
            Tau::String GetLastUsed() const;

            Tau::Vector< Tau::String > Projects;
            Tau::Vector< Tau::String > Courses;

        private:
            void DeserializeProject( const Tau::Deserializer& d );
            void DeserializeCourse( const Tau::Deserializer& d );

            Property::Nullable< Tau::String, DataSourceProjects > FirstUsed;
            Property::Nullable< Tau::String, DataSourceProjects > LastUsed;
        };

        TAU_SMART_PTR( DataSourceProjects )

        // ---------------- //

        class Category: public DataSource
        {
        public:
            virtual void Deserialize( const Tau::Deserializer& d ) _override;

            Property::String< Category > File;

            static const Tau::String EMPLOYERS;
            static const Tau::String PROJECTS;
            static const Tau::String SDK_INTEGRATION;
            static const Tau::String PROGRAMMING_LANGUAGES;
            static const Tau::String PLATFORMS;
            static const Tau::String MIDDLEWARE;
            static const Tau::String OPEN_SOURCE_LIBRARIES;
            static const Tau::String DEVICE_CLASSES;
            static const Tau::String APP_STORES;
            static const Tau::String UI_TECHNOLOGIES;
            static const Tau::String MEDIA_TECHNOLOGIES;
            static const Tau::String WEB_TECHNOLOGIES;
            static const Tau::String IDE;
            static const Tau::String VCS;
            static const Tau::String UNIT_AND_UI_TESTING;
            static const Tau::String DBMS;
            static const Tau::String DATA_EXCHANGE_FORMATS;
            static const Tau::String LOCATIONS;
            static const Tau::String METHODOLOGIES;
            static const Tau::String DEVELOPMENT_TEAM_SIZE;
            static const Tau::String ROLES;
        };

        TAU_SMART_PTR( Category )

        // ---------------- //

        class Publisher: public DataSource {};

        TAU_SMART_PTR( Publisher )

        // ---------------- //

        class Employer: public DataSourceProjects
        {
        public:
            virtual void Deserialize( const Tau::Deserializer& d ) _override;
            virtual void Validate() const _override;

            Property::String< Employer > StartDate;
            Property::String< Employer > EndDate;
        };

        TAU_SMART_PTR( Employer )

        // ---------------- //

        enum ProjectStatus
        {
            PROJECT_STATUS_LIVE,
            PROJECT_STATUS_NOT_YET_AVAILABLE,
            PROJECT_STATUS_NO_LONGER_AVAILABLE,
            PROJECT_STATUS_INTERNAL,
            PROJECT_STATUS_CANCELLED,
            PROJECT_STATUS_DEMO
        };

        TAU_ENUM_STRING( TheApp::ProfessionalExperience, ProjectStatus,
                         "live"               , PROJECT_STATUS_LIVE,
                         "not yet available"  , PROJECT_STATUS_NOT_YET_AVAILABLE,
                         "no longer available", PROJECT_STATUS_NO_LONGER_AVAILABLE,
                         "internal"           , PROJECT_STATUS_INTERNAL,
                         "cancelled"          , PROJECT_STATUS_CANCELLED,
                         "demo"               , PROJECT_STATUS_DEMO,
                         NULL )

        class Project: public DataSource
        {
        public:
            virtual void Deserialize( const Tau::Deserializer& d ) _override;
            virtual void Validate() const _override;

            void SetGroupIndex( int groupIndex ) { GroupIndex = groupIndex; }
            void SetPublisherIndex( int publisherIndex ) { PublisherIndex = publisherIndex; }

            Property::String< Project > StartDate;
            Property::String< Project > EndDate;
            Property::String< Project > Publisher;
            Property::Enum< ProjectStatus, Project > Status;
            Property::String< Project > Description;
            Property::Int< Project > GroupIndex;
            Property::Int< Project > PublisherIndex;

            struct Link
            {
                Link( const Tau::String& a_store, const Tau::String& a_url ): store( a_store ), url( a_url ) {}

                Tau::String store;
                Tau::String url;
            };

            Tau::Vector< Link > Links;

        private:
            void DeserializeDescription( const Tau::Deserializer& d );
            void DeserializeLink( const Tau::Deserializer& d );
        };

        TAU_SMART_PTR( Project )

        // ---------------- //

        class SdkIntegration: public DataSource
        {
        public:
            virtual void Deserialize( const Tau::Deserializer& d ) _override;
            virtual void Validate() const _override;

            Property::String< SdkIntegration > Date;
            Property::String< SdkIntegration > Platform;
        };

        TAU_SMART_PTR( SdkIntegration )

        // ---------------- //

        class ProgrammingLanguage: public DataSourceProjects {};
        class Platform: public DataSourceProjects {};
        class Middleware: public DataSourceProjects {};
        class OpenSourceLibrary: public DataSourceProjects {};
        class DeviceClass: public DataSourceProjects {};
        class AppStore: public DataSourceProjects {};
        class UITechnology: public DataSourceProjects {};
        class MediaTechnology: public DataSourceProjects {};
        class WebTechnology: public DataSourceProjects {};
        class IDE: public DataSourceProjects {};
        class VCS: public DataSourceProjects {};
        class UnitAndUITesting: public DataSourceProjects {};
        class DBMS: public DataSourceProjects {};
        class DataExchangeFormat: public DataSourceProjects {};
        class Location: public DataSourceProjects {};
        class Methodology: public DataSourceProjects {};
        class DevelopmentTeamSize: public DataSourceProjects {};
        class Role: public DataSourceProjects {};

        TAU_SMART_PTR( ProgrammingLanguage )
        TAU_SMART_PTR( Platform )
        TAU_SMART_PTR( Middleware )
        TAU_SMART_PTR( OpenSourceLibrary )
        TAU_SMART_PTR( DeviceClass )
        TAU_SMART_PTR( AppStore )
        TAU_SMART_PTR( UITechnology )
        TAU_SMART_PTR( MediaTechnology )
        TAU_SMART_PTR( WebTechnology )
        TAU_SMART_PTR( VCS )
        TAU_SMART_PTR( IDE )
        TAU_SMART_PTR( UnitAndUITesting )
        TAU_SMART_PTR( DBMS )
        TAU_SMART_PTR( DataExchangeFormat )
        TAU_SMART_PTR( Location )
        TAU_SMART_PTR( Methodology )
        TAU_SMART_PTR( DevelopmentTeamSize )
        TAU_SMART_PTR( Role )

    }

    // ---------------- //

    class ProfessionalExperienceModels: public Tau::Component
    {
        TAU_COMPONENT( ProfessionalExperienceModels )

    public:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;
        virtual void Start() _override;

        void SetEmployersModel( const Tau::Vector< ProfessionalExperience::EmployerPtr >& model, Tau::ListView* view );
        void SetProjectsModel( const Tau::Vector< ProfessionalExperience::ProjectPtr >& model, Tau::ListView* view );
        void SetSdkIntegrationsModel( const Tau::Vector< ProfessionalExperience::SdkIntegrationPtr >& model, Tau::ListView* view );
        void SetCategoryModel( const Tau::String& category, Tau::ListView* view );

        template< class T >
        class SelectItems
        {
        public:
            SelectItems( const Tau::String& project ): m_project( project ) {}

            bool operator()( Tau::SmartPtr< T > item )
            {
                return item.template Cast< ProfessionalExperience::DataSourceProjects >()->Projects.Has( m_project );
            }

        private:
            Tau::String m_project;
        };

        template< class T >
        Tau::Vector< Tau::SmartPtr< T > > Filter( const Tau::Vector< Tau::SmartPtr< T > >& model, const Tau::String& project )
        {
            Tau::Vector< Tau::SmartPtr< T > > items;
            model.Select( items, SelectItems< T >( project ) );
            return items;
        }

        Tau::Vector< ProfessionalExperience::CategoryPtr > Categories;
        Tau::Vector< ProfessionalExperience::PublisherPtr > Publishers;
        Tau::Vector< Tau::String > ProjectGroups;

        Tau::Vector< ProfessionalExperience::EmployerPtr > Employers;
        Tau::Vector< ProfessionalExperience::ProjectPtr > Projects;
        Tau::Vector< ProfessionalExperience::SdkIntegrationPtr > SdkIntegrations;
        Tau::Vector< ProfessionalExperience::ProgrammingLanguagePtr > ProgrammingLanguages;
        Tau::Vector< ProfessionalExperience::PlatformPtr > Platforms;
        Tau::Vector< ProfessionalExperience::MiddlewarePtr > Middlewares;
        Tau::Vector< ProfessionalExperience::OpenSourceLibraryPtr > OpenSourceLibraries;
        Tau::Vector< ProfessionalExperience::DeviceClassPtr > DeviceClasses;
        Tau::Vector< ProfessionalExperience::AppStorePtr > AppStores;
        Tau::Vector< ProfessionalExperience::UITechnologyPtr > UITechnologies;
        Tau::Vector< ProfessionalExperience::MediaTechnologyPtr > MediaTechnologies;
        Tau::Vector< ProfessionalExperience::WebTechnologyPtr > WebTechnologies;
        Tau::Vector< ProfessionalExperience::IDEPtr > IDEs;
        Tau::Vector< ProfessionalExperience::VCSPtr > VCSs;
        Tau::Vector< ProfessionalExperience::UnitAndUITestingPtr > UnitAndUITestings;
        Tau::Vector< ProfessionalExperience::DBMSPtr > DBMSs;
        Tau::Vector< ProfessionalExperience::DataExchangeFormatPtr > DataExchangeFormats;
        Tau::Vector< ProfessionalExperience::LocationPtr > Locations;
        Tau::Vector< ProfessionalExperience::MethodologyPtr > Methodologies;
        Tau::Vector< ProfessionalExperience::DevelopmentTeamSizePtr > DevelopmentTeamSizes;
        Tau::Vector< ProfessionalExperience::RolePtr > Roles;

        Tau::Map< const ProfessionalExperience::Category* > CategoriesMap;
        Tau::Map< const ProfessionalExperience::Publisher* > PublishersMap;
        Tau::Map< const ProfessionalExperience::Project* > ProjectsMap;
        Tau::Map< const ProfessionalExperience::Platform* > PlatformsMap;
        Tau::Map< const ProfessionalExperience::AppStore* > AppStoresMap;
        Tau::Map< const ProfessionalExperience::Location* > LocationsMap;

        Tau::Vector< const ProfessionalExperience::DataSource* > DataSources;
        Tau::Set< Tau::String > DataSourcesDisplayNames;

        Tau::Map< Tau::String > CategoryNames;

    private:
        template< class T >
        void LoadModel( const Tau::String& fileName, Tau::Vector< Tau::SmartPtr< T > >& model );

        void LoadModel( const Tau::String& fileName, Tau::Vector< ProfessionalExperience::ProjectPtr >& model );

        template< class T >
        T* AddDataSource( Tau::XmlIt it, Tau::Vector< Tau::SmartPtr< T > >& model );

        template< class T >
        void SetCategoryModel( const Tau::Vector< Tau::SmartPtr< T > >& model, Tau::ListView* view );

        template< class T, void (ProfessionalExperienceModels::*CellSetter)( const Tau::ListView::CellSetterInfo< Tau::SmartPtr< T > >& ) >
        void SetModel( const Tau::Vector< Tau::SmartPtr< T > >& model, Tau::ListView* view );

        void SetEmployerCell( const Tau::ListView::CellSetterInfo< ProfessionalExperience::EmployerPtr >& info );
        void SetSdkIntegrationCell( const Tau::ListView::CellSetterInfo< ProfessionalExperience::SdkIntegrationPtr >& info );
        void SetProjectCell( const Tau::ListView::CellSetterInfo< ProfessionalExperience::ProjectPtr >& info );

        template< class T >
        void SetCategoryCell( const Tau::ListView::CellSetterInfo< Tau::SmartPtr< T > >& info );
    };

}

#endif
