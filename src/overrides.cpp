#include "menuVisuals.h"
#include "nightscoutData.h"
#include "overrides.h"

void addOverrides(MENU* menu){
    OVERRIDE_LIST list = getOverridesList();
    for (int i = 0; i < list.size; i++)
    {
        String name = list.overrides[i].name;
        String insulinPercent = list.overrides[i].insulinPercent;
        name = name.substring(0, 12);
        int blankspaces = 16-(name.length()+insulinPercent.length());
        String overrideName = name;
        Serial.println(blankspaces);
        while(blankspaces--){
        overrideName += " ";
        }
        overrideName += insulinPercent + "%";
        Serial.println(overrideName);
        addOption(menu, overrideName);
    }
}

void cancelOverride(){
  SetOverride(-1);
}

void override(int override){
  SetOverride(override);
}
