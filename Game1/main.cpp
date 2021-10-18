#include <iostream>
#include "Game.h"
#include "Collision.h"
#include "Math.h"

using namespace std;




int main(int argc, char** argv)
{
	
	/*Game game;
	
	bool s = game.Initialize();

	if (s)
	{
		
		game.Running();
	}
	game.Shutdown();*/

	
	
	Vector3 f = Vector3(0.f, -0.5f, -0.5f);
	f.Normilize();

	std::cout << "Facing\n";
	std::cout << "x: " << f.x << "  y: " << f.y << "  z: " << f.z  << "\n";

	Vector3 a, b;

	a = Vector3::Zero;
	b = Vector3(0.f, 5.f, 5.f);

	Vector3 to = Vector3::Normilize( b - a);

	std::cout << "\nTo Facing\n";
	std::cout << "x: " << to.x << "  y: " << to.y << "  z: " << to.z << "\n";

	Vector3 axis = Vector3::Cross(f, to);

	float angle = Math::Acos(Vector3::Dot(f, to));

	
	
	std::cout << "\nAngle: " << angle << "\n";



	Quaternion newQ = Quaternion(axis, angle);

	std::cout << "\nNew Quaternion\n";
	std::cout << "x: " << newQ.x << "  y: " << newQ.y << "  z: " << newQ.z << "  w: " << newQ.w << "\n";

	
	
	Matrix4 ro = Matrix4::RotationX(angle);
	Vector3 temp;
	temp.y = f.y;
	f.y = ro.TransformVector3(temp).y;

	ro = Matrix4::RotationY(angle);
	temp = Vector3::Zero;
	temp.z = f.z;
	f.z = ro.TransformVector3(temp).z;

	//f = ro.TransformVector3(f);

	std::cout << "\nNew Facing\n";
	std::cout << "x: " << f.x << "  y: " << f.y << "  z: " << f.z  << "\n";


	return 0;
}