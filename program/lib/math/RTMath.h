/*******************************************************************
* �ļ����ƣ� RTMath.h
* ��    �ܣ� �Զ�����һ����ѧ��
* ��    �ߣ� ���
* �������䣺 arun0515@gmail.com
* �������ڣ� 2009��8��2��
*******************************************************************/
#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
//#include "../RTEngine/RTCommon.h"

namespace RTMath
{
	// ȫ�ֺ���
	HRESULT InitCPU( void );            // ��ʼ��CPU�Ĺ�����Ҫ��ʹ�û��ʱ�õ�
	float _fabs(float f);               // �������ֵ

	//���������ͺ�
	extern BOOL gIsUseASM;             // �Ƿ�ʹ��ASM
	
	#define FRONT    0                  // ǰ��
	#define BACK     1                  // ����
	#define PLANAR   2                  // ����
	#define CLIPPED  3                  // �ü�
	#define CULLED   4                  // �޳�
	#define VISIBLE  5                  // �ɼ�
    
	const double RTPI  =  3.14159265;
	const double RTPI2 =  1.5707963;
	const double RT2PI =  6.2831853;
	const float  RTG   = -32.174f; // ft/s^2
	const float  RTEPSILON = 0.00001f;
	//��ѧ���������б�
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

	//������
	class _declspec(dllexport) Vector
	{
	public:
		Vector(void) { x=0, y=0, z=0, w=1.0f; }

		Vector(float _x, float _y, float _z)
		{ x=_x; y=_y; z =_z; w=1.0f;}

		~Vector(){}
	public:  

		// ��������
		inline void  Set(float _x, float _y, float _z, float _w=1.0f);  
        // ��ȡ����
		inline float GetLength(void) const;                          
		// ���ȵ�ƽ����x*x + y*y + z*z��
		inline float GetSqrLength(void) const;         
		// ��-1�� x= -x, y=-y, z=-z��
		inline void  Negate(void);                    
		// sqrt(x*x + y*y + z*z);
		inline void  Normalize(void);                 
		// ����֮��ļн�
		inline float AngleWith( const Vector &v) const;         
		// ��ת
		inline void  RotateWith( const Matrix& );      
		// ����ת
		inline void  InvRotateWith(const Matrix&);   
		// ����֮��Ĳ�this = v2 - v1
		inline void  Difference( const Vector &v1,    
			                     const Vector &v2 );

	public:
		// ��
		void operator += (const Vector &v); 
		void operator += (float f);  
		Vector operator + (const Vector &v )const; 
		Vector operator + (float f)const;  
        // ��
		void operator -= (const Vector &v);
		void operator -= (float f);
		Vector operator - (float f)const; 
		Vector operator - (const Vector &v )const; 
	    // ��
		void operator *= (float f);  
		float  operator * (const Vector &v)const; 
		Vector operator * (float f)const;    
		Quaternion operator * ( const Quaternion &q)const; 
		Vector operator * (const Matrix &m )const;  
		// ��
		void operator /= (float f);   
		Vector operator / (float f)const;   
        // ���
		inline void Cross(const Vector &v1, const Vector &v2);  

	public:
		// 
		float x, y, z, w;
	};

	// ������
	class _declspec(dllexport) Matrix
	{
	public:
		Matrix(void) { ;}
	public:
		// ��һ��
		inline void Identity(void);                      
        // ����һ����X����ת�ı任����
		inline void RotaX(float a);                       
		// ����һ����Y����ת�ı任����
		inline void RotaY(float a);                       
		// ����һ����X����ת�ı任����
		inline void RotaZ(float a);                       
		// ����һ������������ת�ı任����
		inline void Rota(const Vector &vc);            
		// Rota( Vector( x, y, z ) )
		inline void Rota(float x, float y, float z);      
		// ������ vcAxis ��ת a��
		inline void RotaArbi(const Vector &vcAxis, float a);
		// �Ѹñ任����Ӧ���ڸ�������
		inline void ApplyInverseRota(Vector *pvc);
		// ƽ��
		inline void Translate(float dx, float dy, float dz);
		// ����ƽ��
		inline void SetTranslation(Vector vc, bool EraseContent = false);
		// ���ƽ������
		inline Vector GetTranslation(void);
		// ����
		inline void Scaling( float fX, float fY, float fZ );
        // ��������Ʊ任����
		inline void Billboard( Vector vcPos, 
			                   Vector vcDir,
			                   Vector vcWorldUp = Vector(0,1,0));
		// ������Ӱ����
		inline void LookAt( Vector vcPos,                      // ���λ��
			                Vector vcLookAt,                   // �۲�Ŀ��λ��
			                Vector vcWorldUp = Vector(0,1,0)); // �Ϸ���
        // ת��
		inline void TransposeOf(const Matrix &m);     
		// ����
		inline void InverseOf(const Matrix &m);        
        // �;������
		Matrix operator * (const Matrix &m)const;    
		// ���������
		Vector operator * (const Vector &vc)const;   

