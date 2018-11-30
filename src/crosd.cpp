/*
 * crOsd.cpp
 *
 *  Created on: Nov 16, 2018
 *      Author: wzk
 */
# include "crosd.hpp"
# include "glosd.hpp"
# include <opencv2/opencv.hpp>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <iostream>
# include <osa.h>
//# include <typeinfo>
//# include <type_traits>
#include <GLBatchMini.h>
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

using namespace std;

namespace cr_osd
{
std::vector<GLOSDFactory *> vosdFactorys;
static std::vector<GLOSDTxt *> vtxts;
void put(wchar_t* s, const cv::Point& pos, const cv::Scalar& color, size_t n, const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	//unsigned int ID = va_arg(args, unsigned int);
	//vwprintf(__format, args);
	vswprintf(s, n, format, args);
	va_end(args);

	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		cv::Size2f scale((float)vosdFactorys[i]->m_viewport.width/vosdFactorys[0]->m_viewport.width, (float)vosdFactorys[i]->m_viewport.height/vosdFactorys[0]->m_viewport.height);
		GLOSDTxt * txt = new GLOSDTxt(vosdFactorys[i], scale);
		vtxts.push_back(txt);
		txt->txt(pos, s, color);
	}
}

void put(const wchar_t* s, const cv::Point& pos, const cv::Scalar& color)
{
	OSA_assert(s != NULL);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		cv::Size2f scale((float)vosdFactorys[i]->m_viewport.width/vosdFactorys[0]->m_viewport.width, (float)vosdFactorys[i]->m_viewport.height/vosdFactorys[0]->m_viewport.height);
		GLOSDTxt * txt = new GLOSDTxt(vosdFactorys[i], scale);
		vtxts.push_back(txt);
		txt->txt(pos, s, color);
	}
}

void put(const int* pValue, const wchar_t* format, const cv::Point& pos, const cv::Scalar& color)
{
	OSA_assert(pValue != NULL);
	OSA_assert(format != NULL);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		cv::Size2f scale((float)vosdFactorys[i]->m_viewport.width/vosdFactorys[0]->m_viewport.width, (float)vosdFactorys[i]->m_viewport.height/vosdFactorys[0]->m_viewport.height);
		GLOSDTxt * txt = new GLOSDTxt(vosdFactorys[i], scale);
		vtxts.push_back(txt);
		txt->txt(pos, pValue, format, color);
	}
}

void put(const unsigned int* pValue, const wchar_t* format, const cv::Point& pos, const cv::Scalar& color)
{
	OSA_assert(pValue != NULL);
	OSA_assert(format != NULL);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		cv::Size2f scale((float)vosdFactorys[i]->m_viewport.width/vosdFactorys[0]->m_viewport.width, (float)vosdFactorys[i]->m_viewport.height/vosdFactorys[0]->m_viewport.height);
		GLOSDTxt * txt = new GLOSDTxt(vosdFactorys[i], scale);
		vtxts.push_back(txt);
		txt->txt(pos, pValue, format, color);
	}
}

void put(const unsigned char* pValue, const wchar_t* format, const cv::Point& pos, const cv::Scalar& color)
{
	OSA_assert(pValue != NULL);
	OSA_assert(format != NULL);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		cv::Size2f scale((float)vosdFactorys[i]->m_viewport.width/vosdFactorys[0]->m_viewport.width, (float)vosdFactorys[i]->m_viewport.height/vosdFactorys[0]->m_viewport.height);
		GLOSDTxt * txt = new GLOSDTxt(vosdFactorys[i], scale);
		vtxts.push_back(txt);
		txt->txt(pos, pValue, format, color);
	}
}

void put(const float* pValue, const wchar_t* format, const cv::Point& pos, const cv::Scalar& color)
{
	OSA_assert(pValue != NULL);
	OSA_assert(format != NULL);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		cv::Size2f scale((float)vosdFactorys[i]->m_viewport.width/vosdFactorys[0]->m_viewport.width, (float)vosdFactorys[i]->m_viewport.height/vosdFactorys[0]->m_viewport.height);
		GLOSDTxt * txt = new GLOSDTxt(vosdFactorys[i], scale);
		vtxts.push_back(txt);
		txt->txt(pos, pValue, format, color);
	}
}

void put(const int *statValue, const int nStat, const cv::Point& pos, const cv::Scalar& color, ...)
{
	OSA_assert(statValue != NULL);
	va_list args;
	va_start(args, color);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		cv::Size2f scale((float)vosdFactorys[i]->m_viewport.width/vosdFactorys[0]->m_viewport.width, (float)vosdFactorys[i]->m_viewport.height/vosdFactorys[0]->m_viewport.height);
		GLOSDTxt * txt = new GLOSDTxt(vosdFactorys[i], scale);
		vtxts.push_back(txt);
		txt->txt(pos, color, statValue, nStat, args);
	}
	va_end(args);
}

