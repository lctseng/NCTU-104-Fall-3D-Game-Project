#include "vector3.h"

namespace ns_phys {
	vector3 operator + ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
	vector3 operator + ( const vector3& v1, vector3* v2 ) { return vector3( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); }
	vector3 operator - ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
	vector3 operator - ( const vector3& v1, vector3* v2 ) { return vector3( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); }
	vector3 operator - ( const vector3* v1, vector3& v2 ) { return vector3( v1->x - v2.x, v1->y - v2.y, v1->z - v2.z ); }
	// friend vector3 operator - ( const vector3* v1, vector3* v2 ) { return vector3( v1->x - v2->x, v1->y - v2->y, v1->z - v2->z ); }
	vector3 operator ^ ( const vector3& A, const vector3& B ) { return vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x); }
	vector3 operator ^ ( const vector3& A, vector3* B ) { return vector3(A.y*B->z-A.z*B->y,A.z*B->x-A.x*B->z,A.x*B->y-A.y*B->x); }
	vector3 operator * ( const vector3& v, const float f ) { return vector3( v.x * f, v.y * f, v.z * f ); }
	vector3 operator * ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
	vector3 operator * ( const float f, const vector3& v ) { return vector3( v.x * f, v.y * f, v.z * f ); }
	vector3 operator / ( const vector3& v, const float f ) { return vector3( v.x / f, v.y / f, v.z / f ); }
	vector3 operator / ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z ); }
	vector3 operator / ( const float f, const vector3& v ) { return vector3( v.x / f, v.y / f, v.z / f ); }

	
vector3 vector3::Perpendicular() 
{ 
	int ma = MinAxis(); 
	if (ma == 0) return vector3( 0, z, -y ); 
	else if (ma == 1) return vector3( z, 0, -x );
	else return vector3( y, -x, 0 );
}

vector3 vector3::RotateAround( vector3& a_Axis, float a_Angle )
{
	float a = a_Angle * PI / 180;
	if (a < 0) a += 360;
	float cosTheta = cosf( a );
	float sinTheta = sinf( a );
	vector3 current( x, y, z );
	current = Perp( current, a_Axis ) * cosTheta + a_Axis.cross( current ) * sinTheta + Parallel( current, a_Axis ); 
	return current;
}

vector3 vector3::Perp( vector3& a, vector3& axis)
{
	vector3	temp = a - Parallel( a, axis );
	return temp;
}

vector3 vector3::Parallel( vector3& a, vector3& axis )
{
	vector3	temp = axis * a.dot( axis );
	return temp;
}

/*
0 1 2         T    v0x   
3 4 5 = v0 *v1  =  v0y  [ v1x v1y v1z ]
6 7 8              v0z
*/
void accumulateTensor_RowMajor(float *A, const vector3 &v0, const vector3 &v1)
{
	A[0] += v0.x*v1.x;
	A[1] += v0.x*v1.y;
	A[2] += v0.x*v1.z;
	//
	A[3] += v0.y*v1.x;
	A[4] += v0.y*v1.y;
	A[5] += v0.y*v1.z;
	//
	A[6] += v0.z*v1.x;
	A[7] += v0.z*v1.y;
	A[8] += v0.z*v1.z;
}

void matrix::Identity()
{
	cell[1] = cell[2] = cell[TX] = cell[4] = cell[6] = cell[TY] =
	cell[8] = cell[9] = cell[TZ] = cell[12] = cell[13] = cell[14] = 0;
	cell[D0] = cell[D1] = cell[D2] = cell[W] = 1;
}

void matrix::Rotate( vector3 a_Pos, float a_RX, float a_RY, float a_RZ )
{
	matrix t;
	t.RotateX( a_RZ );
	RotateY( a_RY );
	Concatenate( t );
	t.RotateZ( a_RX );
	Concatenate( t );
	Translate( a_Pos );
}

void matrix::RotateX( float a_RX )
{
	float sx = (float)sin( a_RX * PI / 180 );
	float cx = (float)cos( a_RX * PI / 180 );
	Identity();
	cell[5] = cx, cell[6] = sx, cell[9] = -sx, cell[10] = cx;
}

void matrix::RotateY( float a_RY )
{
	float sy = (float)sin( a_RY * PI / 180 );
	float cy = (float)cos( a_RY * PI / 180 );
	Identity ();
	cell[0] = cy, cell[2] = -sy, cell[8] = sy, cell[10] = cy;
}

void matrix::RotateZ( float a_RZ )
{
	float sz = (float)sin( a_RZ * PI / 180 );
	float cz = (float)cos( a_RZ * PI / 180 );
	Identity ();
	cell[0] = cz, cell[1] = sz, cell[4] = -sz, cell[5] = cz;
}

void matrix::Normalize()
{
	float rclx = 1.0f / sqrtf( cell[0] * cell[0] + cell[1] * cell[1] + cell[2] * cell[2] );
	float rcly = 1.0f / sqrtf( cell[4] * cell[4] + cell[5] * cell[5] + cell[6] * cell[6] );
	float rclz = 1.0f / sqrtf( cell[8] * cell[8] + cell[9] * cell[9] + cell[10] * cell[10] );
	cell[0] *= rclx; cell[1] *= rclx; cell[2] *= rclx;
	cell[4] *= rcly; cell[5] *= rcly; cell[10] *= rcly;
	cell[8] *= rclz; cell[9] *= rclz; cell[11] *= rclz;
}

void matrix::Concatenate( matrix& m2 )
{
	matrix res;
	int c;
	for ( c = 0; c < 4; c++ ) for ( int r = 0; r < 4; r++ )
		res.cell[r * 4 + c] = cell[r * 4] * m2.cell[c] +
			  				  cell[r * 4 + 1] * m2.cell[c + 4] +
							  cell[r * 4 + 2] * m2.cell[c + 8] +
							  cell[r * 4 + 3] * m2.cell[c + 12];
	for ( c = 0; c < 16; c++ ) cell[c] = res.cell[c];
}

