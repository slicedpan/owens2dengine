/*
 * engine.h
 *
 *  Created on: 4 Jan 2011
 *      Author: owen
 */

#ifndef ENGINE_H_
#define ENGINE_H_

class gameInstance;

class gameEngine
{
public:
	gameEngine();
	void Start();
	void Init();
	void End();
	~gameEngine();
	void loadInstance(gameInstance * p_gi_ptr);
	static gameEngine * GetSingleton();
	void HandleInput();
private:
	bool m_bQuit, m_bMinimized;
	gameInstance * gi_ptr, * nextInstance;
	static gameEngine * ge_ptr;
};

#endif /* ENGINE_H_ */
