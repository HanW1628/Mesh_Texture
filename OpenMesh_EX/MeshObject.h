#pragma once

#include <string>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/System/config.h>
#include <OpenMesh/Core/Mesh/Status.hh>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include "Common.h"

typedef OpenMesh::TriMesh_ArrayKernelT<>  TriMesh;
using namespace Eigen;
class MyMesh : public TriMesh
{
public:
	MyMesh();
	~MyMesh();

	int FindVertex(MyMesh::Point pointToFind);
	void ClearMesh();
};

class GLMesh
{
public:
	GLMesh();
	~GLMesh();

	bool Init(std::string fileName);
	void Render();
	bool SaveModel(std::string fileName);
	void GetModel(unsigned int faceID, std::vector<unsigned int> selectedFace);
	MyMesh mesh;
	MyMesh mesh_temp;
	// generate vertices
	
	GLuint vao;
	GLuint ebo;
	GLuint vboVertices, vboNormal;

private:

	bool LoadModel(std::string fileName);
	void LoadToShader();
	void LoadToShader_temp();
	void caculateUV();
	
};

class MeshObject
{
public:
	MeshObject();
	~MeshObject();

	bool Init(std::string fileName);
	void Render();
	void Render_temp();
	void RenderSelectedFace();
	bool AddSelectedFace(unsigned int faceID);
	void DeleteSelectedFace(unsigned int faceID);
	bool FindClosestPoint(unsigned int faceID, glm::vec3 worldPos, glm::vec3& closestPos);
	bool AddSelectedFacefinished();

	void MeshFragment();
	void MapToUV();
	
	void CalculateCotWeight();

	double MeshObject::cotan(OpenMesh::Vec3f a,OpenMesh::Vec3f b);
	//double MeshObject::cotan(const VectorXf &a, const  VectorXf& b);
	bool End(std::string fileName);
	
	int render_mode = 0;

private:
	GLMesh model;
	std::vector<unsigned int> selectedFace;
	std::vector<MyMesh::VertexHandle> selectedPoint;
	std::vector<MyMesh::VertexHandle> selectedPoint_temp;
	std::vector<MyMesh::HalfedgeHandle> selectedBoundary_heh;
	std::vector<MyMesh::VertexHandle> selectedMiddle_vh;
	std::vector<std::tuple<MyMesh::VertexHandle, double, double>> UV_tuple;

	//std::vector<MyMesh::Point> point;
	//std::vector<unsigned int*> fvIDsPtr;
	std::vector<int> elemCount;
	std::vector<MyMesh::VertexHandle> vhandle;
	OpenMesh::EPropHandleT<MyMesh::Edge> ep;
	OpenMesh::VPropHandleT<MyMesh::Point> pp;
	OpenMesh::VPropHandleT<MyMesh::Point> pp2;

	//OpenMesh::VPropHandleT<MyMesh::Point> ppnew;
	OpenMesh::VPropHandleT<MyMesh::Point> notinbound;//存非邊界vertex 的property
	
	OpenMesh::VPropHandleT<OpenMesh::ArrayKernel::VertexHandle> vertexId;//存新mesh的vertex 的property


	//std::vector<MyMesh::EdgeHandle> ehandle;
	OpenMesh::EPropHandleT<double> CotWeight;//存weight
	
};

