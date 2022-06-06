#pragma once

namespace sol
{
	template<typename T, size_t N>
	struct Vec
	{
		T data[N];
	};

	typedef Vec<float, 4> Vec4f;
	typedef Vec<float, 3> Vec3f;
	typedef Vec<float, 2> Vec2f;

	template<> struct Vec<float, 4>
	{
		union {float x, r;};
		union {float y, g;};
		union {float z, b;};
		union {float w, a;};

		Vec() = default;
		Vec(float scalar);
		Vec(float x, float y, float z, float w);
		Vec(float x, const Vec<float, 3>& yzw);
		Vec(const Vec<float, 3>& xyz, float w);
		Vec(float x, const Vec<float, 2>& yz, float w);
		Vec(const Vec<float, 2>& xy, float z, float w);
		Vec(float x, float y, const Vec<float, 2>& zw);

		const float& operator[](size_t i) const;
		float& operator[](size_t i);
		Vec<float, 4> operator*(float scalar) const;
		Vec<float, 4> operator+(const Vec<float, 4>& other) const;
	};

	template<> struct Vec<float, 3>
	{
		union {float x, r;};
		union {float y, g;};
		union {float z, b;};

		Vec() = default;
		Vec(float scalar);
		Vec(float x, float y, float z);
		Vec(const Vec<float, 2>& xy, float z);
		Vec(float x, const Vec<float, 2>& yz);
		Vec(const Vec<float, 4>& v);

		const float& operator[](size_t i) const;
		Vec<float, 3> operator*(float scalar) const;
		Vec<float, 3> operator+(const Vec<float, 3>& other) const;
		Vec<float, 3> operator-(const Vec<float, 3>& other) const;
		Vec<float, 3> operator-() const;
	};

	template<> struct Vec<float, 2>
	{	
		union {float x, r;};
		union {float y, g;};
		
		Vec() = default;
		Vec(float scalar);
		Vec(float x, float y);
		Vec(const Vec<float, 3>& v);
		Vec(const Vec<float, 4>& v);

		bool operator==(const Vec<float, 2>& other) const;
		bool operator!=(const Vec<float, 2>& other) const;
	};

	template<typename T, size_t R, size_t C> 
	struct Mat
	{

	};

	typedef Mat<float, 4, 4> Mat4f;

	template<> struct Mat<float, 4, 4>
	{
		using T = float;
		using Row_Type = Vec4f;
		using Col_Type = Vec4f;
		using Type = Mat<float, 4, 4>;

		Row_Type row[4];

		Mat() = default;
		Mat(T scalar);
		Mat(const Row_Type& v1, const Row_Type& v2, const Row_Type& v3, const Row_Type& v4);

		Row_Type operator*(const Row_Type& v4) const;
		Type operator*(const Type& v4) const;
		const Row_Type& operator[](size_t i) const;
		Row_Type& operator[](size_t i);
	};

	constexpr float Radians(float angle) { return angle * M_PI / 180.0f; }
	Vec3f Normalize(const Vec3f& v3) ;

	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/cross.xhtml
	Vec3f Cross(const Vec3f& u, const Vec3f& v);

	constexpr float Dot(const Vec3f& u, const Vec3f& v) { return (u.x*v.x + u.y*v.y + u.z*v.z); }

	Mat4f Transpose(const Mat4f& m);
	Mat4f Translate(const Mat4f& m, const Vec3f& v);

	// https://en.wikipedia.org/wiki/Rotation_matrix
	Mat4f RotateX(float t);
	Mat4f RotateY(float t);
	Mat4f RotateZ(float t);

	Mat4f Scale(float scalar);
	Mat4f Scale(const sol::Vec3f& scalar);

	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix
	Mat4f Perspective(float fov, float aspectRatio, float zNear, float zFar);

	// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
	// https://www.geertarien.com/blog/2017/07/30/breakdown-of-the-lookAt-function-in-OpenGL/
	Mat4f LookAt(const Vec3f& from, const Vec3f& to, const Vec3f& up = Vec3f(0.0f, 1.0f, 0.0f));
}