vector3 matrix::Transform( const vector3& v )
{
	float x  = cell[0] * v.x + cell[1] * v.y + cell[2] * v.z + cell[3];
	float y  = cell[4] * v.x + cell[5] * v.y + cell[6] * v.z + cell[7];
	float z  = cell[8] * v.x + cell[9] * v.y + cell[10] * v.z + cell[11];
	return vector3( x, y, z );
}

void matrix::Invert()
{
	matrix t;
	int h, i;
	float tx = -cell[3], ty = -cell[7], tz = -cell[11];
	for ( h = 0; h < 3; h++ ) for ( int v = 0; v < 3; v++ ) t.cell[h + v * 4] = cell[v + h * 4];
	for ( i = 0; i < 11; i++ ) cell[i] = t.cell[i];
	cell[3] = tx * cell[0] + ty * cell[1] + tz * cell[2];
	cell[7] = tx * cell[4] + ty * cell[5] + tz * cell[6];
	cell[11] = tx * cell[8] + ty * cell[9] + tz * cell[10];
}

quaternion::quaternion() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 1.0f )
{
}

void quaternion::CreateFromAxisAngle( const vector3& a_Axis, const float a_Angle )
{
	float angle = (a_Angle / 180.0f) * PI;
	float result = sinf( angle * 0.5f );
	w = cosf( angle * 0.5f );
	x = a_Axis.x * result;
	y = a_Axis.y * result;
	z = a_Axis.z * result;
}

float quaternion::Length()
{
	return sqrtf( x * x + y * y + z * z + w * w );
}

void quaternion::Normalize()
{
	float rL = 1.0f / Length();
	x *= rL;
	y *= rL;
	z *= rL;
	w *= rL;
}

void quaternion::ConvertToMatrix( matrix& a_Mat )
{
	a_Mat.cell[0] = 1.0f - 2.0f * (y * y + z * z);  
	a_Mat.cell[1] = 2.0f * (x * y - w * z);  
	a_Mat.cell[2] = 2.0f * (x * z + w * y);  
	a_Mat.cell[4] = 2.0f * (x * y + w * z);  
	a_Mat.cell[5] = 1.0f - 2.0f * (x * x + z * z);  
	a_Mat.cell[6] = 2.0f * (y * z - w * x);  
	a_Mat.cell[8] = 2.0f * (x * z - w * y);  
	a_Mat.cell[9] = 2.0f * (y * z + w * x);  
	a_Mat.cell[10] = 1.0f - 2.0f * (x * x + y * y);  
}

quaternion quaternion::operator * ( const quaternion& q )
{
	quaternion r;
	r.w = w*q.w - x*q.x - y*q.y - z*q.z;
	r.x = w*q.x + x*q.w + y*q.z - z*q.y;
	r.y = w*q.y + y*q.w + z*q.x - x*q.z;
	r.z = w*q.z + z*q.w + x*q.y - y*q.x;
	return r;
}

void aabb::BuildFrom( vector3& p1, vector3& p2, vector3& p3 )
{
	float large = 100000;
	vector3 emin( large, large, large );
	vector3 emax( -large, -large, -large );
	for ( int a = 0; a < 3; a++ )
	{
		if (p1.cell[a] < emin.cell[a]) emin.cell[a] = p1.cell[a];
		if (p1.cell[a] > emax.cell[a]) emax.cell[a] = p1.cell[a];
		if (p2.cell[a] < emin.cell[a]) emin.cell[a] = p2.cell[a];
		if (p2.cell[a] > emax.cell[a]) emax.cell[a] = p2.cell[a];
		if (p3.cell[a] < emin.cell[a]) emin.cell[a] = p3.cell[a];
		if (p3.cell[a] > emax.cell[a]) emax.cell[a] = p3.cell[a];
	}
	m_P1 = emin;
	m_P2 = emax;
}

bool aabb::Intersect( aabb& b2 ) const
{
	vector3 v1 = b2.GetPos(), v2 = b2.GetPos() + b2.GetSize();
	vector3 v3 = m_P1, v4 = m_P2;
	return ((v4.x >= v1.x) && (v3.x <= v2.x) && // x-axis overlap
			(v4.y >= v1.y) && (v3.y <= v2.y) && // y-axis overlap
			(v4.z >= v1.z) && (v3.z <= v2.z));   // z-axis overlap
}

bool aabb::Intersect( const vector3& C, const float r )
{
	float s, d = 0; 
	for( unsigned int i = 0; i < 3; i++ ) 
	{ 
		if (C.cell[i] < m_P1.cell[i]) s = C.cell[i] - m_P1.cell[i], d += s * s; 
		else if (C.cell[i] > m_P2.cell[i]) s = C.cell[i] - m_P2.cell[i], d += s * s; 
	}
	return (d <= r * r);
}

bool aabb::Contains( vector3 a_Pos ) const
{
	vector3 v1 = m_P1, v2 = m_P2;
	return ((a_Pos.x >= v1.x) && (a_Pos.x <= v2.x) &&
			(a_Pos.y >= v1.y) && (a_Pos.y <= v2.y) &&
			(a_Pos.z >= v1.z) && (a_Pos.z <= v2.z));
}

const int aabb::LongestSide() const
{ 
	vector3 s = GetSize(); 
	if ((s.x >= s.y) && (s.x >= s.z)) return 0; 
	else if ((s.y >= s.x) && (s.y >= s.z)) return 1;
	else return 2;
}
};