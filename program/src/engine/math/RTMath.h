/*******************************************************************
* 文件名称： RTMath.h
* 功    能： 自定义了一个数学库
* 作    者： 阮复初
* 电子邮箱： arun0515@gmail.com
* 创建日期： 2009年8月2日
*******************************************************************/
#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
//#include "../RTEngine/RTCommon.h"

namespace RTMath
{
	// 全局函数
	HRESULT InitCPU( void );            // 初始化CPU的工作主要是使用汇编时用的
	float _fabs(float f);               // 计算绝对值

	//公共常量和宏
	extern BOOL gIsUseASM;             // 是否使用ASM
	
	#define FRONT    0                  // 前面
	#define BACK     1                  // 后面
	#define PLANAR   2                  // 上面
	#define CLIPPED  3                  // 裁剪
	#define CULLED   4                  // 剔除
	#define VISIBLE  5                  // 可见
    
	const double RTPI  =  3.14159265;
	const double RTPI2 =  1.5707963;
	const double RT2PI =  6.2831853;
	const float  RTG   = -32.174f; // ft/s^2
	const float  RTEPSILON = 0.00001f;
	//数学库类声明列表
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

	//向量类
	class _declspec(dllexport) Vector
	{
	public:
		Vector(void) { x=0, y=0, z=0, w=1.0f; }

		Vector(float _x, float _y, float _z)
		{ x=_x; y=_y; z =_z; w=1.0f;}

		~Vector(){}
	public:  

		// 设置属性
		inline void  Set(float _x, float _y, float _z, float _w=1.0f);  
        // 获取长度
		inline float GetLength(void) const;                          
		// 长度的平方（x*x + y*y + z*z）
		inline float GetSqrLength(void) const;         
		// 乘-1（ x= -x, y=-y, z=-z）
		inline void  Negate(void);                    
		// sqrt(x*x + y*y + z*z);
		inline void  Normalize(void);                 
		// 向量之间的夹角
		inline float AngleWith( const Vector &v) const;         
		// 旋转
		inline void  RotateWith( const Matrix& );      
		// 逆旋转
		inline void  InvRotateWith(const Matrix&);   
		// 向量之间的差this = v2 - v1
		inline void  Difference( const Vector &v1,    
			                     const Vector &v2 );

	public:
		// 加
		void operator += (const Vector &v); 
		void operator += (float f);  
		Vector operator + (const Vector &v )const; 
		Vector operator + (float f)const;  
        // 减
		void operator -= (const Vector &v);
		void operator -= (float f);
		Vector operator - (float f)const; 
		Vector operator - (const Vector &v )const; 
	    // 乘
		void operator *= (float f);  
		float  operator * (const Vector &v)const; 
		Vector operator * (float f)const;    
		Quaternion operator * ( const Quaternion &q)const; 
		Vector operator * (const Matrix &m )const;  
		// 除
		void operator /= (float f);   
		Vector operator / (float f)const;   
        // 叉乘
		inline void Cross(const Vector &v1, const Vector &v2);  

	public:
		// 
		float x, y, z, w;
	};

	// 矩阵类
	class _declspec(dllexport) Matrix
	{
	public:
		Matrix(void) { ;}
	public:
		// 归一化
		inline void Identity(void);                      
        // 建立一个绕X轴旋转的变换矩阵
		inline void RotaX(float a);                       
		// 建立一个绕Y轴旋转的变换矩阵
		inline void RotaY(float a);                       
		// 建立一个绕X轴旋转的变换矩阵
		inline void RotaZ(float a);                       
		// 建立一个绕任意轴旋转的变换矩阵
		inline void Rota(const Vector &vc);            
		// Rota( Vector( x, y, z ) )
		inline void Rota(float x, float y, float z);      
		// 绕向量 vcAxis 旋转 a度
		inline void RotaArbi(const Vector &vcAxis, float a);
		// 把该变换矩阵应用于给定向量
		inline void ApplyInverseRota(Vector *pvc);
		// 平移
		inline void Translate(float dx, float dy, float dz);
		// 设置平移
		inline void SetTranslation(Vector vc, bool EraseContent = false);
		// 获得平移向量
		inline Vector GetTranslation(void);
		// 缩放
		inline void Scaling( float fX, float fY, float fZ );
        // 建立广告牌变换矩阵
		inline void Billboard( Vector vcPos, 
			                   Vector vcDir,
			                   Vector vcWorldUp = Vector(0,1,0));
		// 建立摄影矩阵
		inline void LookAt( Vector vcPos,                      // 相机位置
			                Vector vcLookAt,                   // 观察目标位置
			                Vector vcWorldUp = Vector(0,1,0)); // 上方向
        // 转置
		inline void TransposeOf(const Matrix &m);     
		// 求逆
		inline void InverseOf(const Matrix &m);        
        // 和矩阵相乘
		Matrix operator * (const Matrix &m)const;    
		// 和向量相乘
		Vector operator * (const Vector &vc)const;   

