// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/models/ProfessionalExperience.hpp"
#include "theapp/models/EducationAndTraining.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

#include "components/graphics/TextSprite.hpp"
#include "components/graphics/Layouter.hpp"

namespace TheApp
{

    namespace ProfessionalExperience
    {

        void DataSourceProjects::Deserialize( const Tau::Deserializer& d )
        {
            FirstUsed = d.Has< Tau::String >( "firstUsed" ) ? d.Get< Tau::String >( "firstUsed" ) : Tau::Nullable< Tau::String >::EMPTY;
            LastUsed = d.Has< Tau::String >( "lastUsed" ) ? d.Get< Tau::String >( "lastUsed" ) : Tau::Nullable< Tau::String >::EMPTY;

            d.GetObjects( "Project", DataSourceProjects, DeserializeProject );
            d.GetObjects( "Course", DataSourceProjects, DeserializeCourse );
        }

        void DataSourceProjects::DeserializeProject( const Tau::Deserializer& d )
        {
            Projects.Add( d.Get< Tau::String >( "name" ) );
        }

        void DataSourceProjects::DeserializeCourse( const Tau::Deserializer& d )
        {
            Courses.Add( d.Get< Tau::String >( "name" ) );
        }

        void DataSourceProjects::Validate() const
        {
            CVDataSource::ValidateTimeFrame( GetFirstUsed(), GetLastUsed() );

            TAU_ASSERT( !( Projects.IsEmpty() && Courses.IsEmpty() ) )

            for( Tau::Vector< Tau::String >::const_iterator it = Projects.begin(); it != Projects.end(); it++ )
            {
                TAU_ASSERT( A::professionalExperience->ProjectsMap.Has( *it ) )
            }

            for( Tau::Vector< Tau::String >::const_iterator it = Courses.begin(); it != Courses.end(); it++ )
            {
                TAU_ASSERT( A::educationAndTraining->CoursesMap.Has( *it ) )
            }
        }

        static const Tau::String& GetProjectStartDate( const Tau::String& project )
        {
            return A::professionalExperience->ProjectsMap.Get( project )->StartDate;
        }

        static const Tau::String& GetProjectEndDate( const Tau::String& project )
        {
            return A::professionalExperience->ProjectsMap.Get( project )->EndDate;
        }

        static const Tau::String& GetCourseStartDate( const Tau::String& course )
        {
            return A::educationAndTraining->CoursesMap.Get( course )->StartDate;
        }

        static const Tau::String& GetCourseEndDate( const Tau::String& course )
        {
            return A::educationAndTraining->CoursesMap.Get( course )->EndDate;
        }

        Tau::String DataSourceProjects::GetFirstUsed() const
        {
            if( FirstUsed.m_v.IsSet() ) { return FirstUsed.m_v.Get(); }

            static const char m = 127; Tau::String max( &m, 1 );

            Tau::String result = Math::Min( Projects.IsEmpty() ? max : Tau::ContainerUtils::Min< Tau::String >( Projects, GetProjectStartDate ),
                                            Courses.IsEmpty() ? max : Tau::ContainerUtils::Min< Tau::String >( Courses, GetCourseStartDate ) );
            TAU_ASSERT( result != max )
            return result;
        }

        Tau::String DataSourceProjects::GetLastUsed() const
        {
            if( LastUsed.m_v.IsSet() ) { return LastUsed.m_v.Get(); }

            static const char m = 0; Tau::String min( &m, 1 );

            Tau::String result = Math::Max( Projects.IsEmpty() ? min : Tau::ContainerUtils::Max< Tau::String >( Projects, GetProjectEndDate ),
                                            Courses.IsEmpty() ? min : Tau::ContainerUtils::Max< Tau::String >( Courses, GetCourseEndDate ) );
            TAU_ASSERT( result != min )
            return result;
        }

        // ---------------- //

