#if !defined(_VOLUME_H_INCLUDED_)
#define _VOLUME_H_INCLUDED_

/////////////////////////////////////////////////////////////////////////////
// Volume command target

#define COMPUTE_HISTOGRAM

// THERE are 4 different modes to select 
//
// 1. VOLUME_MODE_STANDART_OPENGL   without OpenGL extensions and without a modifyable transfer function (color table)
//
// 2. VOLUME_MODE_TEXTURE_PALETTE   with color table lookup via paletted textures and intermediate slices
//
// 3. VOLUME_MODE_DEPENDENT_TEXTURE with color table lookup via dependent texture, (no intermediate slices, but much faster than 4)
//
// 4. VOLUME_MODE_FRAGMENT_SHADER   with color table lookup via dependent texture and intermediate slices (best quality, but slower than 3)
//
//
// Notes: Mode 4 requires an nVidia GeforceFX board
//        Mode 3 requires an nVidia Geforce4 board or better
//        Mode 2 requires an nVidia Geforce board or better
//        Mode 1 should run on all OpenGL compliant hardware

//#define VOLUME_MODE_TEXTURE_PALETTE 
#define VOLUME_MODE_STANDART_OPENGL
#define VOLUME_MODE_STANDARD_OPENGL


#ifdef VOLUME_MODE_STANDARD_OPENGL
#define VOLUME_MODE_SET
#endif

#ifdef VOLUME_MODE_TEXTURE_PALETTE
#ifdef VOLUME_MODE_SET
#error volume mode is already set! 
#endif
#define VOLUME_MODE_SET
#define USE_NVIDIA_EXTENSIONS 1
#define USE_PALETTED_TEXTURE 1
#define DRAW_INTERMEDIATE_SLICES 1
#endif

#ifdef VOLUME_MODE_DEPENDENT_TEXTURE
#ifdef VOLUME_MODE_SET
#error volume mode is already set!
#endif
#define VOLUME_MODE_SET
#define USE_NVIDIA_EXTENSIONS 1
#define USE_DEPENDENT_TEXTURE 1
#undef  DRAW_INTERMEDIATE_SLICES
#endif

#ifdef VOLUME_MODE_FRAGMENT_SHADER
#ifdef VOLUME_MODE_SET
#error volume mode is already set!
#endif
#define VOLUME_MODE_SET
#define USE_NVIDIA_EXTENSIONS 1
#undef  USE_DEPENDENT_TEXTURE
#define DRAW_INTERMEDIATE_SLICES 1
#define DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE 1
#endif

class CVolume
{
public:
	CVolume(int resolution[3], double voxelSize[3], unsigned char *pBuffer);           
	
	virtual ~CVolume();

// Attributes
public:
	bool render();
	inline unsigned char *getColorTable() {return m_pTransferFunction;};
	inline void setSampling(double d) {m_dSampling = d;};
	inline double getSampling() {return m_dSampling;};
	inline float *getHistogram() {return m_pHistogram;};
	void applyTransferFunction();
	void glGetLastError();

// Operations
public:
	inline void displayBoundingBox(bool on) {m_bRenderBBox = on;}
	inline bool isBoundingBoxVisible() {return m_bRenderBBox;}

// Implementation
protected:
	double m_dSampling;

	unsigned char *m_pVoxelBuffer;
	int            m_nResolution[3];
	double         m_dVoxelSize[3];
	double         m_dCubeDimensions[3];
	bool           m_bRenderBBox;
	bool           m_bRenderVolume;

private:
	double         m_dCubeDimensions_2[3];
	double         m_dTexCorrect[3];
	bool           m_bTexInit;

	unsigned char *m_pTransferFunction;
	float *m_pHistogram;
#ifdef USE_NVIDIA_EXTENSIONS
	bool           m_bExtInit;
#if defined USE_DEPENDENT_TEXTURE || DRAW_INTERMEDIATE_SLICES_DEPT_TEXTURE
	unsigned int   m_nDepTexName;
	unsigned char *m_pDepTexBuffer;
#endif // USE_DEPENDENT_TEXTURE
#endif // USE_NVIDIA_EXTENSIONS

	// methods
	bool createTextures();
	void deleteTextures();
	bool renderVolume();
	bool renderBoundingBox();
#ifdef USE_NVIDIA_EXTENSIONS
	bool initRegisterCombiners();
#endif // USE_NVIDIA_EXTENSIONS

	unsigned int *m_pTexNames[3];

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_VOLUME_H_INCLUDED_)
