/*#include "nosmoke.h"
#include "menu.h"
#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"


std::vector<const char*> smoke_materials = {
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
};

bool NoSmoke::RenderSmokePostViewmodel()
{
	return Menu::Window.VisualsTab.Active && Menu::Window.VisualsTab.OtherNoSmoke;
}

void NoSmoke::FrameStageNotify(ClientFrameStage_t stage)
{
	

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	for (auto material_name : smoke_materials)
	{
		IMaterial* mat = material->FindMaterial(material_name, TEXTURE_GROUP_OTHER);
		mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Menu::Window.VisualsTab.Active && Menu::Window.VisualsTab.OtherNoSmoke);
	}
}

void NoSmoke::AimTuxShutdown()
{
	for (auto material_name : smoke_materials)
	{
		IMaterial* mat = material->FindMaterial(material_name, TEXTURE_GROUP_OTHER);
		mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
	}
}*/