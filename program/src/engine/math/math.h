
#ifndef ENGINE_MATH_MATH_H
#define ENGINE_MATH_MATH_H

#include <Windows.h>
#include <iostream>
#include <math.h>

namespace engine_math {

	class Vector;
	class Matrix;
	class Ray;
	class Plane;
	class Aabb;
	class Obb;
	class Polygon;
	class Quaternion;
	class PolygonList;
	class BspTree;
	class Octree;
}

#define FRONT    0                  // 前面
#define BACK     1                  // 后面
#define PLANAR   2                  // 上面
#define CLIPPED  3                  // 裁剪
#define CULLED   4                  // 剔除
#define VISIBLE  5                  // 可见

namespace engine_math {

HRESULT InitCPU(void);            
float _fabs(float f);              

extern BOOL gIsUseASM;           
const double RTPI = 3.14159265;
const double RTPI2 = 1.5707963;
const double RT2PI = 6.2831853;
const float  RTG = -32.174f; // ft/s^2
const float  RTEPSILON = 0.00001f;
	
/*--------------------------------------------------------------------------------------------------*/
class Vector
{
public:
	Vector(void) { x = 0, y = 0, z = 0, w = 1.0f; }

	Vector(float _x, float _y, float _z)
	{
		x = _x; y = _y; z = _z; w = 1.0f;
	}

	~Vector() {}
public:

	inline void  Set(float _x, float _y, float _z, float _w = 1.0f);
	inline float GetLength(void) const;
	inline float GetSqrLength(void) const;
	inline void  Negate(void);
	// sqrt(x*x + y*y + z*z);
	inline void  Normalize(void);
	inline float AngleWith(const Vector &v) const;
	inline void  RotateWith(const Matrix&);
	inline void  InvRotateWith(const Matrix&);
	// 向量之间的差this = v2 - v1
	inline void  Difference(const Vector &v1, const Vector &v2);

public:
	void operator += (const Vector &v);
	void operator += (float f);
	Vector operator + (const Vector &v)const;
	Vector operator + (float f)const;
	void operator -= (const Vector &v);
	void operator -= (float f);
	Vector operator - (float f)const;
	Vector operator - (const Vector &v)const;
	void operator *= (float f);
	float  operator * (const Vector &v)const;
	Vector operator * (float f)const;
	Quaternion operator * (const Quaternion &q)const;
	Vector operator * (const Matrix &m)const;
	void operator /= (float f);
	Vector operator / (float f)const;
	inline void Cross(const Vector &v1, const Vector &v2);

public:
	float x, y, z, w;
};


/*--------------------------------------------------------------------------------------------------*/
class Matrix
{
public:
	Matrix(void) { ; }
public:
	inline void Identity(void);
	inline void RotaX(float a);
	inline void RotaY(float a);
	inline void RotaZ(float a);
	inline void Rota(const Vector &vc);
	// Rota( Vector( x, y, z ) )
	inline void Rota(float x, float y, float z);
	inline void RotaArbi(const Vector &vcAxis, float a);
	inline void ApplyInverseRota(Vector *pvc);
	inline void Translate(float dx, float dy, float dz);
	inline void SetTranslation(Vector vc, bool EraseContent = false);
	inline Vector GetTranslation(void);
	inline void Scaling(float fX, float fY, float fZ);
	inline void Billboard(Vector vcPos, Vector vcDir, Vector vcWorldUp = Vector(0, 1, 0));
	inline void LookAt(Vector vcPos, Vector vcLookAt, Vector vcWorldUp = Vector(0, 1, 0));
	inline void TransposeOf(const Matrix &m);
	inline void InverseOf(const Matrix &m);

	Matrix operator * (const Matrix &m)const;
	Vector operator * (const Vector &vc)const;

public:
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};




/*--------------------------------------------------------------------------------------------------*/
class Ray
{
public:

	Ray(void) {}
public:
	inline void Set(Vector vcOrig, Vector vcDir);
	inline void DeTransform(const Matrix &_m);
public:
	bool Intersects(const Vector &vc0, const Vector &vc1,const Vector &vc2, bool bCull,float *t);
	bool Intersects(const Vector &vc0, const Vector &vc1,const Vector &vc2, bool bCull,float fL, float *t);
	bool Intersects(const Plane &plane, bool bCull,float *t, Vector *vcHit);
	bool Intersects(const Plane &plane, bool bCull,float fL, float *t, Vector *vcHit);
	bool Intersects(const Aabb &aabb, float *t);
	bool Intersects(const Aabb &aabb, float fL, float *t);
	bool Intersects(const Obb &obb, float *t);
	bool Intersects(const Obb &obb, float fL, float *t);
public:
	Vector m_vcOrig;
	Vector m_vcDir;
};

/*--------------------------------------------------------------------------------------------------*/
class Plane
{
public:
	Plane(void) {}
public:
	inline void  Set(const Vector &vcN, const Vector &vcP);
	inline void  Set(const Vector &vcN, const Vector &vcP, float fD);
	inline void  Set(const Vector &v0, const Vector &v1, const Vector &v2);
	inline float Distance(const Vector &vcPoint);
	inline int Classify(const Vector &vcPoint);