void erase(const void *share)
{
	std::vector<GLOSDTxt*>::iterator it;
	for(it=vtxts.begin();it!=vtxts.end();){
		if((*it)->m_share == share){
			GLOSDTxt * txt = (*it);
			delete txt;
			vtxts.erase(it);
		}else{
			++it;
		}
	}
}

void clear(void)
{
	int nTxts = vtxts.size();
	for(int i=0; i<nTxts; i++)
		delete vtxts[i];
	vtxts.clear();
}

void set(const void *share, const cv::Scalar& color)
{
	std::vector<GLOSDTxt*>::iterator it;
	for(it=vtxts.begin();it!=vtxts.end(); it++){
		if((*it)->m_share == share){
			GLOSDTxt * txt = (*it);
			txt->setcolor(color);
		}
	}
}

void set(const void *share, const int yuv)
{
	int Y,U,V,R,G,B;
	Y = yuv & 0xff; U = (yuv>>8) & 0xff; V = (yuv>>16) & 0xff;
	R = Y+((360*(V-128))>>8);
	G = Y-((88*(U-128)+184*(V-128))>>8);
	B = Y+((455*(U-128))>>8);
	cv::Scalar color = cv::Scalar(R,G,B,255);
	set(share, color);
}

void set(const cv::Scalar& color)
{
	std::vector<GLOSDTxt*>::iterator it;
	for(it=vtxts.begin();it!=vtxts.end(); it++){
		GLOSDTxt * txt = (*it);
		txt->setcolor(color);
	}
}

void set(const int yuv)
{
	int Y,U,V,R,G,B;
	Y = yuv & 0xff; U = (yuv>>8) & 0xff; V = (yuv>>16) & 0xff;
	R = Y+((360*(V-128))>>8);
	G = Y-((88*(U-128)+184*(V-128))>>8);
	B = Y+((455*(U-128))>>8);
	cv::Scalar color = cv::Scalar(R,G,B,255);
	set(color);
}

void set(const void *share, const cv::Point& pos)
{
	std::vector<GLOSDTxt*>::iterator it;
	for(it=vtxts.begin();it!=vtxts.end(); it++){
		if((*it)->m_share == share){
			GLOSDTxt * txt = (*it);
			txt->setpos(pos);
		}
	}
}

/******************************************************
 *
 *
 */

/*class Pattern
{
	std::vector<void *> vbases;
protected:
	Pattern(int nVert, GLenum primitive = GL_LINES);
	virtual ~Pattern(void);
	virtual int update(const std::vector<cv::Point>& vpts, const cv::Scalar& color = cv::Scalar::all(255), int thickness = 1);
	virtual void set(const cv::Scalar& color);
	virtual void set(const int yuv);
};*/

Pattern::Pattern(int nVert, GLenum primitive)
{
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		GLOSDUNITBase *base = new GLOSDUNITBase(vosdFactorys[i], nVert, primitive);
		vbases.push_back(base);
	}
}
Pattern::~Pattern(void)
{
	std::vector<void *>::iterator it;
	for(it=vbases.begin();it!=vbases.end(); it++){
		GLOSDUNITBase *base = (GLOSDUNITBase *)(*it);
		delete base;
	}
	vbases.clear();
}
int Pattern::update(const std::vector<cv::Point>& vpts, const cv::Scalar& color, int thickness)
{
	std::vector<void *>::iterator it;
	for(it=vbases.begin();it!=vbases.end(); it++){
		GLOSDUNITBase *base = (GLOSDUNITBase *)(*it);
		if(vpts.size() != base->m_nVert)
			return -1;
		cv::Size2f scale((float)base->m_viewport.width/((GLOSDUNITBase *)vbases[0])->m_viewport.width, (float)base->m_viewport.height/((GLOSDUNITBase *)vbases[0])->m_viewport.height);
		cv::Point2f pos;
		float *vVertex, *vColor;
		cv::Scalar norColor(color.val[0]*0.003921569, color.val[1]*0.003921569, color.val[2]*0.003921569, color.val[3]*0.003921569);
		OSA_mutexLock(base->m_mutexlock);
		vVertex = base->vVertexPos;
		vColor = base->vColorPos;
		for(int i=0; i<base->m_nVert; i++){
			base->m_vtps[i] = cv::Point(vpts[i].x*scale.width, vpts[i].y*scale.height);
			pos = base->normalized(base->m_vtps[i]);
			vVertex[0] = pos.x; vVertex[1] = pos.y;
			vVertex += 3;
			vColor[0] = norColor.val[0]; vColor[1] = norColor.val[1];
			vColor[2] = norColor.val[2]; vColor[3] = norColor.val[3];
			vColor += 4;
		}
		base->m_bUpdate = true;
		if(base->m_thickness != thickness)
			base->m_factory->SetThickness(base, thickness);
		OSA_mutexUnlock(base->m_mutexlock);
	}
	return 0;
}

