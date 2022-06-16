#include <Utility/Matrix.h>

#include <cstddef>
#include <iostream>
#include <cmath>

namespace sol
{
	Vec<float, 4>::Vec(float scalar)
	{
		this->x = scalar;
		this->y = scalar;
		this->z = scalar;
		this->w = scalar;
	}
	Vec<float, 4>::Vec(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	Vec<float, 4>::Vec(float x, const Vec<float, 3>& yzw)
	{
		this->x = x;
		this->y = yzw.x;
		this->z = yzw.y;
		this->z = yzw.z;
	}
	Vec<float, 4>::Vec(const Vec<float, 3>& xyz, float w)
	{
		this->x = xyz.x;
		this->y = xyz.y;
		this->z = xyz.z;
		this->w = w;
	}
	Vec<float, 4>::Vec(float x, const Vec<float, 2>& yz, float w)
	{
		this->x = x;
		this->y = yz.x;
		this->z = yz.y;
		this->w = w;
	}
	Vec<float, 4>::Vec(const Vec<float, 2>& xy, float z, float w)
	{
		this->x = xy.x;
		this->y = xy.y;
		this->z = z;
		this->w = w;
	}
	Vec<float, 4>::Vec(float x, float y, const Vec<float, 2>& zw)
	{
		this->x = x;
		this->y = y;
		this->z = zw.x;
		this->w = zw.y;
	}
	const float& Vec<float, 4>::operator[](size_t i) const { return *(reinterpret_cast<const float*>(this) + i); }
	float& Vec<float, 4>::operator[](size_t i) { return *(reinterpret_cast<float*>(this) + i); }
	Vec4f Vec<float, 4>::operator*(float scalar) const
	{
		return { this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar };
	}
	Vec4f Vec<float, 4>::operator+(const Vec4f& other) const
	{
		return { this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w };
	}



	Vec<float, 3>::Vec(float scalar)
	{
		this->x = scalar;
		this->y = scalar;
		this->z = scalar;
	}
	Vec<float, 3>::Vec(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec<float, 3>::Vec(const Vec<float, 2>& xy, float z)
	{
		this->x = xy.x;
		this->y = xy.y;
		this->z = z;
	}
	Vec<float, 3>::Vec(float x, const Vec<float, 2>& yz)
	{
		this->x = x;
		this->y = yz.x;
		this->z = yz.y;
	}
	Vec<float, 3>::Vec(const Vec4f& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
	const float& Vec<float, 3>::operator[](size_t i) const { return *(reinterpret_cast<const float*>(this) + i); }
	Vec3f Vec<float, 3>::operator*(float scalar) const
	{
		return { this->x * scalar, this->y * scalar, this->z * scalar };
	}
	Vec3f Vec<float, 3>::operator+(const Vec3f& other) const
	{
		return { this->x + other.x, this->y + other.y, this->z + other.z };
	}
	Vec3f Vec<float, 3>::operator-(const Vec3f& other) const
	{
		return *this + Vec3f(-other.x, -other.y, -other.z);
	}
	Vec3f Vec<float, 3>::operator-() const
	{
		return { -this->x, -this->y, -this->z };
	}



	Vec<float, 2>::Vec(float scalar)
	{
		this->x = scalar;
		this->y = scalar;
	}
	Vec<float, 2>::Vec(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vec<float, 2>::Vec(const Vec3f& v)
	{
		this->x = v.x;
		this->y = v.y;
	}
	Vec<float, 2>::Vec(const Vec4f& v)
	{
		this->x = v.x;
		this->y = v.y;
	}
	bool Vec<float, 2>::operator==(const Vec2f& other) const
	{
		return (this->x == other.x && this->y == other.y);
	}
	bool Vec<float, 2>::operator!=(const Vec2f& other) const
	{
		return !(*this == other);
	}



	Mat<Mat4f::T, 4, 4>::Mat(T scalar)
	{
		row[0] = Vec4f(scalar, 0.0f, 0.0f, 0.0f);
		row[1] = Vec4f(0.0f, scalar, 0.0f, 0.0f);
		row[2] = Vec4f(0.0f, 0.0f, scalar, 0.0f);
		row[3] = Vec4f(0.0f, 0.0f, 0.0f, scalar);
	}
	Mat<Mat4f::T, 4, 4>::Mat(
		const Vec4f& v1, 
		const Vec4f& v2, 
		const Vec4f& v3, 
		const Vec4f& v4)
	{
		row[0] = v1;
		row[1] = v2;
		row[2] = v3;
		row[3] = v4;
	}
	Vec4f Mat<Mat4f::T, 4, 4>::operator*(const Vec4f& v4) const
	{
		return 
		{
			(*this)[0][0] * v4.x + (*this)[0][1] * v4.y + (*this)[0][2] * v4.z + (*this)[0][3] * v4.w, 
			(*this)[1][0] * v4.x + (*this)[1][1] * v4.y + (*this)[1][2] * v4.z + (*this)[1][3] * v4.w,
			(*this)[2][0] * v4.x + (*this)[2][1] * v4.y + (*this)[2][2] * v4.z + (*this)[2][3] * v4.w,
			(*this)[3][0] * v4.x + (*this)[3][1] * v4.y + (*this)[3][2] * v4.z + (*this)[3][3] * v4.w
		};
	}
	Mat4f Mat<Mat4f::T, 4, 4>::operator*(const Mat4f& m4) const
	{
		Mat4f result(1.0f);
		for (size_t r = 0; r < 4; r++)
		{
			for (size_t c = 0; c < 4; c++)
			{
				result[r][c] = (*this)[r][0] * m4[0][c]
					+ (*this)[r][1] * m4[1][c]
					+ (*this)[r][2] * m4[2][c]
					+ (*this)[r][3] * m4[3][c];
			}
		}
		return result;
	}
	const Mat4f::Row_Type& Mat<Mat4f::T, 4, 4>::operator[](size_t i) const { return this->row[i]; }
	Mat4f::Row_Type& Mat<Mat4f::T, 4, 4>::operator[](size_t i) { return this->row[i]; }



	Vec3f Normalize(const Vec3f& v3) 
	{
		float magnitude = sqrtf(v3.x*v3.x + v3.y*v3.y + v3.z*v3.z);
		return { v3.x / magnitude, v3.y / magnitude, v3.z / magnitude };
	}

	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/cross.xhtml
	Vec3f Cross(const Vec3f& u, const Vec3f& v)
	{
		return
		{
			u[1] * v[2] - v[1] * u[2],
			u[2] * v[0] - v[2] * u[0],
			u[0] * v[1] - v[0] * u[1]
		};
	}

	Mat4f Transpose(const Mat4f& m)
	{
		return
		{
			Vec4f(m[0][0], m[1][0], m[2][0], m[3][0]),
			Vec4f(m[0][1], m[1][1], m[2][1], m[3][1]),
			Vec4f(m[0][2], m[1][2], m[2][2], m[3][2]),
			Vec4f(m[0][3], m[1][3], m[2][3], m[3][3])
		};
	}

	Mat4f Translate(const Mat4f& m, const Vec3f& v)
	{
		Mat4f result(m);
		result[3] = m[0]*v[0] + m[1]*v[1] + m[2]*v[2] + m[3];
		return Transpose(result);
	}

	// https://en.wikipedia.org/wiki/Rotation_matrix
	Mat4f RotateX(float t)
	{
		return
		{
			Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
			Vec4f(0.0f, cos(t), sin(t), 0.0f),
			Vec4f(0.0f, -sin(t), cos(t), 0.0f),
			Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
		};
	}
	Mat4f RotateY(float t)
	{
		return
		{
			Vec4f(cos(t), 0.0f, -sin(t), 0.0f),
			Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
			Vec4f(sin(t), 0.0f, cos(t), 0.0f),
			Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
		};
	}
	Mat4f RotateZ(float t)
	{
		return
		{
			Vec4f(cos(t), -sin(t), 0.0f, 0.0f),
			Vec4f(sin(t), cos(t), 0.0f, 0.0f),
			Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
		};
	}

	Mat4f Scale(float scalar)
	{
		return 
		{
			Vec4f(scalar, 0.0f, 0.0f, 0.0f),
			Vec4f(0.0f, scalar, 0.0f, 0.0f),
			Vec4f(0.0f, 0.0f, scalar, 0.0f),
			Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
		};
	}

	Mat4f Scale(const sol::Vec3f& scalar)
	{
		return 
		{
			Vec4f(scalar.x, 0.0f, 0.0f, 0.0f),
			Vec4f(0.0f, scalar.y, 0.0f, 0.0f),
			Vec4f(0.0f, 0.0f, scalar.z, 0.0f),
			Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
		};
	}


	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix
	Mat4f Perspective(float fov, float aspectRatio, float zNear, float zFar)
	{
		float top = tan(fov / 2.0f) * zNear;
		float bottom = -top;
		float right = top * aspectRatio;
		float left = -right;

		Mat4f result(0.0f);
		
		result[0][0] = (2 * zNear) / (right - left);
		result[1][1] = (2 * zNear) / (top - bottom);
		result[2][0] = (right + left) / (right - left);
		result[2][1] = (top + bottom) / (top - bottom);
		result[2][2] = - (zFar + zNear) / (zFar - zNear);
		result[2][3] = -1.0f;
		result[3][2] = - (2 * zFar * zNear) / (zFar - zNear);
		
		return result;
	}

	// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
	// https://www.geertarien.com/blog/2017/07/30/breakdown-of-the-lookAt-function-in-OpenGL/
	Mat4f LookAt(const Vec3f& from, const Vec3f& to, const Vec3f& up)
	{
		Vec3f f = Normalize(to - from);
		Vec3f r = Normalize(Cross(f, up));
		Vec3f u = Cross(r, f);

		Mat4f result(1.0f);

		result[0][0] = r.x;
		result[0][1] = r.y;
		result[0][2] = r.z;
		result[1][0] = u.x;
		result[1][1] = u.y;
		result[1][2] = u.z;
		result[2][0] = f.x;
		result[2][1] = f.y;
		result[2][2] = f.z;
		result[3][0] = -from.x;
		result[3][1] = -from.y;
		result[3][2] = -from.z;
		return result;
	}
}