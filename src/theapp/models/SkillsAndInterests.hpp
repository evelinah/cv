// rev: 524a6b2, exported: 2015-10-22 11:19:28

#ifndef __INCLUDED_THE_APP_SKILLS_AND_INTERESTS_HPP__
#define __INCLUDED_THE_APP_SKILLS_AND_INTERESTS_HPP__

#include "components/ui/ListView.hpp"

namespace TheApp
{

    class SkillsAndInterestsModels: public Tau::Component
    {
        TAU_COMPONENT( SkillsAndInterestsModels )

    public:
        virtual void Deserialize( const Tau::Deserializer& d ) _override;

        void SetModel( const Tau::Vector< Tau::String >& model, Tau::ListView* view );

        Tau::Vector< Tau::String > Traits;
        Tau::Vector< Tau::String > Languages;
        Tau::Vector< Tau::String > Interests;
        Tau::Vector< Tau::String > PhilosophyDo;
        Tau::Vector< Tau::String > PhilosophyDont;
        Property::String< SkillsAndInterestsModels > PhilosophyQuote;

        struct Category
        {
            Category( const Tau::String& a_label, const Tau::Vector< Tau::String >* a_model )
                : label( a_label ), model( a_model )
            {}

            Tau::String label;
            const Tau::Vector< Tau::String >* model;

            static const Tau::String TRAITS;
            static const Tau::String LANGUAGES;
            static const Tau::String INTERESTS;
        };

        Tau::Map< Category > Categories;

    private:
        void LoadModel( Tau::XmlIt lit, Tau::Vector< Tau::String >& list, bool isCategory );

        void SetCell( const Tau::ListView::CellSetterInfo< Tau::String >& info );
    };

}

#endif
