#ifndef _WAGO_VECTOR_H_
#define _WAGO_VECTOR_H_
//source: from others
#include <math.h>
//#include "../basic/basic.h"
#ifndef PI
#define PI	3.141592654
#endif


namespace ns_phys {

#define v3_float float

class vector3
{
public:
	vector3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {};
	vector3( v3_float a_X, v3_float a_Y, v3_float a_Z ) : x( a_X ), y( a_Y ), z( a_Z ) {};
	void Set( v3_float a_X, v3_float a_Y, v3_float a_Z ) { x = a_X; y = a_Y; z = a_Z; }
	void zero() { x = y = z = 0.0; }
	void Normalize() { v3_float l = 1.0f / Length(); x *= l; y *= l; z *= l; }
	const vector3 Normalized() { v3_float l = 1.0f / Length(); return vector3( x * l, y * l, z * l ); }
	v3_float Length() const { return (v3_float)sqrt( x * x + y * y + z * z ); }
	v3_float SqrLength() const { return x * x + y * y + z * z; }
	vector3 Perp( vector3& a, vector3& axis);
	vector3 Parallel( vector3& a, vector3& axis );
	v3_float dot( const vector3 &a_V ) const { return x * a_V.x + y * a_V.y + z * a_V.z; }
	v3_float distance( const vector3 &a_V ) const { return sqrt((x - a_V.x)*(x - a_V.x) + (y - a_V.y)*(y - a_V.y) + (z - a_V.z)*(z - a_V.z)); }
	const vector3 cross( const vector3 &v ) const { return vector3( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x ); }
	vector3 RotateAround( vector3& a_Axis, v3_float a_Angle );
	vector3 Perpendicular();
	void operator += ( const vector3& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }
	void operator += ( vector3* a_V ) { x += a_V->x; y += a_V->y; z += a_V->z; }
	void operator -= ( const vector3& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }
	void operator -= ( vector3* a_V ) { x -= a_V->x; y -= a_V->y; z -= a_V->z; }
	void operator *= ( const v3_float f ) { x *= f; y *= f; z *= f; }
	void operator *= ( const vector3& a_V ) { x *= a_V.x; y *= a_V.y; z *= a_V.z; }
	void operator *= ( vector3* a_V ) { x *= a_V->x; y *= a_V->y; z *= a_V->z; }
	v3_float& operator [] ( int a_N ) { return cell[a_N]; }
	vector3 operator- () const { return vector3( -x, -y, -z ); }
	/*
	friend vector3 operator + ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
	friend vector3 operator + ( const vector3& v1, vector3* v2 ) { return vector3( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); }
	friend vector3 operator - ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
	friend vector3 operator - ( const vector3& v1, vector3* v2 ) { return vector3( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); }
	friend vector3 operator - ( const vector3* v1, vector3& v2 ) { return vector3( v1->x - v2.x, v1->y - v2.y, v1->z - v2.z ); }
	// friend vector3 operator - ( const vector3* v1, vector3* v2 ) { return vector3( v1->x - v2->x, v1->y - v2->y, v1->z - v2->z ); }
	friend vector3 operator ^ ( const vector3& A, const vector3& B ) { return vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x); }
	friend vector3 operator ^ ( const vector3& A, vector3* B ) { return vector3(A.y*B->z-A.z*B->y,A.z*B->x-A.x*B->z,A.x*B->y-A.y*B->x); }
	friend vector3 operator * ( const vector3& v, const float f ) { return vector3( v.x * f, v.y * f, v.z * f ); }
	friend vector3 operator * ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
	friend vector3 operator * ( const float f, const vector3& v ) { return vector3( v.x * f, v.y * f, v.z * f ); }
	friend vector3 operator / ( const vector3& v, const float f ) { return vector3( v.x / f, v.y / f, v.z / f ); }
	friend vector3 operator / ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z ); }
	friend vector3 operator / ( const float f, const vector3& v ) { return vector3( v.x / f, v.y / f, v.z / f ); }
	*/
	friend vector3 operator + ( const vector3& v1, const vector3& v2 );
	friend vector3 operator + ( const vector3& v1, vector3* v2 );
	friend vector3 operator - ( const vector3& v1, const vector3& v2 );
	friend vector3 operator - ( const vector3& v1, vector3* v2 );
	friend vector3 operator - ( const vector3* v1, vector3& v2 );
	// extern vector3 operator - ( const vector3* v1, vector3* v2 ) { return vector3( v1->x - v2->x, v1->y - v2->y, v1->z - v2->z ); }
	friend vector3 operator ^ ( const vector3& A, const vector3& B );
	friend vector3 operator ^ ( const vector3& A, vector3* B );
	friend vector3 operator * ( const vector3& v, const v3_float f );
	friend vector3 operator * ( const vector3& v1, const vector3& v2 );
	friend vector3 operator * ( const v3_float f, const vector3& v );
	friend vector3 operator / ( const vector3& v, const v3_float f );
	friend vector3 operator / ( const vector3& v1, const vector3& v2 );
	friend vector3 operator / ( const v3_float f, const vector3& v );