	public:
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};


	// 射线（Ray）
	class _declspec(dllexport) Ray
	{
	public:

		Ray(void) {}
	public:
		// 设置
		inline void Set(Vector vcOrig, Vector vcDir);
		// 用矩阵变换射线，为了使射线和被检测的物体在同一坐标系（物体坐标系）中，m为物体变换到世界空间的矩阵
		inline void DeTransform(const Matrix &_m); 
	public:
		// 射线和三角形的碰撞,bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度（从射线原点到相交点）
		bool Intersects( const Vector &vc0, const Vector &vc1,
			             const Vector &vc2, bool bCull,
			             float *t);
		// 射线段和三角新的碰撞 fL为线段的长度
		bool Intersects( const Vector &vc0, const Vector &vc1,
			             const Vector &vc2, bool bCull,
			             float fL, float *t);
		// 射线和面得碰撞（t 返回相交长度，vcHit 返回相交点）
		bool Intersects( const Plane &plane, bool bCull,
			             float *t, Vector *vcHit);
		// 射线段和面得碰撞
		bool Intersects( const Plane &plane, bool bCull,
			             float fL, float *t, Vector *vcHit);
		// 射线和包裹体aabb碰撞
		bool Intersects(const Aabb &aabb, float *t);
		// 射线段和包裹体aabb碰撞
		bool Intersects(const Aabb &aabb, float fL, float *t);
		// 射线和包裹体abb的碰撞
		bool Intersects(const Obb &obb, float *t);
		// 射线段和包裹体abb的碰撞
		bool Intersects(const Obb &obb, float fL, float *t);
	public:
		Vector m_vcOrig,  // 原点位置
			   m_vcDir;   // 方向
	};
	

	// Plane类
	class _declspec(dllexport) Plane
	{
	public:
		Plane(void) {}
	public:
		// 基本操作
		inline void  Set(const Vector &vcN, const Vector &vcP);
		inline void  Set(const Vector &vcN, const Vector &vcP, float fD);
		inline void  Set(const Vector &v0,  const Vector &v1, const Vector &v2);
		// 点到面得距离
		inline float Distance(const Vector &vcPoint);
		// 判断点和面的关系
		inline int Classify(const Vector &vcPoint);
		// 判断多边形和面的关系
		int Classify(const RTMath::Polygon &polygon);
        // 一个线段被面接成两个线段（ fF 返回面前面的线段， pB返回面后面的线段 ）
		bool Clip(const Ray *_pRay, float fL, Ray *pF, Ray *pB);
	public:

		// 和三角形的碰撞检测
		bool Intersects(const Vector &vc0, const Vector &vc1, 
			            const Vector &vc2);
		// 面与射线的碰撞检测
		bool Intersects(const Plane &plane, Ray *pIntersection);
		// 与AABB的碰撞
		bool Intersects(const Aabb &aabb);
		// 与Obb的碰撞
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

	// Aabb 包裹体
	class _declspec(dllexport) Aabb
	{
	public:
		Aabb(void) { ; }
		Aabb( Vector vcMin, Vector vcMax);
	public:
		// 通过Obb创建
		void Construct(const Obb *pObb);     
		// 剔除检测（ 一组面，如 视景体6个面 ）,面的法向量向外的
		int  Cull(const Plane *pPlanes, int nNumPlanes);  
		// 获取AABB的六个面
		void GetPlanes( Plane *pPlanes);
		// 线段是否在Aabb中
		bool Contains(const Ray &Ray, float fL);
	public:
		// 碰撞检测，f返回射线原点到交点的距离
		bool Intersects(const Ray &Ray, float *t);
		// 碰撞检测，f返回线段原点到交点的距离
		bool Intersects(const Ray &Ray, float fL, float *t);
		// 碰撞检测和其它aabb
		bool Intersects(const Aabb &aabb);
		// 点是否在AABB中
		bool Intersects(const Vector &vc0);
	public:
		Vector m_vcMin, m_vcMax; // 存放x y z的最大和最小值
		Vector m_vcCenter;       // 中心
	};

	//Obb
	class _declspec(dllexport) Obb
	{
	public:
		Obb(void) { /* nothing to do */ ; }
		// 改变Obb的坐标系
		inline void DeTransform( const Obb &obb, const Matrix &m);
        // 碰撞检测---射线， t 返回射线原点到交点的距离
		bool Intersects(const Ray &Ray, float *t);
		// 碰撞检测---线段 
		bool Intersects(const Ray &Ray, float fL, float *t);
		// 碰撞检测---Obb
		bool Intersects(const Obb &Obb);
		// 碰撞检测---三角形
		bool Intersects(const Vector &v0, 
			            const Vector &v1,
			            const Vector &v2);
		// 剔除和裁剪
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
		Vector    m_vcCenter;                    // 中心点

	};

