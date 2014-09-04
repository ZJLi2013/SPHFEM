/* $Id: Vector.h,v 1.1.1.1 2005/05/01 15:18:55 ovidiom Exp $ */

#ifndef _VECTOR2F_H_
#define _VECTOR2F_H_

#include <cmath>


struct Vector2f
{
	float	x, z;

	inline Vector2f()
	{
		x = z = 0.0f;
	}
	
	inline Vector2f(float x,  float z)
	{
		this->x = x;
		this->z = z;
	}
	
	inline Vector2f(float xz)
	{
		x  = z = xz;
	}

	inline Vector2f(const float *xzArr)
	{
		x = xzArr[0];
		z = xzArr[1];
	}
	
	inline operator const float *() const
	{
		return ((const float *)&x);
	}
	
	inline float &operator[](unsigned int idx)
	{
		return (*(((float *)&x) + idx));
	}
	
	inline void operator +=(float s)
	{
		x += s;
		z += s;
	}
	
	inline void operator +=(const Vector2f &v)
	{
		x += v.x;
		z += v.z;
	}
	
	inline void operator -=(float s)
	{
		x -= s;
		z -= s;
	}
	
	inline void operator -=(const Vector2f &v)
	{
		x -= v.x;
		z -= v.z;
	}
	
	inline void operator *=(float s)
	{
		x *= s;
		z *= s;
	}
	
	inline void operator *=(const Vector2f &v)
	{
		x *= v.x;
		z *= v.z;
	}
	
	inline void operator /=(float s)
	{
		float	inv = 1.0f / s;

		x *= inv;
		z *= inv;
	}

	inline void operator /=(const Vector2f &v)
	{
		x /= v.x;
		z /= v.z;
	}
};


inline Vector2f operator +(const Vector2f &v, float s)
{
	return (Vector2f(v.x + s,  v.z + s));
}

inline Vector2f operator +(float s, const Vector2f &v)
{
	return (Vector2f(s + v.x,  s + v.z));
}

inline Vector2f operator +(const Vector2f &u, const Vector2f &v)
{
	return (Vector2f(u.x + v.x,  u.z + v.z));
}

inline Vector2f operator -(const Vector2f &v, float s)
{
	return (Vector2f(v.x - s, v.z - s));
}

inline Vector2f operator -(float s, const Vector2f &v)
{
	return (Vector2f(s - v.x,  s - v.z));
}

inline Vector2f operator -(const Vector2f &u, const Vector2f &v)
{
	return (Vector2f(u.x - v.x,  u.z - v.z));
}

inline Vector2f operator *(const Vector2f &v, float s)
{
	return (Vector2f(v.x * s, v.z * s));
}

inline Vector2f operator *(float s, const Vector2f &v)
{
	return (Vector2f(s * v.x, s * v.z));
}

inline Vector2f operator *(const Vector2f &u, const Vector2f &v)
{
	return (Vector2f(u.x * v.x,  u.z * v.z));
}

inline Vector2f operator /(const Vector2f &v, float s)
{
	float	inv = 1.0f / s;

	return (Vector2f(v.x * inv, v.z * inv));
}

inline Vector2f operator /(float s, const Vector2f &v)
{
	return (Vector2f(s / v.x, s / v.z));
}

inline Vector2f operator /(const Vector2f &u, const Vector2f &v)
{
	return (Vector2f(u.x / v.x,  u.z / v.z));
}

inline Vector2f operator -(const Vector2f &v)
{
	return (Vector2f(-v.x, -v.z));
}

inline float dot(const Vector2f &u, const Vector2f &v)
{
	return (u.x * v.x  + u.z * v.z);
}

/*
inline Vector2f cross(const Vector2f &u, const Vector2f &v)
{
	return (Vector2f(u.y * v.z - v.y * u.z,
	                 u.z * v.x - u.x * v.z,
	                 u.x * v.y - u.y * v.x));
}
*/


inline float length(const Vector2f &v)
{
	return ((float)sqrt(v.x * v.x  + v.z * v.z));
}

inline Vector2f normalize(const Vector2f &v)
{
	return (v / length(v));
}



#endif /* _VECTOR3F_H_ */