	public:
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};


	// ���ߣ�Ray��
	class _declspec(dllexport) Ray
	{
	public:

		Ray(void) {}
	public:
		// ����
		inline void Set(Vector vcOrig, Vector vcDir);
		// �þ���任���ߣ�Ϊ��ʹ���ߺͱ�����������ͬһ����ϵ����������ϵ���У�mΪ����任������ռ�ľ���
		inline void DeTransform(const Matrix &_m); 
	public:
		// ���ߺ������ε���ײ,bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ���ȣ�������ԭ�㵽�ཻ�㣩
		bool Intersects( const Vector &vc0, const Vector &vc1,
			             const Vector &vc2, bool bCull,
			             float *t);
		// ���߶κ������µ���ײ fLΪ�߶εĳ���
		bool Intersects( const Vector &vc0, const Vector &vc1,
			             const Vector &vc2, bool bCull,
			             float fL, float *t);
		// ���ߺ������ײ��t �����ཻ���ȣ�vcHit �����ཻ�㣩
		bool Intersects( const Plane &plane, bool bCull,
			             float *t, Vector *vcHit);
		// ���߶κ������ײ
		bool Intersects( const Plane &plane, bool bCull,
			             float fL, float *t, Vector *vcHit);
		// ���ߺͰ�����aabb��ײ
		bool Intersects(const Aabb &aabb, float *t);
		// ���߶κͰ�����aabb��ײ
		bool Intersects(const Aabb &aabb, float fL, float *t);
		// ���ߺͰ�����abb����ײ
		bool Intersects(const Obb &obb, float *t);
		// ���߶κͰ�����abb����ײ
		bool Intersects(const Obb &obb, float fL, float *t);
	public:
		Vector m_vcOrig,  // ԭ��λ��
			   m_vcDir;   // ����
	};
	

	// Plane��
	class _declspec(dllexport) Plane
	{
	public:
		Plane(void) {}
	public:
		// ��������
		inline void  Set(const Vector &vcN, const Vector &vcP);
		inline void  Set(const Vector &vcN, const Vector &vcP, float fD);
		inline void  Set(const Vector &v0,  const Vector &v1, const Vector &v2);
		// �㵽��þ���
		inline float Distance(const Vector &vcPoint);
		// �жϵ����Ĺ�ϵ
		inline int Classify(const Vector &vcPoint);
		// �ж϶���κ���Ĺ�ϵ
		int Classify(const RTMath::Polygon &polygon);
        // һ���߶α���ӳ������߶Σ� fF ������ǰ����߶Σ� pB�����������߶� ��
		bool Clip(const Ray *_pRay, float fL, Ray *pF, Ray *pB);
	public:

		// �������ε���ײ���
		bool Intersects(const Vector &vc0, const Vector &vc1, 
			            const Vector &vc2);
		// �������ߵ���ײ���
		bool Intersects(const Plane &plane, Ray *pIntersection);
		// ��AABB����ײ
		bool Intersects(const Aabb &aabb);
		// ��Obb����ײ
		bool Intersects(const Obb &obb);
	public:
		// ax + by +cz + d = 0;  
		// vcN = [ a, b, c]
		// vcPoint = [ x, y, z]
		// fD = d = -vcN * vcPoint;
		Vector m_vcN,       // ������
			   m_vcPoint;   // ƽ���ϵ�һ��
		float  m_fD;        // �ؾ�
	};

	// Aabb ������
	class _declspec(dllexport) Aabb
	{
	public:
		Aabb(void) { ; }
		Aabb( Vector vcMin, Vector vcMax);
	public:
		// ͨ��Obb����
		void Construct(const Obb *pObb);     
		// �޳���⣨ һ���棬�� �Ӿ���6���� ��,��ķ����������
		int  Cull(const Plane *pPlanes, int nNumPlanes);  
		// ��ȡAABB��������
		void GetPlanes( Plane *pPlanes);
		// �߶��Ƿ���Aabb��
		bool Contains(const Ray &Ray, float fL);
	public:
		// ��ײ��⣬f��������ԭ�㵽����ľ���
		bool Intersects(const Ray &Ray, float *t);
		// ��ײ��⣬f�����߶�ԭ�㵽����ľ���
		bool Intersects(const Ray &Ray, float fL, float *t);
		// ��ײ��������aabb
		bool Intersects(const Aabb &aabb);
		// ���Ƿ���AABB��
		bool Intersects(const Vector &vc0);
	public:
		Vector m_vcMin, m_vcMax; // ���x y z��������Сֵ
		Vector m_vcCenter;       // ����
	};

