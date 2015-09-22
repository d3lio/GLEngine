#include "settings.h"
#define DEFAULT_RES_WIDTH 0
#define DEFAULT_RES_HEIGHT 0

Settings::Settings(const char* path)
{
    if(initFail = testObj.init(path))
        setSettingsFromCfg();
}

Settings::~Settings()
{

}

Settings::Settings(const Settings& other)
{
    *this = other;
}

void Settings::operator=(const Settings& other)
{
    antialiasing = other.antialiasing;
    fullscreen = other.fullscreen;
    windowed = other.windowed;
    fullscreenResolution = other.fullscreenResolution;
    windowedResolution = other.windowedResolution;
    vsync = other.vsync;
    brightness = other.brightness;
    textureQuality = other.textureQuality;
    textureFiltering = other.textureFiltering;
    shadowsQuality = other.shadowsQuality;
    lightingQuality = other.lightingQuality;
    effectsQuality = other.effectsQuality;
    drawDistance = other.drawDistance;
    particlesQuality = other.particlesQuality;
}

//---------------------------------------------------set and get functions

bool Settings::isReadyToGet()
{
    return initFail;
}


void Settings::setSettingsFromCfg()
{
    std::string newValue;
    newValue = testObj["antialiasing"];
    if(!newValue.compare("OFF"))
        antialiasing = OFF;
    else
        if(!newValue.compare("x2"))
            antialiasing = x2;
        else
            if(!newValue.compare("x4"))
                antialiasing = x4;
            else
                if(!newValue.compare("x8"))
                    antialiasing = x8;
                else
                    if(!newValue.compare("x16"))
                        antialiasing = x16;
                    else
                        antialiasing = FAILED;

    newValue = testObj["fullscreen"];
    if (!newValue.compare("OFF"))
        fullscreen = OFF;
    else
        if (!newValue.compare("ON"))
            fullscreen = ON;
        else
            fullscreen = FAILED;

    newValue = testObj["windowed"];
    if (!newValue.compare("OFF"))
        windowed = OFF;
    else
        if (!newValue.compare("ON"))
            windowed = ON;
        else
            windowed = FAILED;

    newValue = testObj["fullscreen-resolution"];
    std::string width;
    std::string height;
    ushort xCount = 0;
    ushort xPosition = 0;
    bool flag = 0;
    char i;
    
    for(int i = 0 ; newValue[i] ; i++)
    {
        if(newValue[i] == 'x')
        {
            xPosition = i;
            xCount++;
        }
        else
            if(newValue[i] < '0' && newValue[i] > '9')
            {
                flag = 1;
                break;
            }
    }
    
    if(xPosition != 0 && xPosition != newValue.length() - 1 && xCount == 1 && !flag)
    {
        for(i = 0 ; i < xPosition && i < 5 ; i++)
            width += newValue[i];
        if(i < 5 && (newValue.length() - (xPosition + 1)) < 5)
        {
            for(i = xPosition + 1 ; i < (char)newValue.length() ; i++)
                height += newValue[i];

            fullscreenResolution.width = atoi(width.c_str());
            fullscreenResolution.height = atoi(height.c_str());
        }
        else
        {
            fullscreenResolution.width = DEFAULT_RES_WIDTH;//default
            fullscreenResolution.height = DEFAULT_RES_HEIGHT;//resolution
        }
    }
    else
    {
        fullscreenResolution.width = DEFAULT_RES_WIDTH;//default
        fullscreenResolution.height = DEFAULT_RES_HEIGHT;//resolution
    }

    newValue = testObj["windowed-resolution"];
    width.clear();
    height.clear();
    xCount = 0;
    xPosition = 0;
    flag = 0;
    
    for(int i = 0 ; newValue[i] ; i++)
    {
        if(newValue[i] == 'x')
        {
            xPosition = i;
            xCount++;
        }
        else
            if(newValue[i] < '0' && newValue[i] > '9')
            {
                flag = 1;
                break;
            }
    }

    if(xPosition != 0 && xPosition != newValue.length() - 1 && xCount == 1 && !flag)
    {
        for(i = 0 ; i < xPosition && i < 5 ; i++)
            width += newValue[i];
        if(i < 5 && (newValue.length() - (xPosition + 1)) < 5)
        {
            for(i = xPosition + 1 ; i < (char)newValue.length() ; i++)
                height += newValue[i];

            windowedResolution.width = atoi(width.c_str());
            windowedResolution.height = atoi(height.c_str());
        }
        else
        {
            windowedResolution.width = DEFAULT_RES_WIDTH;//default
            windowedResolution.height = DEFAULT_RES_HEIGHT;//resolution
        }
    }
    else
    {
        windowedResolution.width = DEFAULT_RES_WIDTH;//default
        windowedResolution.height = DEFAULT_RES_HEIGHT;//resolution
    }

    newValue = testObj["vsync"];
    if (!newValue.compare("ON"))
        vsync = ON;
    else
        if (!newValue.compare("OFF"))
            vsync = OFF;
        else
            vsync = FAILED;

    newValue = testObj["brightness"];
    short calcBrightness;
    if(newValue.length() > 3 || newValue[0] == '\0')
        brightness = 50;//place DEFAULT
    else
    {
        calcBrightness = atoi(newValue.c_str());
        if(calcBrightness > 100)
            calcBrightness = 100;
        if(calcBrightness < 1)
            calcBrightness = 1;
        brightness = (char) calcBrightness;
    }

    newValue = testObj["texture-quality"];
    if(!newValue.compare("LOW"))
        textureQuality = LOW;
    else
        if(!newValue.compare("MED"))
            textureQuality = MED;
        else
            if(!newValue.compare("HIGH"))
                textureQuality = HIGH;
            else
                textureQuality = FAILED;

    newValue = testObj["texture-filtering"];
    if(!newValue.compare("LINEAR"))
        textureFiltering = LINEAR;
    else
        if(!newValue.compare("BILINEAR"))
            textureFiltering = BILINEAR;
        else
            if(!newValue.compare("TRILINEAR"))
                textureFiltering = TRILINEAR;
            else
                if(!newValue.compare("x2"))
                    textureFiltering = x2;
                else
                    if(!newValue.compare("x4"))
                        textureFiltering = x4;
                    else
                        if(!newValue.compare("x8"))
                            textureFiltering = x8;
                        else
                            if(!newValue.compare("x16"))
                                textureFiltering = x16;
                            else
                                textureFiltering = FAILED;

    newValue = testObj["shadows-quality"];
    if (!newValue.compare("LOW"))
        shadowsQuality = LOW;
    else
        if (!newValue.compare("MED"))
            shadowsQuality = MED;
        else
            if (!newValue.compare("HIGH"))
                shadowsQuality = HIGH;
            else
                if (!newValue.compare("OFF"))
                    shadowsQuality = OFF;
                else
                    shadowsQuality = FAILED;

    newValue = testObj["lighting-quality"];
    if(!newValue.compare("HIGH"))
        lightingQuality = HIGH;
    else
        if(!newValue.compare("MED"))
            lightingQuality = MED;
        else
            if(!newValue.compare("LOW"))
                lightingQuality = LOW;
            else
                lightingQuality = FAILED;

    newValue = testObj["effects-quality"];
    if(!newValue.compare("HIGH"))
        effectsQuality = HIGH;
    else
        if(!newValue.compare("MED"))
            effectsQuality = MED;
        else
            if(!newValue.compare("LOW"))
                effectsQuality = LOW;
            else
                effectsQuality = FAILED;

    newValue = testObj["draw-distance"];
    if(!newValue.compare("FAR"))
        drawDistance = FAR;
    else
        if(!newValue.compare("MED"))
            drawDistance = MED;
        else
            if(!newValue.compare("NEAR"))
                drawDistance = NEAR;
            else
                drawDistance = FAILED;

    newValue = testObj["particles-quality"];
    if(!newValue.compare("HIGH"))
        particlesQuality = HIGH;
    else
        if(!newValue.compare("MED"))
            particlesQuality = MED;
        else
            if(!newValue.compare("LOW"))
                particlesQuality = LOW;
            else
                particlesQuality = FAILED;

}

