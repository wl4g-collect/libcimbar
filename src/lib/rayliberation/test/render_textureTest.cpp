/* This code is subject to the terms of the Mozilla Public License, v.2.0. http://mozilla.org/MPL/2.0/. */
#include "unittest.h"

#include "render_texture.h"
#include "texture.h"
#include "RayCommon.h"

#include "raylib.h"
#include "serialize/format.h"
#include <iostream>
#include <string>
using std::string;

TEST_CASE( "render_textureTest/testDefault", "[unit]" )
{
	InitWindow(1024, 1024, "test raylib");
	cimbar::render_texture rt(1024, 1024, BLACK);
	cimbar::texture tx = cimbar::load_texture("bitmap/4/00.png");

	rt.paste(tx, 10, 10);

	tx.copyTo(rt({20, 20, tx.cols, tx.rows}));

	BeginDrawing();
	ClearBackground(BLACK);
	rt.draw();

	EndDrawing();

	assertEquals(true, true);

	/*
	for (int i = 0; i < 1000000; ++i)
		std::cout << "hello" << i << std::endl;
	//*/
}