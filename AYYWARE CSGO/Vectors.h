#pragma once
#include "stdafx.h"
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

inline float isqrt(float _Xx);
class Vector;
Vector CrossProduct(Vector& a, Vector& b);


class Vector
{
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	__forceinline Vector&	operator+=(const Vector &v);
	__forceinline Vector&	operator-=(const Vector &v);
	__forceinline Vector&	operator*=(const Vector &v);
	__forceinline Vector&	operator*=(float s);
	__forceinline Vector&	operator/=(const Vector &v);
	__forceinline Vector&	operator/=(float s);
	__forceinline Vector&	operator+=(float fl);
	__forceinline Vector&	operator-=(float fl);
	inline float	Length() const;

	__forceinline float  Vector::LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x*x + y*y + z*z);
	}

	bool  Vector::IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
	float	NormalizeInPlace();
	Vector Vector::Normalized() const {
		Vector res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}
	__forceinline float	DistToSqr(const Vector &vOther) const;
	float	Dot(const Vector& vOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	Vector& operator=(const Vector &vOther);
	Vector	operator-(void) const;
	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;

	inline Vector Vector::Cross(Vector& vOther)
	{
		Vector res;
		res = CrossProduct(*this, vOther);
		return res;
	}

};
class VectorAligned : public Vector
{
public:
	VectorAligned();
	VectorAligned(const Vector& in);
	float w;
};


inline void VectorClear(Vector& a);
__forceinline void VectorCopy(const Vector& src, Vector& dst);

