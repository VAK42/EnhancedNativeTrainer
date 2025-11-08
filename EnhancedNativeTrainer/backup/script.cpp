#include "script.h"
#include "keyboard.h"
#include <string>
#include <ctime>
#pragma warning(disable : 4244 4305)

void drawRect(float a0, float a1, float a2, float a3, int a4, int a5, int a6, int a7)
{
	GRAPHICS::DRAW_RECT((a0 + (a2 * 0.5f)), (a1 + (a3 * 0.5f)), a2, a3, a4, a5, a6, a7);
}
void drawMenuLine(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText = true)
{
	int textCol[4] = {255, 255, 255, 255};
	int rectCol[4] = {0, 0, 0, 205};
	float textScale = 0.35;
	int font = 0;
	if (active)
	{
		rectCol[0] = 0;
		rectCol[1] = 0;
		rectCol[2] = 0;
		rectCol[3] = 255;
		if (rescaleText)
			textScale = 0.40;
	}
	if (title)
	{
		rectCol[0] = 0;
		rectCol[1] = 0;
		rectCol[2] = 0;
		rectCol[3] = 255;
		if (rescaleText)
			textScale = 0.50;
		font = 1;
	}
	int screenW, screenH;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screenW, &screenH);
	textLeft += lineLeft;
	float lineWidthScaled = lineWidth / (float)screenW;
	float lineTopScaled = lineTop / (float)screenH;
	float textLeftScaled = textLeft / (float)screenW;
	float lineHeightScaled = lineHeight / (float)screenH;
	float lineLeftScaled = lineLeft / (float)screenW;
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, textScale);
	UI::SET_TEXT_COLOUR(textCol[0], textCol[1], textCol[2], textCol[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, textScale);
	UI::SET_TEXT_COLOUR(textCol[0], textCol[1], textCol[2], textCol[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_GXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	int lineCount = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	drawRect(lineLeftScaled, lineTopScaled + (0.00278f), lineWidthScaled, ((((float)(lineCount)*UI::_0xDB88A37483346780(textScale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f), rectCol[0], rectCol[1], rectCol[2], rectCol[3]);
}
bool trainerSwitchPressed()
{
	return IsKeyJustUp(VK_F4);
}
void getButtonState(bool *a, bool *b, bool *up, bool *down, bool *l, bool *r)
{
	if (a)
		*a = IsKeyDown(VK_NUMPAD5);
	if (b)
		*b = IsKeyDown(VK_NUMPAD0) || trainerSwitchPressed() || IsKeyDown(VK_BACK);
	if (up)
		*up = IsKeyDown(VK_NUMPAD8);
	if (down)
		*down = IsKeyDown(VK_NUMPAD2);
	if (r)
		*r = IsKeyDown(VK_NUMPAD6);
	if (l)
		*l = IsKeyDown(VK_NUMPAD4);
}
void menuBeep()
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;
void updateStatusText()
{
	if (GetTickCount() < statusTextDrawTicksMax)
	{
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry)
		{
			UI::_SET_TEXT_ENTRY((char *)statusText.c_str());
		}
		else
		{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}
void setStatusText(std::string str, DWORD time = 2500, bool isGxtEntry = false)
{
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}
bool featurePlayerInvincible = false;
bool featurePlayerInvincibleUpdated = false;
bool featurePlayerNeverWanted = false;
bool featurePlayerIgnored = false;
bool featurePlayerIgnoredUpdated = false;
bool featurePlayerUnlimitedAbility = false;
bool featurePlayerNoNoise = false;
bool featurePlayerNoNoiseUpdated = false;
bool featurePlayerFastSwim = false;
bool featurePlayerFastSwimUpdated = false;
bool featurePlayerFastRun = false;
bool featurePlayerFastRunUpdated = false;
bool featurePlayerSuperJump = false;
bool featureWeaponNoReload = false;
bool featureWeaponFireAmmo = false;
bool featureWeaponExplosiveAmmo = false;
bool featureWeaponExplosiveMelee = false;
bool featureWeaponVehRockets = false;
DWORD featureWeaponVehShootLastTime = 0;
bool featureVehInvincible = false;
bool featureVehInvincibleUpdated = false;
bool featureVehInvincibleWheels = false;
bool featureVehInvincibleWheelsUpdated = false;
bool featureVehSeatbelt = false;
bool featureVehSeatbeltUpdated = false;
bool featureVehSpeedBoost = false;
bool featureVehWrapInSpawned = false;
bool featureWorldMoonGravity = false;
bool featureWorldRandomCops = true;
bool featureWorldRandomTrains = true;
bool featureWorldRandomBoats = true;
bool featureWorldGarbageTrucks = true;
bool featureTimePaused = false;
bool featureTimePausedUpdated = false;
bool featureTimeSynced = false;
bool featureWeatherWind = false;
bool featureWeatherPers = false;
bool featureMiscLockRadio = false;
bool featureMiscHideHud = false;
void checkPlayerModel()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (!ENTITY::DOES_ENTITY_EXIST(playerPed))
		return;
	Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);
	if (ENTITY::IS_ENTITY_DEAD(playerPed) || PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE))
		if (model != GAMEPLAY::GET_HASH_KEY("player_zero") &&
				model != GAMEPLAY::GET_HASH_KEY("player_one") &&
				model != GAMEPLAY::GET_HASH_KEY("player_two"))
		{
			setStatusText("Turning To Normal!");
			WAIT(1000);
			model = GAMEPLAY::GET_HASH_KEY("player_zero");
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				WAIT(0);
			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			while (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE))
				WAIT(0);
		}
}
void updateVehicleGuns()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !featureWeaponVehRockets)
		return;
	bool bSelect = IsKeyDown(0x6B);
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
			PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);
		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}
		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();
	}
}
bool skinchangerUsed = false;
void updateFeatures()
{
	updateStatusText();
	updateVehicleGuns();
	if (skinchangerUsed)
		checkPlayerModel();
	if (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), TRUE))
	{
		WAIT(0);
		return;
	}
	featureWorldRandomCops = PED::CAN_CREATE_RANDOM_COPS() == TRUE;
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);
	if (featurePlayerInvincibleUpdated)
	{
		if (bPlayerExists && !featurePlayerInvincible)
			PLAYER::SET_PLAYER_INVINCIBLE(player, FALSE);
		featurePlayerInvincibleUpdated = false;
	}
	if (featurePlayerInvincible)
	{
		if (bPlayerExists)
			PLAYER::SET_PLAYER_INVINCIBLE(player, TRUE);
	}
	if (featurePlayerNeverWanted)
	{
		if (bPlayerExists)
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
	}
	if (featurePlayerIgnoredUpdated)
	{
		if (bPlayerExists)
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, featurePlayerIgnored);
		featurePlayerIgnoredUpdated = false;
	}
	if (featurePlayerUnlimitedAbility)
	{
		if (bPlayerExists)
			PLAYER::SPECIAL_ABILITY_FILL_METER(player, 1);
	}
	if (featurePlayerNoNoiseUpdated)
	{
		if (bPlayerExists && !featurePlayerNoNoise)
			PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 1.0);
		featurePlayerNoNoiseUpdated = false;
	}
	if (featurePlayerNoNoise)
		PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 0.0);
	if (featurePlayerFastSwimUpdated)
	{
		if (bPlayerExists && !featurePlayerFastSwim)
			PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.0);
		featurePlayerFastSwimUpdated = false;
	}
	if (featurePlayerFastSwim)
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.49);
	if (featurePlayerFastRunUpdated)
	{
		if (bPlayerExists && !featurePlayerFastRun)
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.0);
		featurePlayerFastRunUpdated = false;
	}
	if (featurePlayerFastRun)
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49);
	if (featurePlayerSuperJump)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}
	if (featureWeaponFireAmmo)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponExplosiveAmmo)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponExplosiveMelee)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}
	if (bPlayerExists && featureWeaponNoReload)
	{
		Hash cur;
		if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &cur, 1))
		{
			if (WEAPON::IS_WEAPON_VALID(cur))
			{
				int maxAmmo;
				if (WEAPON::GET_MAX_AMMO(playerPed, cur, &maxAmmo))
				{
					WEAPON::SET_PED_AMMO(playerPed, cur, maxAmmo);
					maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, cur, 1);
					if (maxAmmo > 0)
						WEAPON::SET_AMMO_IN_CLIP(playerPed, cur, maxAmmo);
				}
			}
		}
	}
	if (featureVehInvincibleUpdated)
	{
		if (bPlayerExists && !featureVehInvincible && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
			ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
		}
		featureVehInvincibleUpdated = false;
	}
	if (featureVehInvincible)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, TRUE);
			ENTITY::SET_ENTITY_PROOFS(veh, 1, 1, 1, 1, 1, 1, 1, 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
		}
	}
	if (featureVehInvincibleWheelsUpdated)
	{
		if (bPlayerExists && !featureVehInvincibleWheels && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, TRUE);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, TRUE);
			VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(veh, FALSE);
		}
		featureVehInvincibleWheelsUpdated = false;
	}
	if (featureVehInvincibleWheels)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, FALSE);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, FALSE);
			VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(veh, TRUE);
		}
	}
	const int PED_FLAG_CAN_FLY_THRU_WINDSCREEN = 32;
	if (featureVehSeatbeltUpdated)
	{
		if (bPlayerExists && !featureVehSeatbelt)
			PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, TRUE);
		featureVehSeatbeltUpdated = false;
	}
	if (featureVehSeatbelt)
	{
		if (bPlayerExists)
		{
			if (PED::GET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, TRUE))
				PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, FALSE);
		}
	}
	if (featureVehSpeedBoost && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);
		bool bUp = IsKeyDown(VK_NUMPAD9);
		bool bDown = IsKeyDown(VK_NUMPAD3);
		if (bUp || bDown)
		{
			float speed = ENTITY::GET_ENTITY_SPEED(veh);
			if (bUp)
			{
				if (speed < 3.0f)
					speed = 3.0f;
				speed += speed * 0.05f;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
			}
			else if (ENTITY::IS_ENTITY_IN_AIR(veh) || speed > 5.0)
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0);
		}
	}
	if (featureTimePausedUpdated)
	{
		TIME::PAUSE_CLOCK(featureTimePaused);
		featureTimePausedUpdated = false;
	}
	if (featureTimeSynced)
	{
		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);
		TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
	}
	if (featureMiscHideHud)
		UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
}
LPCSTR pedModels[67][10] = {
		{"player_zero", "player_one", "player_two", "a_c_boar", "a_c_chimp", "a_c_cow", "a_c_coyote", "a_c_deer", "a_c_fish", "a_c_hen"},
		{"a_c_cat_01", "a_c_chickenhawk", "a_c_cormorant", "a_c_crow", "a_c_dolphin", "a_c_humpback", "a_c_killerwhale", "a_c_pigeon", "a_c_seagull", "a_c_sharkhammer"},
		{"a_c_pig", "a_c_rat", "a_c_rhesus", "a_c_chop", "a_c_husky", "a_c_mtlion", "a_c_retriever", "a_c_sharktiger", "a_c_shepherd", "s_m_m_movalien_01"},
		{"a_f_m_beach_01", "a_f_m_bevhills_01", "a_f_m_bevhills_02", "a_f_m_bodybuild_01", "a_f_m_business_02", "a_f_m_downtown_01", "a_f_m_eastsa_01", "a_f_m_eastsa_02", "a_f_m_fatbla_01", "a_f_m_fatcult_01"},
		{"a_f_m_fatwhite_01", "a_f_m_ktown_01", "a_f_m_ktown_02", "a_f_m_prolhost_01", "a_f_m_salton_01", "a_f_m_skidrow_01", "a_f_m_soucentmc_01", "a_f_m_soucent_01", "a_f_m_soucent_02", "a_f_m_tourist_01"},
		{"a_f_m_trampbeac_01", "a_f_m_tramp_01", "a_f_o_genstreet_01", "a_f_o_indian_01", "a_f_o_ktown_01", "a_f_o_salton_01", "a_f_o_soucent_01", "a_f_o_soucent_02", "a_f_y_beach_01", "a_f_y_bevhills_01"},
		{"a_f_y_bevhills_02", "a_f_y_bevhills_03", "a_f_y_bevhills_04", "a_f_y_business_01", "a_f_y_business_02", "a_f_y_business_03", "a_f_y_business_04", "a_f_y_eastsa_01", "a_f_y_eastsa_02", "a_f_y_eastsa_03"},
		{"a_f_y_epsilon_01", "a_f_y_fitness_01", "a_f_y_fitness_02", "a_f_y_genhot_01", "a_f_y_golfer_01", "a_f_y_hiker_01", "a_f_y_hippie_01", "a_f_y_hipster_01", "a_f_y_hipster_02", "a_f_y_hipster_03"},
		{"a_f_y_hipster_04", "a_f_y_indian_01", "a_f_y_juggalo_01", "a_f_y_runner_01", "a_f_y_rurmeth_01", "a_f_y_scdressy_01", "a_f_y_skater_01", "a_f_y_soucent_01", "a_f_y_soucent_02", "a_f_y_soucent_03"},
		{"a_f_y_tennis_01", "a_f_y_topless_01", "a_f_y_tourist_01", "a_f_y_tourist_02", "a_f_y_vinewood_01", "a_f_y_vinewood_02", "a_f_y_vinewood_03", "a_f_y_vinewood_04", "a_f_y_yoga_01", "a_m_m_acult_01"},
		{"a_m_m_afriamer_01", "a_m_m_beach_01", "a_m_m_beach_02", "a_m_m_bevhills_01", "a_m_m_bevhills_02", "a_m_m_business_01", "a_m_m_eastsa_01", "a_m_m_eastsa_02", "a_m_m_farmer_01", "a_m_m_fatlatin_01"},
		{"a_m_m_genfat_01", "a_m_m_genfat_02", "a_m_m_golfer_01", "a_m_m_hasjew_01", "a_m_m_hillbilly_01", "a_m_m_hillbilly_02", "a_m_m_indian_01", "a_m_m_ktown_01", "a_m_m_malibu_01", "a_m_m_mexcntry_01"},
		{"a_m_m_mexlabor_01", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_m_prolhost_01", "a_m_m_rurmeth_01", "a_m_m_salton_01", "a_m_m_salton_02", "a_m_m_salton_03", "a_m_m_salton_04"},
		{"a_m_m_skater_01", "a_m_m_skidrow_01", "a_m_m_socenlat_01", "a_m_m_soucent_01", "a_m_m_soucent_02", "a_m_m_soucent_03", "a_m_m_soucent_04", "a_m_m_stlat_02", "a_m_m_tennis_01", "a_m_m_tourist_01"},
		{"a_m_m_trampbeac_01", "a_m_m_tramp_01", "a_m_m_tranvest_01", "a_m_m_tranvest_02", "a_m_o_acult_01", "a_m_o_acult_02", "a_m_o_beach_01", "a_m_o_genstreet_01", "a_m_o_ktown_01", "a_m_o_salton_01"},
		{"a_m_o_soucent_01", "a_m_o_soucent_02", "a_m_o_soucent_03", "a_m_o_tramp_01", "a_m_y_acult_01", "a_m_y_acult_02", "a_m_y_beachvesp_01", "a_m_y_beachvesp_02", "a_m_y_beach_01", "a_m_y_beach_02"},
		{"a_m_y_beach_03", "a_m_y_bevhills_01", "a_m_y_bevhills_02", "a_m_y_breakdance_01", "a_m_y_busicas_01", "a_m_y_business_01", "a_m_y_business_02", "a_m_y_business_03", "a_m_y_cyclist_01", "a_m_y_dhill_01"},
		{"a_m_y_downtown_01", "a_m_y_eastsa_01", "a_m_y_eastsa_02", "a_m_y_epsilon_01", "a_m_y_epsilon_02", "a_m_y_gay_01", "a_m_y_gay_02", "a_m_y_genstreet_01", "a_m_y_genstreet_02", "a_m_y_golfer_01"},
		{"a_m_y_hasjew_01", "a_m_y_hiker_01", "a_m_y_hippy_01", "a_m_y_hipster_01", "a_m_y_hipster_02", "a_m_y_hipster_03", "a_m_y_indian_01", "a_m_y_jetski_01", "a_m_y_juggalo_01", "a_m_y_ktown_01"},
		{"a_m_y_ktown_02", "a_m_y_latino_01", "a_m_y_methhead_01", "a_m_y_mexthug_01", "a_m_y_motox_01", "a_m_y_motox_02", "a_m_y_musclbeac_01", "a_m_y_musclbeac_02", "a_m_y_polynesian_01", "a_m_y_roadcyc_01"},
		{"a_m_y_runner_01", "a_m_y_runner_02", "a_m_y_salton_01", "a_m_y_skater_01", "a_m_y_skater_02", "a_m_y_soucent_01", "a_m_y_soucent_02", "a_m_y_soucent_03", "a_m_y_soucent_04", "a_m_y_stbla_01"},
		{"a_m_y_stbla_02", "a_m_y_stlat_01", "a_m_y_stwhi_01", "a_m_y_stwhi_02", "a_m_y_sunbathe_01", "a_m_y_surfer_01", "a_m_y_vindouche_01", "a_m_y_vinewood_01", "a_m_y_vinewood_02", "a_m_y_vinewood_03"},
		{"a_m_y_vinewood_04", "a_m_y_yoga_01", "u_m_y_proldriver_01", "u_m_y_rsranger_01", "u_m_y_sbike", "u_m_y_staggrm_01", "u_m_y_tattoo_01", "csb_abigail", "csb_anita", "csb_anton"},
		{"csb_ballasog", "csb_bride", "csb_burgerdrug", "csb_car3guy1", "csb_car3guy2", "csb_chef", "csb_chin_goon", "csb_cletus", "csb_cop", "csb_customer"},
		{"csb_denise_friend", "csb_fos_rep", "csb_g", "csb_groom", "csb_grove_str_dlr", "csb_hao", "csb_hugh", "csb_imran", "csb_janitor", "csb_maude"},
		{"csb_mweather", "csb_ortega", "csb_oscar", "csb_porndudes", "csb_porndudes_p", "csb_prologuedriver", "csb_prolsec", "csb_ramp_gang", "csb_ramp_hic", "csb_ramp_hipster"},
		{"csb_ramp_marine", "csb_ramp_mex", "csb_reporter", "csb_roccopelosi", "csb_screen_writer", "csb_stripper_01", "csb_stripper_02", "csb_tonya", "csb_trafficwarden", "cs_amandatownley"},
		{"cs_andreas", "cs_ashley", "cs_bankman", "cs_barry", "cs_barry_p", "cs_beverly", "cs_beverly_p", "cs_brad", "cs_bradcadaver", "cs_carbuyer"},
		{"cs_casey", "cs_chengsr", "cs_chrisformage", "cs_clay", "cs_dale", "cs_davenorton", "cs_debra", "cs_denise", "cs_devin", "cs_dom"},
		{"cs_dreyfuss", "cs_drfriedlander", "cs_fabien", "cs_fbisuit_01", "cs_floyd", "cs_guadalope", "cs_gurk", "cs_hunter", "cs_janet", "cs_jewelass"},
		{"cs_jimmyboston", "cs_jimmydisanto", "cs_joeminuteman", "cs_johnnyklebitz", "cs_josef", "cs_josh", "cs_lamardavis", "cs_lazlow", "cs_lestercrest", "cs_lifeinvad_01"},
		{"cs_magenta", "cs_manuel", "cs_marnie", "cs_martinmadrazo", "cs_maryann", "cs_michelle", "cs_milton", "cs_molly", "cs_movpremf_01", "cs_movpremmale"},
		{"cs_mrk", "cs_mrsphillips", "cs_mrs_thornhill", "cs_natalia", "cs_nervousron", "cs_nigel", "cs_old_man1a", "cs_old_man2", "cs_omega", "cs_orleans"},
		{"cs_paper", "cs_paper_p", "cs_patricia", "cs_priest", "cs_prolsec_02", "cs_russiandrunk", "cs_siemonyetarian", "cs_solomon", "cs_stevehains", "cs_stretch"},
		{"cs_tanisha", "cs_taocheng", "cs_taostranslator", "cs_tenniscoach", "cs_terry", "cs_tom", "cs_tomepsilon", "cs_tracydisanto", "cs_wade", "cs_zimbor"},
		{"g_f_y_ballas_01", "g_f_y_families_01", "g_f_y_lost_01", "g_f_y_vagos_01", "g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_m_armlieut_01", "g_m_m_chemwork_01", "g_m_m_chemwork_01_p", "g_m_m_chiboss_01"},
		{"g_m_m_chiboss_01_p", "g_m_m_chicold_01", "g_m_m_chicold_01_p", "g_m_m_chigoon_01", "g_m_m_chigoon_01_p", "g_m_m_chigoon_02", "g_m_m_korboss_01", "g_m_m_mexboss_01", "g_m_m_mexboss_02", "g_m_y_armgoon_02"},
		{"g_m_y_azteca_01", "g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_m_y_korean_01", "g_m_y_korean_02", "g_m_y_korlieut_01"},
		{"g_m_y_lost_01", "g_m_y_lost_02", "g_m_y_lost_03", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_mexgoon_02", "g_m_y_mexgoon_03", "g_m_y_mexgoon_03_p", "g_m_y_pologoon_01", "g_m_y_pologoon_01_p"},
		{"g_m_y_pologoon_02", "g_m_y_pologoon_02_p", "g_m_y_salvaboss_01", "g_m_y_salvagoon_01", "g_m_y_salvagoon_02", "g_m_y_salvagoon_03", "g_m_y_salvagoon_03_p", "g_m_y_strpunk_01", "g_m_y_strpunk_02", "hc_driver"},
		{"hc_gunman", "hc_hacker", "ig_abigail", "ig_amandatownley", "ig_andreas", "ig_ashley", "ig_ballasog", "ig_bankman", "ig_barry", "ig_barry_p"},
		{"ig_bestmen", "ig_beverly", "ig_beverly_p", "ig_brad", "ig_bride", "ig_car3guy1", "ig_car3guy2", "ig_casey", "ig_chef", "ig_chengsr"},
		{"ig_chrisformage", "ig_clay", "ig_claypain", "ig_cletus", "ig_dale", "ig_davenorton", "ig_denise", "ig_devin", "ig_dom", "ig_dreyfuss"},
		{"ig_drfriedlander", "ig_fabien", "ig_fbisuit_01", "ig_floyd", "ig_groom", "ig_hao", "ig_hunter", "ig_janet", "ig_jay_norris", "ig_jewelass"},
		{"ig_jimmyboston", "ig_jimmydisanto", "ig_joeminuteman", "ig_johnnyklebitz", "ig_josef", "ig_josh", "ig_kerrymcintosh", "ig_lamardavis", "ig_lazlow", "ig_lestercrest"},
		{"ig_lifeinvad_01", "ig_lifeinvad_02", "ig_magenta", "ig_manuel", "ig_marnie", "ig_maryann", "ig_maude", "ig_michelle", "ig_milton", "ig_molly"},
		{"ig_mrk", "ig_mrsphillips", "ig_mrs_thornhill", "ig_natalia", "ig_nervousron", "ig_nigel", "ig_old_man1a", "ig_old_man2", "ig_omega", "ig_oneil"},
		{"ig_orleans", "ig_ortega", "ig_paper", "ig_patricia", "ig_priest", "ig_prolsec_02", "ig_ramp_gang", "ig_ramp_hic", "ig_ramp_hipster", "ig_ramp_mex"},
		{"ig_roccopelosi", "ig_russiandrunk", "ig_screen_writer", "ig_siemonyetarian", "ig_solomon", "ig_stevehains", "ig_stretch", "ig_talina", "ig_tanisha", "ig_taocheng"},
		{"ig_taostranslator", "ig_taostranslator_p", "ig_tenniscoach", "ig_terry", "ig_tomepsilon", "ig_tonya", "ig_tracydisanto", "ig_trafficwarden", "ig_tylerdix", "ig_wade"},
		{"ig_zimbor", "mp_f_deadhooker", "mp_f_freemode_01", "mp_f_misty_01", "mp_f_stripperlite", "mp_g_m_pros_01", "mp_headtargets", "mp_m_claude_01", "mp_m_exarmy_01", "mp_m_famdd_01"},
		{"mp_m_fibsec_01", "mp_m_freemode_01", "mp_m_marston_01", "mp_m_niko_01", "mp_m_shopkeep_01", "mp_s_m_armoured_01", "s_f_m_fembarber", "s_f_m_maid_01", "s_f_m_shop_high", "s_f_m_sweatshop_01"},
		{"s_f_y_airhostess_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_f_y_cop_01", "s_f_y_factory_01", "s_f_y_hooker_01", "s_f_y_hooker_02", "s_f_y_hooker_03", "s_f_y_migrant_01", "s_f_y_movprem_01"},
		{"s_f_y_ranger_01", "s_f_y_scrubs_01", "s_f_y_sheriff_01", "s_f_y_shop_low", "s_f_y_shop_mid", "s_f_y_stripperlite", "s_f_y_stripper_01", "s_f_y_stripper_02", "s_f_y_sweatshop_01", "s_m_m_ammucountry"},
		{"s_m_m_armoured_01", "s_m_m_armoured_02", "s_m_m_autoshop_01", "s_m_m_autoshop_02", "s_m_m_bouncer_01", "s_m_m_chemsec_01", "s_m_m_ciasec_01", "s_m_m_cntrybar_01", "s_m_m_dockwork_01", "s_m_m_doctor_01"},
		{"s_m_m_fiboffice_01", "s_m_m_fiboffice_02", "s_m_m_gaffer_01", "s_m_m_gardener_01", "s_m_m_gentransport", "s_m_m_hairdress_01", "s_m_m_highsec_01", "s_m_m_highsec_02", "s_m_m_janitor", "s_m_m_lathandy_01"},
		{"s_m_m_lifeinvad_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_m_m_mariachi_01", "s_m_m_marine_01", "s_m_m_marine_02", "s_m_m_migrant_01", "u_m_y_zombie_01", "s_m_m_movprem_01", "s_m_m_movspace_01"},
		{"s_m_m_paramedic_01", "s_m_m_pilot_01", "s_m_m_pilot_02", "s_m_m_postal_01", "s_m_m_postal_02", "s_m_m_prisguard_01", "s_m_m_scientist_01", "s_m_m_security_01", "s_m_m_snowcop_01", "s_m_m_strperf_01"},
		{"s_m_m_strpreach_01", "s_m_m_strvend_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_m_ups_02", "s_m_o_busker_01", "s_m_y_airworker", "s_m_y_ammucity_01", "s_m_y_armymech_01", "s_m_y_autopsy_01"},
		{"s_m_y_barman_01", "s_m_y_baywatch_01", "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_y_busboy_01", "s_m_y_chef_01", "s_m_y_clown_01", "s_m_y_construct_01", "s_m_y_construct_02", "s_m_y_cop_01"},
		{"s_m_y_dealer_01", "s_m_y_devinsec_01", "s_m_y_dockwork_01", "s_m_y_doorman_01", "s_m_y_dwservice_01", "s_m_y_dwservice_02", "s_m_y_factory_01", "s_m_y_fireman_01", "s_m_y_garbage", "s_m_y_grip_01"},
		{"s_m_y_hwaycop_01", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03", "s_m_y_mime", "s_m_y_pestcont_01", "s_m_y_pilot_01", "s_m_y_prismuscl_01", "s_m_y_prisoner_01", "s_m_y_ranger_01"},
		{"s_m_y_robber_01", "s_m_y_sheriff_01", "s_m_y_shop_mask", "s_m_y_strvend_01", "s_m_y_swat_01", "s_m_y_uscg_01", "s_m_y_valet_01", "s_m_y_waiter_01", "s_m_y_winclean_01", "s_m_y_xmech_01"},
		{"s_m_y_xmech_02", "u_f_m_corpse_01", "u_f_m_miranda", "u_f_m_promourn_01", "u_f_o_moviestar", "u_f_o_prolhost_01", "u_f_y_bikerchic", "u_f_y_comjane", "u_f_y_corpse_01", "u_f_y_corpse_02"},
		{"u_f_y_hotposh_01", "u_f_y_jewelass_01", "u_f_y_mistress", "u_f_y_poppymich", "u_f_y_princess", "u_f_y_spyactress", "u_m_m_aldinapoli", "u_m_m_bankman", "u_m_m_bikehire_01", "u_m_m_fibarchitect"},
		{"u_m_m_filmdirector", "u_m_m_glenstank_01", "u_m_m_griff_01", "u_m_m_jesus_01", "u_m_m_jewelsec_01", "u_m_m_jewelthief", "u_m_m_markfost", "u_m_m_partytarget", "u_m_m_prolsec_01", "u_m_m_promourn_01"},
		{"u_m_m_rivalpap", "u_m_m_spyactor", "u_m_m_willyfist", "u_m_o_finguru_01", "u_m_o_taphillbilly", "u_m_o_tramp_01", "u_m_y_abner", "u_m_y_antonb", "u_m_y_babyd", "u_m_y_baygor"},
		{"u_m_y_burgerdrug_01", "u_m_y_chip", "u_m_y_cyclist_01", "u_m_y_fibmugger_01", "u_m_y_guido_01", "u_m_y_gunvend_01", "u_m_y_hippie_01", "u_m_y_imporage", "u_m_y_justin", "u_m_y_mani"},
		{"u_m_y_militarybum", "u_m_y_paparazzi", "u_m_y_party_01", "u_m_y_pogo_01", "u_m_y_prisoner_01", "ig_benny", "ig_g", "ig_vagspeak", "mp_m_g_vagfun_01", "mp_m_boatstaff_01"},
		{"mp_f_boatstaff_01", "", "", "", "", "", "", "", "", ""}};
LPCSTR pedModelNames[67][10] = {
		{"Michael", "Franklin", "Trevor", "Boar", "Chimp", "Cow", "Coyote", "Deer", "Fish", "Hen"},
		{"Cat", "Hawk", "Cormorant", "Crow", "Dolphin", "Humpback", "Whale", "Pigeon", "Seagull", "Sharkhammer"},
		{"Pig", "Rat", "Rhesus", "Chop", "Husky", "Mtlion", "Retriever", "Sharktiger", "Shepherd", "Alien"},
		{"Beach", "Bevhills", "Bevhills", "Bodybuild", "Business", "Downtown", "Eastsa", "Eastsa", "Fatbla", "Fatcult"},
		{"Fatwhite", "Ktown", "Ktown", "Prolhost", "Salton", "Skidrow", "Soucentmc", "Soucent", "Soucent", "Tourist"},
		{"Trampbeac", "Tramp", "Genstreet", "Indian", "Ktown", "Salton", "Soucent", "Soucent", "Beach", "Bevhills"},
		{"Bevhills", "Bevhills", "Bevhills", "Business", "Business", "Business", "Business", "Eastsa", "Eastsa", "Eastsa"},
		{"Epsilon", "Fitness", "Fitness", "Genhot", "Golfer", "Hiker", "Hippie", "Hipster", "Hipster", "Hipster"},
		{"Hipster", "Indian", "Juggalo", "Runner", "Rurmeth", "Scdressy", "Skater", "Soucent", "Soucent", "Soucent"},
		{"Tennis", "Topless", "Tourist", "Tourist", "Vinewood", "Vinewood", "Vinewood", "Vinewood", "Yoga", "Acult"},
		{"Afriamer", "Beach", "Beach", "Bevhills", "Bevhills", "Business", "Eastsa", "Eastsa", "Farmer", "Fatlatin"},
		{"Genfat", "Genfat", "Golfer", "Hasjew", "Hillbilly", "Hillbilly", "Indian", "Ktown", "Malibu", "Mexcntry"},
		{"Mexlabor", "OgBoss", "Paparazzi", "Polynesian", "Prolhost", "Rurmeth", "Salton", "Salton", "Salton", "Salton"},
		{"Skater", "Skidrow", "Socenlat", "Soucent", "Soucent", "Soucent", "Soucent", "Stlat", "Tennis", "Tourist"},
		{"Trampbeac", "Tramp", "Tranvest", "Tranvest", "Acult", "Acult", "Beach", "Genstreet", "Ktown", "Salton"},
		{"Soucent", "Soucent", "Soucent", "Tramp", "Acult", "Acult", "Beachvesp", "Beachvesp", "Beach", "Beach"},
		{"Beach", "Bevhills", "Bevhills", "Breakdance", "Busicas", "Business", "Business", "Business", "Cyclist", "Dhill"},
		{"Downtown", "Eastsa", "Eastsa", "Epsilon", "Epsilon", "Gay", "Gay", "Genstreet", "Genstreet", "Golfer"},
		{"Hasjew", "Hiker", "Hippy", "Hipster", "Hipster", "Hipster", "Indian", "Jetski", "Juggalo", "Ktown"},
		{"Ktown", "Latino", "Methhead", "Mexthug", "Motox", "Motox", "Musclbeac", "Musclbeac", "Polynesian", "Roadcyc"},
		{"Runner", "Runner", "Salton", "Skater", "Skater", "Soucent", "Soucent", "Soucent", "Soucent", "Stbla"},
		{"Stbla", "Stlat", "Stwhi", "Stwhi", "Sunbathe", "Surfer", "Vindouche", "Vinewood", "Vinewood", "Vinewood"},
		{"Vinewood", "Yoga", "Proldriver", "Rsranger", "Sbike", "Staggrm", "Tattoo", "Abigail", "Anita", "Anton"},
		{"Ballasog", "Bride", "Burgerdrug", "Car3guy1", "Car3guy2", "Chef", "ChinGoon", "Cletus", "Cop", "Customer"},
		{"DeniseFriend", "FosRep", "G", "Groom", "Dlr", "Hao", "Hugh", "Imran", "Janitor", "Maude"},
		{"Mweather", "Ortega", "Oscar", "Porndudes", "PorndudesP", "Prologuedriver", "Prolsec", "Gang", "Hic", "Hipster"},
		{"Marine", "Mex", "Reporter", "Roccopelosi", "ScreenWriter", "Stripper", "Stripper", "Tonya", "Trafficwarden", "AmandaTownley"},
		{"Andreas", "Ashley", "Bankman", "Barry", "BarryP", "Beverly", "BeverlyP", "Brad", "Bradcadaver", "Carbuyer"},
		{"Casey", "Chengsr", "ChrisFormage", "Clay", "Dale", "DaveNorton", "Debra", "Denise", "Devin", "Dom"},
		{"Dreyfuss", "DrFriedlander", "Fabien", "Fbisuit", "Floyd", "Guadalope", "Gurk", "Hunter", "Janet", "Jewelass"},
		{"JimmyBoston", "JimmyDisanto", "JoeMinuteman", "JohnnyKlebitz", "Josef", "Josh", "LamarDavis", "Lazlow", "LesterCrest", "Lifeinvad"},
		{"Magenta", "Manuel", "Marnie", "MartinMadrazo", "Maryann", "Michelle", "Milton", "Molly", "Movpremf", "Movpremmale"},
		{"Mrk", "MrsPhillips", "MrsThornhill", "Natalia", "Nervousron", "Nigel", "OldMan1a", "OldMan2", "Omega", "Orleans"},
		{"Paper", "PaperP", "Patricia", "Priest", "Prolsec", "Russiandrunk", "Siemonyetarian", "Solomon", "SteveHains", "Stretch"},
		{"Tanisha", "Taocheng", "Taostranslator", "Tenniscoach", "Terry", "Tom", "Tomepsilon", "TracyDisanto", "Wade", "Zimbor"},
		{"Ballas", "Families", "Lost", "Vagos", "Armboss", "Armgoon", "Armlieut", "Chemwork", "ChemworkP", "Chiboss"},
		{"ChibossP", "Chicold", "ChicoldP", "Chigoon", "ChigoonP", "Chigoon", "Korboss", "Mexboss", "Mexboss", "Armgoon"},
		{"Azteca", "Ballaeast", "Ballaorig", "Ballasout", "Famca", "Famdnf", "Famfor", "Korean", "Korean", "Korlieut"},
		{"Lost", "Lost", "Lost", "Mexgang", "Mexgoon", "Mexgoon", "Mexgoon", "MexgoonP", "Pologoon", "PologoonP"},
		{"Pologoon", "PologoonP", "Salvaboss", "Salvagoon", "Salvagoon", "Salvagoon", "SalvagoonP", "Strpunk", "Strpunk", "HcDriver"},
		{"HcGunman", "HcHacker", "Abigail", "AmandaTownley", "Andreas", "Ashley", "Ballasog", "Bankman", "Barry", "BarryP"},
		{"Bestmen", "Beverly", "BeverlyP", "Brad", "Bride", "Car3guy1", "Car3guy2", "Casey", "Chef", "Chengsr"},
		{"ChrisFormage", "Clay", "Claypain", "Cletus", "Dale", "DaveNorton", "Denise", "Devin", "Dom", "Dreyfuss"},
		{"DrFriedlander", "Fabien", "Fbisuit", "Floyd", "Groom", "Hao", "Hunter", "Janet", "JayNorris", "Jewelass"},
		{"JimmyBoston", "JimmyDisanto", "JoeMinuteman", "JohnnyKlebitz", "Josef", "Josh", "KerryMcintosh", "LamarDavis", "Lazlow", "LesterCrest"},
		{"Lifeinvad", "Lifeinvad", "Magenta", "Manuel", "Marnie", "Maryann", "Maude", "Michelle", "Milton", "Molly"},
		{"Mrk", "MrsPhillips", "MrsThornhill", "Natalia", "Nervousron", "Nigel", "OldMan1a", "OldMan2", "Omega", "Oneil"},
		{"Orleans", "Ortega", "Paper", "Patricia", "Priest", "Prolsec", "Gang", "Hic", "Hipster", "Mex"},
		{"Roccopelosi", "Russiandrunk", "ScreenWriter", "Siemonyetarian", "Solomon", "SteveHains", "Stretch", "Talina", "Tanisha", "Taocheng"},
		{"Taostranslator", "TaostranslatorP", "Tenniscoach", "Terry", "Tomepsilon", "Tonya", "TracyDisanto", "Trafficwarden", "Tylerdix", "Wade"},
		{"Zimbor", "Deadhooker", "Freemode", "Misty", "Stripperlite", "Pros", "MpHeadtargets", "Claude", "Exarmy", "Famdd"},
		{"Fibsec", "Freemode", "Marston", "Niko", "Shopkeep", "Armoured", "Fembarber", "Maid", "ShopHigh", "Sweatshop"},
		{"Airhostess", "Bartender", "Baywatch", "Cop", "Factory", "Hooker", "Hooker", "Hooker", "Migrant", "Movprem"},
		{"Ranger", "Scrubs", "Sheriff", "ShopLow", "ShopMid", "Stripperlite", "Stripper", "Stripper", "Sweatshop", "Ammucountry"},
		{"Armoured", "Armoured", "Autoshop", "Autoshop", "Bouncer", "Chemsec", "Ciasec", "Cntrybar", "Dockwork", "Doctor"},
		{"Fiboffice", "Fiboffice", "Gaffer", "Gardener", "Gentransport", "Hairdress", "Highsec", "Highsec", "Janitor", "Lathandy"},
		{"Lifeinvad", "Linecook", "Lsmetro", "Mariachi", "Marine", "Marine", "Migrant", "Zombie", "Movprem", "Movspace"},
		{"Paramedic", "Pilot", "Pilot", "Postal", "Postal", "Prisguard", "Scientist", "Security", "Snowcop", "Strperf"},
		{"Strpreach", "Strvend", "Trucker", "Ups", "Ups", "Busker", "Airworker", "Ammucity", "Armymech", "Autopsy"},
		{"Barman", "Baywatch", "Blackops", "Blackops", "Busboy", "Chef", "Clown", "Construct", "Construct", "Cop"},
		{"Dealer", "Devinsec", "Dockwork", "Doorman", "Dwservice", "Dwservice", "Factory", "Fireman", "Garbage", "Grip"},
		{"Hwaycop", "Marine", "Marine", "Marine", "Mime", "Pestcont", "Pilot", "Prismuscl", "Prisoner", "Ranger"},
		{"Robber", "Sheriff", "ShopMask", "Strvend", "Swat", "Uscg", "Valet", "Waiter", "Winclean", "Xmech"},
		{"Xmech", "Corpse", "Miranda", "Promourn", "Moviestar", "Prolhost", "Bikerchic", "Comjane", "Corpse", "Corpse"},
		{"Hotposh", "Jewelass", "Mistress", "Poppymich", "Princess", "Spyactress", "Aldinapoli", "Bankman", "Bikehire", "Fibarchitect"},
		{"Filmdirector", "Glenstank", "Griff", "Jesus", "Jewelsec", "Jewelthief", "Markfost", "Partytarget", "Prolsec", "Promourn"},
		{"Rivalpap", "Spyactor", "Willyfist", "Finguru", "Taphillbilly", "Tramp", "Abner", "Antonb", "Babyd", "Baygor"},
		{"Burgerdrug", "Chip", "Cyclist", "Fibmugger", "Guido", "Gunvend", "Hippie", "Imporage", "Justin", "Mani"},
		{"Militarybum", "Paparazzi", "Party", "Pogo", "Prisoner", "Benny", "G", "Vagspeak", "Vagfun", "Boatstaff"},
		{"Femboatstaff", "", "", "", "", "", "", "", "", ""}};
int skinchangerActiveLineIndex = 0;
int skinchangerActiveItemIndex = 0;
bool processSkinchangerMenu()
{
	DWORD waitTime = 150;
	const int lineCount = 67;
	const int itemCount = 10;
	const int itemCountLastLine = 6;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			char caption[32];
			sprintf_s(caption, "Skin Changer %d / %d", skinchangerActiveLineIndex + 1, lineCount);
			drawMenuLine(caption, 350.0, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < itemCount; i++)
				if (strlen(pedModels[skinchangerActiveLineIndex][i]) || strcmp(pedModelNames[skinchangerActiveLineIndex][i], "NONE") == 0)
					drawMenuLine(pedModelNames[skinchangerActiveLineIndex][i], 100.0f, 5.0f, 200.0f, 100.0f + i * 110.0f, 5.0f, i == skinchangerActiveItemIndex, false, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
		if (bSelect)
		{
			menuBeep();
			DWORD model = GAMEPLAY::GET_HASH_KEY((char *)pedModels[skinchangerActiveLineIndex][skinchangerActiveItemIndex]);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model))
					WAIT(0);
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
				WAIT(0);
				for (int i = 0; i < 12; i++)
					for (int j = 0; j < 100; j++)
					{
						int drawable = rand() % 10;
						int texture = rand() % 10;
						if (PED::IS_PED_COMPONENT_VARIATION_VALID(PLAYER::PLAYER_PED_ID(), i, drawable, texture))
						{
							PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, drawable, texture, 0);
							break;
						}
					}
				skinchangerUsed = true;
				WAIT(100);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				waitTime = 200;
			}
		}
		else if (bBack)
		{
			menuBeep();
			break;
		}
		else if (bRight)
		{
			menuBeep();
			skinchangerActiveItemIndex++;
			int itemsMax = (skinchangerActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
			if (skinchangerActiveItemIndex == itemsMax)
				skinchangerActiveItemIndex = 0;
			waitTime = 100;
		}
		else if (bLeft)
		{
			menuBeep();
			if (skinchangerActiveItemIndex == 0)
				skinchangerActiveItemIndex = (skinchangerActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
			skinchangerActiveItemIndex--;
			waitTime = 100;
		}
		else if (bUp)
		{
			menuBeep();
			if (skinchangerActiveLineIndex == 0)
				skinchangerActiveLineIndex = lineCount;
			skinchangerActiveLineIndex--;
			waitTime = 200;
		}
		else if (bDown)
		{
			menuBeep();
			skinchangerActiveLineIndex++;
			if (skinchangerActiveLineIndex == lineCount)
				skinchangerActiveLineIndex = 0;
			waitTime = 200;
		}
		if (skinchangerActiveLineIndex == (lineCount - 1))
			if (skinchangerActiveItemIndex >= itemCountLastLine)
				skinchangerActiveItemIndex = 0;
	}
	return false;
}
int teleportActiveLineIndex = 0;
bool processTeleportMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 17;
	std::string caption = "Teleport";
	static struct
	{
		LPCSTR text;
		float x;
		float y;
		float z;
	} lines[lineCount] = {
			{"Marker"},
			{"Michael's House", -852.4f, 160.0f, 65.6f},
			{"Franklin's House", 7.9f, 548.1f, 175.5f},
			{"Trevor's Trailer", 1985.7f, 3812.2f, 32.2f},
			{"Airport Entrance", -1034.6f, -2733.6f, 13.8f},
			{"Airport Field", -1336.0f, -3044.0f, 13.9f},
			{"Elysian Island", 338.2f, -2715.9f, 38.5f},
			{"Jetsam", 760.4f, -2943.2f, 5.8f},
			{"Stripclub", 127.4f, -1307.7f, 29.2f},
			{"Elburro Heights", 1384.0f, -2057.1f, 52.0f},
			{"Ferris Wheel", -1670.7f, -1125.0f, 13.0f},
			{"Chumash", -3192.6f, 1100.0f, 20.2f},
			{"Windfarm", 2354.0f, 1830.3f, 101.1f},
			{"Military Base", -2047.4f, 3132.1f, 32.8f},
			{"Mckenzie Airfield", 2121.7f, 4796.3f, 41.1f},
			{"Desert Airfield", 1747.0f, 3273.7f, 41.1f},
			{"Chilliad", 425.4f, 5614.3f, 766.5f}};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != teleportActiveLineIndex)
					drawMenuLine(lines[i].text, lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lines[teleportActiveLineIndex].text, lineWidth + 1.0, 11.0, 56.0 + teleportActiveLineIndex * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			Entity e = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
				e = PED::GET_VEHICLE_PED_IS_USING(e);
			Vector3 coords;
			bool success = false;
			if (teleportActiveLineIndex == 0)
			{
				bool blipFound = false;
				int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
				for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
				{
					if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
					{
						coords = UI::GET_BLIP_INFO_ID_COORD(i);
						blipFound = true;
						break;
					}
				}
				if (blipFound)
				{
					bool groundFound = false;
					static float groundCheckHeight[] = {
							100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
							450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0};
					for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
					{
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
						WAIT(100);
						if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, FALSE))
						{
							groundFound = true;
							coords.z += 3.0;
							break;
						}
					}
					if (!groundFound)
					{
						coords.z = 1000.0;
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
					}
					success = true;
				}
				else
				{
					setStatusText("Map Marker Isn't Set!");
				}
			}
			else
			{
				coords.x = lines[teleportActiveLineIndex].x;
				coords.y = lines[teleportActiveLineIndex].y;
				coords.z = lines[teleportActiveLineIndex].z;
				success = true;
			}
			if (success)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
				WAIT(0);
				setStatusText("Teleported!");
				return true;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (teleportActiveLineIndex == 0)
				teleportActiveLineIndex = lineCount;
			teleportActiveLineIndex--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			teleportActiveLineIndex++;
			if (teleportActiveLineIndex == lineCount)
				teleportActiveLineIndex = 0;
			waitTime = 150;
		}
	}
	return false;
}
std::string lineAsStr(std::string text, bool *pState)
{
	while (text.size() < 18)
		text += " ";
	return text + (pState ? (*pState ? " ON" : " OFF") : "");
}
int activeLineIndexPlayer = 0;
void processPlayerMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 15;
	std::string caption = "Player";
	static struct
	{
		LPCSTR text;
		bool *pState;
		bool *pUpdated;
	} lines[lineCount] = {
			{"Skin Changer", NULL, NULL},
			{"Teleport", NULL, NULL},
			{"Fix Player", NULL, NULL},
			{"Reset Skin", NULL, NULL},
			{"Add Cash", NULL, NULL},
			{"Wanted Up", NULL, NULL},
			{"Wanted Down", NULL, NULL},
			{"Never Wanted", &featurePlayerNeverWanted, NULL},
			{"Invincible", &featurePlayerInvincible, &featurePlayerInvincibleUpdated},
			{"Police Ignored", &featurePlayerIgnored, &featurePlayerIgnoredUpdated},
			{"Unlimited Ability", &featurePlayerUnlimitedAbility, NULL},
			{"Noiseless", &featurePlayerNoNoise, &featurePlayerNoNoiseUpdated},
			{"Fast Swim", &featurePlayerFastSwim, &featurePlayerFastSwimUpdated},
			{"Fast Run", &featurePlayerFastRun, &featurePlayerFastRunUpdated},
			{"Super Jump", &featurePlayerSuperJump, NULL}};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexPlayer)
					drawMenuLine(lineAsStr(lines[i].text, lines[i].pState), lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineAsStr(lines[activeLineIndexPlayer].text, lines[activeLineIndexPlayer].pState), lineWidth + 1.0, 11.0, 56.0 + activeLineIndexPlayer * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
			Player player = PLAYER::PLAYER_ID();
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			switch (activeLineIndexPlayer)
			{
			case 0:
				if (processSkinchangerMenu())
					return;
				break;
			case 1:
				if (processTeleportMenu())
					return;
				break;
			case 2:
			{
				ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
				PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
				{
					Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
					if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
						VEHICLE::SET_VEHICLE_FIXED(playerVeh);
				}
				setStatusText("Player Fixed!");
			}
			break;
			case 3:
			{
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed);
				setStatusText("Using Default Model Skin!");
			}
			break;
			case 4:
				for (int i = 0; i < 3; i++)
				{
					char statNameFull[32];
					sprintf_s(statNameFull, "SP%d_TOTAL_CASH", i);
					Hash hash = GAMEPLAY::GET_HASH_KEY(statNameFull);
					int val;
					STATS::STAT_GET_INT(hash, &val, -1);
					val += 1000000;
					STATS::STAT_SET_INT(hash, val, 1);
				}
				setStatusText("Cash Added!");
				break;
			case 5:
				if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
				{
					PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, 0);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
					setStatusText("Wanted Up!");
				}
				break;
			case 6:
				if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) > 0)
				{
					PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) - 1, 0);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
					setStatusText("Wanted Down!");
				}
				break;
			default:
				if (lines[activeLineIndexPlayer].pState)
					*lines[activeLineIndexPlayer].pState = !(*lines[activeLineIndexPlayer].pState);
				if (lines[activeLineIndexPlayer].pUpdated)
					*lines[activeLineIndexPlayer].pUpdated = true;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexPlayer == 0)
				activeLineIndexPlayer = lineCount;
			activeLineIndexPlayer--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexPlayer++;
			if (activeLineIndexPlayer == lineCount)
				activeLineIndexPlayer = 0;
			waitTime = 150;
		}
	}
}
int activeLineIndexWeapon = 0;
void processWeaponMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 6;
	std::string caption = "Weapon";
	static struct
	{
		LPCSTR text;
		bool *pState;
		bool *pUpdated;
	} lines[lineCount] = {
			{"Get All Weapon", NULL, NULL},
			{"No Reload", &featureWeaponNoReload, NULL},
			{"Fire Ammo", &featureWeaponFireAmmo, NULL},
			{"Explosive Ammo", &featureWeaponExplosiveAmmo, NULL},
			{"Explosive Melee", &featureWeaponExplosiveMelee, NULL},
			{"Vehicle Rockets", &featureWeaponVehRockets, NULL}};
	static LPCSTR weaponNames[] = {
			"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
			"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
			"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
			"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
			"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
			"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
			"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
			"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
			"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
			"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN",
			"WEAPON_COMBATPDW", "WEAPON_KNUCKLE", "WEAPON_MARKSMANPISTOL",
			"WEAPON_FLASHLIGHT", "WEAPON_MACHETE", "WEAPON_MACHINEPISTOL",
			"WEAPON_SWITCHBLADE", "WEAPON_REVOLVER"};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWeapon)
					drawMenuLine(lineAsStr(lines[i].text, lines[i].pState), lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineAsStr(lines[activeLineIndexWeapon].text, lines[activeLineIndexWeapon].pState), lineWidth + 1.0, 11.0, 56.0 + activeLineIndexWeapon * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
			Player player = PLAYER::PLAYER_ID();
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			switch (activeLineIndexWeapon)
			{
			case 0:
				for (int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY((char *)weaponNames[i]), 1000, 0);
				setStatusText("All Weapon Added!");
				break;
			default:
				if (lines[activeLineIndexWeapon].pState)
					*lines[activeLineIndexWeapon].pState = !(*lines[activeLineIndexWeapon].pState);
				if (lines[activeLineIndexWeapon].pUpdated)
					*lines[activeLineIndexWeapon].pUpdated = true;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexWeapon == 0)
				activeLineIndexWeapon = lineCount;
			activeLineIndexWeapon--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexWeapon++;
			if (activeLineIndexWeapon == lineCount)
				activeLineIndexWeapon = 0;
			waitTime = 150;
		}
	}
}
LPCSTR vehicleModels[40][10] = {
		{"NINEF", "NINEF2", "BLISTA", "ASEA", "ASEA2", "BOATTRAILER", "BUS", "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2"},
		{"SUNTRAP", "COACH", "AIRBUS", "ASTEROPE", "AIRTUG", "AMBULANCE", "BARRACKS", "BARRACKS2", "BALLER", "BALLER2"},
		{"BJXL", "BANSHEE", "BENSON", "BFINJECTION", "BIFF", "BLAZER", "BLAZER2", "BLAZER3", "BISON", "BISON2"},
		{"BISON3", "BOXVILLE", "BOXVILLE2", "BOXVILLE3", "BOBCATXL", "BODHI2", "BUCCANEER", "BUFFALO", "BUFFALO2", "BULLDOZER"},
		{"BULLET", "BLIMP", "BURRITO", "BURRITO2", "BURRITO3", "BURRITO4", "BURRITO5", "CAVALCADE", "CAVALCADE2", "POLICET"},
		{"GBURRITO", "CABLECAR", "CADDY", "CADDY2", "CAMPER", "CARBONIZZARE", "CHEETAH", "COMET2", "COGCABRIO", "COQUETTE"},
		{"CUTTER", "GRESLEY", "DILETTANTE", "DILETTANTE2", "DUNE", "DUNE2", "HOTKNIFE", "DLOADER", "DUBSTA", "DUBSTA2"},
		{"DUMP", "RUBBLE", "DOCKTUG", "DOMINATOR", "EMPEROR", "EMPEROR2", "EMPEROR3", "ENTITYXF", "EXEMPLAR", "ELEGY2"},
		{"F620", "FBI", "FBI2", "FELON", "FELON2", "FELTZER2", "FIRETRUK", "FLATBED", "FORKLIFT", "FQ2"},
		{"FUSILADE", "FUGITIVE", "FUTO", "GRANGER", "GAUNTLET", "HABANERO", "HAULER", "HANDLER", "INFERNUS", "INGOT"},
		{"INTRUDER", "ISSI2", "JACKAL", "JOURNEY", "JB700", "KHAMELION", "LANDSTALKER", "LGUARD", "MANANA", "MESA"},
		{"MESA2", "MESA3", "CRUSADER", "MINIVAN", "MIXER", "MIXER2", "MONROE", "MOWER", "MULE", "MULE2"},
		{"ORACLE", "ORACLE2", "PACKER", "PATRIOT", "PBUS", "PENUMBRA", "PEYOTE", "PHANTOM", "PHOENIX", "PICADOR"},
		{"POUNDER", "POLICE", "POLICE4", "POLICE2", "POLICE3", "POLICEOLD1", "POLICEOLD2", "PONY", "PONY2", "PRAIRIE"},
		{"PRANGER", "PREMIER", "PRIMO", "PROPTRAILER", "RANCHERXL", "RANCHERXL2", "RAPIDGT", "RAPIDGT2", "RADI", "RATLOADER"},
		{"REBEL", "REGINA", "REBEL2", "RENTALBUS", "RUINER", "RUMPO", "RUMPO2", "RHINO", "RIOT", "RIPLEY"},
		{"ROCOTO", "ROMERO", "SABREGT", "SADLER", "SADLER2", "SANDKING", "SANDKING2", "SCHAFTER2", "SCHWARZER", "SCRAP"},
		{"SEMINOLE", "SENTINEL", "SENTINEL2", "ZION", "ZION2", "SERRANO", "SHERIFF", "SHERIFF2", "SPEEDO", "SPEEDO2"},
		{"STANIER", "STINGER", "STINGERGT", "STOCKADE", "STOCKADE3", "STRATUM", "SULTAN", "SUPERD", "SURANO", "SURFER"},
		{"SURFER2", "SURGE", "TACO", "TAILGATER", "TAXI", "TRASH", "TRACTOR", "TRACTOR2", "TRACTOR3", "GRAINTRAILER"},
		{"BALETRAILER", "TIPTRUCK", "TIPTRUCK2", "TORNADO", "TORNADO2", "TORNADO3", "TORNADO4", "TOURBUS", "TOWTRUCK", "TOWTRUCK2"},
		{"UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3", "VOODOO2", "WASHINGTON", "STRETCH", "YOUGA", "ZTYPE", "SANCHEZ", "SANCHEZ2"},
		{"SCORCHER", "TRIBIKE", "TRIBIKE2", "TRIBIKE3", "FIXTER", "CRUISER", "BMX", "POLICEB", "AKUMA", "CARBONRS"},
		{"BAGGER", "BATI", "BATI2", "RUFFIAN", "DAEMON", "DOUBLE", "PCJ", "VADER", "VIGERO", "FAGGIO2"},
		{"HEXER", "ANNIHILATOR", "BUZZARD", "BUZZARD2", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "SKYLIFT", "POLMAV", "MAVERICK"},
		{"NEMESIS", "FROGGER", "FROGGER2", "CUBAN800", "DUSTER", "STUNT", "MAMMATUS", "JET", "SHAMAL", "LUXOR"},
		{"TITAN", "LAZER", "CARGOPLANE", "SQUALO", "MARQUIS", "DINGHY", "DINGHY2", "JETMAX", "PREDATOR", "TROPIC"},
		{"SEASHARK", "SEASHARK2", "SUBMERSIBLE", "TRAILERS", "TRAILERS2", "TRAILERS3", "TVTRAILER", "RAKETRAILER", "TANKER", "TRAILERLOGS"},
		{"TR2", "TR3", "TR4", "TRFLAT", "TRAILERSMALL", "VELUM", "ADDER", "VOLTIC", "VACCA", "BIFTA"},
		{"SPEEDER", "PARADISE", "KALAHARI", "JESTER", "TURISMOR", "VESTRA", "ALPHA", "HUNTLEY", "THRUST", "MASSACRO"},
		{"MASSACRO2", "ZENTORNO", "BLADE", "GLENDALE", "PANTO", "PIGALLE", "WARRENER", "RHAPSODY", "DUBSTA3", "MONSTER"},
		{"SOVEREIGN", "INNOVATION", "HAKUCHOU", "FUROREGT", "MILJET", "COQUETTE2", "BTYPE", "BUFFALO3", "DOMINATOR2", "GAUNTLET2"},
		{"MARSHALL", "DUKES", "DUKES2", "STALION", "STALION2", "BLISTA2", "BLISTA3", "DODO", "SUBMERSIBLE2", "HYDRA"},
		{"INSURGENT", "INSURGENT2", "TECHNICAL", "SAVAGE", "VALKYRIE", "KURUMA", "KURUMA2", "JESTER2", "CASCO", "VELUM2"},
		{"GUARDIAN", "ENDURO", "LECTRO", "SLAMVAN", "SLAMVAN2", "RATLOADER2", "SWIFT2", "LUXOR2", "FELTZER3", "OSIRIS"},
		{"VIRGO", "WINDSOR", "BESRA", "SWIFT", "BLIMP2", "VINDICATOR", "TORO", "T20", "COQUETTE3", "CHINO"},
		{"BRAWLER", "BUCCANEER2", "CHINO2", "FACTION", "FACTION2", "MOONBEAM", "MOONBEAM2", "PRIMO2", "VOODOO", "LURCHER"},
		{"BTYPE2", "BALLER3", "BALLER4", "BALLER5", "BALLER6", "CARGOBOB4", "COG55", "COG552", "COGNOSCENTI", "COGNOSCENTI2"},
		{"DINGHY4", "LIMO2", "MAMBA", "NIGHTSHADE", "SCHAFTER3", "SCHAFTER4", "SCHAFTER5", "SCHAFTER6", "SEASHARK3", "SPEEDER2"},
		{"SUPERVOLITO", "SUPERVOLITO2", "TORO2", "TROPIC2", "VALKYRIE2", "VERLIERER2", "TAMPA", "BANSHEE2", "SULTANRS", "BTYPE3"}};
