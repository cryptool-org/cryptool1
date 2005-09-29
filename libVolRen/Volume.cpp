// Volume.cpp : implementation file
//

#include "Volume.h"
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include "GL/gl.h"

#ifdef USE_NVIDIA_EXTENSIONS
#define GLH_EXT_SINGLE_FILE
#include "glh_extensions.h"
#endif


#define SET_VECTOR(a,b,c,d) {a[0]=b;a[1]=c;a[2]=d;}

/////////////////////////////////////////////////////////////////////////////
// Volume


CVolume::CVolume(int resolution[3], double voxelSize[3], unsigned char *pBuffer)
{
	assert(m_pVoxelBuffer != NULL);
	
	m_bRenderBBox = true;
	m_bRenderVolume = true;
	m_bTexInit = false;
	m_pVoxelBuffer = pBuffer;
	m_pTransferFunction = NULL;
	m_pHistogram = NULL;
	m_dSampling = 1.0;
	
	for(int i = 0; i < 3; i++) {
		m_nResolution[i] = resolution[i];
		m_dVoxelSize[i]  = voxelSize[i];
		m_dCubeDimensions[i] = m_dVoxelSize[i] * double(m_nResolution[i]);
		m_dCubeDimensions_2[i] = m_dCubeDimensions[i]/2.0;
		m_dTexCorrect[i] = 1.0;
		m_pTexNames[i] = NULL;
	}

#ifdef COMPUTE_HISTOGRAM
	m_pHistogram = new float[256];
	memset(m_pHistogram,0,256*sizeof(float));
	int nNumVoxels = resolution[0] * resolution[1] * resolution[2];
	for(int h = 0; h < nNumVoxels; h++) {
		m_pHistogram[pBuffer[h]]++;
	}
#endif //COMPUTE_HISTOGRAM


#ifdef USE_NVIDIA_EXTENSIONS
	m_bExtInit = false;

	
	m_pTransferFunction = new unsigned char[4*256];
	int nTFIndex = 0;
	for(int j = 0; j < 256; j++) {
		m_pTransferFunction[nTFIndex++] = j;
		m_pTransferFunction[nTFIndex++] = j;
		m_pTransferFunction[nTFIndex++] = j;
		m_pTransferFunction[nTFIndex++] = j;
	}
#if defined (USE_DEPENDENT_TEXTURE) || (DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE)
	m_nDepTexName = 0;
	m_pDepTexBuffer = new unsigned char[2*4*256];
	memcpy(m_pDepTexBuffer,             m_pTransferFunction, 4*256*sizeof(unsigned char));
	memcpy((m_pDepTexBuffer + (256*4)), m_pTransferFunction, 4*256*sizeof(unsigned char));
#endif // USE_DEPENDENT_TEXTURE

#endif // USE_NVIDIA_EXTENSIONS
		
}

CVolume::~CVolume()
{
	deleteTextures();
#ifdef USE_NVIDIA_EXTENSIONS
	delete [] m_pTransferFunction;
#ifdef USE_DEPENDENT_TEXTURE
	delete [] m_pDepTexBuffer;
#endif
#endif
}

