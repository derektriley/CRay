#include "rtlib.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//Driver program
int main(int argc, char **argv) {
	Scene scene; //Scene to raytrace
	float r1, r2, r3;
	int radius;
	srand (static_cast <unsigned> (time(0))); /* initialize random seed: */


	for (int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++) {
				/* generate a number between 0 and 255: */
				r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				Vector3d c((float)r1, (float)r2, (float)r3);
				radius = 20.0f;
				Vector3d p(-100.0f + (i * 100.0f), -100.0f + (j * 100.0f), -700.0f - (k * 200.0f));
				Sphere* s = new Sphere(radius, p, c);
				scene.objects.push_back((Object*)s);
			}
	Light light(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f), Vector3d(1.0f, 1.0f, 1.0f), 200.0f, 1.0f);
	/*Sphere obj(50.0f, Vector3d(0.0f, 0.0f, -700.0f), Vector3d(0.0f, 1.0f, 0.0f));
	Sphere obj2(50.0f, Vector3d(-100.0f, 0.0f, -700.0f), Vector3d(1.0f, 0.0f, 0.0f));
	Sphere obj3(50.0f, Vector3d(100.0f, 0.0f, -700.0f), Vector3d(0.0f, 0.0f, 1.0f));
	Sphere obj4(50.0f, Vector3d(0.0f, 100.0f, -700.0f), Vector3d(0.5f, 0.2f, 0.0f));
	Sphere obj5(50.0f, Vector3d(0.0f, -100.0f, -700.0f), Vector3d(0.0f, 0.5f, 0.5f));
	scene.objects.push_back((Object*)&obj);
	scene.objects.push_back((Object*)&obj2);
	scene.objects.push_back((Object*)&obj3);
	scene.objects.push_back((Object*)&obj4);
	scene.objects.push_back((Object*)&obj5);*/
	scene.lights.push_back((Object*)&light);
	Tracer(stdout, scene);
	return 0;
}