void Pattern::set(const cv::Scalar& color)
{
	std::vector<void *>::iterator it;
	float *vColor;
	cv::Scalar norColor(color.val[0]*0.003921569, color.val[1]*0.003921569, color.val[2]*0.003921569, color.val[3]*0.003921569);
	for(it=vbases.begin();it!=vbases.end(); it++){
		GLOSDUNITBase *base = (GLOSDUNITBase *)(*it);
		OSA_mutexLock(base->m_mutexlock);
		vColor = base->vColorPos;
		for(int i=0; i<base->m_nVert; i++){
			vColor[0] = norColor.val[0]; vColor[1] = norColor.val[1];
			vColor[2] = norColor.val[2]; vColor[3] = norColor.val[3];
			vColor += 4;
		}
		OSA_mutexUnlock(base->m_mutexlock);
	}
}
void Pattern::set(const int yuv)
{
	int Y,U,V,R,G,B;
	Y = yuv & 0xff; U = (yuv>>8) & 0xff; V = (yuv>>16) & 0xff;
	R = Y+((360*(V-128))>>8);
	G = Y-((88*(U-128)+184*(V-128))>>8);
	B = Y+((455*(U-128))>>8);
	cv::Scalar color = cv::Scalar(R,G,B,255);
	set(color);
}


/************************************************************
 *
 *
 *
 */

extern GLShaderManagerMini		glShaderManager;
//using namespace cr_osd;
class glPattern : public IPattern
{
public:
	glPattern(const cv::Mat& mat, const cv::Rect& roi):m_array(NULL),m_mat(mat),m_roi(roi),m_width(0),m_height(0){};
	glPattern(const std::vector<float>* vArray, const cv::Rect& roi):m_array(vArray),m_roi(roi),m_width(0),m_height(0){};
	virtual ~glPattern(void){};

	const std::vector<float>* m_array;
	cv::Mat m_mat;
	cv::Rect m_roi;
	int m_width, m_height;

	GLMatrixStack modelViewMatrix;
	GLMatrixStack projectionMatrix;
	GLFrame       cameraFrame;
	GLGeometryTransform	transformPipeline;
	GLBatchMini   gridBatch;
	GLBatchMini   axisBatch;
	GLBatchMini   dataBatch;
	void ChangeSize(void)
	{
		// Create the projection matrix, and load it on the projection matrix stack
		GLFrustum viewFrustum;
		float perspective_fFov = 45.0f;
		float perspective_fAspect = (float)m_mat.cols/(float)m_mat.rows;
		float perspective_fNear = 1.0f;
		float perspective_fFar = 10000.0f;
		viewFrustum.SetPerspective(perspective_fFov, perspective_fAspect, perspective_fNear, perspective_fFar);
		//viewFrustum.SetOrthographic(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
		projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
		// Set the transformation pipeline to use the two matrix stacks
		transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
	}