        const Tau::String Category::EMPLOYERS = "Employers";
        const Tau::String Category::PROJECTS = "Projects";
        const Tau::String Category::SDK_INTEGRATION = "SDK integration";
        const Tau::String Category::PROGRAMMING_LANGUAGES = "Programming languages";
        const Tau::String Category::PLATFORMS = "Platforms";
        const Tau::String Category::MIDDLEWARE = "Middleware";
        const Tau::String Category::OPEN_SOURCE_LIBRARIES = "Open source libraries";
        const Tau::String Category::DEVICE_CLASSES = "Device classes";
        const Tau::String Category::APP_STORES = "App stores";
        const Tau::String Category::UI_TECHNOLOGIES = "UI technologies";
        const Tau::String Category::MEDIA_TECHNOLOGIES = "Media technologies";
        const Tau::String Category::WEB_TECHNOLOGIES = "Web technologies";
        const Tau::String Category::IDE = "IDE";
        const Tau::String Category::VCS = "VCS";
        const Tau::String Category::UNIT_AND_UI_TESTING = "Unit & UI testing";
        const Tau::String Category::DBMS = "DBMS";
        const Tau::String Category::DATA_EXCHANGE_FORMATS = "Data exchange formats";
        const Tau::String Category::LOCATIONS = "Locations";
        const Tau::String Category::METHODOLOGIES = "Methodologies";
        const Tau::String Category::DEVELOPMENT_TEAM_SIZE = "Development team size";
        const Tau::String Category::ROLES = "Roles";

        void Category::Deserialize( const Tau::Deserializer& d )
        {
            File = d.Get< Tau::String >( "file" );
        }

        // ---------------- //

        void Employer::Deserialize( const Tau::Deserializer& d )
        {
            DataSourceProjects::Deserialize( d );

            StartDate = d.Get< Tau::String >( "startDate" );
            EndDate = d.TryGet< Tau::String >( "endDate", StartDate );
        }

        void Employer::Validate() const
        {
            DataSourceProjects::Validate();

            ValidateTimeFrame( StartDate, EndDate );
        }

        // ---------------- //

        void Project::Deserialize( const Tau::Deserializer& d )
        {
            StartDate = d.Get< Tau::String >( "startDate" );
            EndDate = d.TryGet< Tau::String >( "endDate", StartDate );
            Publisher = d.Get< Tau::String >( "publisher" );
            Status = Enum::ProjectStatus::Parse( d.TryGet< Tau::String >( "status", "live" ) );

            d.GetObjects( "Description", Project, DeserializeDescription );
            d.GetObjects( "Link", Project, DeserializeLink );
        }

        void Project::DeserializeDescription( const Tau::Deserializer& d )
        {
            TAU_ASSERT( !Description.m_v.HasLength() )
            Description = d.Get< Tau::String >( "text" );
        }

        void Project::DeserializeLink( const Tau::Deserializer& d )
        {
            Links.Add( Link( d.Get< Tau::String >( "store" ), d.Get< Tau::String >( "url" ) ) );
        }

        void Project::Validate() const
        {
            ValidateTimeFrame( StartDate, EndDate );
            TAU_ASSERT( A::professionalExperience->PublishersMap.Has( Publisher.m_v ) )

            for( Tau::Vector< Link >::const_iterator it = Links.begin(); it != Links.end(); it++ )
            {
                TAU_ASSERT( A::professionalExperience->AppStoresMap.Has( it->store ) )
            }

            TAU_ASSERT( Links.Size() <= C::uiProjectDetailsIconCount.Get() )
        }

        // ---------------- //

        void SdkIntegration::Deserialize( const Tau::Deserializer& d )
        {
            Date = d.Get< Tau::String >( "date" );
            Platform = d.Get< Tau::String >( "platform" );
        }

        void SdkIntegration::Validate() const
        {
            TAU_ASSERT( A::professionalExperience->PlatformsMap.Has( Platform.m_v ) )
        }

    }

    // ---------------- //

    static bool ComparePublisher( ProfessionalExperience::Publisher* p1, ProfessionalExperience::Publisher* p2 )
    {
        return Tau::StringUtils::Uncapitalize( p1->Name ) < Tau::StringUtils::Uncapitalize( p2->Name );
    }