inline float VectorLength(const Vector& v)
{
	return (float)isqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// poop
//===============================================
inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}
//===============================================
inline Vector::Vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}
//===============================================
inline Vector::Vector(void) { }
//===============================================
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline Vector& Vector::operator=(const Vector &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& Vector::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float Vector::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool Vector::operator==(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool Vector::operator!=(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
__forceinline void VectorCopy(const Vector& src, Vector& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
__forceinline  Vector& Vector::operator+=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
__forceinline  Vector& Vector::operator-=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
__forceinline  Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  Vector& Vector::operator*=(const Vector& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline Vector&	Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline Vector&	Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  Vector& Vector::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  Vector& Vector::operator/=(const Vector& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline float Vector::Length(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqsr = x*x + y*y + z*z;

	__asm
	{
		sqrtss xmm0, sqsr
		movss root, xmm0
	}

	return root;
}
//===============================================
inline float Vector::Length2D(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqst = x*x + y*y;

	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}

	return root;
}
//===============================================
inline float Vector::Length2DSqr(void) const
{
	return (x*x + y*y);
}
//===============================================
inline Vector CrossProduct(Vector& a, Vector& b)
{
	return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
//===============================================
float Vector::DistToSqr(const Vector &vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}
//===============================================
inline float Vector::NormalizeInPlace()
{
	Vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;
	return 0.f;
}
//===============================================
inline Vector Vector::operator+(const Vector& v) const
{
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}
//===============================================
inline Vector Vector::operator-(const Vector& v) const
{
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline Vector Vector::operator*(float fl) const
{
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline Vector Vector::operator*(const Vector& v) const
{
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline Vector Vector::operator/(float fl) const
{
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline Vector Vector::operator/(const Vector& v) const
{
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

class Vector2D
{
public:
	// Members
	float x, y;

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// Initialization methods
	void Random(float minVal, float maxVal);

	// equality
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	// arithmetic operations
	Vector2D&	operator+=(const Vector2D &v);
	Vector2D&	operator-=(const Vector2D &v);
	Vector2D&	operator*=(const Vector2D &v);
	Vector2D&	operator*=(float s);
	Vector2D&	operator/=(const Vector2D &v);
	Vector2D&	operator/=(float s);

	// negate the Vector2D components
	void	Negate();

	// Get the Vector2D's magnitude.
	float	Length() const;

	// Get the Vector2D's magnitude squared.
	float	LengthSqr(void) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	// Normalize in place and return the old length.
	float	NormalizeInPlace();

	// Compare length.
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// Get the distance from this Vector2D to the other one.
	float	DistTo(const Vector2D &vOther) const;

	// Get the distance from this Vector2D to the other one squared.
	float	DistToSqr(const Vector2D &vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector2D equation (because it's done per-component
	// rather than per-Vector2D).
	void	MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

	// Dot product.
	float	Dot(const Vector2D& vOther) const;

	// assignment
	Vector2D& operator=(const Vector2D &vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	Vector2D(const Vector2D &vOther);

	// arithmetic operations
	Vector2D	operator-(void) const;

	Vector2D	operator+(const Vector2D& v) const;
	Vector2D	operator-(const Vector2D& v) const;
	Vector2D	operator*(const Vector2D& v) const;
	Vector2D	operator/(const Vector2D& v) const;
	Vector2D	operator*(float fl) const;
	Vector2D	operator/(float fl) const;

	// Cross product between two vectors.
	Vector2D	Cross(const Vector2D &vOther) const;

	// Returns a Vector2D with the min or max in X, Y, and Z.
	Vector2D	Min(const Vector2D &vOther) const;
	Vector2D	Max(const Vector2D &vOther) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	Vector2D(const Vector2D& vOther);
#endif
};

//=========================================================
// 4D Vector4D
//=========================================================

class Vector4D
{
public:
	// Members
	float x, y, z, w;

	// Construction/destruction
	Vector4D(void);
	Vector4D(float X, float Y, float Z, float W);
	Vector4D(const float *pFloat);

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f, float iw = 0.0f);
	void Init(const Vector& src, float iw = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	inline float* Base();
	inline float const* Base() const;

	// Cast to Vector and Vector2D...
	Vector& AsVector3D();
	Vector const& AsVector3D() const;

	Vector2D& AsVector2D();
	Vector2D const& AsVector2D() const;

	// Initialization methods
	void Random(float minVal, float maxVal);

	// equality
	bool operator==(const Vector4D& v) const;
	bool operator!=(const Vector4D& v) const;

	// arithmetic operations
	Vector4D&	operator+=(const Vector4D &v);
	Vector4D&	operator-=(const Vector4D &v);
	Vector4D&	operator*=(const Vector4D &v);
	Vector4D&	operator*=(float s);
	Vector4D&	operator/=(const Vector4D &v);
	Vector4D&	operator/=(float s);

	Vector4D	operator-(void) const;
	Vector4D	operator*(float fl) const;
	Vector4D	operator/(float fl) const;
	Vector4D	operator*(const Vector4D& v) const;
	Vector4D	operator+(const Vector4D& v) const;
	Vector4D	operator-(const Vector4D& v) const;

	// negate the Vector4D components
	void	Negate();

	// Get the Vector4D's magnitude.
	float	Length() const;

	// Get the Vector4D's magnitude squared.
	float	LengthSqr(void) const;

	// return true if this vector is (0,0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance &&
			w > -tolerance && w < tolerance);
	}

	// Get the distance from this Vector4D to the other one.
	float	DistTo(const Vector4D &vOther) const;

	// Get the distance from this Vector4D to the other one squared.
	float	DistToSqr(const Vector4D &vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector4D equation (because it's done per-component
	// rather than per-Vector4D).
	void	MulAdd(Vector4D const& a, Vector4D const& b, float scalar);

	// Dot product.
	float	Dot(Vector4D const& vOther) const;

	// No copy constructors allowed if we're in optimal mode
#ifdef VECTOR_NO_SLOW_OPERATIONS
private:
#else
public:
#endif
	Vector4D(Vector4D const& vOther);

	// No assignment operators either...
	Vector4D& operator=(Vector4D const& src);
};

const Vector4D vec4_origin(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4D vec4_invalid(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);

//-----------------------------------------------------------------------------
// Vector4D related operations
//-----------------------------------------------------------------------------

// Vector4D clear
void Vector4DClear(Vector4D& a);

// Copy
void Vector4DCopy(Vector4D const& src, Vector4D& dst);

// Vector4D arithmetic
void Vector4DAdd(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DSubtract(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DMultiply(Vector4D const& a, float b, Vector4D& result);
void Vector4DMultiply(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DDivide(Vector4D const& a, float b, Vector4D& result);
void Vector4DDivide(Vector4D const& a, Vector4D const& b, Vector4D& result);
void Vector4DMA(Vector4D const& start, float s, Vector4D const& dir, Vector4D& result);

// Vector4DAligned arithmetic


#define Vector4DExpand( v ) (v).x, (v).y, (v).z, (v).w



// Linearly interpolate between two vectors
void Vector4DLerp(Vector4D const& src1, Vector4D const& src2, float t, Vector4D& dest);


//-----------------------------------------------------------------------------
//
// Inlined Vector4D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline Vector4D::Vector4D(void)
{

}

inline Vector4D::Vector4D(float X, float Y, float Z, float W)
{
	x = X; y = Y; z = Z; w = W;
	Assert(IsValid());
}

inline Vector4D::Vector4D(const float *pFloat)
{
	Assert(pFloat);
	x = pFloat[0]; y = pFloat[1]; z = pFloat[2]; w = pFloat[3];
	Assert(IsValid());
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector4D::Vector4D(const Vector4D &vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void Vector4D::Init(float ix, float iy, float iz, float iw)
{
	x = ix; y = iy; z = iz;	w = iw;
	Assert(IsValid());
}

inline void Vector4D::Init(const Vector& src, float iw)
{
	x = src.x; y = src.y; z = src.z; w = iw;
	Assert(IsValid());
}


inline void Vector4D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

inline void Vector4DClear(Vector4D& a)
{
	a.x = a.y = a.z = a.w = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector4D& Vector4D::operator=(const Vector4D &vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline float& Vector4D::operator[](int i)
{
	Assert((i >= 0) && (i < 4));
	return ((float*)this)[i];
}

inline float Vector4D::operator[](int i) const
{
	Assert((i >= 0) && (i < 4));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// Cast to Vector and Vector2D...
//-----------------------------------------------------------------------------

inline Vector& Vector4D::AsVector3D()
{
	return *(Vector*)this;
}

inline Vector const& Vector4D::AsVector3D() const
{
	return *(Vector const*)this;
}

inline Vector2D& Vector4D::AsVector2D()
{
	return *(Vector2D*)this;
}

inline Vector2D const& Vector4D::AsVector2D() const
{
	return *(Vector2D const*)this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* Vector4D::Base()
{
	return (float*)this;
}

inline float const* Vector4D::Base() const
{
	return (float const*)this;
}

//----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector4D::operator==(Vector4D const& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
}

inline bool Vector4D::operator!=(Vector4D const& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void Vector4DCopy(Vector4D const& src, Vector4D& dst)
{
	Assert(src.IsValid());
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
	dst.w = src.w;
}

inline void	Vector4D::CopyToArray(float* rgfl) const
{
	Assert(IsValid());
	Assert(rgfl);
	rgfl[0] = x; rgfl[1] = y; rgfl[2] = z; rgfl[3] = w;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void Vector4D::Negate()
{
	Assert(IsValid());
	x = -x; y = -y; z = -z; w = -w;
}

inline Vector4D& Vector4D::operator+=(const Vector4D& v)
{
	Assert(IsValid() && v.IsValid());
	x += v.x; y += v.y; z += v.z; w += v.w;
	return *this;
}

inline Vector4D& Vector4D::operator-=(const Vector4D& v)
{
	Assert(IsValid() && v.IsValid());
	x -= v.x; y -= v.y; z -= v.z; w -= v.w;
	return *this;
}

inline Vector4D& Vector4D::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	w *= fl;
	Assert(IsValid());
	return *this;
}

inline Vector4D& Vector4D::operator*=(Vector4D const& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	Assert(IsValid());
	return *this;
}

inline Vector4D Vector4D::operator-(void) const
{
	return Vector4D(-x, -y, -z, -w);
}

inline Vector4D Vector4D::operator+(const Vector4D& v) const
{
	Vector4D res;
	Vector4DAdd(*this, v, res);
	return res;
}

inline Vector4D Vector4D::operator-(const Vector4D& v) const
{
	Vector4D res;
	Vector4DSubtract(*this, v, res);
	return res;
}


inline Vector4D Vector4D::operator*(float fl) const
{
	Vector4D res;
	Vector4DMultiply(*this, fl, res);
	return res;
}

inline Vector4D Vector4D::operator*(const Vector4D& v) const
{
	Vector4D res;
	Vector4DMultiply(*this, v, res);
	return res;
}

inline Vector4D Vector4D::operator/(float fl) const
{
	Vector4D res;
	Vector4DDivide(*this, fl, res);
	return res;
}

inline Vector4D operator*(float fl, const Vector4D& v)
{
	return v * fl;
}

inline Vector4D& Vector4D::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	w *= oofl;
	Assert(IsValid());
	return *this;
}

inline Vector4D& Vector4D::operator/=(Vector4D const& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f && v.w != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	Assert(IsValid());
	return *this;
}



