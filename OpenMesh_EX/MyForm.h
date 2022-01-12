#pragma once

//#include "GL/glew.h"
//#include "GLFW/glfw3.h"
//#include "ResourcePath.h"
#include "MeshObject.h"
#include "DrawModelShader.h"
#include "PickingShader.h"
#include "PickingTexture.h"
#include "DrawPickingFaceShader.h"
#include "ViewManager.h"
#include "DotNetUtilities.h"
//#include "DrawPointShader.h"
//#include "Mesh/GUA_OM.h"
//#include "Mesh/DP.h"
//#include "Mesh/XForm.h"
//#include "Mesh/GLCamera.h"

//const std::string ProjectName = "OpenMesh_EX";
glm::vec3 worldPos;
bool updateFlag = false;

GLuint faceID=0;
//bool isRightButtonPress = false;
GLuint currentFaceID = 0;
int currentMouseX = 0;
int currentMouseY = 0;
int windowWidth = 800;
int windowHeight = 600; 
int selectionMode = 1;
GLuint			program;			// shader program
glm::mat4		proj_matrix;		// projection matrix
float			aspect;
ViewManager		meshWindowCam;
GLuint texture;
MeshObject model;

// shaders
DrawModelShader drawModelShader;
DrawPickingFaceShader drawPickingFaceShader;
PickingShader pickingShader;
PickingTexture pickingTexture;
//DrawPointShader drawPointShader;

// vbo for drawing point
GLuint vboPoint;


//Tri_Mesh *mesh;

//xform xf;
//GLCamera camera;
//float fov = 0.7f;

/*static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};
Mouse::button Mouse_State = Mouse::ROTATE;*/

