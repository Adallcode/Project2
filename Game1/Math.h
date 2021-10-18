#pragma once
#include <cmath>
#include <algorithm>
#include <limits>

namespace Math
{
	const float Pi = 3.14159f;
	const float PiOver2 = Pi / 2.0f;
	const float Epsilon = 0.001f;
	const float Zero = 0.f;

	//Infinity
	const float Infinity = std::numeric_limits<float>::infinity();
	const  float NegInfinity = -std::numeric_limits<float>::infinity();


	inline float ToRadian(float degree)
	{
		return degree * (Pi / 180.0f);
	}

	inline float ToDegree(float radian)
	{
		return radian * (180.0f / Pi);
	}

	inline float SquareRoot(float v)
	{
		return sqrtf(v);
	}

	inline bool NearZero(float value)
	{
		if (fabs(value) <= Epsilon)
		{
			return true;
		}

		return false;
	}

	inline float Cos(float theta)
	{
		return cosf(theta);
	}

	inline float Sine(float theta)
	{
		return sinf(theta);
	}

	inline float Tan(float theta)
	{
		return tanf(theta);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}

	inline float Atan(float z, float y)
	{
		return atan2f(z, y);
	}

	inline float Cot(float theta)
	{
		return 1.0f / Tan(theta);
	}


	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a > b ? a : b);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	inline float Lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}
}

class Vector3
{
public:
	Vector3()
	{
		x = 0.f; y = 0.f; z = 0.f;
	}


	explicit Vector3(float x1, float y1, float z1)
	{
		SetVector(x1, y1, z1);
	}

	

	void SetVector(float x1, float y1, float z1)
	{
		x = x1; y = y1; z = z1;
	}

	float x;
	float y;
	float z;


	//Operators Aritmetic normal no modifiable
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	friend Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	friend Vector3 operator*(float v, const Vector3& b)
	{
		return Vector3(v * b.x, v * b.y, v * b.z);
	}

	friend Vector3 operator/(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	}


	//Operators Aritmetic modifiable

	Vector3 &operator+=(const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;

		return *this;
	}

	Vector3 &operator-=(const Vector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;

		return *this;
	}

	Vector3 &operator*=(const Vector3& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;

		return *this;
	}

	Vector3 &operator/=(const Vector3& a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;

		return *this;
	}
	
	
	//Operators Aritmetic with a single value no modifiable
	friend Vector3 operator+(const Vector3& a, float v)
	{
		return Vector3(a.x + v, a.y + v, a.z + v);
	}

	friend Vector3 operator-(const Vector3& a, float v)
	{
		return Vector3(a.x - v, a.y - v, a.z - v);
	}

	friend Vector3 operator*(const Vector3& a, float v)
	{
		return Vector3(a.x * v, a.y * v, a.z * v);
	}

	friend Vector3 operator/(const Vector3& a, float v)
	{
		return Vector3(a.x / v, a.y / v, a.z / v);
	}


	//Operators Aritmetic with a single value  modifiable
	Vector3 &operator+=(float v)
	{
		x += v;
		y += v;
		z += v;

		return *this;
	}

	Vector3 &operator-=(float v)
	{
		x -= v;
		y -= v;
		z -= v;

		return *this;
	}

	Vector3 &operator*=(float v)
	{
		x *= v;
		y *= v;
		z *= v;

		return *this;
	}

	Vector3 &operator/=(float v)
	{
		x /= v;
		y /= v;
		z /= v;

		return *this;
	} 

	
	//Pointer to this class
	const float * const GetAsFloat()const
	{
		return reinterpret_cast<const float *>(&x);
	}


	//Normal funtions
	float Length(const Vector3& a)const
	{
		float tempX = a.x - x;
		float tempY = a.y - y;
		float tempZ = a.z - z;

		return Math::SquareRoot(tempX*tempX + tempY*tempY + tempZ*tempZ);
	}

	float Length()const
	{
		return Math::SquareRoot(x*x + y*y + z*z);
	}

	float LengthSq(const Vector3& a)const
	{
		float tempX = a.x - x;
		float tempY = a.y - y;
		float tempZ = a.z - z;

		return tempX*tempX + tempY * tempY + tempZ * tempZ;
	}