void Settings::setAntialiasing(char _antialiasing)
{
    antialiasing = _antialiasing;
}

char Settings::getAntialiasing()
{
    return antialiasing;
}


void Settings::setFullscreenResolution(const Resolution& _fullscreenResolution)
{
    fullscreenResolution = _fullscreenResolution;
}

Resolution Settings::getFullscreenResolution()
{
    return fullscreenResolution;
}

void Settings::setWindowedResolution(const Resolution& _windowedResolution)
{
    windowedResolution = _windowedResolution;
}

Resolution Settings::getWindowedResolution()
{
    return windowedResolution;
}

void Settings::setFullscreen(char _fullscreen)
{
    fullscreen = _fullscreen;
}

char Settings::getFullscreen()
{
    return fullscreen;
}

void Settings::setWindowed(char _windowed)
{
    windowed = _windowed;
}

char Settings::getWindowed()
{
    return windowed;
}

void Settings::setVsync(char _vsync)
{
    vsync = _vsync;
}

char Settings::getVsync()
{
    return vsync;
}

void Settings::setBrightness(char _brightness)
{
    brightness = _brightness;
}

char Settings::getBrightness()
{
    return brightness;
}

void Settings::setTextureQuality(char _textureQuality)
{
    textureQuality = _textureQuality;
}

char Settings::getTextureQuality()
{
    return textureQuality;
}

void Settings::setTextureFiltering(char _textureFiltering)
{
    textureFiltering = _textureFiltering;
}

char Settings::getTextureFiltering()
{
    return textureFiltering;
}

void Settings::setShadowsQuality(char _shadowsQuality)
{
    shadowsQuality = _shadowsQuality;
}

char Settings::getShadowsQuality()
{
    return shadowsQuality;
}

void Settings::setLightingQuality(char _lightingQuality)
{
    lightingQuality = _lightingQuality;
}

char Settings::getLightingQuality()
{
    return lightingQuality;
}

void Settings::setEffectsQuality(char _effectsQuality)
{
    effectsQuality = _effectsQuality;
}

char Settings::getEffectsQuality()
{
    return effectsQuality;
}

void Settings::setDrawDistance(char _drawDistance)
{
    drawDistance = _drawDistance;
}

char Settings::getDrawDistance()
{
    return drawDistance;
}

void Settings::setParticlesQuality(char _particlesQuality)
{
    particlesQuality = _particlesQuality;
}

char Settings::getParticlesQuality()
{
    return particlesQuality;
}