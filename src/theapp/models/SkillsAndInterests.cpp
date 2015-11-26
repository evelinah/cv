// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/models/SkillsAndInterests.hpp"

#include "components/graphics/TextSprite.hpp"
#include "components/graphics/Layouter.hpp"

namespace TheApp
{

    const Tau::String SkillsAndInterestsModels::Category::TRAITS = "Traits";
    const Tau::String SkillsAndInterestsModels::Category::LANGUAGES = "Languages";
    const Tau::String SkillsAndInterestsModels::Category::INTERESTS = "Interests";

    // ---------------- //

    void SkillsAndInterestsModels::Deserialize( const Tau::Deserializer& d )
    {
        Tau::Xml xml = Tau::Xml::FromFile( d.Get< Tau::String >( "file" ) );
        Tau::XmlIt root( xml );

        LoadModel( root.GetChild( "Traits" ), Traits, true );
        LoadModel( root.GetChild( "Languages" ), Languages, true );
        LoadModel( root.GetChild( "Interests" ), Interests, true );

        Tau::XmlIt philosophy = root.GetChild( "Philosophy" );
        PhilosophyQuote = Tau::Deserializer( philosophy ).Get< Tau::String >( "quote" );
        LoadModel( philosophy.GetChild( "Do" ), PhilosophyDo, false );
        LoadModel( philosophy.GetChild( "Dont" ), PhilosophyDont, false );
    }

    void SkillsAndInterestsModels::LoadModel( Tau::XmlIt lit, Tau::Vector< Tau::String >& model, bool isCategory )
    {
        if( isCategory )
        {
            Categories.Add( lit.GetName(), Category( Tau::Deserializer( lit ).Get< Tau::String >( "label" ), &model ) );
        }

        for( Tau::XmlIt it = lit.GetChild(); it; it++ )
        {
            model.Add( Tau::Deserializer( it ).Get< Tau::String >( "name" ) );
        }
    }

    void SkillsAndInterestsModels::SetModel( const Tau::Vector< Tau::String >& model, Tau::ListView* view )
    {
        view->SetModel( model, EventHandler( SkillsAndInterestsModels, SetCell, const Tau::ListView::CellSetterInfo< Tau::String >& ) );
        view->GetComponent( Tau::Layouter )->Align();
    }

    void SkillsAndInterestsModels::SetCell( const Tau::ListView::CellSetterInfo< Tau::String >& info )
    {
        info.cell->GetChild( "text" )->GetComponent( Tau::TextSprite )->SetText( info.element );
    }

}
