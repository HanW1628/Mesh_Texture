#include "MeshObject.h"
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdint>
using namespace std;
#define Quad


//#define Harmonic

struct OpenMesh::VertexHandle const OpenMesh::PolyConnectivity::InvalidVertexHandle;

#pragma region MyMesh

MyMesh::MyMesh()
{
	request_vertex_normals();
	request_vertex_status();
	request_face_status();
	request_edge_status();
}

MyMesh::~MyMesh()
{

}

int MyMesh::FindVertex(MyMesh::Point pointToFind)
{
	int idx = -1;
	for (MyMesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
		MyMesh::Point p = point(*v_it);
		if (pointToFind == p)
		{
			idx = v_it->idx();
			break;
		}
	}

	return idx;
}



void MyMesh::ClearMesh()
{
	if (!faces_empty())
	{
		for (MyMesh::FaceIter f_it = faces_begin(); f_it != faces_end(); ++f_it)
		{
			delete_face(*f_it, true);
		}

		garbage_collection();
	}
}

#pragma endregion

#pragma region GLMesh

GLMesh::GLMesh()
{

}

GLMesh::~GLMesh()
{

}

bool GLMesh::Init(std::string fileName)
{
	if (LoadModel(fileName))
	{
		

		LoadToShader();
		return true;
	}
	return false;
}

/*void GLMesh::Render()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, mesh.n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}*/


bool GLMesh::LoadModel(std::string fileName)
{
	OpenMesh::IO::Options ropt;
	if (OpenMesh::IO::read_mesh(mesh, fileName, ropt))
	{
		if (!ropt.check(OpenMesh::IO::Options::VertexNormal) && mesh.has_vertex_normals())
		{
			mesh.request_face_normals();
			mesh.request_edge_status();
			//mesh.request_edge_position();
			mesh.update_normals();
			mesh.release_face_normals();
		}

		return true;
	}

	return false;
}
bool GLMesh::SaveModel(std::string fileName)
{
	bool isSave = false;
	if (OpenMesh::IO::write_mesh(mesh, fileName))
	{
		isSave = true;
	}
	return isSave;
}
void GLMesh::caculateUV() {
	/*MyMesh::HalfedgeHandle heh, heh_init;
	// Get the halfedge handle assigned to vertex[0]
	heh = heh_init = mesh.halfedge_handle(vertex[0].handle());
	// heh now holds the handle to the initial halfedge.
	// We now get further on the boundary by requesting
	// the next halfedge adjacent to the vertex heh
	// points to...
	heh = mesh.next_halfedge_handle(heh);
	// We can do this as often as we want:
	while (heh != heh_init) {
		heh = mesh.next_halfedge_handle(heh);
	}
	bool is_boundary( heh) const ;*/
}
void GLMesh::LoadToShader()
{
	std::vector<MyMesh::Point> vertices;
	vertices.reserve(mesh.n_vertices());
	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		vertices.push_back(mesh.point(*v_it));

		MyMesh::Point p = mesh.point(*v_it);
	}

	std::vector<MyMesh::Normal> normals;
	normals.reserve(mesh.n_vertices());
	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		normals.push_back(mesh.normal(*v_it));
	}
	
	std::vector<unsigned int> indices;
	indices.reserve(mesh.n_faces() * 3);
	for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		for (MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			indices.push_back(fv_it->idx());
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Point) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vboNormal);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Normal) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GLMesh::LoadToShader_temp()
{
	std::vector<MyMesh::Point> vertices;
	vertices.reserve(mesh.n_vertices());
	for (MyMesh::VertexIter v_it = mesh_temp.vertices_begin(); v_it != mesh_temp.vertices_end(); ++v_it)
	{
		vertices.push_back(mesh_temp.point(*v_it));

		MyMesh::Point p = mesh_temp.point(*v_it);
	}

	std::vector<MyMesh::Normal> normals;
	normals.reserve(mesh_temp.n_vertices());
	for (MyMesh::VertexIter v_it = mesh_temp.vertices_begin(); v_it != mesh_temp.vertices_end(); ++v_it)
	{
		normals.push_back(mesh_temp.normal(*v_it));
	}

	std::vector<unsigned int> indices;
	indices.reserve(mesh_temp.n_faces() * 3);
	for (MyMesh::FaceIter f_it = mesh_temp.faces_begin(); f_it != mesh_temp.faces_end(); ++f_it)
	{
		for (MyMesh::FaceVertexIter fv_it = mesh_temp.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			indices.push_back(fv_it->idx());
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Point) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vboNormal);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Normal) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

