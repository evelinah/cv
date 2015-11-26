// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

#include "theapp/controllers/PhilosophyScreen.hpp"
#include "theapp/models/SkillsAndInterests.hpp"
#include "taugen/TauWorldsCache.hpp"

namespace TheApp
{

    void PhilosophyScreen::Start()
    {
        CVMenuScreen::Start();

        A::skillsAndInterests->SetModel( A::skillsAndInterests->PhilosophyDo, M::philosophyDoList );
        A::skillsAndInterests->SetModel( A::skillsAndInterests->PhilosophyDont, M::philosophyDontList );
        M::philosophyQuote->SetText( A::skillsAndInterests->PhilosophyQuote );
    }

}