bool CVolume::render() 
{
#ifdef USE_NVIDIA_EXTENSIONS
	if (false == m_bExtInit) {
#ifdef USE_PALETTED_TEXTURE
		if (glh_init_extensions(" GL_ARB_multitexture GL_NV_register_combiners GL_EXT_paletted_texture GL_EXT_shared_texture_palette ")) {
#else
#ifdef DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE
			
		if (glh_init_extensions("GL_ARB_multitexture GL_NV_texture_rectangle GL_NV_vertex_program WGL_ARB_pbuffer WGL_ARB_render_texture WGL_ARB_pixel_format")) {
		//if (glh_init_extensions(" GL_ARB_multitexture GL_NV_vertex_program GL_NV_register_combiners")) {
#else
		if (glh_init_extensions(" GL_ARB_multitexture GL_NV_texture_shader GL_NV_register_combiners")) {
#endif
#endif
			m_bExtInit = true;
		} else {
			return false;
		}
	}
#endif
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LINE_BIT);
	
	if (m_bRenderBBox) renderBoundingBox();
	if (m_bRenderVolume) renderVolume();
	
	glPopAttrib();
	
	return true;
}

bool CVolume::renderVolume() {
	
	int i;
	
	glDisable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	
	
	// are the texture already created and initialized?
	if (m_bTexInit == false) {
		deleteTextures();
		
		if (createTextures()) {
			m_bTexInit = true;
		} else {
			return false;
		}
	}
	
	// get the current viewing matrix
	GLdouble pMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, pMatrix);
	
	// the viewing direction is calculated by multipling
	// the negative Z-vector (0, 0, -1) with the rotation
	// from the viewing matrix!
	double vecView[3];
	double vecViewAbs[3];
	
	const int nMatIndices[3] = {2,6,10};
	
	for(i = 0; i < 3; i++) {
		vecView[i] = -pMatrix[nMatIndices[i]];
		vecViewAbs[i] = (vecView[i] > 0)? vecView[i] : -vecView[i];
	}
	
	unsigned short nSliceIndex;
	
	// find the vector component of the viewing vector
	// with the larges magnitude
	if ((vecViewAbs[0] > vecViewAbs[1]) && (vecViewAbs[0] > vecViewAbs[2])) {
		nSliceIndex = 0;
	} else if (vecViewAbs[1] > vecViewAbs[2]) {
		nSliceIndex = 1;
	} else {
		nSliceIndex = 2;
	}
	
	double dIncrement;
	
	int nNumSlices;
	
	double backPlane[4][3];
	double dTexU[4], dTexV[4];
	GLuint *pTextureStack;
	double dCurTex, dCurTexInc;
	
	pTextureStack = m_pTexNames[nSliceIndex];
	
#ifdef DRAW_INTERMEDIATE_SLICES
	// slice distance is half the length of the voxel diagonal!
	dIncrement = 0.5 * vecViewAbs[nSliceIndex] * sqrt(
		m_dVoxelSize[0] * m_dVoxelSize[0] + 
		m_dVoxelSize[1] * m_dVoxelSize[1] + 
		m_dVoxelSize[2] * m_dVoxelSize[2]) / m_dSampling;
	
	//dIncrement = 6.0;
	nNumSlices = 1+ int( double(m_nResolution[nSliceIndex]) * m_dVoxelSize[nSliceIndex] /dIncrement);
	dCurTexInc = double(m_nResolution[nSliceIndex])/double(nNumSlices);
#else
	nNumSlices = m_nResolution[nSliceIndex];
	dCurTexInc = 1.0;
#endif
	
#ifdef USE_PALETTED_TEXTURE
	glEnable(GL_SHARED_TEXTURE_PALETTE_EXT);
#endif

	switch (nSliceIndex) {
		
	case 0:
		if (vecView[0] < 0.0) {
#ifndef DRAW_INTERMEDIATE_SLICES
			dIncrement =   m_dVoxelSize[0];
#endif
			SET_VECTOR(backPlane[0], -m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[1], -m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[2], -m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[3], -m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			dCurTex    = 0.0;
		} else {
#ifndef DRAW_INTERMEDIATE_SLICES
			dIncrement = - m_dVoxelSize[0];
#else 
			dIncrement = - dIncrement;
#endif
			SET_VECTOR(backPlane[0],  m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[1],  m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[2],  m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[3],  m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			dCurTex    = double(m_nResolution[0]-1);
			dCurTexInc = -dCurTexInc;
		} 
		dTexU[0] = 0.0;              dTexV[0] = 0.0;
		dTexU[1] = m_dTexCorrect[1]; dTexV[1] = 0.0;
		dTexU[2] = m_dTexCorrect[1]; dTexV[2] = m_dTexCorrect[2];
		dTexU[3] = 0.0;              dTexV[3] = m_dTexCorrect[2];
		break;
	case 1:
		if (vecView[1] < 0.0) {
#ifndef DRAW_INTERMEDIATE_SLICES
			dIncrement =   m_dVoxelSize[1];
#endif
			SET_VECTOR(backPlane[0], -m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[1],  m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[2],  m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[3], -m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			dCurTex    = 0.0;
		} else {
#ifndef DRAW_INTERMEDIATE_SLICES
			dIncrement = - m_dVoxelSize[1];
#else 
			dIncrement = - dIncrement;
#endif
			SET_VECTOR(backPlane[0], -m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[1],  m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[2],  m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[3], -m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			dCurTex    = double(m_nResolution[1]-1);
			dCurTexInc = -dCurTexInc;
		} 
		dTexU[0] = 0.0;            dTexV[0] = 0.0;
		dTexU[1] = m_dTexCorrect[0]; dTexV[1] = 0.0;
		dTexU[2] = m_dTexCorrect[0]; dTexV[2] = m_dTexCorrect[2];
		dTexU[3] = 0.0;            dTexV[3] = m_dTexCorrect[2];
		break;
	case 2:
		if (vecView[2] < 0.0) {
#ifndef DRAW_INTERMEDIATE_SLICES
			dIncrement =   m_dVoxelSize[2];
#endif
			SET_VECTOR(backPlane[0], -m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[1],  m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[2],  m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[3], -m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
			dCurTex    = 0.0;
		} else {
#ifndef DRAW_INTERMEDIATE_SLICES
			dIncrement = - m_dVoxelSize[2];
#else 
			dIncrement = - dIncrement;
#endif
			SET_VECTOR(backPlane[0], -m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[1],  m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[2],  m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			SET_VECTOR(backPlane[3], -m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
			dCurTex    = double(m_nResolution[2]-1);
			dCurTexInc = -dCurTexInc;
		} 
		dTexU[0] = 0.0;            dTexV[0] = 0.0;
		dTexU[1] = m_dTexCorrect[0]; dTexV[1] = 0.0;
		dTexU[2] = m_dTexCorrect[0]; dTexV[2] = m_dTexCorrect[1];
		dTexU[3] = 0.0;            dTexV[3] = m_dTexCorrect[1];
		break;
	}
	
	glLineWidth(1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
#ifdef DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE
	//                           0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111111111
	//                           0000000001111111111222222222233333333334444444444555555555566666666667777777777888888888899999999990000000000111111111122222222223333333333
	//                           1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
	const char *psFragmenProg = "!!FP1.0 TEX R1, f[TEX0], TEX0, 2D; TEX R2, f[TEX1], TEX1, 2D; LRP R3, f[COL0].w, R1, R2; TEX R4, R3, TEX2, 2D; MOV o[COLR], R4; END";
	
	int len = 131;
	
	glGetLastError();
	//glDisable(GL_NV_register_combiners);
	glGetLastError();
	glEnable(GL_FRAGMENT_PROGRAM_NV);
	glGetLastError();
	glLoadProgramNV(GL_FRAGMENT_PROGRAM_NV,1,len,(const unsigned char *)(psFragmenProg));
	glGetLastError();
	const unsigned char *errorstring = glGetString(GL_PROGRAM_ERROR_STRING_NV);
	glBindProgramNV(GL_FRAGMENT_PROGRAM_NV,1);
	glGetLastError();
#else 
#ifdef DRAW_INTERMEDIATE_SLICES
	glEnable(GL_NV_register_combiners);
	initRegisterCombiners();
#endif 
#endif

#ifdef USE_DEPENDENT_TEXTURE
	//--------------------------------------------------
	// Initialization Step 1: Texture Setup
	//--------------------------------------------------
	// first texture stage
	glActiveTextureARB(GL_TEXTURE0_ARB);
	// disable 2D textures, enable 3D texture	
	glEnable(GL_TEXTURE_2D);
	// enable the texture shader
	glEnable(GL_TEXTURE_SHADER_NV);
    glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_TEXTURE_2D);
			
    // second texture stage = dependent texture (Alpha and Red component)
	glActiveTextureARB(GL_TEXTURE1_ARB);
	// enable 2D texture
	glEnable(GL_TEXTURE_2D);
	// enable the texture shader
	glEnable(GL_TEXTURE_SHADER_NV);
	// bind the texture that contains the color table
	glBindTexture(GL_TEXTURE_2D, m_nDepTexName); 
	// enable linear interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	// setup for dependent texture lookup 
	glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_DEPENDENT_AR_TEXTURE_2D_NV );
	glTexEnvi(GL_TEXTURE_SHADER_NV, GL_PREVIOUS_TEXTURE_INPUT_NV, GL_TEXTURE0_ARB);
			
	// disable the remaining texture units
	glActiveTextureARB(GL_TEXTURE2_ARB);
    glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NOOP);
	glActiveTextureARB(GL_TEXTURE3_ARB);
    glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NOOP);
		
	// activate combiners
	glEnable(GL_REGISTER_COMBINERS_NV);
			
	// we only need the final combiner
	glCombinerParameteriNV(GL_NUM_GENERAL_COMBINERS_NV, 0);			
	//                     variable          input         mapping		          comp
	glFinalCombinerInputNV(GL_VARIABLE_A_NV, GL_ZERO,         GL_UNSIGNED_IDENTITY_NV, GL_RGB  );
	glFinalCombinerInputNV(GL_VARIABLE_B_NV, GL_ZERO,         GL_UNSIGNED_IDENTITY_NV, GL_RGB  );
	glFinalCombinerInputNV(GL_VARIABLE_C_NV, GL_ZERO,         GL_UNSIGNED_IDENTITY_NV, GL_RGB  );
	glFinalCombinerInputNV(GL_VARIABLE_D_NV, GL_TEXTURE1_ARB, GL_UNSIGNED_IDENTITY_NV, GL_RGB  );
	glFinalCombinerInputNV(GL_VARIABLE_G_NV, GL_TEXTURE1_ARB, GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);
			
	glActiveTextureARB(GL_TEXTURE0_ARB);
#endif

	for(i = 0; i < nNumSlices; i++) {
		
		glEnable(GL_TEXTURE_2D);
		assert(dCurTex <= m_nResolution[nSliceIndex]);
		
#ifdef DRAW_INTERMEDIATE_SLICES
		float cc0[4];
	    cc0[3] = float(dCurTex) - float(int(dCurTex)); 

#ifdef DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,m_nDepTexName);
		glColor4fv(cc0);
#else 
		glCombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, cc0);
#endif 
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,pTextureStack[int(dCurTex)]);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,pTextureStack[int(dCurTex)+1]);

#else
		glBindTexture(GL_TEXTURE_2D,pTextureStack[int(dCurTex)]);
#endif 
		
		//glColor4d(1.0,1.0,1.0,0.5);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  
		
		glBegin(GL_TRIANGLE_FAN);
		{	
			for(int v = 0; v < 4; v++) {
#ifdef DRAW_INTERMEDIATE_SLICES
				glMultiTexCoord2dARB(GL_TEXTURE0_ARB, dTexU[v], dTexV[v]);
				glMultiTexCoord2dARB(GL_TEXTURE1_ARB, dTexU[v], dTexV[v]);


#else
#ifdef USE_DEPENDENT_TEXTURE
				glMultiTexCoord2dARB(GL_TEXTURE0_ARB, dTexU[v], dTexV[v]);
#else  // USE_DEPENDENT_TEXTURE
				glTexCoord2d(dTexU[v], dTexV[v]);
#endif // USE_DEPENDENT_TEXTURE
#endif // DRAW_INTERMEDIATE_SLICES
				glVertex3d(backPlane[v][0], backPlane[v][1], backPlane[v][2]);
			}
		}
		glEnd();
		backPlane[0][nSliceIndex] += dIncrement;
		backPlane[1][nSliceIndex] += dIncrement;
		backPlane[2][nSliceIndex] += dIncrement;
		backPlane[3][nSliceIndex] += dIncrement;
		dCurTex += dCurTexInc;
	}
	
	return true;
}

bool CVolume::renderBoundingBox() {
	
	glDisable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	glLineWidth(3.0);
	
	// draw the bounding box 
	glBegin(GL_LINE_LOOP);
	{	
		glVertex3d(m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		glVertex3d(m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		glVertex3d(m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
		glVertex3d(m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
	}
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	{	
		glVertex3d(-m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		glVertex3d(-m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		glVertex3d(-m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
		glVertex3d(-m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
	}
	glEnd();
	
	glBegin(GL_LINES);
	{	
		glVertex3d(-m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		glVertex3d( m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		
		glVertex3d(-m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		glVertex3d( m_dCubeDimensions_2[0], m_dCubeDimensions_2[1],  m_dCubeDimensions_2[2]);
		
		glVertex3d(-m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
		glVertex3d( m_dCubeDimensions_2[0],-m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
		
		glVertex3d(-m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
		glVertex3d( m_dCubeDimensions_2[0], m_dCubeDimensions_2[1], -m_dCubeDimensions_2[2]);
	}
	glEnd();
	
	return true;
	
} // end of CVolume::renderBoundingBox()

bool CVolume::createTextures()
{
#ifdef USE_NVIDIA_EXTENSIONS

#ifdef USE_PALETTED_TEXTURE
	GLenum nInternalFormat = GL_COLOR_INDEX8_EXT; 
	GLenum nExternalFormat = GL_COLOR_INDEX; 
#else //USE_PALETTED_TEXTURE
	// use dependent texture
	GLenum nInternalFormat = GL_INTENSITY;
	GLenum nExternalFormat = GL_LUMINANCE;
#endif //USE_PALETTED_TEXTURE

#else // USE_NVIDIA_EXTENSIONS
	GLenum nInternalFormat = GL_INTENSITY;
	GLenum nExternalFormat = GL_LUMINANCE;
#endif // USE_NVIDIA_EXTENSIONS


	glPushAttrib(GL_ENABLE_BIT   | 
	       GL_COLOR_BUFFER_BIT   |
		   GL_STENCIL_BUFFER_BIT |
		   GL_DEPTH_BUFFER_BIT   | 
		   GL_POLYGON_BIT        | 
		   GL_TEXTURE_BIT);
	
#if defined (USE_NVIDIA_EXTENSIONS) && (USE_PALETTED_TEXTURE)
	glEnable(GL_SHARED_TEXTURE_PALETTE_EXT);
#endif

	glPixelStorei(GL_UNPACK_ROW_LENGTH,  0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS,   0);
	glPixelStorei(GL_UNPACK_ALIGNMENT,   4);
	glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
	
	int x,y,z;
	
	int nPower             = (unsigned int) ceil( log((double)m_nResolution[0]) / log(2.0)); 
	unsigned int nFillResX = (unsigned int) pow(2.0, nPower);
	
	nPower                 = (unsigned int) ceil( log((double)m_nResolution[1]) / log(2.0)); 
	unsigned int nFillResY = (unsigned int) pow(2.0, nPower);
	
	nPower                 = (unsigned int) ceil( log((double)m_nResolution[2]) / log(2.0)); 
	unsigned int nFillResZ = (unsigned int) pow(2.0, nPower);
	
	glEnable(GL_TEXTURE_2D);
	GLuint *pZTexNames = new GLuint[m_nResolution[2]]; 
	if (NULL == pZTexNames) return false;
	glGenTextures(  m_nResolution[2], pZTexNames);
	
	GLuint *pYTexNames = new GLuint[m_nResolution[1]]; 
	if (NULL == pYTexNames) return false;
	glGenTextures(  m_nResolution[1], pYTexNames); 
	
	GLuint *pXTexNames = new GLuint[m_nResolution[0]]; 
	if (NULL == pXTexNames) return false;
	glGenTextures(  m_nResolution[0], pXTexNames); 
	
	m_pTexNames[0] = pXTexNames;
	m_pTexNames[1] = pYTexNames;
	m_pTexNames[2] = pZTexNames;
	
	unsigned char *pZBuffer = new unsigned char [ nFillResX * nFillResY];  
	memset(pZBuffer,0, nFillResX * nFillResY  * sizeof(unsigned char)); 
	
	for(z = 0; z < m_nResolution[2]; z++) { 
		// extract z slice; 
		for(y = 0; y <  m_nResolution[1]; y++) { 
			for(x = 0; x <  m_nResolution[0]; x++) { 
				pZBuffer[y * nFillResX + x] = m_pVoxelBuffer[(z *  m_nResolution[1] + y) *  m_nResolution[0] + x]; 
			} 
		} 
		glBindTexture(GL_TEXTURE_2D, m_pTexNames[2][z]); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
		glTexImage2D(GL_TEXTURE_2D,        // target  
			0,                       // level  
			nInternalFormat,         // internal format 
			nFillResX,               // width  
			nFillResY,               // height  
			0,                       // border  
			nExternalFormat,         // format  
			GL_UNSIGNED_BYTE,        // type  
			pZBuffer); 
		
	} 
	delete [] pZBuffer; 
	
	unsigned char *pYBuffer = new unsigned char [ nFillResX * nFillResZ];  
	memset(pYBuffer,0, nFillResX * nFillResZ * sizeof(unsigned char)); 
	
	for(y = 0; y <  m_nResolution[1]; y++) { 
		
		// extract y slice; 
		for(z = 0; z <  m_nResolution[2]; z++) { 
			for(x = 0; x <  m_nResolution[0]; x++) { 
				pYBuffer[(z * nFillResX + x) ] = m_pVoxelBuffer[(z *  m_nResolution[1] + y) *  m_nResolution[0] + x]; 
			} 
		} 
		glBindTexture(GL_TEXTURE_2D, m_pTexNames[1][y]); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glTexImage2D(GL_TEXTURE_2D,        // target  
			0,                    // level  
			nInternalFormat,      // internal format 
			nFillResX,            // width  
			nFillResZ,            // height  
			0,                    // border  
			nExternalFormat,      // format  
			GL_UNSIGNED_BYTE,            // type  
			pYBuffer); 
	} 
	delete [] pYBuffer; 
	
	unsigned char *pXBuffer = new unsigned char [ nFillResY *   nFillResZ];  
	memset(pXBuffer,0, nFillResY *   nFillResZ * sizeof(unsigned char));  
	
	for(x = 0; x <   m_nResolution[0]; x++) { 
		// extract y slice; 
		for(z = 0; z <  m_nResolution[2]; z++) { 
			for(y = 0; y <  m_nResolution[1]; y++) { 
				pXBuffer[z *   nFillResY + y] = m_pVoxelBuffer[(z *m_nResolution[1] + y) * m_nResolution[0] + x];
			} 
		} 
		glBindTexture(GL_TEXTURE_2D, m_pTexNames[0][x]); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
		glTexImage2D(GL_TEXTURE_2D,        // target  
			0,                    // level  
			nInternalFormat,         // internal format 
			nFillResY,                 // width  
			nFillResZ,                 // height  
			0,                    // border  
			nExternalFormat,         // format  
			GL_UNSIGNED_BYTE,          // type  
			pXBuffer); 
	} 
	delete [] pXBuffer; 
	
	m_dTexCorrect[0] = double(m_nResolution[0]) / double(nFillResX); 
	m_dTexCorrect[1] = double(m_nResolution[1]) / double(nFillResY); 
	m_dTexCorrect[2] = double(m_nResolution[2]) / double(nFillResZ); 
	
#ifdef USE_NVIDIA_EXTENSIONS
	
#ifdef USE_PALETTED_TEXTURE
	applyTransferFunction();
#endif

#if defined USE_DEPENDENT_TEXTURE || DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE

	// DEFINE THE DEPENDENT TEXTURE
	glGenTextures(1,&m_nDepTexName);
	//if (0 == m_nDepTexName) return false;

	glBindTexture(GL_TEXTURE_2D, m_nDepTexName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

	glTexImage2D(GL_TEXTURE_2D, // target  
			0,                  // level  
			GL_RGBA,            // internal format 
			256,                // width  
			2,                  // height  
			0,                  // border  
			GL_RGBA,            // format  
			GL_UNSIGNED_BYTE,   // type  
			m_pDepTexBuffer); 
#endif
	
#endif
	
	glPopAttrib();
	
	return true;
}// end of CVolume::initTextures()

void CVolume::deleteTextures() {
	
	for(int i = 0; i < 3; i++) {
		if (NULL != m_pTexNames[i]) {
			glDeleteTextures(m_nResolution[i],m_pTexNames[i]);
			delete [] m_pTexNames[i];
			m_pTexNames[i] = NULL;
		}
	}
	
}

void CVolume::applyTransferFunction() {

#ifdef USE_NVIDIA_EXTENSIONS 
#ifdef USE_PALETTED_TEXTURE
	// paletted texture lookup
	glColorTableEXT(  
		GL_SHARED_TEXTURE_PALETTE_EXT, // GLenum target, 
		GL_RGBA,                       // GLenum internalformat, 
		256,						   // GLsizei width, 
		GL_RGBA,                       // GLenum format, 
		GL_UNSIGNED_BYTE,              // GLenum type, 
		m_pTransferFunction);          // const GLvoid *table  
#endif

#if defined (USE_DEPENDENT_TEXTURE) || (DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE)

	memcpy(m_pDepTexBuffer,             m_pTransferFunction, 4*256*sizeof(unsigned char));
	memcpy((m_pDepTexBuffer + (256*4)), m_pTransferFunction, 4*256*sizeof(unsigned char));

	glBindTexture(GL_TEXTURE_2D, m_nDepTexName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

	glTexImage2D(GL_TEXTURE_2D, // target  
			0,                  // level  
			GL_RGBA,            // internal format 
			256,                // width  
			2,                  // height  
			0,                  // border  
			GL_RGBA,            // format  
			GL_UNSIGNED_BYTE,   // type  
			m_pDepTexBuffer); 
#endif

#endif
}


#ifdef USE_NVIDIA_EXTENSIONS
bool CVolume::initRegisterCombiners() {

	// activate one general combiner only
	glCombinerParameteriNV((GLenum) GL_NUM_GENERAL_COMBINERS_NV, 1);
	
	// First Combiner Stage RGB-Portion
	// ----------------------------------------------
	// Alpha value of const color is used as blending 
	// factor for the RGB components of the two 
	// textures 0 and 1
	
	// input configuration
	//                stage            portion input variable    input register         input mapping             color component
	//--------------------------------------------------------------------------------------------------------------------------------------
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_A_NV, GL_CONSTANT_COLOR0_NV,	GL_UNSIGNED_INVERT_NV,    GL_ALPHA);
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_B_NV, GL_TEXTURE0_ARB, 	    GL_UNSIGNED_IDENTITY_NV,  GL_RGB);	
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_C_NV, GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV,  GL_ALPHA);	
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_D_NV, GL_TEXTURE1_ARB, 	    GL_UNSIGNED_IDENTITY_NV,  GL_RGB);

	// output configuration: component wise A*B + C*D is written to the spare 0 register (RGB)
	//                 stage            portion  A*B Output     C*D output     AB+CD output  scale    bias     AB dot?  CD dot? muxSum?  
	//--------------------------------------------------------------------------------------------------------------------------------------    
	glCombinerOutputNV(GL_COMBINER0_NV, GL_RGB,	 GL_DISCARD_NV, GL_DISCARD_NV, GL_SPARE0_NV, GL_NONE, GL_NONE, FALSE,   FALSE,  FALSE);		  
	glCombinerOutputNV(GL_COMBINER0_NV, GL_RGB,	 GL_DISCARD_NV,	GL_DISCARD_NV, GL_SPARE0_NV, GL_NONE, GL_NONE, FALSE,	FALSE,  FALSE);             

	// First Combiner Stage Alpha-Portion
	// ----------------------------------------------
	// Alpha value of const color is used as blending 
	// factor for the Alpha components of the two 
	// textures 0 and 1

	// input configuration
	//                stage,           portion,  input variable,   input register,        input mapping,           color component,
	//--------------------------------------------------------------------------------------------------------------------------------------
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_A_NV, GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_INVERT_NV,   GL_ALPHA);		
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_B_NV, GL_TEXTURE0_ARB, 	  GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);	
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_C_NV, GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_D_NV, GL_TEXTURE1_ARB, 	  GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);

	// output configuration: alpha component A*B + C*D is written to the spare 0 register (Alpha)
	//                 stage            portion   A*B Output     C*D output     AB+CD output  scale    bias     AB dot?  CD dot? muxSum?  
	//--------------------------------------------------------------------------------------------------------------------------------------    
	glCombinerOutputNV(GL_COMBINER0_NV, GL_ALPHA, GL_DISCARD_NV, GL_DISCARD_NV, GL_SPARE0_NV, GL_NONE, GL_NONE, FALSE, 	 FALSE,  FALSE);


	// Final Combiner Stage
	// ----------------------------------------------
	// The values from the spare0 register are simply 
	// copied to the RGB and Alpha ouput 

	// input configuration
	//                     input variable    input register   input mapping            color component
	//-------------------------------------------------------------------------------------------------
	glFinalCombinerInputNV(GL_VARIABLE_A_NV, GL_ZERO,		  GL_UNSIGNED_IDENTITY_NV, GL_RGB);	
	glFinalCombinerInputNV(GL_VARIABLE_B_NV, GL_ZERO, 		  GL_UNSIGNED_IDENTITY_NV, GL_RGB);	
	glFinalCombinerInputNV(GL_VARIABLE_C_NV, GL_ZERO, 		  GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glFinalCombinerInputNV(GL_VARIABLE_D_NV, GL_SPARE0_NV, 	  GL_UNSIGNED_IDENTITY_NV, GL_RGB);	
  /*glFinalCombinerInputNV(GL_VARIABLE_E_NV, GL_ZERO,   	  GL_UNSIGNED_IDENTITY_NV, GL_RGB); not used */
  /*glFinalCombinerInputNV(GL_VARIABLE_F_NV, GL_ZERO, 	      GL_UNSIGNED_IDENTITY_NV, GL_RGB); not used */
	glFinalCombinerInputNV(GL_VARIABLE_G_NV, GL_SPARE0_NV, 	  GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);
	
	return true;
				
}

#endif USE_NVIDIA_EXTENSIONS

void CVolume::glGetLastError()
{
    GLenum  err = glGetError();
    switch(err)
    {
		
	case GL_NO_ERROR: 
		printf("OpenGL Error:  GL_NO_ERROR\n");
        //AfxMessageBox(_T("OpenGL Error:  GL_NO_ERROR\n"));
        break;
    case GL_INVALID_ENUM : 
		printf("OpenGL Error:  GL_INVALID_ENUM\n");
        //AfxMessageBox(_T("OpenGL Error:  GL_INVALID_ENUM\n"));
        break;
    case GL_INVALID_VALUE: 
		printf("OpenGL Error:  GL_INVALID_VALUE\n");
        //AfxMessageBox(_T("OpenGL Error:  GL_INVALID_VALUE\n"));
        break;
    case GL_INVALID_OPERATION: 
		printf("OpenGL Error:  GL_INVALID_OPERATION\n");
        //AfxMessageBox(_T("OpenGL Error:  GL_INVALID_OPERATION\n"));
        break;
    case GL_STACK_OVERFLOW: 
		//printf("OpenGL Error:  GL_STACK_OVERFLOW\n");
        //AfxMessageBox(_T("OpenGL Error:  GL_STACK_OVERFLOW\n"));
        break;
    case GL_STACK_UNDERFLOW: 
		printf("OpenGL Error:  GL_STACK_UNDERFLOW\n");
        //AfxMessageBox(_T("OpenGL Error:  GL_STACK_UNDERFLOW\n"));
        break;
    case GL_OUT_OF_MEMORY : 
		printf("OpenGL Error:  GL_OUT_OF_MEMORY\n");
        //AfxMessageBox(_T("OpenGL Error:  GL_OUT_OF_MEMORY\n"));
        break;
    }

}

