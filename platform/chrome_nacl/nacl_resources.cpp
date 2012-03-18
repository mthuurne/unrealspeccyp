/*
Portable ZX-Spectrum emulator.
Copyright (C) 2001-2012 SMT, Dexus, Alone Coder, deathsoft, djdron, scor

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef _CHROME_NACL

#include "nacl_url.h"
#include "../../std.h"

using namespace std;

byte sos128[16384];
byte sos48[16384];
byte service[16384];
byte dos513f[16384];
byte spxtrm4f[2048];

static const string rom_sos128	= "res/rom/sos128.rom";
static const string rom_sos48	= "res/rom/sos48.rom";
static const string rom_service	= "res/rom/service.rom";
static const string rom_dos513f	= "res/rom/dos513f.rom";
static const string font_spxtrm4f = "res/font/spxtrm4f.fnt";

namespace xPlatform
{

class eResourceLoader : public eURLLoader::eCallback
{
public:
	eResourceLoader(pp::Instance* i) : instance(i), resources_ok(0), resources_failed(0)
	{
		new eURLLoader(instance, rom_sos128, this);
		new eURLLoader(instance, rom_sos48, this);
		new eURLLoader(instance, rom_service, this);
		new eURLLoader(instance, rom_dos513f, this);
		new eURLLoader(instance, font_spxtrm4f, this);
	}
protected:
	virtual void OnURLLoadOk(const string& url, const char* buffer, size_t size)
	{
		bool ok = false;
		if(url == rom_sos128			&& size == sizeof(sos128))	{ memcpy(sos128,	buffer, sizeof(sos128));	ok = true; }
		else if(url == rom_sos48		&& size == sizeof(sos48))	{ memcpy(sos48,		buffer, sizeof(sos48));		ok = true; }
		else if(url == rom_service		&& size == sizeof(service))	{ memcpy(service,	buffer, sizeof(service));	ok = true; }
		else if(url == rom_dos513f		&& size == sizeof(dos513f))	{ memcpy(dos513f,	buffer, sizeof(dos513f));	ok = true; }
		else if(url == font_spxtrm4f	&& size == sizeof(spxtrm4f)){ memcpy(spxtrm4f,	buffer, sizeof(spxtrm4f));	ok = true; }
		if(ok)
			++resources_ok;
		else
			++resources_failed;
		OnURLLoaded();
	}
	virtual void OnURLLoadFail(const string& url)
	{
		++resources_failed;
		OnURLLoaded();
	}
	void OnURLLoaded()
	{
		if(resources_failed + resources_ok < 5)
			return;
		if(resources_failed)
			instance->PostMessage("resources_failed");
		else
			instance->PostMessage("resources_ok");
		delete this;
	}
protected:
	pp::Instance* instance;
	int resources_ok;
	int resources_failed;
};

void LoadResources(pp::Instance* i)
{
	new eResourceLoader(i);
}

}
//namespace xPlatform

#endif//_CHROME_NACL