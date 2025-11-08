#include "script.h"
#include "keyboard.h"
#include <string>
#include <ctime>
#pragma warning(disable : 4244 4305)
extern LPCSTR gPedModels[67][10];
extern LPCSTR gPedModelNames[67][10];
extern LPCSTR gVehicleModels[40][10];
struct TeleportLine {
  LPCSTR text;
  float x;
  float y;
  float z;
};
extern TeleportLine gTeleportLines[17];
struct PlayerLine {
  LPCSTR text;
  bool *pState;
  bool *pUpdated;
};
extern PlayerLine gPlayerLines[14];
struct WeaponLine {
  LPCSTR text;
  bool *pState;
  bool *pUpdated;
};
extern WeaponLine gWeaponLines[6];
extern LPCSTR gWeaponNames[59];
struct VehicleLine {
  LPCSTR text;
  bool *pState;
  bool *pUpdated;
};
extern VehicleLine gVehicleLines[8];
struct WorldLine {
  LPCSTR text;
  bool *pState;
  bool *pUpdated;
};
extern WorldLine gWorldLines[5];
struct TimeLine {
  LPCSTR text;
  bool *pState;
  bool *pUpdated;
};
extern TimeLine gTimeLines[3];
struct WeatherLine {
  LPCSTR text;
  bool *pState;
  bool *pUpdated;
};
extern WeatherLine gWeatherLines[16];
struct MiscLine {
  LPCSTR text;
  bool *pState;
  bool *pUpdated;
};
extern MiscLine gMiscLines[2];
extern LPCSTR gMainLineCaption[7];
void drawRect(float a0, float a1, float a2, float a3, int a4, int a5, int a6, int a7) {
  GRAPHICS::DRAW_RECT((a0 + (a2 * 0.5f)), (a1 + (a3 * 0.5f)), a2, a3, a4, a5, a6, a7);
}
void drawMenuLine(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText = true, bool *pState = NULL, std::string stepperValue = "") {
  int textCol[4] = { 255, 255, 255, 255 };
  int rectCol[4] = { 0, 0, 0, 205 };
  float textScale = 0.35;
  int font = 0;
  if (active) {
    rectCol[0] = 0;
    rectCol[1] = 0;
    rectCol[2] = 0;
    rectCol[3] = 255;
    if (rescaleText)
      textScale = 0.40;
  }
  if (title) {
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
  float rightTextLeft = (lineLeftScaled + lineWidthScaled) - (5.0f / (float)screenW);
  if (pState != NULL) {
    float boxSize = 10.0f;
    float boxPadding = 15.0f;
    float boxSizeScaledW = boxSize / (float)screenW;
    float boxSizeScaledH = boxSize / (float)screenH;
    float boxLeft = (lineLeftScaled + lineWidthScaled) - (boxPadding / (float)screenW) - boxSizeScaledW;
    float boxTop = lineTopScaled + (lineHeightScaled * 0.25f);
    drawRect(boxLeft, boxTop, boxSizeScaledW, boxSizeScaledH, 255, 255, 255, 255);
    if (*pState) {
      float innerBoxSize = boxSize * 0.6f;
      float innerBoxPadding = boxSize * 0.2f;
      float innerBoxSizeScaledW = innerBoxSize / (float)screenW;
      float innerBoxSizeScaledH = innerBoxSize / (float)screenH;
      float innerBoxLeft = boxLeft + (innerBoxPadding / (float)screenW);
      float innerBoxTop = boxTop + (innerBoxPadding / (float)screenH);
      drawRect(innerBoxLeft, innerBoxTop, innerBoxSizeScaledW, innerBoxSizeScaledH, 255, 255, 255, 255);
    }
  }
  else if (!stepperValue.empty()) {
    UI::SET_TEXT_FONT(font);
    UI::SET_TEXT_SCALE(0.0, textScale);
    UI::SET_TEXT_COLOUR(textCol[0], textCol[1], textCol[2], textCol[3]);
    UI::SET_TEXT_RIGHT_JUSTIFY(TRUE);
    UI::SET_TEXT_WRAP(0.0f, rightTextLeft);
    UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
    UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
    UI::_SET_TEXT_ENTRY("STRING");
    UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)stepperValue.c_str());
    UI::_DRAW_TEXT(rightTextLeft, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
  }
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
bool isTrainerSwitchPressed() {
  return IsKeyJustUp(VK_F4);
}
void getButtonState(bool *a, bool *b, bool *up, bool *down, bool *l, bool *r) {
  if (a)
    *a = IsKeyDown(VK_RETURN) || IsKeyDown(VK_NUMPAD5);
  if (b)
    *b = IsKeyDown(VK_BACK) || IsKeyDown(VK_NUMPAD0) || isTrainerSwitchPressed();
  if (up)
    *up = IsKeyDown(VK_UP) || IsKeyDown(VK_NUMPAD8);
  if (down)
    *down = IsKeyDown(VK_DOWN) || IsKeyDown(VK_NUMPAD2);
  if (r)
    *r = IsKeyDown(VK_RIGHT) || IsKeyDown(VK_NUMPAD6);
  if (l)
    *l = IsKeyDown(VK_LEFT) || IsKeyDown(VK_NUMPAD4);
}
void menuBeep() {
  AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
std::string gStatusText;
DWORD gStatusTextDrawTicksMax;
bool gStatusTextGxtEntry;
const int gMaxItemsOnScreen = 10;
const float gMenuWidth = 250.0f;
const float gMenuLineHeight = 36.0f;
const float gMenuTop = 60.0f;
float gMenuFooterTop = gMenuTop + (gMaxItemsOnScreen * gMenuLineHeight) + 2.78f;
float gMenuFooterHeight = 25.0f;
void drawMenuFooter(int numPages = 0, int currentPage = 0) {
  int screenW, screenH;
  GRAPHICS::GET_SCREEN_RESOLUTION(&screenW, &screenH);
  float footerLeft = 0.0f;
  float lineWidthScaled = gMenuWidth / (float)screenW;
  float footerLeftScaled = footerLeft / (float)screenW;
  float footerTopScaled = gMenuFooterTop / (float)screenH;
  float footerHeightScaled = gMenuFooterHeight / (float)screenH;
  if (numPages > 1) {
    std::string pageText = "Page " + std::to_string(currentPage + 1) + " / " + std::to_string(numPages);
    float textRightScaled = (footerLeft + gMenuWidth - 5.0f) / (float)screenW;
    float textTopScaled = footerTopScaled + (footerHeightScaled * 0.5f) - (10.0f / (float)screenH * 0.5f);
    UI::SET_TEXT_FONT(0);
    UI::SET_TEXT_SCALE(0.0, 0.35);
    UI::SET_TEXT_COLOUR(255, 255, 255, 255);
    UI::SET_TEXT_RIGHT_JUSTIFY(TRUE);
    UI::SET_TEXT_WRAP(0.0f, textRightScaled);
    UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
    UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
    UI::_SET_TEXT_ENTRY("STRING");
    UI::_ADD_TEXT_COMPONENT_STRING((char *)pageText.c_str());
    UI::_DRAW_TEXT(textRightScaled, textTopScaled);
  }
  if (GetTickCount() < gStatusTextDrawTicksMax) {
    DWORD fadeDuration = 1000;
    DWORD timeLeft = gStatusTextDrawTicksMax - GetTickCount();
    int alpha = 205;
    int textAlpha = 255;
    if (timeLeft < fadeDuration) {
      float fadePercent = (float)timeLeft / (float)fadeDuration;
      alpha = (int)(205.0f * fadePercent);
      textAlpha = (int)(255.0f * fadePercent);
    }
    float textLeftScaled = (footerLeft + 5.0f) / (float)screenW;
    float textTopScaled = footerTopScaled + (footerHeightScaled * 0.5f) - (10.0f / (float)screenH * 0.5f);
    drawRect(footerLeftScaled, footerTopScaled, lineWidthScaled, footerHeightScaled, 0, 0, 0, alpha);
    UI::SET_TEXT_FONT(0);
    UI::SET_TEXT_SCALE(0.0, 0.35);
    UI::SET_TEXT_COLOUR(255, 255, 255, textAlpha);
    UI::SET_TEXT_CENTRE(0);
    UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
    UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
    if (gStatusTextGxtEntry) {
      UI::_SET_TEXT_ENTRY((char *)gStatusText.c_str());
    }
    else {
      UI::_SET_TEXT_ENTRY("STRING");
      UI::_ADD_TEXT_COMPONENT_STRING((char *)gStatusText.c_str());
    }
    UI::_DRAW_TEXT(textLeftScaled, textTopScaled);
  }
}
void setStatusText(std::string str, DWORD time = 5000, bool isGxtEntry = false) {
  gStatusText = str;
  gStatusTextDrawTicksMax = GetTickCount() + time;
  gStatusTextGxtEntry = isGxtEntry;
}
bool gFeaturePlayerInvincible = false;
bool gFeaturePlayerInvincibleUpdated = false;
bool gFeaturePlayerNeverWanted = false;
bool gFeaturePlayerIgnored = false;
bool gFeaturePlayerIgnoredUpdated = false;
bool gFeaturePlayerUnlimitedAbility = false;
bool gFeaturePlayerNoNoise = false;
bool gFeaturePlayerNoNoiseUpdated = false;
bool gFeaturePlayerFastSwim = false;
bool gFeaturePlayerFastSwimUpdated = false;
bool gFeaturePlayerFastRun = false;
bool gFeaturePlayerFastRunUpdated = false;
bool gFeaturePlayerSuperJump = false;
bool gFeatureWeaponNoReload = false;
bool gFeatureWeaponFireAmmo = false;
bool gFeatureWeaponExplosiveAmmo = false;
bool gFeatureWeaponExplosiveMelee = false;
bool gFeatureWeaponVehRockets = false;
DWORD gFeatureWeaponVehShootLastTime = 0;
bool gFeatureVehInvincible = false;
bool gFeatureVehInvincibleUpdated = false;
bool gFeatureVehInvincibleWheels = false;
bool gFeatureVehInvincibleWheelsUpdated = false;
bool gFeatureVehSeatbelt = false;
bool gFeatureVehSeatbeltUpdated = false;
bool gFeatureVehSpeedBoost = false;
bool gFeatureVehWrapInSpawned = false;
bool gFeatureWorldMoonGravity = false;
bool gFeatureWorldRandomCops = true;
bool gFeatureWorldRandomTrains = true;
bool gFeatureWorldRandomBoats = true;
bool gFeatureWorldGarbageTrucks = true;
bool gFeatureTimePaused = false;
bool gFeatureTimePausedUpdated = false;
bool gFeatureTimeSynced = false;
bool gFeatureWeatherWind = false;
bool gFeatureWeatherPers = false;
bool gFeatureMiscLockRadio = false;
bool gFeatureMiscHideHud = false;
void checkPlayerModel() {
  Player player = PLAYER::PLAYER_ID();
  Ped playerPed = PLAYER::PLAYER_PED_ID();
  if (!ENTITY::DOES_ENTITY_EXIST(playerPed))
    return;
  Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);
  if (ENTITY::IS_ENTITY_DEAD(playerPed) || PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE))
    if (model != GAMEPLAY::GET_HASH_KEY("player_zero") &&
      model != GAMEPLAY::GET_HASH_KEY("player_one") &&
      model != GAMEPLAY::GET_HASH_KEY("player_two")) {
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
void updateVehicleGuns() {
  Player player = PLAYER::PLAYER_ID();
  Ped playerPed = PLAYER::PLAYER_PED_ID();
  if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !gFeatureWeaponVehRockets)
    return;
  bool bSelect = IsKeyDown(0x6B);
  if (bSelect && gFeatureWeaponVehShootLastTime + 150 < GetTickCount() &&
    PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
    Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
    Vector3 v0, v1;
    GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);
    Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
    if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)) {
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
    gFeatureWeaponVehShootLastTime = GetTickCount();
  }
}
bool gSkinchangerUsed = false;
void updateFeatures() {
  updateVehicleGuns();
  if (gSkinchangerUsed)
    checkPlayerModel();
  if (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), TRUE)) {
    WAIT(0);
    return;
  }
  gFeatureWorldRandomCops = PED::CAN_CREATE_RANDOM_COPS() == TRUE;
  Player player = PLAYER::PLAYER_ID();
  Ped playerPed = PLAYER::PLAYER_PED_ID();
  BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);
  if (gFeaturePlayerInvincibleUpdated) {
    if (bPlayerExists && !gFeaturePlayerInvincible)
      PLAYER::SET_PLAYER_INVINCIBLE(player, FALSE);
    gFeaturePlayerInvincibleUpdated = false;
  }
  if (gFeaturePlayerInvincible) {
    if (bPlayerExists)
      PLAYER::SET_PLAYER_INVINCIBLE(player, TRUE);
  }
  if (gFeaturePlayerNeverWanted) {
    if (bPlayerExists)
      PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
  }
  if (gFeaturePlayerIgnoredUpdated) {
    if (bPlayerExists)
      PLAYER::SET_POLICE_IGNORE_PLAYER(player, gFeaturePlayerIgnored);
    gFeaturePlayerIgnoredUpdated = false;
  }
  if (gFeaturePlayerUnlimitedAbility) {
    if (bPlayerExists)
      PLAYER::SPECIAL_ABILITY_FILL_METER(player, 1);
  }
  if (gFeaturePlayerNoNoiseUpdated) {
    if (bPlayerExists && !gFeaturePlayerNoNoise)
      PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 1.0);
    gFeaturePlayerNoNoiseUpdated = false;
  }
  if (gFeaturePlayerNoNoise)
    PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 0.0);
  if (gFeaturePlayerFastSwimUpdated) {
    if (bPlayerExists && !gFeaturePlayerFastSwim)
      PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.0);
    gFeaturePlayerFastSwimUpdated = false;
  }
  if (gFeaturePlayerFastSwim)
    PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.49);
  if (gFeaturePlayerFastRunUpdated) {
    if (bPlayerExists && !gFeaturePlayerFastRun)
      PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.0);
    gFeaturePlayerFastRunUpdated = false;
  }
  if (gFeaturePlayerFastRun)
    PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49);
  if (gFeaturePlayerSuperJump) {
    if (bPlayerExists)
      GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
  }
  if (gFeatureWeaponFireAmmo) {
    if (bPlayerExists)
      GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
  }
  if (gFeatureWeaponExplosiveAmmo) {
    if (bPlayerExists)
      GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
  }
  if (gFeatureWeaponExplosiveMelee) {
    if (bPlayerExists)
      GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
  }
  if (bPlayerExists && gFeatureWeaponNoReload) {
    Hash cur;
    if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &cur, 1)) {
      if (WEAPON::IS_WEAPON_VALID(cur)) {
        int maxAmmo;
        if (WEAPON::GET_MAX_AMMO(playerPed, cur, &maxAmmo)) {
          WEAPON::SET_PED_AMMO(playerPed, cur, maxAmmo);
          maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, cur, 1);
          if (maxAmmo > 0)
            WEAPON::SET_AMMO_IN_CLIP(playerPed, cur, maxAmmo);
        }
      }
    }
  }
  if (gFeatureVehInvincibleUpdated) {
    if (bPlayerExists && !gFeatureVehInvincible && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
      Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
      ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
      ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
      VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
      VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
      VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
    }
    gFeatureVehInvincibleUpdated = false;
  }
  if (gFeatureVehInvincible) {
    if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
      Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
      ENTITY::SET_ENTITY_INVINCIBLE(veh, TRUE);
      ENTITY::SET_ENTITY_PROOFS(veh, 1, 1, 1, 1, 1, 1, 1, 1);
      VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
      VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
      VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
    }
  }
  if (gFeatureVehInvincibleWheelsUpdated) {
    if (bPlayerExists && !gFeatureVehInvincibleWheels && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
      Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
      VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, TRUE);
      VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, TRUE);
      VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(veh, FALSE);
    }
    gFeatureVehInvincibleWheelsUpdated = false;
  }
  if (gFeatureVehInvincibleWheels) {
    if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
      Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
      VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, FALSE);
      VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, FALSE);
      VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(veh, TRUE);
    }
  }
  const int PED_FLAG_CAN_FLY_THRU_WINDSCREEN = 32;
  if (gFeatureVehSeatbeltUpdated) {
    if (bPlayerExists && !gFeatureVehSeatbelt)
      PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, TRUE);
    gFeatureVehSeatbeltUpdated = false;
  }
  if (gFeatureVehSeatbelt) {
    if (bPlayerExists) {
      if (PED::GET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, TRUE))
        PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, FALSE);
    }
  }
  if (gFeatureVehSpeedBoost && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
    Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
    DWORD model = ENTITY::GET_ENTITY_MODEL(veh);
    bool bUp = IsKeyDown(VK_NUMPAD9) || IsKeyDown(VK_PRIOR);
    bool bDown = IsKeyDown(VK_NUMPAD3) || IsKeyDown(VK_NEXT);
    if (bUp || bDown) {
      float speed = ENTITY::GET_ENTITY_SPEED(veh);
      if (bUp) {
        if (speed < 3.0f)
          speed = 3.0f;
        speed += speed * 0.05f;
        VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
      }
      else if (ENTITY::IS_ENTITY_IN_AIR(veh) || speed > 5.0)
        VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0);
    }
  }
  if (gFeatureTimePausedUpdated) {
    TIME::PAUSE_CLOCK(gFeatureTimePaused);
    gFeatureTimePausedUpdated = false;
  }
  if (gFeatureTimeSynced) {
    time_t now = time(0);
    tm t;
    localtime_s(&t, &now);
    TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
  }
  if (gFeatureMiscHideHud)
    UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
}
int gSkinchangerCurrentPage = 0;
int gSkinchangerActiveItem = 0;
bool processSkinchangerMenu() {
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = 67;
  gSkinchangerActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      if (strlen(gPedModelNames[gSkinchangerCurrentPage][i]) > 0) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      char caption[32];
      sprintf_s(caption, "Skin Changer %d / %d", gSkinchangerCurrentPage + 1, numPages);
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        LPCSTR modelName = gPedModelNames[gSkinchangerCurrentPage][i];
        drawMenuLine(modelName, gMenuWidth, 9.0, 60.0 + i * gMenuLineHeight, 0.0, 9.0, i == gSkinchangerActiveItem, false, false);
      }
      drawMenuFooter(numPages, gSkinchangerCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    if (bSelect) {
      menuBeep();
      DWORD model = GAMEPLAY::GET_HASH_KEY((char *)gPedModels[gSkinchangerCurrentPage][gSkinchangerActiveItem]);
      if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model)) {
        STREAMING::REQUEST_MODEL(model);
        while (!STREAMING::HAS_MODEL_LOADED(model))
          WAIT(0);
        PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
        PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
        WAIT(0);
        for (int i = 0; i < 12; i++)
          for (int j = 0; j < 100; j++) {
            int drawable = rand() % 10;
            int texture = rand() % 10;
            if (PED::IS_PED_COMPONENT_VARIATION_VALID(PLAYER::PLAYER_PED_ID(), i, drawable, texture)) {
              PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, drawable, texture, 0);
              break;
            }
          }
        gSkinchangerUsed = true;
        WAIT(100);
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
        waitTime = 200;
      }
    }
    else if (bBack) {
      menuBeep();
      break;
    }
    else if (bRight) {
      menuBeep();
      gSkinchangerCurrentPage++;
      if (gSkinchangerCurrentPage >= numPages)
        gSkinchangerCurrentPage = 0;
      gSkinchangerActiveItem = 0;
      waitTime = 150;
    }
    else if (bLeft) {
      menuBeep();
      if (gSkinchangerCurrentPage == 0)
        gSkinchangerCurrentPage = numPages;
      gSkinchangerCurrentPage--;
      gSkinchangerActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gSkinchangerActiveItem == 0)
        gSkinchangerActiveItem = itemsOnThisPage;
      gSkinchangerActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gSkinchangerActiveItem++;
      if (gSkinchangerActiveItem >= itemsOnThisPage)
        gSkinchangerActiveItem = 0;
      waitTime = 150;
    }
  }
  return false;
}
const int gTeleportLineCount = 17;
int gTeleportActiveItem = 0;
int gTeleportCurrentPage = 0;
bool processTeleportMenu() {
  std::string caption = "Teleport";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gTeleportLineCount + itemsPerPage - 1) / itemsPerPage;
  gTeleportActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gTeleportCurrentPage * itemsPerPage + i;
      if (itemIndex < gTeleportLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gTeleportCurrentPage * itemsPerPage + i;
        drawMenuLine(gTeleportLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gTeleportActiveItem, false);
      }
      drawMenuFooter(numPages, gTeleportCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gTeleportCurrentPage * itemsPerPage + gTeleportActiveItem;
    if (bSelect) {
      menuBeep();
      Entity e = PLAYER::PLAYER_PED_ID();
      if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
        e = PED::GET_VEHICLE_PED_IS_USING(e);
      Vector3 coords;
      bool success = false;
      if (selectedGlobalIndex == 0) {
        bool blipFound = false;
        int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
        for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) {
          if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4) {
            coords = UI::GET_BLIP_INFO_ID_COORD(i);
            blipFound = true;
            break;
          }
        }
        if (blipFound) {
          bool groundFound = false;
          static float groundCheckHeight[] = {
            100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
            450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
          };
          for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++) {
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
            WAIT(100);
            if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, FALSE)) {
              groundFound = true;
              coords.z += 3.0;
              break;
            }
          }
          if (!groundFound) {
            coords.z = 1000.0;
            WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
          }
          success = true;
        }
        else {
          setStatusText("Map Marker Isn't Set!");
        }
      }
      else {
        coords.x = gTeleportLines[selectedGlobalIndex].x;
        coords.y = gTeleportLines[selectedGlobalIndex].y;
        coords.z = gTeleportLines[selectedGlobalIndex].z;
        success = true;
      }
      if (success) {
        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
        WAIT(0);
        setStatusText("Teleported!");
        return true;
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      menuBeep();
      if (gTeleportCurrentPage == 0)
        gTeleportCurrentPage = numPages;
      gTeleportCurrentPage--;
      gTeleportActiveItem = 0;
      waitTime = 150;
    }
    else if (bRight) {
      menuBeep();
      gTeleportCurrentPage++;
      if (gTeleportCurrentPage >= numPages)
        gTeleportCurrentPage = 0;
      gTeleportActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gTeleportActiveItem == 0)
        gTeleportActiveItem = itemsOnThisPage;
      gTeleportActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gTeleportActiveItem++;
      if (gTeleportActiveItem >= itemsOnThisPage)
        gTeleportActiveItem = 0;
      waitTime = 150;
    }
  }
  return false;
}
const int gPlayerLineCount = 14;
int gPlayerActiveItem = 0;
int gPlayerCurrentPage = 0;
void processPlayerMenu() {
  std::string caption = "Player";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gPlayerLineCount + itemsPerPage - 1) / itemsPerPage;
  gPlayerActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gPlayerCurrentPage * itemsPerPage + i;
      if (itemIndex < gPlayerLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gPlayerCurrentPage * itemsPerPage + i;
        std::string stepperValue = "";
        if (itemIndex == 5) {
          Player player = PLAYER::PLAYER_ID();
          int wantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(player);
          stepperValue = "< " + std::to_string(wantedLevel) + " >";
        }
        drawMenuLine(gPlayerLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gPlayerActiveItem, false, true, gPlayerLines[itemIndex].pState, stepperValue);
      }
      drawMenuFooter(numPages, gPlayerCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gPlayerCurrentPage * itemsPerPage + gPlayerActiveItem;
    if (bSelect) {
      menuBeep();
      Player player = PLAYER::PLAYER_ID();
      Ped playerPed = PLAYER::PLAYER_PED_ID();
      switch (selectedGlobalIndex) {
      case 0:
        if (processSkinchangerMenu())
          return;
        break;
      case 1:
        if (processTeleportMenu())
          return;
        break;
      case 2: {
        ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
        PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
        if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
          Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
          if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
            VEHICLE::SET_VEHICLE_FIXED(playerVeh);
        }
        setStatusText("Player Fixed!");
      }
            break;
      case 3: {
        PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed);
        setStatusText("Using Default Model Skin!");
      }
            break;
      case 4:
        for (int i = 0; i < 3; i++) {
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
        break;
      default:
        if (gPlayerLines[selectedGlobalIndex].pState)
          *gPlayerLines[selectedGlobalIndex].pState = !(*gPlayerLines[selectedGlobalIndex].pState);
        if (gPlayerLines[selectedGlobalIndex].pUpdated)
          *gPlayerLines[selectedGlobalIndex].pUpdated = true;
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      if (selectedGlobalIndex == 5) {
        menuBeep();
        Player player = PLAYER::PLAYER_ID();
        if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PLAYER::GET_PLAYER_WANTED_LEVEL(player) > 0) {
          PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) - 1, 0);
          PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
          setStatusText("Wanted Down!");
        }
        waitTime = 150;
      }
      else {
        menuBeep();
        if (gPlayerCurrentPage == 0)
          gPlayerCurrentPage = numPages;
        gPlayerCurrentPage--;
        gPlayerActiveItem = 0;
        waitTime = 150;
      }
    }
    else if (bRight) {
      if (selectedGlobalIndex == 5) {
        menuBeep();
        Player player = PLAYER::PLAYER_ID();
        if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5) {
          PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, 0);
          PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
          setStatusText("Wanted Up!");
        }
        waitTime = 150;
      }
      else {
        menuBeep();
        gPlayerCurrentPage++;
        if (gPlayerCurrentPage >= numPages)
          gPlayerCurrentPage = 0;
        gPlayerActiveItem = 0;
        waitTime = 150;
      }
    }
    else if (bUp) {
      menuBeep();
      if (gPlayerActiveItem == 0)
        gPlayerActiveItem = itemsOnThisPage;
      gPlayerActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gPlayerActiveItem++;
      if (gPlayerActiveItem >= itemsOnThisPage)
        gPlayerActiveItem = 0;
      waitTime = 150;
    }
  }
}
const int gWeaponLineCount = 6;
const int gWeaponNamesCount = 59;
int gWeaponActiveItem = 0;
int gWeaponCurrentPage = 0;
void processWeaponMenu() {
  std::string caption = "Weapon";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gWeaponLineCount + itemsPerPage - 1) / itemsPerPage;
  gWeaponActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gWeaponCurrentPage * itemsPerPage + i;
      if (itemIndex < gWeaponLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gWeaponCurrentPage * itemsPerPage + i;
        drawMenuLine(gWeaponLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gWeaponActiveItem, false, true, gWeaponLines[itemIndex].pState);
      }
      drawMenuFooter(numPages, gWeaponCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gWeaponCurrentPage * itemsPerPage + gWeaponActiveItem;
    if (bSelect) {
      menuBeep();
      Ped playerPed = PLAYER::PLAYER_PED_ID();
      switch (selectedGlobalIndex) {
      case 0:
        for (int i = 0; i < gWeaponNamesCount; i++)
          WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY((char *)gWeaponNames[i]), 1000, 0);
        setStatusText("All Weapon Added!");
        break;
      default:
        if (gWeaponLines[selectedGlobalIndex].pState)
          *gWeaponLines[selectedGlobalIndex].pState = !(*gWeaponLines[selectedGlobalIndex].pState);
        if (gWeaponLines[selectedGlobalIndex].pUpdated)
          *gWeaponLines[selectedGlobalIndex].pUpdated = true;
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      menuBeep();
      if (gWeaponCurrentPage == 0)
        gWeaponCurrentPage = numPages;
      gWeaponCurrentPage--;
      gWeaponActiveItem = 0;
      waitTime = 150;
    }
    else if (bRight) {
      menuBeep();
      gWeaponCurrentPage++;
      if (gWeaponCurrentPage >= numPages)
        gWeaponCurrentPage = 0;
      gWeaponActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gWeaponActiveItem == 0)
        gWeaponActiveItem = itemsOnThisPage;
      gWeaponActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gWeaponActiveItem++;
      if (gWeaponActiveItem >= itemsOnThisPage)
        gWeaponActiveItem = 0;
      waitTime = 150;
    }
  }
}
int gCarspawnCurrentPage = 0;
int gCarspawnActiveItem = 0;
bool processCarspawnMenu() {
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = 40;
  gCarspawnActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      if (strlen(gVehicleModels[gCarspawnCurrentPage][i]) > 0) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      char caption[32];
      sprintf_s(caption, "Car Spawner %d / %d", gCarspawnCurrentPage + 1, numPages);
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        LPCSTR modelName = gVehicleModels[gCarspawnCurrentPage][i];
        drawMenuLine(modelName, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gCarspawnActiveItem, false, false);
      }
      drawMenuFooter(numPages, gCarspawnCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    if (bSelect) {
      menuBeep();
      LPCSTR modelName = gVehicleModels[gCarspawnCurrentPage][gCarspawnActiveItem];
      DWORD model = GAMEPLAY::GET_HASH_KEY((char *)modelName);
      if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)) {
        STREAMING::REQUEST_MODEL(model);
        while (!STREAMING::HAS_MODEL_LOADED(model))
          WAIT(0);
        Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
        Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
        VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
        if (gFeatureVehWrapInSpawned) {
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
    else if (bBack) {
      menuBeep();
      break;
    }
    else if (bRight) {
      menuBeep();
      gCarspawnCurrentPage++;
      if (gCarspawnCurrentPage >= numPages)
        gCarspawnCurrentPage = 0;
      gCarspawnActiveItem = 0;
      waitTime = 100;
    }
    else if (bLeft) {
      menuBeep();
      if (gCarspawnCurrentPage == 0)
        gCarspawnCurrentPage = numPages;
      gCarspawnCurrentPage--;
      gCarspawnActiveItem = 0;
      waitTime = 100;
    }
    else if (bUp) {
      menuBeep();
      if (gCarspawnActiveItem == 0)
        gCarspawnActiveItem = itemsOnThisPage;
      gCarspawnActiveItem--;
      waitTime = 100;
    }
    else if (bDown) {
      menuBeep();
      gCarspawnActiveItem++;
      if (gCarspawnActiveItem >= itemsOnThisPage)
        gCarspawnActiveItem = 0;
      waitTime = 100;
    }
  }
  return false;
}
const int gVehicleLineCount = 8;
int gVehicleActiveItem = 0;
int gVehicleCurrentPage = 0;
void processVehMenu() {
  std::string caption = "Vehicle";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gVehicleLineCount + itemsPerPage - 1) / itemsPerPage;
  gVehicleActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gVehicleCurrentPage * itemsPerPage + i;
      if (itemIndex < gVehicleLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gVehicleCurrentPage * itemsPerPage + i;
        drawMenuLine(gVehicleLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gVehicleActiveItem, false, true, gVehicleLines[itemIndex].pState);
      }
      drawMenuFooter(numPages, gVehicleCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gVehicleCurrentPage * itemsPerPage + gVehicleActiveItem;
    if (bSelect) {
      menuBeep();
      BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
      Ped playerPed = PLAYER::PLAYER_PED_ID();
      switch (selectedGlobalIndex) {
      case 0:
        if (processCarspawnMenu())
          return;
        break;
      case 1:
        if (bPlayerExists) {
          if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
            Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
            VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
            if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(veh))
              VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
          }
          else {
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
        if (gVehicleLines[selectedGlobalIndex].pState)
          *gVehicleLines[selectedGlobalIndex].pState = !(*gVehicleLines[selectedGlobalIndex].pState);
        if (gVehicleLines[selectedGlobalIndex].pUpdated)
          *gVehicleLines[selectedGlobalIndex].pUpdated = true;
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      menuBeep();
      if (gVehicleCurrentPage == 0)
        gVehicleCurrentPage = numPages;
      gVehicleCurrentPage--;
      gVehicleActiveItem = 0;
      waitTime = 150;
    }
    else if (bRight) {
      menuBeep();
      gVehicleCurrentPage++;
      if (gVehicleCurrentPage >= numPages)
        gVehicleCurrentPage = 0;
      gVehicleActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gVehicleActiveItem == 0)
        gVehicleActiveItem = itemsOnThisPage;
      gVehicleActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gVehicleActiveItem++;
      if (gVehicleActiveItem >= itemsOnThisPage)
        gVehicleActiveItem = 0;
      waitTime = 150;
    }
  }
}
const int gWorldLineCount = 5;
int gWorldActiveItem = 0;
int gWorldCurrentPage = 0;
void processWorldMenu() {
  std::string caption = "World";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gWorldLineCount + itemsPerPage - 1) / itemsPerPage;
  gWorldActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gWorldCurrentPage * itemsPerPage + i;
      if (itemIndex < gWorldLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gWorldCurrentPage * itemsPerPage + i;
        drawMenuLine(gWorldLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gWorldActiveItem, false, true, gWorldLines[itemIndex].pState);
      }
      drawMenuFooter(numPages, gWorldCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gWorldCurrentPage * itemsPerPage + gWorldActiveItem;
    if (bSelect) {
      menuBeep();
      switch (selectedGlobalIndex) {
      case 0:
        gFeatureWorldMoonGravity = !gFeatureWorldMoonGravity;
        GAMEPLAY::SET_GRAVITY_LEVEL(gFeatureWorldMoonGravity ? 2 : 0);
        break;
      case 1:
        PED::SET_CREATE_RANDOM_COPS(!gFeatureWorldRandomCops);
        break;
      case 2:
        gFeatureWorldRandomTrains = !gFeatureWorldRandomTrains;
        VEHICLE::SET_RANDOM_TRAINS(gFeatureWorldRandomTrains);
        break;
      case 3:
        gFeatureWorldRandomBoats = !gFeatureWorldRandomBoats;
        VEHICLE::SET_RANDOM_BOATS(gFeatureWorldRandomBoats);
        break;
      case 4:
        gFeatureWorldGarbageTrucks = !gFeatureWorldGarbageTrucks;
        VEHICLE::SET_GARBAGE_TRUCKS(gFeatureWorldGarbageTrucks);
        break;
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      menuBeep();
      if (gWorldCurrentPage == 0)
        gWorldCurrentPage = numPages;
      gWorldCurrentPage--;
      gWorldActiveItem = 0;
      waitTime = 150;
    }
    else if (bRight) {
      menuBeep();
      gWorldCurrentPage++;
      if (gWorldCurrentPage >= numPages)
        gWorldCurrentPage = 0;
      gWorldActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gWorldActiveItem == 0)
        gWorldActiveItem = itemsOnThisPage;
      gWorldActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gWorldActiveItem++;
      if (gWorldActiveItem >= itemsOnThisPage)
        gWorldActiveItem = 0;
      waitTime = 150;
    }
  }
}
const int gTimeLineCount = 3;
int gTimeActiveItem = 0;
int gTimeCurrentPage = 0;
void processTimeMenu() {
  std::string caption = "Time";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gTimeLineCount + itemsPerPage - 1) / itemsPerPage;
  gTimeActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gTimeCurrentPage * itemsPerPage + i;
      if (itemIndex < gTimeLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gTimeCurrentPage * itemsPerPage + i;
        std::string stepperValue = "";
        if (itemIndex == 0) {
          int h = TIME::GET_CLOCK_HOURS();
          int m = TIME::GET_CLOCK_MINUTES();
          char timeStr[16];
          sprintf_s(timeStr, "< %02d:%02d >", h, m);
          stepperValue = timeStr;
        }
        drawMenuLine(gTimeLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gTimeActiveItem, false, true, gTimeLines[itemIndex].pState, stepperValue);
      }
      drawMenuFooter(numPages, gTimeCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gTimeCurrentPage * itemsPerPage + gTimeActiveItem;
    if (bSelect) {
      menuBeep();
      switch (selectedGlobalIndex) {
      case 0:
        break;
      default:
        if (gTimeLines[selectedGlobalIndex].pState)
          *gTimeLines[selectedGlobalIndex].pState = !(*gTimeLines[selectedGlobalIndex].pState);
        if (gTimeLines[selectedGlobalIndex].pUpdated)
          *gTimeLines[selectedGlobalIndex].pUpdated = true;
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      if (selectedGlobalIndex == 0) {
        menuBeep();
        int h = TIME::GET_CLOCK_HOURS();
        h = (h == 0) ? 23 : h - 1;
        int m = TIME::GET_CLOCK_MINUTES();
        TIME::SET_CLOCK_TIME(h, m, 0);
        waitTime = 100;
      }
      else {
        menuBeep();
        if (gTimeCurrentPage == 0)
          gTimeCurrentPage = numPages;
        gTimeCurrentPage--;
        gTimeActiveItem = 0;
        waitTime = 150;
      }
    }
    else if (bRight) {
      if (selectedGlobalIndex == 0) {
        menuBeep();
        int h = TIME::GET_CLOCK_HOURS();
        h = (h == 23) ? 0 : h + 1;
        int m = TIME::GET_CLOCK_MINUTES();
        TIME::SET_CLOCK_TIME(h, m, 0);
        waitTime = 100;
      }
      else {
        menuBeep();
        gTimeCurrentPage++;
        if (gTimeCurrentPage >= numPages)
          gTimeCurrentPage = 0;
        gTimeActiveItem = 0;
        waitTime = 150;
      }
    }
    else if (bUp) {
      menuBeep();
      if (gTimeActiveItem == 0)
        gTimeActiveItem = itemsOnThisPage;
      gTimeActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gTimeActiveItem++;
      if (gTimeActiveItem >= itemsOnThisPage)
        gTimeActiveItem = 0;
      waitTime = 150;
    }
  }
}
const int gWeatherLineCount = 16;
int gWeatherActiveItem = 0;
int gWeatherCurrentPage = 0;
void processWeatherMenu() {
  std::string caption = "Weather";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gWeatherLineCount + itemsPerPage - 1) / itemsPerPage;
  gWeatherActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gWeatherCurrentPage * itemsPerPage + i;
      if (itemIndex < gWeatherLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gWeatherCurrentPage * itemsPerPage + i;
        drawMenuLine(gWeatherLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gWeatherActiveItem, false, true, gWeatherLines[itemIndex].pState);
      }
      drawMenuFooter(numPages, gWeatherCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gWeatherCurrentPage * itemsPerPage + gWeatherActiveItem;
    if (bSelect) {
      menuBeep();
      switch (selectedGlobalIndex) {
      case 0:
        gFeatureWeatherWind = !gFeatureWeatherWind;
        if (gFeatureWeatherWind) {
          GAMEPLAY::SET_WIND(1.0);
          GAMEPLAY::SET_WIND_SPEED(11.99);
          GAMEPLAY::SET_WIND_DIRECTION(ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
        }
        else {
          GAMEPLAY::SET_WIND(0.0);
          GAMEPLAY::SET_WIND_SPEED(0.0);
        }
        break;
      case 1:
        gFeatureWeatherPers = !gFeatureWeatherPers;
        break;
      default:
        GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
        if (gFeatureWeatherPers) {
          GAMEPLAY::SET_OVERRIDE_WEATHER((char *)gWeatherLines[selectedGlobalIndex].text);
        }
        else {
          GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char *)gWeatherLines[selectedGlobalIndex].text);
          GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
        }
        setStatusText(gWeatherLines[selectedGlobalIndex].text);
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      menuBeep();
      if (gWeatherCurrentPage == 0)
        gWeatherCurrentPage = numPages;
      gWeatherCurrentPage--;
      gWeatherActiveItem = 0;
      waitTime = 150;
    }
    else if (bRight) {
      menuBeep();
      gWeatherCurrentPage++;
      if (gWeatherCurrentPage >= numPages)
        gWeatherCurrentPage = 0;
      gWeatherActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gWeatherActiveItem == 0)
        gWeatherActiveItem = itemsOnThisPage;
      gWeatherActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gWeatherActiveItem++;
      if (gWeatherActiveItem >= itemsOnThisPage)
        gWeatherActiveItem = 0;
      waitTime = 150;
    }
  }
}
const int gMiscLineCount = 2;
int gMiscActiveItem = 0;
int gMiscCurrentPage = 0;
void processMiscMenu() {
  std::string caption = "Misc";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gMiscLineCount + itemsPerPage - 1) / itemsPerPage;
  gMiscActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gMiscCurrentPage * itemsPerPage + i;
      if (itemIndex < gMiscLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gMiscCurrentPage * itemsPerPage + i;
        drawMenuLine(gMiscLines[itemIndex].text, gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gMiscActiveItem, false, true, gMiscLines[itemIndex].pState);
      }
      drawMenuFooter(numPages, gMiscCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gMiscCurrentPage * itemsPerPage + gMiscActiveItem;
    if (bSelect) {
      menuBeep();
      switch (selectedGlobalIndex) {
      case 0:
        if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) &&
          PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
          AUDIO::SKIP_RADIO_FORWARD();
        break;
      default:
        if (gMiscLines[selectedGlobalIndex].pState)
          *gMiscLines[selectedGlobalIndex].pState = !(*gMiscLines[selectedGlobalIndex].pState);
        if (gMiscLines[selectedGlobalIndex].pUpdated)
          *gMiscLines[selectedGlobalIndex].pUpdated = true;
      }
      waitTime = 200;
    }
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      menuBeep();
      if (gMiscCurrentPage == 0)
        gMiscCurrentPage = numPages;
      gMiscCurrentPage--;
      gMiscActiveItem = 0;
      waitTime = 150;
    }
    else if (bRight) {
      menuBeep();
      gMiscCurrentPage++;
      if (gMiscCurrentPage >= numPages)
        gMiscCurrentPage = 0;
      gMiscActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gMiscActiveItem == 0)
        gMiscActiveItem = itemsOnThisPage;
      gMiscActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gMiscActiveItem++;
      if (gMiscActiveItem >= itemsOnThisPage)
        gMiscActiveItem = 0;
      waitTime = 150;
    }
  }
}
const int gMainLineCount = 7;
int gMainActiveItem = 0;
int gMainCurrentPage = 0;
void processMainMenu() {
  std::string caption = "Native Trainer";
  DWORD waitTime = 150;
  const int itemsPerPage = 10;
  const int numPages = (gMainLineCount + itemsPerPage - 1) / itemsPerPage;
  gMainActiveItem = 0;
  while (true) {
    int itemsOnThisPage = 0;
    for (int i = 0; i < itemsPerPage; i++) {
      int itemIndex = gMainCurrentPage * itemsPerPage + i;
      if (itemIndex < gMainLineCount) itemsOnThisPage++;
    }
    DWORD maxTickCount = GetTickCount() + waitTime;
    do {
      drawMenuLine(caption, gMenuWidth, 15.0, 18.0, 0.0, 5.0, false, true);
      for (int i = 0; i < itemsOnThisPage; i++) {
        int itemIndex = gMainCurrentPage * itemsPerPage + i;
        drawMenuLine(gMainLineCaption[itemIndex], gMenuWidth, 9.0, gMenuTop + i * gMenuLineHeight, 0.0, 9.0, i == gMainActiveItem, false);
      }
      drawMenuFooter(numPages, gMainCurrentPage);
      updateFeatures();
      WAIT(0);
    } while (GetTickCount() < maxTickCount);
    waitTime = 0;
    bool bSelect, bBack, bUp, bDown, bLeft, bRight;
    getButtonState(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);
    int selectedGlobalIndex = gMainCurrentPage * itemsPerPage + gMainActiveItem;
    if (bSelect) {
      menuBeep();
      switch (selectedGlobalIndex) {
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
    else if (bBack || isTrainerSwitchPressed()) {
      menuBeep();
      break;
    }
    else if (bLeft) {
      menuBeep();
      if (gMainCurrentPage == 0)
        gMainCurrentPage = numPages;
      gMainCurrentPage--;
      gMainActiveItem = 0;
      waitTime = 150;
    }
    else if (bRight) {
      menuBeep();
      gMainCurrentPage++;
      if (gMainCurrentPage >= numPages)
        gMainCurrentPage = 0;
      gMainActiveItem = 0;
      waitTime = 150;
    }
    else if (bUp) {
      menuBeep();
      if (gMainActiveItem == 0)
        gMainActiveItem = itemsOnThisPage;
      gMainActiveItem--;
      waitTime = 150;
    }
    else if (bDown) {
      menuBeep();
      gMainActiveItem++;
      if (gMainActiveItem >= itemsOnThisPage)
        gMainActiveItem = 0;
      waitTime = 150;
    }
  }
}
void resetGlobals() {
  gMainActiveItem = 0;
  gMainCurrentPage = 0;
  gPlayerActiveItem = 0;
  gPlayerCurrentPage = 0;
  gSkinchangerCurrentPage = 0;
  gSkinchangerActiveItem = 0;
  gTeleportActiveItem = 0;
  gTeleportCurrentPage = 0;
  gWeaponActiveItem = 0;
  gWeaponCurrentPage = 0;
  gVehicleActiveItem = 0;
  gVehicleCurrentPage = 0;
  gCarspawnCurrentPage = 0;
  gCarspawnActiveItem = 0;
  gWorldActiveItem = 0;
  gWorldCurrentPage = 0;
  gWeatherActiveItem = 0;
  gWeatherCurrentPage = 0;
  gMiscActiveItem = 0;
  gMiscCurrentPage = 0;
  gFeaturePlayerInvincible = false;
  gFeaturePlayerInvincibleUpdated = false;
  gFeaturePlayerNeverWanted = false;
  gFeaturePlayerIgnored = false;
  gFeaturePlayerIgnoredUpdated = false;
  gFeaturePlayerUnlimitedAbility = false;
  gFeaturePlayerNoNoise = false;
  gFeaturePlayerNoNoiseUpdated = false;
  gFeaturePlayerFastSwim = false;
  gFeaturePlayerFastSwimUpdated = false;
  gFeaturePlayerFastRun = false;
  gFeaturePlayerFastRunUpdated = false;
  gFeaturePlayerSuperJump = false;
  gFeatureWeaponNoReload = false;
  gFeatureWeaponFireAmmo = false;
  gFeatureWeaponExplosiveAmmo = false;
  gFeatureWeaponExplosiveMelee = false;
  gFeatureWeaponVehRockets = false;
  gFeatureVehInvincible = false;
  gFeatureVehInvincibleUpdated = false;
  gFeatureVehInvincibleWheels = false;
  gFeatureVehInvincibleWheelsUpdated = false;
  gFeatureVehSeatbelt = false;
  gFeatureVehSeatbeltUpdated = false;
  gFeatureVehSpeedBoost = false;
  gFeatureVehWrapInSpawned = false;
  gFeatureWorldMoonGravity = false;
  gFeatureTimePaused = false;
  gFeatureTimePausedUpdated = false;
  gFeatureTimeSynced = false;
  gFeatureWeatherWind = false;
  gFeatureWeatherPers = false;
  gFeatureMiscLockRadio = false;
  gFeatureMiscHideHud = false;
  gFeatureWorldRandomCops = true;
  gFeatureWorldRandomTrains = true;
  gFeatureWorldRandomBoats = true;
  gFeatureWorldGarbageTrucks = true;
  gSkinchangerUsed = false;
}
void main() {
  resetGlobals();
  while (true) {
    if (isTrainerSwitchPressed()) {
      menuBeep();
      processMainMenu();
    }
    updateFeatures(); 
    WAIT(0);
  }
}
void ScriptMain() {
  srand(GetTickCount());
  main();
}
