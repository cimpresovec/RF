/*
* Copyright (c) 2012-2012 Luka Horvat (redreaper132@gmail.com) http://www.redgamedevblog.blogspot.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

//Configuration file
#include "RF_config.h"
#ifdef RF_SOUND

//This file is the rendering part of the framework
#ifndef RF_SOUND_H
#define RF_SOUND_H

//Linker setting for libraries
#if defined(_MSC_VER)
#	pragma comment(lib, "irrklang.lib")
#else
//TODO
#endif

//Libraries needed for RF_main
#if defined(_MSC_VER)
#	include <irrKlang.h>
#else
//TODO
#endif

//Definitions
#define RF_SoundEngine irrklang::ISoundEngine*
#define RF_SoundSource irrklang::ISoundSource*

//Inline function to create an irrklang engine
inline irrklang::ISoundEngine* RF_CreateSoundEngine()
{
	return irrklang::createIrrKlangDevice();
}

//Inline functions that takes the sound engine and sound path and loads it preloaded
inline irrklang::ISoundSource* RF_LoadSound(irrklang::ISoundEngine* soundEngine, const std::string filePath)
{
	return soundEngine->addSoundSourceFromFile(filePath.c_str(), irrklang::ESM_AUTO_DETECT, true);
}

#endif
#endif