    void ProfessionalExperienceModels::Deserialize( const Tau::Deserializer& d )
    {
        LoadModel( d.Get< Tau::String >( "categoriesFile" ), Categories );
        CVModels::FillMap( Categories, CategoriesMap );

        for( Tau::Vector< ProfessionalExperience::CategoryPtr >::const_iterator it = Categories.begin(); it != Categories.end(); it++ )
        {
            CategoryNames.Add( (*it)->DisplayName, (*it)->Name );
        }

        LoadModel( d.Get< Tau::String >( "publishersFile" ), Publishers );
        Publishers.Sort( ComparePublisher );
        CVModels::FillMap( Publishers, PublishersMap );

        for( Tau::Vector< ProfessionalExperience::CategoryPtr >::const_iterator it = Categories.begin(); it != Categories.end(); it++ )
        {
            ProfessionalExperience::Category* c = *it;

                 if( c->Name == ProfessionalExperience::Category::EMPLOYERS )             { LoadModel( c->File, Employers ); }
            else if( c->Name == ProfessionalExperience::Category::PROJECTS )              { LoadModel( c->File, Projects ); }
            else if( c->Name == ProfessionalExperience::Category::SDK_INTEGRATION )       { LoadModel( c->File, SdkIntegrations ); }
            else if( c->Name == ProfessionalExperience::Category::PROGRAMMING_LANGUAGES ) { LoadModel( c->File, ProgrammingLanguages ); }
            else if( c->Name == ProfessionalExperience::Category::PLATFORMS )             { LoadModel( c->File, Platforms ); }
            else if( c->Name == ProfessionalExperience::Category::MIDDLEWARE )            { LoadModel( c->File, Middlewares ); }
            else if( c->Name == ProfessionalExperience::Category::OPEN_SOURCE_LIBRARIES ) { LoadModel( c->File, OpenSourceLibraries ); }
            else if( c->Name == ProfessionalExperience::Category::DEVICE_CLASSES )        { LoadModel( c->File, DeviceClasses ); }
            else if( c->Name == ProfessionalExperience::Category::APP_STORES )            { LoadModel( c->File, AppStores ); }
            else if( c->Name == ProfessionalExperience::Category::UI_TECHNOLOGIES )       { LoadModel( c->File, UITechnologies ); }
            else if( c->Name == ProfessionalExperience::Category::MEDIA_TECHNOLOGIES )    { LoadModel( c->File, MediaTechnologies ); }
            else if( c->Name == ProfessionalExperience::Category::WEB_TECHNOLOGIES )      { LoadModel( c->File, WebTechnologies ); }
            else if( c->Name == ProfessionalExperience::Category::IDE )                   { LoadModel( c->File, IDEs ); }
            else if( c->Name == ProfessionalExperience::Category::VCS )                   { LoadModel( c->File, VCSs ); }
            else if( c->Name == ProfessionalExperience::Category::UNIT_AND_UI_TESTING )   { LoadModel( c->File, UnitAndUITestings ); }
            else if( c->Name == ProfessionalExperience::Category::DBMS )                  { LoadModel( c->File, DBMSs ); }
            else if( c->Name == ProfessionalExperience::Category::DATA_EXCHANGE_FORMATS ) { LoadModel( c->File, DataExchangeFormats ); }
            else if( c->Name == ProfessionalExperience::Category::LOCATIONS )             { LoadModel( c->File, Locations ); }
            else if( c->Name == ProfessionalExperience::Category::METHODOLOGIES )         { LoadModel( c->File, Methodologies ); }
            else if( c->Name == ProfessionalExperience::Category::DEVELOPMENT_TEAM_SIZE ) { LoadModel( c->File, DevelopmentTeamSizes ); }
            else if( c->Name == ProfessionalExperience::Category::ROLES )                 { LoadModel( c->File, Roles ); }
            else
            {
                TAU_MSG_ASSERT( false, "Unrecognized category: " << c->Name.Val() )
            }
        }

        CVModels::FillMap( Projects, ProjectsMap );
        CVModels::FillMap( Platforms, PlatformsMap );
        CVModels::FillMap( AppStores, AppStoresMap );
        CVModels::FillMap( Locations, LocationsMap );
    }

    void ProfessionalExperienceModels::Start()
    {
        for( Tau::Vector< const ProfessionalExperience::DataSource* >::const_iterator it = DataSources.begin(); it != DataSources.end(); it++ )
        {
            (*it)->Validate();
        }
    }