	int Classify(const Polygon &polygon);
	bool Clip(const Ray *_pRay, float fL, Ray *pF, Ray *pB);
public:
	bool Intersects(const Vector &vc0, const Vector &vc1,const Vector &vc2);
	bool Intersects(const Plane &plane, Ray *pIntersection);
	bool Intersects(const Aabb &aabb);
	bool Intersects(const Obb &obb);
public:
	// ax + by +cz + d = 0;  
	// vcN = [ a, b, c]
	// vcPoint = [ x, y, z]
	// fD = d = -vcN * vcPoint;
	Vector m_vcN,       // 法向量
		m_vcPoint;   // 平面上的一点
	float  m_fD;        // 截距
};


/*--------------------------------------------------------------------------------------------------*/
class Aabb
{
public:
	Aabb(void) { ; }
	Aabb(Vector vcMin, Vector vcMax);
public:
	void Construct(const Obb *pObb);
	int  Cull(const Plane *pPlanes, int nNumPlanes);
	void GetPlanes(Plane *pPlanes);
	bool Contains(const Ray &Ray, float fL);
public:
	bool Intersects(const Ray &Ray, float *t);
	bool Intersects(const Ray &Ray, float fL, float *t);
	bool Intersects(const Aabb &aabb);
	bool Intersects(const Vector &vc0);
public:
	Vector m_vcMin, m_vcMax; // 存放x y z的最大和最小值
	Vector m_vcCenter;       // 中心
};

/*--------------------------------------------------------------------------------------------------*/
class Obb
{
public:
	Obb(void) { /* nothing to do */; }
	inline void DeTransform(const Obb &obb, const Matrix &m);
	bool Intersects(const Ray &Ray, float *t);
	bool Intersects(const Ray &Ray, float fL, float *t);
	bool Intersects(const Obb &Obb);
	bool Intersects(const Vector &v0, const Vector &v1, const Vector &v2);
	int  Cull(const Plane *pPlanes, int nNumPlanes);

private:
	void ObbProj(const Obb &Obb, const Vector &vcV, float *pfMin, float *pfMax);
	void TriProj(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &vcV, float *pfMin, float *pfMax);
public:
	float     m_fA0, m_fA1, m_fA2;       // half axis length
	Vector    m_vcA0, m_vcA1, m_vcA2;       // box axis
	Vector    m_vcCenter;                    // 中心点

};

/*--------------------------------------------------------------------------------------------------*/
class Polygon
{
	friend class Plane;
public:
	Polygon(void);
	~Polygon(void);
public:
	void Set(const Vector *pPoints, int nNumP, const unsigned int *pIndis, int nNumI);
	void Clip(const Plane &Plane, Polygon *pFront, Polygon *pBack);
	void Clip(const Aabb &aabb);
	int  Cull(const Aabb &aabb);
	void CopyOf(const Polygon &Poly);
	void SwapFaces(void);
	bool Intersects(const Ray &Ray, bool, float *t);
	bool Intersects(const Ray &Ray, bool, float fL, float *t);
	int GetNumPoints(void) { return m_NumP; }
	int GetNumIndis(void) { return m_NumI; }
	Vector* GetPoints(void) { return m_pPoints; }
	unsigned int* GetIndices(void) { return m_pIndis; }
	Plane  GetPlane(void) { return m_Plane; }
	Aabb   GetAabb(void) { return m_Aabb; }
	unsigned int  GetFlag(void) { return m_Flag; }
	void SetFlag(unsigned int n) { m_Flag = n; }

	// DEBUG ONLY
	void Print(FILE*);
private:
	// 计算外接体
	void CalcBoundingBox(void);
public:
	Vector * m_pPoints;      // 顶点列表
	unsigned int *m_pIndis;       //  定点索引列表
private:
	Plane          m_Plane;    // 多变型所在的面
	int            m_NumP;     // 顶点数
	int            m_NumI;     // 顶点索引数
	Aabb           m_Aabb;     // 外界体
	unsigned int   m_Flag;     // whatever you want it to be
};

/*--------------------------------------------------------------------------------------------------*/
class Quaternion
{
public:
	Quaternion(void) { x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f; }
	Quaternion(float _x, float _y, float _z, float _w)
	{
		x = _x; y = _y; z = _z; w = _w;
	}

	void  MakeFromEuler(float fPitch, float fYaw, float fRoll);
	void  Normalize();
	void  Conjugate(Quaternion q);
	void  GetEulers(float *fPitch, float *fYaw, float *fRoll);
	void  GetMatrix(Matrix *m);
	float GetMagnitude(void);


