// rev: 524a6b2, exported: 2015-10-22 11:19:28

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