    template< class T >
    void ProfessionalExperienceModels::LoadModel( const Tau::String& fileName, Tau::Vector< Tau::SmartPtr< T > >& model )
    {
        Tau::Xml xml = Tau::Xml::FromFile( fileName );

        for( Tau::XmlIt it = Tau::XmlIt( xml ).GetChild(); it; it++ )
        {
            AddDataSource( it, model );
        }
    }

    void ProfessionalExperienceModels::LoadModel( const Tau::String& fileName, Tau::Vector< ProfessionalExperience::ProjectPtr >& model )
    {
        Tau::Xml xml = Tau::Xml::FromFile( fileName );

        int groupIndex = 0;

        for( Tau::XmlIt git = Tau::XmlIt( xml ).GetChild(); git; git++ )
        {
            Tau::String group = Tau::Deserializer( git ).Get< Tau::String >( "label" );
            ProjectGroups.Add( group );

            for( Tau::XmlIt pit = Tau::XmlIt( git ).GetChild( "Project" ); pit; pit++ )
            {
                ProfessionalExperience::Project* project = AddDataSource( pit, model );
                project->SetGroupIndex( groupIndex );
                project->SetPublisherIndex( Publishers.FindIndex( ProfessionalExperience::PublisherPtr( const_cast< ProfessionalExperience::Publisher* >( PublishersMap.Get( project->Publisher ) ) ) ).Get() );
            }

            groupIndex++;
        }
    }

    template< class T >
    T* ProfessionalExperienceModels::AddDataSource( Tau::XmlIt it, Tau::Vector< Tau::SmartPtr< T > >& model )
    {
        T* dataSource = model.Add( CVDataSource::Create< T >( it ) );
        DataSources.Add( dataSource );
        DataSourcesDisplayNames.Add( dataSource->DisplayName, true );
        return dataSource;
    }

    void ProfessionalExperienceModels::SetEmployersModel( const Tau::Vector< ProfessionalExperience::EmployerPtr >& model, Tau::ListView* view )
    {
        SetModel< ProfessionalExperience::Employer, &ProfessionalExperienceModels::SetEmployerCell >( model, view );
    }

    void ProfessionalExperienceModels::SetProjectsModel( const Tau::Vector< ProfessionalExperience::ProjectPtr >& model, Tau::ListView* view )
    {
        SetModel< ProfessionalExperience::Project, &ProfessionalExperienceModels::SetProjectCell >( model, view );
    }

    void ProfessionalExperienceModels::SetSdkIntegrationsModel( const Tau::Vector< ProfessionalExperience::SdkIntegrationPtr >& model, Tau::ListView* view )
    {
        SetModel< ProfessionalExperience::SdkIntegration, &ProfessionalExperienceModels::SetSdkIntegrationCell >( model, view );
    }

    void ProfessionalExperienceModels::SetCategoryModel( const Tau::String& category, Tau::ListView* view )
    {
             if( category == ProfessionalExperience::Category::PROGRAMMING_LANGUAGES ) { SetCategoryModel( ProgrammingLanguages, view ); }
        else if( category == ProfessionalExperience::Category::PLATFORMS )             { SetCategoryModel( Platforms, view ); }
        else if( category == ProfessionalExperience::Category::MIDDLEWARE )            { SetCategoryModel( Middlewares, view ); }
        else if( category == ProfessionalExperience::Category::OPEN_SOURCE_LIBRARIES ) { SetCategoryModel( OpenSourceLibraries, view ); }
        else if( category == ProfessionalExperience::Category::DEVICE_CLASSES )        { SetCategoryModel( DeviceClasses, view ); }
        else if( category == ProfessionalExperience::Category::APP_STORES )            { SetCategoryModel( AppStores, view ); }
        else if( category == ProfessionalExperience::Category::UI_TECHNOLOGIES )       { SetCategoryModel( UITechnologies, view ); }
        else if( category == ProfessionalExperience::Category::MEDIA_TECHNOLOGIES )    { SetCategoryModel( MediaTechnologies, view ); }
        else if( category == ProfessionalExperience::Category::WEB_TECHNOLOGIES )      { SetCategoryModel( WebTechnologies, view ); }
        else if( category == ProfessionalExperience::Category::IDE )                   { SetCategoryModel( IDEs, view ); }
        else if( category == ProfessionalExperience::Category::VCS )                   { SetCategoryModel( VCSs, view ); }
        else if( category == ProfessionalExperience::Category::UNIT_AND_UI_TESTING )   { SetCategoryModel( UnitAndUITestings, view ); }
        else if( category == ProfessionalExperience::Category::DBMS )                  { SetCategoryModel( DBMSs, view ); }
        else if( category == ProfessionalExperience::Category::DATA_EXCHANGE_FORMATS ) { SetCategoryModel( DataExchangeFormats, view ); }
        else if( category == ProfessionalExperience::Category::LOCATIONS )             { SetCategoryModel( Locations, view ); }
        else if( category == ProfessionalExperience::Category::METHODOLOGIES )         { SetCategoryModel( Methodologies, view ); }
        else if( category == ProfessionalExperience::Category::DEVELOPMENT_TEAM_SIZE ) { SetCategoryModel( DevelopmentTeamSizes, view ); }
        else if( category == ProfessionalExperience::Category::ROLES )                 { SetCategoryModel( Roles, view ); }
        else
        {
            TAU_MSG_ASSERT( false, "Unexpected category: " << category )
        }
    }

