#include "pch.h"
#define SFML_STATIC
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-s-d.lib")
#pragma comment(lib,"sfml-audio-s-d.lib")
#pragma comment(lib,"sfml-system-s-d.lib")
#pragma comment(lib,"sfml-window-s-d.lib")
#pragma comment(lib,"sfml-network-s-d.lib")
#else
#pragma comment(lib,"sfml-graphics-s.lib")
#pragma comment(lib,"sfml-audio-s.lib")
#pragma comment(lib,"sfml-system-s.lib")
#pragma comment(lib,"sfml-window-s.lib")
#pragma comment(lib,"sfml-network-s.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"freetype.lib")


#include <SFML\System\Vector2.hpp>
#include "../Easing/Viewport.h"

//TEST(TestCaseName, TestName) {
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);
//}

TEST(CornersMappedCorrectly, Viewport) {
	Viewport vp(100, 100, 10, 10, 1000,1000);

	auto p = vp.screenSpace(sf::Vector2f(0,0));
	EXPECT_EQ(10, p.x);
	EXPECT_EQ(990, p.y);

	auto q = vp.screenSpace(sf::Vector2f(1, 1));
	EXPECT_EQ(110, q.x);
	EXPECT_EQ(890, q.y);


}
