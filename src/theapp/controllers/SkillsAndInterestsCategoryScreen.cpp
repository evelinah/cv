// rev: 5b8c3b9, exported: 2015-11-26 00:57:21

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