	// 多边形
	class _declspec( dllexport )Polygon
	{
		friend class Plane;      
	public:
		Polygon(void);
		~Polygon(void);
	public:
		// 设置属性
		void Set(const Vector *pPoints, int nNumP,
			const unsigned int *pIndis, int nNumI);
		// 被平面切割处成前后两多边形
		void Clip(const Plane &Plane, 
			Polygon *pFront,
			Polygon *pBack);
		void Clip(const Aabb &aabb);
		int  Cull(const Aabb &aabb);

		void CopyOf( const Polygon &Poly );

		void SwapFaces(void);

		// 与射线相交
		bool Intersects(const Ray &Ray, bool, float *t);

		// 与射线段相交
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
		// 计算外接体
		void CalcBoundingBox(void);
	public:
		Vector       *m_pPoints;      // 顶点列表
		unsigned int *m_pIndis;       //  定点索引列表
	private:
		Plane          m_Plane;    // 多变型所在的面
		int            m_NumP;     // 顶点数
		int            m_NumI;     // 顶点索引数
		Aabb           m_Aabb;     // 外界体
		unsigned int   m_Flag;     // whatever you want it to be
	};

	// 四元组
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

	// 一个多边形列表的管理器
	class _declspec( dllexport )PolygonList
	{
	public:
		PolygonList( void );
		~PolygonList( void );

		// 插入多边形
		bool AddPolygon( const Polygon& polygon );

		// 重置多边形列表
		void Reset( void );

		Polygon* GetPolygon( void ){ return m_pPolygon; }
		unsigned int GetNum( void ){ return m_uNum; }
	private:
		Polygon*     m_pPolygon;
		unsigned int m_uNum;
		unsigned int m_uMax;

		// 检查存储空间
		bool CheckMem( void );
	};

	// BSP树结构
	class _declspec( dllexport )BspTree
	{
	public:
		BspTree( void );
		~BspTree( void );

		// 建立bsp树
		void BuildTree( const Polygon* pPolygons, UINT uNum );

		// 遍历( 建立一个从后到前顺序的多边形列表)
		void TraverseBtF( PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum );
		// 遍历( 建立一个从前到后顺序的多边形列表)
		void TraverseFtB( PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum );

		//UINT GetNumPolygon(){ return BspTree::m_sNumPolyOfTree; }
		Aabb GetAabb(){ return m_Aabb;}

		// 碰撞检测
		bool TestCollision( const Ray* pRay, float fL, float* pfD, Vector* pvcN );
        bool TestCollision( const Aabb* pAabb, const Plane* pFrustum );
		// 检测线段间的空间是否为空
        bool LineOfSight(const Vector& vcOrg, const Vector& vcDes );
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

		// 创建子节点
		void CreateChilds(void);
		// 寻找最佳分割多边形
		bool FindBestSplitter(void);
		// 添加多边形
		void AddPolygon(const Polygon&);
		// 设置属性
		void SetRelationships( BspTree*, BspTree*);
		// 计算外接球
		void CalcBoundingBox(const Polygon*, unsigned int);
		// 判断是否是叶子节点
		bool IsLeaf(void) { return (m_pFrontChild==NULL)&&(m_pBackChild==NULL); }
	};

	// 八叉树结构
	class _declspec( dllexport )Octree
	{
	public:
		Octree(void);
		~Octree(void);
        // 建立八叉树
		void BuildTree( const Polygon*, UINT );
		// 遍历八叉树,返回可见的多边形集合
		void Traverse( PolygonList*, PolygonList*, const Plane* ) ;

		Aabb GetAabb(){ return m_Aabb; }
		// 获取在给定点下方且距离该店最近的面
		bool GetFloor( const Vector& vcOrg, float* fD, Plane* pPlane );
		// 碰撞检测
		bool TestCollision( const Ray*, float fL, float* );
		bool TestCollision( const Aabb&, Plane* );

	private:
		Aabb     m_Aabb;
		Polygon* m_pPolygons;     // 多边形列表（叶子节点）
		UINT     m_nNumPolygons;  // 多边形数量（叶子节点）
		Octree*  m_pChild[8];
		int      m_nPos;          // 在父亲节点中的位置
		Octree*  m_pRoot;
		Octree*  m_pParent;

		// 计算Aabb
		void CalcBoundingBox( const Polygon* pPolygon, UINT nInt );
        // 初始化子节点的数据
		void InitChildObject( int iChildID, Octree* pParent );
		// 改变多边形列表
		void ChopListToMe( Polygon* pPolygons, UINT nNum );
		// 建立孩子节点
		void CreateChilds( Octree *pRoot);
		// 检测方向为-y的射线的碰撞情况
		bool IntersectsDownwardsRay(const Vector&, float fL );
		// 创建以多边形的形式组成的AABB---正方体
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