    template< class T >
    void ProfessionalExperienceModels::SetCategoryModel( const Tau::Vector< Tau::SmartPtr< T > >& model, Tau::ListView* view )
    {
        SetModel< T, &ProfessionalExperienceModels::SetCategoryCell< T > >( model, view );
    }

    template< class T, void (ProfessionalExperienceModels::*CellSetter)( const Tau::ListView::CellSetterInfo< Tau::SmartPtr< T > >& ) >
    void ProfessionalExperienceModels::SetModel( const Tau::Vector< Tau::SmartPtr< T > >& model, Tau::ListView* view )
    {
        view->SetModel( model, Tau::Delegate< void, const Tau::ListView::CellSetterInfo< Tau::SmartPtr< T > >& >::template Create< ProfessionalExperienceModels, CellSetter >( this ) );
        view->GetComponent( Tau::Layouter )->Align();
    }

    void ProfessionalExperienceModels::SetEmployerCell( const Tau::ListView::CellSetterInfo< ProfessionalExperience::EmployerPtr >& info )
    {
        CVModels::SetBasicCell( info.cell, info.element );

        info.cell->GetChild( "startDate" )->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( info.element->StartDate );
        info.cell->GetChild( "endDate" )->GetChild( "value" )->GetComponent( Tau::TextSprite )->SetText( info.element->EndDate );
    }

    void ProfessionalExperienceModels::SetProjectCell( const Tau::ListView::CellSetterInfo< ProfessionalExperience::ProjectPtr >& info )
    {
        CVModels::SetBasicCell( info.cell, info.element );
    }

    void ProfessionalExperienceModels::SetSdkIntegrationCell( const Tau::ListView::CellSetterInfo< ProfessionalExperience::SdkIntegrationPtr >& info )
    {
        CVModels::SetBasicCell( info.cell, info.element );

        info.cell->GetChild( "date" )->GetChild( "text" )->GetComponent( Tau::TextSprite )->SetText( info.element->Date );
        info.cell->GetChild( "platform" )->GetChild( "text" )->GetComponent( Tau::TextSprite )->SetText( Tau::StringUtils::String( info.element->Platform ) );
    }

    template< class T >
    void ProfessionalExperienceModels::SetCategoryCell( const Tau::ListView::CellSetterInfo< Tau::SmartPtr< T > >& info )
    {
        CVModels::SetBasicCell( info.cell, info.element );

        ProfessionalExperience::DataSourceProjects* d = info.element.template Cast< ProfessionalExperience::DataSourceProjects >();
        info.cell->GetChild( "firstUsed" )->GetChild( "text" )->GetComponent( Tau::TextSprite )->SetText( d->GetFirstUsed() );
        info.cell->GetChild( "lastUsed" )->GetChild( "text" )->GetComponent( Tau::TextSprite )->SetText( d->GetLastUsed() );
        info.cell->GetChild( "projects" )->GetChild( "text" )->GetComponent( Tau::TextSprite )->SetText( Tau::StringUtils::String( d->Projects.Size() ) );
    }

}
