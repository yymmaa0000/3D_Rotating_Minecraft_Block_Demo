#include "camera.h"
#include "object.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

int main() {
	Camera camera;
	//Cube cube;
	Plank plank;

	FsOpenWindow(16, 16,WINDOW_X,WINDOW_Y, 1);
	bool gameover = false;
	while (!gameover) {

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key) gameover = true;

		camera.move();
		//cube.draw(camera);
		plank.draw(camera);

		FsSwapBuffers();

		FsSleep(20);
	}
	return 0;
}