	void drawMat(void)
	{
		if(m_mat.cols<=0 || m_mat.rows<=0)
			return ;

		if(m_width!=m_mat.cols || m_height!=m_mat.rows){
			m_width=m_mat.cols; m_height=m_mat.rows;
			ChangeSize();

		    dataBatch.Reset();
			gridBatch.Begin(GL_LINES, (m_width+m_height)*20);
		    GLfloat cellx = 2.0f/m_width;
		    GLfloat cellz = 2.0f/m_height;
		    for(GLfloat x = -1.0f; x < 1.0; x+= cellx) {
		    	gridBatch.Vertex3f(x, -1.f, 1.0f);
		    	gridBatch.Vertex3f(x, -1.f, -1.0f);
		    }
		    for(GLfloat z = -1.0f; z < 1.0; z+=cellz) {
		    	gridBatch.Vertex3f(1.0f, -1.f, z);
		    	gridBatch.Vertex3f(-1.0f, -1.f, z);
		    }
		    gridBatch.End();

		    dataBatch.Reset();
		    axisBatch.Begin(GL_LINES, 6);
		    axisBatch.Vertex3f(-1, -1.f, -1.0f);
		    axisBatch.Vertex3f(+1.2, -1.f, -1.0f);
		    axisBatch.Vertex3f(-1, -1.f, -1.0f);
		    axisBatch.Vertex3f(-1, 1.2f, -1.0f);
		    axisBatch.Vertex3f(-1, -1.f, -1.0f);
		    axisBatch.Vertex3f(-1, -1.f, 1.2f);
		    axisBatch.End();

		    //cameraFrame.MoveUp(1.0f);
		    cameraFrame.RotateWorld(-30.f*M3D_PI_DIV_180, 1.0f, 0.0f, 0.0f);
		    cameraFrame.RotateWorld(45.f*M3D_PI_DIV_180, 0.0f, 1.0f, 0.0f);
		    cameraFrame.MoveForward(-5.f);
		}

	    GLfloat cellx = 2.0f/m_width;
	    GLfloat cellz = 2.0f/m_height;
	    dataBatch.Reset();
	    dataBatch.Begin(GL_LINE_STRIP, (m_width*m_height));
	    GLfloat z = -1.0f;
	    GLfloat x = -1.0f;
	    for(int i=0; i<m_width*m_height; i++){
			dataBatch.Vertex3f(x, m_mat.at<float>(i/m_width, i%m_width), z);
			x+= cellx;
			if(fabs(x)>1.0f) {
				cellx *= -1.0f;
				x+= cellx;
				z += cellz;
			}
	    }
	    dataBatch.End();

	    M3DMatrix44f mCamera;
	    cameraFrame.GetCameraMatrix(mCamera);
	    modelViewMatrix.PushMatrix(mCamera);

	    GLfloat color[4] = { 0.0f, 0.6f, 0.0f, 1.0f};
	    glViewport(m_roi.x, m_roi.y, m_roi.width, m_roi.height);
	    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	    M3DMatrix44f project;
	    memcpy(project, transformPipeline.GetModelViewProjectionMatrix(), sizeof(M3DMatrix44f));
	    //memcpy(project, mCamera, sizeof(M3DMatrix44f));

	    /*
		// Draw the grid
	    color[0] = 0; color[1] = 0.6; color[2] = 0;
	    glShaderManager.UseStockShader(GLT_SHADER_FLAT,project,color);
	    glLineWidth(1.0);
	    gridBatch.Draw();
	    glLineWidth(1.0);
	    */

		// Draw the axis
	    color[0] = 1.0; color[1] = 1.0; color[2] = 1.0;
	    glShaderManager.UseStockShader(GLT_SHADER_FLAT,project,color);
	    glLineWidth(2.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    axisBatch.Draw();
	    glDisable(GL_BLEND);
	    glLineWidth(1.0);

		// Draw the data
	    color[0] = 0; color[1] = 1; color[2] = 0.0; color[3] = 0.5;
	    glShaderManager.UseStockShader(GLT_SHADER_FLAT,project,color);
	    glLineWidth(1.0);
		glEnable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    dataBatch.Draw();
	    glDisable(GL_BLEND);
	    //glDisable(GL_DEPTH_TEST);
	    glLineWidth(1.0);

	    modelViewMatrix.PopMatrix();
	}

	void drawArray(void)
	{
	    glViewport(m_roi.x, m_roi.y, m_roi.width, m_roi.height);
		m_width = m_array->size();
		//OSA_printf("%d", m_width);
		m_height = 1;
		GLfloat cellx = 2.0f/m_width;
		dataBatch.Reset();
		dataBatch.Begin(GL_LINE_STRIP, m_width);
		GLfloat z = 0.0f;
		GLfloat x = -1.0f;
		for(int i=0; i<m_width; i++){
			dataBatch.Vertex3f(x, (*m_array)[i], z);
			x+= cellx;
		}
		dataBatch.End();
		// Draw the data
		M3DVector4f color = { 1.0f, 1.0f, 0.0f, 1.0f};
	    glShaderManager.UseStockShader(GLT_SHADER_IDENTITY,color);
	    glLineWidth(1.0);
		glEnable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    dataBatch.Draw();
	    glDisable(GL_BLEND);
	    //glDisable(GL_DEPTH_TEST);
	    glLineWidth(1.0);
	}

	virtual void draw(void)
	{
		if(m_array != NULL && m_array->size()>0)
			drawArray();
		else if(m_mat.cols>0 && m_mat.rows>0)
			drawMat();
	}
};

IPattern* IPattern::Create(const cv::Mat& mat, const cv::Rect& rcVeiw)
{
	IPattern* pattern = new glPattern(mat, rcVeiw);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		vosdFactorys[i]->Add(pattern);
	}
	return pattern;
}
IPattern* IPattern::Create(const std::vector<float>* vArray, const cv::Rect& rcVeiw)
{
	IPattern* pattern = new glPattern(vArray, rcVeiw);
	int nFacts = vosdFactorys.size();
	for(int i=0; i<nFacts; i++){
		vosdFactorys[i]->Add(pattern);
	}
	return pattern;
}
void IPattern::Destroy(IPattern *pattern)
{
	glPattern *glpattern = (glPattern*)pattern;
	delete glpattern;
}

};//namespace cr_osd

