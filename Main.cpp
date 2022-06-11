#include <Application.h>
#include <Utility/Matrix.h>
#include <Utility/Vertex.h>

bool operator==(const glm::mat4& m1, const sol::Mat4f& m2)
{
	return m1[0][0] == m2[0][0] && m1[0][1] == m2[0][1] && m1[0][2] == m2[0][2] && m1[0][3] == m2[0][3]
		&& m1[1][0] == m2[1][0] && m1[1][1] == m2[1][1] && m1[1][2] == m2[1][2] && m1[1][3] == m2[1][3]
		&& m1[2][0] == m2[2][0] && m1[2][1] == m2[2][1] && m1[2][2] == m2[2][2] && m1[2][3] == m2[2][3]
		&& m1[3][0] == m2[3][0] && m1[3][1] == m2[3][1] && m1[3][2] == m2[3][2] && m1[3][3] == m2[3][3];
}

int main()
{	

	sol::Vec2f v1 = {0.5f, 0.5f};
	glm::vec2 v2 = {0.5f, 0.5f};

	sol::Mat4f rotate = sol::RotateZ(sol::Radians(45.0f));
	glm::mat4 grotate = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	std::cout << (grotate == rotate) << std::endl;

	sol::Mat4f scale = sol::Scale(sol::Vec3f(1.0f, 2.0f, 3.0f));
	glm::mat4 gscale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f));

	std::cout << (grotate == rotate) << std::endl;

	sol::Mat4f transl = sol::Translate(sol::Mat4f(1.0f), sol::Vec3f(10.0f, 12.0f, 15.0f));
	glm::mat4 gtransl = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 12.0f, 15.0f));

	std::cout << (grotate == rotate) << std::endl;

	sol::Mat4f model = transl * rotate * scale;

	glm::mat4 gmodel = gtransl * grotate * gscale;


	// std::cout << model[0][0] << " " << model[0][1] << " "<< model[0][2] << " " << model[0][3] << std::endl;
	// std::cout << model[1][0] << " " << model[1][1] << " "<< model[1][2] << " " << model[1][3] << std::endl;
	// std::cout << model[2][0] << " " << model[2][1] << " "<< model[2][2] << " " << model[2][3] << std::endl;
	// std::cout << model[3][0] << " " << model[3][1] << " "<< model[3][2] << " " << model[3][3] << std::endl;
	// std::cout << std::endl;
	// std::cout << gmodel[0][0] << " " << gmodel[0][1] << " "<< gmodel[0][2] << " " << gmodel[0][3] << std::endl;
	// std::cout << gmodel[1][0] << " " << gmodel[1][1] << " "<< gmodel[1][2] << " " << gmodel[1][3] << std::endl;
	// std::cout << gmodel[2][0] << " " << gmodel[2][1] << " "<< gmodel[2][2] << " " << gmodel[2][3] << std::endl;
	// std::cout << gmodel[3][0] << " " << gmodel[3][1] << " "<< gmodel[3][2] << " " << gmodel[3][3] << std::endl;


	v1 = sol::Vec2f(model * sol::Vec4f(v1, 0.0f, 1.0f));
	v2 = glm::vec2(gmodel * glm::vec4(v2, 0.0f, 1.0f));

	std::cout << v1.x << " " << v1.y << std::endl;
	std::cout << v2.x << " " << v2.y << std::endl;

	// We create a pointer with an application and run it immediately
	std::unique_ptr<Application> app = std::make_unique<Application>("Cartesian Plotter");
	app->SetVsync(true);
	app->Run(1920, 1000);
}

/*
TODO: AABB not being rendered correctly
*/