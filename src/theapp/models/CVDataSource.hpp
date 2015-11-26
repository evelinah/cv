// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#ifndef __INCLUDED_THE_APP_CV_DATA_SOURCE_HPP__
#define __INCLUDED_THE_APP_CV_DATA_SOURCE_HPP__

#include "components/base/Dictionary.hpp"
#include "components/ui/ListView.hpp"

namespace TheApp
{

    class CVDataSource: public Tau::SmartPointable, public Tau::WeakPointable
    {
    public:
        template< class T >
        static Tau::SmartPtr< T > Create( const Tau::Deserializer& d )
        {
            Tau::SmartPtr< T > object( new T() );
            object.template Cast< CVDataSource >()->Name = d.Get< Tau::String >( "name" );
            object.template Cast< CVDataSource >()->DisplayName = d.TryGet< Tau::String >( "displayName", object.template Cast< CVDataSource >()->Name );
            object.template Cast< CVDataSource >()->Icon = d.TryGet< Tau::String >( "icon", Tau::String::EMPTY );
            object.template Cast< CVDataSource >()->Url = d.TryGet< Tau::String >( "url", Tau::String::EMPTY );
            object.template Cast< CVDataSource >()->DisplayUrl = GetDisplayUrl( object.template Cast< CVDataSource >()->Url );

            object->Deserialize( d );
            return object;
        }

        virtual void Deserialize( const Tau::Deserializer& d ) {}

        Property::String< CVDataSource > Name;
        Property::String< CVDataSource > DisplayName;
        Property::String< CVDataSource > Icon;
        Property::String< CVDataSource > Url;
        Property::String< CVDataSource > DisplayUrl;

    protected:
        CVDataSource() {}

        static void ValidateTimeFrame( const Tau::String& startDate, const Tau::String& endDate );

    private:
        static Tau::String GetDisplayUrl( const Tau::String& url );
    };

    TAU_SMART_PTR( CVDataSource )

    // ---------------- //

    class CVModels
    {
    public:
        template< class T >
        static void FillMap( const Tau::Vector< Tau::SmartPtr< T > >& model, Tau::Map< const T* >& map )
        {
            for( typename Tau::Vector< Tau::SmartPtr< T > >::const_iterator it = model.begin(); it != model.end(); it++ )
            {
                map.Add( (*it)->Name, *it );
            }
        }

        static void SetBasicCell( Tau::Entity* cell, const CVDataSource* dataSource );
    };

}

#endif