#pragma endregion

MeshObject::MeshObject()
{

}

MeshObject::~MeshObject()
{
}

bool MeshObject::Init(std::string fileName)
{
	selectedFace.clear();
	selectedPoint.clear();

	return model.Init(fileName);
}
bool MeshObject::End(std::string fileName)
{
	//selectedFace.clear();

	return model.SaveModel(fileName);
}

void MeshObject::Render()
{
	glBindVertexArray(model.vao);
	glDrawElements(GL_TRIANGLES, model.mesh.n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void MeshObject::Render_temp()
{
	glBindVertexArray(model.vao);
	glDrawElements(GL_TRIANGLES, model.mesh_temp.n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void MeshObject::RenderSelectedFace()
{
	if (selectedFace.size() > 0)
	{

		std::vector<unsigned int*> offsets(selectedFace.size());
		for (int i = 0; i < offsets.size(); ++i)
		{
			offsets[i] = (GLuint*)(selectedFace[i] * 3 * sizeof(GLuint));
		}

		std::vector<int> count(selectedFace.size(), 3);

		glBindVertexArray(model.vao);
		glMultiDrawElements(GL_TRIANGLES, &count[0], GL_UNSIGNED_INT, (const GLvoid **)&offsets[0], selectedFace.size());
		glBindVertexArray(0);
	}
}

bool MeshObject::AddSelectedFace(unsigned int faceID)
{	
	if (std::find(selectedFace.begin(), selectedFace.end(), faceID) == selectedFace.end() &&
		faceID >= 0 && faceID < model.mesh.n_faces())
	{
		selectedFace.push_back(faceID);
		model.mesh.add_property(pp);

		// lotus
		for (auto fv_it = model.mesh.fv_ccwiter((MyMesh::FaceHandle)faceID); fv_it.is_valid(); ++fv_it)
		{
			selectedPoint.push_back(*fv_it);
		}
		return true;
		// sutol
	}
	return false;
}

void MeshObject::MeshFragment()
{
	MyMesh::VertexHandle newvh;
	int temp_num = 0, tempidx;

	//selectedPoint_temp.clear();

	//cout << selectedFace.size() << endl;
	//cout << selectedPoint.size() << endl;

	for (auto it = selectedFace.begin(); it != selectedFace.end(); ++it)
	{
		selectedPoint_temp.clear();
		for (int i = 0; i < 3; i++)
		{
			tempidx = model.mesh_temp.FindVertex(model.mesh.point(selectedPoint[3 * temp_num + i]));
			if (tempidx < 0)
			{
				newvh = model.mesh_temp.add_vertex(model.mesh.point(selectedPoint[3 * temp_num + i]));
			}
			else
			{
				newvh = (MyMesh::VertexHandle) tempidx;
			}

			selectedPoint_temp.push_back(newvh);
		}
		
		model.mesh_temp.add_face(selectedPoint_temp);

		temp_num++;
	}
	//cout << model.mesh_temp.n_edges() << endl;
	//cout << model.mesh_temp.n_vertices() << endl;

}



void MeshObject::MapToUV()
{
	MyMesh::HalfedgeHandle first_heh, temp_heh;
	double total_edgelen = 0, now_UVlen = 0;

	std::cout << "MapToUV start" << endl;
	// --------------get boundary----------------
	for (auto he_it = model.mesh_temp.halfedges_begin(); he_it != model.mesh_temp.halfedges_end(); ++he_it)
	{
		if (model.mesh_temp.is_boundary(*he_it))
		{
			first_heh = temp_heh = *he_it;
			break;
		}
	}
	//cout << "first_heh" << first_heh << endl;
	temp_heh = model.mesh_temp.next_halfedge_handle(temp_heh);
	selectedBoundary_heh.clear();
	while (temp_heh != first_heh)
	{
		selectedBoundary_heh.push_back(temp_heh);
		total_edgelen += model.mesh_temp.calc_edge_length(temp_heh);
		//cout << model.mesh_temp.calc_edge_length(temp_heh) << endl;
		temp_heh = model.mesh_temp.next_halfedge_handle(temp_heh);
	}
	selectedBoundary_heh.push_back(temp_heh);
	total_edgelen += model.mesh_temp.calc_edge_length(temp_heh);

	selectedMiddle_vh.clear();
	for (auto v_it = model.mesh_temp.vertices_begin(); v_it != model.mesh_temp.vertices_end(); ++v_it)
	{
		if (!model.mesh_temp.is_boundary(*v_it))
		{
			selectedMiddle_vh.push_back(*v_it);
			//cout << "Middle vh: " << *v_it << endl;
		}
	}
	//cout << model.mesh_temp.n_vertices() << endl;
	std::cout << selectedBoundary_heh.size() << endl;
	//cout << selectedMiddle_vh.size() << endl;
	double temp_d = 0;

	UV_tuple.push_back(make_tuple(model.mesh_temp.from_vertex_handle(*selectedBoundary_heh.begin()), 0, 0));

	for (auto it = selectedBoundary_heh.begin(); it != selectedBoundary_heh.end()-1; ++it)
	{

		temp_d = now_UVlen + 4 * (model.mesh_temp.calc_edge_length(*it) / total_edgelen);
		std::cout << "double" << temp_d << "int" << int(temp_d) << endl;
		switch (int(temp_d))
		{
			case 0:
				UV_tuple.push_back(make_tuple(model.mesh_temp.to_vertex_handle(*it), temp_d, 0));
				break;
			case 1:
				UV_tuple.push_back(make_tuple(model.mesh_temp.to_vertex_handle(*it), 1, temp_d - 1));
				break;
			case 2:
				UV_tuple.push_back(make_tuple(model.mesh_temp.to_vertex_handle(*it), 3 - temp_d, 1));
				break;
			case 3:
				UV_tuple.push_back(make_tuple(model.mesh_temp.to_vertex_handle(*it), 0, 4 - temp_d));
				break;
			case 4:
				std::cout << "oh no" << endl;
				break;
		}
		//cout << "1" << endl;
		now_UVlen += 4 * (model.mesh_temp.calc_edge_length(*it) / total_edgelen);
		//UV_tuple.push_back(make_tuple(model.mesh_temp.to_vertex_handle(*it),)))
	}


	std::cout << UV_tuple.size() << endl;
	for (auto it = UV_tuple.begin(); it != UV_tuple.end(); ++it)
	{
		//cout << 2 << endl;
		std::cout << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << endl;
	}

}



// 偉大的人

//bool MeshObject::AddSelectedFacefinished()
//{
//	//§R±¼¤W¤@¦¸¿ïªº­±
//	if (!model.mesh_temp.faces_empty())
//	{
//		for (MyMesh::FaceIter f_it = model.mesh_temp.faces_begin(); f_it != model.mesh_temp.faces_end(); ++f_it)
//		{
//			model.mesh_temp.delete_face(*f_it, true);
//		}
//
//		model.mesh_temp.garbage_collection();
//	}
//	//§R±¼¤W¤@¦¸¿ïªºÂI
//	if (!model.mesh_temp.vertices_empty())
//	{
//		for (MyMesh::VertexIter v_it = model.mesh_temp.vertices_begin(); v_it != model.mesh_temp.vertices_end(); ++v_it)
//		{
//			model.mesh_temp.delete_vertex(*v_it, true);
//		}
//
//		model.mesh_temp.garbage_collection();
//	}
//	model.mesh.add_property(vertexId);
//	
//	std::cout  << std::endl;
//
//    //add¿ïªºÂI¨ìnew mesh©M¹ïÀ³·sÂÂÂIvertex ID
//	for (int i = 0; i < selectedPoint.size(); i++)
//	{
//		vhandle.push_back(model.mesh_temp.add_vertex(MyMesh::Point(model.mesh.point(selectedpoint[i]))));
//		model.mesh.property(vertexId, selectedpoint[i]) = vhandle[i];
//
//		//std::cout << selectedpoint[i]<<"selectedpoint[i]"<<model.mesh.property(vertexId, selectedpoint[i]) << std::endl;
//		//std::cout << selectedpoint[i] << std::endl;
//		//std::cout << vhandle[i] << std::endl;
//	}
//	
//	//§â·smeshªºÂI¦s¨ìÂÂmeshªºproperty
//	/*model.mesh.add_property(ppnew);
//	for (MyMesh::VertexIter v_it = model.mesh_temp.vertices_begin();v_it != model.mesh_temp.vertices_end(); ++v_it)
//	{	
//		model.mesh.property(ppnew, *v_it) = model.mesh_temp.point(*v_it);
//		//std::cout <<*v_it<< " new: " << model.mesh.property(ppnew, *v_it) << std::endl;			
//	}*/
//
//	//add face¨ìnew mesh
//	std::vector<MyMesh::VertexHandle>  face_vhandles;
//	for (MyMesh::FaceIter f_it = model.mesh.faces_begin(); f_it != model.mesh.faces_end(); ++f_it)
//	{
//		for (int i = 0; i < selectedFace.size(); i++)
//		{
//			if (*f_it == (const OpenMesh::ArrayKernel::FaceHandle)selectedFace[i])
//			{
//				face_vhandles.clear();
//				for (MyMesh::FaceVertexIter fv_it = model.mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
//				{	
//					face_vhandles.push_back(model.mesh.property(vertexId, *fv_it));
//					//std::cout << *fv_it << ":   " << model.mesh.property(vertexId, *fv_it) << std::endl;
//				}
//				model.mesh_temp.add_face(face_vhandles);
//			}
//		}
//	}
//	
//
//	//´ú¸Õ¦sÃä¬ÉªºÂI
//	model.mesh_temp.add_property(pp2);
//	for (MyMesh::VertexIter v_it = model.mesh_temp.vertices_begin(); v_it != model.mesh_temp.vertices_end(); ++v_it)
//	{
//		//std::cout << std::endl;
//		//std::cout << *v_it << ":³o­Ó¬O¤À¹j½utest==================   " << model.mesh_temp.property(pp2, *v_it) << std::endl;
//
//		//if (model.mesh_temp.is_boundary(*v_it)) 
//		//{
//			model.mesh_temp.property(pp2, *v_it) = model.mesh_temp.point(*v_it);
//			std::cout << *v_it << " *v_it:   " << model.mesh_temp.property(pp2, *v_it) << std::endl;
//		//}
//	}
//	//¦sÃä¬É
//	model.mesh_temp.add_property(ep);
//	std::cout <<  ":=====================================================   " << std::endl;
//	for (MyMesh::EdgeIter e_it = model.mesh_temp.edges_begin(); e_it != model.mesh_temp.edges_end(); ++e_it)
//	{				   
//			//std::cout << "*e_it: " << *e_it << std::endl;
//			std::cout <<  ":³o­Ó¬O¤À¹j½u2==================   "  << std::endl;
//			if (model.mesh_temp.is_boundary(*e_it))
//			{
//				model.mesh_temp.property(ep, *e_it) = model.mesh_temp.edge(*e_it);
//				std::cout << "*e_it: "<<*e_it <<" is boundary"<<  std::endl;
//			}		
//	}
//	CalculateCotWeight();
//	model.mesh_temp.remove_property(pp2);
//	model.mesh_temp.remove_property(ep);
//	vhandle.clear();
//	return true;
//}

void MeshObject::CalculateCotWeight()
{
	MyMesh::HalfedgeHandle heh;
	MyMesh::VertexHandle vhF, vhT, vhTnext;
	MyMesh::Point pF, pT, p1, p2;
	double v0, v1, v2, v3, v4;
	double cos_alpha, cos_beta, cotan1, cotan2;
	double wij;

	model.mesh_temp.add_property(CotWeight);

	for (auto e_it = model.mesh_temp.edges_begin(); e_it != model.mesh.edges_end(); ++e_it)
	{
		heh = model.mesh_temp.halfedge_handle(*e_it, 0);
		vhF = model.mesh_temp.from_vertex_handle(heh);
		vhT = model.mesh_temp.to_vertex_handle(heh);
		vhTnext = model.mesh_temp.opposite_vh(heh);
		pF = model.mesh_temp.point(vhF);
		pT = model.mesh_temp.point(vhT);
		p1 = model.mesh_temp.point(vhTnext);
		p2 = model.mesh_temp.point(model.mesh_temp.opposite_he_opposite_vh(heh));

		v0 = (p1 - p2).norm();
		v1 = (pF - p1).norm();
		v2 = (pT - p1).norm();
		v3 = (pF - p2).norm();
		v4 = (pT - p2).norm();

		// NOTE: cos(alpha) = (a^2.b^2  - c^2) / (2.a.b)
		// with a, b, c the lengths of of the sides of the triangle and (a, b) forming the angle alpha.
		// p1, p2 是相鄰某條邊的兩個 face 的兩個頂點
		/*
								  pT◀---v4----p2
								 ◥ ◤         /
								/   \       /
							  v2    v0    v3
							  /       \   /
							 /         \ ◣
						   p1----v1---▶ pF
		*/

		cos_alpha = fabs((v1 * v1 + v2 * v2 - v0 * v0) / (2.0f * v1 * v2));
		cos_beta  = fabs((v3 * v3 + v4 * v4 - v0 * v0) / (2.0f * v3 * v4));
		// NOTE: cot(x) = cos(x)/sin(x)
		// and recall cos(x)^2 + sin(x)^2 = 1
		// then sin(x) = sqrt(1-cos(x))
		cotan1 = cos_alpha / sqrt(1.0f - cos_alpha * cos_alpha);
		cotan2 = cos_beta / sqrt(1.0f - cos_beta * cos_beta);

		// If the mesh is not a water-tight closed volume
		// we must check for edges lying on the sides of wholes
		if (model.mesh.is_boundary(vhT) && model.mesh.is_boundary(vhF))
		{
			if (p1 == p2)
			{
				cotan2 = 0.0;
			}
			else {
				if (model.mesh.is_boundary(vhT) && model.mesh.is_boundary(vhTnext))
					cotan2 = 0.0;
				else
					cotan1 = 0.0;
			}
		}

		// wij = (cot(alpha) + cot(beta))
		wij = (cotan1 + cotan2) / 2.0;
		if (isnan(wij)) {
			wij = 0.0;
		}
		// compute the cotangent value close to 0.0f.
		// as cotan approaches infinity close to zero we clamp
		// higher values
		const double eps = 1e-6f;
		const double cotan_max = cos(eps) / sin(eps);
		if (wij >= cotan_max) {
			wij = cotan_max;
		}

		model.mesh_temp.property(CotWeight, *e_it) = wij;
	}
}


// 偉大的人
//void MeshObject::CaculateWeight()
//{
//	double cotan_alpha = 0;
//	double cotan_beta = 0;
//	double wij = 0;
//	const float eps = 1e-6f;
//	const float cotan_max = cos(eps) / sin(eps);
//	//¦s«DÃä¬ÉÂIªºone_ring
//	/*std::vector< std::vector<OpenMesh::ArrayKernel::VertexHandle> > first_ring;
//	std::vector<OpenMesh::ArrayKernel::VertexHandle>  vertexindex;
//
//	std::vector<OpenMesh::ArrayKernel::VertexHandle>  vertex_is_not_boundary;//¦s«DÃä¬Évertex_id
//
//	std::vector<OpenMesh::ArrayKernel::EdgeHandle>  edgetmp;//¦s«DÃä¬Évertex_id
//
//	
//
//	//std::vector<int>nb_neigh;
//	//int nb_neighs=0;
//	model.mesh_temp.add_property(notinbound);//±Ò¥Î¦s«DÃä¬Évertexªºproperty
//	for (MyMesh::VertexIter v_it = model.mesh_temp.vertices_begin(); v_it != model.mesh_temp.vertices_end(); ++v_it)
//	{                
//		        
//				if (!model.mesh_temp.is_boundary(*v_it))
//				{
//					vertex_is_not_boundary.push_back(*v_it);//¦s¤J«DÃä¬Évertex_id			
//					model.mesh_temp.property(notinbound, *v_it) =model.mesh_temp.point(*v_it);//¦s¤J«DÃä¬Évertex
//
//					for (MyMesh::VertexVertexIter vv_it = model.mesh_temp.vv_iter(*v_it); vv_it.is_valid(); ++vv_it)
//					{
//						vertexindex.push_back(*vv_it);
//						//nb_neighs++;
//					}
//					first_ring.push_back(vertexindex);
//					//nb_neigh.push_back(nb_neighs);
//					vertexindex.clear();
//					//nb_neighs = 0;
//				}
//	}
//	OpenMesh::ArrayKernel::VertexHandle vertex_j;
//	OpenMesh::ArrayKernel::VertexHandle vertex_j_next;
//	OpenMesh::ArrayKernel::VertexHandle vertex_j_prev;
//	int neighs;
//	for (int i = 0; i < vertex_is_not_boundary.size(); i++)
//	{
//		std::cout << "X BOUND" << std::endl;
//		std::cout << vertex_is_not_boundary[i] << std::endl;
//		std::cout << model.mesh_temp.property(notinbound, (OpenMesh::ArrayKernel::VertexHandle)vertex_is_not_boundary[i]) << std::endl;
//		std::cout  << "X BOUND" << std::endl;
//	}
//	//model.mesh_temp.add_property(pe);
//	for (int i = 0; i < first_ring.size(); i++)
//	{
//		neighs = first_ring[i].size();
//		std::cout << "*******************" << std::endl;
//		std::cout << first_ring[i].size() << std::endl;
//		for (int j = 0; j < first_ring[i].size(); j++)
//		{
//			vertex_j = first_ring[i][j]; 	
//
//			vertex_j_next = first_ring[i][(j + 1) % neighs];
//			vertex_j_prev = first_ring[i][(j - 1) >= 0 ? (j - 1) : neighs - 1];			
//			std::cout << vertex_j << vertex_j_next<< vertex_j_prev<< std::endl;
//			//std::cout << first_ring[i][j] << std::endl;
//			std::cout << std::endl;
//			for (MyMesh::VertexIter v_it = model.mesh_temp.vertices_begin(); v_it != model.mesh_temp.vertices_end(); ++v_it)
//			{
//
//				if (*v_it == vertex_j)
//				{
//					//for (int i = 0; i < vertex_is_not_boundary.size(); i++)
//					//{
//						
//						for (MyMesh::VertexEdgeIter ve_it = model.mesh_temp.ve_iter(*v_it); ve_it.is_valid(); ++ve_it)
//						{
//							edgetmp.push_back(*ve_it);
//							model.mesh_temp.edge(*ve_it);
//							std::cout << "*ve_it"<< *ve_it << std::endl;;//¦s¤J«DÃä¬Évertex
//							//std::cout << "X BOUND" << std::endl;
//							//std::cout << vertex_is_not_boundary[i] << std::endl;
//							//std::cout << model.mesh_temp.property(notinbound, (OpenMesh::ArrayKernel::VertexHandle)vertex_is_not_boundary[i]) << std::endl;
//							//std::cout << "v1" << std::endl;
//							//std::cout << model.mesh_temp.property(notinbound, (OpenMesh::ArrayKernel::VertexHandle)vertex_is_not_boundary[i]) - model.mesh_temp.point(vertex_j_prev) << std::endl;	
//							
//						}
//						
//
//						OpenMesh::Vec3f v1 = (OpenMesh::Vec3f)(model.mesh_temp.property(notinbound, (OpenMesh::ArrayKernel::VertexHandle)vertex_is_not_boundary[i]) - model.mesh_temp.point(vertex_j_prev));
//						//std::cout << "v2" << std::endl;
//						//std::cout << model.mesh_temp.point(vertex_j) - model.mesh_temp.point(vertex_j_prev) << std::endl;
//						OpenMesh::Vec3f v2 = (OpenMesh::Vec3f)(model.mesh_temp.point(vertex_j) - model.mesh_temp.point(vertex_j_prev));
//						//std::cout << "v3" << std::endl;
//						//std::cout << model.mesh_temp.property(notinbound, (OpenMesh::ArrayKernel::VertexHandle)vertex_is_not_boundary[i]) - model.mesh_temp.point(vertex_j_next) << std::endl;
//						OpenMesh::Vec3f v3 = (OpenMesh::Vec3f)(model.mesh_temp.property(notinbound, (OpenMesh::ArrayKernel::VertexHandle)vertex_is_not_boundary[i]) - model.mesh_temp.point(vertex_j_next));
//						//std::cout << "v4" << std::endl;
//						//std::cout << model.mesh_temp.point(vertex_j) - model.mesh_temp.point(vertex_j_next) << std::endl;
//						OpenMesh::Vec3f v4 = (OpenMesh::Vec3f)(model.mesh_temp.point(vertex_j) - model.mesh_temp.point(vertex_j_next));
//						//std::cout << "X BOUND" << std::endl;	
//						cotan_alpha = cotan(v1, v2);
//						cotan_beta = cotan(v3, v4);
//						//std::cout <<"cotan_alpha "<< cotan(v1, v2)<<std::endl;
//						//std::cout << "cotan_beta " << cotan(v3, v4) << std::endl;
//						
//						
//						wij = (cotan_alpha + cotan_beta)/ 2.0f;
//						std::cout << "edgetmp[1] " << edgetmp[1] << " weight " <<wij << std::endl;
//						
//						//std::cout << "weight " << std::setprecision(10)<< wij  << std::endl;
//						//wij = clamp(cotan_max, cotan_max, cotan_max);
//						if (wij >= cotan_max) {
//							wij = cotan_max;
//						}
//						std::cout << "finial_weight " << wij << std::endl;
//						/*for (int i = 0; i < v1_to_v4_edge.size(); i++)
//						{
//							std::cout<<v1_to_v4_edge[i] << std::endl;
//						}
//						edgetmp.clear();
//						
//					//}
//					//std::cout << "test " << 0.123456789-0.12345679 << std::endl;;
//					//std::cout << "+++++++++++++++" << std::endl;
//					//std::cout<<model.mesh_temp.point(*v_it)<<std::endl;
//					
//
//				}
//				
//			}
//		}
//		std::cout << std::endl;
//		std::cout  << std::endl;
//	}*/
//    model.mesh_temp.add_property(weight);
//	for (MyMesh::EdgeIter e_it = model.mesh_temp.edges_begin(); e_it != model.mesh_temp.edges_end(); ++e_it)
//	{
//		if (!model.mesh_temp.is_boundary(*e_it))
//		{
//			//ehandle.push_back(*e_it);
//			TriMesh::HalfedgeHandle heh,  heh_next, heh2,heh_next2 ;
//			OpenMesh::ArrayKernel::VertexHandle   vertex_j, vertex_j_next, vertex_j_prev, vertex_i;
//			heh = model.mesh_temp.halfedge_handle(*e_it, 1);//¥ªÃä
//			heh2 = model.mesh_temp.halfedge_handle(*e_it, 0);//¥kÃä
//
//			//std::cout << model.mesh_temp.to_vertex_handle(heh) << std::endl;
//			vertex_j = model.mesh_temp.from_vertex_handle(heh);//<---------------------------------------------vertex_j
//			
//			std::cout << vertex_j << std::endl;
//			//std::cout << model.mesh_temp.from_vertex_handle(heh) << std::endl;
//			vertex_i = model.mesh_temp.to_vertex_handle(heh);//<---------------------------------------------vertex_i
//			std::cout << vertex_i << std::endl;
//
//			std::cout << model.mesh_temp.to_vertex_handle(heh2) << std::endl;
//			std::cout << model.mesh_temp.from_vertex_handle(heh2) << std::endl;
//			std::cout << "heh: " << heh << std::endl;
//			std::cout << "heh2: " << heh2 << std::endl;
//			std::cout << "---------------------------------------- " << std::endl;
//			heh_next = model.mesh_temp.next_halfedge_handle(heh);
//			heh_next2 = model.mesh_temp.next_halfedge_handle(heh2);
//			//heh_pre = model.mesh_temp.prev_halfedge_handle(heh);
//			std::cout << "hehnext: " << heh_next << std::endl;
//			std::cout << "hehnext2: " << heh_next2 << std::endl;
//			//std::cout << "hehpre: " << heh_pre << std::endl;
//			std::cout << "---------------------------------------- " << std::endl;
//			//std::cout << model.mesh_temp.to_vertex_handle(heh_next) << std::endl;
//			vertex_j_next = model.mesh_temp.to_vertex_handle(heh_next);//<---------------------------------------------vertex_j_next
//			std::cout << vertex_j_next << std::endl;
//			//std::cout << model.mesh_temp.to_vertex_handle(heh_next2) << std::endl;
//			vertex_j_prev = model.mesh_temp.to_vertex_handle(heh_next2);//<---------------------------------------------vertex_j_prev
//			std::cout << vertex_j_prev << std::endl;
//			std::cout << "---------------------------------------- " << std::endl;
//
//			OpenMesh::Vec3f v1 = model.mesh_temp.point(vertex_i) - model.mesh_temp.point(vertex_j_prev) ;
//			OpenMesh::Vec3f v2 = model.mesh_temp.point(vertex_j) - model.mesh_temp.point(vertex_j_prev) ;
//			OpenMesh::Vec3f v3 = model.mesh_temp.point(vertex_i) - model.mesh_temp.point(vertex_j_next) ;
//			OpenMesh::Vec3f v4 = model.mesh_temp.point(vertex_j) - model.mesh_temp.point(vertex_j_next) ;
//
//			std::cout << v1 << std::endl;
//			std::cout <<v2 << std::endl;
//			std::cout << v3 << std::endl;
//			std::cout << v4 << std::endl;
//			cotan_alpha = cotan(v1, v2);
//			cotan_beta = cotan(v3, v4);
//			wij = (cotan_alpha + cotan_beta) / 2.0f;
//			std::cout<<wij << std::endl;
//			model.mesh_temp.property(weight, *e_it) = wij;
//		}	
//	}
//	for (MyMesh::EdgeIter e_it = model.mesh_temp.edges_begin(); e_it != model.mesh_temp.edges_end(); ++e_it)
//	{
//		std::cout << "====================================" << std::endl;
//		std::cout<< *e_it <<"        "<<model.mesh_temp.property(weight, *e_it)<<std::endl;
//	}
//	/*for (int i = 0; i < ehandle.size(); i++)
//	{
//		std::cout << "ehandle: " << ehandle[i] << std::endl;
//	}
//	TriMesh::HalfedgeHandle heh, heh_init;
//	heh = heh_init = model.mesh_temp.halfedge_handle(vhandle[0]);
//	std::cout << "heh: " << heh << std::endl;
//	heh = model.mesh_temp.next_halfedge_handle(heh);
//	//heh = model.mesh_temp.prev_halfedge_handle(heh);
//	std::cout << "hehnext: " << heh << std::endl;
//	while (heh != heh_init) {
//
//		heh = model.mesh_temp.next_halfedge_handle(heh);
//		//heh = model.mesh_temp.prev_halfedge_handle(heh);
//		std::cout << "hehnext: " << heh << std::endl;
//
//	}*/
//}
// 偉大的人
double MeshObject::cotan(OpenMesh::Vec3f a, OpenMesh::Vec3f b) {
	return (a|b) / (a%b).norm();
}
//¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×
void MeshObject::DeleteSelectedFace(unsigned int faceID)
{
	selectedFace.erase(std::remove(selectedFace.begin(), selectedFace.end(), faceID), selectedFace.end());
}

bool MeshObject::FindClosestPoint(unsigned int faceID, glm::vec3 worldPos, glm::vec3& closestPos)
{
	OpenMesh::FaceHandle fh = model.mesh.face_handle(faceID);
	if (!fh.is_valid())
	{
		return false;
	}

	double minDistance = 0.0;
	MyMesh::Point p(worldPos.x, worldPos.y, worldPos.z);
	MyMesh::FVIter fv_it = model.mesh.fv_iter(fh);
	MyMesh::VertexHandle closestVH = *fv_it;
	MyMesh::Point v1 = model.mesh.point(*fv_it);
	++fv_it;

	minDistance = (p - v1).norm();
	for (; fv_it.is_valid(); ++fv_it)
	{
		MyMesh::Point v = model.mesh.point(*fv_it);
		double distance = (p - v).norm();
		if (minDistance > distance)
		{
			minDistance = distance;
			closestVH = *fv_it;
		}
	}
	MyMesh::Point closestPoint = model.mesh.point(closestVH);
	closestPos.x = closestPoint[0];
	closestPos.y = closestPoint[1];
	closestPos.z = closestPoint[2];
	return true;
}