	//Obb
	class _declspec(dllexport) Obb
	{
	public:
		Obb(void) { /* nothing to do */ ; }
		// �ı�Obb������ϵ
		inline void DeTransform( const Obb &obb, const Matrix &m);
        // ��ײ���---���ߣ� t ��������ԭ�㵽����ľ���
		bool Intersects(const Ray &Ray, float *t);
		// ��ײ���---�߶� 
		bool Intersects(const Ray &Ray, float fL, float *t);
		// ��ײ���---Obb
		bool Intersects(const Obb &Obb);
		// ��ײ���---������
		bool Intersects(const Vector &v0, 
			            const Vector &v1,
			            const Vector &v2);
		// �޳��Ͳü�
		int  Cull(const Plane *pPlanes, int nNumPlanes);      

	private:
		void ObbProj( const Obb &Obb, const Vector &vcV, 
			          float *pfMin, float *pfMax );
		void TriProj(const Vector &v0, const Vector &v1, 
			         const Vector &v2, const Vector &vcV, 
			         float *pfMin, float *pfMax);
	public:
		float     m_fA0,   m_fA1,  m_fA2;       // half axis length
		Vector    m_vcA0, m_vcA1, m_vcA2;       // box axis
		Vector    m_vcCenter;                    // ���ĵ�

	};

	// �����
	class _declspec( dllexport )Polygon
	{
		friend class Plane;      
	public:
		Polygon(void);
		~Polygon(void);
	public:
		// ��������
		void Set(const Vector *pPoints, int nNumP,
			const unsigned int *pIndis, int nNumI);
		// ��ƽ���и��ǰ���������
		void Clip(const Plane &Plane, 
			Polygon *pFront,
			Polygon *pBack);
		void Clip(const Aabb &aabb);
		int  Cull(const Aabb &aabb);

		void CopyOf( const Polygon &Poly );

		void SwapFaces(void);

		// �������ཻ
		bool Intersects(const Ray &Ray, bool, float *t);

		// �����߶��ཻ
		bool Intersects(const Ray &Ray, bool, float fL, float *t);

		int GetNumPoints(void){ return m_NumP;}
		int GetNumIndis(void) { return m_NumI;}
		Vector* GetPoints(void){ return m_pPoints;}
		unsigned int* GetIndices(void){ return m_pIndis;}
		Plane  GetPlane(void){ return m_Plane;}
		Aabb   GetAabb(void){ return m_Aabb; }
		unsigned int  GetFlag(void){ return m_Flag;}
		void SetFlag(unsigned int n){ m_Flag = n;}

		// DEBUG ONLY
		void Print(FILE*);
	private:
		// ���������
		void CalcBoundingBox(void);
	public:
		Vector       *m_pPoints;      // �����б�
		unsigned int *m_pIndis;       //  ���������б�
	private:
		Plane          m_Plane;    // ��������ڵ���
		int            m_NumP;     // ������
		int            m_NumI;     // ����������
		Aabb           m_Aabb;     // �����
		unsigned int   m_Flag;     // whatever you want it to be
	};

	// ��Ԫ��
	class _declspec( dllexport )Quaternion
	{
	public:
		Quaternion(void) { x=0.0f, y=0.0f, z=0.0f, w=1.0f; }
		Quaternion(float _x, float _y, float _z, float _w)
		{ x=_x; y=_y; z=_z; w=_w; }

		void  MakeFromEuler(float fPitch, float fYaw, float fRoll);
		void  Normalize();
		void  Conjugate(Quaternion q);
		void  GetEulers( float *fPitch, float *fYaw, float *fRoll);
		void  GetMatrix( Matrix *m);
		float GetMagnitude(void);


		void    operator /= (float f);
		Quaternion operator /  (float f);

		void    operator *= (float f);
		Quaternion operator *  (float f);

		Quaternion operator *  (const Vector &v) const;

		Quaternion operator *  (const Quaternion &q) const;
		void    operator *= (const Quaternion &q);

		void    operator += (const Quaternion &q);
		Quaternion operator +  (const Quaternion &q) const;

		Quaternion operator~(void) const { return Quaternion(-x, -y, -z, w); }

		void Rotate(const Quaternion &q1, const Quaternion &q2);

		Vector Rotate(const Vector &v);

	public:
		float x, y, z, w;
	};

	// һ��������б�Ĺ�����
	class _declspec( dllexport )PolygonList
	{
	public:
		PolygonList( void );
		~PolygonList( void );

