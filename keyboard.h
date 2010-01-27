#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "device.h"

#pragma once

class eKeyboard : public eDevice
{
public:
	virtual void Init();
	virtual void Reset();
	virtual void IoRead(word port, byte* v);
	void OnKey(char key, bool down, bool shift, bool ctrl, bool alt);

protected:
	void KeyState(char key, bool down);
	byte Read(byte scan) const;
	byte kbd[8];
};

#endif//__KEYBOARD_H__