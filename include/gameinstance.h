/*
 * gameinstance.h
 *
 *  Created on: 4 Jan 2011
 *      Author: owen
 */

#ifndef GAMEINSTANCE_H_
#define GAMEINSTANCE_H_

class gameInstance
{
public:
	gameInstance();
	virtual void Unload();
	virtual void Load();
	inline const bool& Running() {return m_bRunning;}
	virtual void Step();

	virtual void KeyUp		(const int& iKeyEnum);
	virtual void KeyDown		(const int& iKeyEnum);

	virtual void MouseMoved		(const int& iButton,
					 const int& iX,
					 const int& iY,
					 const int& iRelX,
					 const int& iRelY);
	virtual void MouseButtonUp	(const int& iButton,
					 const int& iX,
					 const int& iY,
					 const int& iRelX,
					 const int& iRelY);
	virtual void MouseButtonDown	(const int& iButton,
					 const int& iX,
					 const int& iY,
					 const int& iRelX,
					 const int& iRelY);
	virtual void WindowActive();
	virtual void WindowInactive();
protected:
	bool m_bRunning;
};

#endif /* GAMEINSTANCE_H_ */