	void operator /= (float f);
	Quaternion operator /  (float f);

	void operator *= (float f);
	Quaternion operator *  (float f);

	Quaternion operator *  (const Vector &v) const;

	Quaternion operator *  (const Quaternion &q) const;
	void operator *= (const Quaternion &q);

	void operator += (const Quaternion &q);
	Quaternion operator +  (const Quaternion &q) const;

	Quaternion operator~(void) const { return Quaternion(-x, -y, -z, w); }

	void Rotate(const Quaternion &q1, const Quaternion &q2);

	Vector Rotate(const Vector &v);

public:
	float x, y, z, w;
};

/*--------------------------------------------------------------------------------------------------*/
class PolygonList
{
public:
	PolygonList(void);
	~PolygonList(void);

	bool AddPolygon(const Polygon& polygon);
	void Reset(void);

	Polygon* GetPolygon(void) { return m_pPolygon; }
	unsigned int GetNum(void) { return m_uNum; }
private:
	Polygon * m_pPolygon;
	unsigned int m_uNum;
	unsigned int m_uMax;

	bool CheckMem(void);
};

/*--------------------------------------------------------------------------------------------------*/
class BspTree
{
public:
	BspTree(void);
	~BspTree(void);

	void BuildTree(const Polygon* pPolygons, UINT uNum);
	void TraverseBtF(PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum);
	void TraverseFtB(PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum);

	//UINT GetNumPolygon(){ return BspTree::m_sNumPolyOfTree; }
	Aabb GetAabb() { return m_Aabb; }

	bool TestCollision(const Ray* pRay, float fL, float* pfD, Vector* pvcN);
	bool TestCollision(const Aabb* pAabb, const Plane* pFrustum);
	bool LineOfSight(const Vector& vcOrg, const Vector& vcDes);
private:
	Aabb           m_Aabb;
	Plane          m_SplitePlane;        // 分割多边形所在的面
	BspTree*       m_pFrontChild;        // 前面孩子节点
	BspTree*       m_pBackChild;         // 后面孩子节点
	BspTree*       m_pRoot;              // 根节点
	BspTree*       m_pParent;            // 父亲节点
	Polygon*       m_pPolygon;           // 多边形( 叶子节点 )
	UINT           m_nNumPolys;          // 多边形的个数( 叶子节点 )

	//static UINT    m_sNumPolyOfTree;     // 整个树的总多边形数
	void CreateChilds(void);
	bool FindBestSplitter(void);
	void AddPolygon(const Polygon&);
	void SetRelationships(BspTree*, BspTree*);
	void CalcBoundingBox(const Polygon*, unsigned int);
	bool IsLeaf(void) { return (m_pFrontChild == NULL) && (m_pBackChild == NULL); }
};

/*--------------------------------------------------------------------------------------------------*/
class Octree
{
public:
	Octree(void);
	~Octree(void);
	void BuildTree(const Polygon*, UINT);
	void Traverse(PolygonList*, PolygonList*, const Plane*);

	Aabb GetAabb() { return m_Aabb; }
	bool GetFloor(const Vector& vcOrg, float* fD, Plane* pPlane);
	bool TestCollision(const Ray*, float fL, float*);
	bool TestCollision(const Aabb&, Plane*);

private:
	Aabb     m_Aabb;
	Polygon* m_pPolygons;     // 多边形列表（叶子节点）
	UINT     m_nNumPolygons;  // 多边形数量（叶子节点）
	Octree*  m_pChild[8];
	int      m_nPos;          // 在父亲节点中的位置
	Octree*  m_pRoot;
	Octree*  m_pParent;

	void CalcBoundingBox(const Polygon* pPolygon, UINT nInt);
	void InitChildObject(int iChildID, Octree* pParent);
	void ChopListToMe(Polygon* pPolygons, UINT nNum);
	void CreateChilds(Octree *pRoot);
	bool IntersectsDownwardsRay(const Vector&, float fL);
	void GetAabbAsPolygons(PolygonList* pPolygonList);
	bool IsLeaf(void) { return (m_pChild[0] == NULL); }

	void SetBoundingBox(const Aabb& aabb)
	{
		memcpy(&m_Aabb, &aabb, sizeof(Aabb));
	}
};

/*--------------------------------------------------------------------------------------------------*/
class Color
{
public:
	Color()
	{
		r = g = b = 0.0f;
		a = 1.0f;
	}
	Color(float v1, float v2, float v3, float v4 = 1.0f)
	{
		r = v1, g = v2, b = v3, a = v4;
	}
public:
	float r, g, b, a;
};
}


#include "vector.inl"
#include "matrix.inl"
#include "obb.inl"
#include "plane.inl"
#include "ray.inl"

#endif