int carspawnActiveLineIndex = 0;
int carspawnActiveItemIndex = 0;
bool processCarspawnMenu()
{
	DWORD waitTime = 150;
	const int lineCount = 40;
	const int itemCount = 10;
	const int itemCountLastLine = 10;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			char caption[32];
			sprintf_s(caption, "Car Spawner %d / %d", carspawnActiveLineIndex + 1, lineCount);
			drawMenuLine(caption, 350.0, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < itemCount; i++)
				if (strlen(vehicleModels[carspawnActiveLineIndex][i]))
					drawMenuLine(vehicleModels[carspawnActiveLineIndex][i], 100.0, 5.0, 200.0, 100.0 + i * 110.0, 5.0, i == carspawnActiveItemIndex, false, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
		if (bSelect)
		{
			menuBeep();
			LPCSTR modelName = vehicleModels[carspawnActiveLineIndex][carspawnActiveItemIndex];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char *)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model))
					WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
				if (featureVehWrapInSpawned)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}
				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
				char statusText[32];
				sprintf_s(statusText, "%s Spawned!", modelName);
				setStatusText(statusText);
				return true;
			}
		}
		else if (bBack)
		{
			menuBeep();
			break;
		}
		else if (bRight)
		{
			menuBeep();
			carspawnActiveItemIndex++;
			int itemsMax = (carspawnActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
			if (carspawnActiveItemIndex == itemsMax)
				carspawnActiveItemIndex = 0;
			waitTime = 100;
		}
		else if (bLeft)
		{
			menuBeep();
			if (carspawnActiveItemIndex == 0)
				carspawnActiveItemIndex = (carspawnActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
			carspawnActiveItemIndex--;
			waitTime = 100;
		}
		else if (bUp)
		{
			menuBeep();
			if (carspawnActiveLineIndex == 0)
				carspawnActiveLineIndex = lineCount;
			carspawnActiveLineIndex--;
			waitTime = 200;
		}
		else if (bDown)
		{
			menuBeep();
			carspawnActiveLineIndex++;
			if (carspawnActiveLineIndex == lineCount)
				carspawnActiveLineIndex = 0;
			waitTime = 200;
		}
		if (carspawnActiveLineIndex == (lineCount - 1))
			if (carspawnActiveItemIndex >= itemCountLastLine)
				carspawnActiveItemIndex = 0;
	}
	return false;
}
int activeLineIndexVeh = 0;
void processVehMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 8;
	std::string caption = "Vehicle";
	static struct
	{
		LPCSTR text;
		bool *pState;
		bool *pUpdated;
	} lines[lineCount] = {
			{"Car Spawner", NULL, NULL},
			{"Paint Random", NULL, NULL},
			{"Fix", NULL, NULL},
			{"Seat Belt", &featureVehSeatbelt, &featureVehSeatbeltUpdated},
			{"Wrap In Spawned", &featureVehWrapInSpawned, NULL},
			{"Invincible", &featureVehInvincible, &featureVehInvincibleUpdated},
			{"Strong Wheels", &featureVehInvincibleWheels, &featureVehInvincibleWheelsUpdated},
			{"Speed Boost", &featureVehSpeedBoost, NULL}};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexVeh)
					drawMenuLine(lineAsStr(lines[i].text, lines[i].pState), lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineAsStr(lines[activeLineIndexVeh].text, lines[activeLineIndexVeh].pState), lineWidth + 1.0, 11.0, 56.0 + activeLineIndexVeh * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
			Player player = PLAYER::PLAYER_ID();
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			switch (activeLineIndexVeh)
			{
			case 0:
				if (processCarspawnMenu())
					return;
				break;
			case 1:
				if (bPlayerExists)
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
						if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(veh))
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
					}
					else
					{
						setStatusText("Player Isn't In A Vehicle!");
					}
				}
				break;
			case 2:
				if (bPlayerExists)
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
						VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(playerPed));
					else
						setStatusText("Player Isn't In A Vehicle!");
				break;
			default:
				if (lines[activeLineIndexVeh].pState)
					*lines[activeLineIndexVeh].pState = !(*lines[activeLineIndexVeh].pState);
				if (lines[activeLineIndexVeh].pUpdated)
					*lines[activeLineIndexVeh].pUpdated = true;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexVeh == 0)
				activeLineIndexVeh = lineCount;
			activeLineIndexVeh--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexVeh++;
			if (activeLineIndexVeh == lineCount)
				activeLineIndexVeh = 0;
			waitTime = 150;
		}
	}
}
int activeLineIndexWorld = 0;
void processWorldMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 5;
	std::string caption = "World";
	static struct
	{
		LPCSTR text;
		bool *pState;
		bool *pUpdated;
	} lines[lineCount] = {
			{"Moon Gravity", &featureWorldMoonGravity, NULL},
			{"Random Cops", &featureWorldRandomCops, NULL},
			{"Random Trains", &featureWorldRandomTrains, NULL},
			{"Random Boats", &featureWorldRandomBoats, NULL},
			{"Garbage Trucks", &featureWorldGarbageTrucks, NULL}};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWorld)
					drawMenuLine(lineAsStr(lines[i].text, lines[i].pState), lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineAsStr(lines[activeLineIndexWorld].text, lines[activeLineIndexWorld].pState), lineWidth + 1.0, 11.0, 56.0 + activeLineIndexWorld * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			switch (activeLineIndexWorld)
			{
			case 0:
				featureWorldMoonGravity = !featureWorldMoonGravity;
				GAMEPLAY::SET_GRAVITY_LEVEL(featureWorldMoonGravity ? 2 : 0);
				break;
			case 1:
				PED::SET_CREATE_RANDOM_COPS(!featureWorldRandomCops);
				break;
			case 2:
				featureWorldRandomTrains = !featureWorldRandomTrains;
				VEHICLE::SET_RANDOM_TRAINS(featureWorldRandomTrains);
				break;
			case 3:
				featureWorldRandomBoats = !featureWorldRandomBoats;
				VEHICLE::SET_RANDOM_BOATS(featureWorldRandomBoats);
				break;
			case 4:
				featureWorldGarbageTrucks = !featureWorldGarbageTrucks;
				VEHICLE::SET_GARBAGE_TRUCKS(featureWorldGarbageTrucks);
				break;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexWorld == 0)
				activeLineIndexWorld = lineCount;
			activeLineIndexWorld--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexWorld++;
			if (activeLineIndexWorld == lineCount)
				activeLineIndexWorld = 0;
			waitTime = 150;
		}
	}
}
int activeLineIndexTime = 0;
void processTimeMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 4;
	std::string caption = "Time";
	static struct
	{
		LPCSTR text;
		bool *pState;
		bool *pUpdated;
	} lines[lineCount] = {
			{"Hour Forward", NULL, NULL},
			{"Hour Backward", NULL, NULL},
			{"Clock Paused", &featureTimePaused, &featureTimePausedUpdated},
			{"Sync With System", &featureTimeSynced, NULL}};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexTime)
					drawMenuLine(lineAsStr(lines[i].text, lines[i].pState), lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineAsStr(lines[activeLineIndexTime].text, lines[activeLineIndexTime].pState), lineWidth + 1.0, 11.0, 56.0 + activeLineIndexTime * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			switch (activeLineIndexTime)
			{
			case 0:
			case 1:
			{
				int h = TIME::GET_CLOCK_HOURS();
				if (activeLineIndexTime == 0)
					h = (h == 23) ? 0 : h + 1;
				else
					h = (h == 0) ? 23 : h - 1;
				int m = TIME::GET_CLOCK_MINUTES();
				TIME::SET_CLOCK_TIME(h, m, 0);
				char text[32];
				sprintf_s(text, "Time %d:%d", h, m);
				setStatusText(text);
			}
			break;
			default:
				if (lines[activeLineIndexTime].pState)
					*lines[activeLineIndexTime].pState = !(*lines[activeLineIndexTime].pState);
				if (lines[activeLineIndexTime].pUpdated)
					*lines[activeLineIndexTime].pUpdated = true;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexTime == 0)
				activeLineIndexTime = lineCount;
			activeLineIndexTime--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexTime++;
			if (activeLineIndexTime == lineCount)
				activeLineIndexTime = 0;
			waitTime = 150;
		}
	}
}
int activeLineIndexWeather = 0;
void processWeatherMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 16;
	std::string caption = "Weather";
	static struct
	{
		LPCSTR text;
		bool *pState;
		bool *pUpdated;
	} lines[lineCount] = {
			{"Wind", &featureWeatherWind, NULL},
			{"Set Persist", &featureWeatherPers, NULL},
			{"Extrasunny", NULL, NULL},
			{"Clear", NULL, NULL},
			{"Clouds", NULL, NULL},
			{"Smog", NULL, NULL},
			{"Foggy", NULL, NULL},
			{"Overcast", NULL, NULL},
			{"Rain", NULL, NULL},
			{"Thunder", NULL, NULL},
			{"Clearing", NULL, NULL},
			{"Neutral", NULL, NULL},
			{"Snow", NULL, NULL},
			{"Blizzard", NULL, NULL},
			{"Snowlight", NULL, NULL},
			{"Xmas", NULL, NULL}};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWeather)
					drawMenuLine(lineAsStr(lines[i].text, lines[i].pState), lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineAsStr(lines[activeLineIndexWeather].text, lines[activeLineIndexWeather].pState), lineWidth + 1.0, 11.0, 56.0 + activeLineIndexWeather * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			switch (activeLineIndexWeather)
			{
			case 0:
				featureWeatherWind = !featureWeatherWind;
				if (featureWeatherWind)
				{
					GAMEPLAY::SET_WIND(1.0);
					GAMEPLAY::SET_WIND_SPEED(11.99);
					GAMEPLAY::SET_WIND_DIRECTION(ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				}
				else
				{
					GAMEPLAY::SET_WIND(0.0);
					GAMEPLAY::SET_WIND_SPEED(0.0);
				}
				break;
			case 1:
				featureWeatherPers = !featureWeatherPers;
				break;
			default:
				GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
				if (featureWeatherPers)
				{
					GAMEPLAY::SET_OVERRIDE_WEATHER((char *)lines[activeLineIndexWeather].text);
				}
				else
				{
					GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char *)lines[activeLineIndexWeather].text);
					GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
				}
				setStatusText(lines[activeLineIndexWeather].text);
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexWeather == 0)
				activeLineIndexWeather = lineCount;
			activeLineIndexWeather--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexWeather++;
			if (activeLineIndexWeather == lineCount)
				activeLineIndexWeather = 0;
			waitTime = 150;
		}
	}
}
int activeLineIndexMisc = 0;
void processMiscMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 2;
	std::string caption = "Misc";
	static struct
	{
		LPCSTR text;
		bool *pState;
		bool *pUpdated;
	} lines[lineCount] = {
			{"Next Radio Track", NULL, NULL},
			{"Hide Hud", &featureMiscHideHud, NULL}};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexMisc)
					drawMenuLine(lineAsStr(lines[i].text, lines[i].pState), lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineAsStr(lines[activeLineIndexMisc].text, lines[activeLineIndexMisc].pState), lineWidth + 1.0, 11.0, 56.0 + activeLineIndexMisc * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			switch (activeLineIndexMisc)
			{
			case 0:
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) &&
						PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
					AUDIO::SKIP_RADIO_FORWARD();
				break;
			default:
				if (lines[activeLineIndexMisc].pState)
					*lines[activeLineIndexMisc].pState = !(*lines[activeLineIndexMisc].pState);
				if (lines[activeLineIndexMisc].pUpdated)
					*lines[activeLineIndexMisc].pUpdated = true;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexMisc == 0)
				activeLineIndexMisc = lineCount;
			activeLineIndexMisc--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexMisc++;
			if (activeLineIndexMisc == lineCount)
				activeLineIndexMisc = 0;
			waitTime = 150;
		}
	}
}
int activeLineIndexMain = 0;
void processMainMenu()
{
	const float lineWidth = 250.0;
	const int lineCount = 7;
	std::string caption = "Native Trainer";
	static LPCSTR lineCaption[lineCount] = {"Player", "Weapon", "Vehicle", "World", "Time", "Weather", "Misc"};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			drawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexMain)
					drawMenuLine(lineCaption[i], lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			drawMenuLine(lineCaption[activeLineIndexMain], lineWidth + 1.0, 11.0, 56.0 + activeLineIndexMain * 36.0, 0.0, 7.0, true, false);
			updateFeatures();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		getButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menuBeep();
			switch (activeLineIndexMain)
			{
			case 0:
				processPlayerMenu();
				break;
			case 1:
				processWeaponMenu();
				break;
			case 2:
				processVehMenu();
				break;
			case 3:
				processWorldMenu();
				break;
			case 4:
				processTimeMenu();
				break;
			case 5:
				processWeatherMenu();
				break;
			case 6:
				processMiscMenu();
				break;
			}
			waitTime = 200;
		}
		else if (bBack || trainerSwitchPressed())
		{
			menuBeep();
			break;
		}
		else if (bUp)
		{
			menuBeep();
			if (activeLineIndexMain == 0)
				activeLineIndexMain = lineCount;
			activeLineIndexMain--;
			waitTime = 150;
		}
		else if (bDown)
		{
			menuBeep();
			activeLineIndexMain++;
			if (activeLineIndexMain == lineCount)
				activeLineIndexMain = 0;
			waitTime = 150;
		}
	}
}
void resetGlobals()
{
	activeLineIndexMain = 0;
	activeLineIndexPlayer = 0;
	skinchangerActiveLineIndex = 0;
	skinchangerActiveItemIndex = 0;
	teleportActiveLineIndex = 0;
	activeLineIndexWeapon = 0;
	activeLineIndexVeh = 0;
	carspawnActiveLineIndex = 0;
	carspawnActiveItemIndex = 0;
	activeLineIndexWorld = 0;
	activeLineIndexWeather = 0;
	featurePlayerInvincible = false;
	featurePlayerInvincibleUpdated = false;
	featurePlayerNeverWanted = false;
	featurePlayerIgnored = false;
	featurePlayerIgnoredUpdated = false;
	featurePlayerUnlimitedAbility = false;
	featurePlayerNoNoise = false;
	featurePlayerNoNoiseUpdated = false;
	featurePlayerFastSwim = false;
	featurePlayerFastSwimUpdated = false;
	featurePlayerFastRun = false;
	featurePlayerFastRunUpdated = false;
	featurePlayerSuperJump = false;
	featureWeaponNoReload = false;
	featureWeaponFireAmmo = false;
	featureWeaponExplosiveAmmo = false;
	featureWeaponExplosiveMelee = false;
	featureWeaponVehRockets = false;
	featureVehInvincible = false;
	featureVehInvincibleUpdated = false;
	featureVehInvincibleWheels = false;
	featureVehInvincibleWheelsUpdated = false;
	featureVehSeatbelt = false;
	featureVehSeatbeltUpdated = false;
	featureVehSpeedBoost = false;
	featureVehWrapInSpawned = false;
	featureWorldMoonGravity = false;
	featureTimePaused = false;
	featureTimePausedUpdated = false;
	featureTimeSynced = false;
	featureWeatherWind = false;
	featureWeatherPers = false;
	featureMiscLockRadio = false;
	featureMiscHideHud = false;
	featureWorldRandomCops = true;
	featureWorldRandomTrains = true;
	featureWorldRandomBoats = true;
	featureWorldGarbageTrucks = true;
	skinchangerUsed = false;
}
void main()
{
	resetGlobals();
	while (true)
	{
		if (trainerSwitchPressed())
		{
			menuBeep();
			processMainMenu();
		}
		updateFeatures();
		WAIT(0);
	}
}
void ScriptMain()
{
	srand(GetTickCount());
	main();
}