namespace OpenMesh_EX {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm ªººK­n
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  ¦b¦¹¥[¤J«Øºc¨ç¦¡µ{¦¡½X
			//
		}

	protected:
		/// <summary>
		/// ²M°£¥ô¦ó¨Ï¥Î¤¤ªº¸ê·½¡C
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadModelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;

	protected:

	private:
		/// <summary>
		/// ³]­p¤u¨ã©Ò»ÝªºÅÜ¼Æ¡C
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ¦¹¬°³]­p¤u¨ã¤ä´©©Ò»Ýªº¤èªk - ½Ð¤Å¨Ï¥Îµ{¦¡½X½s¿è¾¹­×§ï
		/// ³o­Ó¤èªkªº¤º®e¡C
		/// </summary>
		void InitializeComponent(void)
		{
			HKOGLPanel::HKCOGLPanelCameraSetting^ hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^ hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(800, 25);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadModelToolStripMenuItem,
					this->saveModelToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(40, 21);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 25);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(800, 599);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::hkoglPanelControl1_KeyPress);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseWheel);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 624);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"OpenMesh_EX";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void hkoglPanelControl1_Load(System::Object^  sender, System::EventArgs^  e)
{
	   //glfwInit();
	    GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cout << "GLEW is not initialized!\n";
			return;
		}
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_POINT_SMOOTH);
		//ResourcePath::shaderPath = "./Shader/" + ProjectName + "/";
		drawModelShader.Init();
		pickingShader.Init();
		pickingTexture.Init(windowWidth, windowHeight);
		
		drawPickingFaceShader.Init();
		//drawPointShader.Init();
		glGenBuffers(1, &vboPoint);
		

		
}
//µe
private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	
	//glEnable(GL_COLOR_MATERIAL);
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//point center;
	//center[0] = 0.0;
	//center[1] = 0.0;
	//center[2] = 0.0;
	//camera.setupGL(xf * center, 1.0);
	aspect = windowWidth * 1.0f / windowHeight;
	//std::cout << aspect << std::endl;
	glm::mat4 mvMat = meshWindowCam.GetViewMatrix()*meshWindowCam.GetModelMatrix();
	glm::mat4 pMat = meshWindowCam.GetProjectionMatrix(aspect);


	// write faceID+1 to framebuffer
	pickingTexture.Enable();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pickingShader.Enable();
	pickingShader.SetMVMat(value_ptr(mvMat));
	pickingShader.SetPMat(value_ptr(pMat));
	
	// lotus

	if (model.render_mode == 0)
	{
		model.Render();
	}
	else if (model.render_mode == 1)
	{
		model.Render_temp();
	}

	// sutol

	pickingShader.Disable();
	pickingTexture.Disable();


	// draw model
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawModelShader.Enable();
	glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(mvMat)));

	drawModelShader.SetWireColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	drawModelShader.SetFaceColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	drawModelShader.UseLighting(true);
	drawModelShader.DrawWireframe(true);
	drawModelShader.SetNormalMat(normalMat);
	drawModelShader.SetMVMat(mvMat);
	drawModelShader.SetPMat(pMat);

	// lotus

	if (model.render_mode == 0)
	{
		model.Render();
	}
	else if (model.render_mode == 1)
	{
		model.Render_temp();
	}

	// sutol

	drawModelShader.Disable();

	if (selectionMode == 1 || selectionMode == 2) {
		//glBindTexture(GL_TEXTURE_2D, texture);
		drawPickingFaceShader.Enable();
		drawPickingFaceShader.SetMVMat(value_ptr(mvMat));
		drawPickingFaceShader.SetPMat(value_ptr(pMat));
		drawPickingFaceShader.SetTex();
		model.RenderSelectedFace();
		drawPickingFaceShader.Disable();
	}


	/*if (selectionMode == 3)
	{
		if (updateFlag)
		{
			float depthValue = 0;
			int windowX = currentMouseX;
			int windowY = windowHeight - currentMouseY;
			glReadPixels(windowX, windowY, 2, 1.5, GL_DEPTH_COMPONENT, GL_FLOAT, &depthValue);

			GLint _viewport[4];
			glGetIntegerv(GL_VIEWPORT, _viewport);
			glm::vec4 viewport(_viewport[0], _viewport[1], _viewport[2], _viewport[3]);
			glm::vec3 windowPos(windowX, windowY, depthValue);
			glm::vec3 wp = glm::unProject(windowPos, mvMat, pMat, viewport);
			model.FindClosestPoint(currentFaceID - 1, wp, worldPos);

			updateFlag = false;
			//hkoglPanelControl1->Invalidate();
		}*/
		/*
			Using OpenGL 1.1 to draw point
		*/
		/*glPushMatrix();
		glPushAttrib(GL_POINT_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMultMatrixf(glm::value_ptr(pMat));

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMultMatrixf(glm::value_ptr(mvMat));

			glPointSize(15.0f);
			glColor3f(1.0, 0.0, 1.0);
			glBegin(GL_POINTS);
			glVertex3fv(glm::value_ptr(worldPos));
			glEnd();
		glPopAttrib();
		glPopMatrix();*/


		/*glBindBuffer(GL_ARRAY_BUFFER, vboPoint);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), glm::value_ptr(worldPos), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glm::vec4 pointColor(1.0, 0.0, 1.0, 1.0);
		drawPointShader.Enable();
		drawPointShader.SetMVMat(mvMat);
		drawPointShader.SetPMat(pMat);
		drawPointShader.SetPointColor(pointColor);
		drawPointShader.SetPointSize(15.0);

		glDrawArrays(GL_POINTS, 0, 1);

		drawPointShader.Disable();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//hkoglPanelControl1->Invalidate();
	}*/
	//glUseProgram(0);
	/*glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixd((double *)xf);
	if (mesh != NULL)
		mesh->Render_SolidWireframe();
	glPopMatrix();*/
}
//·Æ¹««ö¤U¥h
private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Right ||
		e->Button == System::Windows::Forms::MouseButtons::Middle)
	{
		SelectionHandler(e->X, e->Y);
	}
	else if (e->Button == System::Windows::Forms::MouseButtons::Left )
	{
		meshWindowCam.mouseEvents(0, 1, e->X, e->Y);
	}
}
//·Æ¹«Âà°Ê
private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		meshWindowCam.mouseMoveEvent(e->X, e->Y);
		hkoglPanelControl1->Invalidate();
	}

	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		SelectionHandler(e->X, e->Y);
		hkoglPanelControl1->Invalidate();
	}
}
//·Æ¹«ºu½ü
private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Delta < 0)
	{
		meshWindowCam.mouseEvents(3, 3, e->X, e->Y);
		/*point center;
		Mouse_State = Mouse::WHEELDOWN;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);*/
		hkoglPanelControl1->Invalidate();
	}
	else
	{
		meshWindowCam.mouseEvents(4, 4, e->X, e->Y);
		/*point center;
		Mouse_State = Mouse::WHEELUP;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);*/
		hkoglPanelControl1->Invalidate();
	}
}
private: System::Void hkoglPanelControl1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	meshWindowCam.keyEvents(e->KeyChar);
	if (e->KeyChar == 'w' || e->KeyChar == 'W') {
		meshWindowCam.keyEvents(e->KeyChar);
		
		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if(e->KeyChar == 'a' || e->KeyChar == 'A') {
		meshWindowCam.keyEvents(e->KeyChar);

		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == 's' || e->KeyChar == 'S') {
		meshWindowCam.keyEvents(e->KeyChar);

		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == 'd' || e->KeyChar == 'D') {
		meshWindowCam.keyEvents(e->KeyChar);

		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == '-' ) {
		meshWindowCam.keyEvents(e->KeyChar);

		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == '+') {
		meshWindowCam.keyEvents(e->KeyChar);

		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
//¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×
	// 偉大的人
	else if (e->KeyChar == '1') {
		selectionMode = 1;
		//std::cout << "selectionMode=" << selectionMode << std::endl;
		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == '2') {
		selectionMode = 2;
		//std::cout << "selectionMode=" << selectionMode << std::endl;
		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == '3') {
		selectionMode = 3;
		//std::cout << "selectionMode=" << selectionMode << std::endl;
		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == '4') {

		model.render_mode = 0;
		
		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == '5') {

		model.render_mode = 1;

		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}
	else if (e->KeyChar == '6') {
		model.MeshFragment();
		model.MapToUV();

		hkoglPanelControl1->Invalidate();
		//e.Handled = true;
	}


//¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×
}
//«ö¤Uload model¿ï³æ
private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	openModelDialog->Filter = "Model(*.obj)|*obj";
	openModelDialog->Multiselect = false;
	openModelDialog->ShowDialog();
}
//¸ü¤JÀÉ®×
private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename;
	
	MarshalString(openModelDialog->FileName, filename);

	//if (mesh != NULL)
		//delete mesh;

	//mesh = new Tri_Mesh;
	if (model.Init(filename))
		{
			std::cout << "Load Model"<<filename << std::endl;
		}
		else
		{
			std::cout << "Load Model Failed" << std::endl;
		}
	hkoglPanelControl1->Invalidate();
}
//«ö¤Usave model¿ï³æ
private: System::Void saveModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	saveModelDialog->Filter = "Model(*.obj)|*obj";
	saveModelDialog->ShowDialog();
}
//¿é¥XÀÉ®×
private: System::Void saveModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename;
	MarshalString(saveModelDialog->FileName, filename);
	model.End(filename);
	//if (SaveFile(filename, mesh))
		//std::cout << filename << std::endl;
	hkoglPanelControl1->Invalidate();
}

//¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×
// 
private: System::Void SelectionHandler(unsigned int x, unsigned int y)
	{
	faceID = pickingTexture.ReadTexture(x, windowHeight - y - 1);
	//std::cout << "x=" << x << "  y=" << y << std::endl;
	//std::cout << "faceID="<<faceID << std::endl;
	//if (faceID != 0)
		//{
		//	currentFaceID = faceID;
		//}
	//std::cout << "selectionMode=" << selectionMode << std::endl;
		//if (selectionMode == ADD_FACE)
	    if (selectionMode == 1)
		{
			if (faceID != 0)
			{
				model.AddSelectedFace(faceID -1);
				//std::cout << "AddSelectedFace_finish" << std::endl;
			}
			hkoglPanelControl1->Invalidate();
		}
		else if (selectionMode == 2)
		{
			if (faceID != 0)
			{
				model.DeleteSelectedFace(faceID - 1);
				//std::cout << "DeleteSelectedFace_finish" << std::endl;
			}
			hkoglPanelControl1->Invalidate();
		}
		/*else if (selectionMode == 3)
		{
			currentMouseX = x;
			currentMouseY = y;
			updateFlag = true;
			hkoglPanelControl1->Invalidate();
		}*/
	}
//¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×¡×
};
}
