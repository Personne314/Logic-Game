#pragma once



class Game {
public:

	Game(int width, int height);
	~Game();

	void render(double elapsed_time);

	bool isInit() const { return m_init; };

private:

	bool m_init;

};
