// rev: 89281ca, exported: 2015-10-16 23:24:12

#include "theapp/controllers/SkillsAndInterestsCategoryScreen.hpp"
#include "theapp/models/SkillsAndInterests.hpp"
#include "taugen/TauSettingsCache.hpp"
#include "taugen/TauWorldsCache.hpp"

namespace TheApp
{

    void SkillsAndInterestsCategoryScreen::Navigation_Setup( const Tau::Any& data )
    {
        const Tau::String& categoryName = data.Cast< Tau::String >();
        const SkillsAndInterestsModels::Category& category = A::skillsAndInterests->Categories.Get( categoryName );

        this->Navigation_SetTabsTexts( C::uiSkillsAndInterestsNavigationTabs.Get() + '/' + category.label );
        this->Navigation_SetAnalyticsName( categoryName );

        A::skillsAndInterests->SetModel( *category.model, M::skillsAndInterestsCategoryList );
    }

}