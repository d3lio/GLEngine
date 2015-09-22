#pragma once
#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "utils/engine_defines.h"
#include "cfgLoader.h"

struct Resolution
{
    ushort width;
    ushort height;
};

enum SettingsEnum
{
    FAILED = -1,
    OFF = 0x00,
    ON = 0x01,
    LOW = 0x01,
    MED = 0x02,
    HIGH = 0x03,
    NEAR = 0x01,
    FAR = 0x02,

    LINEAR = 0x11,
    BILINEAR = 0x12,
    TRILINEAR = 0x13,

    x2 = 0x02,
    x4 = 0x04,
    x8 = 0x08,
    x16 = 0x10,
};

class Settings
{
public:
    Settings(const char* path);
    ~Settings();
    Settings(const Settings& other);
    void operator=(const Settings& other);

    ///returns 1 if syntax is OK, 0 if NOT
    bool isReadyToGet();
    
    void setAntialiasing(char _antialiasing);
    ///returns OFF, x2, x4, x8, x16 if value is OK or FAILED if NOT
    char getAntialiasing();
    void setFullscreen(char _fullscreen);
    ///returns OFF, ON if value is OK or FAILED if NOT
    char getFullscreen();
    void setWindowed(char _windowed);
    ///returns OFF, ON if value is OK or FAILED if NOT
    char getWindowed();
    void setFullscreenResolution(const Resolution& _fullscreenResolution);
    ///returns a Resolution struct consisting of width and height which will be both 0 if wrong value in cfgFile, otherwise their values will be the actual parameters
    Resolution getFullscreenResolution();
    void setWindowedResolution(const Resolution& _windowedResolution);
    ///returns a Resolution struct consisting of width and height which will be both 0 if wrong value in cfgFile, otherwise their values will be the actual parameters
    Resolution getWindowedResolution();
    void setVsync(char _vsync);
    ///returns OFF, ON if value is OK or FAILED if NOT
    char getVsync();
    void setBrightness(char _brightness);
    ///returns a value from 1 to 100, there is no FAILED here, it returns 50 if the value is wrong
    char getBrightness();
    void setTextureQuality(char _textureQuality);
    ///returns LOW, MED, HIGH if value is OK or FAILED of NOT
    char getTextureQuality();
    void setTextureFiltering(char _textureFiltering);
    ///returns LINEAR, BILINEAR, TRILINEAR, x2, x4, x8, x16 if value is OK or FAILED if NOT
    char getTextureFiltering();
    void setShadowsQuality(char _shadowsQuality);
    ///returns OFF, LOW, MED, HIGH if value is OK or FAILED if NOT
    char getShadowsQuality();
    void setLightingQuality(char _lightingQuality);
    ///returns LOW, MED, HIGH if value is OK or FAILED of NOT
    char getLightingQuality();
    void setEffectsQuality(char _effectsQuality);
    ///returns LOW, MED, HIGH if value is OK or FAILED of NOT
    char getEffectsQuality();
    void setDrawDistance(char _drawDistance);
    ///returns NEAR, MED, FAR if value is OK or FAILED of NOT
    char getDrawDistance();
    void setParticlesQuality(char _particlesQuality);
    ///returns LOW, MED, HIGH if value is OK or FAILED of NOT
    char getParticlesQuality();

private:
    void setSettingsFromCfg();

    bool initFail;

    char antialiasing;
    char fullscreen;
    char windowed;
    Resolution fullscreenResolution;
    Resolution windowedResolution;
    char vsync;
    char brightness;
    char textureQuality;
    char textureFiltering;
    char shadowsQuality;
    char lightingQuality;
    char effectsQuality;
    char drawDistance;
    char particlesQuality;

    CfgLoader testObj;
};
#endif