	bool operator == ( const vector3& a_V ) { if((x==a_V.x)&&(y==a_V.y)&&(z==a_V.z)) return true; return false; }
	bool operator == ( const vector3* a_V ) { if((x==a_V->x)&&(y==a_V->y)&&(z==a_V->z)) return true; return false; }
	bool operator != ( const vector3& a_V ) { if((x==a_V.x)&&(y==a_V.y)&&(z==a_V.z)) return false; return true; }
	bool operator != ( const vector3* a_V ) { if((x==a_V->x)&&(y==a_V->y)&&(z==a_V->z)) return false; return true; }
private:
	int MinAxis() { return (fabs(x)<=fabs(y)?((fabs(x)<=fabs(z))?0:2):((fabs(y)<=fabs(z))?1:2)); }
public:
	union
	{
		struct { v3_float x, y, z; };
		struct { v3_float nx, ny, nz; };
		struct { v3_float cell[3]; };
		struct { v3_float e[3];};
		struct {  v3_float r, g, b; };
		v3_float xyz[3];
		v3_float ptr[3];
		v3_float p[3];
	};
};

class aabb
{
public:
	aabb() : m_P1( vector3( 0, 0, 0 ) ), m_P2( vector3( 0, 0, 0 ) ) {};
	aabb( vector3& a_Pos, vector3& a_Size ) : m_P1( a_Pos ), m_P2( a_Pos + a_Size ) {};
	vector3& GetPos() { return m_P1; }
	vector3& GetP1() { return m_P1; }
	vector3& GetP2() { return m_P2; }
	void SetP1( vector3& a_P1 ) { m_P1 = a_P1; }
	void SetP2( vector3& a_P2 ) { m_P2 = a_P2; }
	const vector3 GetSize() const { return vector3( w(), h(), d() ); }
	bool Intersect( aabb& b2 ) const;
	bool Intersect( const vector3& C, const v3_float r );
	
	bool Contains( vector3 a_Pos ) const;
	void BuildFrom( vector3& p1, vector3& p2, vector3& p3 );
	const v3_float area() const { return 2.0f * (w() * h() + w() * d() + d() * h()); }
	const v3_float w() const { return m_P2.x - m_P1.x; }
	const v3_float h() const { return m_P2.y - m_P1.y; }
	const v3_float d() const { return m_P2.z - m_P1.z; }
	const v3_float x() const { return m_P1.x; }
	const v3_float y() const { return m_P1.y; }
	const v3_float z() const { return m_P1.z; }
	const v3_float Centre( int a_Axis ) const { return (m_P1.cell[a_Axis] + m_P2.cell[a_Axis]) * 0.5f; }
	v3_float& Min( int a_Axis ) { return m_P1.cell[a_Axis]; }
	v3_float& Max( int a_Axis ) { return m_P2.cell[a_Axis]; }
	const int LongestSide() const;
	vector3 m_P1, m_P2;
};

class plane
{
public:
	plane() : N( 0, 0, 0 ), D( 0 ) {};
	plane( vector3 a_Normal, v3_float a_D ) : N( a_Normal ), D( a_D ) {};
	vector3 N;
	v3_float D;
};

class matrix
{
public:
	enum 
	{ 
		TX=3, 
		TY=7, 
		TZ=11, 
		D0=0, D1=5, D2=10, D3=15, 
		SX=D0, SY=D1, SZ=D2, 
		W=D3 
	};
	matrix() { Identity(); }
	v3_float& operator [] ( int a_N ) { return cell[a_N]; }
	void Identity();
	void Rotate( vector3 a_Pos, v3_float a_RX, v3_float a_RY, v3_float a_RZ );
	void RotateX( v3_float a_RX );
	void RotateY( v3_float a_RY );
	void RotateZ( v3_float a_RZ );
	void Translate( vector3 a_Pos ) { cell[TX] += a_Pos.x; cell[TY] += a_Pos.y; cell[TZ] += a_Pos.z; }
	void SetTranslation( vector3 a_Pos ) { cell[TX] = a_Pos.x; cell[TY] = a_Pos.y; cell[TZ] = a_Pos.z; }
	void Normalize();
	void Concatenate( matrix& m2 );
	vector3 Transform( const vector3& v );
	vector3 GetTranslation() { return vector3(cell[TX], cell[TY], cell[TZ]); }
	void Invert();
	v3_float cell[16];
};

class quaternion
{
public:
	quaternion();
	void ConvertToMatrix( matrix& a_Mat );
	v3_float Length();
	void Normalize();
	void CreateFromAxisAngle( const vector3& a_Axis, const v3_float a_Angle );
	quaternion operator * ( const quaternion &q );
private:
	v3_float x, y, z, w;
};

extern vector3 operator + ( const vector3& v1, const vector3& v2 );
	extern vector3 operator + ( const vector3& v1, vector3* v2 );
	extern vector3 operator - ( const vector3& v1, const vector3& v2 );
	extern vector3 operator - ( const vector3& v1, vector3* v2 );
	extern vector3 operator - ( const vector3* v1, vector3& v2 );
	// extern vector3 operator - ( const vector3* v1, vector3* v2 ) { return vector3( v1->x - v2->x, v1->y - v2->y, v1->z - v2->z ); }
	extern vector3 operator ^ ( const vector3& A, const vector3& B );
	extern vector3 operator ^ ( const vector3& A, vector3* B );
	extern vector3 operator * ( const vector3& v, const v3_float f );
	extern vector3 operator * ( const vector3& v1, const vector3& v2 );
	extern vector3 operator * ( const v3_float f, const vector3& v );
	extern vector3 operator / ( const vector3& v, const v3_float f );
	extern vector3 operator / ( const vector3& v1, const vector3& v2 );
	extern vector3 operator / ( const v3_float f, const vector3& v );

	inline v3_float VecDot(const vector3 &a, const vector3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z;}
	void accumulateTensor_RowMajor(float *A, const vector3 &v0, const vector3 &v1);
};
#endif