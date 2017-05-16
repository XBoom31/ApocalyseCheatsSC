#pragma once
#include "stdafx.h"

#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )
#define  FORCEINLINE			__forceinline

inline float isqrt(float _Xx)
{
	return (sqrtf(_Xx));
}

void CalcAngle(Vector src, Vector dst, Vector &angles);

typedef float vec_t;
struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}
	float *operator[](int i)
	{
		return m_flMatVal[i];
	}
	const float *operator[](int i) const
	{
		return m_flMatVal[i];
	}
	float *Base()
	{
		return &m_flMatVal[0][0];
	}
	const float *Base() const
	{
		return &m_flMatVal[0][0];
	}

	float m_flMatVal[3][4];
};

class CMath
{
public:
	static CMath* Singleton(void);
	bool WorldToScreen(Vector& vecOrigin, Vector& vecScreen);
	VOID sinCos(float radians, PFLOAT sine, PFLOAT cosine);
	void angleVectors(const Vector &angles, Vector &forward);
	float sseSqrt(float x);
	VOID vectorAngles(float* forward, float* angles);
	void vectorAnglesVec(Vector forward, Vector &angles);
	void VectorAngles3D(Vector&vecForward, Vector&vecAngles);
	float deg2rad(float deg);
	float DotProduct(const Vector& a, const Vector& b);
	void VectorTransform(const Vector in1, matrix3x4_t in2, Vector &out);
	void AngleMatrix(Vector &angles, matrix3x4_t &matrix);
	void VectorRotate(Vector &in1, Vector &in2, Vector &out);
	void Normalize(Vector &vIn, Vector &vOut);
	void VectorTransform2(const Vector in1, float in2[3][4], Vector &out);
	void VectorITransform(const float *in1, const matrix3x4_t& in2, float *out)
	{
		Assert(s_bMathlibInitialized);
		float in1t[3];

		in1t[0] = in1[0] - in2[0][3];
		in1t[1] = in1[1] - in2[1][3];
		in1t[2] = in1[2] - in2[2][3];

		out[0] = in1t[0] * in2[0][0] + in1t[1] * in2[1][0] + in1t[2] * in2[2][0];
		out[1] = in1t[0] * in2[0][1] + in1t[1] * in2[1][1] + in1t[2] * in2[2][1];
		out[2] = in1t[0] * in2[0][2] + in1t[1] * in2[1][2] + in1t[2] * in2[2][2];
	}
	void AngleNormalise(Vector& angle)
	{
		while (angle.y <= -180) angle.y += 360;
		while (angle.y > 180) angle.y -= 360;
		while (angle.x <= -180) angle.x += 360;
		while (angle.x > 180) angle.x -= 360;

		if (angle.x > 89.0) angle.x = 89;
		if (angle.x < -89.0) angle.x = -89;
		if (angle.y < -180) angle.y = -179.999;
		if (angle.y > 180) angle.y = 179.999;

		angle.z = 0;
	}
};



extern CMath g_Math;