	float LengthSq()const
	{
		return (x*x + y * y + z * z);
	}

	void Normilize()
	{
		float d = Length();

		if (d > 0.f)
		{
			x /= d;
			y /= d;
			z /= d;
		}
	}

	static Vector3 Normilize(const Vector3& a)
	{
		Vector3 Temp = a;
		Temp.Normilize();

		return Temp;
	}

	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;

		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;

		return temp;
	}

	static float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	static Vector3 TransformByQuaternion(const Vector3& v, const class Quaternion& q);

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
};



//Matrix
class Matrix4
{
public:
	float mat[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	explicit Matrix4(const float m[4][4])
	{
		memcpy(mat, m, sizeof(float) * 4 * 4);
	}


	const float * const GetAsFloat()const
	{
		return reinterpret_cast<const float *>(&mat[0][0]);
	}

	//Transform vector
	Vector3 TransformVector3(const Vector3& a);

	// Invert the matrix - super slow
	void Invert();

	//Translation
	Vector3 GetTranslation()const { return Vector3(mat[3][0], mat[3][1], mat[3][2]); }


	friend Matrix4 operator*(const Matrix4& left, const Matrix4& right)
	{
		Matrix4 temp;
		//Row 0, 0
		temp.mat[0][0] =
			left.mat[0][0] * right.mat[0][0] +
			left.mat[0][1] * right.mat[1][0] +
			left.mat[0][2] * right.mat[2][0] +
			left.mat[0][3] * right.mat[3][0];

		//Row 0, 1
		temp.mat[0][1] =
			left.mat[0][0] * right.mat[0][1] +
			left.mat[0][1] * right.mat[1][1] +
			left.mat[0][2] * right.mat[2][1] +
			left.mat[0][3] * right.mat[3][1];

		//Row 0, 2
		temp.mat[0][2] =
			left.mat[0][0] * right.mat[0][2] +
			left.mat[0][1] * right.mat[1][2] +
			left.mat[0][2] * right.mat[2][2] +
			left.mat[0][3] * right.mat[3][2];

		//Row 0, 3
		temp.mat[0][3] =
			left.mat[0][0] * right.mat[0][3] +
			left.mat[0][1] * right.mat[1][3] +
			left.mat[0][2] * right.mat[2][3] +
			left.mat[0][3] * right.mat[3][3];

		//Row 1, 0
		temp.mat[1][0] =
			left.mat[1][0] * right.mat[0][0] +
			left.mat[1][1] * right.mat[1][0] +
			left.mat[1][2] * right.mat[2][0] +
			left.mat[1][3] * right.mat[3][0];

		//Row 1, 1
		temp.mat[1][1] =
			left.mat[1][0] * right.mat[0][1] +
			left.mat[1][1] * right.mat[1][1] +
			left.mat[1][2] * right.mat[2][1] +
			left.mat[1][3] * right.mat[3][1];

		//Row 1, 2
		temp.mat[1][2] =
			left.mat[1][0] * right.mat[0][2] +
			left.mat[1][1] * right.mat[1][2] +
			left.mat[1][2] * right.mat[2][2] +
			left.mat[1][3] * right.mat[3][2];

		//Row 1, 3
		temp.mat[1][3] =
			left.mat[1][0] * right.mat[0][3] +
			left.mat[1][1] * right.mat[1][3] +
			left.mat[1][2] * right.mat[2][3] +
			left.mat[1][3] * right.mat[3][3];


		//Row 2, 0
		temp.mat[2][0] =
			left.mat[2][0] * right.mat[0][0] +
			left.mat[2][1] * right.mat[1][0] +
			left.mat[2][2] * right.mat[2][0] +
			left.mat[2][3] * right.mat[3][0];

		//Row 2, 1
		temp.mat[2][1] =
			left.mat[2][0] * right.mat[0][1] +
			left.mat[2][1] * right.mat[1][1] +
			left.mat[2][2] * right.mat[2][1] +
			left.mat[2][3] * right.mat[3][1];

		//Row 2, 2
		temp.mat[2][2] =
			left.mat[2][0] * right.mat[0][2] +
			left.mat[2][1] * right.mat[1][2] +
			left.mat[2][2] * right.mat[2][2] +
			left.mat[2][3] * right.mat[3][2];

		//Row 2, 3
		temp.mat[2][3] =
			left.mat[2][0] * right.mat[0][3] +
			left.mat[2][1] * right.mat[1][3] +
			left.mat[2][2] * right.mat[2][3] +
			left.mat[2][3] * right.mat[3][3];

		
		//Row 3, 0
		temp.mat[3][0] =
			left.mat[3][0] * right.mat[0][0] +
			left.mat[3][1] * right.mat[1][0] +
			left.mat[3][2] * right.mat[2][0] +
			left.mat[3][3] * right.mat[3][0];

		//Row 3, 1
		temp.mat[3][1] =
			left.mat[3][0] * right.mat[0][1] +
			left.mat[3][1] * right.mat[1][1] +
			left.mat[3][2] * right.mat[2][1] +
			left.mat[3][3] * right.mat[3][1];

		//Row 3, 2
		temp.mat[3][2] =
			left.mat[3][0] * right.mat[0][2] +
			left.mat[3][1] * right.mat[1][2] +
			left.mat[3][2] * right.mat[2][2] +
			left.mat[3][3] * right.mat[3][2];

		//Row 3, 3
		temp.mat[3][3] =
			left.mat[3][0] * right.mat[0][3] +
			left.mat[3][1] * right.mat[1][3] +
			left.mat[3][2] * right.mat[2][3] +
			left.mat[3][3] * right.mat[3][3];

		return temp;
	}

	Matrix4 operator*=(const Matrix4& a)
	{
		*this = *this * a;
		return *this;
	}

	
	//Simple view
	static Matrix4 View(float width, float height)
	{
		float temp[4][4]
		{
			{2.f / width, 0.f, 0.f, 0.f},
			{0.f, 2.f / height, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 1.f, 1.f},
		};

		return Matrix4(temp);
	}


	static Matrix4 Lookat(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 Zaxis = Vector3::Normilize(target - eye);

		Vector3 Xaxis = Vector3::Normilize( Vector3::Cross(up, Zaxis) );

		Vector3 Yaxis = Vector3::Normilize(Vector3::Cross( Zaxis, Xaxis));

		float x = -Vector3::Dot(eye, Xaxis);
		float y = -Vector3::Dot(eye, Yaxis);
		float z = -Vector3::Dot(eye, Zaxis);

		float temp[4][4] =
		{
			{Xaxis.x, Yaxis.x, Zaxis.x, 0.f},
			{Xaxis.y, Yaxis.y, Zaxis.y, 0.f},
			{Xaxis.z, Yaxis.z, Zaxis.z, 0.f},
			{x,       y,       z,       1.f}
		};

		return Matrix4(temp);
	}


	static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
	{
		float yScale = Math::Cot(fovY / 2.0f);
		float xScale = yScale * height / width;
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, far / (far - near), 1.0f },
			{ 0.0f, 0.0f, -near * far / (far - near), 0.0f }
		};
		return Matrix4(temp);
	}


	//Scale
	static Matrix4 Scale(float scaleX, float scaleY)
	{
		float temp[4][4]
		{
			{scaleX, 0.f, 0.f, 0.f},
			{0.f, scaleY, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f},
		};

		return Matrix4(temp);
	}

	static Matrix4 Scale(float scale)
	{
		float temp[4][4]
		{
			{scale, 0.f, 0.f, 0.f},
			{0.f, scale, 0.f, 0.f},
			{0.f, 0.f, scale, 0.f},
			{0.f, 0.f, 0.f, 1.f},
		};

		return Matrix4(temp);
	}


	//Rotation about z
	static Matrix4 Rotation(float theta)
	{
		float cos = Math::Cos(theta);
		float sin = Math::Sine(theta);

		float temp[4][4]
		{
			{cos, sin, 0.f, 0.f},
			{-sin, cos, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f},
		};

		return Matrix4(temp);
	}

	//Rotation about y
	static Matrix4 RotationY(float theta)
	{
		float cos = Math::Cos(theta);
		float sin = Math::Sine(theta);

		float temp[4][4]
		{
			{cos, 0.f, -sin, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{sin, 0.f, cos, 0.f},
			{0.f, 0.f, 0.f, 1.f},
		};

		return Matrix4(temp);
	}

	//Rotation about X
	static Matrix4 RotationX(float theta)
	{
		float cos = Math::Cos(theta);
		float sin = Math::Sine(theta);

		float temp[4][4]
		{
			{1.f,  0.f, 0.f, 0.f},
			{0.f,  cos, sin, 0.f},
			{0.f, -sin, cos, 0.f},
			{0.f, 0.f, 0.f, 1.f},
		};

		return Matrix4(temp);
	}

	// Create a rotation matrix from a quaternion
	static Matrix4 CreateFromQuaternion(const class Quaternion& q);


	//Translate
	static Matrix4 Translate(const Vector3 & pos)
	{

		float temp[4][4]
		{
			{1.f, 0.f, 0.f, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{pos.x, pos.y, pos.z, 1.f},
		};

		return Matrix4(temp);
	}


	const static Matrix4 Identity;
};



// (Unit) Quaternion
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	explicit Quaternion(float inX, float inY, float inZ, float inW)
	{
		Set(inX, inY, inZ, inW);
	}

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	explicit Quaternion(const Vector3& axis, float angle)
	{
		float scalar = Math::Sine(angle / 2.0f);
		x = axis.x * scalar;
		y = axis.y * scalar;
		z = axis.z * scalar;
		w = Math::Cos(angle / 2.0f);
	}

	// Directly set the internal components
	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	void Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	float LengthSq() const
	{
		return (x*x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Math::SquareRoot(LengthSq());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	// Normalize the provided quaternion
	static Quaternion Normalize(const Quaternion& q)
	{
		Quaternion retVal = q;
		retVal.Normalize();
		return retVal;
	}

	// Linear interpolation
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
	{
		Quaternion retVal;
		retVal.x = Math::Lerp(a.x, b.x, f);
		retVal.y = Math::Lerp(a.y, b.y, f);
		retVal.z = Math::Lerp(a.z, b.z, f);
		retVal.w = Math::Lerp(a.w, b.w, f);
		retVal.Normalize();
		return retVal;
	}

	static float Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	// Spherical Linear Interpolation
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
	{
		float rawCosm = Quaternion::Dot(a, b);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float omega = Math::Acos(cosom);
			const float invSin = 1.f / Math::Sine(omega);
			scale0 = Math::Sine((1.f - f) * omega) * invSin;
			scale1 = Math::Sine(f * omega) * invSin;
		}
		else
		{
			// Use linear interpolation if the quaternions
			// are collinear
			scale0 = 1.0f - f;
			scale1 = f;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion retVal;
		retVal.x = scale0 * a.x + scale1 * b.x;
		retVal.y = scale0 * a.y + scale1 * b.y;
		retVal.z = scale0 * a.z + scale1 * b.z;
		retVal.w = scale0 * a.w + scale1 * b.w;
		retVal.Normalize();
		return retVal;
	}

	// Concatenate
	// Rotate by q FOLLOWED BY p
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	{
		Quaternion retVal;

		// Vector component is:
		// ps * qv + qs * pv + pv x qv
		Vector3 qv(q.x, q.y, q.z);
		Vector3 pv(p.x, p.y, p.z);
		Vector3 newVec = p.w * qv + q.w * pv + Vector3::Cross(pv, qv);
		retVal.x = newVec.x;
		retVal.y = newVec.y;
		retVal.z = newVec.z;

		// Scalar component is:
		// ps * qs - pv . qv
		retVal.w = p.w * q.w - Vector3::Dot(pv, qv);

		return retVal;
	}

	static const Quaternion Identity;
};

namespace Color
{
	static const Vector3 Black(0.0f, 0.0f, 0.0f);
	static const Vector3 White(1.0f, 1.0f, 1.0f);
	static const Vector3 Red(1.0f, 0.0f, 0.0f);
	static const Vector3 Green(0.0f, 1.0f, 0.0f);
	static const Vector3 Blue(0.0f, 0.0f, 1.0f);
	static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
	static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
	static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
	static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
	static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}