		// ��������
		bool AddPolygon( const Polygon& polygon );

		// ���ö�����б�
		void Reset( void );

		Polygon* GetPolygon( void ){ return m_pPolygon; }
		unsigned int GetNum( void ){ return m_uNum; }
	private:
		Polygon*     m_pPolygon;
		unsigned int m_uNum;
		unsigned int m_uMax;

		// ���洢�ռ�
		bool CheckMem( void );
	};

	// BSP���ṹ
	class _declspec( dllexport )BspTree
	{
	public:
		BspTree( void );
		~BspTree( void );

		// ����bsp��
		void BuildTree( const Polygon* pPolygons, UINT uNum );

		// ����( ����һ���Ӻ�ǰ˳��Ķ�����б�)
		void TraverseBtF( PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum );
		// ����( ����һ����ǰ����˳��Ķ�����б�)
		void TraverseFtB( PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum );

		//UINT GetNumPolygon(){ return BspTree::m_sNumPolyOfTree; }
		Aabb GetAabb(){ return m_Aabb;}

		// ��ײ���
		bool TestCollision( const Ray* pRay, float fL, float* pfD, Vector* pvcN );
        bool TestCollision( const Aabb* pAabb, const Plane* pFrustum );
		// ����߶μ�Ŀռ��Ƿ�Ϊ��
        bool LineOfSight(const Vector& vcOrg, const Vector& vcDes );
	private:
		Aabb           m_Aabb;
		Plane          m_SplitePlane;        // �ָ��������ڵ���
		BspTree*       m_pFrontChild;        // ǰ�溢�ӽڵ�
		BspTree*       m_pBackChild;         // ���溢�ӽڵ�
		BspTree*       m_pRoot;              // ���ڵ�
		BspTree*       m_pParent;            // ���׽ڵ�
		Polygon*       m_pPolygon;           // �����( Ҷ�ӽڵ� )
		UINT           m_nNumPolys;          // ����εĸ���( Ҷ�ӽڵ� )

		//static UINT    m_sNumPolyOfTree;     // ���������ܶ������

		// �����ӽڵ�
		void CreateChilds(void);
		// Ѱ����ѷָ�����
		bool FindBestSplitter(void);
		// ��Ӷ����
		void AddPolygon(const Polygon&);
		// ��������
		void SetRelationships( BspTree*, BspTree*);
		// ���������
		void CalcBoundingBox(const Polygon*, unsigned int);
		// �ж��Ƿ���Ҷ�ӽڵ�
		bool IsLeaf(void) { return (m_pFrontChild==NULL)&&(m_pBackChild==NULL); }
	};

	// �˲����ṹ
	class _declspec( dllexport )Octree
	{
	public:
		Octree(void);
		~Octree(void);
        // �����˲���
		void BuildTree( const Polygon*, UINT );
		// �����˲���,���ؿɼ��Ķ���μ���
		void Traverse( PolygonList*, PolygonList*, const Plane* ) ;

		Aabb GetAabb(){ return m_Aabb; }
		// ��ȡ�ڸ������·��Ҿ���õ��������
		bool GetFloor( const Vector& vcOrg, float* fD, Plane* pPlane );
		// ��ײ���
		bool TestCollision( const Ray*, float fL, float* );
		bool TestCollision( const Aabb&, Plane* );

	private:
		Aabb     m_Aabb;
		Polygon* m_pPolygons;     // ������б�Ҷ�ӽڵ㣩
		UINT     m_nNumPolygons;  // �����������Ҷ�ӽڵ㣩
		Octree*  m_pChild[8];
		int      m_nPos;          // �ڸ��׽ڵ��е�λ��
		Octree*  m_pRoot;
		Octree*  m_pParent;

		// ����Aabb
		void CalcBoundingBox( const Polygon* pPolygon, UINT nInt );
        // ��ʼ���ӽڵ������
		void InitChildObject( int iChildID, Octree* pParent );
		// �ı������б�
		void ChopListToMe( Polygon* pPolygons, UINT nNum );
		// �������ӽڵ�
		void CreateChilds( Octree *pRoot);
		// ��ⷽ��Ϊ-y�����ߵ���ײ���
		bool IntersectsDownwardsRay(const Vector&, float fL );
		// �����Զ���ε���ʽ��ɵ�AABB---������
		void GetAabbAsPolygons( PolygonList* pPolygonList );

		bool IsLeaf(void) { return (m_pChild[0]==NULL); }

		void SetBoundingBox(const Aabb& aabb) 
		{ memcpy(&m_Aabb, &aabb, sizeof(Aabb)); }
	};

	class _declspec(dllexport) Color
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
