#pragma once

struct Vector2
{
	float x, y;
};
typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (Vector3 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	const Vector3& operator* (const float mul)
	{
		return Vector3(this->x *= mul, this->y *= mul, this->z *= mul);
	}

	const bool operator != (Vector3 const &Vector)
	{
		return (this->x != Vector.x && this->y != Vector.y && this->z != Vector.z);
	}
	const Vector3& operator+ (Vector3 const &Vector)
	{
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	const Vector3& operator- (Vector3 const &Vector)
	{
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}
	float Distance(Vector3 const &Vector)
	{
		return sqrt(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const &Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}

	Vector3 crossVector3D(const Vector3 &vec) const
	{
		return Vector3(y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x);
	}

	inline float Length(void) const { return (float)sqrtf(x*x + y * y + z * z); }

	inline Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}

	Vector3 GetForwardVector() const
	{
		return Vector3(2 * (x * z + 1 * y),
			2 * (y * x - 1 * x),
			1 - 2 * (x * x + y * y));
	}
	Vector3 GetUpVector() const
	{
		return Vector3(2 * (x * y - 1 * z),
			1 - 2 * (x * x + z * z),
			2 * (y * z + 1 * x));
	}

	Vector3 GetRightVector() const
	{
		return Vector3(1 - 2 * (y * y + z * z),
			2 * (x * y + 1 * z),
			2 * (x * z - 1 * y));
	}


} Vector3, *PVector3;

typedef struct Vector4
{
	float x, y, z, a;

	Vector4()
	{
		x = y = z = a = 0;
	}
	Vector4(float x, float y, float z, float a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}
	const bool operator== (Vector4 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z && this->a == Vector.z);
	}
	const bool operator != (Vector4 const &Vector)
	{
		return (this->x != Vector.x && this->y != Vector.y && this->z != Vector.z && this->a != Vector.a);
	}
	const Vector4& operator+ (Vector4 const &Vector)
	{
		return Vector4(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z, this->a + Vector.a);
	}
	const Vector4& operator- (Vector4 const &Vector)
	{
		return Vector4(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z, this->a - Vector.a);
	}
	float DotProduct(Vector4 const &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z) + (this->a * Vector.a);
	}

	inline float Length(void) const { return (float)sqrtf(x*x + y * y + z * z + a * a); }

} Vector4, *PVector4;

typedef struct
{
	float r, g, b, a;
} Color;

typedef struct
{
	float height, width, intensity;
} Dimensions;